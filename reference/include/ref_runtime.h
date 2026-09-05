#ifndef REF_RUNTIME_H
#define REF_RUNTIME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define QMAX 16u
#define XMAX 4u
#define DMAX 4u
#define ACTIVE_MAX (QMAX + XMAX)
#define EPMAX 1u
#define MAX_RECOVERY_ACTIONS 4u
#define MAX_TRANSACTION_MEMBERS 4u
#define TRACE_EVENT_CAP 256u
#define INVALID_SLOT 0xFFu
#define INVALID_TX 0xFFFFu

typedef enum { EVT_PERIPHERAL_READ=0, EVT_PERIPHERAL_WRITE, EVT_SERVICE, EVT_HOUSEKEEPING, EVT_RECOVERY_CONTROL } EventType;
typedef enum { PERIPH_NONE=0, PERIPH_I2C0, PERIPH_SPI0, PERIPH_UART0 } PeripheralId;
typedef enum { CRITICAL=0, NORMAL, DEFERABLE } Criticality;
typedef enum { DEP_INDEPENDENT=0, DEP_ORDERED, DEP_COUPLED } DependencyKind;
typedef enum { ST_FREE=0, ST_QUEUED, ST_ELIGIBLE, ST_EXECUTING, ST_FAILED, ST_QUARANTINED, ST_RETRY_PENDING, ST_COMPLETED, ST_DISCARDED, ST_ESCALATED } EventState;
typedef enum { ASSOC_EXACT=0, ASSOC_SERVICE_ONLY, ASSOC_PERIPHERAL_ONLY, ASSOC_UNKNOWN } AssociationLevel;
typedef enum { FAULT_NONE=0, FAULT_I2C_NACK, FAULT_I2C_TIMEOUT, FAULT_I2C_BERR, FAULT_I2C_ARLO, FAULT_I2C_PERSISTENT, FAULT_SPI_TIMEOUT, FAULT_SPI_VERIFY, FAULT_SPI_PERSISTENT, FAULT_SW_SERVICE, FAULT_AMBIGUOUS } FaultClass;
typedef enum { ACT_NONE=0, ACT_RETRY, ACT_REINIT_OR_RESET, ACT_DEGRADE, ACT_ESCALATE } RecoveryAction;
typedef enum { VAR_P0_FIXED_RETRY=0, VAR_P1_FIXED_RETRY_RECOVERY, VAR_P2_CONTEXT_ONLY, VAR_P3_CONTEXT_HISTORY, VAR_P4_INTEGRATED } PolicyVariant;
typedef enum { EP_IDLE=0, EP_ACTIVE, EP_TERMINAL } EpisodeState;
typedef enum { OUTCOME_NONE=0, OUTCOME_SUCCESS, OUTCOME_FAILURE, OUTCOME_TERMINAL_DEGRADE, OUTCOME_TERMINAL_ESCALATE, OUTCOME_QUEUE_FULL, OUTCOME_QUARANTINE_FULL, OUTCOME_EPISODE_FULL, OUTCOME_STALE_REF, OUTCOME_INVALID_DEPENDENCY } OutcomeCode;

typedef struct { uint8_t slot_id; uint8_t generation; } EventRef;
typedef struct { EventRef referenced; DependencyKind kind; uint8_t acceptable_state; } DependencyEntry;
typedef struct { uint16_t transaction_id; uint8_t member_count; EventRef members[MAX_TRANSACTION_MEMBERS]; bool member_retry_safe; bool valid; } TransactionRecord;
typedef struct { uint8_t slot_id; uint8_t generation; EventType type; uint8_t producer_id; uint8_t service_id; uint8_t consumer_id; PeripheralId peripheral; Criticality criticality; uint16_t transaction_id; DependencyEntry dependencies[DMAX]; uint8_t dependency_count; EventState state; bool fault_associated; bool degradable; bool verification_ok; bool shared_state_valid; } EventSlot;
typedef struct { FaultClass fault_class; AssociationLevel association; uint8_t attempt_count; Criticality criticality; bool retry_safe; bool reinit_safe; bool degrade_safe; bool dependencies_safe; bool shared_state_valid; EpisodeState episode_state; EventRef target_ref; uint16_t target_transaction; uint8_t service_id; PeripheralId peripheral; uint8_t observation_count; bool active; } FaultContext;
typedef struct { RecoveryAction action; AssociationLevel target_scope; bool quarantine_required; bool retry_authorized; bool release_candidate; bool terminal; uint8_t attempt_index; uint8_t reason_code; } PolicyDecision;
typedef struct { FaultClass fault_class; EventRef target_ref; uint16_t transaction_id; uint8_t trigger_action_index; uint8_t remaining_failures; bool enabled; } FaultInjection;
typedef struct { uint32_t run_id; uint32_t trace_seq; uint32_t fault_episode_id; EventRef event_ref; uint16_t transaction_id; uint8_t observation_seq; uint8_t action_index; uint8_t state; uint8_t action; uint8_t outcome; uint8_t correctness; } TraceRecord;
typedef struct { EventSlot slots[ACTIVE_MAX]; uint8_t queue[QMAX]; uint8_t queue_count; uint8_t quarantine_count; uint8_t generation_next[ACTIVE_MAX]; TransactionRecord transactions[QMAX]; uint8_t transaction_count; FaultContext episode; bool episode_in_use; PolicyVariant variant; uint32_t run_id; uint32_t fault_episode_id_next; uint32_t active_fault_episode_id; uint8_t workload_id; uint8_t fault_schedule_id; uint32_t trace_seq; TraceRecord trace[TRACE_EVENT_CAP]; uint16_t trace_count; } Runtime;

void runtime_init(Runtime *rt, PolicyVariant variant);
EventRef event_ref_invalid(void);
bool event_ref_equal(EventRef a, EventRef b);
bool event_ref_valid(const Runtime *rt, EventRef ref);
OutcomeCode runtime_admit(Runtime *rt, const EventSlot *spec, EventRef *out_ref);
OutcomeCode runtime_add_dependency(Runtime *rt, EventRef target, EventRef predecessor, DependencyKind kind, EventState acceptable_state);
bool scheduler_select(Runtime *rt, EventRef *selected);
OutcomeCode runtime_execute_selected(Runtime *rt, EventRef selected, const FaultInjection *fault, bool *faulted);
PolicyDecision policy_decide(const Runtime *rt, const FaultContext *ctx);
OutcomeCode runtime_start_fault(Runtime *rt, FaultClass fault, AssociationLevel assoc, EventRef target, uint16_t tx_id, Criticality criticality, bool retry_safe, bool reinit_safe, bool degrade_safe);
OutcomeCode runtime_apply_policy(Runtime *rt, const FaultInjection *fault);
OutcomeCode runtime_verify_and_release(Runtime *rt, bool verification_ok);
bool dependency_allows(const Runtime *rt, const EventSlot *event);
bool ordinary_dispatch_allowed(const Runtime *rt, const EventSlot *event);
size_t runtime_static_bytes(void);
size_t runtime_slot_bytes(void);
size_t runtime_trace_bytes(void);
void runtime_set_trace_metadata(Runtime *rt, uint32_t run_id, uint8_t workload_id, uint8_t fault_schedule_id);
size_t trace_write_csv(const Runtime *rt, int fd);
bool fault_injection_triggers(const FaultInjection *fault, EventRef ref, uint8_t action_index);

#endif
