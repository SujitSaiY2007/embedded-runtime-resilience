#include "virtual_system.h"
#include <assert.h>
#include <stdio.h>

static void test_S01_independent_preservation(void) {
    static const VirtualEventSpec events[] = {
        {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 101u, true},
        {2u, EVT_PERIPHERAL_READ, 1u, 2u, 2u, PERIPH_I2C0, NORMAL, 102u, true},
        {3u, EVT_PERIPHERAL_READ, 1u, 3u, 3u, PERIPH_UART0, DEFERABLE, 103u, true}
    };
    static const VirtualFaultSchedule faults[] = {
        {1u, 1u, FAULT_I2C_NACK, ASSOC_EXACT, 2u, 102u, NORMAL, true, true, true, true},
        {1u, 2u, FAULT_I2C_NACK, ASSOC_EXACT, 2u, 102u, NORMAL, true, true, true, false}
    };
    static const VirtualStep steps[] = {
        {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
        {2u, VSTEP_ADMIT, 1u, 0u, 0u, 0u},
        {3u, VSTEP_ADMIT, 2u, 0u, 0u, 0u},
        {4u, VSTEP_START_FAULT, 1u, 0u, 0u, 0u},
        {5u, VSTEP_DRAIN, 0u, 0u, 0u, 0u},
        {6u, VSTEP_APPLY_FAULT, 1u, 0u, 0u, 0u}
    };
    static const VirtualScenario scenario = {1u, events, 3u, NULL, 0u,
                                             faults, 2u, steps, 6u};
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario, VAR_P4_INTEGRATED, 1001u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(virtual_system_complete(&vs));
    assert(vs.runtime.episode_in_use == false);
    assert(vs.runtime.slots[1u].state == ST_COMPLETED);
    assert(vs.runtime.slots[0u].state == ST_COMPLETED);
    assert(vs.runtime.slots[2u].state == ST_COMPLETED);
    assert(vs.peripheral_trace_count >= 4u);
}

static void test_S02_ordered_blocking(void) {
    static const VirtualEventSpec events[] = {
        {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 201u, true},
        {2u, EVT_PERIPHERAL_READ, 1u, 2u, 2u, PERIPH_I2C0, NORMAL, 202u, true},
        {3u, EVT_PERIPHERAL_READ, 1u, 3u, 3u, PERIPH_UART0, NORMAL, 203u, true}
    };
    static const VirtualDependencySpec deps[] = {
        {2u, 1u, DEP_ORDERED, ST_COMPLETED}
    };
    static const VirtualFaultSchedule faults[] = {
        {2u, 1u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 201u, NORMAL, true, true, true, true},
        {2u, 2u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 201u, NORMAL, true, true, true, false}
    };
    static const VirtualStep steps[] = {
        {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
        {2u, VSTEP_ADMIT, 1u, 0u, 0u, 0u},
        {3u, VSTEP_ADMIT, 2u, 0u, 0u, 0u},
        {4u, VSTEP_DEPEND, 1u, 0u, DEP_ORDERED, ST_COMPLETED},
        {5u, VSTEP_START_FAULT, 2u, 0u, 0u, 0u},
        {6u, VSTEP_DRAIN, 0u, 0u, 0u, 0u},
        {7u, VSTEP_APPLY_FAULT, 2u, 0u, 0u, 0u},
        {8u, VSTEP_DRAIN, 0u, 0u, 0u, 0u}
    };
    static const VirtualScenario scenario = {2u, events, 3u, deps, 1u,
                                             faults, 2u, steps, 8u};
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario, VAR_P4_INTEGRATED, 1002u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(vs.runtime.slots[0u].state == ST_COMPLETED);
    assert(vs.runtime.slots[1u].state == ST_COMPLETED);
    assert(vs.runtime.slots[2u].state == ST_COMPLETED);
}

static void test_S05_retry_success_and_correlation(void) {
    static const VirtualEventSpec events[] = {
        {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 501u, true}
    };
    static const VirtualFaultSchedule faults[] = {
        {5u, 1u, FAULT_I2C_NACK, ASSOC_EXACT, 1u, 501u, NORMAL, true, true, true, false}
    };
    static const VirtualStep steps[] = {
        {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
        {2u, VSTEP_START_FAULT, 5u, 0u, 0u, 0u},
        {3u, VSTEP_APPLY_FAULT, 5u, 0u, 0u, 0u}
    };
    static const VirtualScenario scenario = {5u, events, 1u, NULL, 0u,
                                             faults, 1u, steps, 3u};
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario, VAR_P4_INTEGRATED, 1005u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(vs.trace_count > 0u);
    const VirtualTraceRecord *last = virtual_system_trace_at(
        &vs, (uint16_t)(vs.trace_count - 1u));
    assert(last != NULL && last->runtime_authoritative);
    assert(vs.runtime.episode_in_use == false);
}

static void test_S06_bounded_progression(void) {
    static const VirtualEventSpec events[] = {
        {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 601u, true}
    };
    static const VirtualFaultSchedule faults[] = {
        {6u, 1u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 601u, NORMAL, true, true, true, true},
        {6u, 2u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 601u, NORMAL, true, true, true, true},
        {6u, 3u, FAULT_I2C_TIMEOUT, ASSOC_EXACT, 1u, 601u, NORMAL, true, true, true, false}
    };
    static const VirtualStep steps[] = {
        {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
        {2u, VSTEP_START_FAULT, 6u, 0u, 0u, 0u},
        {3u, VSTEP_APPLY_FAULT, 6u, 0u, 0u, 0u},
        {4u, VSTEP_APPLY_FAULT, 6u, 0u, 0u, 0u},
        {5u, VSTEP_APPLY_FAULT, 6u, 0u, 0u, 0u}
    };
    static const VirtualScenario scenario = {6u, events, 1u, NULL, 0u,
                                             faults, 3u, steps, 5u};
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario, VAR_P4_INTEGRATED, 1006u);
    assert(virtual_system_run(&vs) == OUTCOME_SUCCESS);
    assert(vs.runtime.episode.attempt_count == 3u);
    assert(vs.runtime.episode_in_use == false);
}

static void test_S08_ambiguous_no_fabricated_ref(void) {
    static const VirtualEventSpec events[] = {
        {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, CRITICAL, 801u, false}
    };
    static const VirtualFaultSchedule faults[] = {
        {8u, 1u, FAULT_AMBIGUOUS, ASSOC_UNKNOWN, VIRTUAL_MAX_EVENT_KEY, INVALID_TX,
         CRITICAL, false, false, false, true}
    };
    static const VirtualStep steps[] = {
        {1u, VSTEP_ADMIT, 0u, 0u, 0u, 0u},
        {2u, VSTEP_START_FAULT, 8u, 0u, 0u, 0u},
        {3u, VSTEP_APPLY_FAULT, 8u, 0u, 0u, 0u}
    };
    static const VirtualScenario scenario = {8u, events, 1u, NULL, 0u,
                                             faults, 1u, steps, 3u};
    VirtualSystem vs;
    virtual_system_init(&vs, &scenario, VAR_P4_INTEGRATED, 1008u);
    assert(virtual_system_run(&vs) == OUTCOME_TERMINAL_ESCALATE);
    assert(vs.runtime.episode.target_ref.slot_id == INVALID_SLOT);
    assert(vs.runtime.slots[0u].fault_associated == false);
}

static void test_S14_replay_digest(void) {
    static const VirtualEventSpec events[] = {
        {1u, EVT_PERIPHERAL_READ, 1u, 1u, 1u, PERIPH_I2C0, NORMAL, 1401u, true},
        {2u, EVT_PERIPHERAL_READ, 1u, 2u, 2u, PERIPH_I2C0, NORMAL, 1402u, true},
        {3u, EVT_PERIPHERAL_READ, 1u, 3u, 3u, PERIPH_UART0, DEFERABLE, 1403u, true}
    };
    static const VirtualDependencySpec deps[] = {
        {2u, 1u, DEP_ORDERED, ST_COMPLETED},
        {3u, 2u, DEP_COUPLED, ST_COMPLETED}
    };
    static const VirtualFaultSchedule faults[] = {
        {14u, 1u, FAULT_I2C_NACK, ASSOC_EXACT, 1u, 1401u, NORMAL, true, true, true, true},
        {14u, 2u, FAULT_I2C_NACK, ASSOC_EXACT, 1u, 1401u, NORMAL, true, true, true, false}
    };
    static const VirtualStep steps[] = {
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
    static const VirtualScenario scenario = {14u, events, 3u, deps, 2u,
                                             faults, 2u, steps, 9u};
    VirtualSystem a, b;
    virtual_system_init(&a, &scenario, VAR_P4_INTEGRATED, 1014u);
    virtual_system_init(&b, &scenario, VAR_P4_INTEGRATED, 1014u);
    assert(virtual_system_run(&a) == OUTCOME_SUCCESS);
    assert(virtual_system_run(&b) == OUTCOME_SUCCESS);
    assert(virtual_system_digest(&a) == virtual_system_digest(&b));
    assert(a.runtime.trace_count == b.runtime.trace_count);
}

int main(void) {
    test_S01_independent_preservation();
    test_S02_ordered_blocking();
    test_S05_retry_success_and_correlation();
    test_S06_bounded_progression();
    test_S08_ambiguous_no_fabricated_ref();
    test_S14_replay_digest();
    puts("PASS: K.6 virtual-system deterministic scenarios, authority/correlation, and replay");
    return 0;
}
