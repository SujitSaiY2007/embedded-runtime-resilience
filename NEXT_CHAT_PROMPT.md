# Next Chat Prompt — Chat 08: P4 Policy-to-BME280 Hardware Integration

The current working BME280 `main.c` has been supplied and a separate integration candidate is already committed. Do not ask the user to upload the source again and do not repeat completed baseline/NACK experiments.

**Authoritative prompt:** [Chat 08 runtime-to-hardware integration](Plan2.0/prompts/CHAT_08_RUNTIME_HARDWARE_INTEGRATION_PROMPT_2026-10-25.md)

## Current source and status

- Candidate: [`Plan2.0/firmware/bme280_policy_integration/main.c`](Plan2.0/firmware/bme280_policy_integration/main.c)
- Build and acceptance steps: [candidate README](Plan2.0/firmware/bme280_policy_integration/README.md)
- Candidate report: [Chat 08 result record](Plan2.0/results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md)
- Previous peripheral test: [Chat 07.1 controlled-NACK result](Plan2.0/results/CHAT_07_1_BME280_CONTROLLED_NACK_RECOVERY_2026-10-25.md)
- Board: ST NUCLEO-L476RG, STM32L476RG; BME280 address `0x76`, expected chip ID `0x60`; PB8/PB9 are I2C1 SCL/SDA.

## Immediate task

1. Preserve the current local CubeIDE source and external backup.
2. Place the candidate `main.c` in the existing CubeIDE project's application source location.
3. Add the unchanged `reference/include/ref_runtime.h` and `reference/src/ref_runtime.c` to the local CubeIDE project.
4. Perform a clean build. If it fails, request the first relevant compiler/linker errors and fix the candidate without editing protected reference runtime files.
5. Do **not** flash until the build is clean. Then state exactly what will be programmed and obtain explicit user approval.
6. After approval, flash/run and collect debugger evidence.

## Acceptance values (expected, not yet observed)

- `baseline_ok=1`, `fault_nack_observed=1`
- `policy_variant=4` (`VAR_P4_INTEGRATED`)
- `policy_event_admit_result=1`, `policy_fault_start_result=1`
- `policy_decision_action=2` (`ACT_REINIT_OR_RESET`), `policy_decision_reason=23`
- `hardware_action_result=0`
- `post_recovery_read_ok=1`, `post_recovery_chip_id=0x60`
- `policy_release_result=1`, `test_state=3`
- Record build warnings/errors, `policy_runtime_bytes`, and `policy_runtime_trace_count`.

## Protected boundaries

Work on `main` only. Do not modify `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen 400-execution evidence, prior-art reviews, manuscript, or the separate LD2 experiment. The previous Chat 07.1 screenshot is not evidence for this new policy-driven candidate. Do not claim physical stuck-bus recovery or MCU performance measurements.