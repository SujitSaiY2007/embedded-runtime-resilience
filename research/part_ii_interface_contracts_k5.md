# Part II — K.5 Interface and Contract Specification

Checkpoint: K.5  
Status: Design-only contract; implementation deferred to K.6

## 1. Contract layers

### C1 — Scenario -> Virtual Environment
Input: ScenarioDefinition plus deterministic workload/fault schedule IDs.  
Output: bounded run context and reset acknowledgement.

The caller cannot specify a recovery action.

### C2 — Virtual Environment -> C Runtime

Event admission:
VirtualEventSpec -> EventSlot -> runtime_admit() -> EventRef

Dependency declaration:
DependencySpec -> runtime_add_dependency()

Fault observation:
VirtualFaultObservation -> runtime_start_fault()

Recovery progression:
FaultInjection -> runtime_apply_policy()

Verification:
verification_ok -> runtime_verify_and_release() where the existing runtime path requires direct verification.

### C3 — C Runtime -> Adapter

Outputs: EventRef, OutcomeCode, PolicyDecision, event/episode state, queue/quarantine counts, trace records and verification/release/terminal result.

### C4 — Runtime/Environment -> Trace

Runtime-generated trace is authoritative. Environment records are supplementary and correlate to runtime identifiers.

### C5 — Trace -> UI

Read-only projection. UI controls scenario selection, reset/start and display filtering only. It cannot mutate runtime policy state or supply an action.

## 2. VirtualEventSpec

VirtualEventSpec {
    scenario_event_key
    event_type
    producer_id
    service_id
    consumer_id
    peripheral
    criticality
    transaction_id
    degradable
    dependencies[DMAX]
    dependency_count
}

The adapter constructs the existing EventSlot. Runtime supplies slot_id and generation.

## 3. DependencySpec

DependencySpec {
    target_scenario_key
    predecessor_scenario_key
    kind
    acceptable_state
}

kind is ORDERED or COUPLED. Failure to resolve a scenario key is an input error, not a policy decision.

## 4. FaultObservation

FaultObservation {
    scenario_id
    sequence
    peripheral
    fault_class
    association_level
    target_scenario_key_or_none
    target_event_ref_or_none
    transaction_id_or_none
    criticality
    retry_safe
    reinit_safe
    degrade_safe
    evidence_flags
}

Rules:
- EXACT requires a valid runtime EventRef.
- SERVICE_ONLY/PERIPHERAL_ONLY/UNKNOWN do not fabricate an exact target.
- association specificity may not exceed evidence specificity.

## 5. FaultInjection

The runtime-facing record remains the existing C structure:
fault_class, target_ref, transaction_id, trigger_action_index, remaining_failures, enabled.

K.5 does not add fields to that structure.

## 6. PolicyDecision

The existing runtime PolicyDecision is authoritative:
action, target_scope, quarantine_required, retry_authorized, release_candidate, terminal, attempt_index, reason_code.

The UI/virtual system may display these fields. It may not calculate a replacement decision.

## 7. Peripheral contract

PeripheralOperation {
    peripheral
    event_ref
    transaction_id
    operation_kind
    sequence
}

PeripheralResult {
    status
    fault_class
    evidence_level
    progress
    verification_ok
}

The environmental model is finite and deterministic. It cannot mutate C-runtime recovery state directly.

## 8. Run/trace correlation

RunContext {
    run_id
    scenario_id
    variant
    workload_id
    fault_schedule_id
    deterministic_schedule_id
}

Every wrapper observation carries the runtime EventRef or an explicit no-event-ref marker. Runtime trace retains run_id, trace_seq, fault_episode_id, EventRef and transaction ID.

## 9. Ownership and lifetime

- Scenario definitions: immutable for a run.
- Fault schedules: immutable for a run.
- Virtual peripheral state: environment-owned; reset per run.
- Runtime state: Runtime-owned; reset with runtime_init().
- EventRef: runtime-generated; valid only while runtime says it is valid.
- Trace records: runtime-owned; adapter/UI reads snapshots.
- Wrapper correlation records: fixed-capacity environment-owned records.
- No layer transfers ownership of a Runtime EventSlot.

## 10. Error handling

Adapter errors are distinct from policy outcomes.

Examples: unresolved scenario key, dependency target not yet admitted, malformed fault schedule, exhausted environmental schedule, wrapper trace-correlation overflow.

These are scenario/adapter errors and must not be converted into synthetic recovery decisions.

Runtime outcomes such as OUTCOME_FAILURE, OUTCOME_TERMINAL_ESCALATE, OUTCOME_EPISODE_FULL and OUTCOME_QUARANTINE_FULL remain runtime outcomes.

## 11. Baseline boundary

K.5 defines the baseline connection but does not implement a new baseline.

P0-P4 continue to use the existing Runtime.variant selector.

For K.6, a baseline scenario is the same virtual workload/fault input routed through the selected existing runtime variant. No separate baseline recovery engine is introduced.

The known P0-P3 quarantine-ablation limitation remains unchanged.

## 12. Authority rules

1. Runtime owns recovery.
2. Runtime owns EventRef identity.
3. Runtime owns dependency evaluation.
4. Runtime owns quarantine state.
5. Runtime owns verification/release.
6. Environment owns stimulus and peripheral state.
7. UI owns presentation and scenario controls only.
8. Trace records runtime facts; wrapper records environmental facts.
9. No layer may infer more causal precision than supplied evidence.
10. No interface accepts a desired recovery action.

## 13. K.5 acceptance

The contract is implementation-ready when K.6 can implement the virtual system using the existing ref_runtime.h API without modifying recovery semantics. This is satisfied for the current reference path, with the documented limitation that peripheral action execution is an environmental mirror of the deterministic runtime fault schedule rather than a new runtime callback.
