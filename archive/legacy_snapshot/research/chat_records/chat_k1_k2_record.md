# Chat K.1 / K.2 Research Continuity Record

**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Branch:** `experiment/host-p0-p4-corpus-2026-10-01`  
**K.1 checkpoint commit:** `949bd4c`  
**Date:** 2026-10-01

## Chat K.1 — Host Experiment Verification

### Purpose

Complete the smallest reproducible host experiment checkpoint after auditing the committed reference implementation against frozen Gates A-E.

### Completed work

1. Audited the reference implementation against Gates A-E.
2. Identified and documented the concrete P0-P3 quarantine-ablation gap: `runtime_start_fault()` applies exact-event quarantine across P0-P4.
3. Preserved the frozen Gate A-E contracts; no silent semantic changes were made.
4. Added/verified the declarative workload and deterministic fault-schedule corpus.
5. Added the matched P0-P4 host experiment runner and deterministic replay checks.
6. Corrected the small Windows/MSVC build/launcher issues encountered during execution.
7. Executed the harness in the user-controlled Windows/MSVC environment.

### Verification evidence

- `reference_tests.exe` built successfully.
- `host_experiment.exe` built successfully.
- CTest: **2/2 passed**.
- Host check: **PASS** for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- Matched corpus: **70 runs** = W01-W14 × P0-P4.
- W09/W10 explicitly marked capacity-confounded.
- P0-P3 explicitly marked `ablation_contract_valid=0`.
- P4 explicitly marked `ablation_contract_valid=1`.

### Implementation corrections recorded during K.1

- Windows/MSVC warning handling for `strtok` in `host_experiment.c`.
- MSVC-safe size conversion in `trace_write_csv()` in `ref_runtime.c`.
- Corrected `action_index` records in deterministic fault schedules 106-108.
- Multi-config Windows build-output resolution and cleanup handling in the Python launcher.

These were build/harness portability corrections; they did not change the frozen Gate A-E semantics.

### Artifact handling

The generated `reference/experiments/out/` and `out.replay/` directories were used for execution and inspection, then removed before the clean commit. They are therefore not currently committed artifacts.

## Chat K.1 research conclusions

- The host experiment harness is executable and reproducible under the tested Windows/MSVC environment.
- Harness-level checks pass.
- The current P0-P3 variants are **not** clean quarantine ablations.
- W09/W10 remain capacity-confounded.
- Host evidence must not be presented as MCU/physical evidence.

## Chat K.2 — Completed 2026-10-01

**Status:** Planned / next chat, not yet completed.

### Objective

Validate the actual regenerated host corpus at the trace/outcome level against Gate E.

### Required checks

1. W01-W14 × P0-P4 coverage is exactly matched.
2. Run/variant/workload/trace identities are consistent.
3. EventRef generation and W11 stale-generation/slot-reuse behavior are coherent.
4. Recovery action sequences follow the frozen Gate-C ladder.
5. Outcome and correctness fields are internally consistent.
6. Capacity-confound and ablation-contract flags are correct.
7. Quarantine/preservation evidence is interpreted according to current runtime semantics.
8. Harness correctness is separated from policy correctness.
9. Remaining Gate-E evidence gaps are identified before any experimental comparison is interpreted.

### Explicit non-goals

- No Gates A-E redesign.
- No STM32U575 integration.
- No physical fault injection.
- No MCU timing/RAM/Flash claims.
- No RTOS or unrelated peripherals.
- No ML/weighted scoring.
- No statistical significance/generalization claims.
- No novelty/patentability claims.

### Stop condition

Stop after the smallest reproducible corpus-validation checkpoint and update the repository continuity records with the actual findings.


### K.2 execution findings

The regenerated corpus was inspected after successful K.1 harness execution.

- 70 matched runs were present: W01-W14 × P0-P4.
- `corpus_manifest.csv` reported PASS for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- The manifest explicitly identified host-only evidence and zero MCU/physical evidence.
- Representative `runs.csv`/`trace.csv` slices across W05-W08 and W11-W14 were coherent in the inspected recovery, action/outcome, correctness, and metadata fields.
- No concrete corpus-generation, serialization, or runtime defect was found.

### K.2 interpretation

The corpus checkpoint is complete, but P0-P3 are not clean quarantine ablations because the current implementation applies exact-event quarantine across all variants. W09/W10 remain capacity-confounded. Host/reference evidence remains distinct from MCU and physical validation.

### K.2 stop condition

**K.2 COMPLETE.** No Gates A-E were changed and no MCU integration was started.

## K.3 — Starting boundary

Final synthesis and evidence-bounded project packaging. Consolidate the demonstrated host/reference evidence, known limitations, and remaining validation gaps without introducing unsupported hardware, performance, novelty, or patentability claims.
