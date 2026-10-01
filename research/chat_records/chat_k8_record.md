# Chat K.8 Record — Matched Baseline vs Proposed Software Validation

Date: 2026-10-01  
Checkpoint: K.8  
Focused branch: `feature/k8-baseline-validation-2026-10-01`  
Base exp commit: `d808436440ec5a0f62dc9dcfabf53f3e2e0e5c6a`  

## Objective

Execute **K.8: Matched Baseline vs Proposed Software Validation**.

Under frozen Gates A-E, evaluate the comparative performance of baseline policies against the proposed policy across canonical workloads and fault schedules:
- **Baselines:**
  - P0: Fixed retry (minimal baseline: retry <= 2, blind escalate)
  - P1: Fixed retry + recovery (retry <= 2, reinit <= 3, degrade/escalate)
  - P2: Context only (uses local context/safety, no attempt history)
  - P3: Context + history (uses context and history, no Gate C exact bounds)
- **Proposed:**
  - P4: Zero-heap context-aware recovery with exact-association event quarantine

## Continuity check

- Part I K.1–K.3 are complete.
- Part II K.4, K.5, K.6, and K.7 are complete.
- Gates A–E remain frozen and normative.
- The C reference runtime remains the sole recovery-policy authority.
- K.9 and K.10 were not executed.

## Work performed

1. **Comparative Evaluation Harness (`reference/experiments/evaluate_baselines.py`):**
   - Evaluated the canonical 70-run host experiment corpus (14 declarative workloads W01–W14 × 5 policy variants P0–P4).
   - Evaluated the canonical 30-run virtual demonstrator scenario matrix (6 scenarios S01, S02, S05, S06, S08, S14 × P0–P4).
   - Validated that total evaluated runs equal 100 deterministic executions.
   - Aggregated comparative metrics: terminal outcomes, recovery attempt counts, trace record counts, unassociated work preservation, failure mode handling, and known qualification flags.

2. **Comparative Findings across Workloads and Scenarios:**
   - **Persistent Fault Progression (W06, S06):**
     - Baseline P0 blindly escalates after 2 retries without resetting (`OUTCOME_TERMINAL_ESCALATE`), leaving slot escalated.
     - P1, P2, P3, and P4 progress to `ACT_REINIT_OR_RESET` on attempt 3, reinitialize the peripheral, and achieve recovery (`OUTCOME_SUCCESS`).
   - **Ambiguous Association Safety (W12, S08):**
     - Baseline P0 blindly retries unmapped target resulting in `OUTCOME_STALE_REF` and leaves episode in an unclosed active state (`ACTIVE`).
     - P4 enforces exact association (`ctx->association == ASSOC_EXACT`), immediately failing closed safely to `OUTCOME_TERMINAL_ESCALATE`, closing the episode, and admitting zero synthetic EventRefs (`target_slot == 255`).
   - **Graceful Degradation (W07):**
     - P0 blindly escalates deferable work.
     - P1–P4 cleanly transition deferable work to `TERMINAL_DEGRADE`, preventing halt.
   - **Independent Work Preservation (W01, S01):**
     - Unassociated events (e1, e3, e4) complete while e2 is quarantined across all variants.
   - **Dependency Blocking (W02, S02):**
     - Dependent event e2 remains blocked in `ST_QUEUED` while prerequisite e1 is quarantined across all variants.

3. **Dedicated C Baseline Test Suite (`reference/virtual/tests/test_virtual_baselines.c`):**
   - Added C11 unit assertions testing:
     - S06 baseline failure (P0 escalates) vs recovery (P1, P4 succeed).
     - S08 stale ref handling (P0) vs clean fail-closed escalation (P4).
     - S05 transient recovery across all variants.
     - S01 independent event preservation across all variants.
     - S02 dependency blocking across all variants.
     - Deterministic 32-bit replay digest reproducibility across all variants and scenarios.

4. **CMake & CTest Integration:**
   - Added `virtual_baseline_tests` executable to `reference/virtual/CMakeLists.txt`.
   - Added `matched_baseline_validation_test` invoking `evaluate_baselines.py --check`.
   - CTest suite expanded from 5 to 7 tests, all passing 100%.

5. **Comparative Validation Synthesis Document:**
   - Authored `research/phase2_k8_matched_baseline_validation.md` documenting executive summary, comparative metrics tables, scenario matrix, and explicit evidence boundaries.

## Authority and runtime integrity validation

- `reference/src/ref_runtime.c` and `reference/include/ref_runtime.h` were NOT modified.
- `policy_decide()` in `ref_runtime.c` remains the sole decider for all variants (P0–P4).
- `runtime_apply_policy()` remains the sole authoritative transition engine.
- No second recovery policy or second scheduler was invented.
- No peripheral callbacks were introduced.
- Known qualifications preserved: W09/W10 capacity confound (`capacity_confounded=1`) and P0–P3 quarantine-gap limitation (`ablation_contract_valid=0`).

## Verification status

### CTest suite
- Total tests: 7
- Passed: 7 (100%)
- Failed: 0
- Targets:
  1. `reference_tests` (Passed)
  2. `host_experiment_replay` (Passed)
  3. `virtual_system_tests` (Passed)
  4. `virtual_demo_test` (Passed)
  5. `virtual_baseline_tests` (Passed)
  6. `virtual_ui_contracts_test` (Passed)
  7. `matched_baseline_validation_test` (Passed)

### Determinism
- 100% reproducible digests verified across repeated runs for all workloads and scenarios across P0–P4.

## Pull Request and Merge into exp

- PR: #9 (`K.8: matched baseline validation`)
- Source branch: `feature/k8-baseline-validation-2026-10-01` (`319068c`)
- Target branch: `exp` (`d808436`)
- Merge type: Non-fast-forward (`--no-ff`)
- Merge commit: `5590bf1`
- Post-merge verification on `exp`:
  - CTest suite: 7/7 passed (100%)
  - Baseline validation test suite (`evaluate_baselines.py --check`): 100 runs evaluated, all assertions passed.
  - Working tree clean.

## K.8 exit status

**`K.8 CLOSED — MERGED INTO EXP`**

Canonical checkpoint status:
- K.1–K.3: completed
- K.4: completed
- K.5: completed
- K.6: VERIFIED AND MERGED INTO EXP
- K.7: VERIFIED AND MERGED INTO EXP
- K.8: VERIFIED AND MERGED INTO EXP
- K.9: NOT STARTED
- K.10: NOT STARTED

## Scope discipline

No recovery-policy redesign, new algorithm, hardware integration, physical fault injection, Gates A-E change, or K.9–K.10 work was performed.

