# Chat K.4 Record — Novelty Re-Research + Conceptual Architecture Lock

Date: 2026-10-01
Active branch: research/k4-novelty-architecture-2026-10-01
Checkpoint: K.4
Part: Part II

## Continuity check

- Part I: K.1-K.3 COMPLETE.
- Part II: K.4 onward ACTIVE.
- Last completed checkpoint: K.3.
- Active checkpoint: K.4.
- exp: canonical active reference branch; starting commit 1f3a471d2987b066ee995f4bf563fcdcbcd74d97.
- main: one merge commit ahead of exp; that merge contains the older integrated-software-phase K.4 material and is not treated as the active Part-II research state.
- K.4 allowed: prior-art research, falsification, element matrix, conceptual architecture, interface/data-boundary definition, continuity documentation.
- K.4 prohibited: simulator/UI implementation, K.5 interface implementation, Gates A-E changes, recovery-policy redesign, hardware, K.8 experiments, K.9/K.10 work.

## 1. Prior-art re-research

The search was intentionally adversarial and covered peripheral recovery, isolation, recovery history, failed-event queues, quarantine, dependency-aware containment, selective rollback, constrained runtime verification, and zero-dynamic-allocation embedded execution.

Key findings:

1. Phoenix and US8510592B1 materially establish peripheral fault recovery, isolation, reinitialization and escalation.
2. US10921871B2 establishes recovery history affecting later recovery action.
3. US10331522/US10929373 and US20180365126 establish failed-event retention/quarantine, association with resources, retry and corrective action.
4. Dependency-aware containment is established in fault-tolerant service-robot work.
5. Selective rollback/preservation based on dependencies is established in distributed/dataflow recovery.
6. R2U2 and runtime-verification literature establish resource-constrained event observation, fault disambiguation and trace/verdict reasoning.
7. Zero-heap/static allocation is established engineering practice.
8. Recent 2026 patent activity demonstrates retaining queued events during recoverable errors and releasing them after recovery.

The detailed element-by-element matrix is in research/novelty_investigation.md.

## 2. Falsification result

The broad novelty framing is not defensible. Close prior art exists for nearly every individual ingredient and for several meaningful combinations.

The remaining hypothesis is narrower:

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

Status: UNRESOLVED.

No novelty or patentability claim is made.

## 3. Conceptual architecture lock

The Part-II chain is locked as:

UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI

Responsibilities:

- UI = presentation and scenario control only.
- Virtual embedded system = deterministic workload/peripheral/fault environment only.
- C runtime = sole recovery-policy authority.
- Recovery Decision = observable C-runtime result, not a second algorithm.
- Trace/Evidence = authoritative runtime-produced evidence.

The architecture is documented in research/part_ii_conceptual_architecture.md.

## 4. Authority constraints

- UI cannot choose recovery actions.
- Virtual system cannot choose recovery actions.
- Trace cannot infer policy.
- Event identity and evidence precision must survive across layers.
- Gates A-E remain frozen.

## 5. Documentation inconsistency

Historical files still contain the earlier integrated-software interpretation of K.4, including research/chat_records/chat_k4_record.md and research/phase1_software_demonstrator_methodology_lock.md.

These are preserved for provenance. They are superseded for active scope by research/PART_II_CHAT_PLAN.md and the current Part-II scope override. Current continuity documents explicitly identify this.

## 6. Branch finding

At K.4 entry:
- exp = 1f3a471d2987b066ee995f4bf563fcdcbcd74d97
- main = e413a5986df9a486622bb4b34ef13ebc1e63ae80

main is one merge commit ahead because of the earlier integrated-software-phase package. K.4 research is based on exp as required.

## 7. Exit condition

K.4 is complete when the novelty record, conceptual architecture, continuity state, and exact K.5 handoff are committed to exp through the focused-work branch.

No simulator/UI implementation is performed in K.4.

## 8. Next checkpoint

K.5 — Virtual Embedded System Technical Design + Interface Contracts.

K.5 must turn the locked conceptual boundaries into implementable contracts and must not implement the simulator/UI or redesign the recovery policy.
