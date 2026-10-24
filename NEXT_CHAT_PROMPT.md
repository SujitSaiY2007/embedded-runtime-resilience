# Next Chat Prompt — Chat 06 Minimal-Firmware Scaffold and Provenance

Continue the same Plan 2.0 hardware work from the successful Chat 05.3 debugger milestone. Do not restart board setup or repeat completed diagnostics.

## Read first
- `Plan2.0/CURRENT_STATE.md`
- `Plan2.0/CHAT_PROTOCOL.md`
- `Plan2.0/EXECUTION_ROADMAP.md`
- `CURRENT_HANDOFF.md`
- `Plan2.0/results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md`
- `Plan2.0/handoffs/CHAT_05_3_HANDOFF.md`

## Verified user evidence as of 2026-10-24
- Target: ST NUCLEO-L476RG / STM32L476RG (prior target discrepancy with NUCLEO-U575ZI-Q remains unresolved).
- Local STM32CubeIDE 2.2.0 project `Embedded-Runtime-Resilience` built with 0 errors and 0 warnings.
- CubeIDE console reported “Download verified successfully.”
- Live debugger execution reached the final loop after the GPIO experiment.
- Expressions values: `test_event_count=1`, `test_fault_count=1`, `test_recovery_count=1`, `test_state=4`, `test_recovered=1`, `test_fault_injected=1`, `test_gpio_mode=1`, `test_gpio_output=1`.
- The experiment injects a software configuration fault by switching PA5 (LD2) from output to input; recovery restores output mode, sets PA5 high, and checks the GPIO mode/output latch.
- This is a narrow software-injected GPIO configuration test, not physical peripheral-failure recovery. No sensor is wired/read; no MCU performance measurements or repeated-run study exist.

## Chat 06 objective
Make the minimal firmware experiment reproducible and traceable. First inspect the local project/source provenance and current canonical repository structure. Preserve the external backup of the verified pre-experiment `main.c`. Determine a safe, reviewable way to keep the experiment source in version control without copying generated startup/linker files or replacing the protected C reference runtime. Document exact build, download and debugger steps and the evidence limits.

## Hard constraints
- Work only on `main`; inspect live HEAD and fetch current file blob SHAs before writes.
- Do not create/switch branches or force-push.
- Do not alter `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen K.10 evidence, prior-art analyses, or historical records.
- Do not claim the local generated CubeIDE project is already canonical repository firmware.
- Do not wire the BME280-labelled module until its exact marking, pinout, supply/logic levels, and pull-ups are verified and a wiring plan is reviewed.
- No purchases or installs. Keep sensor and external wiring disconnected until the compatibility gate passes.
- Do not repeat CLI target-identification, firmware update, old port checks, or the earlier manual GDB-server test unless a new hypothesis requires it.

## Acceptance gate
A version-controlled, reproducible minimal-firmware record with exact source provenance, build/download/debug instructions, explicit user-evidence provenance, and no unsupported physical-recovery claims. Then hand off to Chat 07 for safe peripheral compatibility/baseline planning. Chat 08 remains the broader controlled-fault/recovery package; this GPIO experiment is only an initial milestone.
