#include "virtual_system.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <crtdbg.h>
#include <stdlib.h>
#endif

/* S01 */
static const VirtualEventSpec s01_events[] = {
    {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 101u, true},
    {2u, EVT_PERIPHERAL_READ, 1u, 2u, 2u, PERIPH_I2C0, NORMAL, 102u, true},
    {3u, EVT_PERIPHERAL_READ, 1u, 3u, 3u, PERIPH_UART0, DEFERABLE, 103u, true}
};
static const VirtualFaultSchedule s01_faults[] = {
    {1u, 0u, FAULT_I2C_NACK, ASSOC_EXACT, 2u, 102u, NORMAL, true, true, true, true},
    {1u, 1u, FAULT_I2C_NACK, ASSOC_EXACT, 2u, 102u, NORMAL, true, true, true, false}
};
static const VirtualStep s01_steps[] = {
    {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
    {2u, VSTEP_ADMIT, 1u, 0u, 0u, 0u},
    {3u, VSTEP_ADMIT, 2u, 0u, 0u, 0u},
    {4u, VSTEP_START_FAULT, 1u, 0u, 0u, 0u},
    {5u, VSTEP_DRAIN, 0u, 0u, 0u, 0u},
    {6u, VSTEP_APPLY_FAULT, 1u, 0u, 0u, 0u},
    {7u, VSTEP_DRAIN, 0u, 0u, 0u, 0u}
};
static const VirtualScenario scenario_S01 = {1u, s01_events, 3u, NULL, 0u,
                                             s01_faults, 2u, s01_steps, 7u};

/* S02 */
static const VirtualEventSpec s02_events[] = {
    {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 201u, true},
    {2u, EVT_PERIPHERAL_READ, 1u, 2u, 2u, PERIPH_I2C0, NORMAL, 202u, true},
    {3u, EVT_PERIPHERAL_READ, 1u, 3u, 3u, PERIPH_UART0, NORMAL, 203u, true}
};
static const VirtualDependencySpec s02_deps[] = {
    {2u, 1u, DEP_ORDERED, ST_COMPLETED}
};
static const VirtualFaultSchedule s02_faults[] = {
    {2u, 0u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 201u, NORMAL, true, true, true, true},
    {2u, 1u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 201u, NORMAL, true, true, true, false}
};
static const VirtualStep s02_steps[] = {
    {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
    {2u, VSTEP_ADMIT, 1u, 0u, 0u, 0u},
    {3u, VSTEP_ADMIT, 2u, 0u, 0u, 0u},
    {4u, VSTEP_DEPEND, 1u, 0u, DEP_ORDERED, ST_COMPLETED},
    {5u, VSTEP_START_FAULT, 2u, 0u, 0u, 0u},
    {6u, VSTEP_DRAIN, 0u, 0u, 0u, 0u},
    {7u, VSTEP_APPLY_FAULT, 2u, 0u, 0u, 0u},
    {8u, VSTEP_DRAIN, 0u, 0u, 0u, 0u}
};
static const VirtualScenario scenario_S02 = {2u, s02_events, 3u, s02_deps, 1u,
                                             s02_faults, 2u, s02_steps, 8u};

/* S05 */
static const VirtualEventSpec s05_events[] = {
    {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 501u, true}
};
static const VirtualFaultSchedule s05_faults[] = {
    {5u, 0u, FAULT_I2C_NACK, ASSOC_EXACT, 1u, 501u, NORMAL, true, true, true, true},
    {5u, 1u, FAULT_I2C_NACK, ASSOC_EXACT, 1u, 501u, NORMAL, true, true, true, false}
};
static const VirtualStep s05_steps[] = {
    {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
    {2u, VSTEP_START_FAULT, 5u, 0u, 0u, 0u},
    {3u, VSTEP_APPLY_FAULT, 5u, 0u, 0u, 0u}
};
static const VirtualScenario scenario_S05 = {5u, s05_events, 1u, NULL, 0u,
                                             s05_faults, 2u, s05_steps, 3u};

/* S06 */
static const VirtualEventSpec s06_events[] = {
    {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 601u, true}
};
static const VirtualFaultSchedule s06_faults[] = {
    {6u, 0u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 601u, NORMAL, true, true, true, true},
    {6u, 1u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 601u, NORMAL, true, true, true, true},
    {6u, 2u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 601u, NORMAL, true, true, true, true},
    {6u, 3u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 601u, NORMAL, true, true, true, false}
};
static const VirtualStep s06_steps[] = {
    {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
    {2u, VSTEP_START_FAULT, 6u, 0u, 0u, 0u},
    {3u, VSTEP_APPLY_FAULT, 6u, 0u, 0u, 0u},
    {4u, VSTEP_APPLY_FAULT, 6u, 0u, 0u, 0u},
    {5u, VSTEP_APPLY_FAULT, 6u, 0u, 0u, 0u}
};
static const VirtualScenario scenario_S06 = {6u, s06_events, 1u, NULL, 0u,
                                             s06_faults, 4u, s06_steps, 5u};

/* S08 */
static const VirtualEventSpec s08_events[] = {
    {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, CRITICAL, 801u, false}
};
static const VirtualFaultSchedule s08_faults[] = {
    {8u, 0u, FAULT_AMBIGUOUS, ASSOC_UNKNOWN, VIRTUAL_MAX_EVENT_KEY, INVALID_TX,
     CRITICAL, false, false, false, true},
    {8u, 1u, FAULT_AMBIGUOUS, ASSOC_UNKNOWN, VIRTUAL_MAX_EVENT_KEY, INVALID_TX,
     CRITICAL, false, false, false, true}
};
static const VirtualStep s08_steps[] = {
    {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
    {2u, VSTEP_START_FAULT, 8u, 0u, 0u, 0u},
    {3u, VSTEP_APPLY_FAULT, 8u, 0u, 0u, 0u}
};
static const VirtualScenario scenario_S08 = {8u, s08_events, 1u, NULL, 0u,
                                             s08_faults, 2u, s08_steps, 3u};

/* S14 */
static const VirtualEventSpec s14_events[] = {
    {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 1401u, true},
    {2u, EVT_PERIPHERAL_READ, 1u, 2u, 2u, PERIPH_I2C0, NORMAL, 1402u, true},
    {3u, EVT_PERIPHERAL_READ, 1u, 3u, 3u, PERIPH_UART0, DEFERABLE, 1403u, true}
};
static const VirtualDependencySpec s14_deps[] = {
    {2u, 1u, DEP_ORDERED, ST_COMPLETED},
    {3u, 2u, DEP_COUPLED, ST_COMPLETED}
};
static const VirtualFaultSchedule s14_faults[] = {
    {14u, 0u, FAULT_I2C_NACK, ASSOC_EXACT, 1u, 1401u, NORMAL, true, true, true, true},
    {14u, 1u, FAULT_I2C_NACK, ASSOC_EXACT, 1u, 1401u, NORMAL, true, true, true, false}
};
static const VirtualStep s14_steps[] = {
    {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
    {2u, VSTEP_ADMIT, 1u, 0u, 0u, 0u},
    {3u, VSTEP_ADMIT, 2u, 0u, 0u, 0u},
    {4u, VSTEP_DEPEND, 1u, 0u, DEP_ORDERED, ST_COMPLETED},
    {5u, VSTEP_DEPEND, 2u, 1u, DEP_COUPLED, ST_COMPLETED},
    {6u, VSTEP_START_FAULT, 14u, 0u, 0u, 0u},
    {7u, VSTEP_DRAIN, 0u, 0u, 0u, 0u},
    {8u, VSTEP_APPLY_FAULT, 14u, 0u, 0u, 0u},
    {9u, VSTEP_DRAIN, 0u, 0u, 0u, 0u}
};
static const VirtualScenario scenario_S14 = {14u, s14_events, 3u, s14_deps, 2u,
                                             s14_faults, 2u, s14_steps, 9u};

static void test_S01_independent_preservation(void) {
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario_S01, VAR_P4_INTEGRATED, 1001u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(virtual_system_complete(&vs));
    assert(vs.runtime.episode_in_use == false);
    assert(vs.runtime.slots[1u].state == ST_COMPLETED);
    assert(vs.runtime.slots[0u].state == ST_COMPLETED);
    assert(vs.runtime.slots[2u].state == ST_COMPLETED);
    assert(vs.peripheral_trace_count >= 4u);
}

static void test_S02_ordered_blocking(void) {
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario_S02, VAR_P4_INTEGRATED, 1002u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(vs.runtime.slots[0u].state == ST_COMPLETED);
    assert(vs.runtime.slots[1u].state == ST_QUEUED);
    assert(vs.runtime.slots[2u].state == ST_COMPLETED);
}

static void test_S05_retry_success_and_correlation(void) {
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario_S05, VAR_P4_INTEGRATED, 1005u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(vs.trace_count > 0u);
    const VirtualTraceRecord *last = virtual_system_trace_at(
        &vs, (uint16_t)(vs.trace_count - 1u));
    assert(last != NULL && last->runtime_authoritative);
    assert(vs.runtime.episode_in_use == false);
}

static void test_S06_bounded_progression(void) {
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario_S06, VAR_P4_INTEGRATED, 1006u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(vs.runtime.episode.attempt_count == 3u);
    assert(vs.runtime.episode_in_use == false);
}

static void test_S08_ambiguous_no_fabricated_ref(void) {
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario_S08, VAR_P4_INTEGRATED, 1008u);
    assert(virtual_system_run(&vs) == OUTCOME_TERMINAL_ESCALATE);
    assert(vs.runtime.episode.target_ref.slot_id == INVALID_SLOT);
    assert(vs.runtime.slots[0u].fault_associated == false);
}

static void test_S14_replay_digest(void) {
    VirtualSystem a, b;
    virtual_system_init(&a, &scenario_S14, VAR_P4_INTEGRATED, 1014u);
    virtual_system_init(&b, &scenario_S14, VAR_P4_INTEGRATED, 1014u);
    assert(virtual_system_run(&a) == OUTCOME_SUCCESS);
    assert(virtual_system_run(&b) == OUTCOME_SUCCESS);
    assert(virtual_system_digest(&a) == virtual_system_digest(&b));
    assert(a.runtime.trace_count == b.runtime.trace_count);
}

static void dump_scenario(const char *id, const VirtualScenario *sc, uint32_t run_id) {
    VirtualSystem v1, v2;
    virtual_system_init(&v1, sc, VAR_P4_INTEGRATED, run_id);
    virtual_system_init(&v2, sc, VAR_P4_INTEGRATED, run_id);
    OutcomeCode o1 = virtual_system_run(&v1);
    OutcomeCode o2 = virtual_system_run(&v2);
    uint32_t d1 = virtual_system_digest(&v1);
    uint32_t d2 = virtual_system_digest(&v2);

    printf("=== SCENARIO %s (run_id=%u) ===\n", id, run_id);
    printf("Outcome: %u | Complete: %d | Run1 Digest: 0x%08X | Run2 Digest: 0x%08X | Equal: %s\n",
           (unsigned)o1, virtual_system_complete(&v1) ? 1 : 0, d1, d2, (d1 == d2 && o1 == o2) ? "YES" : "NO");
    printf("Runtime Trace Records (%u):\n", (unsigned)v1.runtime.trace_count);
    for (uint16_t i = 0u; i < v1.runtime.trace_count; ++i) {
        const TraceRecord *t = &v1.runtime.trace[i];
        printf("  [RT#%02u] seq=%u ep=%u slot=%u gen=%u tx=%u obs=%u act_idx=%u st=%u act=%u out=%u corr=%u\n",
               i, t->trace_seq, t->fault_episode_id, t->event_ref.slot_id, t->event_ref.generation,
               t->transaction_id, t->observation_seq, t->action_index, t->state, t->action, t->outcome, t->correctness);
    }
    printf("Wrapper Trace Records (%u):\n", (unsigned)v1.trace_count);
    for (uint16_t i = 0u; i < v1.trace_count; ++i) {
        const VirtualTraceRecord *w = &v1.trace[i];
        printf("  [WRAP#%02u] wrap_seq=%u step_seq=%u key=%u slot=%u gen=%u periph=%u tx=%u act=%u out=%u env_st=%u fault=%u rt_first=%u rt_last=%u auth=%d\n",
               i, w->wrapper_sequence, w->step_sequence, w->scenario_event_key, w->event_ref.slot_id, w->event_ref.generation,
               (unsigned)w->peripheral, w->transaction_id, (unsigned)w->action, (unsigned)w->outcome,
               (unsigned)w->environmental_status, (unsigned)w->fault_class, w->runtime_trace_first, w->runtime_trace_last,
               w->runtime_authoritative ? 1 : 0);
    }
    printf("Peripheral Trace Records (%u):\n", (unsigned)v1.peripheral_trace_count);
    for (uint16_t i = 0u; i < v1.peripheral_trace_count; ++i) {
        const VirtualPeripheralRecord *p = &v1.peripheral_trace[i];
        printf("  [PERIPH#%02u] periph=%u op_seq=%u status=%u fault=%u tx=%u slot=%u gen=%u\n",
               i, (unsigned)p->peripheral, p->operation_sequence, (unsigned)p->status,
               (unsigned)p->fault_class, p->transaction_id, p->event_ref.slot_id, p->event_ref.generation);
    }
    printf("\n");
}

int main(int argc, char **argv) {
#ifdef _WIN32
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif
    test_S01_independent_preservation();
    test_S02_ordered_blocking();
    test_S05_retry_success_and_correlation();
    test_S06_bounded_progression();
    test_S08_ambiguous_no_fabricated_ref();
    test_S14_replay_digest();

    if (argc > 1 && strcmp(argv[1], "--dump") == 0) {
        dump_scenario("S01", &scenario_S01, 1001u);
        dump_scenario("S02", &scenario_S02, 1002u);
        dump_scenario("S05", &scenario_S05, 1005u);
        dump_scenario("S06", &scenario_S06, 1006u);
        dump_scenario("S08", &scenario_S08, 1008u);
        dump_scenario("S14", &scenario_S14, 1014u);
    }

    puts("PASS: K.6 virtual-system deterministic scenarios, authority/correlation, and replay");
    return 0;
}
