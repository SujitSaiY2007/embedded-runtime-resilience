#ifndef VIRTUAL_SYSTEM_H
#define VIRTUAL_SYSTEM_H

#include "ref_runtime.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VIRTUAL_MAX_EVENTS ACTIVE_MAX
#define VIRTUAL_MAX_STEPS 64u
#define VIRTUAL_MAX_FAULT_SCHEDULES 32u
#define VIRTUAL_MAX_ENV_TRACE 256u
#define VIRTUAL_MAX_PERIPHERALS 3u
#define VIRTUAL_MAX_EVENT_KEY 255u

typedef uint8_t ScenarioEventKey;

typedef enum {
    VSTEP_ADMIT = 0,
    VSTEP_DEPEND,
    VSTEP_START_FAULT,
    VSTEP_DRAIN,
    VSTEP_APPLY_FAULT
} VirtualStepKind;

typedef enum {
    VPERIPH_READY = 0,
    VPERIPH_SUCCESS,
    VPERIPH_NACK,
    VPERIPH_TIMEOUT,
    VPERIPH_PROTOCOL_ERROR,
    VPERIPH_ARBITRATION_ERROR,
    VPERIPH_VERIFY_FAILURE,
    VPERIPH_PERSISTENT_FAILURE
} VirtualPeripheralStatus;

typedef struct {
    ScenarioEventKey scenario_event_key;
    EventType event_type;
    uint8_t producer_id;
    uint8_t service_id;
    uint8_t consumer_id;
    PeripheralId peripheral;
    Criticality criticality;
    uint16_t transaction_id;
    bool degradable;
} VirtualEventSpec;

typedef struct {
    ScenarioEventKey target_key;
    ScenarioEventKey predecessor_key;
    DependencyKind kind;
    EventState acceptable_state;
} VirtualDependencySpec;

typedef struct {
    uint16_t schedule_id;
    uint8_t action_index;
    FaultClass fault_class;
    AssociationLevel association;
    ScenarioEventKey target_key;
    uint16_t transaction_id;
    Criticality criticality;
    bool retry_safe;
    bool reinit_safe;
    bool degrade_safe;
    bool enabled;
} VirtualFaultSchedule;

typedef struct {
    uint16_t sequence;
    VirtualStepKind kind;
    uint16_t a;
    uint16_t b;
    uint16_t c;
    uint16_t d;
} VirtualStep;

typedef struct {
    uint16_t scenario_id;
    const VirtualEventSpec *events;
    uint8_t event_count;
    const VirtualDependencySpec *dependencies;
    uint8_t dependency_count;
    const VirtualFaultSchedule *fault_schedules;
    uint8_t fault_schedule_count;
    const VirtualStep *steps;
    uint8_t step_count;
} VirtualScenario;

typedef struct {
    PeripheralId peripheral;
    uint32_t operation_sequence;
    VirtualPeripheralStatus status;
    FaultClass fault_class;
    uint16_t transaction_id;
    EventRef event_ref;
} VirtualPeripheralRecord;

typedef struct {
    uint32_t wrapper_sequence;
    uint32_t runtime_trace_first;
    uint32_t runtime_trace_last;
    uint16_t scenario_id;
    uint16_t step_sequence;
    ScenarioEventKey scenario_event_key;
    EventRef event_ref;
    PeripheralId peripheral;
    uint16_t transaction_id;
    RecoveryAction action;
    OutcomeCode outcome;
    VirtualPeripheralStatus environmental_status;
    FaultClass fault_class;
    bool runtime_authoritative;
} VirtualTraceRecord;

typedef struct {
    Runtime runtime;
    const VirtualScenario *scenario;
    EventRef event_refs[VIRTUAL_MAX_EVENTS];
    bool event_ref_valid[VIRTUAL_MAX_EVENTS];
    uint32_t run_id;
    uint16_t step_index;
    uint32_t wrapper_sequence;
    uint32_t peripheral_sequence[VIRTUAL_MAX_PERIPHERALS];
    VirtualPeripheralRecord peripheral_trace[VIRTUAL_MAX_ENV_TRACE];
    uint16_t peripheral_trace_count;
    VirtualTraceRecord trace[VIRTUAL_MAX_ENV_TRACE];
    uint16_t trace_count;
    bool adapter_error;
    OutcomeCode last_outcome;
} VirtualSystem;

void virtual_system_init(VirtualSystem *vs, const VirtualScenario *scenario,
                         PolicyVariant variant, uint32_t run_id);
OutcomeCode virtual_system_run(VirtualSystem *vs);
OutcomeCode virtual_system_step(VirtualSystem *vs);
bool virtual_system_complete(const VirtualSystem *vs);
uint32_t virtual_system_digest(const VirtualSystem *vs);

const EventRef *virtual_system_event_ref(const VirtualSystem *vs,
                                         ScenarioEventKey key);
const VirtualTraceRecord *virtual_system_trace_at(const VirtualSystem *vs,
                                                  uint16_t index);
const VirtualPeripheralRecord *virtual_system_peripheral_trace_at(
    const VirtualSystem *vs, uint16_t index);

#endif
