# Next Chat Prompt — K.5: Virtual Embedded System Technical Design + Interface Contracts

Continue SujitSaiY2007/embedded-runtime-resilience from completed K.4.

## Mandatory startup

Read, in order:
1. PROJECT_MANUAL.md
2. PROJECT_STATE.md
3. CURRENT_HANDOFF.md
4. DECISION_LOG.md
5. CHAT_CONTINUITY_PROTOCOL.md
6. NEXT_CHAT_PROMPT.md
7. research/PART_II_CHAT_PLAN.md
8. research/novelty_investigation.md
9. research/part_ii_conceptual_architecture.md
10. research/chat_records/chat_k4_record.md
11. relevant Gate A-E/reference design records

Then report a Continuity Check before substantive work.

## Partition

- Part I — K.1-K.3: COMPLETE.
- Part II — K.4 onward: ACTIVE.
- K.4: COMPLETE.
- Current checkpoint: K.5 — Virtual Embedded System Technical Design + Interface Contracts.

## K.4 facts that K.5 must preserve

The broad novelty framing was rejected as insufficiently differentiated.

Remaining hypothesis:

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

This is unresolved. Do not call it novel or patentable.

Locked architecture:

UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI

The C reference runtime is the only recovery-policy authority.

## K.5 ALLOWED

1. Define implementable contracts for the virtual embedded system.
2. Define the virtual scheduler/environment model.
3. Define virtual I2C/SPI/UART boundaries.
4. Define deterministic fault-injection API and stimulus representation.
5. Define simulator-to-C-runtime adapter contract.
6. Define runtime input/output schemas needed for integration.
7. Define UI-facing state/trace schema.
8. Define baseline interface boundary for later K.8 comparison.
9. Define deterministic scenario contracts and terminal cases.
10. Define data ownership, identity and resource boundaries.
11. Identify implementation dependencies that must be deferred.

## K.5 MUST NOT

Do NOT:
- implement the virtual embedded system;
- implement the virtual circuit;
- implement the UI;
- modify Gates A-E;
- modify the recovery policy;
- create a second recovery algorithm;
- perform K.6 implementation;
- perform K.7 UI implementation;
- perform K.8 baseline experiments;
- perform K.9 methodology lock;
- perform K.10 final conclusion;
- integrate STM32U575 hardware;
- perform physical validation.

If a later-stage dependency is discovered, document it and hand it forward; do not execute it.

## Required K.5 outputs

Create/update:
1. technical design document for the virtual embedded system;
2. interface/contract document;
3. deterministic scenario definitions;
4. research/chat_records/chat_k5_record.md;
5. PROJECT_STATE.md;
6. CURRENT_HANDOFF.md;
7. DECISION_LOG.md if consequential decisions are made;
8. NEXT_CHAT_PROMPT.md for K.6.

## Exit condition

K.5 is complete only when interfaces are explicit enough for K.6 implementation, data ownership is unambiguous, runtime authority is preserved, deterministic fault injection is specified, trace/state boundaries are explicit, baseline integration boundary is explicit, and K.6 has an unambiguous starting point.

Do not begin K.6.
