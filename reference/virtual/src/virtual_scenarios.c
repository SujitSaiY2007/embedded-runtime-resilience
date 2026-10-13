#include "virtual_scenarios.h"
#include <string.h>

/* ============================================================================
 * S01: Independent Preservation Under Transient Fault
 * ============================================================================ */
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
const VirtualScenario scenario_S01 = {
    1u, s01_events, 3u, NULL, 0u, s01_faults, 2u, s01_steps, 7u
};

/* ============================================================================
 * S02: Ordered Dependency Blocking Under Fault
 * ============================================================================ */
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
const VirtualScenario scenario_S02 = {
    2u, s02_events, 3u, s02_deps, 1u, s02_faults, 2u, s02_steps, 8u
};

/* ============================================================================
 * S05: Retry Success and Trace Correlation
 * ============================================================================ */
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
const VirtualScenario scenario_S05 = {
    5u, s05_events, 1u, NULL, 0u, s05_faults, 2u, s05_steps, 3u
};

/* ============================================================================
 * S06: Bounded Recovery Progression (Retry to Reinitialization)
 * ============================================================================ */
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
const VirtualScenario scenario_S06 = {
    6u, s06_events, 1u, NULL, 0u, s06_faults, 4u, s06_steps, 5u
};

/* ============================================================================
 * S08: Ambiguous Association Safe Isolation (No Fabricated EventRef)
 * ============================================================================ */
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
const VirtualScenario scenario_S08 = {
    8u, s08_events, 1u, NULL, 0u, s08_faults, 2u, s08_steps, 3u
};

/* ============================================================================
 * S14: Mixed Dependencies and Replay Determinism
 * ============================================================================ */
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
const VirtualScenario scenario_S14 = {
    14u, s14_events, 3u, s14_deps, 2u, s14_faults, 2u, s14_steps, 9u
};

/* ============================================================================
 * Scenario Registry
 * ============================================================================ */
static const ScenarioRegistryEntry registry[] = {
    {
        "S01",
        "Independent Preservation Under Transient Fault",
        "Task 2 on I2C0 experiences transient NACK. Independent tasks 1 (I2C0) and 3 (UART0) continue and complete while task 2 recovers.",
        &scenario_S01
    },
    {
        "S02",
        "Ordered Dependency Blocking",
        "Task 2 depends on Task 1 (ORDERED). When Task 1 encounters a fault, Task 2 is blocked in ST_QUEUED while independent Task 3 completes.",
        &scenario_S02
    },
    {
        "S05",
        "Retry Success and Trace Correlation",
        "Single-event transient I2C NACK resolved by recovery retry. Demonstrates exact 1:1 wrapper-to-runtime trace correlation.",
        &scenario_S05
    },
    {
        "S06",
        "Bounded Recovery Progression to Reinitialization",
        "Repeated I2C timeouts trigger retry actions, followed by ACT_REINIT_OR_RESET on the third observation and a successful runtime transition.",
        &scenario_S06
    },
    {
        "S08",
        "Ambiguous Association Isolation",
        "Unmapped environmental fault with unknown association. Runtime terminates safely without fabricating synthetic EventRefs.",
        &scenario_S08
    },
    {
        "S14",
        "Mixed Dependencies and Deterministic Replay",
        "Chained dependencies (ORDERED + COUPLED) with transient fault recovery. Verifies bit-for-bit replay digest reproducibility.",
        &scenario_S14
    }
};

static const size_t registry_count = sizeof(registry) / sizeof(registry[0]);

const ScenarioRegistryEntry *virtual_scenario_get(size_t index) {
    if (index < registry_count) {
        return &registry[index];
    }
    return NULL;
}

size_t virtual_scenario_count(void) {
    return registry_count;
}

const ScenarioRegistryEntry *virtual_scenario_find(const char *id) {
    if (!id) return NULL;
    for (size_t i = 0; i < registry_count; ++i) {
        if (strcmp(registry[i].id, id) == 0) {
            return &registry[i];
        }
    }
    return NULL;
}
