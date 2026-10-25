# Chat 08 — BME280 policy-to-hardware integration

**Date:** 2026-10-25  
**Branch:** `main`  
**Status:** **Hardware run completed successfully according to user-provided CubeIDE debugger screenshots.**

## Goal

Connect the C reference runtime's P4 policy decision to a physical BME280 transaction on the STM32L476RG, without modifying the protected reference runtime or replacing frozen host evidence.

## Firmware and build

- Candidate: [`Plan2.0/firmware/bme280_policy_integration/main.c`](../firmware/bme280_policy_integration/main.c)
- Build completed with **0 errors and 0 warnings**, per user-provided CubeIDE build output.
- Firmware download and verification completed successfully, per user-provided CubeIDE debugger screenshots.
- Test reporting uses debugger-visible variables and a terminal breakpoint; it does not depend on semihosting console output.

## Observed debugger evidence

The user-provided terminal debugger screenshot showed:

| Variable | Observed value | Interpretation |
|---|---:|---|
| `baseline_ok` | 1 | Initial BME280 read succeeded |
| `fault_attempted` | 1 | Controlled fault was attempted |
| `fault_nack_observed` | 1 | Controlled NACK was observed |
| `recovery_attempted` | 1 | Recovery path was attempted |
| `post_recovery_read_ok` | 1 | Fresh post-recovery read succeeded |
| `post_recovery_chip_id` | 96 (`0x60`) | Expected BME280 chip ID |
| `sensor_error` | 0 | No sensor error at terminal result |
| `test_state` | 3 | Recovery test passed |
| `test_finished` | 1 | Terminal report reached |
| `test_report_code` | 8 | Success report |

The debugger halted at the reporting breakpoint. The screenshots have been saved by the user.

## What this demonstrates

The observed run completed the baseline read, controlled transaction-level NACK, recovery attempt, fresh sensor read and terminal success report on the physical NUCLEO-L476RG/BME280 setup. The board's BME280 address is `0x76`, expected chip ID `0x60`; I2C1 uses PB8/SCL (Arduino D15) and PB9/SDA (Arduino D14).

## Evidence boundaries

- This is one successful hardware demonstration run, based on the user's screenshots; it is not a repeated-trial reliability result.
- The stimulus was a controlled address-level NACK, not a physically stuck SCL/SDA bus.
- Do not claim universal P4 superiority, hardware performance gains, physical stuck-bus recovery, or MCU timing/memory measurements from this run.
- The screenshot values above do not by themselves record every runtime trace field. Chat 09 should capture the remaining policy decision/action/release/trace variables if they are available from the current firmware.
- Preserve the protected `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen 400-execution host evidence, prior-art analyses and manuscript.

## Chat 08 outcome

**The principal Chat 08 objective is achieved:** the P4-integrated firmware built, flashed, and completed the controlled NACK → hardware recovery → fresh BME280 verification path. Chat 09 should document and audit the evidence, reconcile runtime decision fields with the hardware action, and only then determine whether any additional narrowly scoped validation is necessary. Do not repeat the completed setup or baseline/NACK experiment without a specific evidence gap.

## Source and setup

- Candidate source: [`main.c`](../firmware/bme280_policy_integration/main.c)
- Candidate setup notes: [`README.md`](../firmware/bme280_policy_integration/README.md)
- Board: ST NUCLEO-L476RG, STM32L476RG
- Sensor: BME280 breakout, VIN to 3V3, GND to GND, SCL to PB8/D15, SDA to PB9/D14.
