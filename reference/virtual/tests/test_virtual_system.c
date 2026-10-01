#include "virtual_system.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <crtdbg.h>
#include <stdlib.h>
#endif

#include "virtual_scenarios.h"


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
