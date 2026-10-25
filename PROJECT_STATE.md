# Project State — Canonical Current Snapshot

**Last reconciled:** 2026-10-24  
**Project:** Embedded Runtime Resilience  
**Repository:** SujitSaiY2007/embedded-runtime-resilience  
**Current state:** **Software/research scope finalized; Plan 2.0 hardware demonstration active. First local GPIO fault-injection/recovery run verified under CubeIDE debugger; sensor integration and broader physical validation remain open.**

> Current hardware status is maintained in [Plan2.0/CURRENT_STATE.md](Plan2.0/CURRENT_STATE.md). The historical software/research findings below remain valid; the old “hardware is future work” wording is superseded by active Plan 2.0 bring-up. As of 2026-10-24, later user screenshots supersede the earlier debugger-blocked status: a local CubeIDE build succeeded, firmware download was verified, the debugger reached the test's final loop, and expected GPIO recovery values were observed. See Plan2.0/CURRENT_STATE.md and the GPIO experiment report. Sensor operation, physical peripheral failure recovery, and MCU measurements remain unverified.

## 1. Finalized deliverable

The repository contains:
- frozen Gates A–E and protected C reference runtime;
- deterministic host experiment sources and frozen K.10 result report;
- adversarial technical-distinction review K.10.1–K.10.4;
- evidence-bounded final research conclusion;
- K.11 software synthesis and future hardware handoff;
- K.12 virtual embedded-system demo, Python bridge, browser UI and tests;
- curated project documentation under `docs/`;
- historical checkpoint records and decision logs.

## 2. Branch status

- `main`: finalized reader-facing documentation and approved software/research implementation.
- `exp`: retained unchanged at `ab766b47ce7bae2791028cea22b7915f8debc41c` as frozen research baseline.
- `feature/k10-4-final-technical-conclusion-2026-10-13`: preserved historical integration branch; not the current presentation entry point.

Always query GitHub for live branch heads before a new write. This snapshot is a dated record, not a substitute for fetching current refs.

## 3. Verification provenance

The user reported successful local CMake/CTest and UI-contract test runs and a working browser demo on 2026-10-13. These are user-run observations. The remote GitHub review did not independently run the Windows toolchain or browser; do not call these CI-verified.

## 4. Research conclusion

The frozen K.10 campaign contains 16 case families × 5 variants × 5 repetitions = 400 deterministic host/reference executions. The reports support bounded advantages for P4 in selected cases, not universal superiority. Exact-event quarantine is shared across P0–P4. The CF16 trade-off records P2 success in one attempt versus P4 in three. QMAX=16 and EPMAX=1 are important constraints.

CF01 has a table/narrative conflict on P2 attempt count. For final presentation, use only the uncontested qualitative outcomes (P0 terminal escalation, P2 success, P4 success) and omit the disputed count from numerical comparisons. Frozen records remain unchanged.

## 5. Protected boundaries

Do not alter without a separately approved research change:
- `reference/src/ref_runtime.c`
- `reference/include/ref_runtime.h`
- `research/phase1_reference_implementation_design.md`
- `research/phase2_k9_methodology_lock.md`
- `research/phase2_k9_2_p4_advantage_novelty_design.md`
- frozen K.10 results and Gate A–E contracts.

Do not rerun the K.10 matrix to resolve editorial inconsistencies. Do not imply hardware validation was performed.

## 6. Plan 2.0 hardware continuation (current as of 2026-10-22)

The historical software/research closure remains valid, but the separate Plan 2.0 physical-demonstration work package is now active. Chat 05.3 has progressed beyond the earlier ST-LINK/GDB blocker: user screenshots show successful download verification and debugger execution of a local GPIO experiment on the NUCLEO-L476RG. A software-injected PA5 mode fault was followed by register-checked restoration, with all eight expected debugger values observed. This is a narrow hardware-execution milestone, not physical peripheral-failure recovery. Sensor wiring/reads, repeatability, MCU timing/stack/energy measurements, and the L476/U575 target discrepancy remain open. Continue from Plan2.0/CURRENT_STATE.md and the GPIO experiment report; the next planned package is Chat 06 reproducible minimal-firmware scaffold, followed by Chat 07 baseline peripheral integration and Chat 08 broader controlled fault/recovery.

## 7. Reader navigation

Start with `README.md`, then `docs/PROJECT_OVERVIEW.md`, `docs/ARCHITECTURE_AND_REPOSITORY_MAP.md`, `docs/DEMONSTRATOR_GUIDE.md`, and the final K.10.4/K.11/K.12 reports. The root continuity files and `research/chat_records/` preserve detailed history.


## Hardware status update — 2026-10-25

The user has now demonstrated a successful BME280 chip-ID read on the physical NUCLEO-L476RG. The user-provided debugger screenshot showed `sensor_found=1`, `sensor_address=0x76`, `sensor_chip_id=0x60`, `sensor_type=1`, and `sensor_error=0`; the user-pasted ST-LINK log reported “Download verified successfully.” This supersedes older statements that sensor reads had not yet been performed. See `Plan2.0/results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md`.

This supports baseline I²C chip identification only. Full environmental measurements, repeated trials, controlled sensor fault/recovery with a fresh successful post-recovery transaction, and MCU timing/stack/energy measurements remain unverified. The prior LD2/PA5 GPIO configuration recovery remains a separate, preserved milestone. Continue from `Plan2.0/prompts/CHAT_07_1_BME280_BASELINE_AND_RECOVERY_PROMPT_2026-10-25.md`; do not repeat completed setup or overwrite the user's external backup.


## Hardware status update — Chat 07.1, 2026-10-25

The user supplied debugger values showing `baseline_ok=1`, `fault_nack_observed=1`, `fault_result=-1`, `recovery_attempted=1`, `recovery_error=0`, `post_recovery_read_ok=1`, `post_recovery_chip_id=0x60`, `post_recovery_result=0`, and `test_state=3 (RECOVERY_PASSED)`. User screenshot showed a clean local build (0 errors, 0 warnings). Full report: `Plan2.0/results/CHAT_07_1_BME280_CONTROLLED_NACK_RECOVERY_2026-10-25.md`.

This is a narrow controlled address-NACK/reinitialization result with a fresh successful sensor transaction. It is not stuck-bus recovery and does not prove the protected reference runtime controlled the recovery policy. The next package is Chat 08 runtime-to-hardware integration, specified in `Plan2.0/prompts/CHAT_08_RUNTIME_HARDWARE_INTEGRATION_PROMPT_2026-10-25.md`. No protected source or frozen evidence should be modified.

## Plan 2.0 status update — Chat 10 planned (2026-10-25)

Chat 09 has closed the bounded Chat 08 P4 policy-to-BME280 hardware demonstration based on user-supplied CubeIDE evidence. Chat 10 is planned—not yet executed—as the final hardware-validation and evidence-closure phase. The same-run screenshots show controlled transaction-level NACK handling, attempted I²C1 reinitialization, a fresh BME280 chip-ID read of `0x60`, and terminal report code 8. They do not establish stuck-bus recovery, repeatability, MCU performance/memory measurements, or universal P4 superiority.

Follow [Plan2.0/CURRENT_STATE.md](Plan2.0/CURRENT_STATE.md) and [the Chat 10 prompt](Plan2.0/prompts/CHAT_10_FINAL_HARDWARE_VALIDATION_PROMPT_2026-10-25.md). Preserve all protected research artifacts and use `main` only. Chat 10 should prepare an evidence-backed Chat 11 handoff for real-time UI integration; it must not implement the UI or claim unperformed tests.


## Plan 2.0 Chat 10 status — 2026-10-25

Chat 10 has completed read-only source inspection and defined a five-total-trial protocol for the controlled NACK → P4-selected I2C1 reinitialization → fresh BME280 ID read → runtime release path. Trial 1 is the historical Chat 08 run, evidenced by the saved screenshots; Trials 2–5 are not yet performed. This GitHub-side audit did not compile, flash, reset, or operate hardware. No new flashing is approved.

See [Chat 10 validation report](Plan2.0/results/CHAT_10_FINAL_HARDWARE_VALIDATION_2026-10-25.md) and [Chat 11 UI integration prompt](Plan2.0/prompts/CHAT_11_REALTIME_UI_INTEGRATION_PROMPT_2026-10-25.md). Repeatability remains unverified until actual per-trial evidence is collected and reconciled. Existing research conclusions and frozen evidence remain unchanged.
