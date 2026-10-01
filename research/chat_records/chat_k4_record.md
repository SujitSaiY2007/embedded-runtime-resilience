# Chat K.4 Record — Integrated Software Proof of Concept and Methodology Lock

**Date:** 2026-10-01

## Objective

Continue from K.3 and change the immediate goal to a single integrated software phase: construct the professor-facing software demonstrator; re-verify the existing software methodology; lock the research process and evidence boundaries; present the novelty hypothesis accurately; and conclude the software phase before target-MCU validation.

Professor verification is part of this phase and is not a separate stage.

## Repository changes

- Added demo/index.html.
- Added research/phase1_software_demonstrator_methodology_lock.md.
- Updated README.md, PROJECT_MANUAL.md, PROJECT_STATE.md, CURRENT_HANDOFF.md, CHAT_CONTINUITY_PROTOCOL.md, NEXT_CHAT_PROMPT.md, PROJECT_REFERENCE_GUIDE.md, DECISION_LOG.md, research/README.md, research/phase1_final_evidence_synthesis.md, reference/README.md, and reference/experiments/README.md.

No Gates A-E semantics were changed.

## Demonstrator boundary

The UI is a presentation layer for the frozen research mechanism. The ISO C11 reference runtime and host corpus remain authoritative. The UI is not a second specification and does not establish MCU or physical evidence.

## Locked limitations

- P0-P3 remain non-clean quarantine ablations.
- W09/W10 remain capacity-confounded.
- Host evidence remains distinct from MCU/physical evidence.
- Host layout observations remain distinct from STM32U575 resource measurements.
- Novelty and patentability remain unestablished.

## Software-phase conclusion

The mechanism is sufficiently specified, implemented, reproducible, demonstrable, and evidence-bounded to justify target-MCU validation.

This is not a claim that hardware performance, statistical superiority, final novelty, or patentability has already been proven.

## File hygiene assessment

No clearly useless file was identified. Earlier design/reference documents are retained because they provide research history and provenance. PROJECT_REFERENCE_GUIDE.md contains older planning language but is explicitly marked as superseded by the current continuity documents rather than deleted.

## Next boundary

Complete the final clean re-verification of the repository/software demonstrator, then merge the integrated software-phase package to main. After that, the next empirical objective is STM32U575 target validation.

---
## Part-II Scope Reclassification

The project has now been formally divided into:
- Part I = K.1-K.3, COMPLETE.
- Part II = K.4 onward, ACTIVE.

The previous K.4 document described an integrated software-phase objective. Under the new project structure, that material is retained as historical context, while the active K.4 checkpoint is strictly narrowed to **Novelty Re-Research + Conceptual Architecture Lock**.

### Active branch contract

- exp is the active reference branch.
- main is the integrated stable mirror.
- Part-II work must originate from exp.
- Completed checkpoints return to exp and are then synchronized to main through an explicit PR/merge.

### Active K.4 scope

Allowed:
- focused prior-art research;
- claim-element and combination analysis;
- novelty hypothesis refinement;
- conceptual virtual-system/UI/runtime architecture;
- interface ownership and evidence-boundary decisions.

Out of scope:
- simulator implementation;
- UI implementation;
- recovery-policy redesign;
- Gates A-E redesign;
- hardware work;
- K.5-K.10 execution.

### Required next checkpoint

K.5 — Virtual Embedded System Technical Design + Interface Contracts.
