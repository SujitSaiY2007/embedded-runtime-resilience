# Execution Roadmap — Plan 2.0

Each numbered chat is a bounded work package. Read the current state, previous handoff, relevant original artifacts, and protected-boundary rules before proceeding.

| Chat | Work package | Required output | Exit condition |
|---|---|---|---|
| 00 | Initialize Plan 2.0 | State, protocols, roadmap, archive index, README navigation | Framework committed on `main`; no code/evidence changed |
| 01 | Reference inventory | Complete source inventory and per-entry status for preliminary ~43 references | Every entry has a stable ID and verification status |
| 02 | Metadata and venue verification | DOI/title/authors/year/venue/type checks; journal/conference/source classification | No fabricated or silently guessed metadata |
| 03 | Literature gap and influence mapping | Source-to-design traceability, related-work matrix, research-gap map | Each project claim linked to evidence or flagged unsupported |
| 04 | Bibliography/manuscript revision | IEEE-style reference list and revised related work | Citations resolve and claims are source-supported |
| 05 | Hardware compatibility audit | Board/component inventory, target discrepancy, zero-budget feasibility, risk register | Compatibility blockers documented; no unsafe wiring approved |\n| 05.2 | Zero-budget hardware bring-up | Identify only existing parts; verify board/cable/sensor; staged safe connection, build/flash and baseline tests where feasible | Every electrical gate passes before wiring/power; raw evidence and truthful handoff recorded |
| 06 | Minimal firmware scaffold | Reproducible build and serial trace, no recovery claims yet | Firmware builds/flashes and baseline trace captured |
| 07 | Baseline peripheral integration | Sensor/peripheral reads with raw logs | Stable baseline demonstrated and documented |
| 08 | Controlled fault and recovery | Safe fault injection, detection, recovery, post-recovery success | Recovery verified by a fresh successful operation |
| 09 | Measurement and repeatability | MCU timing/resource observations, raw traces, repetitions and limitations | Results reproducible and clearly separated from host results |
| 10 | Manuscript and demo integration | Hardware methods/results, figures, demo guide, limitations | All claims trace to artifacts |
| 11 | Final audit and release | Repository audit, clean README/state/handoff, evidence manifest | No unverified claims or unresolved critical gaps hidden |

## Rules for every chat

- Read `Plan2.0/CURRENT_STATE.md`, `Plan2.0/CHAT_PROTOCOL.md`, and the latest handoff first.
- Make the smallest scope-specific changes; use only `main`.
- Do not run or rewrite the frozen 400-execution campaign to repair a documentation inconsistency.
- Do not edit the protected reference runtime or frozen reports merely to make new hardware work.
- Before claiming a source is influential, classify the relationship as direct adoption, adaptation, conceptual context, comparator, or no demonstrated influence.
- Close with a handoff containing completed work, files changed, checks actually run, commit SHA, open questions, and the exact next task.
