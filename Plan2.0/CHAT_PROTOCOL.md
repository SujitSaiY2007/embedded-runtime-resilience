# Multi-Chat Execution Protocol

## Live continuation note — 2026-10-22

Chat 05.2 is paused at ST-LINK/GDB initialization. Before asking the user to repeat any step, read Plan2.0/CURRENT_STATE.md and Plan2.0/handoffs/CHAT_05_2_HANDOFF.md; board-only USB detection, ST-LINK firmware upgrade, clean generated-project build, exact server command/error and empty netstat checks are already recorded. The next chat is Chat 05.3 and must continue from this exact point. The user does not have standalone STM32CubeProgrammer; do not request an installation or any purchase.

## Startup

At the start of each chat:
1. Read this file, `Plan2.0/CURRENT_STATE.md`, `Plan2.0/EXECUTION_ROADMAP.md`, and the latest handoff.
2. Inspect the live `main` head before writing.
3. Read exact source files and frozen evidence relevant to the task.
4. State task scope, files permitted to change, protected files, and acceptance criteria.

## Branch policy

**Only `main` may be used.** No feature branches, temporary branches, merges from other branches, or writes to another branch for this plan. Before every write, confirm the branch is `main` and expected head has not moved. If it moved, re-fetch and reconcile; never force-push.

## Protected assets

Unless a separate research-change decision is explicitly recorded, do not alter:
- `reference/src/ref_runtime.c`
- `reference/include/ref_runtime.h`
- Gate A–E contracts and frozen K.10 results.
- Existing experiment sources/configuration used for the frozen campaign.
- Historical chat records, decision logs, and prior-art reviews.

Do not delete old documents or citations. Archive copies are historical snapshots; original paths are retained during this initial transition.

## Required closeout

Each chat must record:
- Chat ID, date, objective, outcome, exact commit SHA and branch (`main)).
- Files added/changed and why.
- Commands/checks actually executed and results.
- Provenance: user-reported, tool-run, CI-run, or not run.
- Research/hardware claims newly supported and claims still unsupported.
- Open questions, blockers, risks, and next acceptance gate.
- One exact next-chat prompt.

Never write “passed” when a check was not run. Never state hardware was tested if only host simulation was run.
\n\n## Live continuation note — 2026-10-24 GPIO experiment\n\nNew user-supplied CubeIDE screenshots supersede the earlier Chat 05.3 debugger-blocked status: the local project built cleanly, firmware download verification succeeded, debugger execution reached the final loop, and eight expressions matched the expected successful GPIO recovery path. The narrow experiment changed PA5 from output mode to input mode, then restored output mode and set the output latch high. Read [the experiment report](results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md) and [current state](CURRENT_STATE.md). This does not establish physical peripheral-damage recovery, sensor operation, repeatability, or MCU resource measurements. Next is Chat 06 minimal-firmware source provenance/reproducibility; then Chat 07 baseline peripheral integration, then broader Chat 08 controlled fault/recovery. Work only on main and preserve all protected research evidence.\n

## Chat 06 source-preservation note — 2026-10-24

The user supplied `main.c`, `err_runtime.c`, and `err_runtime.h` from the local GPIO experiment and confirmed the separate external backup exists. A normalized plain-C transcription and provenance README now live at `Plan2.0/firmware/ld2_gpio_recovery/`. This source record is not the generated CubeIDE project; no startup/linker files or IDE metadata were copied. Continue by inspecting the local project configuration, preserving the working copy and backup, and documenting reproducibility. Do not claim an independent build or hardware test was run by GitHub tools.


## Live continuation note — 2026-10-25 BME280 chip-ID read

The latest sensor test has succeeded according to user-provided evidence: `sensor_found=1`, address `0x76`, chip ID `0x60`, `sensor_type=1`, `sensor_error=0`; the user's ST-LINK log says “Download verified successfully.” This supersedes earlier notes that sensor reads had not been demonstrated. Details and evidence limits are in `results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md`.

Next prompt: `prompts/CHAT_07_1_BME280_BASELINE_AND_RECOVERY_PROMPT_2026-10-25.md`. Review the actual local sensor source, preserve its provenance separately from the LD2 GPIO experiment, and design a safe software-controlled I²C recovery test requiring a fresh successful chip-ID read after recovery. No unsafe electrical faulting, no overwriting the external backup, no changes to protected research assets, and main only. Clearly distinguish user-supplied evidence from repository-side checks.
