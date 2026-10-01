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

The implementation diff was inspected against the K.5 contracts and existing runtime API. Direct repository compilation/execution is not available in this chat environment because external GitHub network resolution is unavailable to the local execution container.

Therefore this record deliberately does NOT claim that the new CTest target has passed.

## K.6 exit status

**Implementation present; execution exit pending.**

The next K.6 chat must build the reference tree, run CTest, verify the focused scenarios against the actual ref_runtime.c, verify correlated trace records and replay digest equality, and only then close K.6 and move the active prompt to K.7.

## Scope discipline

No recovery-policy redesign, new algorithm, new policy variant, UI work, baseline comparison experiment, hardware integration, physical fault injection, Gates A-E change, or K.7-K.10 work was performed.
