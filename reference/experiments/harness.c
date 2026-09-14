#include "../include/ref_runtime.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LINE 512
#define MAX_WORKLOADS 32u
#define MAX_SCHEDULES 32u
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
    static const char *names[] = {"P0", "P1", "P2", "P3", "P4"};
    return names[(unsigned)v];
}

static int ensure_dir(const char *path) {
    if (mkdir(path, 0777) == 0) return 1;
    return errno == EEXIST;
}

static int parse_fault(const char *s, FaultClass *out) {
    static const struct { const char *n; FaultClass v; } map[] = {
        {"FAULT_NONE", FAULT_NONE},
        {"FAULT_I2C_NACK", FAULT_I2C_NACK},
        {"FAULT_I2C_TIMEOUT", FAULT_I2C_TIMEOUT},
        {"FAULT_I2C_BERR", FAULT_I2C_BERR},
        {"FAULT_I2C_ARLO", FAULT_I2C_ARLO},
        {"FAULT_I2C_PERSISTENT", FAULT_I2C_PERSISTENT},
        {"FAULT_AMBIGUOUS", FAULT_AMBIGUOUS}
    };
    for (size_t i = 0u; i < sizeof(map) / sizeof(map[0]); ++i) {
        if (strcmp(s, map[i].n) == 0) {
            *out = map[i].v;
            return 1;
        }
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
                   crit, w->schedule_id) != 11 ||
            !parse_fault(fault, &w->fault_class) ||
            !parse_assoc(assoc, &w->association) ||
            !parse_criticality(crit, &w->criticality)) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return *count > 0u;
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
        if (sscanf(line, "%7[^|]|%31[^|]|%d|%d|%d|%15s",
                   s->id, fault, &s->retry1_fail, &s->retry2_fail,
                   &s->reinit_fail, s->terminal) != 6 ||
            !parse_fault(fault, &s->fault_class)) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return *count > 0u;
}

static const Schedule *find_schedule(const Schedule *rows, size_t n, const char *id) {
    for (size_t i = 0u; i < n; ++i) {
        if (strcmp(rows[i].id, id) == 0) return &rows[i];
    }
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
    e->degradable = (w->degrade_safe != 0);
    e->shared_state_valid = true;
}

static void set_injection_for_action(const Schedule *s, FaultInjection *fi, unsigned action_index) {
    fi->trigger_action_index = (uint8_t)action_index;
    fi->enabled = false;
    if (action_index == 1u) fi->enabled = s->retry1_fail != 0;
    else if (action_index == 2u) fi->enabled = s->retry2_fail != 0;
    else if (action_index == 3u) fi->enabled = s->reinit_fail != 0;
}

static void add_canonical_dependencies(Runtime *rt, const Workload *w, const EventRef *refs, unsigned admitted) {
    if (strcmp(w->id, "W02") == 0 && admitted >= 3u)
        (void)runtime_add_dependency(rt, refs[1], refs[0], DEP_ORDERED, ST_COMPLETED);
    else if (strcmp(w->id, "W03") == 0 && admitted >= 2u)
        (void)runtime_add_dependency(rt, refs[1], refs[0], DEP_COUPLED, ST_COMPLETED);
    else if (strcmp(w->id, "W14") == 0 && admitted >= 4u) {
        (void)runtime_add_dependency(rt, refs[1], refs[0], DEP_ORDERED, ST_COMPLETED);
        (void)runtime_add_dependency(rt, refs[2], refs[1], DEP_COUPLED, ST_COMPLETED);
    }
}

static void write_trace_file(const Runtime *rt, const char *path) {
    FILE *f = fopen(path, "w");
    if (f == NULL) return;
    (void)trace_write_csv(rt, fileno(f));
    fclose(f);
}

static void emit_result(FILE *summary, unsigned run_id, const Workload *w, const Schedule *s,
                        PolicyVariant variant, const Runtime *rt, unsigned admitted,
                        unsigned preserved, unsigned correctly_blocked, unsigned incorrectly_blocked,
                        unsigned capacity_confounded, unsigned trace_complete) {
    fprintf(summary,
            "%u,%s,%s,%s,%s,%u,%u,%u,%u,%u,%u,%u,%u,%u,%zu,%zu,%zu,%u\n",
            run_id, variant_name(variant), w->id, s->id, w->scenario, w->event_count,
            admitted, preserved, correctly_blocked, incorrectly_blocked,
            rt->quarantine_count, rt->episode_in_use ? 1u : 0u,
            capacity_confounded, trace_complete,
            runtime_static_bytes(), runtime_slot_bytes(), runtime_trace_bytes(), rt->trace_count);
}

static int run_one(const Workload *w, const Schedule *s, PolicyVariant variant,
                   unsigned run_id, const char *trace_dir, FILE *summary) {
    Runtime rt;
    EventRef refs[ACTIVE_MAX];
    EventRef target = event_ref_invalid();
    FaultInjection injection = {0};
    unsigned admitted = 0u;
    unsigned preserved = 0u;
    unsigned correctly_blocked = 0u;
    unsigned incorrectly_blocked = 0u;
    unsigned capacity_confounded = 0u;
    unsigned trace_complete = 1u;
    unsigned pre_fault_admitted;
    unsigned initial_quarantine;

    memset(refs, 0, sizeof(refs));
    runtime_init(&rt, variant);
    runtime_set_trace_metadata(&rt, run_id,
                               (uint8_t)(w->id[1] >= '0' && w->id[1] <= '9' ? w->id[1] - '0' : 0u),
                               (uint8_t)(s->id[1] >= '0' && s->id[1] <= '9' ? s->id[1] - '0' : 0u));

    if (w->event_count > ACTIVE_MAX) capacity_confounded = 1u;
    for (unsigned i = 0u; i < w->event_count && i < ACTIVE_MAX; ++i) {
        EventSlot spec;
        init_spec(&spec, i, w);
        if (runtime_admit(&rt, &spec, &refs[i]) != OUTCOME_SUCCESS) {
            capacity_confounded = 1u;
            continue;
        }
        ++admitted;
        if (i == w->fault_event_index) target = refs[i];
    }
    pre_fault_admitted = admitted;
    add_canonical_dependencies(&rt, w, refs, admitted);

    if (w->fault_class != FAULT_NONE) {
        uint16_t tx = INVALID_TX;
        if (event_ref_valid(&rt, target)) tx = rt.slots[target.slot_id].transaction_id;
        OutcomeCode start = runtime_start_fault(&rt, w->fault_class, w->association, target, tx,
                                                w->criticality, w->retry_safe != 0,
                                                w->reinit_safe != 0, w->degrade_safe != 0);
        if (start != OUTCOME_SUCCESS) {
            capacity_confounded = (start == OUTCOME_QUEUE_FULL || start == OUTCOME_QUARANTINE_FULL ||
                                    start == OUTCOME_EPISODE_FULL) ? 1u : capacity_confounded;
        }
        injection.fault_class = w->fault_class;
        injection.target_ref = target;
        injection.transaction_id = tx;
        injection.enabled = false;
    }
    initial_quarantine = rt.quarantine_count;

    /* Drain all ordinary eligible work after fault admission. The target itself is not ordinary-dispatchable. */
    for (;;) {
        EventRef selected;
        if (!scheduler_select(&rt, &selected)) break;
        OutcomeCode out = runtime_execute_selected(&rt, selected, NULL, NULL);
        if (out != OUTCOME_SUCCESS) {
            ++incorrectly_blocked;
            break;
        }
        if (selected.slot_id != target.slot_id || selected.generation != target.generation)
            ++preserved;
    }

    /* Apply the same explicit schedule to all variants. */
    for (unsigned guard = 0u; guard < MAX_RECOVERY_ACTIONS && rt.episode_in_use; ++guard) {
        unsigned next_action = rt.episode.attempt_count + 1u;
        set_injection_for_action(s, &injection, next_action);
        OutcomeCode out = runtime_apply_policy(&rt, &injection);
        if (out == OUTCOME_FAILURE) continue;
        if (out == OUTCOME_SUCCESS || out == OUTCOME_TERMINAL_DEGRADE || out == OUTCOME_TERMINAL_ESCALATE)
            break;
        if (out == OUTCOME_EPISODE_FULL || out == OUTCOME_QUARANTINE_FULL || out == OUTCOME_STALE_REF) {
            capacity_confounded = 1u;
            break;
        }
        break;
    }

    /* W11 is the frozen identity-boundary case and is not a performance result. */
    if (strcmp(w->id, "W11") == 0 && pre_fault_admitted > 0u) {
        EventRef stale = refs[0];
        EventSlot fresh_spec;
        EventRef fresh;
        rt.slots[stale.slot_id].state = ST_COMPLETED;
        if (rt.queue_count > 0u) --rt.queue_count;
        init_spec(&fresh_spec, 99u, w);
        if (runtime_admit(&rt, &fresh_spec, &fresh) == OUTCOME_SUCCESS &&
            !event_ref_valid(&rt, stale) && event_ref_valid(&rt, fresh)) {
            ++correctly_blocked;
        } else {
            ++incorrectly_blocked;
        }
    }

    if (strcmp(w->id, "W09") == 0 || strcmp(w->id, "W10") == 0 || w->event_count >= QMAX || initial_quarantine >= XMAX)
        capacity_confounded = 1u;

    if (rt.trace_count == TRACE_EVENT_CAP) trace_complete = 0u;

    {
        char path[256];
        if (snprintf(path, sizeof(path), "%s/%s-%s-run%04u.csv", trace_dir, w->id,
                     variant_name(variant), run_id) < (int)sizeof(path)) {
            write_trace_file(&rt, path);
        }
    }
    emit_result(summary, run_id, w, s, variant, &rt, admitted, preserved,
                correctly_blocked, incorrectly_blocked, capacity_confounded, trace_complete);
    return 1;
}

int main(int argc, char **argv) {
    const char *out_root = argc > 1 ? argv[1] : "reference/experiments/results";
    char trace_dir[256];
    char summary_path[256];
    Workload workloads[MAX_WORKLOADS];
    Schedule schedules[MAX_SCHEDULES];
    size_t workload_count = 0u;
    size_t schedule_count = 0u;
    unsigned run_id = 1u;
    FILE *summary;

    (void)ensure_dir(out_root);
    if (snprintf(trace_dir, sizeof(trace_dir), "%s/traces", out_root) >= (int)sizeof(trace_dir)) return 2;
    if (snprintf(summary_path, sizeof(summary_path), "%s/host_summary.csv", out_root) >= (int)sizeof(summary_path)) return 2;
    (void)ensure_dir(trace_dir);

    if (!load_workloads("reference/experiments/workloads.txt", workloads, MAX_WORKLOADS, &workload_count) ||
        !load_schedules("reference/experiments/fault_schedules.txt", schedules, MAX_SCHEDULES, &schedule_count)) {
        fprintf(stderr, "failed to load explicit experiment inputs\n");
        return 3;
    }

    summary = fopen(summary_path, "w");
    if (summary == NULL) return 4;
    fprintf(summary,
            "run_id,variant,workload,schedule,scenario,event_count,admitted,preserved,correctly_blocked,"
            "incorrectly_blocked,quarantine_count,episode_active,capacity_confounded,trace_complete,"
            "runtime_bytes,event_slot_bytes,trace_pool_bytes,trace_count\n");

    for (size_t i = 0u; i < workload_count; ++i) {
        const Schedule *s = find_schedule(schedules, schedule_count, workloads[i].schedule_id);
        if (s == NULL || s->fault_class != workloads[i].fault_class) {
            fclose(summary);
            fprintf(stderr, "workload %s has no matching explicit schedule\n", workloads[i].id);
            return 5;
        }
        for (unsigned v = 0u; v < VARIANT_COUNT; ++v) {
            if (!run_one(&workloads[i], s, (PolicyVariant)v, run_id++, trace_dir, summary)) {
                fclose(summary);
                return 6;
            }
        }
    }
    fclose(summary);
    return 0;
}
