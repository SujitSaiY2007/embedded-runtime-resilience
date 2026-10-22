# Plan 2.0 — Current State

**Snapshot date:** 2026-10-22  
**Execution branch:** main only  
**Active work package:** Chat 05.2 hardware bring-up, paused at ST-LINK/GDB initialization  
**Status:** Board-only USB detection and IDE build verified by user; MCU debug connection, firmware flash/execution, sensor wiring and physical recovery remain unverified.

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
- The user showed Src/main.c containing an infinite loop. The latest build console screenshot reports **0 errors, 0 warnings**. This confirms compilation/linking of the generated empty project only, not custom runtime integration or hardware execution.
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
| Firmware flashed to MCU | **Not verified** | No successful download evidence |
| MCU application execution | **Not verified** | No live debug or runtime evidence |
| Sensor identity/electrical compatibility/wiring | **Unverified / do not wire** | See Chat 05.2 prompt |
| Sensor read, fault injection, recovery, MCU measurements | **Not performed / not verified** | No raw evidence |

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

Continue in **Chat 05.3**, using [the continuation prompt](prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md) and [the Chat 05.2 handoff](handoffs/CHAT_05_2_HANDOFF.md). Do not repeat completed USB detection, firmware upgrade, clean build or empty netstat checks unless new evidence justifies it. Diagnose the ST-LINK initialization failure using already-installed tools only. Do not claim flashing or execution until raw success evidence exists.
