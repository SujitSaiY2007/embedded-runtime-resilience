# Part II — Virtual Embedded System Technical Design (K.5)

Checkpoint: K.5 — Virtual Embedded System Technical Design + Interface Contracts  
Date: 2026-10-01  
Status: Design complete; implementation deferred to K.6  
Base exp commit: 5b7e1c3565a20462629c20c97b13545a1be8f878

## 1. Purpose

K.5 converts the K.4 conceptual chain into an implementation-ready virtual embedded-system design without implementing the simulator, UI, or a second recovery policy.

Locked chain:

UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI

The virtual system is an environmental model. The existing ISO C11 reference runtime remains the sole recovery-policy authority.

## 2. Existing runtime contract observed

The current runtime exposes Runtime with fixed EventSlot[ACTIVE_MAX], queue, transactions, one active FaultContext, trace pool and bounded metadata; EventRef={slot_id,generation}; runtime_admit(); runtime_add_dependency(); scheduler_select(); runtime_execute_selected(); runtime_start_fault(); policy_decide(); runtime_apply_policy(); runtime_verify_and_release(); FaultInjection; PolicyDecision; and TraceRecord.

The virtual system must adapt to these APIs. It must not replace them with a parallel policy representation.

## 3. Virtual-system components

### Deterministic scheduler/environment

Owns scenario step index, deterministic workload admission order, virtual sequence/time, event specifications, runtime invocation order, and external observations. It does not choose recovery actions.

The C runtime scheduler_select() remains authoritative for event eligibility.

### Virtual event/workload source

A workload is a declarative sequence of event specifications containing event type, producer/service/consumer IDs, primary peripheral, criticality, transaction ID, degradability and dependency declarations.

The source submits through runtime_admit(). It never assigns the final EventRef.

### Virtual peripherals

Three models are defined:

- I2C0 — primary fault domain
- SPI0 — secondary fault domain
- UART0 — diagnostic/control path

Peripheral state is environmental state, not recovery-policy state.

### Fault injector

Owns an immutable deterministic schedule identifying scenario/run, injection sequence, peripheral, fault class, injection point, affected EventRef when exact association is justified, transaction ID where applicable, association level and deterministic recovery-action failure positions.

It does not infer association from peripheral equality.

### Runtime adapter

The adapter is the only bridge between virtual environment and C runtime.

It:
1. converts workload event specifications into EventSlot;
2. calls runtime_admit();
3. records returned EventRef;
4. installs dependencies with runtime_add_dependency();
5. presents fault observations through runtime_start_fault();
6. obtains authoritative PolicyDecision through policy_decide() when a decision must be observed;
7. invokes the existing runtime transition path without changing policy semantics;
8. reads authoritative runtime state/trace for presentation.

It never computes an alternative recovery action.

## 4. Event identity and lifecycle

The C runtime is the identity authority.

The virtual system may maintain a scenario-side ScenarioEventKey -> EventRef mapping only for lookup/correlation. It must not manufacture EventRefs.

Required identity chain:

scenario event -> runtime EventRef -> fault observation -> episode -> trace

When a slot is reused, the new generation returned by runtime_admit() replaces the old mapping. Stale EventRefs must fail closed.

The virtual model does not introduce a second lifecycle. Runtime lifecycle states are authoritative.

## 5. Dependency and ordering

Scenario declarations use:

- INDEPENDENT — no dependency entry
- ORDERED — predecessor EventRef + acceptable state
- COUPLED — predecessor/transaction EventRef + coupled semantics

The scenario layer may validate bounded declarations, but it must not infer dependencies from shared peripheral identity.

dependency_allows() and scheduler_select() remain authoritative.

Admission order is preserved by workload sequence. Execution eligibility is determined by the runtime.

## 6. Virtual peripheral contract

Conceptual operation:

PeripheralOperation = {peripheral, event_ref, transaction_id, operation_kind, sequence}

Conceptual result:

PeripheralResult = {status, fault_class, evidence_level, progress, verification_ok}

Finite environmental statuses are:

- READY/SUCCESS
- NACK
- TIMEOUT/NO_PROGRESS
- PROTOCOL_ERROR
- ARBITRATION_ERROR
- VERIFY_FAILURE
- PERSISTENT_FAILURE

The peripheral model may report evidence, but it cannot turn weak evidence into an exact EventRef.

### I2C mapping

NACK -> FAULT_I2C_NACK  
timeout/no progress -> FAULT_I2C_TIMEOUT  
bus/protocol error -> FAULT_I2C_BERR  
arbitration loss -> FAULT_I2C_ARLO  
repeated declared failure -> FAULT_I2C_PERSISTENT

### SPI mapping

timeout -> FAULT_SPI_TIMEOUT  
verification failure -> FAULT_SPI_VERIFY  
repeated declared failure -> FAULT_SPI_PERSISTENT

SPI does not inherit I2C-specific evidence assumptions.

### UART

UART is diagnostic/control infrastructure in K.5. It does not receive a new recovery policy or fault taxonomy.

## 7. Deterministic fault injection

A fault schedule is immutable for a run.

The runtime-facing record maps to the existing FaultInjection:

- fault_class
- target_ref
- transaction_id
- trigger_action_index
- enabled

For non-exact association, target_ref is invalid rather than fabricated.

The same scenario inputs must reproduce the same fault schedule. No schedule mutation based on observed results is permitted.

## 8. Runtime input boundary

The adapter may supply only information already represented by the current runtime API.

Admission:
VirtualEventSpec -> EventSlot -> runtime_admit() -> EventRef

Dependency:
EventRef pairs + dependency kind + acceptable state -> runtime_add_dependency()

Fault observation:
FaultClass + AssociationLevel + target EventRef/transaction + criticality + safety flags -> runtime_start_fault()

Recovery stimulus:
FaultInjection -> runtime_apply_policy()

No UI or simulator command may directly supply RecoveryAction.

## 9. Runtime output boundary

Authoritative outputs include returned EventRef, OutcomeCode, PolicyDecision, runtime event/episode state, queue/quarantine counts, trace records and verification/release/terminal result.

Environmental observations may be added, but displayed recovery conclusions must be traceable to runtime output.

## 10. Important adapter limitation

The current C runtime models recovery outcomes through FaultInjection and runtime_apply_policy(); it does not expose a peripheral-action callback.

K.6 must therefore not silently add one or modify the recovery mechanism.

For the K.6 demonstrator, the virtual peripheral model may mirror the same deterministic action-success/failure schedule as an environmental observation, while the C runtime remains authoritative for recovery transition and verification. A mismatch is an adapter/model inconsistency, not an opportunity to add a new policy.

If later hardware validation requires a callback-based action boundary, that is a separate design decision and must stop for review before changing the C runtime API.

## 11. Ownership boundaries

| Object/state | Owner | Other layers |
|---|---|---|
| EventRef | C runtime | read-only |
| EventSlot lifecycle | C runtime | read-only |
| Queue/quarantine state | C runtime | read-only |
| Dependency semantics | C runtime | declarations only |
| Fault schedule | Virtual environment | runtime consumes mapped observation |
| Peripheral environmental state | Virtual peripheral model | runtime observes evidence |
| Recovery decision | C runtime | read-only |
| Recovery attempt count | C runtime | read-only |
| Verification/release | C runtime | read-only |
| Trace record | C runtime | rendered/exported |
| Scenario selection | UI/controller | cannot select action |
| Run/scenario metadata | environment | copied into runtime trace metadata |

## 12. Static/bounded constraints

K.5 preserves:
QMAX=16, XMAX=4, DMAX=4, EPMAX=1, MAX_RECOVERY_ACTIONS=4, TRACE_EVENT_CAP=256.

The virtual layer must use fixed-capacity records for the canonical implementation. No dynamic allocation is required.

## 13. Trace/evidence path

Authoritative causal path:

admission -> EventRef -> observation -> association -> quarantine/retention -> policy decision -> action outcome -> verification -> release/terminal -> trace

The runtime TraceRecord is authoritative for fields it emits. K.6 may add wrapper-level scenario/environment records, but they must retain run ID, EventRef and sequence correlation where applicable and must never invent a recovery decision.

## 14. Determinism rules

For the same scenario definition, workload sequence, initial peripheral state, fault schedule, policy variant and runtime build, the virtual system must produce the same runtime input sequence and equivalent authoritative trace.

Every canonical run starts with fresh virtual state and runtime_init().

## 15. K.6 implementation starting point

1. fixed scenario/workload representation
2. virtual I2C/SPI/UART models
3. deterministic fault schedule
4. runtime adapter using existing ref_runtime.h
5. event/dependency admission
6. scheduler loop
7. fault observation bridge
8. authoritative recovery/verification path
9. trace correlation and replay checks

No runtime policy code is required by this design.

## 16. Non-goals

No simulator implementation, UI implementation, new recovery action, new policy variant, hardware driver, STM32U575 integration, physical fault injection, baseline experiment, or K.7-K.10 work.
