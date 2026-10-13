#include "virtual_system.h"
#include "virtual_scenarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <crtdbg.h>
#endif

static const char *state_to_str(EventState s) {
    switch (s) {
        case ST_FREE: return "ST_FREE";
        case ST_QUEUED: return "ST_QUEUED";
        case ST_ELIGIBLE: return "ST_ELIGIBLE";
        case ST_EXECUTING: return "ST_EXECUTING";
        case ST_FAILED: return "ST_FAILED";
        case ST_QUARANTINED: return "ST_QUARANTINED";
        case ST_RETRY_PENDING: return "ST_RETRY_PENDING";
        case ST_COMPLETED: return "ST_COMPLETED";
        case ST_DISCARDED: return "ST_DISCARDED";
        case ST_ESCALATED: return "ST_ESCALATED";
        default: return "UNKNOWN";
    }
}

static const char *action_to_str(RecoveryAction a) {
    switch (a) {
        case ACT_NONE: return "ACT_NONE";
        case ACT_RETRY: return "ACT_RETRY";
        case ACT_REINIT_OR_RESET: return "ACT_REINIT_OR_RESET";
        case ACT_DEGRADE: return "ACT_DEGRADE";
        case ACT_ESCALATE: return "ACT_ESCALATE";
        default: return "UNKNOWN";
    }
}

static const char *outcome_to_str(OutcomeCode o) {
    switch (o) {
        case OUTCOME_NONE: return "OUTCOME_NONE";
        case OUTCOME_SUCCESS: return "OUTCOME_SUCCESS";
        case OUTCOME_FAILURE: return "OUTCOME_FAILURE";
        case OUTCOME_TERMINAL_DEGRADE: return "OUTCOME_TERMINAL_DEGRADE";
        case OUTCOME_TERMINAL_ESCALATE: return "OUTCOME_TERMINAL_ESCALATE";
        case OUTCOME_QUEUE_FULL: return "OUTCOME_QUEUE_FULL";
        case OUTCOME_QUARANTINE_FULL: return "OUTCOME_QUARANTINE_FULL";
        case OUTCOME_EPISODE_FULL: return "OUTCOME_EPISODE_FULL";
        case OUTCOME_STALE_REF: return "OUTCOME_STALE_REF";
        case OUTCOME_INVALID_DEPENDENCY: return "OUTCOME_INVALID_DEPENDENCY";
        default: return "UNKNOWN";
    }
}

static const char *periph_to_str(PeripheralId p) {
    switch (p) {
        case PERIPH_NONE: return "NONE";
        case PERIPH_I2C0: return "I2C0";
        case PERIPH_SPI0: return "SPI0";
        case PERIPH_UART0: return "UART0";
        default: return "UNKNOWN";
    }
}

static const char *periph_status_to_str(VirtualPeripheralStatus s) {
    switch (s) {
        case VPERIPH_READY: return "READY";
        case VPERIPH_SUCCESS: return "SUCCESS";
        case VPERIPH_NACK: return "NACK";
        case VPERIPH_TIMEOUT: return "TIMEOUT";
        case VPERIPH_PROTOCOL_ERROR: return "PROTOCOL_ERROR";
        case VPERIPH_ARBITRATION_ERROR: return "ARBITRATION_ERROR";
        case VPERIPH_VERIFY_FAILURE: return "VERIFY_FAILURE";
        case VPERIPH_PERSISTENT_FAILURE: return "PERSISTENT_FAILURE";
        default: return "UNKNOWN";
    }
}

static const char *fault_class_to_str(FaultClass f) {
    switch (f) {
        case FAULT_NONE: return "NONE";
        case FAULT_I2C_NACK: return "I2C_NACK";
        case FAULT_I2C_TIMEOUT: return "I2C_TIMEOUT";
        case FAULT_I2C_BERR: return "I2C_BERR";
        case FAULT_I2C_ARLO: return "I2C_ARLO";
        case FAULT_I2C_PERSISTENT: return "I2C_PERSISTENT";
        case FAULT_SPI_TIMEOUT: return "SPI_TIMEOUT";
        case FAULT_SPI_VERIFY: return "SPI_VERIFY";
        case FAULT_SPI_PERSISTENT: return "SPI_PERSISTENT";
        case FAULT_SW_SERVICE: return "SW_SERVICE";
        case FAULT_AMBIGUOUS: return "AMBIGUOUS";
        default: return "UNKNOWN";
    }
}

static const char *crit_to_str(Criticality c) {
    switch (c) {
        case CRITICAL: return "CRITICAL";
        case NORMAL: return "NORMAL";
        case DEFERABLE: return "DEFERABLE";
        default: return "UNKNOWN";
    }
}

static const char *step_kind_to_str(VirtualStepKind k) {
    switch (k) {
        case VSTEP_ADMIT: return "VSTEP_ADMIT";
        case VSTEP_DEPEND: return "VSTEP_DEPEND";
        case VSTEP_START_FAULT: return "VSTEP_START_FAULT";
        case VSTEP_DRAIN: return "VSTEP_DRAIN";
        case VSTEP_APPLY_FAULT: return "VSTEP_APPLY_FAULT";
        default: return "UNKNOWN";
    }
}

static void print_json_state(FILE *f, const VirtualSystem *vs, const char *scenario_id,
                             const char *scenario_name, const char *scenario_desc) {
    fprintf(f, "{\n");
    fprintf(f, "  \"scenario_id\": \"%s\",\n", scenario_id);
    fprintf(f, "  \"scenario_name\": \"%s\",\n", scenario_name);
    fprintf(f, "  \"scenario_description\": \"%s\",\n", scenario_desc);
    fprintf(f, "  \"run_id\": %u,\n", vs->run_id);
    fprintf(f, "  \"variant\": %u,\n", (unsigned)vs->runtime.variant);
    fprintf(f, "  \"step_index\": %u,\n", vs->step_index);
    fprintf(f, "  \"step_count\": %u,\n", vs->scenario->step_count);
    fprintf(f, "  \"is_complete\": %s,\n", virtual_system_complete(vs) ? "true" : "false");
    fprintf(f, "  \"adapter_error\": %s,\n", vs->adapter_error ? "true" : "false");
    fprintf(f, "  \"adapter_error_message\": \"%s\",\n", vs->adapter_error ? "A scenario references a disconnected or invalid virtual resource" : "");
    fprintf(f, "  \"outcome_code\": %u,\n", (unsigned)vs->last_outcome);
    fprintf(f, "  \"outcome_str\": \"%s\",\n", outcome_to_str(vs->last_outcome));
    fprintf(f, "  \"digest\": \"0x%08X\",\n", virtual_system_digest(vs));
    fprintf(f, "  \"runtime_authoritative\": true,\n");

    /* Current step info */
    if (vs->step_index > 0u && vs->step_index <= vs->scenario->step_count) {
        const VirtualStep *curr = &vs->scenario->steps[vs->step_index - 1u];
        fprintf(f, "  \"last_executed_step\": {\n");
        fprintf(f, "    \"sequence\": %u,\n", curr->sequence);
        fprintf(f, "    \"kind\": \"%s\",\n", step_kind_to_str(curr->kind));
        fprintf(f, "    \"a\": %u, \"b\": %u, \"c\": %u, \"d\": %u\n",
                curr->a, curr->b, curr->c, curr->d);
        fprintf(f, "  },\n");
    } else {
        fprintf(f, "  \"last_executed_step\": null,\n");
    }

    if (vs->step_index < vs->scenario->step_count) {
        const VirtualStep *next = &vs->scenario->steps[vs->step_index];
        fprintf(f, "  \"next_step\": {\n");
        fprintf(f, "    \"sequence\": %u,\n", next->sequence);
        fprintf(f, "    \"kind\": \"%s\",\n", step_kind_to_str(next->kind));
        fprintf(f, "    \"a\": %u, \"b\": %u, \"c\": %u, \"d\": %u\n",
                next->a, next->b, next->c, next->d);
        fprintf(f, "  },\n");
    } else {
        fprintf(f, "  \"next_step\": null,\n");
    }

    /* Episode & Policy */
    PolicyDecision pd = {ACT_NONE, ASSOC_UNKNOWN, false, false, false, false, 0u, 0u};
    if (vs->runtime.episode_in_use) {
        pd = policy_decide(&vs->runtime, &vs->runtime.episode);
    }
    fprintf(f, "  \"episode\": {\n");
    fprintf(f, "    \"in_use\": %s,\n", vs->runtime.episode_in_use ? "true" : "false");
    fprintf(f, "    \"episode_id\": %u,\n", vs->runtime.active_fault_episode_id);
    fprintf(f, "    \"attempt_count\": %u,\n", vs->runtime.episode.attempt_count);
    fprintf(f, "    \"target_slot\": %u,\n", vs->runtime.episode.target_ref.slot_id);
    fprintf(f, "    \"target_gen\": %u,\n", vs->runtime.episode.target_ref.generation);
    fprintf(f, "    \"fault_class\": \"%s\",\n", fault_class_to_str(vs->runtime.episode.fault_class));
    fprintf(f, "    \"observation_count\": %u,\n", vs->runtime.episode.observation_count);
    fprintf(f, "    \"policy_action\": \"%s\",\n", action_to_str(pd.action));
    fprintf(f, "    \"quarantine_required\": %s,\n", pd.quarantine_required ? "true" : "false");
    fprintf(f, "    \"terminal\": %s\n", pd.terminal ? "true" : "false");
    fprintf(f, "  },\n");

    /* Slots */
    fprintf(f, "  \"active_slots\": [\n");
    bool first_slot = true;
    for (uint8_t i = 0u; i < ACTIVE_MAX; ++i) {
        const EventSlot *s = &vs->runtime.slots[i];
        if (s->state == ST_FREE) continue;
        if (!first_slot) fprintf(f, ",\n");
        first_slot = false;
        bool is_quarantined = (s->state == ST_FAILED || s->state == ST_QUARANTINED || s->state == ST_RETRY_PENDING);
        bool is_eligible = ordinary_dispatch_allowed(&vs->runtime, s);
        fprintf(f, "    {\n");
        fprintf(f, "      \"slot_id\": %u,\n", i);
        fprintf(f, "      \"generation\": %u,\n", s->generation);
        fprintf(f, "      \"ref_str\": \"%u:%u\",\n", i, s->generation);
        fprintf(f, "      \"tx_id\": %u,\n", s->transaction_id);
        fprintf(f, "      \"state\": \"%s\",\n", state_to_str(s->state));
        fprintf(f, "      \"peripheral\": \"%s\",\n", periph_to_str(s->peripheral));
        fprintf(f, "      \"criticality\": \"%s\",\n", crit_to_str(s->criticality));
        fprintf(f, "      \"quarantined\": %s,\n", is_quarantined ? "true" : "false");
        fprintf(f, "      \"fault_associated\": %s,\n", s->fault_associated ? "true" : "false");
        fprintf(f, "      \"eligible\": %s,\n", is_eligible ? "true" : "false");
        fprintf(f, "      \"degradable\": %s,\n", s->degradable ? "true" : "false");
        fprintf(f, "      \"dep_count\": %u\n", s->dependency_count);
        fprintf(f, "    }");
    }
    fprintf(f, "\n  ],\n");

    /* Peripherals */
    fprintf(f, "  \"peripherals\": [\n");
    for (uint8_t p = 1u; p <= VIRTUAL_MAX_PERIPHERALS; ++p) {
        VirtualPeripheralStatus pstat = VPERIPH_READY;
        FaultClass pfc = FAULT_NONE;
        for (int k = (int)vs->peripheral_trace_count - 1; k >= 0; --k) {
            if (vs->peripheral_trace[k].peripheral == (PeripheralId)p) {
                pstat = vs->peripheral_trace[k].status;
                pfc = vs->peripheral_trace[k].fault_class;
                break;
            }
        }
        fprintf(f, "    {\n");
        fprintf(f, "      \"id\": %u,\n", p);
        fprintf(f, "      \"name\": \"%s\",\n", periph_to_str((PeripheralId)p));
        fprintf(f, "      \"status\": \"%s\",\n", vs->peripheral_connected[p - 1u] ? periph_status_to_str(pstat) : "DISCONNECTED");
        fprintf(f, "      \"fault_class\": \"%s\",\n", fault_class_to_str(pfc));
        fprintf(f, "      \"op_seq\": %u\n", vs->peripheral_sequence[p - 1u]);
        fprintf(f, "    }%s\n", p < VIRTUAL_MAX_PERIPHERALS ? "," : "");
    }
    fprintf(f, "  ],\n");

    /* Runtime trace */
    fprintf(f, "  \"runtime_trace\": [\n");
    for (uint16_t i = 0u; i < vs->runtime.trace_count; ++i) {
        const TraceRecord *t = &vs->runtime.trace[i];
        fprintf(f, "    {\n");
        fprintf(f, "      \"seq\": %u,\n", t->trace_seq);
        fprintf(f, "      \"episode_id\": %u,\n", t->fault_episode_id);
        fprintf(f, "      \"slot_id\": %u,\n", t->event_ref.slot_id);
        fprintf(f, "      \"generation\": %u,\n", t->event_ref.generation);
        fprintf(f, "      \"tx_id\": %u,\n", t->transaction_id);
        fprintf(f, "      \"obs_seq\": %u,\n", t->observation_seq);
        fprintf(f, "      \"action_index\": %u,\n", t->action_index);
        fprintf(f, "      \"state\": \"%s\",\n", state_to_str((EventState)t->state));
        fprintf(f, "      \"action\": \"%s\",\n", action_to_str((RecoveryAction)t->action));
        fprintf(f, "      \"outcome\": \"%s\",\n", outcome_to_str((OutcomeCode)t->outcome));
        fprintf(f, "      \"correctness\": %u\n", t->correctness);
        fprintf(f, "    }%s\n", (i + 1u < vs->runtime.trace_count) ? "," : "");
    }
    fprintf(f, "  ],\n");

    /* Wrapper trace */
    fprintf(f, "  \"wrapper_trace\": [\n");
    for (uint16_t i = 0u; i < vs->trace_count; ++i) {
        const VirtualTraceRecord *w = &vs->trace[i];
        fprintf(f, "    {\n");
        fprintf(f, "      \"wrap_seq\": %u,\n", w->wrapper_sequence);
        fprintf(f, "      \"step_seq\": %u,\n", w->step_sequence);
        fprintf(f, "      \"key\": %u,\n", w->scenario_event_key);
        fprintf(f, "      \"slot_id\": %u,\n", w->event_ref.slot_id);
        fprintf(f, "      \"generation\": %u,\n", w->event_ref.generation);
        fprintf(f, "      \"peripheral\": \"%s\",\n", periph_to_str(w->peripheral));
        fprintf(f, "      \"tx_id\": %u,\n", w->transaction_id);
        fprintf(f, "      \"action\": \"%s\",\n", action_to_str(w->action));
        fprintf(f, "      \"outcome\": \"%s\",\n", outcome_to_str(w->outcome));
        fprintf(f, "      \"env_status\": \"%s\",\n", periph_status_to_str(w->environmental_status));
        fprintf(f, "      \"fault_class\": \"%s\",\n", fault_class_to_str(w->fault_class));
        fprintf(f, "      \"rt_first\": %u,\n", w->runtime_trace_first);
        fprintf(f, "      \"rt_last\": %u,\n", w->runtime_trace_last);
        fprintf(f, "      \"runtime_authoritative\": %s\n", w->runtime_authoritative ? "true" : "false");
        fprintf(f, "    }%s\n", (i + 1u < vs->trace_count) ? "," : "");
    }
    fprintf(f, "  ]\n");

    fprintf(f, "}\n");
}

static int export_all_scenarios(const char *filepath) {
    FILE *out = filepath ? fopen(filepath, "w") : stdout;
    if (!out) {
        fprintf(stderr, "Error opening file %s for write\n", filepath ? filepath : "stdout");
        return 1;
    }

    fprintf(out, "{\n  \"timestamp\": \"2026-10-01T20:00:00Z\",\n  \"scenarios\": {\n");

    size_t count = virtual_scenario_count();
    for (size_t s = 0; s < count; ++s) {
        const ScenarioRegistryEntry *entry = virtual_scenario_get(s);
        uint32_t run_id = 1000u + entry->scenario->scenario_id;

        fprintf(out, "    \"%s\": {\n", entry->id);
        fprintf(out, "      \"id\": \"%s\",\n", entry->id);
        fprintf(out, "      \"name\": \"%s\",\n", entry->name);
        fprintf(out, "      \"description\": \"%s\",\n", entry->description);
        fprintf(out, "      \"step_count\": %u,\n", entry->scenario->step_count);

        fprintf(out, "      \"timeline\": [\n");
        for (uint16_t st = 0u; st <= entry->scenario->step_count; ++st) {
            VirtualSystem vs;
            virtual_system_init(&vs, entry->scenario, VAR_P4_INTEGRATED, run_id);
            for (uint16_t j = 0u; j < st; ++j) {
                virtual_system_step(&vs);
            }
            print_json_state(out, &vs, entry->id, entry->name, entry->description);
            if (st < entry->scenario->step_count) fprintf(out, ",\n");
        }
        fprintf(out, "\n      ]\n    }%s\n", (s + 1 < count) ? "," : "");
    }

    fprintf(out, "  }\n}\n");

    if (filepath) fclose(out);
    return 0;
}

static int run_single(const char *id, PolicyVariant var, uint32_t run_id, int target_step, const bool disconnected[VIRTUAL_MAX_PERIPHERALS]) {
    const ScenarioRegistryEntry *entry = virtual_scenario_find(id);
    if (!entry) {
        fprintf(stderr, "Scenario %s not found\n", id);
        return 1;
    }

    if (run_id == 0u) {
        run_id = 1000u + entry->scenario->scenario_id;
    }

    VirtualSystem vs;
    virtual_system_init(&vs, entry->scenario, var, run_id);
    for (uint8_t p = 0u; p < VIRTUAL_MAX_PERIPHERALS; ++p) {
        if (disconnected[p]) (void)virtual_system_set_peripheral_connected(&vs, (PeripheralId)(p + 1u), false);
    }

    if (target_step < 0) {
        virtual_system_run(&vs);
    } else {
        int steps_to_do = target_step;
        if (steps_to_do > (int)entry->scenario->step_count) {
            steps_to_do = (int)entry->scenario->step_count;
        }
        for (int i = 0; i < steps_to_do; ++i) {
            virtual_system_step(&vs);
            if (vs.adapter_error) break;
        }
    }

    print_json_state(stdout, &vs, entry->id, entry->name, entry->description);
    return 0;
}

static int verify_all(void) {
    size_t count = virtual_scenario_count();
    printf("Verifying %u scenarios...\n", (unsigned)count);

    for (size_t s = 0; s < count; ++s) {
        const ScenarioRegistryEntry *entry = virtual_scenario_get(s);
        uint32_t run_id = 1000u + entry->scenario->scenario_id;

        VirtualSystem a, b;
        virtual_system_init(&a, entry->scenario, VAR_P4_INTEGRATED, run_id);
        virtual_system_init(&b, entry->scenario, VAR_P4_INTEGRATED, run_id);

        OutcomeCode oa = virtual_system_run(&a);
        OutcomeCode ob = virtual_system_run(&b);

        if (oa != ob) {
            fprintf(stderr, "FAIL: %s outcome mismatch %u vs %u\n", entry->id, oa, ob);
            return 1;
        }

        uint32_t da = virtual_system_digest(&a);
        uint32_t db = virtual_system_digest(&b);
        if (da != db) {
            fprintf(stderr, "FAIL: %s digest mismatch 0x%08X vs 0x%08X\n", entry->id, da, db);
            return 1;
        }

        for (uint16_t i = 0u; i < a.trace_count; ++i) {
            const VirtualTraceRecord *w = &a.trace[i];
            if (!w->runtime_authoritative) {
                fprintf(stderr, "FAIL: %s wrapper trace %u not runtime authoritative\n", entry->id, i);
                return 1;
            }
            if (w->runtime_trace_first > w->runtime_trace_last && w->runtime_trace_last > 0) {
                fprintf(stderr, "FAIL: %s invalid trace seq range %u..%u\n", entry->id,
                        w->runtime_trace_first, w->runtime_trace_last);
                return 1;
            }
        }

        if (strcmp(entry->id, "S08") == 0) {
            if (a.runtime.episode.target_ref.slot_id != INVALID_SLOT) {
                fprintf(stderr, "FAIL: S08 fabricated EventRef: slot_id=%u\n", a.runtime.episode.target_ref.slot_id);
                return 1;
            }
        }

        printf("  [%s] %s -> Outcome: %s | Digest: 0x%08X (PASS)\n",
               entry->id, entry->name, outcome_to_str(oa), da);
    }

    printf("ALL SCENARIOS VERIFIED SUCCESSFULLY.\n");
    return 0;
}

int main(int argc, char **argv) {
#ifdef _WIN32
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif

    const char *scenario_id = "S01";
    PolicyVariant variant = VAR_P4_INTEGRATED;
    uint32_t run_id = 0u;
    int step = -1;
    bool disconnected[VIRTUAL_MAX_PERIPHERALS] = {false, false, false};

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--scenario") == 0 && i + 1 < argc) {
            scenario_id = argv[++i];
        } else if (strcmp(argv[i], "--variant") == 0 && i + 1 < argc) {
            variant = (PolicyVariant)atoi(argv[++i]);
        } else if (strcmp(argv[i], "--run-id") == 0 && i + 1 < argc) {
            run_id = (uint32_t)atoi(argv[++i]);
        } else if (strcmp(argv[i], "--step") == 0 && i + 1 < argc) {
            step = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--run") == 0) {
            step = -1;
        } else if (strcmp(argv[i], "--disconnect") == 0 && i + 1 < argc) {
            const char *name = argv[++i];
            if (strcmp(name, "I2C0") == 0) disconnected[0] = true;
            else if (strcmp(name, "SPI0") == 0) disconnected[1] = true;
            else if (strcmp(name, "UART0") == 0) disconnected[2] = true;
            else { fprintf(stderr, "Unsupported virtual peripheral: %s\\n", name); return 2; }
        } else if (strcmp(argv[i], "--export-all") == 0) {
            const char *out_file = (i + 1 < argc && argv[i + 1][0] != '-') ? argv[++i] : NULL;
            return export_all_scenarios(out_file);
        } else if (strcmp(argv[i], "--verify") == 0) {
            return verify_all();
        } else if (strcmp(argv[i], "--list") == 0) {
            size_t count = virtual_scenario_count();
            printf("Available Scenarios (%u):\n", (unsigned)count);
            for (size_t s = 0; s < count; ++s) {
                const ScenarioRegistryEntry *e = virtual_scenario_get(s);
                printf("  %s: %s (steps=%u)\n", e->id, e->name, e->scenario->step_count);
            }
            return 0;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: virtual_demo_cli [OPTIONS]\n");
            printf("  --scenario <ID>     Select scenario (S01, S02, S05, S06, S08, S14)\n");
            printf("  --variant <0-4>     Policy variant (0=P0, 1=P1, 2=P2, 3=P3, 4=P4)\n");
            printf("  --step <N>          Execute up to step N (0 to step_count)\n");
            printf("  --run               Execute to completion (default)\n");
            printf("  --run-id <N>        Run identifier\n");
            printf("  --export-all [FILE] Export complete timeline of all scenarios as JSON\n");
            printf("  --verify            Run verification checks\n");
            printf("  --list              List scenarios\n");
            return 0;
        }
    }

    return run_single(scenario_id, variant, run_id, step, disconnected);
}
