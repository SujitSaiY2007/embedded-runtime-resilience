# Plan 2.0 — Current State

**Snapshot date:** 2026-10-25  
**Execution branch:** main only  
**Active work package:** Chat 09 — evidence reconciliation and final hardware integration audit following successful Chat 08 P4 policy-to-BME280 run.  
**Status:** Chat 08 firmware built with 0 errors/0 warnings, flashed and verified, and completed the controlled NACK → recovery → fresh BME280 read path with terminal success (`test_finished=1`, `test_report_code=8`, `test_state=3`) in user-provided debugger screenshots. This is one transaction-level NACK demonstration, not stuck-bus recovery or a statistical superiority result.  

## Completed before Plan 2.0

- C11 reference runtime and tests.
- Virtual embedded system, scenario runner, Python bridge, and browser demonstrator.
- Frozen deterministic host/reference campaign: 16 case families × 5 policy variants × 5 repetitions = 400 executions.
- Evidence-bounded K.10 findings and K.10.1–K.10.4 distinction reviews.
- K.11 software synthesis/hardware handoff and K.12 software demonstrator audit.

## Current hardware identity and constraints

- Board reported and shown: **ST NUCLEO-L476RG, revision MB1136 C**, targeting STM32L476RG.
- Earlier design documents proposed STM32U575ZI / NUCLEO-U575ZI-Q. This target discrepancy remains a research/requirements decision; do not claim the L476 is equivalent to the U575 for MPU/security requirements.
- User confirmed the board powers on and the laptop detects a USB device when connected board-only.
- ST-LINK firmware upgrade via STLinkUpgrade 3.17.11 completed successfully. The tool showed type STM32 Debug+Mass storage+VCP and firmware version V2J48M35.
- STM32CubeIDE 2.2.0 is installed. A generated Empty Project named Embedded-Runtime-Resilience exists in the user's CubeIDE workspace under STM32CubeIDE/workspace_2.2.0/Embedded-Runtime-Resilience. It is a local generated project and must not be assumed to be the canonical GitHub source tree.
- The local generated CubeIDE workspace project now contains a register-level GPIO recovery experiment. User screenshots show a **0 errors / 0 warnings** build, “Download verified successfully,” a live debug session reaching the final loop, and all eight expected debugger values. This is evidence for that local experiment, not yet proof that its sources are integrated into the canonical repository.
- The user does not have the standalone STM32CubeProgrammer application available. Do not ask them to install it or purchase anything. If useful, inspect existing CubeIDE-bundled tools first.

## Chat 05.2 debugger attempt — exact observations

- ST-LINK firmware upgrade succeeded, but this alone does not prove SWD communication with the target MCU.
- Existing debug configuration shown: ST-LINK (ST-LINK GDB server), interface SWD, access port 0 - Cortex-M4.
- CubeIDE's shown GDB-server command was:

    C:\ST\STM32CubeIDE_2.2.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.win32_2.2.500.202604010938\tools\bin\ST-LINK_gdbserver.exe -p 61234 -l 1 -d -s -cp C:\ST\STM32CubeIDE_2.2.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_2.2.500.202603051304\tools\bin -m 0 -g

- Console error: Failed to bind to port 61235, error code -1: No error; Failure starting SWV server on TCP port 61235; Failed to bind to port 61234, error code -1: No error; Failure starting GDB server: TCP port 61234 not available.
- Expanded launch error: Error in initializing ST-LINK device. Reason: (0) Unknown. Please check power and cabling to target.
- User ran netstat -ano | findstr :61234 and netstat -ano | findstr :61235; both commands returned no matching entries. Therefore, there is no evidence from that check that another process owns either port. Do not assume port occupation is the root cause.
- Restarting CubeIDE did not resolve the launch failure. A later attempt showed the same error. A suggested reset-behaviour change to Software system reset may have been attempted, but the latest saved setting is not confirmed; inspect it rather than assuming.
- Standalone STM32CubeProgrammer was suggested but the user confirmed it is not available.

## Verified / unverified evidence ledger

| Item | Status | Provenance |
|---|---|---|
| NUCLEO-L476RG powers on | Verified as user-observed | User confirmation |
| Laptop detects board-only USB device | Verified as user-observed | User confirmation |
| ST-LINK firmware update to V2J48M35 | Successful | User screenshot |
| Generated CubeIDE project build | 0 errors, 0 warnings | User screenshot |
| TCP port entries from the two netstat checks | No matches returned | User screenshot |
| ST-LINK GDB server starts and connects over SWD | **Blocked / failed** | User screenshot and console |
| Custom local experiment downloaded to MCU | **User-evidence verified** | CubeIDE console screenshot: “Download verified successfully” |
| Custom local experiment executed under debugger | **User-evidence verified** | Debugger paused in final loop; Expressions view showed expected values |
| Sensor identity/electrical compatibility/wiring | **Unverified / do not wire** | See Chat 05.2 prompt |
| Software-injected PA5 configuration fault and register-checked recovery | **Narrow test passed** | User screenshots; see [GPIO experiment report](results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md) |\n| Sensor reads, physical peripheral-failure recovery, MCU timing/stack/energy measurements | **Not performed / not verified** | No evidence supplied |

## Existing component inventory and zero-budget rule

The Chat 05.2 prompt remains authoritative for the already-owned inventory: expected NUCLEO-L476RG; one BME280-labelled module; MB-102 breadboard; two packs of 4-pin push buttons; four resistor packs of unknown values; six jumper-wire items/packs as recorded; one cable described for Arduino Uno/Mega; STM32CubeIDE installed. Recorded receipt total: ₹739. Additional spending: **₹0**. Exact module markings/pinout/electrical design, resistor values, jumper ends/count, and cable data capability remain unverified unless directly evidenced.

## Protected boundaries

- Work only on main; do not create/switch to other branches, merge, or force-push.
- Preserve the C reference runtime, Gate A–E contracts, frozen 400-execution host/reference evidence, experiment sources/configuration, prior-art analyses, manuscript and historical records.
- Do not rerun the frozen 400-execution campaign.
- Do not treat the generated CubeIDE Empty Project as repository firmware; do not copy generated startup/linker files into the repository without a reviewed plan.
- Do not wire the sensor or add external components until identity, target requirements, pinout, logic levels, supply and pull-ups have been verified and the full wiring table reviewed.
- No new purchases, borrowing, installs or dependencies. If a needed check requires unavailable equipment/software, record the blocker honestly.

## Next action

The original Chat 05.3 debugger blocker is superseded by the 2026-10-24 GPIO experiment evidence recorded below and in [the experiment report](results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md). Continue with **Chat 06 — minimal-firmware scaffold and source provenance** using [the current next-chat prompt](../NEXT_CHAT_PROMPT.md). Do not repeat earlier target-identification, firmware-update, port checks or manual GDB-server tests. Do not wire the sensor or modify protected research assets.


## Chat 05.3 continuation outcome — 2026-10-22

**Outcome: BLOCKED / ROOT CAUSE NOT YET ESTABLISHED.** Continuity documents and saved user evidence were reconciled against live `main`. The repository connector cannot inspect the Windows host's local CubeIDE UI, filesystem, process table, installed executables, or local log files; no claim is made that bundled tools have been physically verified on that host during this chat.

### Checks performed in this chat
- Read the mandatory Chat 05.3 state, handoff, prompt, protocol and roadmap from live `main`.
- Read the prompt-required top-level README, Plan 2.0 README, Chat 05 hardware compatibility audit, and Chat 05.2 bring-up prompt from live `main`.
- Inspected live `main` before repository writes. Initial head: `af38761a153129d36c58aca84fba2a7e78e2f7cd`.
- No Windows command was run by this chat. The previous no-match results for ports 61234/61235, firmware update, and empty-project build remain **user-reported/screenshot evidence from Chat 05.2**, not new tests.
- No board interaction, debugger launch, target-identification operation, firmware download, sensor wiring, source edit, or research experiment was performed in this chat.

### Diagnosis bounded by available evidence
- The recorded log reports ST-LINK initialization failure together with GDB/SWV listener bind errors on 61234/61235. Prior `netstat` checks produced no matching entries, so occupied ports are not established as the cause.
- The root cause remains unresolved among local configuration/tool startup, probe/driver communication, target-access, and listener startup possibilities; none is proven from saved screenshots alone.
- Current reset-behaviour setting and the actual existence/version of CubeIDE-bundled CLI utilities remain unknown because these are local-host facts not exposed by the GitHub connector.
- Safe next check is specified in `Plan2.0/handoffs/CHAT_05_3_HANDOFF.md`: inspect the existing Debug Configuration (reset behaviour and SWV setting), then use File Explorer to verify whether the already-referenced `ST-LINK_gdbserver.exe` and `STM32_Programmer_CLI.exe` are present. No write-capable command is to be run at this stage.

### Evidence boundary
The generated CubeIDE Empty Project build result remains compilation/link evidence only. Target connection, firmware flash, application execution, sensor access, fault injection, recovery and MCU-specific measurements remain unverified. NUCLEO-L476RG is not assumed equivalent to the historical NUCLEO-U575ZI-Q proposal. Frozen 400-execution research evidence and protected runtime files remain untouched.

### Chat 05.3 repository provenance
- Branch: `main` only.
- Continuity documentation and navigation were updated in this closeout sequence; the final live HEAD is recorded in the Chat 05.3 response.
- Repository-side checks: live files were fetched and blob SHAs compared before edits. No firmware/toolchain build or hardware test was run by the repository connector.


## Chat 05.3 resumed investigation — 2026-10-24

Status: target identification verified; CubeIDE debug session remains blocked; root cause not yet established. Do not restart setup or repeat earlier checks.

New user evidence:
- Device Manager lists ST LINK DEBUG without a yellow warning; user says it works fine.
- Bundled STM32_Programmer_CLI.exe is present; CLI version/help reports 2.23.0. Bundled ST-LINK_gdbserver.exe reports version 7.14.0.
- Read-only SWD connection using mode=HOTPLUG and freq=4000 identified NUCLEO-L476RG, device ID 0x415, Rev 4, Cortex-M4, target voltage 3.27 V, ST-LINK firmware V2J48M35.
- CubeIDE's original ports 61234/61235 failed to bind; earlier netstat checks had no matching entries. Do not assume an occupied port.
- Manual GDB server launch with explicit CubeProgrammer tools path and port 50000 reached 'Waiting for debugger connection...'. This proves the server reached a wait/listen state, not a complete debug session.
- CubeIDE generated command on port 50000 was supplied by the user and includes the same GDB server and CubeProgrammer tools paths as the manual command, plus -m 0 -g --frequency 140. Do not ask for that command again.
- CubeIDE still failed. A localhost/remote attempt also failed and showed 'No ST-LINK detected!'. Current server process/listener state is unknown.
- SWV was unchecked and retry still failed. The exact root cause is unresolved.

Next chat must continue this same Chat 05.3 task. Do not repeat the CLI target identification, executable-path checks, old port checks, build, firmware update, manual server test on 50000, or generic localhost instructions. Investigate the lifecycle/configuration difference between a manually waiting GDB server and CubeIDE autostart/remote modes. Ask for one new diagnostic only if its result distinguishes hypotheses. Do not leave two servers competing for the same ST-LINK. No installs, purchases, erase, option-byte change, flash, sensor wiring, source/runtime edits, or changes to protected research evidence. Work on main only. The GitHub connector cannot inspect local Windows processes or UI; clearly distinguish user-provided evidence from repository-side verification.
\n\n## Chat 05.3 GPIO experiment update — 2026-10-24\n\nThe earlier debugger-blocked status above is superseded by the new user-provided evidence in [the experiment report](results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md). The local CubeIDE build completed with 0 errors/0 warnings; the console showed successful download verification; the debugger reached the final loop; and the eight Expressions values matched the expected successful path (event=1, fault=1, recovery=1, state=4/RECOVERED, recovered=1, injection=1, GPIO mode=output, output latch=high). The experiment injects a software configuration fault by changing PA5 from output to input, then restores output mode and sets PA5 high. This does not establish physical peripheral failure recovery, independent pin-voltage/optical measurement, sensor operation, repeated-trial reliability, or MCU resource measurements. The code remains in the local generated CubeIDE workspace; do not imply it is already canonical repository firmware.\n\n### Next action\n\nTransition from Chat 05.3 diagnosis to Chat 06 minimal-firmware scaffold/provenance. Preserve the local backup and working firmware. First reconcile source provenance and make the minimal test reproducible without copying generated startup/linker files or modifying the protected C reference runtime. Then plan Chat 07 baseline peripheral integration; do not wire the BME280-labelled module until identity and electrical compatibility are verified. Chat 08 remains the broader controlled-fault/recovery work package; this first GPIO test is only a narrow initial milestone.\n

## Chat 06 source-preservation update — 2026-10-24

The user supplied the three current source files and confirmed the external backup of the earlier `main.c` remains separate. A normalized plain-C transcription of the supplied `main.c`, `err_runtime.c`, and `err_runtime.h`, plus provenance notes, is preserved in [firmware/ld2_gpio_recovery](firmware/ld2_gpio_recovery/README.md). The source is now version-controlled on `main`; this does not mean the generated local CubeIDE workspace has been integrated or that a clean build from the repository source has been independently verified.

**Checks performed in this repository session:** inspected the live `main` head and relevant current state/experiment records; confirmed the new source paths did not already exist; wrote the three source files and provenance README sequentially on `main`. No compiler, CubeIDE, board, local filesystem, or CI build was run by the repository connector. The original user's 24 October build/download/debug observations remain screenshot-supported user evidence.

**Next action:** inspect the local CubeIDE project structure/configuration without modifying it, then design a reproducible build/scaffold boundary. Do not copy generated startup/linker/IDE files or change the protected C reference runtime. Chat 07 remains blocked on sensor identity and electrical-compatibility gates; Chat 08 remains the broader controlled recovery package.


## Chat 06 configuration review update — 2026-10-24

User screenshots now confirm the existing local CubeIDE project's active `Debug` configuration, GNU Tools for STM32 `14.3.rel1`, GNU11 (`-std=gnu11`), Flash linker script `STM32L476RGTX_FLASH.ld`, map-file generation, unused-section removal, and minimal system-call implementation (`--specs=nosys.specs`). The project tree includes generated startup/build artifacts, ELF/list/map files, a debug launch configuration, and both Flash and RAM linker scripts. The screenshots do not confirm the full CPU/FPU flags or prove a clean repository-checkout build.

The user asked to stop further configuration-screen inspection and proceed. No more screenshots/settings checks should be requested without a concrete blocker. Next, finish Chat 06 by documenting the observed build configuration and safe reproduction procedure, without copying generated workspace/build artifacts or overwriting the local working project/backup. No local build or board action was performed by the repository connector.

## Chat 06 follow-up — local rebuild confirmed (2026-10-24)

After configuration inspection, the user closed project Properties with Cancel and ran `Project → Build Project` on the existing local `Embedded-Runtime-Resilience` CubeIDE project. User reported that it “works fine.” Exact final error/warning counts were not supplied in this follow-up. No download/debug/board interaction was requested. This is evidence that the existing local project still builds; it is not a clean build from a repository checkout and does not independently verify that the GitHub-preserved source directory alone is buildable.

Chat 06 can now close its local inspection phase: source files and provenance are preserved, relevant CubeIDE settings are recorded, and the existing local project rebuild was user-confirmed. Remaining limitation: a clean, reproducible build from a reviewed repository scaffold has not been demonstrated. Do not ask for more configuration screenshots unless a concrete blocker appears. Next work is Chat 07 planning only: verify the exact sensor/module identity and electrical compatibility from markings/documentation before any wiring; no sensor wiring is currently approved.

## Chat 07 sensor baseline milestone — 2026-10-25

User-provided STM32CubeIDE Expressions screenshot and ST-LINK log now establish a successful sensor chip-ID read:
- Firmware download log: **“Download verified successfully”**; target device ID `0x415`, voltage 3.26 V.
- Expressions: `sensor_found=1`, `sensor_address=118 (0x76)`, `sensor_chip_id=96 (0x60)`, `sensor_type=1`, `sensor_error=0`.
- The read of register `0xD0` at I²C address `0x76` returned `0x60`, matching the BME280 chip ID. User reports the build worked after adding HSI16 enable/wait and setting `I2C1->TIMINGR = 0x30420F13U`.

This is a meaningful physical peripheral baseline-read result and supersedes earlier statements that no sensor read had been performed. Evidence is user-supplied; the GitHub connector did not operate CubeIDE or the board. Full temperature/pressure/humidity reads, calibration compensation, repeatability, sensor fault recovery, a fresh post-recovery transaction, and MCU performance measurements remain unverified. Stale `test_*` Expressions entries showed “Error: Multiple errors…” in this sensor-test session; these are separate from the valid `sensor_*` results and should be cleared/recreated for future debugging.

Detailed result and evidence boundary: [Chat 07 BME280 chip-ID detection report](results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md).

### Next action — Chat 07.1

Review the exact current local sensor-test source and preserve its provenance separately from the successful LD2 GPIO recovery experiment. Then design the smallest safe, reversible software-controlled I²C fault/recovery test whose acceptance criterion is a **fresh successful chip-ID transaction after recovery**. Do not use electrical shorts or unsafe pin forcing. Preserve the external `main.c` backup and protected research assets. See [Chat 07.1 prompt](prompts/CHAT_07_1_BME280_BASELINE_AND_RECOVERY_PROMPT_2026-10-25.md).


## Chat 07.1 update — controlled BME280 NACK and I²C reinitialization (2026-10-25)

The user supplied CubeIDE evidence for a successful run of the controlled NACK/reinitialization test. The screenshot showed `baseline_ok=1`, `fault_attempted=1`, `fault_nack_observed=1`, `fault_result=-1`, `recovery_attempted=1`, `recovery_error=0`, `post_recovery_read_ok=1`, `post_recovery_chip_id=96 (0x60)`, `post_recovery_result=0`, `sensor_address=118 (0x76)`, `sensor_chip_id=96 (0x60)`, `sensor_found=1`, `sensor_error=0`, and `test_state=3 (RECOVERY_PASSED)`. User-provided build screenshot showed 0 errors and 0 warnings.

This demonstrates a fresh successful BME280 chip-ID read after a controlled address-NACK attempt and I²C1 peripheral reinitialization. It does not establish recovery from a physically stuck bus or show the protected reference runtime making the recovery decision. Semihosting output was not visible; debugger Expressions provided the evidence. GitHub tools did not run CubeIDE, compile, flash, or operate the board.

Full report: [Chat 07.1 controlled-NACK result](results/CHAT_07_1_BME280_CONTROLLED_NACK_RECOVERY_2026-10-25.md).

**Next package: Chat 08 — runtime-to-hardware integration.** Inspect the runtime and contracts; define the smallest safe hardware adapter and fault model; then integrate incrementally. The acceptance gate is a runtime-controlled recovery decision/action followed by a fresh successful sensor transaction. Do not repeat the baseline or completed NACK test, do not overwrite the separate LD2 experiment, and do not flash without explicit user approval. See [Chat 08 prompt](prompts/CHAT_08_RUNTIME_HARDWARE_INTEGRATION_PROMPT_2026-10-25.md).


## Chat 08 source-preparation update — 2026-10-25

The user's current working BME280 `main.c` was supplied and used as the base for a separate policy-integration candidate at [`firmware/bme280_policy_integration/main.c`](firmware/bme280_policy_integration/main.c). Its [README](firmware/bme280_policy_integration/README.md) records required files, expected debugger values, and the local validation sequence. The candidate admits an exact I2C read event into `VAR_P4_INTEGRATED`, confirms the controlled NACK, starts a `FAULT_I2C_NACK` episode, calls `policy_decide()`, executes the selected `ACT_REINIT_OR_RESET` through the real `i2c_recover()` function, and only releases the quarantined event after a fresh chip-ID read succeeds.

The protected `reference/src/ref_runtime.c` and `reference/include/ref_runtime.h` were not modified. The LD2 experiment and external `main.c` backup remain separate; the frozen 400-execution campaign and Gate A–E contracts were not rerun or changed. A result record is available at [Chat 08 integration candidate report](results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md).

**Validation boundary:** source preparation and GitHub documentation updates are complete. No STM32 cross-compiler/CubeIDE build, firmware flash, or hardware run was performed by the repository connector. The Chat 07.1 screenshot is evidence only for the previous non-policy-driven test. Chat 08 acceptance remains pending a clean local build and an explicitly approved flash/run. Do not claim physical stuck-bus recovery or MCU performance measurements.

**Immediate next action:** copy the candidate and the exact protected runtime source/header into the existing CubeIDE project using the README instructions; build first, resolve compile/link errors without editing the protected repository runtime, and report the build result before any flash operation.

## Chat 08 hardware result (2026-10-25)

- User-provided CubeIDE build: 0 errors, 0 warnings.
- Firmware download and verification: successful.
- Observed terminal variables: `baseline_ok=1`, `fault_attempted=1`, `fault_nack_observed=1`, `recovery_attempted=1`, `post_recovery_read_ok=1`, `post_recovery_chip_id=0x60` (96), `sensor_error=0`, `test_state=3`, `test_finished=1`, `test_report_code=8`.
- Full record: [Chat 08 hardware integration result](results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md).
- Chat 09: reconcile the runtime decision/action/release/trace fields with the physical action; check source/report consistency and finish documentation. Do not repeat successful baseline/NACK steps without a concrete evidence gap.


## Chat 09 hardware evidence reconciliation — 2026-10-25

**Status: Chat 08 physical hardware milestone complete at the bounded controlled-NACK scope.** User-provided screenshots (saved by the user) show a clean CubeIDE build (0 errors/0 warnings), successful download verification, `baseline_ok=1`, `fault_attempted=1`, `fault_nack_observed=1`, `recovery_attempted=1`, `post_recovery_read_ok=1`, `post_recovery_chip_id=0x60`, `sensor_error=0`, `test_state=3`, `test_finished=1`, and `test_report_code=8`. The debugger halted at the intentional terminal breakpoint.

The live firmware source and current protected reference runtime were audited read-only. Source logic indicates the success code is assigned only after a fresh chip-ID read succeeds and `runtime_verify_and_release()` returns `OUTCOME_SUCCESS`. `print_test_report()` sets `test_finished`, executes `__BKPT(0)`, then enters a terminal `while(1)` loop; this makes the breakpoint intentional and holds final values stable after resume.

Auxiliary fields (`policy_variant`, event admission/fault-start results, decision action/reason, action-attempt flag, hardware action result, release result, event slot/generation, runtime byte count and trace count) were not included in the available screenshot summary. The source-derived expected path is P4 variant 4, successful admission/fault start (1), `ACT_REINIT_OR_RESET` (2), reason 23, hardware action result 0 and successful release (1), but these are **not confirmed as debugger observations**. Exact slot/generation/trace/byte counts are **not captured** and are not inferred.

**Recommendation:** do not repeat the baseline/NACK sequence or flash again for this milestone. An optional debugger-only inspection of the already-saved terminal session may document the omitted auxiliary fields without rerunning the experiment. No additional hardware run is necessary to close Chat 08's acceptance gate. Full stuck-bus recovery, repeated-run reliability, environmental measurement, MCU performance/memory measurements, and universal P4 superiority remain unverified. Full audit: [Chat 09 evidence reconciliation](results/CHAT_09_HARDWARE_EVIDENCE_RECONCILIATION_2026-10-25.md).

**Audit provenance:** live `main` was read before edits; the GitHub connector did not execute the Windows toolchain, access the local screenshots, operate the board, or compile/flash firmware. Protected reference files, Gate A–E, frozen 400-run evidence, prior-art reviews and manuscript remain unchanged.

## Chat 10 planned scope — 2026-10-25

Chat 09 closed the bounded Chat 08 hardware demonstration. Chat 10 is now specified as **final hardware validation, evidence reconciliation and UI-integration readiness**; it has not yet been executed. The starting evidence is the two user-provided screenshots of the same Chat 08 run: controlled address NACK observed, recovery attempted, fresh BME280 ID read succeeded (`0x60`), and terminal report code 8. Do not count these screenshots as separate trials.

Chat 10 must first inspect the current repository and propose an experiment matrix with predeclared criteria. It may perform only justified, safe, feasible and approved experiments. Repeated runs, failure-path tests, P0–P4 target comparisons, and MCU resource/latency measurements are not presumed complete. Distinguish target observations, software/reference results, and source-derived expectations. Physical stuck-bus recovery and unsupported measurements remain unverified unless separately tested.

After hardware validation is closed or remaining blockers are explicitly documented, Chat 10 must prepare Chat 11 requirements for real-time UI integration, including a verified firmware-to-host communication path, real versus simulated data boundaries, message fields and an end-to-end acceptance test. No UI changes in Chat 10.

Prompt: [CHAT_10_FINAL_HARDWARE_VALIDATION_PROMPT_2026-10-25.md](prompts/CHAT_10_FINAL_HARDWARE_VALIDATION_PROMPT_2026-10-25.md).


## Chat 10 update — 2026-10-25: repeated-trial protocol defined

The user selected a target of **five total controlled recovery trials**. Read-only inspection of the current integration source confirms a one-shot test sequence: healthy BME280 chip-ID read, controlled address NACK at `0x77`, P4 decision, I2C1 peripheral reinitialization, fresh chip-ID read at `0x76`, runtime event release, then terminal `__BKPT(0)` and loop.

The existing Chat 08 run is recorded as **Trial 1 (historical evidence)**; the two screenshots are one run. Its main-path pass variables are user-evidence verified, but exact build artifact identity and some auxiliary runtime fields are not captured. Trials 2–5 have **not been performed**. No compiler, CubeIDE, reset, MCU, or flash operation was performed by the GitHub-side audit. No flashing is authorized unless the user explicitly approves it after source/build review and a clean build.

Predeclared pass criteria require baseline success, observed controlled NACK, P4-selected I2C1 reinitialization, successful action result, fresh post-recovery BME280 ID `0x60`, successful runtime release, and terminal report `test_state=3`, `test_finished=1`, `test_report_code=8`. Failures must be preserved; missing/contradictory evidence is inconclusive. Do not count a diagnostic rerun as the same trial.

Report and procedure: [Chat 10 final hardware validation](results/CHAT_10_FINAL_HARDWARE_VALIDATION_2026-10-25.md). Chat 11 prompt: [real-time UI integration](prompts/CHAT_11_REALTIME_UI_INTEGRATION_PROMPT_2026-10-25.md).

**Current status: Chat 10 in progress.** Repeatability closure, available build-artifact inspection, and final hardware-to-UI readiness review remain pending. Physical stuck-bus recovery, P0–P4 hardware comparison, MCU timing/stack/energy measurements and universal P4 superiority remain unproven.

## Unified five-policy matrix candidate — 2026-10-25

A new candidate was added on `main`: [`embedded_runtime_five_policy_matrix.c`](firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix.c), with review plan [`FIVE_POLICY_HARDWARE_MATRIX_PLAN_2026-10-25.md`](results/FIVE_POLICY_HARDWARE_MATRIX_PLAN_2026-10-25.md). It attempts a sequential physical controlled-NACK comparison for P0–P4 plus an 80-row (5 policies × 16 provisional runtime contexts) decision matrix using the protected reference runtime API.

**Not yet compiled, run, or validated. Do not flash yet.** The 16 in-firmware contexts are provisional and must be reconciled against the exact frozen host campaign definitions before claiming case-family equivalence. Physical execution covers only the controlled I²C address NACK; the matrix rows are runtime decision tests, not physical fault injections. Existing `main.c`, protected reference runtime files, and frozen 400-execution evidence remain unchanged.



## Chat 11 — five-policy diagnostic hardware run and manuscript transition (2026-10-25)

**Status:** The user-provided CubeIDE debugger evidence shows the diagnostic harness reached its terminal completion function (`progress_stage=900`, `finished=1`, `overall_code=1`). The latest values are reconciled in [Chat 11 hardware report](results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md).

Observed values include baseline error slots 0; all five `nack_result` values -1 (source-defined `E_NACK`); physical statuses P0–P4 = 7,1,7,7,1; and for P1/P4, `post_read_ok=1`, chip ID 96 (`0x60`), and `release_result=1`. The source maps 7 to `R_TERMINAL` and 1 to `R_PASS`. This is one controlled wrong-address NACK followed by the selected I²C1 peripheral recovery/reinitialization path and a fresh BME280 read; it is not stuck-bus recovery or a repeatability/performance study.

### Matrix qualification

The embedded matrix has 5 policies × 16 provisional contexts = 80 runtime decisions. These are not 80 physical fault injections and the 16 contexts are not verified as identical to the frozen CF01–CF16 host corpus. A screenshot showed `matrix_status[79]=1`, while the user later described all matrix entries as 1 except the last. Since the complete array was not captured in a readable export, this conflict remains unresolved. Do not assert that all 80 slots are independently verified solely from `overall_code=1`.

### Next work package

The hardware milestone is closed at its bounded evidence scope; the next priority is the journal manuscript and literature audit. Use [Claude manuscript prompt](../research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md). Preserve the frozen 400-execution host campaign, protected runtime, Gate A–E contracts and all historic evidence. No hardware or build operation was performed by this GitHub-side update.
