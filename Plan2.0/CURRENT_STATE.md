# Plan 2.0 — Current State

**Snapshot date:** 2026-10-24  
**Execution branch:** main only  
**Active work package:** Chat 05.3 debugger recovery succeeded; first software-injected GPIO recovery experiment completed. Transition next to Chat 06 reproducible minimal-firmware scaffold.  
**Status:** User-provided CubeIDE screenshots show clean build, successful firmware download verification, live debugger execution, and expected GPIO recovery values. Sensor integration, physical fault recovery and MCU performance measurements remain unverified.

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