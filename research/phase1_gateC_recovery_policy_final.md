# Phase 1E.1 — Gate C Final Recovery Policy and Bounded State Machine

**Gate:** C — Recovery Policy + Bounded State Machine  
**Phase:** 1E.1 — Experimental Design / Formalization Foundation  
**Status:** ACCEPTED at the semantic/design level; implementation and physical validation remain deferred.  
**Date:** 2026-09-03

## 1. Scope and acceptance boundary

Gate C derives the smallest defensible deterministic recovery policy from the frozen Gate A event/dependency contract and Gate B fault/association contract.

The policy is deliberately software-only, zero-heap, finite, inspectable, and bounded. It does not attempt to be a general resilience framework.

Gate C freezes policy semantics, state transitions, action preconditions/effects/postconditions, association-aware containment, recovery-history representation, scheduling interaction, degraded behavior, and bounded termination. It does not freeze byte-level C packing, final workload capacities, benchmark values, physical fault-injection apparatus, or MPU configuration details that belong to Gates D/E or physical bring-up.

Acceptance requires that:

1. every policy input has a decision or safety justification;
2. no input is retained merely because it appeared in the earlier proposal;
3. the action set is finite and technically meaningful;
4. every path terminates within the declared bound;
5. quarantine and dependency semantics cannot be bypassed by recovery;
6. ambiguous association never becomes false event-level precision;
7. the policy has no runtime heap requirement;
8. ablation can test whether context/history/quarantine actually adds value.

## 2. Relationship to Gate A

Gate A defines what work exists, how events are identified, what depends on what, and when an event is eligible. Gate C consumes those semantics; it does not redefine them.

Frozen Gate A constraints carried into this gate:

- `EventRef = {slot_id, generation}`;
- separate bounded transaction identity where required;
- dependency classes `INDEPENDENT`, `ORDERED`, and `COUPLED/TRANSACTIONAL`;
- FIFO is admission order, not universal execution order;
- dispatch is controlled by an eligibility predicate;
- quarantine is retained non-executable state;
- preservation means correct verified execution;
- fault association scope is distinct from dependency-blocking scope.

Recovery may quarantine/release/retry an event only through explicit lifecycle transitions. It may not silently delete queue entries or bypass dependency rules.

## 3. Relationship to Gate B

Gate B supplies the observed fault class, association confidence, event/transaction/resource context where available, and episode/history semantics.

Primary I2C observations remain NACK, timeout/no-progress, bus/protocol error, arbitration loss, and persistent no-progress/suspected peripheral-state failure. SPI remains deliberately reduced.

The governing rule is:

`association precision <= evidence precision`

Gate C therefore treats association level as a safety-relevant policy input. It never manufactures an event-level target from peripheral equality alone.

## 4. Design challenge of the earlier proposal

The earlier `research/phase1_recovery_policy_design.md` proposed eight inputs and a provisional `Rmax=3`. Gate C does not copy them blindly.

### 4.1 `fault_class` — RETAIN

It directly changes which actions are sensible. For example, a NACK and persistent no-progress need not follow the same recovery ladder.

### 4.2 `fault_recurrence` — REPLACE WITH DERIVED EPISODE STATE

A separate recurrence field is unnecessary for the decision engine. Recurrence is represented by the bounded episode's observation/attempt progression. The policy receives `attempt_count` and `episode_status`; repeated qualifying observations update the bounded episode state.

### 4.3 `attempt_count` — RETAIN

It is necessary to enforce the finite recovery ladder and prevent retry loops.

### 4.4 `last_action` — REJECT AS AN INDEPENDENT INPUT

The current recovery phase plus bounded action-attempt state already identifies what has been attempted. Storing `last_action` separately duplicates state-machine information.

### 4.5 `last_outcome` — REJECT AS AN INDEPENDENT INPUT

The current recovery phase transitions only after an explicit outcome. Therefore the state machine itself records the information needed to choose the next step. A separate last-outcome field is retained only in experimental logging if needed; it is not a policy input.

### 4.6 `service_criticality` — RETAIN, BUT ONLY AS A CONSTRAINING CONTEXT

Criticality genuinely affects whether degradation is permissible and whether inability to continue requires escalation. It does not decide ordinary retry ordering and never overrides dependency or safety constraints.

The policy therefore consumes a bounded `criticality/degradability` context rather than treating criticality as a priority score.

### 4.7 `event_dependency_status` — MOVE TO POLICY PRECONDITIONS

The policy should not duplicate Gate A's scheduler graph. Dependency eligibility is computed by the scheduler. The recovery action receives the result needed to determine whether an event can be released/retried and whether dependent work must remain blocked.

Thus dependency status is a safety gate, not a free-standing policy feature.

### 4.8 `pending_independent_work` — REJECT AS A POLICY INPUT

Whether independent work is pending is scheduler state. It should not change the recovery action itself. The scheduler independently evaluates eligible work while recovery is in progress.

This separation prevents the recovery policy from becoming coupled to queue occupancy and makes ablation cleaner.

## 5. Minimum policy context

The minimum normative policy context is:

1. `fault_class` — observed fault category;
2. `association_level` — one of the four Gate B association levels;
3. `attempt_count` — bounded number of recovery attempts already started for the episode;
4. `criticality` — `CRITICAL`, `NORMAL`, or `DEFERABLE`;
5. `recovery_safety` — bounded precondition results indicating whether retry, peripheral recovery, and degradation are currently permitted;
6. `episode_state` — bounded recovery phase/terminal status.

The following are carried only when required by the action target, not as general policy variables:

- `EventRef` and transaction identity for exact association;
- service/peripheral identity for broader association;
- dependency references and shared-state validity from Gate A;
- verification result produced by the action.

This is intentionally smaller than the original eight-variable proposal.

### Policy input decision rule

A variable is normative only if removing it can change a permitted action or a safety precondition. Timing/cycle counts, queue occupancy, and detailed diagnostic flags may be logged for experiments but are not policy inputs unless a later gate demonstrates a necessary decision dependency.

## 6. Minimum bounded recovery history

The minimum history is **per active fault episode**, not a general circular database.

Normative recovery state contains:

- `attempt_count`;
- `episode_state`;
- the currently/previously selected action as implied by the state-machine phase, not a duplicated `last_action` field;
- bounded association target information required while the episode is active.

The episode state distinguishes at least:

`IDLE -> QUARANTINED -> RETRY_PENDING/RECOVERY_PENDING -> VERIFYING -> terminal`

A separate recurrence counter is not required for policy correctness. Repeated observations are represented by the episode's attempt/failure progression. If later experiments require a metric such as exact observation count, it may be recorded in a fixed diagnostic field without becoming a decision input.

No unbounded history is retained. A new episode begins after verified success, degraded terminal handling, or escalation, consistent with Gate B.

## 7. Finite action set

Gate C freezes four **logical** policy actions:

1. `RETRY`
2. `REINIT_OR_RESET`
3. `DEGRADE`
4. `ESCALATE`

`REINIT_OR_RESET` is intentionally one policy action rather than two artificial actions.

### 7.1 U575 reinitialization versus reset challenge

The distinction is real at the implementation-mechanism level: HAL-style deinitialization/reinitialization can restore peripheral configuration and invoke associated low-level resource setup, whereas a peripheral reset through the reset/clock-control mechanism resets the peripheral hardware state. These operations can therefore have different scope and side effects. ST documentation distinguishes initialization/de-initialization APIs, and the U5 documentation provides the peripheral/reset architecture. citeturn0search4turn0search1

However, Gate C is the policy gate, not the implementation experiment. It therefore does **not** claim that the two operations will always produce different experimental outcomes. The policy-level action is `REINIT_OR_RESET`; the later implementation/test configuration may define a concrete method such as `DRIVER_REINIT` or `RCC_PERIPHERAL_RESET` only if it is technically supported and experimentally distinguishable. A bus-recovery sequence that changes GPIO/clock ownership is a separate implementation mechanism and must not be silently conflated with either operation.

### 7.2 RETRY

Repeat the same event/transaction only when the transaction contract permits retry and required peripheral/shared state remains valid.

### 7.3 REINIT_OR_RESET

Perform one bounded peripheral-local recovery operation using the implementation-selected method, then verify the peripheral/service and affected event before release.

### 7.4 DEGRADE

Move a safely degradable service/event to its declared degraded terminal behavior while leaving unrelated eligible work available.

### 7.5 ESCALATE

Terminate local recovery and emit the bounded escalation result. The project does not prescribe a general system-level escalation architecture.

## 8. Action preconditions, effects, postconditions, failure handling

| Action | Preconditions | Effects | Success postcondition | Failure handling |
|---|---|---|---|---|
| `RETRY` | exact/recoverable association; retry-safe transaction; dependencies/shared state valid; retry budget available | associated event remains quarantined; one retry execution occurs | transaction/service verification succeeds | remain quarantined; increment attempt; reassess or escalate if bound reached |
| `REINIT_OR_RESET` | local peripheral/service recovery permitted; affected dependencies remain blocked where required; bound available | peripheral is reinitialized/reset by one declared method; affected event remains quarantined | peripheral/service and event verification succeed | remain quarantined; go to degrade if safe, otherwise escalate |
| `DEGRADE` | service has declared safe degraded behavior; criticality does not prohibit it; dependency consequences are bounded | affected service/event becomes terminal degraded state; dependent work remains blocked or reclassified according to contract | degraded state is explicitly recorded and safe | escalate if degraded state cannot be established safely |
| `ESCALATE` | local recovery is unsafe, unsupported, ambiguous beyond safe scope, or exhausted | local recovery stops; bounded escalation result emitted | episode is terminal escalated | no further local recovery attempts |

A successful peripheral operation is not sufficient by itself. The associated event/service must satisfy its verification condition before release.

## 9. Association-confidence-dependent behavior

### `EXACT_EVENT_TRANSACTION`

The specific event/transaction may be quarantined. Independent events remain governed by Gate A eligibility. Retry is permitted when transaction retry is safe. Broader containment is allowed only when the recovery action itself invalidates shared state or dependencies.

### `SERVICE_ONLY`

Do not invent a specific event target. Service-level recovery may quarantine/block the service's affected work according to explicit service ownership rules. Other services remain eligible unless dependencies/shared state require blocking.

### `PERIPHERAL_ONLY`

Do not attribute the fault to one event. Peripheral-local recovery may proceed. All events whose correctness depends on the affected peripheral state are blocked by the scheduler until the peripheral is verified; independent work remains eligible.

### `UNKNOWN_AMBIGUOUS`

No event-level quarantine target is invented. The policy enters the narrowest conservative containment supported by safety evidence. If safe local containment cannot be established, the policy escalates. Release requires fresh positive verification; absence of another error is not sufficient evidence when the association remains unresolved.

This is intentionally conservative: ambiguity can widen dependency blocking, but it can never create false precision.

## 10. Deterministic decision policy

The policy is a rule table, not a numeric score.

### Decision table

| Condition, evaluated in order | Action/result |
|---|---|
| No active fault episode | `NO_ACTION` / normal scheduling |
| Association is ambiguous and no safe local containment is available | `ESCALATE` |
| Current action/verification has succeeded | `RELEASE` affected event if Gate A eligibility is restored; close episode |
| Recovery safety says continued local execution is prohibited | `ESCALATE` unless a declared degraded terminal state is immediately safe |
| Attempt bound exhausted | `DEGRADE` if safely degradable; otherwise `ESCALATE` |
| Fault is retry-safe and retry budget remains | `RETRY` |
| Retry has failed and local peripheral recovery is permitted | `REINIT_OR_RESET` |
| Peripheral recovery failed and safe degraded mode exists | `DEGRADE` |
| None of the above permits a bounded safe action | `ESCALATE` |

The order matters. Safety/termination checks precede convenience. `pending_independent_work` never changes this table.

### Retry budget

Gate C freezes **at most two `RETRY` actions per episode** before `REINIT_OR_RESET` becomes the next local recovery opportunity. This gives a deterministic distinction between a single transient failure and repeated failure without making retry unbounded.

### Recovery ladder

`FAULT -> QUARANTINE -> RETRY #1 -> VERIFY`

If failed:

`-> RETRY #2 -> VERIFY`

If failed again:

`-> REINIT_OR_RESET -> VERIFY`

If that fails:

`-> DEGRADE` when safe, otherwise `ESCALATE`.

The ladder is a policy order, not a claim that every fault class must traverse every action. A fault class may skip retry when its preconditions say retry is unsafe or meaningless.

## 11. Exact attempt semantics

An **attempt** is one invocation of a recovery action that can produce an observable recovery outcome. Specifically:

- each `RETRY` transaction execution counts as one attempt;
- one `REINIT_OR_RESET` operation counts as one attempt;
- `DEGRADE` and `ESCALATE` are terminal policy actions and do not create retry attempts;
- verification following an action is part of that attempt's completion and does not create a second attempt;
- scheduler dispatches of unrelated events are not recovery attempts;
- repeated fault observations without a new recovery action update episode evidence but do not themselves increment the action-attempt count.

This makes the budget measurable and prevents hidden retries inside driver code from escaping the policy count. Implementation must ensure the lower-level driver does not silently perform additional recovery retries under the policy's name.

## 12. Exact transition-budget semantics

Gate C freezes a maximum of **4 recovery-action transitions per fault episode**:

`T1 = RETRY #1`
`T2 = RETRY #2`
`T3 = REINIT_OR_RESET`
`T4 = one terminal action: DEGRADE or ESCALATE`

The terminal action is mandatory by `T4` if earlier recovery has not succeeded.

Therefore:

`MAX_RECOVERY_ACTIONS = 4`

and every episode terminates no later than the completion of `T4`.

State transitions that merely move `QUARANTINED -> RETRY_PENDING -> VERIFYING` are lifecycle transitions, not additional recovery-action budget units. They are nevertheless bounded by the action sequence above.

If an action fails before its normal postcondition can be evaluated, that action still consumes its one transition and the policy proceeds to the next permitted ladder step.

The earlier proposal's `Rmax=3` is therefore **rejected as underspecified**, because it did not distinguish retries, peripheral recovery, and terminal handling. Gate C replaces it with the explicit four-action budget above.

## 13. Complete recovery state machine

```text
IDLE/NORMAL
   |
   | observed fault
   v
FAULT_CAPTURED
   |
   | validate episode + association
   v
QUARANTINED_OR_CONTAINED
   |
   | safety/eligibility checks
   v
POLICY_EVALUATION
   |-----------------------------|
   | safe retry                  | retry unsafe / retry budget exhausted
   v                             v
RETRY_PENDING              RECOVERY_PENDING
   |                             |
   v                             v
EXECUTING_RETRY            REINIT_OR_RESET
   |                             |
   v                             v
VERIFYING ----------------> VERIFYING
   |
   | success
   v
RELEASE_CANDIDATE
   |
   | Gate A eligibility + verification satisfied
   v
RELEASED/ELIGIBLE -> COMPLETED -> EPISODE CLOSED

VERIFYING -- failure --> POLICY_EVALUATION

POLICY_EVALUATION -- safe degradation --> DEGRADE_PENDING
DEGRADE_PENDING -> DEGRADED (terminal) -> EPISODE CLOSED

POLICY_EVALUATION -- unsafe/exhausted/ambiguous --> ESCALATE_PENDING
ESCALATE_PENDING -> ESCALATED (terminal) -> EPISODE CLOSED
```

No terminal state returns to the active recovery ladder. A later fault begins a new episode.

## 14. Quarantine and scheduling interaction

### During `RETRY`

The fault-associated event remains non-executable except for the explicitly authorized retry operation. Independent events may be dispatched if Gate A marks them eligible and the active retry does not invalidate their shared state.

### During `REINIT_OR_RESET`

The affected event remains quarantined. Any event whose correctness depends on the peripheral's state/configuration is blocked until the peripheral and required shared state are verified. Independent events may proceed only if the recovery operation does not temporarily invalidate resources they require.

### During `DEGRADE`

The affected event reaches a terminal degraded outcome. Dependent events are either retained blocked, reclassified, or completed through a declared degraded contract; there is no silent bypass.

### During `ESCALATE`

Local recovery stops. The scheduler does not treat escalation as successful release. Any remaining events are handled by their existing Gate A eligibility/dependency semantics and by whatever bounded escalation result the implementation later defines.

`pending_independent_work` is therefore a scheduler concern, not a policy input.

## 15. Coupled/transactional recovery

A coupled transaction cannot be recovered by retrying one member in isolation if doing so can produce a partial or inconsistent transaction.

For `COUPLED/TRANSACTIONAL` events:

1. the entire logical transaction remains contained according to its transaction contract;
2. a retry is permitted only when the transaction contract explicitly defines the retry as safe/idempotent or otherwise valid;
3. if safe retry cannot be established, the policy skips `RETRY` and moves to `REINIT_OR_RESET`, `DEGRADE`, or `ESCALATE` according to the decision table;
4. a member is not released merely because another member succeeded.

This preserves Gate A transaction semantics.

## 16. Release criteria

A quarantined event can become release-eligible only when all of the following hold:

1. the selected recovery action completed without an action-level failure;
2. the relevant peripheral/service verification succeeded;
3. the event/transaction verification succeeded where applicable;
4. Gate A dependencies and ordering conditions are satisfied;
5. shared state required by the event is valid;
6. no active recovery constraint still forbids execution;
7. the event's `EventRef` remains valid and has not been recycled.

Release is therefore a re-entry into Gate A eligibility evaluation, not an unconditional execution command.

## 17. Degraded-mode semantics

Gate C uses one common bounded abstraction with service-specific verification:

`ACTIVE -> DEGRADED -> TERMINAL`

The common abstraction means the recovery manager need not implement a separate resilience framework for every service. The service contract supplies the bounded degraded behavior.

Reference examples:

- a noncritical sensor service may stop issuing new sensor transactions and retain last-known-valid data with an explicit stale/degraded flag;
- a diagnostic-only service may suppress further peripheral operations while leaving unrelated housekeeping active;
- a critical service for which no safe degraded behavior exists cannot enter `DEGRADED` and must escalate.

These are semantic examples, not measured implementation behavior. The final service contracts must define exact validity and user-visible consequences before implementation.

## 18. Fixed-size policy output record

The normative output is conceptually:

```text
PolicyDecision {
    action;                 // RETRY, REINIT_OR_RESET, DEGRADE, ESCALATE, RELEASE/NO_ACTION
    target_scope;           // EVENT_TRANSACTION, SERVICE, PERIPHERAL, CONSERVATIVE_CONTAINMENT
    quarantine_required;
    retry_permitted;
    attempt_index;          // bounded 0..2 for retry attempts
    terminal;               // boolean
    release_permitted;      // only after verification + Gate A eligibility
    reason_code;             // bounded deterministic rule identifier
}
```

The exact C packing is deferred. The record is fixed-size and statically allocated. `reason_code` is deliberately an enum/identifier rather than free-form text.

The policy does not return queue contents or dynamic objects.

## 19. Zero-heap and resource implications

The policy requires only:

- one fixed active recovery-state record per simultaneously retained recovery episode, bounded by `XMAX`;
- bounded `EventRef`/transaction identifiers;
- fixed-size decision records;
- bounded dependency references already defined by Gate A;
- no dynamic allocation;
- no unbounded logs in the recovery path.

Worst-case policy-state memory is therefore a constant determined before implementation from the fixed record sizes and `XMAX`. Gate E will perform exact byte accounting and workload-capacity validation.

The policy's computational path is bounded by a fixed decision table and a fixed number of dependency/safety checks. No score normalization, search over an unbounded history, or machine-learning inference is used.

## 20. Policy ablation plan

Gate C freezes the following conceptual variants for later Gate E experimental design:

### P0 — Fixed retry baseline

A fixed retry count with no context-aware selection and no selective quarantine policy.

### P1 — Fixed retry + peripheral recovery

Fixed retry followed by the baseline peripheral reset/reinitialization behavior.

### P2 — Context-only policy

Uses current `fault_class`, association/safety context, criticality, and bounded attempt state, but no retained prior episode outcome beyond the current ladder state.

### P3 — Context + episode-history policy

Uses the full Gate C bounded episode state to distinguish repeated failure and choose the bounded recovery ladder.

### P4 — Integrated proposed mechanism

Gate C policy plus dependency-aware event quarantine and preservation scheduling.

The ablation is intentionally capable of falsifying the hypothesis. If P3/P4 does not improve relevant outcomes over simpler baselines without unacceptable overhead, the additional mechanism is not justified.

## 21. Rejected assumptions and alternatives

### Rejected: `pending_independent_work` as policy input
It is scheduler state and should not alter recovery action selection.

### Rejected: independent `last_action` + `last_outcome` fields
They duplicate explicit state-machine progression.

### Rejected: separate recurrence/persistence fault classes
Gate B established them as episode/history properties.

### Rejected: peripheral equality as fault scope
It violates evidence-bounded association.

### Rejected: unconditional peripheral-wide queue flush
It conflicts with service-preservation objective and Gate A semantics.

### Rejected: automatic retry of coupled transactions
It can violate transaction atomicity/consistency.

### Rejected: weighted numeric policy score
No evidence justifies arbitrary weights; it also makes formal reasoning and ablation less transparent.

### Rejected: automatic whole-system reset as a normal local action
It destroys the selective-service-preservation objective and should remain outside the local finite action set.

### Rejected: fixed `Rmax=3` without action semantics
It was not sufficiently precise to establish termination or comparable experimental cost.

### Rejected: claim that REINIT and RESET are always experimentally identical
They have distinct implementation scopes; the policy therefore combines them logically but leaves method-level distinction to later controlled implementation experiments.

## 22. Unresolved questions transferred to Gate D

1. Formalize the state invariants implied by quarantine, release, association, dependency safety, and bounded termination.
2. Prove/constructively check that no state path can exceed the four-action recovery budget.
3. Formalize the scheduler/recovery interaction, especially shared-state invalidation during `REINIT_OR_RESET`.
4. Define exact predicates for `retry_safe`, `degrade_safe`, and `shared_state_valid`.
5. Check whether the association-scope rules preserve the required monotonicity/conservatism properties.
6. Establish machine-checkable assertions for `EventRef` generation validity and quarantine non-execution.
7. Determine whether the common degraded abstraction is sufficient for all selected reference services without semantic leakage.
8. Evaluate whether the fixed decision table is complete with respect to every Gate B fault/association combination.

## 23. Gate C acceptance decision

**ACCEPTED — semantic/design level.**

Gate C is accepted because it now provides:

- a materially reduced policy input set;
- a bounded episode representation instead of redundant history fields;
- a finite, technically grounded action set;
- explicit U575-aware handling of reinitialization/reset as one logical policy action with method-level distinction deferred to controlled implementation testing;
- association-confidence-dependent containment;
- exact retry and transition semantics;
- deterministic scheduling/quarantine/dependency interaction;
- bounded degraded behavior;
- a fixed-size output contract;
- explicit ablation variants;
- a falsifiable design rather than an assumption that sophistication is beneficial.

No hardware performance, recovery-success, energy, or benchmark result is claimed by this gate.
