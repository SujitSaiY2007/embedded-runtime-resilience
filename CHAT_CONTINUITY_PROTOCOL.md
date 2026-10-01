# Chat Continuity and Project Checkpoint Protocol

This file defines how the project is handed from one ChatGPT chat to the next.

## Principle

GitHub is the durable project source of truth. Chat history is useful working context, but it must not be the only place where project decisions, progress, open questions, or next steps exist.

## Required checkpoint before opening a new chat

Update and commit, as applicable:

1. `PROJECT_STATE.md` — current phase, frozen decisions, completed work, open gates.
2. `CURRENT_HANDOFF.md` — exact next task and instructions for the next chat.
3. `DECISION_LOG.md` — new accepted/rejected decisions.
4. Relevant `research/` documents — technical design or experimental artifacts completed in the chat.

Never delete historical material merely to shorten the repository. Prefer additive updates and explicit supersession notes.

## Recommended chat boundaries

| Chat | Scope | Stop condition |
|---|---|---|
| A | Gate A — Event Model + dependency semantics | Gate A is reviewed, internally consistent, and checkpointed |
| B | Gate B — Fault model + association | Fault taxonomy/injection/association semantics are frozen and checkpointed |
| C | Gate C — Recovery policy | Context/history variables, action set, state machine, and bounds are frozen |
| D | Gate D — Formal reasoning | Invariants/properties and practical verification strategy are defined |
| E | Gate E — Experiment design | Baselines, workload matrix, injection schedule, metrics, logging, and repetitions are fixed |
| F | Minimal reference implementation | Small prototype builds/tests at host level and is checkpointed |
| G | Physical testbed bring-up | Board/peripherals/toolchain are verified and first safe hardware execution is recorded |
| H | Baseline experiments | Baseline measurements are complete and raw artifacts/checksums/logging are preserved |
| I | Proposed-policy experiments | Proposed mechanism measurements and correctness observations are complete |
| J | Analysis | Statistical/technical analysis, limitations, and interpretation are checkpointed |
| K.1 | Host experiment verification | Harness builds/runs reproducibly, matched P0-P4 execution is verified, and checkpoint is committed |
| K.2 | Host corpus validation | Generated traces/outcomes are inspected against Gate-E evidence requirements and remaining host-only limitations are recorded |
| K.3 | Final synthesis | Evidence-bounded synthesis and final repository organization |

## Early-stop rule

Do not wait for the entire listed scope if a chat becomes unusually long. Stop at the nearest coherent sub-boundary after checkpointing the repository.

A new chat must first read the repository's continuity documents before performing substantive work.

## Next-chat startup order

1. Read `PROJECT_MANUAL.md`.
2. Read `PROJECT_STATE.md`.
3. Read `CURRENT_HANDOFF.md`.
4. Read `DECISION_LOG.md`.
5. Read the relevant `research/` design files for the active gate.
6. If available, read the corresponding educational companion for conceptual continuity; for Gate B this is `research/phase1_gateB_learning_summary.md`.
7. State a concise continuity check: current phase, completed gates, next gate, and explicit non-goals.
8. Continue from the checkpoint; do not restart earlier decisions without evidence requiring reconsideration.

## Current checkpoint

**Phase:** 1E.1 — Experimental Design / Formalization Foundation; K.3 final host/reference synthesis checkpoint.  
**Completed:** Gates A-E; minimal reference implementation; K.1 host-experiment verification; K.2 host-corpus validation; K.3 evidence-bounded synthesis.  
**Current boundary:** host/reference + deterministic software injection only. MCU/physical validation remains absent.  
**Status:** K.3 COMPLETE. Any future work must explicitly select a deferred validation objective.

## Gate C checkpoint note

`research/phase1_gateC_recovery_policy_final.md` is the authoritative Gate C artifact. Gate C freezes the minimum policy context, bounded episode representation, logical action set, association-aware behavior, exact four-action recovery budget, scheduling/quarantine/dependency interaction, degraded-mode abstraction, fixed-size policy output, and P0–P4 ablation plan. `research/phase1_recovery_policy_design.md` remains retained as the earlier non-frozen design baseline.

## Gate B checkpoint note

`research/phase1_gateB_fault_model_final.md` is the authoritative Gate B artifact. `research/phase1_gateB_learning_summary.md` is an additive educational companion that explains the same gate in simpler terms and does not replace the normative artifact. The earlier `research/phase1_peripheral_testbed_fault_model.md` remains retained as historical/baseline material.

## Chat K.1/K.2/K.3 checkpoint

**Chat K.1 — completed 2026-10-01**

- Audited the reference implementation against Gates A-E.
- Recorded the concrete P0-P3 quarantine-ablation gap.
- Built the smallest declarative matched P0-P4 host experiment harness.
- Verified Windows/MSVC execution.
- CTest: 2/2 passed.
- Host harness checks: all PASS.
- 70 matched runs generated during verification.
- Commit: `949bd4c`.

**Chat K.2 — completed 2026-10-01**

- Regenerated and inspected the 70-run W01-W14 × P0-P4 corpus.
- Confirmed manifest PASS fields for replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- Inspected representative run/trace slices for recovery, action/outcome, correctness, and metadata coherence.
- Found no concrete corpus-generation, serialization, or runtime defect.
- Preserved the P0-P3 exact-event-quarantine limitation and host-only evidence boundary.

**Chat K.3 — next**

- Finalize evidence-bounded synthesis and repository organization.
- Separate demonstrated host/reference facts from MCU/physical evidence gaps.
- Preserve the W09/W10 capacity-confound qualification and P0-P3 ablation limitation.
- Do not introduce new design semantics merely to make the final package look complete.

The earlier K.1/K.2 pending text in this document is historical and superseded by the completed checkpoints above.
