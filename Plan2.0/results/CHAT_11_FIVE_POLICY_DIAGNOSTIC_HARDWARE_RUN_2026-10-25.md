# Chat 11 — Five-Policy Diagnostic Hardware Run and Manuscript Handoff

**Date:** 2026-10-25  
**Branch:** `main`  
**Board reported by user:** ST NUCLEO-L476RG (MB1136 C), STM32L476RG  
**Sensor:** BME280, expected chip ID `0x60` at address `0x76`  
**Evidence provenance:** user-provided STM32CubeIDE debugger screenshots and source inspected on GitHub. The GitHub connector did not compile, flash, or operate the hardware.

## Executive result

The user ran the diagnostic five-policy harness and captured a terminal debugger state with `progress_stage=900`, `finished=1`, and `overall_code=1`. The harness's own status code says the run completed with valid physical outcomes and its matrix-completion criterion satisfied. This is a successful harness completion, but it must not be interpreted as all five policies achieving physical recovery: the per-policy outcomes differ, and the full `matrix_status[0..79]` array has not been independently captured as a complete list in the evidence available for this record.

## Captured values

| Field | Captured value | Interpretation / boundary |
|---|---:|---|
| `progress_stage` | 900 | Diagnostic harness reached its completion function. |
| `progress_policy` | 4 | Last tracked policy index is P4 (zero-based). |
| `progress_scenario` | 15 | Last tracked scenario index is 15 (zero-based). |
| `finished` | 1 | Harness marks itself finished before the terminal breakpoint. |
| `overall_code` | 1 | Harness's own success/completion code; not independent proof of every policy's physical recovery. |
| `baseline_error[0..4]` | all 0 in screenshot | All five baseline error slots are zero in the captured view. |
| `baseline_ok[0..4]` | all 1 in screenshot | All five baseline checks were shown as successful. |
| `nack_result[0..4]` | all -1 | Source defines `E_NACK=-1`; expected controlled NACK result. |
| `physical_status[0..4]` | 7, 1, 7, 7, 1 | Source enum: 7 = `R_TERMINAL`; 1 = `R_PASS`. P1 and P4 pass; P0/P2/P3 terminal. |
| `post_read_ok[1]`, `post_read_ok[4]` | 1, 1 | Post-recovery reads succeeded for P1 and P4 in the captured run. |
| `post_chip_id[1]`, `post_chip_id[4]` | 96, 96 | Decimal 96 = hexadecimal `0x60`, the expected BME280 ID. |
| `release_result[1]`, `release_result[4]` | 1, 1 | Release result reported successful for P1 and P4. |
| `matrix_reason[0]`, `matrix_reason[1]`, `matrix_reason[79]` | 1, 1, 19 | Selected matrix reason samples only; not a full-array audit. |
| `matrix_action[0]`, `matrix_action[1]`, `matrix_action[79]` | 1, 1, 4 | Selected matrix action samples only. |
| `matrix_status[79]` | 1 in the screenshot shown in the conversation | Source enum defines 1 = `M_RECORDED`. This is one entry, not proof by itself of all 80 entries. |

## Matrix-status discrepancy to preserve

The user subsequently stated that all matrix statuses were 1 except the last. However, the available screenshot in this conversation visibly shows `matrix_status[79] = 1`. These statements conflict or refer to different views/runs. The complete 80-element array was not supplied as a readable screenshot or exported log, so this record **does not assert** that all 80 values were 1 or that the last was different. Preserve the screenshots and resolve this only if a complete matrix audit is needed; do not rerun or overwrite frozen host evidence merely to repair a documentation ambiguity.

The harness defines `M_RECORDED=1`. Its header says `overall_code=1` means the run completed with valid physical outcomes and all 80 decisions recorded. This code-level aggregate is reported as observed, but a reviewer should distinguish it from an independent full-array inspection.

## What the physical experiment demonstrates

The firmware attempted a controlled I²C read at the intentionally wrong address `0x77`. The source assigns `nack_result[p]=x` and proceeds only when `x==E_NACK`; since the enum defines `E_NACK=-1`, the observed -1 values match the intended NACK branch. The physical sensor at `0x76` returned the expected ID `0x60` after the recovery path for P1 and P4, and their release results were 1.

This supports one user-observed controlled transaction-level NACK → I²C1 peripheral reinitialization/recovery path → fresh BME280 ID read → runtime release for P1 and P4 in this run. It does **not** demonstrate physically stuck SDA/SCL recovery, 80 physical fault injections, repeated-run reliability, MCU timing/stack/Flash/RAM/energy measurements, or universal P4 superiority.

## Relationship to frozen software evidence

The established host/reference campaign remains **16 case families × 5 policy variants × 5 repetitions = 400 executions**. Do not rerun, rewrite, or overwrite that frozen corpus. The firmware's 16 embedded contexts are explicitly described in source as provisional and not reconciled as identical to the frozen host case-family definitions. Therefore the 80 embedded runtime decisions must not be presented as a replication of the 400-run campaign without a separate mapping audit.

The hardware run is complementary evidence: it checks that a selected policy path can interact with a real BME280 via the STM32L476RG register-level adapter. It does not replace the frozen host campaign or make host-derived metrics into MCU measurements.

## Policy outcome summary

- **P0:** `R_TERMINAL` (7)
- **P1:** `R_PASS` (1), with post-read ID `0x60` and release result 1
- **P2:** `R_TERMINAL` (7)
- **P3:** `R_TERMINAL` (7)
- **P4:** `R_PASS` (1), with post-read ID `0x60` and release result 1

Do not describe terminal outcomes as successful sensor recovery. P1 and P4 reached the harness's physical pass state in this run; P0, P2, and P3 did not.

## Build and execution provenance

The user reported successful build/download and shared debugger values from the target session. The screenshots include “Download verified successfully” from the CubeIDE/ST-LINK workflow. This GitHub-side documentation pass did not run the local compiler, CubeIDE, debugger, or hardware, so the results remain user-observed rather than independently reproduced here. The diagnostic source is preserved as a separate candidate; the protected reference runtime and frozen host evidence are not modified.

## Research/manuscript claims allowed

1. The host/reference campaign evaluated 400 deterministic executions across 16 case families, five policy variants and five repetitions; cite the existing frozen report and preserve its caveats.
2. The physical target run observed the expected controlled NACK return code and successful post-recovery BME280 ID reads for P1 and P4.
3. The integrated P4 policy is promising in selected contexts; the evidence does not establish universal superiority.
4. The software matrix and physical demonstration have different evidentiary roles and must be reported separately.

## Claims not supported by this evidence

- physical stuck-bus recovery;
- full physical execution of all 80 matrix rows;
- exact one-to-one equivalence between the 16 embedded contexts and frozen CF01–CF16;
- repeated-trial reliability or statistical generalization;
- MCU performance, stack, memory, timing, energy, or latency results;
- universal P4 superiority, legal novelty, non-obviousness, or patentability.

## Next phase

The next primary work package is manuscript drafting and evidence audit. Before drafting, read the complete repository and the existing literature/reference review artifacts. Verify citations and metadata, map every claim to its evidence, distinguish host/reference from physical results, and do not invent missing measurements or bibliographic details. A Claude-ready drafting prompt is stored at [`research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md`](../../research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md).
