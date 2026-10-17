# Phase 1 — Recovery Policy Design

**Date:** 2026-08-20  
**Phase:** Phase 1 — System Design and Experimental Planning  
**Status:** Proposed architecture; implementation not yet started.

## 1. Objective

Define the smallest deterministic recovery policy capable of testing the frozen hypothesis without turning the project into a general-purpose resilience framework.

The policy must:

- use no runtime heap allocation;
- consume bounded local fault context and short history;
- select from a finite action set;
- associate the fault with the smallest defensible event/transaction scope;
- quarantine the affected event when safe;
- preserve valid independent queued work;
- terminate within a declared transition bound;
- expose measurable CPU/RAM/Flash cost.

## 2. Policy principle

The policy should not attempt to predict arbitrary system behavior. It should make a deterministic bounded decision from a compact context record.

Conceptually:

`Action = Policy(FaultContext, RecoveryHistory, EventContext, ServiceCriticality)`

The policy must be inspectable and reproducible. An opaque learned model is out of scope for the reference mechanism.

## 3. Minimum context variables

The initial policy context is deliberately limited to variables that can plausibly change the appropriate recovery action:

1. `fault_class`
2. `fault_recurrence`
3. `attempt_count`
4. `last_action`
5. `last_outcome`
6. `service_criticality`
7. `event_dependency_status`
8. `pending_independent_work`

Optional diagnostic fields such as timestamps/cycle counts may be logged without becoming policy inputs.

The policy should be experimentally ablated later to determine which variables materially affect decisions.

## 4. Recovery action set

The original candidate set was:

1. Retry
2. Reinitialize
3. Peripheral reset
4. Controlled degradation/isolation
5. Escalation

For the minimum reference implementation, use the first four as local actions where technically supported and use escalation as the terminal policy outcome.

However, **reinitialize and peripheral reset must not be assumed to be meaningfully distinct for every peripheral**. If the selected MCU driver makes them equivalent, the experiment should represent them as one action rather than creating artificial distinctions.

Thus the effective action set is:

`RETRY`
`REINIT_OR_RESET`
`DEGRADE`
`ESCALATE`

A separate `PERIPHERAL_RESET` action may be retained only where it has experimentally distinct semantics from reinitialization.

## 5. Decision hierarchy

The first version should be a deterministic bounded rule table rather than a complex scoring engine.

### Class A — transient-looking failure

Conditions:

- first occurrence within history window;
- low recurrence;
- retry is safe;
- event can remain isolated.

Action:

`QUARANTINE -> RETRY`

### Class B — repeated failure

Conditions:

- repeated same fault class within bounded history;
- retry budget exhausted or repeated retry failure.

Action:

`QUARANTINE -> REINIT_OR_RESET`

### Class C — persistent failure affecting a noncritical service

Conditions:

- reset/reinitialization unsuccessful;
- service is safely degradable;
- independent work remains executable.

Action:

`QUARANTINE -> DEGRADE`

### Class D — critical or unsafe continuation

Conditions:

- critical dependency cannot be satisfied;
- fault association is ambiguous in a safety-relevant case;
- bounded local recovery is unsuccessful;
- continued execution would violate a defined safety/correctness rule.

Action:

`ESCALATE`

## 6. Why not use a weighted score initially?

A weighted score could make the mechanism appear more sophisticated, but unless weights are justified by evidence it would add arbitrary complexity.

A deterministic decision table is preferable for the first implementation because:

- it is explainable;
- it is easy to reproduce;
- it is easy to compare against baselines;
- it permits formal state-transition reasoning;
- it has low RAM/Flash overhead;
- it supports ablation experiments.

A score-based policy may be evaluated later only if experimental evidence shows that a rule table is inadequate.

## 7. Recovery state machine

Initial state machine:

```text
NORMAL
  |
  | fault detected
  v
FAULT_DETECTED
  |
  | associate event + classify
  v
CLASSIFIED
  |
  | isolate affected event
  v
QUARANTINED
  |
  | select bounded action
  v
RECOVERING
  |
  | verify service
  +-----------------------+
  | success               | failure
  v                       v
RELEASED              REASSESS
  |                       |
  v                       +----> RETRY (if budget permits)
NORMAL                    |
                          +----> REINIT_OR_RESET
                          |
                          +----> DEGRADE
                          |
                          +----> ESCALATE
```

`REASSESS` is a bounded decision point, not an unbounded recovery loop.

## 8. Recovery transition bound

Define a finite maximum number of local recovery transitions per fault episode:

`MAX_TRANSITIONS = Rmax`

The initial experimental configuration should use a small value such as 3, but the exact number is a tunable experimental parameter rather than a permanently frozen constant.

The termination property is:

Every fault episode reaches one of:

- `SUCCESS`
- `DEGRADED`
- `ESCALATED`

within `Rmax` policy transitions.

## 9. Quarantine interaction with recovery actions

### RETRY

The affected event remains quarantined while the retry is attempted.

Independent valid events may execute concurrently in the cooperative event loop only if their dependency/order rules permit it.

### REINIT_OR_RESET

The affected event remains quarantined during peripheral reinitialization/reset and verification.

Events dependent on the peripheral state must remain blocked if the reset invalidates their assumptions.

### DEGRADE

The affected event may transition to `DISCARDED` or remain permanently non-executable according to the service's declared degraded-mode semantics.

Independent services remain eligible.

### ESCALATE

The local policy stops attempting recovery and emits a bounded escalation event/control result.

The proposed mechanism does not prescribe a specific system-level escalation architecture.

## 10. Context/history storage

History is a fixed-size circular/static record set.

No dynamic allocation is permitted.

The minimum useful history should capture only recent recovery episodes relevant to the same service/peripheral/fault class.

A later experiment should compare history windows such as:

- no history;
- short history;
- larger bounded history.

This tests whether history actually contributes enough benefit to justify its memory cost.

## 11. Policy ablation

To establish whether context-awareness contributes measurable value, the experiment should include controlled policy variants:

### P0 — fixed retry baseline

No contextual policy.

### P1 — context without history

Uses current fault/event context only.

### P2 — context + short recovery history

Uses current context plus bounded recent recovery outcome.

### P3 — proposed integrated policy

Uses context/history plus dependency-aware event quarantine.

This is an important experimental design point: if P2 and P3 perform no better than the fixed baseline, the hypothesis is weakened rather than forced into acceptance.

## 12. Policy output

The policy should return a compact bounded decision record:

```text
Decision {
    action
    quarantine_required
    max_attempts
    terminal_condition
}
```

The final C representation must be statically allocated and fixed-size.

## 13. Success criteria

A recovery attempt is successful only if the relevant service verification condition passes.

A successful peripheral reset/reinitialization alone is insufficient if the associated event still fails its transaction/service verification.

For the experiment, record separately:

- recovery action completed;
- peripheral state restored;
- fault-associated event completed;
- unrelated events preserved;
- system-level escalation avoided.

## 14. Design rationale

The policy intentionally avoids:

- machine learning;
- large rule engines;
- dynamic recovery objects;
- arbitrary weighted scoring;
- global queue flushing;
- automatic whole-system restart;
- heavyweight RTOS dependencies.

These would enlarge the mechanism without directly strengthening the frozen research question.

## 15. Remaining decisions before implementation

1. Exact fault-class taxonomy for the selected peripheral.
2. Exact numerical retry budget and transition bound.
3. Exact history window size.
4. Exact dependency representation and worst-case storage.
5. Exact degraded-mode semantics for each test service.
6. Exact verification criteria for I2C/SPI transactions.
7. Whether peripheral reset and driver reinitialization are experimentally distinct on the U575 implementation.
8. MPU configuration and whether it is included in the primary or secondary experimental condition.

These remain open deliberately until the experimental protocol is defined.
