# Chat 08 — BME280 policy-to-hardware integration candidate

**Status: source prepared; target build and hardware execution not yet verified.**

This candidate connects the protected C reference runtime's P4 decision function to the existing register-level STM32L476RG I2C adapter. It is deliberately a separate firmware experiment and does not overwrite the LD2 GPIO experiment or any frozen host/reference evidence.

## Files required in the CubeIDE project

- This `main.c`
- `reference/include/ref_runtime.h` (copy to the project's `Core/Inc`, or add `reference/include` to compiler include paths)
- `reference/src/ref_runtime.c` (copy to the project's `Core/Src`, or add the source directory to the project)

Do not replace or edit the protected reference files in the repository. If copying them locally, preserve the originals and keep the user's external backup of the prior `main.c`.

## Execution path

1. Initialize I2C1 and confirm BME280 chip ID `0x60` at address `0x76`.
2. Admit an exact peripheral-read event into a P4 runtime instance.
3. Attempt the existing controlled NACK at address `0x77`; proceed only when NACK is actually observed.
4. Start an exact-association `FAULT_I2C_NACK` episode.
5. Call `policy_decide()`. With retry disabled and reinitialization safe, P4 is expected to select `ACT_REINIT_OR_RESET` (numeric value 2, reason code 23).
6. The selected action invokes the real `i2c_recover()` peripheral reinitialization.
7. A fresh BME280 chip-ID read must pass before `runtime_verify_and_release()` releases the quarantined event.

The integration intentionally does **not** call `runtime_apply_policy()`, because that function's existing retry/reinitialization branch simulates success rather than invoking a physical peripheral operation.

## Debugger acceptance values

After a successful target run, inspect:

- `baseline_ok = 1`
- `fault_nack_observed = 1`
- `policy_variant = 4` (`VAR_P4_INTEGRATED`)
- `policy_event_admit_result = 1` and `policy_fault_start_result = 1` (`OUTCOME_SUCCESS`)
- `policy_decision_action = 2` (`ACT_REINIT_OR_RESET`)
- `policy_decision_reason = 23`
- `hardware_action_result = 0`
- `post_recovery_read_ok = 1`
- `post_recovery_chip_id = 0x60`
- `policy_release_result = 1` (`OUTCOME_SUCCESS`)
- `test_state = 3` (`RECOVERY_PASSED`)

Also record `policy_runtime_bytes`, `policy_runtime_trace_count`, and the CubeIDE build warnings/errors. These values are expected acceptance criteria, not results already observed.

## Validation boundary

No STM32 cross-compiler build, flash, or physical test was run by the repository update. The user must first build this separate candidate in CubeIDE. Do not flash until the build is clean and the user explicitly approves. A successful controlled address-NACK/reinitialization test does not prove recovery from a physically stuck I2C bus, and the existing 400-run host campaign remains untouched.
