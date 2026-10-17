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
