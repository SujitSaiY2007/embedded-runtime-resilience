# Chat 08 — Integrate the Actual Recovery Runtime with Physical Hardware

**Date:** 2026-10-25  
**Repository:** https://github.com/SujitSaiY2007/embedded-runtime-resilience  
**Branch policy:** `main` only  
**Goal:** Move from isolated peripheral tests toward a truthful, repeatable demonstration in which the project's actual recovery-runtime decision/action path controls a physical BME280 transaction on the NUCLEO-L476RG.

## Start here — do not rediscover prior work

Fetch live `main` HEAD and read:
1. `README.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `Plan2.0/CURRENT_STATE.md`
5. `Plan2.0/CHAT_PROTOCOL.md`
6. `Plan2.0/EXECUTION_ROADMAP.md`
7. `Plan2.0/results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md`
8. `Plan2.0/firmware/ld2_gpio_recovery/README.md`
9. `Plan2.0/results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md`
10. `Plan2.0/results/CHAT_07_1_BME280_CONTROLLED_NACK_RECOVERY_2026-10-25.md`
11. `Plan2.0/firmware/bme280_i2c_recovery/README.md` and its source, if present.

Check the actual repository paths and live content; do not assume a path exists because this prompt mentions it. Confirm current commit SHA before any write.

## Hardware baseline already completed — do not repeat

Board: ST NUCLEO-L476RG revision MB1136 C, STM32L476RG. IDE: STM32CubeIDE 2.2.0. Sensor: BME280, I²C1 PB8/SCL and PB9/SDA, address `0x76`, chip-ID register `0xD0`, expected ID `0x60`. The user reported unchanged wiring and a successful local build with 0 errors/0 warnings.

Chat 07.1 user-supplied debugger evidence:
- `baseline_ok=1`
- `fault_attempted=1`
- `fault_nack_observed=1`
- `fault_result=-1` (expected NACK in the test)
- `recovery_attempted=1`
- `recovery_error=0`
- `post_recovery_read_ok=1`
- `post_recovery_chip_id=96 (0x60)`
- `post_recovery_result=0`
- `sensor_address=118 (0x76)`
- `sensor_chip_id=96 (0x60)`
- `sensor_found=1`
- `sensor_error=0`
- `test_state=3 (RECOVERY_PASSED)`

The report is user-observed evidence, not independently run by GitHub tooling. Semihosting text did not appear in the visible console; Expressions showed the results. Do not troubleshoot console output unless essential. See the dated Chat 07.1 report for the precise evidence boundaries.

## Chat 08 scope

### Task A — Audit runtime integration boundaries
- Inspect the protected C reference runtime, public interfaces, Gate A–E contracts, existing host bridge/demo architecture, and the local hardware experiment source records.
- Do not edit protected reference files or frozen evidence.
- Identify the smallest interface boundary between a hardware I²C adapter, fault/error reporting, policy decision, recovery action, and fresh post-recovery read.
- Classify each implementation relationship as direct reuse, adaptation, or hardware-specific wrapper. Do not imply the STM32 implementation is identical to the host/reference runtime if it is not.
- Decide whether the full runtime can be compiled in the CubeIDE project or whether a small clearly labelled adapter is needed. Explain the reason before editing.

### Task B — Define the next experiment before coding
- State the fault model, why it is safe and reversible, exact trigger, expected error classification, bounded recovery action, retry limit, timeout behavior, and pass/fail criteria.
- Do not use electrical shorts, force SDA/SCL levels, disconnect powered sensor wiring, or perform unsafe voltage/power manipulations.
- The previous address-NACK test is already complete. Do not repeat it as if it were new evidence.
- Prefer a new controlled software-level case that exercises the actual runtime's decision path. If the only available safe case does not exercise a real peripheral error, label that limitation explicitly.
- Acceptance must include a fresh successful BME280 transaction after the runtime-controlled recovery action.

### Task C — Implement incrementally
1. Propose source changes and exact paths first.
2. Preserve the working local source and external backup; do not overwrite the LD2 experiment.
3. Build locally in the user's existing CubeIDE project only after the code is reviewed.
4. Do not flash until the user has been told exactly what will be programmed and explicitly approves.
5. Capture debugger-visible decision, fault/error, recovery attempt/result, and post-recovery sensor ID.
6. Avoid relying on semihosting; use debugger-visible volatile evidence fields if console output remains unavailable.

### Task D — Record the outcome
Update the result report, current state, handoff, roadmap, protocol, and README only after evidence is available. Mark each check as user-observed, tool-verified, or not run. Keep the new integration result distinct from the old GPIO and address-NACK results.

## Protected assets and hard rules
- Work on `main` only. No branches, merges, force-pushes, or history rewrites.
- Before every write, fetch the current file and blob SHA. Write sequentially; refetch after each update and reconcile if HEAD/content changed.
- Do not modify `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen K.10 400-execution evidence, prior-art reviews, or manuscript.
- Preserve `Plan2.0/firmware/ld2_gpio_recovery/` and the external local `main.c` backup.
- Do not repeat USB/ST-LINK setup, old port checks, baseline chip-ID read, or the already successful NACK/reinitialization test without a specific technical reason.
- No purchase/install requests; inspect tools already available.
- Never claim a hardware test, build, timing result, or runtime integration succeeded unless the user supplied evidence or a tool actually ran it.
- Distinguish the L476 board from the earlier U575 requirements; do not claim target equivalence.

## Definition of done
- Runtime integration boundary and fault model approved before hardware action.
- Minimal reviewed implementation compiles in the user's CubeIDE project.
- User explicitly approves flashing.
- Runtime-controlled fault decision/action is observed on hardware.
- Fresh BME280 transaction succeeds after recovery.
- Result and limitations are recorded in GitHub with a verified commit SHA.
- A next-chat handoff names only remaining work; no rediscovery or repetition.


## Chat 08 continuation update — 2026-10-25

The user has now supplied the working BME280 `main.c`. Do **not** ask them to upload it again and do not restart the source audit. A separate integration candidate is committed at [`Plan2.0/firmware/bme280_policy_integration/main.c`](../firmware/bme280_policy_integration/main.c), with local build and debugger acceptance instructions in the adjacent README and a status report under `results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md`.

**Immediate next action:** ask the user to preserve the current CubeIDE source/backup, place the candidate `main.c` into the existing project's application source location, add the unchanged `reference/include/ref_runtime.h` and `reference/src/ref_runtime.c` to the CubeIDE include/source locations, then perform a clean build. Do not flash yet. If the build fails, request the first relevant compiler/linker errors and fix the candidate without editing protected runtime files. If it builds cleanly, summarize the exact image about to be programmed and obtain explicit approval before flashing. Then verify debugger-visible values against the README acceptance list.

Expected P4 context: `policy_decision_action=2` (`ACT_REINIT_OR_RESET`), `policy_decision_reason=23`, real `hardware_action_result=0`, fresh `post_recovery_chip_id=0x60`, and `policy_release_result=1`. These are expected values, not observed results yet. Do not repeat the baseline or old controlled-NACK test unless a concrete technical reason arises. Preserve the separate LD2 experiment and frozen host/reference evidence.
