#include "virtual_system.h"
#include "virtual_scenarios.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <crtdbg.h>
#include <stdlib.h>
#endif

static void test_S06_baseline_P0_escalates_P1_P4_recover(void) {
    VirtualSystem p0, p1, p4;

    /* P0: Fixed retry cannot reset peripheral. Fails closed after 2 retries. */
    virtual_system_init(&p0, &scenario_S06, VAR_P0_FIXED_RETRY, 1006u);
    OutcomeCode out_p0 = virtual_system_run(&p0);
    assert(out_p0 == OUTCOME_TERMINAL_ESCALATE);
    assert(p0.runtime.episode.attempt_count == 2u);
    assert(p0.runtime.slots[0u].state == ST_ESCALATED);

    /* P1: Fixed retry + reset progresses to ACT_REINIT_OR_RESET on attempt 3 and recovers. */
    virtual_system_init(&p1, &scenario_S06, VAR_P1_FIXED_RETRY_RECOVERY, 1006u);
    OutcomeCode out_p1 = virtual_system_run(&p1);
    assert(out_p1 == OUTCOME_SUCCESS);
    assert(p1.runtime.episode.attempt_count == 3u);
    assert(p1.runtime.episode_in_use == false);

    /* P4: Context-aware integrated recovery also progresses to reinit and recovers. */
    virtual_system_init(&p4, &scenario_S06, VAR_P4_INTEGRATED, 1006u);
    OutcomeCode out_p4 = virtual_system_run(&p4);
    assert(out_p4 == OUTCOME_SUCCESS);
    assert(p4.runtime.episode.attempt_count == 3u);
    assert(p4.runtime.episode_in_use == false);
}

static void test_S08_baseline_P0_stale_ref_P4_escalates_cleanly(void) {
    VirtualSystem p0, p4;

    /* P0: Attempts blind retry on target with INVALID_SLOT, fails closed with OUTCOME_STALE_REF */
    virtual_system_init(&p0, &scenario_S08, VAR_P0_FIXED_RETRY, 1008u);
    OutcomeCode out_p0 = virtual_system_run(&p0);
    assert(out_p0 == OUTCOME_STALE_REF);
    assert(p0.runtime.episode.target_ref.slot_id == INVALID_SLOT);
    assert(p0.runtime.episode_in_use == true); /* Unclosed episode in baseline */

    /* P4: Context-aware check detects non-exact association, cleanly escalates and closes episode */
    virtual_system_init(&p4, &scenario_S08, VAR_P4_INTEGRATED, 1008u);
    OutcomeCode out_p4 = virtual_system_run(&p4);
    assert(out_p4 == OUTCOME_TERMINAL_ESCALATE);
    assert(p4.runtime.episode.target_ref.slot_id == INVALID_SLOT);
    assert(p4.runtime.episode_in_use == false); /* Cleanly closed episode */
    assert(p4.runtime.slots[0u].fault_associated == false);
}

static void test_S05_all_variants_recover_transient(void) {
    for (int v = 0; v <= 4; ++v) {
        VirtualSystem vs;
        virtual_system_init(&vs, &scenario_S05, (PolicyVariant)v, 1005u);
        OutcomeCode out = virtual_system_run(&vs);
        assert(out == OUTCOME_SUCCESS);
        assert(vs.runtime.episode_in_use == false);
        assert(vs.runtime.episode.attempt_count == 1u);
    }
}

static void test_S01_independent_preservation_across_variants(void) {
    for (int v = 0; v <= 4; ++v) {
        VirtualSystem vs;
        virtual_system_init(&vs, &scenario_S01, (PolicyVariant)v, 1001u);
        OutcomeCode out = virtual_system_run(&vs);
        assert(out == OUTCOME_SUCCESS);
        assert(virtual_system_complete(&vs));
        assert(vs.runtime.slots[0u].state == ST_COMPLETED);
        assert(vs.runtime.slots[1u].state == ST_COMPLETED);
        assert(vs.runtime.slots[2u].state == ST_COMPLETED);
    }
}

static void test_S02_dependency_blocking_across_variants(void) {
    for (int v = 0; v <= 4; ++v) {
        VirtualSystem vs;
        virtual_system_init(&vs, &scenario_S02, (PolicyVariant)v, 1002u);
        OutcomeCode out = virtual_system_run(&vs);
        assert(out == OUTCOME_SUCCESS);
        assert(vs.runtime.slots[0u].state == ST_COMPLETED);
        assert(vs.runtime.slots[1u].state == ST_QUEUED); /* Blocked on e1 */
        assert(vs.runtime.slots[2u].state == ST_COMPLETED);
    }
}

static void test_baseline_determinism_across_variants(void) {
    const VirtualScenario *scenarios[] = {
        &scenario_S01, &scenario_S02, &scenario_S05,
        &scenario_S06, &scenario_S08, &scenario_S14
    };
    uint32_t run_ids[] = { 1001u, 1002u, 1005u, 1006u, 1008u, 1014u };

    for (size_t s = 0; s < sizeof(scenarios)/sizeof(scenarios[0]); ++s) {
        for (int v = 0; v <= 4; ++v) {
            VirtualSystem r1, r2;
            virtual_system_init(&r1, scenarios[s], (PolicyVariant)v, run_ids[s]);
            virtual_system_init(&r2, scenarios[s], (PolicyVariant)v, run_ids[s]);
            OutcomeCode o1 = virtual_system_run(&r1);
            OutcomeCode o2 = virtual_system_run(&r2);
            assert(o1 == o2);
            assert(virtual_system_digest(&r1) == virtual_system_digest(&r2));
        }
    }
}

int main(void) {
#ifdef _WIN32
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif

    test_S06_baseline_P0_escalates_P1_P4_recover();
    test_S08_baseline_P0_stale_ref_P4_escalates_cleanly();
    test_S05_all_variants_recover_transient();
    test_S01_independent_preservation_across_variants();
    test_S02_dependency_blocking_across_variants();
    test_baseline_determinism_across_variants();

    puts("PASS: K.8 matched baseline validation tests (P0-P4 comparative execution & determinism)");
    return 0;
}
