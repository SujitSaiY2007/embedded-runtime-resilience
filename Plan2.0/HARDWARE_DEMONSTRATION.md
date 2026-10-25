# Physical Hardware Demonstration Plan

## Purpose

Validate a minimal, reproducible peripheral-fault and recovery path on physical hardware while preserving the host/reference runtime and separating MCU evidence from virtual simulation.

## Before firmware work

1. Inspect exact board markings and revision; record MCU part number and debugger interface.
2. Resolve the mismatch between the earlier proposed NUCLEO-U575ZI-Q / STM32U575ZI target and the identified NUCLEO-L476RG. Compare required MPU, memory, peripheral, clock, and toolchain features before selecting a target.
3. Record toolchain versions and reproducible build/flash procedure.
4. Select a 3.3-V-compatible sensor breakout and verify pinout, voltage, I²C address, and pull-up arrangement from its datasheet.
5. Create a wiring table and photograph the setup before power-on. Avoid shorts, unsafe hot-unplug, and deliberate electrical abuse.
6. Define acceptance tests and expected logs before implementing recovery.

## Minimal demonstration sequence

1. **Build/flash gate:** firmware builds reproducibly and reports board/build identity over serial.
2. **Healthy baseline:** repeated peripheral transactions succeed; save raw serial trace.
3. **Controlled failure:** induce a safe, reversible software-visible failure (for example, a bounded timeout/invalid response at the driver boundary). Only use physical disconnection if the setup and procedure make it safe.
4. **Detection:** record actual driver status/error and timestamp/counter.
5. **Policy decision:** route fault context through the same policy decision logic where portability permits. Document hardware-specific adapters or divergence.
6. **Recovery action:** record the action taken and its return status.
7. **Verification:** perform a new peripheral transaction after recovery. A reset attempt alone does not count as success.
8. **Repeatability:** run a predeclared number of trials and retain failures, timeouts, and raw traces as well as successes.

## Required evidence bundle

Board/MCU/revision, pin map and wiring photo; sensor/module identity; compiler/IDE/SDK versions; build/flash commands; firmware commit and binary hash; configuration; fault-injection procedure; trial count and acceptance criteria; raw serial logs; timing/resource measurement method and limits; failed trials; and explicit labels distinguishing physical measurements from host/reference-model results.

## Acceptance criteria

Baseline operation is stable; the injected failure is observed at the real driver interface or clearly labeled software-injected boundary; the recovery action is evidenced by trace; a fresh post-recovery transaction succeeds within a predeclared bound; the result is repeatable; raw evidence is retained; no MCU recovery claim is made from virtual-only results.


## Live bring-up status — 22 October 2026

The current NUCLEO-L476RG board powers on and is detected over USB, and the ST-LINK firmware update completed to V2J48M35. The generated CubeIDE Empty Project builds with 0 errors and 0 warnings. Debug launch currently fails with ST-LINK initialization error and GDB/SWV bind messages on TCP ports 61234/61235; the same ports had no matching entries in the user's netstat checks. Standalone STM32CubeProgrammer is not available to the user. Firmware flashing, MCU execution, sensor wiring, sensor reads and recovery remain unverified. Continue from [Chat 05.3 prompt](prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md), without repeating completed checks or buying/installing anything.


## Bounded hardware demonstration result — 25 October 2026

The current bounded controlled-NACK demonstration is complete at the scope evidenced by user-provided CubeIDE screenshots. See [Chat 11 five-policy diagnostic hardware report](results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md). The run reached `finished=1`, `overall_code=1`; the controlled wrong-address read returned the source-defined `E_NACK=-1`; P1 and P4 showed successful post-recovery BME280 ID reads (`0x60`) and release result 1. P0/P2/P3 ended in terminal outcomes.

This closes the current bounded demonstration task, not every possible hardware acceptance criterion listed above. The experiment did not demonstrate a physically stuck SDA/SCL bus, repeatability across independent trials, or MCU timing/stack/Flash/RAM/energy measurements. The 80 firmware decisions are runtime cases, not physical fault injections. The full matrix-status array is not independently reconciled because the available screenshots and later user description disagree about the last entry. Do not overstate these limits in a manuscript.

The next primary project phase is manuscript drafting and reference audit: [Claude prompt](../research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md). Do not rerun the hardware sequence merely to populate missing values, and do not alter the frozen 400-execution host/reference campaign.
