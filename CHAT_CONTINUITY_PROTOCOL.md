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
| K | Final synthesis | Report, paper/patent assessment, demonstrations, and final repository organization |

## Early-stop rule

Do not wait for the entire listed scope if a chat becomes unusually long. Stop at the nearest coherent sub-boundary after checkpointing the repository.

A new chat must first read the repository's continuity documents before performing substantive work.

## Next-chat startup order

1. Read `PROJECT_MANUAL.md`.
2. Read `PROJECT_STATE.md`.
3. Read `CURRENT_HANDOFF.md`.
4. Read `DECISION_LOG.md`.
5. Read the relevant `research/` design files for the active gate.
6. State a concise continuity check: current phase, completed gate, next gate, and explicit non-goals.
7. Continue from the checkpoint; do not restart earlier decisions without evidence requiring reconsideration.

## Current checkpoint

**Phase:** 1E.1 — Experimental Design / Formalization Foundation  
**Completed:** six core invariants established.  
**Next:** Gate A — exact Event Model and dependency semantics.  
**Implementation status:** large-scale firmware implementation has not started and must remain deferred until the design gates are sufficiently complete.
