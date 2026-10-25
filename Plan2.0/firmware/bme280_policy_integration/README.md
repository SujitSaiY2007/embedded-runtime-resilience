# Chat 08 — BME280 policy-to-hardware integration candidate

**Status: user-evidenced target run completed; the GitHub-side audit did not independently build, flash, or execute the firmware.**

This candidate connects the protected C reference runtime's P4 decision function to the register-level STM32L476RG I²C adapter. It remains a separate firmware experiment and does not overwrite the LD2 GPIO experiment or frozen host/reference evidence.

## Files required in the CubeIDE project

- This `main.c`
- `reference/include/ref_runtime.h` (copy to the project's `Core/Inc`, or add `reference/include` to compiler include paths)
- `reference/src/ref_runtime.c` (copy to the project's `Core/Src`, or add the source directory to the project)

Do not replace or edit the protected reference files in the repository. Preserve the user's external backup of the prior `main.c`.

## Execution path

1. Initialize I²C1 and confirm BME280 chip ID `0x60` at address `0x76`.
2. Admit an exact peripheral-read event into a P4 runtime instance.
3. Attempt the controlled NACK at address `0x77`; proceed only when NACK is observed.
4. Start an exact-association `FAULT_I2C_NACK` episode.
5. Call `policy_decide()`. With retry disabled and reinitialization safe, P4 selects `ACT_REINIT_OR_RESET` (numeric value 2, reason code 23) for this source-defined context.
6. Execute the selected action using `i2c_recover()`, which resets/reinitializes the MCU's I²C1 peripheral. This is not physical stuck-bus recovery.
7. Require a fresh BME280 chip-ID read before `runtime_verify_and_release()` releases the quarantined event.

The integration intentionally does **not** call `runtime_apply_policy()`, because the existing function's retry/reinitialization branch models success rather than invoking a physical peripheral operation.

## Target run status and evidence

The user's saved CubeIDE screenshots reportedly show:
- build: 0 errors, 0 warnings;
- download: “Download verified successfully”;
- `baseline_ok=1`, `fault_attempted=1`, `fault_nack_observed=1`, `recovery_attempted=1`;
- `post_recovery_read_ok=1`, `post_recovery_chip_id=0x60`, `sensor_error=0`;
- `test_state=3`, `test_finished=1`, `test_report_code=8`;
- debugger stopped at the terminal report breakpoint.

Detailed audit and evidence classification: [Chat 09 hardware evidence reconciliation](../../results/CHAT_09_HARDWARE_EVIDENCE_RECONCILIATION_2026-10-25.md). The screenshots/handoff summary do not include the auxiliary policy/runtime fields listed below; those are **not captured in the available evidence summary**. Do not report expected values as measured.

## Auxiliary debugger values (useful if already available, not a new run requirement)

The following are source-derived expectations, not confirmed screenshot observations:
- `policy_variant = 4` (`VAR_P4_INTEGRATED`)
- `policy_event_admit_result = 1` and `policy_fault_start_result = 1` (`OUTCOME_SUCCESS`)
- `policy_decision_action = 2` (`ACT_REINIT_OR_RESET`)
- `policy_decision_reason = 23`
- `policy_action_attempted = 1`
- `hardware_action_result = 0`
- `policy_release_result = 1` (`OUTCOME_SUCCESS`)
- `policy_event_slot`, `policy_event_generation`, `policy_runtime_bytes`, and `policy_runtime_trace_count`: exact values must be read from the debugger, not inferred here.

If desired, inspect the saved terminal debugger session/variable view only. Do not rerun baseline/NACK testing solely to populate this list, and do not flash again without a source change, clean build, and explicit user approval.

## Scope limitation

One controlled transaction-level NACK → I²C1 peripheral reinitialization → fresh chip-ID read → runtime release is user-evidenced. No physically stuck SDA/SCL bus, repeated-run reliability, full environmental measurement, MCU timing/stack/energy measurement, or universal P4 superiority is demonstrated. The GitHub-side audit did not run CubeIDE or hardware, and the frozen 400-execution host/reference campaign remains separate and unchanged.


## Chat 10 repeatability protocol — 2026-10-25

The user selected five total trials. The historical Chat 08 run is designated Trial 1; the two screenshots are complementary evidence from that same run. Trials 2–5 remain pending. The source is a one-shot test that halts at `__BKPT(0)` and then loops, so a repeated trial requires starting the same unchanged programmed image from reset. A new flash is not inherently necessary when the same image is already programmed, but its binary identity has not been independently verified by this audit.

For each trial capture the baseline, controlled NACK, recovery action/result, fresh post-recovery chip ID, runtime release result and terminal state/report code. Required pass criteria and the full ledger are in [Chat 10 final hardware validation](../../results/CHAT_10_FINAL_HARDWARE_VALIDATION_2026-10-25.md). Do not infer auxiliary fields from source. Do not flash without source/build review, a clean build and explicit user approval. This documentation update did not run CubeIDE or hardware.


## Five-policy diagnostic run — 2026-10-25

A separate diagnostic candidate is preserved at [`embedded_runtime_five_policy_matrix_diagnostic.c`](embedded_runtime_five_policy_matrix_diagnostic.c). User-provided CubeIDE screenshots show a terminal state with `progress_stage=900`, `finished=1`, `overall_code=1`. The observed baseline error slots were zero; `nack_result[0..4]=-1` matched the source-defined `E_NACK`. Physical statuses P0–P4 were 7,1,7,7,1, corresponding to `R_TERMINAL`, `R_PASS`, `R_TERMINAL`, `R_TERMINAL`, `R_PASS`. For P1 and P4, the screenshots show `post_read_ok=1`, `post_chip_id=96 (0x60)`, and `release_result=1`.

This is one controlled wrong-address NACK → I²C1 peripheral recovery/reinitialization → fresh BME280 ID read → runtime release run. It does not prove physically stuck SDA/SCL recovery, repeated-run reliability, MCU timing/stack/Flash/RAM/energy, or universal P4 superiority. The 80 embedded runtime decisions (5 policies × 16 provisional contexts) are not 80 physical fault injections and are not proven identical to the frozen host case families.

**Matrix evidence caveat:** one screenshot shows `matrix_status[79]=1`, while the user later stated all matrix statuses were 1 except the last. No complete readable export of all 80 entries is present in this report, so the discrepancy remains unresolved. Do not assert a full-array audit from the aggregate `overall_code=1` alone.

See [Chat 11 diagnostic report](../../results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md). This GitHub update did not compile, flash, or execute the candidate.
