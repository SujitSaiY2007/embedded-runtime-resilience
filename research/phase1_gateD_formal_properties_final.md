# Phase 1E.1 — Gate D Final Formal Properties and Proof/Check Strategy

**Gate:** D — Formal Properties + Proof/Check Strategy  
**Phase:** 1E.1 — Experimental Design / Formalization Foundation  
**Status:** **ACCEPTED at the semantic/design-model level**; implementation, Gate E experimental protocol, and physical validation remain deferred.  
**Date:** 2026-09-03

## 1. Purpose and acceptance boundary

Gate D turns the accepted Gate A, Gate B, and Gate C semantic contracts into explicit safety, termination, boundedness, identity, release, dependency, and decision-table properties.

The goal is not to claim full formal verification of future firmware. The goal is to establish a finite, inspectable reference model whose important correctness obligations can be stated as predicates, reasoned about, exhaustively checked where practical, and later represented by runtime assertions in the reference prototype.

Gate D therefore distinguishes:

- properties that follow from the frozen finite semantics and can be proved by invariant reasoning;
- properties that can be exhaustively checked over a bounded host model;
- properties that can be checked by deterministic trace/property tests;
- properties that remain dependent on implementation or physical MCU/hardware behavior and therefore require later experimental validation.

No Gate A–C semantic rule is silently redesigned in this document.

## 2. Normative inputs

Gate D treats these artifacts as normative inputs:

1. `research/phase1_gateA_event_model_final.md`
2. `research/phase1_gateB_fault_model_final.md`
3. `research/phase1_gateC_recovery_policy_final.md`

The retained earlier documents remain historical/baseline material:

- `research/phase1_event_model.md`
- `research/phase1_peripheral_testbed_fault_model.md`
- `research/phase1_recovery_policy_design.md`

The frozen platform direction remains STM32U575ZI / NUCLEO-U575ZI-Q, with I2C primary, SPI secondary, and UART/USART diagnostic/control. Hardware availability is not assumed.

## 3. Formal vocabulary

Let:

- `E` be an event record;
- `Ei`, `Ej` be event instances;
- `R = {slot_id, generation}` be an `EventRef`;
- `T` be a bounded transaction identity where applicable;
- `Q` be the normal bounded queue;
- `X` be bounded quarantine/recovery retention;
- `D(E)` be the bounded explicit dependency relation for event `E`;
- `S` be the scheduler/recovery state;
- `F` be a fault observation/context;
- `A` be a logical recovery action;
- `P` be the deterministic policy decision.

The reference model uses provisional host capacities:

`QMAX = 16`  
`XMAX = 4`  
`DMAX = 4`

These values remain provisional workload parameters and must be validated by Gate E. Gate D uses them only to establish a finite design envelope.

### 3.1 Event representation

`Represented(E)` means the event remains present in one of the bounded representations permitted by the implementation strategy.

`Active(E)` means the event is nonterminal and still participates in scheduling/recovery semantics.

`Terminal(E)` means the event has reached `COMPLETED`, `DISCARDED`, `ESCALATED`, or another explicitly declared terminal state.

### 3.2 Valid EventRef

For an event reference `R=(s,g)`:

```text
ValidRef(R) :=
    0 <= s < ACTIVE_SLOT_LIMIT
    AND slot[s] is active
    AND slot[s].generation == g
    AND NOT Terminal(slot[s])
```

For the basic queue/quarantine model:

`ACTIVE_SLOT_LIMIT <= QMAX + XMAX`

The exact physical storage arrangement is an implementation choice, but the semantic identity rule is fixed.

### 3.3 Dispatchability

The Gate A eligibility rule is normalized as:

```text
Dispatchable(Ej) :=
    Represented(Ej)
    AND State(Ej) == ELIGIBLE
    AND AssociationAllowsExecution(Ej)
    AND AllOrderedDependenciesSatisfied(Ej)
    AND AllCoupledContractsSatisfied(Ej)
    AND SharedStateValid(Ej)
    AND ActiveRecoveryConstraintsAllow(Ej)
```

A queue scan that checks only `State != QUARANTINED` is therefore insufficient.

## 4. Property classification

Gate D uses four property classes.

| Class | Meaning | Typical checking method |
|---|---|---|
| Safety | Something forbidden never occurs | invariant reasoning, exhaustive state exploration, assertions |
| Termination / liveness | A bounded episode reaches a terminal outcome | transition reasoning, exhaustive bounded traces |
| Boundedness | State/resource usage never exceeds a declared finite bound | arithmetic invariant, exhaustive capacity checks |
| Observational correctness | Recorded outcome matches the modeled event/state transition | deterministic trace/property tests |

A host-model result is evidence about the model, not proof about arbitrary future firmware or hardware.

## 5. Six core invariants

### I1 — Quarantine safety

**Statement**

```text
State(E) == QUARANTINED
    => Exec(E) is forbidden
```

Execution is permitted only after an explicit permitted transition such as authorized retry execution or release/reclassification.

**Required stronger form**

```text
Exec(E, t) =>
    NOT Quarantined(E, t)
    OR AuthorizedRecoveryExecution(E, t)
```

An authorized retry is not ordinary dispatch; it is a specifically permitted recovery operation.

**Proof/check idea**

- Enumerate all lifecycle transitions.
- Mark `QUARANTINED` as non-dispatchable.
- Permit only explicitly enumerated recovery transitions.
- Assert that the scheduler's ordinary dispatch predicate cannot return true for a quarantined event.

**Counterexample**

A quarantined event is selected by the normal dispatcher and executes before release/retry authorization.

**Later runtime assertion**

`assert(!(event.state == QUARANTINED && normal_dispatch_selected(event)));`

**Classification:** safety; host-exhaustible; later runtime-checkable.

### I2 — Fault-association conservatism

**Statement**

The policy may not assign an association scope more precise than the evidence supports.

```text
AssociationPrecision(assigned) <= AssociationPrecision(evidence)
```

Operationally:

- exact event/transaction target requires valid active `EventRef`, transaction context where applicable, and direct attributable evidence;
- service-only evidence cannot manufacture an event target;
- peripheral-only evidence cannot manufacture an event target;
- ambiguous evidence cannot manufacture a service/event target.

**Proof/check idea**

Construct an evidence-to-association matrix from Gate B and assert that every policy result is within the maximum permitted scope.

**Counterexample**

A NACK observed on I2C0 while several candidate events exist is assigned to one event solely because that event uses I2C0.

**Later runtime assertion**

`assert(target_scope <= evidence_scope);`

where the implementation uses a documented finite ordering of association precision.

**Classification:** safety; finite-table exhaustive check; later runtime-checkable.

### I3 — Service preservation / correct blocking

For a fault-associated event `Ei`, define:

`U(Ei) = {Ej | Ej is valid, not fault-associated, and independent of Ei under Gate A semantics}`.

An event in `U(Ei)` is preserved only when it:

1. executes;
2. passes service/transaction verification;
3. violates no dependency/order rule;
4. bypasses no invalid shared state;
5. is not later invalidated by the same episode.

The required classification is:

```text
PRESERVED
CORRECTLY_BLOCKED
INCORRECTLY_BLOCKED_OR_LOST
```

**Property**

A valid independent event must not be blocked solely because another event is quarantined, provided no active recovery action invalidates its state/resources.

Conversely, a dependent event must not be labeled a preservation failure when blocking is required by an explicit dependency or shared-state condition.

**Counterexamples**

- Global queue flush deletes independent valid work.
- A dependent event executes despite an invalid predecessor.
- A non-fault-associated event is retained but never executes even though all eligibility predicates remain true.

**Classification:** safety plus observational correctness; finite trace/exhaustive scheduler slice; later runtime/property test.

### I4 — Dependency safety

For each dependency `d in D(Ej)`:

```text
ORDERED:
    Exec(Ej) => AcceptableCondition(ReferencedEvent(d))

COUPLED:
    Exec(Ej) => CoupledContractAllows(Ej, current_transaction_state)
```

Therefore:

```text
NOT FaultAssociated(Ej)
    does NOT imply
Dispatchable(Ej)
```

**Proof/check idea**

Enumerate dependency states for a bounded event set and reject any trace in which an ordered or coupled event executes before its required condition.

**Counterexample**

`E1` is quarantined and `E2` is ordered after `E1`; a scheduler scan executes `E2` merely because `E2` itself is not quarantined.

**Classification:** safety; exhaustive bounded dependency-state check; runtime assertion.

### I5 — Recovery termination

Every nonterminal fault episode reaches success, degraded, or escalated terminal handling within the frozen four-action recovery budget.

```text
T1 = RETRY #1
T2 = RETRY #2
T3 = REINIT_OR_RESET
T4 = terminal DEGRADE or ESCALATE
```

Therefore:

`MAX_RECOVERY_ACTIONS = 4`

An action plus its verification counts as one attempt. Lifecycle transitions and unrelated scheduler dispatches do not consume action budget.

**Proof/check idea**

The longest possible unsuccessful local path is:

```text
FAULT
 -> RETRY #1 [fail]
 -> RETRY #2 [fail]
 -> REINIT_OR_RESET [fail]
 -> DEGRADE/ESCALATE [terminal]
```

There is no transition from a terminal state back into the active recovery ladder.

**Counterexample**

After `T4`, policy evaluation re-enters `RETRY_PENDING`, creating an unbounded retry loop.

**Classification:** bounded liveness/termination; directly provable from the frozen state-machine transition structure, subject to implementation conformance.

### I6 — Bounded resource usage

The model never requires runtime heap growth and all retained event/dependency/recovery state remains within declared static bounds.

For the initial bounded envelope:

```text
|normal queue| <= QMAX
|quarantine retention| <= XMAX
incoming dependencies per event <= DMAX
ActiveEventCount <= QMAX + XMAX
```

Dependency storage has the bound:

`DependencyStorage <= ActiveEventSlots * DMAX * sizeof(DependencyEntry)`

where `ActiveEventSlots <= QMAX + XMAX` for the bounded event domain.

**Important qualification**

If an implementation permits multiple simultaneous service/peripheral recovery episodes that are not represented by quarantined event slots, it must introduce an explicit fixed `EPMAX` recovery-context bound before implementation. Gate D does not silently assume an unbounded episode store.

For the host proof model, a single active policy episode is used as a proof decomposition. This is not a new normative system restriction; it is a tractable slice. A multi-episode implementation must prove its own declared `EPMAX` bound.

**Classification:** boundedness; arithmetic/invariant proof plus capacity exhaustion tests; later memory/heap instrumentation.

## 6. EventRef generation validity

### 6.1 Generation validity rule

`EventRef={slot_id,generation}` is valid only when the slot is active and its current generation equals the reference generation.

A slot reuse operation must change the generation before the new event becomes an active target.

Therefore, for an old reference `R_old=(s,g_old)` and a reused slot with `g_new != g_old`:

`R_old != CurrentRef(s)`

and `R_old` must not identify the new event.

### 6.2 Generation wrap

Generation values may wrap only when the implementation can establish that no outstanding reference can still refer to the older generation. If that condition cannot be established, the implementation must not permit the wrap to create ambiguous identity.

Gate D therefore treats generation-wrap safety as an assumption requiring a concrete implementation policy later. A finite host model may use a small generation domain, but wrap must be explicitly modeled and checked rather than ignored.

### 6.3 Required identity invariants

```text
ValidRef(R) => slot[R.slot_id].generation == R.generation

StaleRef(R) => NOT ValidRef(R)

Terminal event => NOT Dispatchable(event)

Reused slot with changed generation => old Ref cannot target new event
```

### 6.4 Counterexamples

- fault record arrives with an old `EventRef` after slot reuse and recovery targets the new event;
- a generation wraps while an old reference remains outstanding;
- a terminal event remains dispatchable through a stale reference.

### 6.5 Checking strategy

Exhaustively enumerate:

- finite slot IDs;
- finite generation values;
- allocation/release/reuse transitions;
- outstanding-reference sets;
- terminal/nonterminal states.

The key property is an ABA-style identity check: the same slot number alone must never make two live generations indistinguishable.

## 7. Release safety

Release is not unconditional execution. It is a transition back to Gate A eligibility evaluation.

Define:

```text
ReleaseAllowed(E) :=
    State(E) == QUARANTINED
    AND ValidRef(EventRef(E))
    AND ActionVerificationSucceeded(E)
    AND RelevantPeripheralOrServiceVerified(E)
    AND EventOrTransactionVerificationSatisfied(E)
    AND AllOrderedDependenciesSatisfied(E)
    AND AllCoupledContractsSatisfied(E)
    AND SharedStateValid(E)
    AND NOT ActiveRecoveryProhibition(E)
```

If exact event/transaction association is required for release, the active episode's target reference must still match the current event generation.

A successful peripheral reset/reinitialization alone is insufficient.

### Release safety theorem

If `ReleaseAllowed(E)` is false, the quarantined event cannot transition to executable dispatch solely through the release path.

### Counterexamples

- peripheral reports healthy but the event's transaction verification still fails;
- the event's generation changed while it was quarantined;
- an ordered predecessor remains invalid;
- recovery still prohibits execution of the affected resource;
- release directly invokes execution without returning through eligibility evaluation.

**Classification:** safety; predicate/invariant proof; exhaustive trace check; runtime assertion.

## 8. Coupled-transaction containment

Coupled/transactional events require stronger containment than ordinary ordering.

Let `T` be a transaction and `Members(T)` its bounded event members.

Define:

```text
CoupledExecAllowed(Ej,T) :=
    CoupledContractAllows(Ej,T.state)
    AND all required transaction invariants hold
```

A member of a coupled transaction may not be retried independently unless the transaction contract explicitly declares member-level retry safe.

If one member is quarantined or the transaction state is invalid:

- all members whose correctness depends on that invalid transaction state remain blocked;
- no member may execute merely because it is not itself fault-associated;
- recovery should operate at the transaction/peripheral/service scope permitted by Gate C.

### Required property

```text
Coupled member invalid/quarantined
    AND member-level retry not contractually safe
=> no member-by-member retry
```

### Counterexample

A write member fails, is quarantined, and the recovery manager retries the verification member independently, creating a partial transaction.

**Classification:** safety; finite transaction-state exploration; runtime assertion/property test.

## 9. Fault association and target-scope formalization

Gate B defines four association levels:

1. `EXACT_EVENT_TRANSACTION`
2. `SERVICE_ONLY`
3. `PERIPHERAL_ONLY`
4. `UNKNOWN_AMBIGUOUS`

Use the following target rule:

| Association | Defensible direct target | Forbidden inference |
|---|---|---|
| EXACT_EVENT_TRANSACTION | specific event/transaction with valid generation | widening to unrelated events without dependency/recovery justification |
| SERVICE_ONLY | service scope | inventing a specific event target |
| PERIPHERAL_ONLY | peripheral scope | inventing a specific event or transaction target |
| UNKNOWN_AMBIGUOUS | conservative containment/escalation only | inventing service/peripheral/event precision |

Fault association scope is separate from dependency-blocking scope. A peripheral-only fault may block several dependent events without claiming that all those events caused the fault.

### Association monotonicity check

If evidence becomes less precise, policy target precision must not become more precise.

A useful finite ordering is:

```text
EXACT_EVENT_TRANSACTION > SERVICE_ONLY > PERIPHERAL_ONLY > UNKNOWN_AMBIGUOUS
```

The implementation must document the corresponding numeric encoding if used; the semantic ordering is what matters.

## 10. Preservation and correct-blocking predicates

For non-fault-associated `Ej`:

```text
Preservable(Ej,Ei) :=
    Valid(Ej)
    AND NOT FaultAssociated(Ej)
    AND Independent(Ej,Ei)
    AND SharedStateValid(Ej)
    AND OrderingSatisfied(Ej)
    AND RecoveryAllows(Ej)
```

```text
Preserved(Ej) :=
    Preservable(Ej,Ei)
    AND Executed(Ej)
    AND VerificationSucceeded(Ej)
    AND NOT LaterInvalidatedByEpisode(Ej)
```

```text
CorrectlyBlocked(Ej) :=
    NOT Executed(Ej)
    AND NOT Preservable(Ej,Ei)
    AND BlockingReasonIsExplicit
```

The final clause is important: an implementation should record why an event was blocked so that safety blocking is distinguishable from accidental loss.

```text
IncorrectlyBlockedOrLost(Ej) :=
    Valid(Ej)
    AND NOT Executed(Ej)
    AND Preservable(Ej,Ei)
```

This gives Gate E a correctness basis for measuring preservation without rewarding over-blocking.

## 11. Recovery termination proof/check

### 11.1 Rank function

Define the remaining recovery-action budget for a nonterminal episode:

`B = 4 - actions_started`

with:

`0 <= actions_started <= 4`

Each nonterminal recovery action decreases `B` by one. Terminal handling at `T4` ends the episode.

Thus no infinite sequence of recovery actions is possible under the normative state machine.

### 11.2 Worst-case path

```text
T1 RETRY #1       -> failure
T2 RETRY #2       -> failure
T3 REINIT_OR_RESET -> failure
T4 DEGRADE/ESCALATE -> terminal
```

Number of recovery-action invocations = 4.

Any successful verification terminates earlier through release/episode closure.

### 11.3 Hidden retry hazard

The policy-level proof is invalidated if a lower-level driver silently performs additional retries under one policy action. Therefore the reference implementation must expose or disable hidden recovery retries when measuring policy attempt counts.

This is an implementation conformance requirement, not a new policy action.

## 12. Deterministic decision-table completeness and consistency

Gate C defines the ordered rule table:

1. no active episode -> `NO_ACTION` / normal scheduling;
2. ambiguous with no safe local containment -> `ESCALATE`;
3. successful current action -> `RELEASE` if Gate A eligibility is restored;
4. continued local execution prohibited -> `DEGRADE` if immediately safe, otherwise `ESCALATE`;
5. attempt bound exhausted -> `DEGRADE` if safe, otherwise `ESCALATE`;
6. retry-safe and retry budget remains -> `RETRY`;
7. retry unavailable/failed and local peripheral recovery permitted -> `REINIT_OR_RESET`;
8. peripheral recovery failed and safe degraded mode exists -> `DEGRADE`;
9. otherwise -> `ESCALATE`.

### 12.1 Completeness

For any active encoded policy context, one of the rules above must produce an outcome. Rule 9 is the total fallback, so the table is total even when no recovery action is permitted.

### 12.2 Consistency

Rules are evaluated in the declared order. Earlier safety/terminal conditions dominate later convenience conditions.

Examples:

- a successful action does not fall through to another recovery action;
- an exhausted budget cannot select another retry;
- unsafe continuation cannot be rescued by queue occupancy or criticality;
- `pending_independent_work` does not modify policy action;
- association ambiguity cannot create an exact event target.

### 12.3 Association/fault cross-product audit

Gate B contributes 11 bounded fault classes for the abstract policy audit:

- 5 primary I2C classes;
- 4 reduced SPI classes;
- 1 software/service class;
- 1 ambiguous class.

Combined with:

- 4 association levels;
- 3 criticality classes;
- 4 active attempt-count values (`0..3`);
- 8 possible three-bit recovery-safety masks (retry/reinit/degrade);
- 2 success values;
- 2 local-prohibition values;
- 2 ambiguous-containment-safety values.

This gives an abstract decision-context space of:

`11 * 4 * 3 * 4 * 8 * 2 * 2 * 2 = 33,792`

contexts before filtering semantically impossible combinations.

A host-side deterministic audit of this abstract space was performed for Gate D. Every one of the 33,792 encoded contexts produced exactly one policy outcome from:

`RELEASE`, `RETRY`, `REINIT_OR_RESET`, `DEGRADE`, or `ESCALATE`.

The audit therefore establishes **table totality for the encoded abstraction**. It does not establish firmware correctness or physical behavior.

### 12.4 Important limitation of the cross-product audit

The audit deliberately treats safety/precondition bits as abstract inputs. Gate E/implementation must define how concrete fault classes and association evidence populate those bits. Therefore the audit proves that the decision function is total and deterministic over the modeled inputs; it does not prove that the chosen precondition classifier is correct on hardware.

## 13. Finite-state host model

A practical host model should avoid enumerating every possible concrete MCU data structure at once. Instead use layered state-space decomposition.

### Layer A — policy decision model

State variables:

- fault class: 11;
- association: 4;
- criticality: 3;
- attempt count: 0–3 for active nonterminal action selection;
- episode state: finite set;
- safety precondition mask: 3 bits;
- action-verification result;
- local-containment status.

This layer is small enough for complete cross-product checking.

### Layer B — event identity/dependency model

Bound:

- event slots <= `QMAX + XMAX = 20`;
- dependency entries/event <= `DMAX = 4`;
- finite generation domain selected by the checker;
- finite dependency classes;
- finite event lifecycle states.

Use symmetry reduction where event labels have no semantic distinction, while preserving at least one fault-associated event and representative independent, ordered, and coupled events.

### Layer C — scheduler/recovery interaction

Explore bounded traces containing:

- admission;
- quarantine;
- independent dispatch;
- dependency blocking;
- retry;
- verification success/failure;
- peripheral recovery;
- release eligibility;
- degrade/escalate terminal handling.

This layer directly checks preservation and correct blocking.

### Layer D — capacity boundaries

Explicitly test:

- queue empty;
- queue partially occupied;
- queue at `QMAX`;
- quarantine at zero and `XMAX`;
- dependency count at zero and `DMAX`;
- stale `EventRef` after slot reuse;
- terminal event references;
- attempted admission when capacity is exhausted.

The host model should never allocate beyond the declared bounds.

## 14. State-space assumptions

The following assumptions are required for a finite host model:

1. Event types are the closed Gate A set.
2. Criticality has three values.
3. Dependency kinds are the closed Gate A set.
4. Queue/quarantine capacities are finite.
5. Dependency entries per event are bounded by `DMAX`.
6. Fault classes use the bounded Gate B taxonomy.
7. Association uses the four Gate B levels.
8. Recovery action set is the four Gate C logical actions.
9. Recovery action count is bounded by four.
10. Episode state is finite.
11. Event generation values are finite in the checker model.
12. Service/peripheral identifiers used by the checker are finite.
13. The host model's scheduler rule is deterministic.
14. A recovery action has a finite verification result (`success`/`failure` for the abstract model).
15. Hardware timing and electrical behavior are abstracted away from the semantic proof model.

Assumptions 10–15 are model assumptions, not physical claims.

## 15. Recommended exhaustive-check properties

The future host checker should assert at least:

### P-D01 — no quarantined ordinary dispatch

For every reachable state:

`State(E)=QUARANTINED => NormalDispatch(E)=false`

### P-D02 — valid EventRef only

Every recovery target reference must satisfy `ValidRef` at the instant it is consumed.

### P-D03 — stale references fail closed

A stale generation must result in no target/recovery action against the recycled event.

### P-D04 — association cannot gain precision

No policy output may identify a target scope more precise than the evidence scope.

### P-D05 — ordered dependency cannot be bypassed

No execution of `Ej` occurs while any required ordered predecessor condition is unsatisfied.

### P-D06 — coupled member isolation

No member-level retry occurs when the coupled transaction contract forbids it.

### P-D07 — independent-event preservation

A valid independent event remains eligible unless an explicit dependency/shared-state/recovery constraint blocks it.

### P-D08 — blocking reason is explicit

Every non-execution of a represented nonterminal event is attributable to a declared blocking/quarantine reason.

### P-D09 — release re-enters eligibility

Release never directly implies execution; it returns the event to Gate A eligibility evaluation.

### P-D10 — action count bound

No trace contains more than four recovery-action invocations in one episode.

### P-D11 — terminal closure

After `DEGRADED` or `ESCALATED`, no further local recovery action occurs in that episode.

### P-D12 — fixed resource bounds

No reachable host state exceeds queue, quarantine, dependency, or declared recovery-context capacity.

### P-D13 — decision totality

Every active policy context yields exactly one decision outcome.

### P-D14 — decision determinism

Identical policy input/state yields identical decision output.

## 16. Deterministic trace tests

Some properties are easier to demonstrate through short canonical traces than through full-state exploration.

### Trace T-D01 — exact fault with independent follower

```text
E1 independent
E2 fault-associated exact transaction
E3 independent

fault(E2)
-> quarantine(E2)
-> E1 executes
-> E3 executes if eligible
-> recovery(E2)
-> verify
-> release candidate
-> Gate A eligibility
```

Expected: E1/E3 preserved when no other constraint blocks them; E2 never executes normally while quarantined.

### Trace T-D02 — ordered follower

```text
E1 fault-associated
E2 ORDERED-after-E1

quarantine(E1)
-> E2 blocked
-> recover E1
-> verify predecessor condition
-> E2 becomes eligible only after Gate A re-evaluation
```

Expected: correct blocking, not preservation failure.

### Trace T-D03 — coupled transaction

```text
T1 = {E1,E2}
E1 fails
coupled retry not safe
```

Expected: no member-by-member retry; transaction remains contained until the declared contract permits a valid transition.

### Trace T-D04 — stale generation

```text
slot 3 generation 7 -> Eold
Eold terminal
slot 3 reused -> generation 8 -> Enew
late fault reference = {3,7}
```

Expected: late reference cannot target Enew.

### Trace T-D05 — full quarantine capacity

```text
X occupancy = XMAX
new quarantine request
```

Expected: deterministic overflow/containment behavior; no hidden allocation and no silent deletion of a retained event.

### Trace T-D06 — worst-case recovery

```text
retry #1 fails
retry #2 fails
reinit/reset fails
degrade or escalate
```

Expected: exactly four recovery-action invocations at most, with terminal closure after T4.

## 17. Runtime assertions for the reference prototype

Later implementation should expose a compact assertion layer. Candidate assertions include:

```text
ASSERT(queue_count <= QMAX)
ASSERT(quarantine_count <= XMAX)
ASSERT(dependency_count(event) <= DMAX)
ASSERT(active_event_count <= QMAX + XMAX)
ASSERT(no_runtime_heap_growth)

ASSERT(valid_ref(ref) before consuming ref)
ASSERT(!ordinary_dispatch(quarantined_event))
ASSERT(association_precision <= evidence_precision)
ASSERT(ordered_dependencies_satisfied(event) before dispatch)
ASSERT(coupled_contract_satisfied(event) before dispatch)
ASSERT(shared_state_valid(event) before dispatch)
ASSERT(action_count(episode) <= 4)
ASSERT(terminal_episode_has_no_next_recovery_action)
ASSERT(release_implies_eligibility_recheck)
```

These are design targets, not yet compiled firmware assertions.

## 18. Properties that can be proven/checkable now vs. properties requiring experiments

| Property/claim | Gate D status | Why |
|---|---|---|
| Quarantined ordinary dispatch is forbidden by the semantic model | **Provable/checkable** | Explicit lifecycle/dispatch predicate. |
| Association cannot exceed evidence precision | **Provable/checkable** | Finite association ordering and evidence matrix. |
| Ordered/coupled dependency bypass is forbidden | **Provable/checkable** | Explicit dependency predicates. |
| Four-action recovery bound | **Provable/checkable** | Finite ranked recovery ladder. |
| Terminal recovery cannot re-enter local ladder | **Provable/checkable** | State-machine structure. |
| Queue/quarantine/dependency bounds | **Provable/checkable conditionally** | Requires implementation to honor declared static capacities. |
| EventRef stale-generation rejection | **Provable/checkable conditionally** | Requires concrete generation update/wrap implementation. |
| Release safety | **Provable/checkable conditionally** | Requires implementation of all stated verification/eligibility gates. |
| Independent-event preservation | **Model-checkable** | Depends on modeled scheduler/dependency/shared-state semantics. |
| Exact CPU/RAM/Flash overhead | **Experimental** | Depends on compiler, build, implementation, and MCU execution. |
| Recovery latency | **Experimental** | Depends on actual implementation/timing. |
| Recovery success rate | **Experimental** | Depends on injected/physical fault behavior. |
| Physical fault mechanism validity | **Experimental** | Requires hardware/testbed evidence. |
| MPU containment behavior | **Experimental** | Requires actual MCU configuration and execution. |
| Energy impact | **Experimental** | Requires physical measurement if claimed. |
| Generalization to arbitrary MCU/hardware behavior | **Not established by Gate D** | Host model is not a universal firmware/hardware proof. |

## 19. Proof/check workflow

The practical verification workflow is:

### Step 1 — Semantic invariant audit

Review each Gate A–C rule against the Gate D predicates. Any mismatch must be recorded as an amendment rather than silently edited.

### Step 2 — Pure policy-table checker

Enumerate the finite abstract decision context and assert exactly one outcome for each context.

Gate D performed this abstract totality audit over 33,792 contexts.

### Step 3 — EventRef checker

Exhaustively explore bounded slot allocation, generation change, terminal transition, reuse, and stale-reference consumption.

### Step 4 — Dependency/scheduler checker

Explore representative independent, ordered, and coupled event sets and bounded queue states.

### Step 5 — Recovery-transition checker

Explore all action-success/failure combinations and verify the four-action bound and terminal closure.

### Step 6 — Capacity checker

Exercise empty, partial, full, and quarantine-capacity-boundary conditions.

### Step 7 — Runtime assertion mapping

Map each property to one or more implementation assertions without changing the semantic rule.

### Step 8 — Experimental handoff

Only after Gate D acceptance should Gate E define workloads, baselines, fault schedules, logging, repetitions, and statistical treatment.

## 20. What Gate D does not prove

Gate D does **not** prove:

- that the future C implementation is bug-free;
- that the STM32U575 hardware will behave exactly like the host model;
- that every I2C fault class can be physically injected safely;
- that a software-injected timeout reproduces a physical timeout mechanism;
- that the policy improves performance or recovery success;
- that the mechanism is novel;
- that the mechanism is patentable;
- that MPU configuration will improve measured outcomes;
- that the provisional capacities are optimal.

A host-state proof establishes properties of the modeled semantics and implementation conformance, not arbitrary real-world behavior.

## 21. Gate D acceptance decision

### Accepted

Gate D is **accepted at the semantic/design-model level** because:

1. all six core invariants have explicit predicates and counterexamples;
2. quarantine safety, association conservatism, preservation/correct blocking, dependency safety, recovery termination, and bounded resource usage have defined checking strategies;
3. `EventRef` generation validity and stale-reference behavior are formalized;
4. release safety is explicit and returns through Gate A eligibility;
5. coupled-transaction containment is explicit;
6. the four-action bound has a finite rank argument;
7. the deterministic policy table is total over the encoded abstract context space;
8. a practical finite-state host-checking decomposition is defined;
9. runtime assertions are mapped for later implementation;
10. proven/model-checkable properties are distinguished from experimental hardware/implementation claims.

### Qualification

Acceptance is deliberately limited to the design/model level. The formalization does not replace implementation testing, compiler/build verification, MCU execution, physical fault validation, or Gate E experimental protocol.

## 22. Next gate

The next gate is:

**Gate E — Baselines + Experimental Protocol**

Gate E must freeze, before large-scale implementation:

- baseline definitions and exact comparability;
- workload matrix and event/dependency scenarios;
- software fault schedule;
- capacities and final host-model values where required;
- metrics and correctness outcomes;
- logging schema and trace identifiers;
- repetitions/randomization or deterministic schedule policy;
- statistical/reproducibility treatment;
- acceptance criteria and reporting format.

No firmware implementation is started by Gate D.

## 23. Research-honesty boundary

The following remain explicitly unclaimed:

- physical board acquisition;
- physical measurements;
- benchmark results;
- energy results;
- hardware fault-injection results;
- implementation performance;
- novelty;
- patentability.

The Gate D host-side abstract audit is a model-level result only.
