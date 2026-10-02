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
| K.4 | Integrated software proof of concept + methodology lock | Professor-facing demonstrator, re-verification, methodology lock, final software-phase conclusion, then handoff to MCU validation |

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

**Phase:** Integrated software proof-of-concept and methodology-lock phase after K.3.  
**Completed:** Gates A-E; minimal reference implementation; K.1 host-experiment verification; K.2 host-corpus validation; K.3 evidence-bounded synthesis.  
**Current boundary:** host/reference + deterministic software injection + professor-facing software demonstrator. MCU/physical validation remains absent.  
**Status:** K.4 ACTIVE. Professor verification is part of this integrated phase, not a separate stage.

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


## K.4 — Integrated software proof of concept + methodology lock — 2026-10-01

K.4 is the current continuation boundary. The objective is to demonstrate the whole software mechanism, re-verify the methodology, lock the evidence boundaries, and produce a clear conclusion for proceeding to target-MCU validation.

The professor-facing activity is not a separate gate. It is the intended use of this checkpoint.

Authoritative record: `research/phase1_software_demonstrator_methodology_lock.md`.

Current limitations remain unchanged: P0-P3 are not clean quarantine ablations; W09/W10 are capacity-confounded; host evidence is not MCU/physical evidence; novelty/patentability are not established.


---

# Part-II Two-Branch / Multi-Chat Continuity Protocol

## Project partition
- Part I: K.1-K.3 — COMPLETE.
- Part II: K.4 onward — ACTIVE.
- K.3 is the explicit boundary between the two parts.

## Reference branch rule
exp is always the active reference branch. Every continuation recovers state from exp. Child branches must record their base exp commit. Completed checkpoint work returns to exp before becoming current project state.

## Main synchronization rule
main must be aware of every completed checkpoint declared integrated. The authoritative chain is exp checkpoint -> PR -> main. The PR records checkpoint, source exp commit, change summary, validation and limitations.

## Chat entry contract
Every new chat begins with a Continuity Check containing Part, checkpoint, exp reference, last completed checkpoint, allowed scope, explicit out-of-scope work and required end state.

## Chat exit contract
Every chat finishes with completed work, tests/evidence, unresolved issues, files changed, exact next checkpoint, exact branch state, whether exp was updated and whether main was synchronized. The next chat must not rely on conversation memory.


## 2026-10-01 — Part-II K.5 checkpoint

K.4 is complete and K.5 is complete at design/contract level. The current next checkpoint is K.6 — Virtual Embedded System Implementation.

K.5 established the implementation boundary around the existing C runtime and preserved Gates A-E. The next chat must read the K.5 technical design, interface contracts, deterministic scenarios and K.5 record before coding.

K.6 must not redesign the recovery policy or create a second policy authority. The current runtime has no peripheral-action callback; this is a documented adapter limitation and must not be silently solved by changing runtime semantics.

---

# Canonical Post-K.10 Continuity Protocol — 2026-10-02

The historical checkpoint tables and earlier current-checkpoint sections above are retained for provenance. They are superseded for active execution by this section and by research/PART_II_CHAT_PLAN.md.

## Active project partition
- Part I — K.1-K.3: COMPLETE.
- Part II — K.4-K.10: COMPLETE.
- Post-K.10 research closure: ACTIVE.
- Final software demonstration: follows research closure.

## Current canonical checkpoint
**K.10.1 — Adversarial Prior-Art & Technical-Distinction Review**

K.10 itself is complete. Its experimental result is frozen and must not be rerun or reinterpreted merely to obtain a preferred conclusion.

## Canonical sequence
**K.10.1 → K.10.2 → K.10.3 → K.10.4 → K.11 → K.12 → final exp audit → validated synchronization to main**

### K.10.1
Attack the remaining technical distinction. Build the P4 feature/limitation matrix, map strong prior art, perform adversarial searching, and identify genuine remaining distinctions.

### K.10.2
Perform deep single-reference anticipation analysis. Determine whether one reference actually discloses the complete relevant P4 combination.

### K.10.3
Perform multi-reference combination and technical-obviousness analysis. Identify the strongest technically supported combination attacks and their missing steps/interactions.

### K.10.4
Integrate K.10 evidence with K.10.1-K.10.3 and produce the final evidence-bounded technical-distinction/research conclusion.

### K.11
Produce the final software research synthesis and target-MCU validation handoff. Do not claim hardware validation unless it is actually performed.

### K.12
Finalize the software productization and clean professor-facing UI demonstration without changing the research mechanism to improve presentation.

## ChatGPT / Antigravity rule
**ChatGPT owns the chat-wise sequence.**

Antigravity is an execution agent inside the current ChatGPT-defined checkpoint only. It may execute repository work, tests, searches, experiments, and documentation updates explicitly authorized by that checkpoint.

Antigravity must not create or redefine the roadmap, renumber checkpoints, advance to the next checkpoint, or redesign P4 outside the active scope.

Every ChatGPT checkpoint must close with exact branch/SHA, completed work, evidence/tests, changed files, unresolved items, explicit non-goals, exact next checkpoint, and complete next-ChatGPT continuation prompt.

## Branch rule
- exp = active research/integration branch.
- main = stable integrated mirror.
- Historical child branches = provenance only; they are not active roadmap authorities.

Completed checkpoint work is developed and verified on exp. main is synchronized only after the checkpoint is reviewed and explicitly closed.

## Startup order for every new ChatGPT chat
1. Read PROJECT_MANUAL.md.
2. Read PROJECT_STATE.md.
3. Read CURRENT_HANDOFF.md.
4. Read DECISION_LOG.md.
5. Read research/PART_II_CHAT_PLAN.md.
6. Read NEXT_CHAT_PROMPT.md.
7. Read the active checkpoint's research artifacts.
8. State the continuity check.
9. Execute only the current checkpoint.

## Canonical source files
- Active roadmap: research/PART_II_CHAT_PLAN.md
- Current next-chat prompt: NEXT_CHAT_PROMPT.md
- Current state: PROJECT_STATE.md
- Exact handoff: CURRENT_HANDOFF.md
- Decisions: DECISION_LOG.md
- K.10 evidence: research/phase2_k10_p4_advantage_novelty_results.md
- Post-K.10 plan: research/phase2_post_k10_review_plan.md

No earlier roadmap section should override these active sources.