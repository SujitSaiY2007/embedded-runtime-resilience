# Execution Roadmap — Plan 2.0

Each numbered chat is a bounded work package. Read the current state, previous handoff, relevant original artifacts, and protected-boundary rules before proceeding.

| Chat | Work package | Required output | Exit condition |
|---|---|---|---|
| 00 | Initialize Plan 2.0 | State, protocols, roadmap, archive index, README navigation | Framework committed on `main`; no code/evidence changed |
| 01 | Reference inventory | Complete source inventory and per-entry status for preliminary ~43 references | Every entry has a stable ID and verification status |
| 02 | Metadata and venue verification | DOI/title/authors/year/venue/type checks; journal/conference/source classification | No fabricated or silently guessed metadata |
| 03 | Literature gap and influence mapping | Source-to-design traceability, related-work matrix, research-gap map | Each project claim linked to evidence or flagged unsupported |
| 04 | Bibliography/manuscript revision | IEEE-style reference list and revised related work | Citations resolve and claims are source-supported |
| 05 | Hardware compatibility audit | Board/component inventory, target discrepancy, zero-budget feasibility, risk register | Compatibility blockers documented; no unsafe wiring approved |
| 05.2 | Zero-budget hardware bring-up — paused | Board-only USB detection and ST-LINK firmware update succeeded; generated Empty Project builds cleanly; GDB server/ST-LINK initialization fails. See current state and handoff. | Resume from recorded diagnostics; do not repeat completed checks; no sensor wiring until gates pass |
| 05.3 | ST-LINK debugger continuation — **debugger now working for local test** | Reconcile earlier GDB blocker with the new successful CubeIDE download/debug evidence; document the narrow GPIO experiment | Download verification and debugger execution evidenced; broader recovery claims remain bounded |
| 06 | Minimal firmware scaffold and provenance — **in progress** | Source files and provenance notes are preserved under `Plan2.0/firmware/ld2_gpio_recovery/`; inspect the local CubeIDE project configuration and establish a reproducible procedure without generated startup/linker churn | Source provenance explicit; reproducibility procedure documented and checked without overwriting the working project; build/download evidence kept distinct |
| 07 | Baseline peripheral integration | Sensor/peripheral reads with raw logs | Stable baseline demonstrated and documented |
| 08 | Controlled fault and recovery | Broader safe fault injection, detection, recovery, and a fresh post-recovery operation | Recovery verified by a fresh successful operation across documented cases; the Chat 05.3 PA5 test is only an initial narrow configuration-fault milestone |
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


**Chat 06 progress update (2026-10-24):** source files and provenance are preserved in `Plan2.0/firmware/ld2_gpio_recovery/`. User screenshots confirm the local CubeIDE Debug configuration, GNU Tools for STM32 14.3.rel1, GNU11, `STM32L476RGTX_FLASH.ld`, map-file generation, unused-section removal, and `--specs=nosys.specs`. The generated project tree includes startup/build artifacts, ELF/list/map outputs, debug launch configuration, and Flash/RAM linker scripts. No more configuration screenshots should be requested absent a concrete blocker. Chat 06 must now consolidate a safe reproduction procedure and evidence boundaries; do not copy generated artifacts or disturb the local project/backup.

## Chat 06 milestone update — 2026-10-24

The user confirmed that `Project → Build Project` works in the existing local CubeIDE project after the settings review. Source preservation, configuration recording, and local rebuild continuity are complete for this stage. A clean build from a repository checkout is still **not demonstrated**; do not label the GitHub source folder a standalone CubeIDE project. The user asked to stop further configuration inspection. Chat 07 may begin with sensor identity/electrical-compatibility research only; keep the module unwired until its identity, pinout, supply/logic levels, and pull-ups are verified.