# Chat 05.3 — First On-Board GPIO Recovery Experiment

**Date:** 2026-10-24  
**Repository:** SujitSaiY2007/embedded-runtime-resilience  
**Documentation branch:** `main` only  
**Target shown by prior user evidence:** ST NUCLEO-L476RG, STM32L476RG, board revision MB1136 C  
**Outcome:** **PASS for the narrow software-injected GPIO configuration experiment; broader hardware validation remains incomplete.**

## Objective

Continue from the ST-LINK/GDB initialization blocker, establish a working CubeIDE debug session, and run a minimal software-controlled GPIO fault-injection/recovery check on the onboard green user LED LD2 (PA5).

## Evidence reported by the user

- The local STM32CubeIDE project `Embedded-Runtime-Resilience` built with **0 errors, 0 warnings** after the backup C file was excluded from the Debug build.
- The firmware download console showed **“Download verified successfully.”**
- A subsequent live debug session paused in `main()` at the final infinite loop, after the test code had executed.
- The Expressions view showed all eight expected values:

| Expression | Observed | Interpretation |
|---|---:|---|
| `test_event_count` | 1 | One event recorded |
| `test_fault_count` | 1 | One fault reported |
| `test_recovery_count` | 1 | One recovery action passed the software checks |
| `test_state` | 4 | `ERR_STATE_RECOVERED` |
| `test_recovered` | 1 | Recovery function returned true |
| `test_fault_injected` | 1 | Software fault-injection step executed |
| `test_gpio_mode` | 1 | PA5 MODER bits indicate general-purpose output mode |
| `test_gpio_output` | 1 | PA5 output data latch reads high |

- The user also observed LD1 status-LED activity and LD2 eventually illuminated green. LED behavior is user-observed and is not treated as a photometric or electrical measurement.

## Experiment sequence

1. Initialize the runtime status.
2. Enable the GPIOA clock.
3. Configure PA5 as output and set its output latch low.
4. Inject a software-controlled configuration fault by changing PA5 to input mode.
5. Report one fault using peripheral ID `1U`.
6. Attempt recovery: restore PA5 output mode, write the GPIO set register to drive PA5 high, and read back the mode bits and output latch.
7. Return success and increment the recovery count only when both register checks pass.
8. Capture the final runtime and GPIO values for debugger inspection.

The implementation has a three-attempt loop, but this observed successful run only establishes that the first successful pass completed; it does not measure worst-case timing or demonstrate all retry/failure paths.

## What this result establishes

- The user successfully built and programmed the local STM32CubeIDE project and obtained a live debugger stop after the test sequence.
- The software-injected PA5 configuration fault was followed by a recovery action.
- The observed register checks and runtime state matched the expected successful path.

## Explicit limits

- This is **not** a physical peripheral-damage experiment. The fault is a software-induced change to GPIO configuration.
- The register readback verifies the GPIO mode and output data latch; it does not independently verify voltage at the pin, LED optical output, or electrical recovery from hardware failure.
- The test uses a direct register-level implementation in the local generated CubeIDE workspace. That local project is not yet asserted to be the canonical, version-controlled firmware implementation in this repository.
- No sensor has been wired or read. No sensor-baseline test, repeated-trial study, MCU timing/stack/energy measurement, or comparison against the frozen P0–P4 host/reference campaign was performed.
- The NUCLEO-L476RG / STM32L476RG target remains distinct from the earlier proposed NUCLEO-U575ZI-Q / STM32U575ZI platform. This result does not resolve target-equivalence or MPU/security requirements.

## Provenance

The build, download, debugger and Expressions results above are based on screenshots supplied by the user on 2026-10-24. They were not run by the GitHub repository connector or independently reproduced by CI. The connector was used only to update repository documentation.

## Next acceptance gate

1. Preserve the local working firmware and its verified backup.
2. Reconcile the local firmware with the canonical repository before treating it as a maintained project artifact; do not copy generated startup/linker files or replace the protected C reference runtime.
3. Create a reproducible Chat 06 minimal-firmware scaffold record and document the build/download/debug procedure and exact project-source provenance.
4. Only after that baseline is stable, proceed to Chat 07 peripheral/sensor compatibility and baseline reads. Do not wire the BME280-labelled module until its exact marking, pinout, supply/logic levels and pull-up requirements are verified and the wiring plan is reviewed.
5. Chat 08 remains the broader controlled-fault/recovery stage; this single GPIO configuration test is an initial narrow milestone, not completion of that entire stage.
