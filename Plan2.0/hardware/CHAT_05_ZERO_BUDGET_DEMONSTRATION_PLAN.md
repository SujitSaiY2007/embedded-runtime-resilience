# Chat 05 — Zero-Budget Demonstration Plan

**Date:** 2026-10-22  
**Baseline:** `main` at `52bf814862fec94d991f190b28a01698996d4223`  
**Budget:** ₹0 additional  
**Current physical status:** `BLOCKED` pending board/cable inspection and BME280 module identification.

## 1. What the existing project can currently demonstrate

Repository files describe a C11 reference runtime, CMake tests, deterministic host experiments, a virtual embedded system, a Python bridge and browser demonstrator. The C reference runtime is authoritative for software policy transitions and trace records; the virtual system models peripheral state and scenario steps.

The README records a frozen host/reference campaign of 16 case families × 5 policy variants × 5 repetitions = 400 executions. These are software-model executions, not physical measurements. No STM32 firmware build/flash, BME280 driver, physical fault test, post-recovery sensor read, or MCU resource/timing result was verified in this audit.

Do not rerun or regenerate the frozen campaign to create a hardware-like result. Do not edit protected runtime, Gate A–E, or frozen evidence as part of this chat.

## 2. Requirements trace to current repository

| Behavior | Current repository evidence | Status for physical demo |
|---|---|---|
| Policy decision and runtime trace | Existing C reference runtime and its public contract | `VERIFIED` as software architecture presence; not MCU integration |
| Virtual peripheral and deterministic scenarios | `reference/virtual/` | `VERIFIED` as software model presence |
| Browser/Python demo path | README and demo layout | `VERIFIED` as documented software path; not rerun in this audit |
| STM32 firmware/toolchain project | No target project or STM32 adapter found in inspected paths | `UNVERIFIED / likely missing` |
| BME280 driver and real I²C acquisition | No BME280 driver found in inspected paths/search | `UNVERIFIED / likely missing` |
| Button event on MCU | Onboard user button exists per ST product documentation; no MCU firmware path verified | `UNVERIFIED` |
| Safe, reproducible fault at real driver boundary | No implemented physical driver path inspected | `BLOCKED` |
| Actual recovery action and fresh sensor transaction | No physical evidence found | `BLOCKED` |
| MCU timing/RAM/Flash/power measurements | No measurements verified | `BLOCKED` |

## 3. Smallest scientifically honest staged path

### Stage A — Zero-risk documentation gate (now)

1. Inspect the board silk-screen and product label; record exact NUCLEO model and MB1136 revision.
2. Inspect both ends of the existing cable and the board’s ST-LINK USB connector; verify fit and data capability without forcing or energizing a circuit.
3. Take one clear photo of the BME280 module, all pin labels, and any model/PCB marking. Identify it using manufacturer documentation, not appearance alone.
4. Confirm that no extra component is required. If the available kit cannot meet a requirement, stop physical work; do not buy anything.
5. Keep all sensor wiring unapproved until the compatibility matrix in `CHAT_05_HARDWARE_COMPATIBILITY_AUDIT.md` is complete.

### Stage B — Firmware and driver feasibility gate (not yet approved)

Only after Stage A and the board-target discrepancy are resolved, inspect/install nothing new and decide whether an existing toolchain is available. Do not assume one is installed.

A candidate minimal firmware would use the board’s existing ST-LINK, onboard user button and LED for event indication, and the BME280 only after the module is electrically verified. The policy integration must reuse the same policy decision logic where technically possible, with any MCU-specific adapter and divergence documented. No claim of “same runtime” is justified until source-level equivalence is reviewed.

### Stage C — Safe fault model

Prefer a bounded software-injected driver-boundary failure (for example, a test stub that returns a documented timeout/error) over electrical disruption. It is useful for validating policy wiring and trace handling, but it is **not** proof that the physical sensor or I²C bus experienced a real failure.

A physical-path test may proceed only if the real driver has a safe, reversible mechanism, such as a bounded timeout triggered by software configuration, and no damaging voltage, pin short, hot-unplug, or overcurrent is involved. Do not disconnect live wires as a fault trigger. If the existing implementation has no safe physical-path trigger, stop and report that limitation.

## 4. Required test record and acceptance criteria

Record one row per trial, including failures.

| Field | Required record |
|---|---|
| Test ID | Unique, stable ID |
| Firmware/source | Commit SHA, build configuration and binary hash |
| Board | Exact model, MCU, PCB revision |
| Sensor | Exact module/model, pinout evidence |
| Initial conditions | Supply, bus configuration, initial sensor identity/read |
| Fault trigger | Exact safe procedure and layer at which it is injected |
| Expected behavior | Predeclared policy decision, recovery action and bound |
| Observed behavior | Raw logs/status values; no paraphrased-only result |
| Recovery verification | A fresh successful sensor transaction after recovery |
| Pass/fail | Apply predeclared rule; count timeouts and failures |
| Repeatability | Predeclared trial count and conditions |
| Reset/recovery procedure | Exact safe steps |
| Safety condition | No shorts, overvoltage, unsafe hot-unplug or extra purchases |

**Pass** requires: healthy baseline is stable; the fault is observed at the claimed interface; the existing policy logic is actually invoked; action and trace are recorded; a fresh post-recovery transaction succeeds within a predeclared bound; and repeated trials preserve both successful and failed records. A reset command alone is not recovery proof. A stub-injected error must be labeled software-injected.

No physical test has been run; therefore there are no observed results and no pass/fail conclusion at this stage.

## 5. Pin map — conditional, not an instruction to wire now

The official ST UM1724 Table 23 lists PB9 as I2C1_SDA on Arduino D14 and PB8 as I2C1_SCL on Arduino D15. Actual routing depends on board configuration/solder bridges, and the exact sensor module is unknown. Thus the only responsible current status is:

| Signal | Candidate board route | Sensor side | Approval |
|---|---|---|---|
| Ground | Board GND | Unknown module GND pin | `BLOCKED` |
| SDA | PB9 / Arduino D14, after board configuration verification | Unknown module SDA pin | `BLOCKED` |
| SCL | PB8 / Arduino D15, after board configuration verification | Unknown module SCL pin | `BLOCKED` |
| Supply | No supply selected | Unknown module supply pin/range | `BLOCKED` |

Do not connect 5 V to the module or MCU. Do not connect the module to 3.3 V merely because the bare BME280 chip accepts a supply in that range; the actual breakout must first be identified. This table is deliberately **not** a wiring approval.

## 6. Zero-budget fallback

If sensor or target requirements cannot be verified without purchasing something, physical implementation remains `BLOCKED — ADDITIONAL HARDWARE WOULD BE REQUIRED` and no purchase is to be made. Continue with the already existing software demonstrator and clearly state that it validates the host/reference model only. If evaluation specifically requires a physical MCU test, disclose that it remains incomplete.

## 7. Decision

- Software/reference demo: existing and documented; not independently rerun in Chat-05.
- Physical sensor demo: `BLOCKED`.
- Ready for safe wiring: **No**.
- Ready for user approval of wiring: **No**.
- Next evidence needed: board/cable photo and BME280 module photo/model markings, followed by the target capability gate. No purchase required.
