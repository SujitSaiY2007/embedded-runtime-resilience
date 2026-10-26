#include "ref_runtime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static EventRef admit_event(Runtime *rt) {
    EventSlot spec;
    memset(&spec, 0, sizeof(spec));
    spec.type = EVT_PERIPHERAL_READ;
    spec.peripheral = PERIPH_I2C0;
    spec.criticality = NORMAL;
    spec.shared_state_valid = true;
    EventRef ref = event_ref_invalid();
    assert(runtime_admit(rt, &spec, &ref) == OUTCOME_SUCCESS);
    return ref;
}

static void test_release_when_queue_full_is_recoverable(void) {
    Runtime rt;
    runtime_init(&rt, VAR_P4_INTEGRATED);
    EventRef refs[QMAX];
    for (size_t i = 0; i < QMAX; ++i) refs[i] = admit_event(&rt);

    assert(runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, refs[0],
                               rt.slots[refs[0].slot_id].transaction_id,
                               NORMAL, true, true, false) == OUTCOME_SUCCESS);
    /* Fill the freed queue slot while the original event remains quarantined. */
    (void)admit_event(&rt);
    assert(rt.queue_count == QMAX);
    assert(runtime_apply_policy(&rt, NULL) == OUTCOME_QUEUE_FULL);
    assert(rt.episode_in_use);
    assert(rt.slots[refs[0].slot_id].state == ST_QUARANTINED);
    assert(rt.slots[refs[0].slot_id].fault_associated);
    assert(rt.quarantine_count == 1u);

    EventRef selected = event_ref_invalid();
    assert(scheduler_select(&rt, &selected));
    assert(runtime_execute_selected(&rt, selected, NULL, NULL) == OUTCOME_SUCCESS);
    assert(rt.queue_count == QMAX - 1u);
    assert(runtime_verify_and_release(&rt, true) == OUTCOME_SUCCESS);
    assert(!rt.episode_in_use);
    assert(rt.queue_count == QMAX);
    assert(rt.quarantine_count == 0u);
}

static void test_generation_survives_more_than_255_reuses(void) {
    Runtime rt;
    runtime_init(&rt, VAR_P4_INTEGRATED);
    EventRef ref = event_ref_invalid();
    for (unsigned i = 0; i < 300u; ++i) {
        ref = admit_event(&rt);
        rt.slots[ref.slot_id].state = ST_COMPLETED;
        rt.queue_count = 0u;
    }
    assert(ref.slot_id == 0u);
    assert(ref.generation == 300u);
}

static void test_trace_overflow_is_observable_and_bounded(void) {
    Runtime rt;
    runtime_init(&rt, VAR_P4_INTEGRATED);
    for (unsigned i = 0; i < 300u; ++i) {
        EventRef ref = admit_event(&rt);
        rt.slots[ref.slot_id].state = ST_COMPLETED;
        rt.queue_count = 0u;
    }
    assert(rt.trace_count == TRACE_EVENT_CAP);
    assert(rt.trace_dropped_count == 44u);
}


static void test_p5_reset_only_and_p6_backoff_baselines(void) {
    Runtime rt;
    FaultContext ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.active = true;
    ctx.episode_state = EP_ACTIVE;
    ctx.association = ASSOC_EXACT;
    ctx.retry_safe = true;
    ctx.reinit_safe = true;
    ctx.dependencies_safe = true;
    ctx.shared_state_valid = true;

    runtime_init(&rt, VAR_P5_RESET_ONLY);
    PolicyDecision p5 = policy_decide(&rt, &ctx);
    assert(p5.action == ACT_REINIT_OR_RESET);
    assert(!p5.retry_authorized);
    assert(p5.target_scope == ASSOC_EXACT);

    runtime_init(&rt, VAR_P6_EXP_BACKOFF_RETRY);
    PolicyDecision p6 = policy_decide(&rt, &ctx);
    assert(p6.action == ACT_RETRY);
    assert(p6.retry_authorized);
    assert(policy_backoff_delay(0u) == 1u);
    assert(policy_backoff_delay(1u) == 2u);
    assert(policy_backoff_delay(2u) == 4u);
    assert(policy_backoff_delay(3u) == 8u);
    ctx.attempt_count = 3u;
    p6 = policy_decide(&rt, &ctx);
    assert(p6.action == ACT_ESCALATE);
    assert(p6.terminal);
}


static void test_p6_records_backoff_schedule(void) {
    Runtime rt;
    runtime_init(&rt, VAR_P6_EXP_BACKOFF_RETRY);
    EventRef ref = admit_event(&rt);
    assert(runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, ref,
                               INVALID_TX, NORMAL, true, true, false) == OUTCOME_SUCCESS);
    assert(runtime_apply_policy(&rt, NULL) == OUTCOME_SUCCESS);
    bool saw_retry = false;
    for (uint16_t i = 0; i < rt.trace_count; ++i) {
        if (rt.trace[i].action == ACT_RETRY) {
            saw_retry = true;
            assert(rt.trace[i].backoff_delay_units == 1u);
        }
    }
    assert(saw_retry);
}

static void test_invalid_target_does_not_leak_episode(void) {
    Runtime rt;
    runtime_init(&rt, VAR_P0_FIXED_RETRY);
    EventRef invalid = event_ref_invalid();

    assert(runtime_start_fault(&rt, FAULT_AMBIGUOUS, ASSOC_UNKNOWN, invalid,
                               INVALID_TX, NORMAL, true, true, false) == OUTCOME_SUCCESS);
    assert(rt.episode_in_use);
    assert(runtime_apply_policy(&rt, NULL) == OUTCOME_STALE_REF);
    assert(!rt.episode_in_use);
    assert(!rt.episode.active);
    assert(rt.episode.episode_state == EP_TERMINAL);
    assert(rt.active_fault_episode_id == 0u);
}


static void assert_failed_recovery_budget_closes_episode(
    PolicyVariant variant, FaultClass fault_class, Criticality criticality,
    bool degrade_safe) {
    Runtime rt;
    runtime_init(&rt, variant);
    EventRef ref = admit_event(&rt);

    assert(runtime_start_fault(&rt, fault_class, ASSOC_EXACT, ref,
                               INVALID_TX, criticality, true, true,
                               degrade_safe) == OUTCOME_SUCCESS);

    OutcomeCode out = OUTCOME_NONE;
    for (uint8_t action = 1u; action <= MAX_RECOVERY_ACTIONS; ++action) {
        FaultInjection fi;
        memset(&fi, 0, sizeof(fi));
        fi.enabled = true;
        fi.fault_class = fault_class;
        fi.target_ref = ref;
        fi.trigger_action_index = action;
        out = runtime_apply_policy(&rt, &fi);
        if (action < MAX_RECOVERY_ACTIONS) {
            assert(out == OUTCOME_FAILURE);
            assert(rt.episode_in_use);
        }
    }

    assert(rt.episode.attempt_count == MAX_RECOVERY_ACTIONS);
    assert(!rt.episode_in_use);
    assert(!rt.episode.active);
    assert(rt.episode.episode_state == EP_TERMINAL);
    assert(rt.active_fault_episode_id == 0u);
    assert(out == (degrade_safe ? OUTCOME_TERMINAL_DEGRADE
                                : OUTCOME_TERMINAL_ESCALATE));
}

static void test_failed_recovery_budget_closes_cf05_cf06_episodes(void) {
    const PolicyVariant variants[] = {
        VAR_P2_CONTEXT_ONLY,
        VAR_P3_CONTEXT_HISTORY,
        VAR_P5_RESET_ONLY
    };
    for (size_t i = 0u; i < sizeof(variants) / sizeof(variants[0]); ++i) {
        /* CF05: critical timeout; degradation is not authorized. */
        assert_failed_recovery_budget_closes_episode(
            variants[i], FAULT_I2C_TIMEOUT, CRITICAL, false);
        /* CF06: deferable persistent fault; degradation is authorized. */
        assert_failed_recovery_budget_closes_episode(
            variants[i], FAULT_I2C_PERSISTENT, DEFERABLE, true);
    }
}

int main(void) {
    test_release_when_queue_full_is_recoverable();
    test_generation_survives_more_than_255_reuses();
    test_trace_overflow_is_observable_and_bounded();
    test_p5_reset_only_and_p6_backoff_baselines();
    test_p6_records_backoff_schedule();
    test_invalid_target_does_not_leak_episode();
    test_failed_recovery_budget_closes_cf05_cf06_episodes();
    puts("reference_v2 edge-case tests: PASS");
    return 0;
}
