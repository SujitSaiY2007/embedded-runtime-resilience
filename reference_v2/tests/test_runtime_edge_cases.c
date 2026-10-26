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
    rt.slots[refs[0].slot_id].verification_ok = true;
    rt.slots[refs[0].slot_id].shared_state_valid = true;

    assert(runtime_verify_and_release(&rt, true) == OUTCOME_QUEUE_FULL);
    assert(rt.episode_in_use);
    assert(rt.slots[refs[0].slot_id].state == ST_QUARANTINED);
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

int main(void) {
    test_release_when_queue_full_is_recoverable();
    test_invalid_target_does_not_leak_episode();
    puts("reference_v2 edge-case tests: PASS");
    return 0;
}
