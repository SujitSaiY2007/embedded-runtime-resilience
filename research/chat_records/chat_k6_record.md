# Chat K.6 Record — Virtual Embedded System Implementation

Date: 2026-10-01
Checkpoint: K.6
Focused branch: feature/k6-virtual-system-implementation-2026-10-01
Base exp commit: c39fef60c6570c2f2136e9b7fcf6b1d22b773172
Implementation commit: 91b1e16825ec093c99aedaaa3213bc6482c77d12

## Objective

Implement the bounded virtual embedded system around the SAME existing ISO C11 C reference runtime using the K.5 contracts.

## Continuity check

- Part I K.1-K.3 complete.
- Part II K.4 and K.5 complete.
- K.5 contracts are treated as fixed.
- Gates A-E remain frozen.
- The C runtime remains the sole recovery-policy authority.
- K.7 and later checkpoints were not executed.

## Work performed

1. Added fixed-capacity virtual scenario/workload structures.
2. Added runtime-generated ScenarioEventKey -> EventRef mapping.
3. Added deterministic I2C/SPI/UART environmental observation records.
4. Added immutable per-scenario fault schedules mapped to the existing FaultInjection structure.
5. Added a runtime adapter using runtime_admit(), runtime_add_dependency(), scheduler_select(), runtime_execute_selected(), runtime_start_fault(), policy_decide(), and runtime_apply_policy().
6. Added wrapper trace records linked to runtime trace sequence, EventRef and transaction ID.
7. Added a deterministic replay digest over authoritative runtime trace and wrapper trace.
8. Added focused tests for S01, S02, S05, S06, S08 and S14.
9. Integrated the K.6 test target into the existing reference CMake without changing ref_runtime.h/ref_runtime.c.

## Authority validation

The virtual layer never selects a RecoveryAction. policy_decide() is observed from the runtime only; runtime_apply_policy() performs the actual recovery transition. No peripheral-action callback was added.

The peripheral model mirrors the predeclared deterministic schedule only as an environmental observation. It does not mutate runtime policy state.

## Files

- reference/virtual/include/virtual_system.h
- reference/virtual/src/virtual_system.c
- reference/virtual/tests/test_virtual_system.c
- reference/virtual/CMakeLists.txt
- reference/virtual/README.md
- reference/CMakeLists.txt

## Focused scenarios

S01 — independent preservation
S02 — ordered blocking
S05 — retry success and correlation
S06 — bounded retry/reinit progression
S08 — ambiguous association without fabricated exact target
S14 — mixed dependency/replay correlation

S03/S04/S07/S09-S13 remain represented by the K.5 scenario contracts and are not used as a comparative experiment in K.6.

## Verification status
 
- Full build completed successfully under MSVC / CMake with 0 errors and 0 warnings.
- CTest suite executed: 3/3 passed (100%): `reference_tests`, `host_experiment_replay`, `virtual_system_tests`.
- Scenarios verified:
  - S01: PASS (`OUTCOME_SUCCESS`, digest: `0xB72131CB`)
  - S02: PASS (`OUTCOME_SUCCESS`, digest: `0xE8691374`)
  - S05: PASS (`OUTCOME_SUCCESS`, digest: `0xBDC168BD`)
  - S06: PASS (`OUTCOME_SUCCESS`, digest: `0xA123BB47`)
  - S08: PASS (`OUTCOME_TERMINAL_ESCALATE`, digest: `0x5A52628A`)
  - S14: PASS (`OUTCOME_SUCCESS`, digest: `0x9185616C`)
- Deterministic replay digests: verified equal across consecutive runs for all scenarios.
- Runtime authority: verified that `policy_decide()` and `runtime_apply_policy()` remain the sole recovery engine; no peripheral-action callback added; no fabricated EventRef created; `ref_runtime.c` and `ref_runtime.h` unchanged.
- Fixes applied in commit `fc5be9d`: resolved MSVC C4244 truncation warning, aligned fault schedule indexing with `fault_schedules.csv`, and aligned S02 test assertion to `ST_QUEUED` dependency blocking.
- PR #7 merged into `exp` at commit `b161589`.

## K.6 exit status

**K.6 VERIFIED AND MERGED**

- K.1–K.3: completed
- K.4: completed
- K.5: completed
- K.6: VERIFIED AND MERGED
- K.7: NOT STARTED

## Scope discipline

No recovery-policy redesign, new algorithm, new policy variant, UI work, baseline comparison experiment, hardware integration, physical fault injection, Gates A-E change, or K.7-K.10 work was performed.

