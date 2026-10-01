# Current Handoff — K.4 Complete / K.5 Next

## Current checkpoint

Part II — K.4 — Novelty Re-Research + Conceptual Architecture Lock

Part I (K.1-K.3) is complete.

## Branch state

K.4 research is based on exp commit 1f3a471d2987b066ee995f4bf563fcdcbcd74d97.

main is e413a5986df9a486622bb4b34ef13ebc1e63ae80 and is one merge commit ahead because it contains the older integrated-software-phase material. That history is preserved; it is not treated as a newer exp state.

Focused K.4 work branch:
research/k4-novelty-architecture-2026-10-01

## K.4 result

### Novelty

The broad novelty framing has been rejected as insufficiently differentiated.

Prior art materially covers:
- peripheral recovery/isolation;
- recovery history;
- event failure queues/quarantine;
- dependency-aware containment;
- selective rollback/preservation;
- runtime fault disambiguation and trace verification;
- static/zero-dynamic-allocation embedded execution.

Remaining hypothesis:

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

Status: UNRESOLVED.

No novelty or patentability conclusion has been made.

Detailed record:
research/novelty_investigation.md

### Architecture

Locked conceptual chain:

UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI

Authority rules:
1. C reference runtime is the only recovery-policy authority.
2. UI cannot choose recovery actions.
3. Virtual system cannot choose recovery actions.
4. Trace records runtime decisions and does not infer policy.
5. Recovery Decision is a conceptual presentation stage, not a second algorithm/component.
6. Event identity and evidence precision must survive across layers.
7. Gates A-E semantics remain frozen.

Architecture record:
research/part_ii_conceptual_architecture.md

## Historical documentation note

research/chat_records/chat_k4_record.md and research/phase1_software_demonstrator_methodology_lock.md contain the earlier integrated-software interpretation of K.4. They are retained as historical provenance.

The active K.4 scope is governed by research/PART_II_CHAT_PLAN.md and the Part-II scope override.

## Exact K.5 starting point

K.5 must turn the locked conceptual architecture into implementable contracts for:
- virtual scheduler/environment;
- virtual I2C/SPI/UART models;
- deterministic fault injection;
- simulator-to-C-runtime adapter;
- UI-facing state/trace schema;
- baseline interface boundary.

K.5 must not implement the virtual system or UI and must not redesign the recovery policy.

## Non-goals

Do not modify Gates A-E, create a second recovery algorithm, integrate STM32U575 hardware, perform physical fault injection, run K.8 matched baseline experiments, perform K.9 methodology lock, or perform K.10 final conclusion.

## Persistent evidence limitations

- P0-P3 remain non-clean quarantine ablations.
- W09/W10 remain capacity-confounded.
- Host evidence remains host/reference evidence.
- No MCU/physical performance evidence is established.
- Novelty/patentability remain unresolved.
