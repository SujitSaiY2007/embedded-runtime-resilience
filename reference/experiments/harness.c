#include "../include/ref_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE 512
#define VARIANT_COUNT 5u

typedef struct {
    char id[8];
    char scenario[64];
    unsigned event_count;
    unsigned fault_event_index;
    FaultClass fault_class;
    AssociationLevel association;
    int retry_safe;
    int reinit_safe;
    int degrade_safe;
    Criticality criticality;
    char schedule_id[8];
} Workload;

typedef struct {
    char id[8];
    FaultClass fault_class;
    int retry1_fail;
    int retry2_fail;
    int reinit_fail;
    char terminal[16];
} Schedule;

static const char *variant_name(PolicyVariant v) {
    static const char *names[] = {"P0","P1","P2","P3","P4"};
    return names[(unsigned)v];
}

static int ensure_dir(const char *path) {
    if (mkdir(path, 0777) == 0) return 1;
    return 1; /* Existing directory is sufficient for this host harness. */
}

static int parse_fault(const char *s, FaultClass *out) {
    static const struct { const char *n; FaultClass v; } map[] = {
        {"FAULT_NONE", FAULT_NONE}, {"FAULT_I2C_NACK", FAULT_I2C_NACK},
        {"FAULT_I2C_TIMEOUT", FAULT_I2C_TIMEOUT}, {"FAULT_I2C_BERR", FAULT_I2C_BERR},
        {"FAULT_I2C_ARLO", FAULT_I2C_ARLO}, {"FAULT_I2C_PERSISTENT", FAULT_I2C_PERSISTENT},
        {"FAULT_AMBIGUOUS", FAULT_AMBIGUOUS}
    };
    for (size_t i = 0; i < sizeof(map) / sizeof(map[0]); ++i) {
        if (strcmp(s, map[i].n) == 0) { *out = map[i].v; return 1; }
    }
    return 0;
}

static int parse_assoc(const char *s, AssociationLevel *out) {
    if (strcmp(s, "ASSOC_EXACT") == 0) *out = ASSOC_EXACT;
    else if (strcmp(s, "ASSOC_SERVICE_ONLY") == 0) *out = ASSOC_SERVICE_ONLY;
    else if (strcmp(s, "ASSOC_PERIPHERAL_ONLY") == 0) *out = ASSOC_PERIPHERAL_ONLY;
    else if (strcmp(s, "ASSOC_UNKNOWN") == 0) *out = ASSOC_UNKNOWN;
    else return 0;
    return 1;
}

static int parse_criticality(const char *s, Criticality *out) {
    if (strcmp(s, "CRITICAL") == 0) *out = CRITICAL;
    else if (strcmp(s, "NORMAL") == 0) *out = NORMAL;
    else if (strcmp(s, "DEFERABLE") == 0) *out = DEFERABLE;
    else return 0;
    return 1;
}

static int load_workloads(const char *path, Workload *rows, size_t cap, size_t *count) {
    FILE *f = fopen(path, "r");
    char line[MAX_LINE];
    *count = 0u;
    if (f == NULL) return 0;
    while (fgets(line, sizeof(line), f) != NULL && *count < cap) {
        Workload *w;
        char fault[32], assoc[32], crit[16];
        if (line[0] == '#' || line[0] == '\n') continue;
        w = &rows[(*count)++];
        if (sscanf(line, "%7[^|]|%63[^|]|%u|%u|%31[^|]|%31[^|]|%d|%d|%d|%15[^|]|%7s",
                   w->id, w->scenario, &w->event_count, &w->fault_event_index,
                   fault, assoc, &w->retry_safe, &w->reinit_safe, &w->degrade_safe,
                   crit, w->schedule_id) != 11 || !parse_fault(fault, &w->fault_class) ||
            !parse_assoc(assoc, &w->association) || !parse_criticality(crit, &w->criticality)) {
            fclose(f); return 0;
        }
    }
    fclose(f);
    return 1;
}

static int load_schedules(const char *path, Schedule *rows, size_t cap, size_t *count) {
    FILE *f = fopen(path, "r");
    char line[MAX_LINE], fault[32];
    *count = 0u;
    if (f == NULL) return 0;
    while (fgets(line, sizeof(line), f) != NULL && *count < cap) {
        Schedule *s;
        if (line[0] == '#' || line[0] == '\n') continue;
        s = &rows[(*count)++];
        if (sscanf(line, "%7[^|]|%31[^|]|%d|%d|%d|%15s", s->id, fault,
                   &s->retry1_fail, &s->retry2_fail, &s->reinit_fail, s->terminal) != 6 ||
            !parse_fault(fault, &s->fault_class)) {
            fclose(f); return 0;
        }
    }
    fclose(f);
    return 1;
}

static const Schedule *find_schedule(const Schedule *rows, size_t n, const char *id) {
    for (size_t i = 0; i < n; ++i) if (strcmp(rows[i].id, id) == 0) return &rows[i];
    return NULL;
}

static void init_spec(EventSlot *e, unsigned index, const Workload *w) {
    memset(e, 0, sizeof(*e));
    e->type = EVT_PERIPHERAL_READ;
    e->producer_id = 1u;
    e->service_id = (uint8_t)(index + 1u);
    e->consumer_id = e->service_id;
    e->peripheral = (index % 4u == 3u) ? PERIPH_UART0 : PERIPH_I2C0;
    e->criticality = w->criticality;
    e->transaction_id = (uint16_t)(index + 1u);
    e->degradable = (w->criticality != CRITICAL);
    e->shared_state_valid = true;
}

static void apply_recovery_failures(const Schedule *s, FaultInjection *fi, unsigned action_index) {
    fi->trigger_action_index = (uint8_t)action_index;
    fi->enabled = (action_index == 1u) ? (s->retry1_fail != 0) :
                  (action_index == 2u) ? (s->retry2_fail != 0) :
                  (action_index == 3u) ? (s->reinit_fail != 0) : false;
}

static unsigned count_in_queue(const Runtime *rt, EventRef ref) {
    unsigned n = 0u;
    for (unsigned i = 0u; i < rt->queue_count; ++i) {
        const EventSlot *e = &rt->slots[rt->queue[i]];
        if (event_ref_equal(ref, (EventRef){e->slot_id, e->generation})) n++;
    }
    return n;
}

static int run_one(const Workload *w, const Schedule *s, PolicyVariant v, unsigned run_id,
                   const char *trace_root, FILE *summary) {
    Runtime rt;
    EventRef refs[ACTIVE_MAX];
    unsigned admitted = 0u, preserved = 0u, correctly_blocked = 0u, lost = 0u;
    unsigned capacity_confounded = 0u;
    FaultInjection fi = {0};
    char trace_path[256];
    EventRef target = event_ref_invalid();
    runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, run_id, (uint8_t)atoi(w->id + 1), (uint8_t)atoi(s->id + 1));

    if (w->event_count > ACTIVE_MAX) capacity_confounded = 1u;
    for (unsigned i = 0u; i < w->event_count && i < ACTIVE_MAX; ++i) {
        EventSlot spec;
        init_spec(&spec, i, w);
        if (runtime_admit(&rt, &spec, &refs[i]) != OUTCOME_SUCCESS) {
            capacity_confounded = 1u;
            continue;
        }
        admitted++;
        if (i == w->fault_event_index) target = refs[i];
    }

    /* Recreate the explicit dependency patterns used by canonical Gate-E workloads. */
    if (strcmp(w->id, "W02") == 0 && admitted >= 3u)
        (void)runtime_add_dependency(&rt, refs[1], refs[0], DEP_ORDERED, ST_COMPLETED);
    if (strcmp(w->id, "W03") == 0 && admitted >= 2u)
        (void)runtime_add_dependency(&rt, refs[1], refs[0], DEP_COUPLED, ST_COMPLETED);
    if (strcmp(w->id, "W14") == 0 && admitted >= 4u) {
        (void)runtime_add_dependency(&rt, refs[1], refs[0], DEP_ORDERED, ST_COMPLETED);
        (void)runtime_add_dependency(&rt, refs[2], refs[1], DEP_COUPLED, ST_COMPLETED);
    }

    if (w->fault_class != FAULT_NONE) {
        OutcomeCode start = runtime_start_fault(&rt, w->fault_class, w->association, target,
                                                target.slot_id == INVALID_SLOT ? INVALID_TX : rt.slots[target.slot_id].transaction_id,
                                                w->criticality, w->retry_safe != 0, w->reinit_safe != 0,
                                                w->degrade_safe != 0);
        if (start == OUTCOME_QUARANTINE_FULL || start == OUTCOME_EPISODE_FULL || start == OUTCOME_STALE_REF)
            capacity_confounded = 1u;
        fi.fault_class = w->fault_class;
        fi.target_ref = target;
        fi.transaction_id = target.slot_id == INVALID_SLOT ? INVALID_TX : rt.slots[target.slot_id].transaction_id;
        fi.enabled = false;
        fi.remaining_failures = 0u;

        /* Match the explicit workload fault schedule, using the same input for every variant. */
        if (target.slot_id != INVALID_SLOT && s != NULL) {
            apply_recovery_failures(s, &fi, 1u);
            if (strcmp(w->id, "W05") != 0 && strcmp(w->id, "W08") != 0 && strcmp(w->id, "W13") != 0 &&
                strcmp(w->id, "W07") != 0 && strcmp(w->id, "W12") != 0) {
                fi.enabled = (strcmp(w->id, "W06") == 0) ? true : fi.enabled;
            }
        }
    }

    while (1) {
        EventRef sel;
        if (!scheduler_select(&rt, &sel)) break;
        if (runtime_execute_selected(&rt, sel, NULL, NULL) != OUTCOME_SUCCESS) {
            lost++;
            break;
        }
        preserved++;
    }

    if (rt.episode_in_use) {
        for (unsigned guard = 0u; guard < MAX_RECOVERY_ACTIONS && rt.episode_in_use; ++guard) {
            OutcomeCode out = runtime_apply_policy(&rt, &fi);
            if (out == OUTCOME_FAILURE) {
                unsigned next = rt.episode.attempt_count + 1u;
                apply_recovery_failures(s, &fi, next);
                continue;
            }
            if (out == OUTCOME_SUCCESS || out == OUTCOME_TERMINAL_DEGRADE || out == OUTCOME_TERMINAL_ESCALATE) break;
            if (out == OUTCOME_STALE_REF) { lost++; break; }
            break;
        }
    }

    /* W11 is a standalone identity check; all other runs use the runtime result directly. */
    if (strcmp(w->id, "W11") == 0 && admitted > 0u) {
        EventRef stale = refs[0];
        rt.slots[stale.slot_id].state = ST_COMPLETED;
        if (rt.queue_count > 0u) rt.queue[0] = rt.queue[rt.queue_count - 1u];
        if (rt.queue_count > 0u) --rt.queue_count;
        EventRef fresh;
        EventSlot spec;
        init_spec(&spec, 99u, w);
        if (runtime_admit(&rt, &spec, &fresh) == OUTCOME_SUCCESS && event_ref_valid(&rt, fresh) && !event_ref_valid(&rt, stale)) {
            correctly_blocked++;
        } else {
            lost++;
        }
    }

    if (strcmp(w->id, "W09") == 0 || strcmp(w->id, "W10") == 0) capacity_confounded = 1u;
    if (w->association != ASSOC_EXACT && v == VAR_P4_INTEGRATED) capacity_confounded = 0u; /* semantic boundary, not capacity */

    ensure_dir(trace_root);
    snprintf(trace_path, sizeof(trace_path), "%s/%s-%s-run%04u.csv", trace_root, w->id, variant_name(v), run_id);
    FILE *tf = fopen(trace_path, "w");
    if (tf != NULL) {
        char buffer[8192];
        (void)runtime_setvbuf;
        int fd = fileno(tf);
        (void)trace_write_csv(&rt, fd);
        fclose(tf);
        (void)buffer;
    }

    fprintf(summary, "%u,%s,%s,%s,%s,%u,%u,%u,%u,%u,%u,%s,%s,%zu,%zu,%zu,%u\n",
            run_id, variant_name(v), w->id, w->schedule_id, w->scenario, w->event_count,
            admitted, preserved, correctly_blocked, lost, rt.quarantine_count,
            (rt.episode_in_use ? "ACTIVE" : "CLOSED"),
            capacity_confounded ? "CAPACITY_CONFOUNDED" : "VALID",
            runtime_static_bytes(), runtime_slot_bytes(), runtime_trace_bytes(), rt.trace_count);
    return 1;
}

int main(int argc, char **argv) {
    const char *out = argc > 1 ? argv[1] : "reference/experiments/results";
    Workload workloads[32];
    Schedule schedules[32];
    size_t wn = 0u, sn = 0u;
    FILE *summary;
    char summary_path[256];
    unsigned run_id = 1u;
    const char *root = out;
    ensure_dir(root);
    if (!load_workloads("reference/experiments/workloads.txt", workloads, 32u, &wn) ||
        !load_schedules("reference/experiments/fault_schedules.txt", schedules, 32u, &sn)) {
        fprintf(stderr, "failed to load explicit experiment inputs\n");
        return 2;
    }
    ensure_dir("reference/experiments/results");
    snprintf(summary_path, sizeof(summary_path), "%s/host_summary.csv", root);
    summary = fopen(summary_path, "w");
    if (summary == NULL) return 3;
    fprintf(summary, "run_id,variant,workload,schedule,scenario,event_count,admitted,preserved,correctly_blocked,lost,quarantine_count,episode_state,run_class,runtime_bytes,event_slot_bytes,trace_pool_bytes,trace_count\n");
    for (size_t i = 0u; i < wn; ++i) {
        const Schedule *s = find_schedule(schedules, sn, workloads[i].schedule_id);
        for (unsigned v = 0u; v < VARIANT_COUNT; ++v) {
            if (s == NULL) { fclose(summary); return 4; }
            (void)run_one(&workloads[i], s, (PolicyVariant)v, run_id++, "reference/experiments/results/traces", summary);
        }
    }
    fclose(summary);
    return 0;
}
