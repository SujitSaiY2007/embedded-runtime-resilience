# Phase 1 — Reference Implementation Gate A-E Audit

**Date:** 2026-10-01  
**Base:** `main` at experiment-branch creation  
**Purpose:** Audit the committed host reference against frozen Gates A-E before adding the smallest matched P0-P4 host experiment harness.

## Frozen-contract result

Gates A-E remain internally consistent and are not amended by this audit.

- **Gate A:** `EventRef={slot_id,generation}`, explicit dependency classes, FIFO admission versus eligibility, retained quarantine are implemented in the host reference.
- **Gate B:** observable fault classes, association levels, and conservative association handling are represented. Exact association is executable; broader association does not fabricate an event target.
- **Gate C:** the policy exposes RETRY, REINIT_OR_RESET, DEGRADE, and ESCALATE with the four-transition bound. P4 follows the frozen retry/reinit/terminal progression.
- **Gate D:** the reference contains checks for dependency, stale identity, quarantine/dispatch, bounded recovery, and terminal behavior.
- **Gate E:** W01-W14 identifiers, deterministic injection, QMAX/XMAX/DMAX/EPMAX, stable trace identifiers, and host-only evidence boundaries are represented.

## Concrete implementation contradiction

The committed implementation has one material **ablation-contract gap**:

`runtime_start_fault()` unconditionally marks an exact target `fault_associated=true`, moves it to `ST_QUARANTINED`, and removes it from the normal queue, regardless of `PolicyVariant`.

That means P0-P3 currently execute with the same exact-event quarantine primitive that Gate C/E reserve as the distinctive P4 integrated mechanism.

This is a real contradiction with the frozen variant definitions:

- P0: no selective quarantine policy;
- P1: fixed retry + peripheral recovery;
- P2: context-only without dependency-aware quarantine contribution;
- P3: context + episode history without the full dependency-aware quarantine mechanism;
- P4: integrated dependency-aware event quarantine.

This audit **does not silently change runtime semantics**. Changing the baseline containment behavior requires a separate implementation decision because the expected baseline semantics must be specified before code is changed.

## Experimental handling

The new host harness therefore:

1. runs P0-P4 on identical declarative workload/fault inputs;
2. preserves the actual runtime behavior;
3. emits `ablation_contract_valid=0` for the current P0-P3 runs;
4. does not present those runs as a clean causal ablation of event quarantine;
5. still permits matched-input, deterministic-replay, trace, correctness, and host-resource verification;
6. records this limitation in the generated corpus metadata.

No Gate A-E contract is amended.

## Other implementation observations

- The reference is zero-heap at the source/symbol-audit level documented by the project.
- The trace pool is fixed and bounded.
- The trace serializer is fixed-buffer based.
- Host `sizeof()` values remain host evidence only.
- The current runtime trace is a compact implementation trace; the harness adds a run manifest and outcome/correctness records rather than claiming that the existing `TraceRecord` alone implements every conceptual Gate E record type.

## Non-goals

This audit does not add MCU integration, physical fault injection, RTOS/framework layers, statistical claims, MCU timing/RAM/Flash claims, or novelty/patentability claims.

## Chat K.1 verification record

The host experiment harness was subsequently executed in the user-controlled Windows/MSVC environment.

- Build outputs: `reference_tests.exe`, `host_experiment.exe`.
- CTest: **2/2 passed**.
- Host check: deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging all **PASS**.
- Matched runs: **70** (W01-W14 × P0-P4).
- W09/W10 were explicitly capacity-confounded.
- P0-P3 remained `ablation_contract_valid=0`; P4 remained valid.
- No remaining compile/runtime/test failure was reported.

This verifies execution of the harness. It does not yet constitute corpus-level validation of every Gate-E trace claim; that is the Chat K.2 task.
