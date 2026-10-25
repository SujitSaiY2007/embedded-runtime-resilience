# Plan 2.0 — Reference Overhaul + Hardware Demonstration

**Status:** Active planning and execution framework  
**Control branch:** `main` only  
**Repository:** [embedded-runtime-resilience](https://github.com/SujitSaiY2007/embedded-runtime-resilience)

## Purpose

Plan 2.0 begins the next phase after the software/reference-model demonstrator: conduct a defensible, source-verified literature and reference overhaul, and build and validate a physical hardware demonstrator without misrepresenting host-model results as MCU evidence.

## Non-negotiable rules

1. **Work only on `main`.** Do not create, switch to, merge from, or write to any other branch for Plan 2.0.
2. **Preserve existing work.** Do not overwrite or delete the protected C reference runtime, tests, frozen experimental results, Gate A–E contracts, prior-art analyses, or dated research records.
3. **Archive, do not discard.** A historical snapshot of pre-Plan-2.0 non-code documentation and preliminary reference material is retained under `archive/legacy_snapshot/`. Original paths remain intact during setup so history and links are not lost.
4. **No unsupported claims.** The current 400-run campaign is deterministic host/reference-model evidence. It is not physical MCU evidence and does not prove universal P4 superiority, legal novelty, non-obviousness, or patentability.
5. **Trace every source.** Do not claim a baseline was copied from a paper unless the specific source and design relationship are verified.
6. **Evidence before closure.** Record actual commands, toolchain/board versions, raw traces, configuration, commit SHA, and test outcomes. Distinguish user-reported checks from independently reproduced checks.

## Start here

1. [Current state and branch rules](CURRENT_STATE.md)
2. [Execution roadmap and chat sequence](EXECUTION_ROADMAP.md)
3. [Reference overhaul protocol](REFERENCE_OVERHAUL.md)
4. [Hardware demonstration plan](HARDWARE_DEMONSTRATION.md)
5. [Multi-chat continuity protocol](CHAT_PROTOCOL.md)
6. [Chat 00 — initialization and next-chat handoff](CHAT_00_INITIALIZATION.md)
7. [Chat 05 hardware compatibility audit](hardware/CHAT_05_HARDWARE_COMPATIBILITY_AUDIT.md)
8. [Chat 05.2 — detailed hardware bring-up prompt](prompts/CHAT_05_2_ZERO_BUDGET_HARDWARE_BRINGUP_PROMPT.md)
9. [Chat 05.2 handoff — paused at ST-LINK initialization](handoffs/CHAT_05_2_HANDOFF.md)
10. [Chat 05.3 — ST-LINK debugger continuation prompt](prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md)
11. [Chat 05.3 — bounded diagnosis handoff](handoffs/CHAT_05_3_HANDOFF.md)
12. [Archive index](../archive/README.md)

## Definition of done

- Verified, high-quality bibliography with publication-type and source-quality classifications, DOI/metadata checks, and source-to-design traceability.
- Revised literature review and novelty/gap analysis with claims proportionate to evidence.
- Safe, reproducible physical demonstration using the actual board and documented peripheral setup.
- MCU-specific measurements and raw artifacts, clearly separated from host-model results.
- Updated top-level README, project state, decision log, and next-chat handoff.
- Every chat closes with an evidence-backed handoff so the next chat can continue without rediscovery.


## Latest milestone — Chat 07.1 (2026-10-25)

User-supplied CubeIDE evidence confirms a controlled address-NACK attempt, I²C1 reinitialization, and a fresh successful BME280 chip-ID read (`0x60`), ending at `test_state=3 (RECOVERY_PASSED)`. This is narrowly scoped peripheral-reinitialization evidence; it is not physically stuck-bus recovery or proof that the full reference runtime controlled the policy decision.

- [Chat 07.1 result report](results/CHAT_07_1_BME280_CONTROLLED_NACK_RECOVERY_2026-10-25.md)
- [Chat 08 runtime-to-hardware integration prompt](prompts/CHAT_08_RUNTIME_HARDWARE_INTEGRATION_PROMPT_2026-10-25.md)

Chat 08 begins by inspecting runtime interfaces and defining the safe integration/fault model. Do not repeat completed tests or alter protected assets.


## Latest milestone — Chat 08 source candidate (2026-10-25)

A separate candidate now connects the P4 reference runtime decision to the real I2C1 reinitialization adapter and requires a fresh BME280 chip-ID read before event release. **This source is prepared but not yet build- or hardware-verified.**

- [Chat 08 integration candidate source](firmware/bme280_policy_integration/main.c)
- [Build and debugger acceptance checklist](firmware/bme280_policy_integration/README.md)
- [Chat 08 evidence-boundary report](results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md)

Next action: build the candidate in the existing CubeIDE project using the protected reference header/source. Do not flash until the build is clean and the user explicitly approves. Previous LD2 and Chat 07.1 evidence remain separate; frozen host/reference evidence is untouched.

## Latest hardware milestone — Chat 08 (2026-10-25)

The user-provided CubeIDE screenshots show the P4-integrated BME280 test completed with `test_finished=1`, `test_report_code=8`, `test_state=3`, successful controlled NACK observation and a fresh post-recovery chip-ID read of `0x60`. This demonstrates one transaction-level NACK recovery run, not physically stuck-bus recovery or statistical superiority. See the [Chat 08 result record](results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md). The next work package is Chat 09 evidence reconciliation and handoff.


## Chat 10 — current status (2026-10-25)

Chat 10 has audited the current P4/BME280 firmware source and defined the five-total-trial procedure. The existing Chat 08 run is Trial 1; its two screenshots document the same run. Trials 2–5 remain pending. No new build, flash, reset, or physical trial was performed by the GitHub-side audit. Do not flash unless the user explicitly approves after source/build review and a clean build.

- [Chat 10 final hardware validation and trial ledger](results/CHAT_10_FINAL_HARDWARE_VALIDATION_2026-10-25.md)
- [Chat 11 real-time UI integration prompt](prompts/CHAT_11_REALTIME_UI_INTEGRATION_PROMPT_2026-10-25.md)

Repeatability, MCU timing/resource measurements, physical stuck-bus recovery and P0–P4 hardware comparison remain unverified. Chat 11 must verify the real firmware-to-host transport and transmitted bytes before showing live hardware telemetry; simulated data must remain clearly labeled.


## Current status — 2026-10-25: bounded hardware run complete; manuscript next

The latest user-provided five-policy diagnostic run reached `progress_stage=900`, `finished=1`, `overall_code=1`. Baseline error slots were zero, all five controlled wrong-address reads returned `E_NACK=-1`, and P1/P4 achieved post-recovery BME280 ID `0x60` plus successful release results. P0/P2/P3 reached `R_TERMINAL`. The detailed evidence and limitations are in [Chat 11 diagnostic hardware report](results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md).

The matrix is 5 policies × 16 provisional runtime contexts; it is not 80 physical fault injections and is not established as identical to the frozen 400-execution host corpus. The complete `matrix_status[0..79]` array has not been independently captured as a readable export; a user statement about the last entry conflicts with a screenshot showing `matrix_status[79]=1`.

**Next:** use [Claude's journal manuscript prompt](../research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md) to audit the full repository, verify the bibliography and claims, and draft the paper. Preserve all frozen host evidence and protected runtime files.
