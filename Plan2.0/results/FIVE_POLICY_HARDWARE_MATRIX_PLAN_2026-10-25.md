# Unified Five-Policy Hardware/Runtime Matrix — Candidate Review

**Date:** 2026-10-25  
**Branch:** `main`  
**Status:** Candidate source committed; NOT compiled or hardware-validated. Do not flash until reviewed and built cleanly.

## Candidate source

[`embedded_runtime_five_policy_matrix.c`](../firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix.c)

The existing `main.c`, protected runtime source/header, frozen host campaign, and historical evidence remain unchanged.

## What this candidate attempts

1. Runs a common physical BME280 baseline + controlled address-NACK scenario sequentially under P0, P1, P2, P3 and P4, using the actual `ref_runtime` policy API.
2. Runs 80 in-firmware policy-decision evaluations (5 policies × 16 explicitly listed runtime contexts) through the real `policy_decide()` implementation.
3. Exposes per-row volatile debugger arrays for physical results and matrix decisions, then stops at one final breakpoint.
4. Uses bounded retries of the deliberately absent I²C address; it never intentionally shorts SDA/SCL or claims stuck-bus recovery.

## Crucial scope distinction

The 16 rows in this candidate are a **provisional context matrix**, derived from the enums and context flags in `reference/include/ref_runtime.h`. They have NOT yet been reconciled against the exact frozen host campaign's 16 case-family definitions. Therefore:
- Do not describe this as reproducing the frozen 400-execution campaign.
- The physical portion tests one physical fault class (controlled I²C address NACK) under each policy.
- The 80 matrix rows test runtime decisions inside firmware; they are not 80 physical fault injections.
- SPI and software-service cases in the runtime matrix are policy-context evaluations, not physical SPI/service tests.
- No conclusion of universal P4 superiority is supported by this candidate alone.

## Required pre-build review

1. Compare each of the 16 `ScenarioSpec` rows against the frozen host case corpus and replace provisional rows with exact scenario definitions/IDs. Preserve a clear mapping if any scenario cannot be reproduced.
2. Audit policy semantics: retry loops deliberately retry the absent address and increment episode counters to evaluate the next decision. Confirm this matches the intended baseline semantics and do not call it a retry of the actual BME280 operation.
3. Audit the physical result taxonomy and all early exits so every policy row has a clear classified outcome.
4. Build in the user's actual STM32CubeIDE project with the protected reference runtime, only one active `main()`, and inspect all warnings/errors.
5. Review stack/static RAM impact before flashing. The reference `Runtime` contains a large trace buffer; this harness uses one static runtime and several result arrays.
6. Only after clean build and user approval, download to the board. No flash is authorized by this commit.

## Wiring and test safety

Use the existing verified wiring only: BME280 3V3/GND and PB8/PB9 I²C. No deliberate shorting or external forced line states. Baseline timeout is recorded as a failure; do not silently retry within a row.

## Output arrays

Physical rows: `physical_status[]`, `physical_baseline_ok[]`, `physical_nack_observed[]`, `physical_first_action[]`, `physical_first_reason[]`, `physical_retry_count[]`, `physical_reinit_attempted[]`, `physical_reinit_result[]`, `physical_post_read_ok[]`, `physical_post_chip_id[]`, `physical_release_result[]`.

Runtime matrix: `matrix_status[]`, `matrix_policy[]`, `matrix_scenario[]`, `matrix_fault[]`, `matrix_assoc[]`, `matrix_action[]`, `matrix_reason[]`, `matrix_terminal[]`, `matrix_retry_authorized[]`.

Flat matrix index is `policy_index * 16 + scenario_index). A recorded matrix row means the decision was captured, not that a hardware recovery succeeded.

## Preservation

- Continue using `main` as the working branch; preserve `exp` as frozen reference.
- Do not change protected `reference/include/ref_runtime.h` or `reference/src/ref_runtime.c`.
- Do not modify frozen 400-execution evidence or retroactively rewrite previous screenshots/results.
- This documentation and source commit did not compile, flash, reset, or execute hardware.
