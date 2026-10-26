# Phase 2 Hardware Validation Closure

Date: 2026-10-26
Target: ST NUCLEO-L476RG (STM32L476RG), BME280 at I2C address 0x76
Status: **Hardware validation phase closed with bounded findings and documented limitations. No further runs planned.**

## 1. Scope and evidence provenance

This closure is based on the user's STM32CubeIDE build/debugger screenshots and reported debugger values in the project conversation. The committed diagnostic source is `Plan2.0/firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix_diagnostic.c`, and the protected runtime enum is in `reference/include/ref_runtime.h`. These map physical status 7 to `R_TERMINAL`, physical status 1 to `R_PASS`, and `runtime_result=4` to `OUTCOME_TERMINAL_ESCALATE`. The exact modified control-trial source used in CubeIDE is not separately committed or hash-linked to the flashed ELF/binary, so source-to-binary identity remains unverified. The exact flashed ELF/binary hash is not available; source-to-binary identity remains unverified.

The build screenshot reports a successful build with 0 errors and 0 warnings. Linker size output reported text=12,948 bytes, data=112 bytes, BSS=12,704 bytes, total=25,764 bytes. These are build/linker figures, not runtime stack usage, recovery latency, energy, or a complete MCU resource profile.

## 2. No-full-reinitialization controlled NACK

The control trial results reported by the debugger were:

| Trial index | NACK result | NACK observed | Post-NACK read OK | Chip ID |
|---:|---:|---:|---:|---:|
| 0 | -1 | 1 | 1 | 96 (0x60) |
| 1 | -1 | 1 | 1 | 96 (0x60) |
| 2 | -1 | 1 | 1 | 96 (0x60) |
| 3 | -1 | 1 | 1 | 96 (0x60) |
| 4 | -1 | 1 | 1 | 96 (0x60) |

The user-reported enum mapping identifies -1 as `E_NACK`. All five control trials observed the intended NACK and then read the expected BME280 chip ID (0x60) without invoking the full `iinit()` routine between the NACK probe and the subsequent read.

Interpretation: for this specific absent-address NACK scenario, the experiment supports that a full peripheral initialization call was not necessary to obtain a successful subsequent sensor read in the tested setup. The existing transaction helper may perform local transaction-abort/flag handling; this is not a test of leaving all peripheral state untouched.

## 3. Policy-specific physical run

Reported debugger values:

| Policy | Index | Physical status | Runtime result | Release result | Post-read chip ID | Interpretation supported by observed values |
|---|---:|---:|---:|---:|---:|---|
| P0 | 0 | 7 | 4 | 0 | 0 | Terminal/non-pass; no successful post-read recorded |
| P1 | 1 | 1 | 1 | 1 | 96 (0x60) | Harness pass; successful release and post-read |
| P2 | 2 | 7 | 4 | 0 | 0 | Terminal/non-pass; no successful post-read recorded |
| P3 | 3 | 7 | 4 | 0 | 0 | Terminal/non-pass; no successful post-read recorded |
| P4 | 4 | 1 | 1 | 1 | 96 (0x60) | Harness pass; successful release and post-read |

All five `baseline_ok` entries were reported as 1. The policy NACK-observation and reinitialization arrays were not fully shown in the final combined screenshot. The committed `OutcomeCode` enum maps numeric `runtime_result=4` to `OUTCOME_TERMINAL_ESCALATE`; the policy harness separately records `physical_status=7` as `R_TERMINAL`. The three terminal results are consistent with terminal policy decisions, not evidence of a processor crash.

The policy outcome is therefore mixed: P1 and P4 passed this harness run, while P0, P2, and P3 produced terminal/non-pass results. This is one policy-specific run, not five independent physical repetitions per policy.

## 4. Policy-decision matrix

The debugger showed sampled `matrix_status` entries 0, 15, 16, 31, 32, 47, 48, 63, 64 and 79 equal to 1. Entry 79 was reported as action=4, reason=19, terminal=1, retry_authorized=0, runtime_start=1.

This confirms the displayed entries were recorded; it is not a complete independently captured 80-element export and must not be described as 80 physical fault injections.

## 5. Conclusions supported by this phase

1. The firmware built successfully in STM32CubeIDE with 0 errors and 0 warnings.
2. Five controlled wrong-address NACK trials were followed by successful BME280 chip-ID reads without a full `iinit()` between the NACK and read.
3. In the observed policy run, P1 and P4 passed the harness and read back chip ID 0x60; P0, P2 and P3 ended in terminal/non-pass outcomes without successful post-read IDs.
4. The sampled policy-decision matrix entries were recorded, including index 79.
5. Linker size output is available, but runtime stack usage, measured recovery latency, energy, and a complete MCU resource profile were not measured.

## 6. Explicit limitations

- No physical stuck-SDA or stuck-SCL bus fault was tested.
- No claim is made that full reinitialization is unnecessary for faults other than this controlled address NACK.
- The no-full-reinitialization control does not isolate every low-level transaction cleanup operation.
- There were not five independent firmware runs per policy; the five controls are trials within one firmware execution, and the five policy slots are a single policy comparison run.
- Exact flashed binary identity is not hash-linked to the source.
- The complete 80-entry matrix was not exported as a readable record.
- The exact enum-name mapping for numeric `runtime_result=4` could not be verified from a committed hardware source file during this review.
- The outcomes do not establish universal P4 superiority, broad physical fault coverage, or statistical reliability.

## 7. Phase decision

**Phase 2 is closed for the planned scope, with the limitations above retained in the manuscript. No further hardware runs are planned at this stage.** Manuscript claims must remain bounded to the observed controlled-NACK scenario and the single policy-specific physical run. Any future extension to stuck-bus faults, repeated independent policy trials, target resource profiling, or binary provenance is future work, not completed evidence.
