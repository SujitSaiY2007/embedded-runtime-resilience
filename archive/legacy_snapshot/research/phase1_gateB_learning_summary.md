# Phase 1E.1 — Gate B Learning Summary

**Purpose:** educational companion to the accepted Gate B semantic/design artifact. This file explains the gate in simple terms for project continuity and onboarding. It does not replace or weaken the normative contract in `research/phase1_gateB_fault_model_final.md`.

## 1. What Gate B accomplished

Gate A defined how events, dependencies, scheduling, and quarantine behave. Gate B defines how the system describes a failure before recovery policy decisions are made.

In simple terms:

> Gate B turns “something went wrong” into a bounded, evidence-aware fault context: what was observed, where it can defensibly be associated, how certain that association is, whether the observation is part of an ongoing episode, and what scope may need to be isolated or blocked.

The project therefore moves conceptually from:

`EVENT MODEL -> FAULT UNDERSTANDING -> RECOVERY POLICY`

Gate C will use the Gate B fault context and recovery history to decide what action to take.

## 2. Why this matters to the research question

The research is not merely asking whether an MCU can recover from an error. It asks whether recovery can reduce unnecessary disruption to unrelated valid work.

To do that safely, the recovery mechanism must distinguish:

- the event/transaction that is actually fault-associated;
- other events that are independent and may remain eligible;
- events that are not fault-associated but must still be blocked because they depend on invalid or quarantined state;
- cases where the available evidence is too weak for precise attribution.

This is why fault association is a first-class part of the design rather than an implementation detail.

## 3. Observation is not the same as physical cause

A controller/driver may observe a NACK, timeout, bus/protocol error, or arbitration loss. That observation is real evidence about the communication attempt.

It does not automatically prove a particular physical root cause.

For example:

`I2C transaction -> NACK`

supports:

`Observed fault = NACK`

but does not automatically support:

`Physical device is permanently defective`

The model therefore separates observable evidence from inference and unknown physical cause.

## 4. Fault association in plain language

The system asks: “How specifically can I connect this fault to queued work?”

The accepted association levels are:

1. `EXACT_EVENT_TRANSACTION` — evidence supports a particular event/transaction.
2. `SERVICE_ONLY` — the affected service/driver is known, but a particular transaction is not defensible.
3. `PERIPHERAL_ONLY` — the peripheral context is known, but event-level attribution is not defensible.
4. `UNKNOWN_AMBIGUOUS` — the available evidence is insufficient for a narrower attribution.

The governing idea is:

`association precision <= evidence precision`

Never claim more causal precision than the evidence supports.

## 5. Why same-peripheral does not mean same-event

Several queued events can use the same I2C peripheral.

Therefore:

`same peripheral != same fault-associated event`

A peripheral fault may justify broader blocking only when dependency, shared-state, or recovery-safety reasoning requires it. Fault association scope and dependency-blocking scope are separate concepts.

## 6. Fault classes and history

The primary I2C taxonomy is intentionally small and focuses on observable conditions:

- NACK/non-acknowledge;
- transfer timeout/no-progress;
- bus/protocol error;
- arbitration/bus-ownership error;
- persistent no-progress / suspected peripheral-state failure.

SPI uses a deliberately reduced secondary taxonomy because SPI has different device/protocol semantics and no universal NACK equivalent.

Recurrence and persistence are not treated as independent instantaneous fault classes. They describe what happens over time within a fault episode.

Conceptually:

`observation 1 -> observation 2 -> repeated failure -> persistent/recurring context`

The episode continues across qualifying repeated observations until verified success, degraded terminal handling, or escalation. A later failure after terminal handling starts a new episode.

## 7. Software fault injection

Software fault injection provides deterministic, repeatable experimental stimuli before physical fault injection is available.

Conceptually:

`normal transaction -> controlled injected fault -> fault observation -> recovery policy`

This makes matched experiments possible. However, software injection is not proof that the same physical fault mechanism exists on hardware. Physical fault mechanisms remain unvalidated until the real MCU/testbed is available and safely tested.

## 8. Bounded fault context

The fault record is fixed-size and statically allocated because the project has a zero-heap requirement.

It retains only bounded information needed by later recovery decisions and experimental metrics, such as:

- episode/observation identity;
- bounded timing information;
- resource/fault context;
- conditional event/transaction identity;
- association level;
- evidence flags;
- recurrence/recovery context;
- episode status.

The goal is not to build a large logging framework. The goal is to provide enough trustworthy context for the deterministic recovery policy.

## 9. Example

Suppose the queue contains:

`E1 Display -> E2 Sensor Read -> E3 Storage -> E4 LED`

If E2 produces an I2C NACK and the evidence identifies the transaction precisely:

`E2 -> NACK -> EXACT_EVENT_TRANSACTION`

then E2 can become the fault-associated event and may be quarantined.

E1, E3, and E4 are not automatically discarded. Their eligibility still depends on Gate A's dependency, ordering, shared-state, and recovery-safety rules.

If the system only knows that the I2C peripheral experienced an error but cannot identify which transaction is responsible, it must not invent an event-level attribution. It may record:

`PERIPHERAL_ONLY` or `UNKNOWN_AMBIGUOUS`

and let Gate C define the conservative recovery behavior for that uncertainty.

## 10. What Gate B did not decide

Gate B did not freeze the final recovery action policy.

It did not yet decide exactly when to:

- retry;
- reinitialize/reset a peripheral;
- enter degraded mode;
- escalate.

Those are Gate C decisions.

Gate B supplies the trustworthy fault context that Gate C needs to make those decisions deterministically.

## 11. Relationship between Gates A, B, and C

`Gate A: What work exists and what depends on what?`

`Gate B: What failed, what can we prove, and what work is defensibly associated with it?`

`Gate C: Given that context and recovery history, what bounded action should be taken?`

The final experimental chain is then:

`fault -> context/association -> policy -> quarantine/recovery -> service outcome -> measured evidence`

## 12. Important non-claims

- Gate B does not claim a novel fault taxonomy.
- Gate B does not claim that an observed controller error proves a physical root cause.
- Gate B does not claim that software injection validates hardware behavior.
- Gate B does not claim that event quarantine, context-aware recovery, or any individual ingredient is novel.
- Gate B does not claim physical validation or benchmark results.
- Gate B is accepted at the semantic/design level; implementation and physical validation remain later work.

## 13. One-line takeaway

> **Gate B is the project's fault-understanding layer: it tells the recovery mechanism what was observed, how confidently it can be associated with work, how the fault episode is evolving, and what scope may safely be considered affected—without pretending to know more than the evidence shows.**
