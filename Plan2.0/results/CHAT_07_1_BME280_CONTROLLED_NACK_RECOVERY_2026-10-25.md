# Chat 07.1 — BME280 Controlled-NACK and I²C Reinitialization Result

**Date:** 2026-10-25  
**Board:** ST NUCLEO-L476RG, revision MB1136 C / STM32L476RG  
**IDE:** STM32CubeIDE 2.2.0  
**Branch:** `main`  
**Evidence provenance:** user-provided CubeIDE build and debugger screenshots in Chat 07.1.

## Outcome

**User-observed hardware test state: `RECOVERY_PASSED` (`test_state = 3`).**

The user reported the revised test built with **0 errors and 0 warnings**. After flashing/running under the debugger, the Expressions view showed:

| Variable | Observed value | Meaning |
|---|---:|---|
| `baseline_ok` | 1 | Initial sensor chip-ID read passed |
| `fault_attempted` | 1 | Controlled address-NACK attempt executed |
| `fault_nack_observed` | 1 | The expected NACK result was observed |
| `fault_result` | -1 | Test code's `ERR_NACK` |
| `recovery_attempted` | 1 | I²C reinitialization attempted |
| `recovery_error` | 0 | Reinitialization reported no error |
| `post_recovery_read_ok` | 1 | Fresh post-reinitialization read passed |
| `post_recovery_chip_id` | 96 (`0x60`) | Expected BME280 chip ID |
| `post_recovery_result` | 0 | Fresh read returned `ERR_NONE` |
| `sensor_address` | 118 (`0x76`) | Device address used for valid read |
| `sensor_chip_id` | 96 (`0x60`) | Baseline chip ID |
| `sensor_found` | 1 | Baseline sensor detection succeeded |
| `sensor_error` | 0 | No baseline error |
| `test_state` | 3 | `RECOVERY_PASSED` |

The debugger screenshot also showed the program at the final loop. Semihosting text was not visible in the console, but the debugger-visible variables were sufficient to inspect the outcome. A source change added the declaration for `initialise_monitor_handles()`; the user then reported a clean build. This repository report does not independently compile the local CubeIDE project or operate the board.

## What this demonstrates

The tested firmware:
1. completed a valid BME280 chip-ID read at address `0x76`, register `0xD0`;
2. attempted a transaction at address `0x77` and observed the test's expected NACK result (`-1`);
3. reset/reinitialized I²C1;
4. completed a **fresh** read from `0x76` returning `0x60`.

This is evidence for recovery of I²C communication after a controlled address-NACK transaction and peripheral reinitialization on this setup.

## Explicit limits

- This is not evidence of recovery from a physically stuck SDA/SCL line, sensor power loss, a damaged peripheral, or every I²C error class.
- The NACK stimulus is an address transaction to `0x77`; it is accepted only when the test observes the expected NACK. It is not equivalent to forcing a hardware line fault.
- The experiment does not yet show that the project's protected reference runtime or a full P0–P4 policy made the recovery decision. It is a firmware-level peripheral reinitialization test.
- No environmental temperature, pressure, or humidity conversion was measured.
- No repeated-trial statistics, latency, stack, energy, or worst-case recovery bounds were measured.
- STM32L476RG hardware does not establish equivalence to the earlier STM32U575 target requirements.
- Semihosting console reporting did not become visible. The observed result was read through debugger Expressions.
- The screenshots and build outcome are user-supplied evidence; GitHub tools did not run the local compiler, flash the board, or independently reproduce the experiment.

## Next acceptance gate

Chat 08 must inspect the actual runtime architecture and integration boundaries before changing firmware. Integrate the actual runtime decision/action path with the hardware adapter only after defining what can be reused, adapted, or must remain unchanged. Then define a safe fault model, bounded recovery action, and fresh post-recovery sensor operation. Preserve this report and the earlier LD2 and chip-ID reports unchanged.
