# Chat 08 — BME280 policy-to-hardware integration candidate

**Date:** 2026-10-25  
**Branch:** `main`  
**Status:** Candidate source prepared; local target build and hardware execution pending.

## Goal

Move beyond the already demonstrated controlled-NACK/reinitialization test by connecting the C reference runtime's actual P4 policy decision to the STM32L476RG I2C hardware action, while preserving the protected reference implementation and previous experiment.

## Source created

- Firmware candidate: [`firmware/bme280_policy_integration/main.c`](../firmware/bme280_policy_integration/main.c)
- Build and acceptance notes: [`firmware/bme280_policy_integration/README.md`](../firmware/bme280_policy_integration/README.md)
- Runtime interface: `reference/include/ref_runtime.h`
- Runtime implementation: `reference/src/ref_runtime.c`

## Integration path in the candidate

1. Initialize I2C1 and verify BME280 chip ID `0x60` at address `0x76`.
2. Admit an exact peripheral-read event to `Runtime` using `VAR_P4_INTEGRATED`.
3. Apply the existing controlled NACK stimulus at `0x77`; proceed only if the I2C peripheral reports `ERR_NACK`.
4. Start an exact-association `FAULT_I2C_NACK` episode with retry disabled and reinitialization marked safe.
5. Call `policy_decide()`. Expected selection for this context: `ACT_REINIT_OR_RESET` (value 2, reason code 23).
6. Execute the selected action through the real `i2c_recover()` adapter.
7. Perform a fresh physical BME280 chip-ID read. Only on success set event verification/shared-state flags and call `runtime_verify_and_release()`.

The candidate deliberately does not use `runtime_apply_policy()` to claim physical recovery: its existing reinitialization path simulates success and does not operate the peripheral.

## Evidence variables added

`policy_variant`, `policy_event_admit_result`, `policy_fault_start_result`, `policy_decision_action`, `policy_decision_reason`, `policy_action_attempted`, `hardware_action_result`, `policy_release_result`, `policy_runtime_bytes`, `policy_runtime_trace_count`, `policy_event_slot`, and `policy_event_generation`.

## Acceptance criteria (not yet observed)

- `baseline_ok=1`, `fault_nack_observed=1`
- `policy_variant=4`
- `policy_event_admit_result=1`, `policy_fault_start_result=1`
- `policy_decision_action=2`, `policy_decision_reason=23`
- `hardware_action_result=0`
- `post_recovery_read_ok=1`, `post_recovery_chip_id=0x60`
- `policy_release_result=1`, `test_state=3`
- Clean CubeIDE build, with RAM/static runtime size recorded.

## Validation and evidence boundary

The source was assembled from the user-supplied working BME280 `main.c` and the live reference runtime interface. Repository files were updated on `main`; no other branch was created. The repository connector did not run the STM32 cross-compiler, CubeIDE, a flash operation, or a hardware test. The candidate is therefore **not yet build-verified or hardware-verified**.

The prior user-provided Chat 07.1 screenshot remains the evidence for the previous non-policy-driven NACK/reinitialization test. Do not treat it as evidence for this candidate. Preserve the LD2 GPIO experiment, the user's external `main.c` backup, protected reference files, Gate A–E contracts, and the frozen 400-execution campaign. Do not claim physically stuck-bus recovery or MCU performance measurements.
