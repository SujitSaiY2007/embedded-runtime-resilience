# Phase 1 — Formal Event Model

**Date:** 2026-08-20  
**Phase:** Phase 1 — System Design and Experimental Planning  
**Status:** Design baseline; implementation intentionally deferred.

## 1. Design objective

Define the smallest event representation that can support the frozen research question:

> Can a zero-heap, context-aware recovery policy quarantine a fault-associated event while preserving unrelated valid queued work, subject to dependency and ordering constraints?

The model must be finite, statically representable, deterministic, and small enough for a resource-constrained MCU.

## 2. Event identity

Each event has a bounded unique `event_id` within the active queue/history domain.

An event may also carry a bounded `transaction_id` when a peripheral transaction must be distinguished from the logical service event.

Identity must not depend on heap-allocated objects or globally unbounded identifiers.

## 3. Conceptual event record

The reference event record is defined conceptually as:

```text
Event {
    event_id
    event_type
    producer_id
    consumer_id
    service_id
    peripheral_id
    transaction_id
    criticality
    dependency_class
    ordering_class
    state
    fault_assoc
    retry_count
}
```

This is a **semantic model**, not a final C struct. Field packing and representation must be optimized after the semantics are validated.

## 4. Event types

Initial event types should remain small and closed:

1. `PERIPHERAL_READ`
2. `PERIPHERAL_WRITE`
3. `SERVICE`
4. `HOUSEKEEPING`
5. `RECOVERY_CONTROL`

Additional event types require evidence that they are necessary for the experiment.

## 5. Producer and consumer

`producer_id` identifies the bounded source of the event.

`consumer_id`/`service_id` identifies the bounded service responsible for execution.

This distinction allows the experiment to determine whether a fault in one service has implications for another queued event.

## 6. Peripheral association

An event may reference a bounded `peripheral_id`:

- `NONE`
- `I2C0`
- `SPI0`
- `UART0`/equivalent diagnostic interface

Peripheral association alone is **not** treated as a dependency relation. Two events using the same peripheral may still have different transaction semantics.

## 7. Criticality

Use a small finite criticality class rather than arbitrary numeric priorities:

- `CRITICAL`
- `NORMAL`
- `DEFERABLE`

Criticality influences preservation and escalation decisions but does not override safety/dependency constraints.

A critical event must not be executed merely because it is critical if its required dependency is invalid or its execution would violate the defined recovery semantics.

## 8. Dependency semantics

Dependencies are represented as a bounded relation between event classes/IDs.

For two events Ei and Ej:

`Ei -> Ej` means Ej requires a defined condition established by Ei before Ej may execute.

The implementation must avoid an unbounded dependency graph. The preferred initial representation is a small fixed dependency mask or bounded dependency reference set.

Three semantic cases are required:

### Independent

Ej can execute without Ei completing.

### Ordered

Ej may execute only after Ei completes or reaches a defined acceptable terminal state.

### Coupled/transactional

Ej is part of the same logical transaction or depends on shared state whose validity is affected by Ei. Ej must not bypass Ei merely because Ei is quarantined.

## 9. Ordering semantics

Ordering is not globally FIFO in every case.

Define two levels:

### Queue ordering

Events enter the bounded queue in insertion order.

### Execution ordering constraint

For events that explicitly require ordering:

`Ei ≺ Ej => Exec(Ei) ≺ Exec(Ej)`

unless Ei is quarantined and the defined recovery semantics explicitly allow Ej to be reclassified/released.

Independent events may bypass a quarantined event.

## 10. Event state machine

Initial bounded states:

```text
QUEUED
  ↓
ELIGIBLE
  ↓
EXECUTING
  ├── COMPLETED
  ├── FAILED
  └── QUARANTINED
          ├── RETRY_PENDING
          ├── RELEASED
          ├── DISCARDED
          └── ESCALATED
```

State transitions must be explicit. No implicit deletion from the queue is permitted.

## 11. Fault association

An event becomes fault-associated when a fault record links the observed failure to its event/transaction identity and service/peripheral context.

The initial association hierarchy is:

1. exact transaction/event identity;
2. service identity;
3. peripheral identity;
4. unknown/ambiguous.

The policy must not silently convert an ambiguous association into a precise one. Ambiguity should trigger conservative behavior according to the recovery policy.

## 12. Quarantine semantics

`QUARANTINED` means:

> The event is retained in bounded recovery storage or an explicitly marked queue location but is not executable until a permitted transition occurs.

A quarantined event must therefore remain observable to the recovery manager.

Quarantine transitions:

```text
FAILED
  ↓
QUARANTINED
  ├── RETRY_PENDING → EXECUTING
  ├── RELEASED → ELIGIBLE
  ├── DISCARDED → terminal
  └── ESCALATED → system-level handling
```

Quarantine is not equivalent to deletion and is not equivalent to flushing the queue.

## 13. Unrelated-event preservation

For a fault associated with Ei, an event Ej may remain executable only if:

1. Ej is not the fault-associated event;
2. Ej has no unsatisfied dependency on Ei;
3. Ej does not share invalid state whose correctness depends on Ei;
4. required ordering constraints are satisfied;
5. executing Ej does not violate the active recovery action's safety constraints.

This definition prevents an overly broad claim that all unrelated queue entries are always safe.

## 14. Queue model

Let Q be a bounded event queue with capacity Qmax.

Invariant:

`0 <= |Q| <= Qmax`

Quarantined events must not cause silent queue overflow.

Initial design preference:

- fixed event queue;
- fixed quarantine/recovery slots;
- no dynamic expansion;
- explicit overflow policy.

The overflow policy will be selected after the worst-case quarantine occupancy is derived.

## 15. Full-queue behavior

The system must define what happens if the queue is full while one or more events are quarantined.

Candidate policies:

1. reserve a fixed quarantine capacity;
2. reserve a fixed critical-event capacity;
3. reject/defer new noncritical events;
4. escalate if a safety-critical event cannot be represented.

The final policy must be deterministic and bounded.

## 16. Event preservation metric

For an experiment with a set U of events that are valid and independent of the fault-associated event:

`PreservationRate = |U_exec_correctly| / |U|`

An event counts as preserved only if it executes correctly without violating dependency, ordering, or transaction semantics.

This prevents a misleading metric where merely leaving an event in the queue is treated as successful preservation.

## 17. Quarantine correctness metric

For all events marked quarantined:

`QuarantineViolation = count(events executed while quarantined without permitted release)`

Target:

`QuarantineViolation = 0`

Any non-zero value is a correctness failure, not merely a performance degradation.

## 18. Initial worked example

Given:

`E1 -> E2 -> E3 -> E4 -> E5`

and a fault associated with E3:

- E1 executes normally.
- E2 executes normally.
- E3 enters `QUARANTINED`.
- E4 may execute only if independent of E3 and all ordering constraints permit it.
- E5 follows the same rule.
- E3 remains represented until retry/release/discard/escalation.

If E4 depends on E3, E4 is not preserved merely because it is not itself fault-associated.

## 19. Design decision

The project will use **dependency-aware event quarantine**, not unconditional queue filtering and not peripheral-wide queue flushing.

This is an architectural requirement for the proposed mechanism, not a claim that dependency-aware quarantine is novel by itself.

## 20. Next derivation

This event model now constrains the next design gate:

1. derive the minimum fault-context record;
2. determine which history variables materially change recovery choice;
3. derive the minimum bounded recovery-action set;
4. define the recovery state machine;
5. derive queue/recovery invariants;
6. define baseline semantics against the same event model.
