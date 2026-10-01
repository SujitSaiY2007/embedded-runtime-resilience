# Current Handoff

## Session status

Gates A-E remain closed and normative. The Minimal Reference Implementation, K.1 host verification, K.2 corpus validation, and K.3 synthesis are complete. The active objective is the integrated software demonstrator + methodology lock before MCU validation.

## Frozen topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Frozen platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**, I2C primary, SPI secondary, UART/USART diagnostic/control. Hardware acquisition is not assumed.

## Continuity check

- **Gate A:** exact event/dependency semantics are frozen, including `EventRef={slot_id,generation}`, explicit dependency classes, FIFO admission versus eligibility-driven execution, and retained quarantine.
- **Gate B:** observable fault taxonomy and evidence-bounded association are frozen; `association precision <= evidence precision`.
- **Gate C:** deterministic bounded recovery policy is frozen with RETRY, REINIT_OR_RESET, DEGRADE, ESCALATE and four recovery-action transitions.
- **Gate D:** formal safety/termination/boundedness/identity/release/transaction properties are specified; the 33,792-context audit remains model-level evidence.
- **Gate E:** P0-P4, W01-W14, deterministic injection, fixed capacities, trace schema, metrics, and evidence boundaries are frozen.

These gates are one chain: event semantics constrain fault association; fault context constrains policy; policy/recovery interacts with scheduler/quarantine semantics; formal properties define correctness; the experimental protocol makes those properties comparable and reproducible.

## What was implemented

Directory: `reference/`

- ISO C11 host reference.
- CMake build.
- Fixed `EventSlot[20]` storage (`QMAX=16`, `XMAX=4`).
- Queue stores slot IDs; quarantine retains the same event slot and does not duplicate records.
- Four fixed dependency entries per event (`DMAX=4`).
- One fixed recovery episode (`EPMAX=1`).
- 8-bit EventRef generation; generation wrap fails closed instead of recycling.
- Deterministic first-eligible scheduler scan.
- Fixed-size `PolicyDecision` and P0-P4 policy variants.
- Deterministic software fault injection keyed by EventRef/action index.
- W01-W14 executable correctness scenarios.
- Gate-D-oriented policy/property assertions.
- Stable trace identifiers and deterministic CSV trace serialization.
- Static resource accounting and allocator audit.

## Verification result

Host C11/CMake build passed. `ctest` passed the W01-W14 suite plus recovery-bound, policy-property, trace-metadata, and static-accounting checks.

Host layout observed in this build:

- Runtime: 8164 bytes
- EventSlot: 84 bytes
- TraceRecord: 24 bytes
- fixed trace pool: 6144 bytes

Allocator source/symbol audit found no runtime allocator path in the reference implementation/test executable.

## Important implementation qualification

The minimal prototype intentionally implements exact event/transaction recovery as the executable recovery target. For `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS`, it does not invent an event target; where broader recovery is not implemented safely, it fails closed to terminal escalation. This is an implementation boundary, not a change to Gate B/C semantics.

`EPMAX=1` is explicit. W10 tests the bounded second-episode outcome rather than hiding additional recovery storage.

## Current exact task

Complete the software-only proof-of-concept and methodology lock. The professor review is part of this integrated phase, not a separate stage.

The demonstrator should expose the full mechanism: fault observation -> evidence-bounded association -> event quarantine -> bounded context/history-aware recovery -> verification -> release/degrade/escalate -> trace explanation.

After the demonstrator is complete, re-run/confirm the host verification path, lock the methodology and evidence boundaries, and record the final software-phase conclusion. Do not reopen Gates A-E unless new evidence directly contradicts them.

## Non-goals

Do not yet:

- integrate full STM32U575 firmware;
- claim MCU RAM/Flash/timing;
- perform physical fault injection;
- add RTOS/framework layers;
- add unrelated peripherals;
- optimize before correctness;
- claim novelty, patentability, robustness, generalization, or statistical significance.

## 2026-10-01 continuation

The required startup audit is complete. Gates A-E remain frozen.

The committed implementation review found one concrete ablation gap: exact-event quarantine is currently applied by `runtime_start_fault()` for P0-P4, although frozen Gate C/E define selective dependency-aware quarantine as the P4 mechanism. This is documented in `research/phase1_reference_implementation_audit.md` and in Decision Log D-076. No semantic patch was made.

The next host checkpoint now exists under `reference/experiments/`:

- declarative `workloads.csv`;
- deterministic `fault_schedules.csv`;
- `host_experiment.c` matched P0-P4 runner;
- `run_host_experiment.py` deterministic-replay/matched-input driver;
- CTest registration when Python 3 is available.

The runner flags W09/W10 as capacity-confounded and flags P0-P3 as not valid for a clean quarantine ablation until their baseline containment semantics are separately specified.

### Verification qualification

The code was inspected against the committed API and frozen protocol, but this chat environment could not clone/compile the repository because external network resolution was unavailable. Therefore the harness is **committed but not execution-verified here**. Do not cite generated results until the host build and replay test pass.

### Exact next task

Build `reference/`, run CTest, execute `python3 experiments/run_host_experiment.py --check`, inspect the generated corpus, and fix only concrete compile/runtime/input errors. Do not change Gate A-E semantics. After successful execution, commit the generated raw-input-preserved corpus and update this handoff with actual run/test results.

### Non-goals

No STM32U575 integration, MCU timing/RAM/Flash claims, physical fault injection, RTOS, unrelated peripherals, ML/weighted scoring, statistical significance, generalization, novelty, or patentability claims.

## Chat K.1 — 2026-10-01 verified host-experiment checkpoint

This section supersedes the earlier “execution verification pending” language above.

### Completed

The smallest reproducible host P0-P4 experiment harness was built and executed in the user-controlled Windows/MSVC environment.

- Commit: `949bd4c`
- Branch: `experiment/host-p0-p4-corpus-2026-10-01`
- Working tree: clean after commit and push.
- Build: successful; `reference_tests.exe` and `host_experiment.exe` present.
- CTest: **2/2 passed**.
- Host experiment check: **all five harness checks passed**.
- Corpus: **70 matched runs** across W01-W14 and P0-P4.
- W09/W10 capacity confounds are explicit.
- P0-P3 quarantine-ablation validity is explicitly false; P4 is valid under the current implementation.
- The exact-event quarantine semantic gap remains documented; no frozen contract was changed.

### Important artifact note

The generated `out/` and `out.replay/` directories were used for verification and inspection, then removed before the clean commit. Do not describe those generated files as currently committed artifacts.

### Chat K.2 exact next task

Regenerate and inspect the actual `runs.csv`, `trace.csv`, and `corpus_manifest.csv`. Determine whether the traces themselves provide the expected Gate-E evidence and identify any remaining measurement/evidence boundary. Only after that inspection should another code change be considered.

### Non-goals remain unchanged

No STM32U575 integration, physical fault injection, MCU resource/timing claims, RTOS, unrelated peripherals, ML/weighted scoring, statistical significance, generalization, novelty, or patentability claims.


## Chat K.3 — 2026-10-01 completed final synthesis

### Completed

- Produced `research/phase1_final_evidence_synthesis.md`.
- Reconciled the current continuity documents with K.1/K.2 completion status.
- Preserved the P0-P3 ablation limitation, W09/W10 capacity qualification, and host-only evidence boundary.
- Added explicit reproducibility and deferred-validation notes.
- Did not modify Gates A-E or add MCU/physical evidence.

### Archive boundary

**K.3 COMPLETE — final host/reference synthesis checkpoint.**

If the project is resumed, the next task must be explicitly selected from the deferred validation list. Do not infer MCU integration, physical validation, clean ablation comparisons, statistical analysis, novelty, or patentability from the host checkpoint.


## Historical K.2 record (preserved)

## Chat K.2 — 2026-10-01 completed host corpus validation

### Completed

The regenerated P0-P4 corpus was inspected at the CSV/trace level after the K.1 harness verification.

- **70 matched runs**: W01-W14 × P0-P4.
- Manifest checks remained PASS for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- Host-only evidence boundary was explicit: no MCU or physical-fault evidence was generated.
- Representative trace/run slices across W05-W08 and W11-W14 were internally coherent in the inspected fields.
- No concrete corpus-generation, serialization, or runtime defect was found.

### Interpretation constraints retained

- W09/W10 are capacity-confounded and must remain explicitly scoped in later analysis.
- P0-P3 are not clean quarantine ablations because exact-event quarantine is currently applied across all variants.
- P4 is the only variant marked valid under the current implementation boundary.
- Harness correctness must not be presented as policy superiority/correctness.

Generated `reference/experiments/out/` and `out.replay/` remain transient verification outputs and are not required source-checkpoint artifacts.

### Exact next task — K.3

Prepare the **final evidence-bounded synthesis** from the current repository state. Consolidate the frozen design, host/reference implementation, K.1/K.2 evidence, known semantic/ablation limitations, and explicit MCU/physical evidence gaps. Review the repository for consistency and produce the final project-facing documentation/package without silently changing Gates A-E or manufacturing unsupported performance, novelty, or patentability claims.

Do not begin MCU integration merely because the host corpus is complete.


## Integrated Software Phase — 2026-10-01

### Completed in this checkpoint

- Added `demo/index.html` as the professor-facing software demonstrator UI.
- Added `demo/README.md` with the UI's authority/evidence boundary.
- Added `research/phase1_software_demonstrator_methodology_lock.md` as the methodology-lock and conclusion record.
- Updated continuity state to treat professor verification as the intended use of this integrated software checkpoint, not as a separate gate.

### Remaining immediate work

1. Re-verify the repository from a clean checkout/build environment available to the user.
2. Run the demonstrator scenarios against the documented software evidence.
3. Review all current documents for stale pre-K.3 continuation language.
4. Decide whether any historical file is truly redundant; do not delete historical research merely for brevity.
5. Merge the completed software-phase package to `main` once re-verification passes.

### Methodology lock

The authoritative lock is `research/phase1_software_demonstrator_methodology_lock.md`.

The locked conclusion is: the project now has a specified, implemented, reproducible, demonstrable, evidence-bounded software mechanism suitable for target-MCU validation. This does not establish hardware performance, final novelty, or patentability.

### Important limitations remain

- P0-P3 are not clean quarantine ablations.
- W09/W10 are capacity-confounded.
- Host evidence is not MCU/physical evidence.
- No novelty/patentability conclusion is inferred from the software checkpoint.


---

## 2026-10-01 — Part-II boundary established after K.3

### Part-I closure
Part I = K.1 -> K.2 -> K.3 — COMPLETE.
K.3 is the final host/reference synthesis checkpoint of Part I. It remains evidence-bounded and does not claim MCU/physical validation, statistical superiority, final novelty or patentability.

### Part-II opening
Part II begins at K.4.
Part II is the integrated novelty re-investigation, virtual embedded-system/virtual-circuit construction, software demonstrator/UI, matched software comparison, full software re-verification, methodology lock, professor-facing proof of concept and hardware-validation handoff.

Professor review is the intended use of this integrated Part-II phase, not a separate stage.

### Branch state
- exp = active reference branch.
- main = stable integrated mirror.
- Part-II work starts from the latest exp state.
- Completed checkpoints return to exp, then synchronize to main by PR/merge.
- Direct Part-II development on main is prohibited by project protocol.

### Immediate next checkpoint
K.4 — Novelty Re-Research and Part-II Architecture Lock.

K.4 must establish the current prior-art landscape and lock the conceptual software demonstrator architecture before implementation begins.

### No-forward-scope rule
K.4 must not implement the virtual circuit/UI or alter the recovery mechanism. K.5 follows only after K.4 closes.


## Active K.4 Scope Update — 2026-10-01

The preceding handoff sections are preserved as historical continuity. They described the earlier integrated-software interpretation of K.4 and are superseded for active scope by research/PART_II_CHAT_PLAN.md and this section.

### Current Part
Part II.

### Current checkpoint
K.4 — Novelty Re-Research + Conceptual Architecture Lock.

### Last completed checkpoint
K.3 — Final host/reference synthesis.

### Active exp reference
1f3a471d2987b066ee995f4bf563fcdcbcd74d97.

### main relationship
main is e413a5986df9a486622bb4b34ef13ebc1e63ae80, one merge commit ahead of exp. That merge contains the older integrated-software-phase package. It is preserved and is not treated as a newer exp research state.

### K.4 result
Adversarial prior-art research materially weakens the broad novelty framing. Prior art covers peripheral recovery/isolation, recovery history, failed-event quarantine, dependency-aware containment, selective rollback/preservation, constrained runtime fault disambiguation, and zero-dynamic-allocation execution.

The remaining hypothesis is:

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

Status: UNRESOLVED. No novelty or patentability conclusion is made.

### Architecture lock
UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI.

The C reference runtime is the sole recovery-policy authority. UI and virtual-system layers cannot choose recovery actions. Trace records runtime-produced evidence and does not infer policy.

Authoritative architecture:
research/part_ii_conceptual_architecture.md

### Exact K.5 starting point
K.5 — Virtual Embedded System Technical Design + Interface Contracts.

K.5 defines, but does not implement, the virtual scheduler/environment, I2C/SPI/UART models, deterministic fault injection, C-runtime adapter, UI-facing state/trace schema, and baseline interface boundary.

Do not execute K.5 or later work in K.4 history sections above; this section is the active handoff.


## 2026-10-01 — Chat K.5 completed

### Current Part
Part II.

### Completed checkpoints
K.1-K.3 complete; K.4 complete; K.5 complete at design/contract level.

### K.5 result
The virtual embedded-system architecture and interfaces are now implementation-ready and are explicitly based on the actual ref_runtime.h/ref_runtime.c API. The C runtime remains the only recovery-policy authority.

Completed K.5 design boundaries:
- deterministic virtual scheduler/environment;
- EventSlot admission and runtime-generated EventRef identity;
- explicit dependency/order/transaction representation;
- I2C/SPI/UART environmental models;
- deterministic fault injection;
- simulator-to-C-runtime adapter;
- runtime input/output schemas;
- trace/evidence correlation;
- UI control/read-only evidence boundary;
- ownership/lifetime/static-capacity rules;
- S01-S14 deterministic scenario contracts.

### Critical K.6 constraint
The current runtime has no peripheral-action callback. K.6 must not silently modify runtime_apply_policy(), policy_decide(), or other recovery semantics to create one. The virtual peripheral may mirror deterministic action outcomes for environmental visualization, but runtime transition/verification remains authoritative. Any callback-based redesign requires a separate decision and is outside K.6 unless explicitly authorized.

### Exact K.6 starting sequence
1. implement bounded scenario/workload structures;
2. implement virtual I2C/SPI/UART state models;
3. implement immutable deterministic fault schedules;
4. implement adapter against existing ref_runtime.h;
5. implement event admission/dependencies;
6. implement deterministic scheduler loop around scheduler_select();
7. bridge fault observations to runtime_start_fault();
8. use existing policy/recovery/verification APIs without policy changes;
9. correlate authoritative runtime trace with environment records;
10. add focused deterministic/replay tests.

### K.6 non-goals
No UI implementation/polish, no recovery-policy redesign, no new policy variant, no hardware integration, no physical fault injection, no final baseline comparison, and no K.7-K.10 work.


## 2026-10-01 — Chat K.6 verification and merge complete

### Continuity

- Part II remains active.
- K.1–K.3 are complete.
- K.4 is complete.
- K.5 is complete.
- K.6 is VERIFIED AND MERGED into `exp` via PR #7 (merge commit `b161589`).
- Gates A-E remain frozen.
- The C reference runtime remains the sole recovery-policy authority.

### Merged K.6 implementation

Branch: `feature/k6-virtual-system-implementation-2026-10-01`
Final feature commit: `fc5be9d`
Base exp commit: `c39fef6`
Merged into `exp`: `b161589`
PR: #7 (`K.6: implement bounded virtual embedded system`) — Merged and closed.

Surface in `reference/virtual/`:
- `reference/virtual/include/virtual_system.h`
- `reference/virtual/src/virtual_system.c`
- `reference/virtual/tests/test_virtual_system.c`
- `reference/virtual/CMakeLists.txt`
- `reference/virtual/README.md`
- `reference/CMakeLists.txt`

### Verification evidence

- CTest: 3/3 passed (100%): `reference_tests`, `host_experiment_replay`, `virtual_system_tests`.
- Scenarios: S01, S02, S05, S06, S08, S14 passed.
- Deterministic replay digests:
  - S01: `0xB72131CB` == `0xB72131CB` (Equal: YES)
  - S02: `0xE8691374` == `0xE8691374` (Equal: YES)
  - S05: `0xBDC168BD` == `0xBDC168BD` (Equal: YES)
  - S06: `0xA123BB47` == `0xA123BB47` (Equal: YES)
  - S08: `0x5A52628A` == `0x5A52628A` (Equal: YES)
  - S14: `0x9185616C` == `0x9185616C` (Equal: YES)
- Runtime integrity verified: `ref_runtime.c` and `ref_runtime.h` unchanged. `policy_decide()` remains sole decider; `runtime_apply_policy()` remains authoritative transition. No peripheral-action callback added. No fabricated EventRef created.

### Canonical status
- K.1–K.3: completed
- K.4: completed
- K.5: completed
- K.6: VERIFIED AND MERGED INTO EXP
- K.7: VERIFIED AND MERGED INTO EXP
- K.8: VERIFIED AND MERGED INTO EXP
- K.9: CLOSED — MERGED INTO EXP
- K.10: NOT STARTED


## 2026-10-01 — Chat K.8 complete: matched baseline validation verified and merged into exp

### Continuity

- Part II remains active.
- K.1–K.3 are complete.
- K.4, K.5, K.6, and K.7 are complete and merged into `exp`.
- K.8 is VERIFIED AND MERGED into `exp` via PR #9 at merge commit `5590bf1`.
- Gates A-E remain frozen and normative.
- The C reference runtime remains the sole recovery-policy authority.

### Implemented K.8 surface

Branch: `feature/k8-baseline-validation-2026-10-01`
Base exp commit: `d808436`
Merge commit: `5590bf1`
PR: #9 (`K.8: matched baseline validation`) — Merged and closed.

Files created/updated:
- `reference/experiments/evaluate_baselines.py`: Comprehensive comparative evaluation harness for 70 host runs (W01–W14 × P0–P4) and 30 virtual demonstrator runs (S01–S14 × P0–P4) = 100 total deterministic runs.
- `reference/virtual/tests/test_virtual_baselines.c`: C11 unit assertions testing baseline progression, persistent fault escalation vs reinit recovery, stale ref handling vs fail-closed escalation, unassociated work preservation, and deterministic replay.
- `reference/virtual/CMakeLists.txt`: Integrated `virtual_baseline_tests` executable and `matched_baseline_validation_test`.
- `research/phase2_k8_matched_baseline_validation.md`: Structured comparative evidence report documenting metric tables, scenario matrices, and qualification locks.
- `research/chat_records/chat_k8_record.md`: Canonical chat record for K.8.

### Verification evidence

- CTest: 7/7 passed (100%):
  1. `reference_tests` (Passed)
  2. `host_experiment_replay` (Passed)
  3. `virtual_system_tests` (Passed)
  4. `virtual_demo_test` (Passed)
  5. `virtual_baseline_tests` (Passed)
  6. `virtual_ui_contracts_test` (Passed)
  7. `matched_baseline_validation_test` (Passed)
- Comparative findings:
  - Persistent fault (W06/S06): P0 escalates blindly (`OUTCOME_TERMINAL_ESCALATE`), while P1, P3, and P4 progress to `ACT_REINIT_OR_RESET` on attempt 3 (and P2 retries without history bounds), all achieving recovery (`OUTCOME_SUCCESS`).
  - Ambiguous association (W12/S08): P0 blindly retries unmapped target returning `OUTCOME_STALE_REF` and leaves episode active; P4 detects non-exact association, cleanly terminates with `OUTCOME_TERMINAL_ESCALATE` and closes episode with zero synthetic EventRefs.
  - Deferable work (W07): P0 escalates; P1–P4 cleanly degrade to `TERMINAL_DEGRADE`.
  - Independent work preservation (W01/S01): All variants preserve unassociated work under exact quarantine.
- Runtime integrity verified: `ref_runtime.c` and `ref_runtime.h` unchanged. `policy_decide()` remains sole decider; `runtime_apply_policy()` remains authoritative transition. No peripheral-action callback added.
- Post-merge verification on `exp`: 7/7 CTest passed; `evaluate_baselines.py --check` passed (100 runs); working tree clean.



## 2026-10-01 — Chat K.9 complete: full software re-verification, evidence reconciliation, and methodology lock closed

### Continuity

- Part II remains active.
- K.1–K.3 are complete.
- K.4–K.8 are complete and merged into `exp`.
- K.9 is CLOSED and MERGED into `exp` via PR #10 at merge commit `d1e0dcb`.
- Gates A–E remain frozen and normative.
- The C reference runtime remains the sole recovery-policy authority.

### Implemented K.9 surface

Branch: `feature/k9-methodology-lock-2026-10-01`
Base exp commit: `9ebd84c`
Implementation commit: `33fe87c`
Reconciliation commit: `2e0e5a0`
Merge commit: `d1e0dcb`
PR: #10 (`K.9: methodology lock and re-verification`) — Merged and closed.

Files created/updated:
- `research/phase2_k9_methodology_lock.md`: Comprehensive formal methodology lock freezing Items A through O, locking limitations (quarantine symmetry, S06 multi-policy recovery, capacity confounds, software-only scope, prohibited claims), and clarifying scenario scope (S01–S14 vs 6-scenario demonstrator subset).
- `research/chat_records/chat_k9_record.md`: Canonical chat record for K.9.
- `DECISION_LOG.md`: Added architectural decisions `D-110` (methodology lock) and `D-111` (merge and closure).

### Evidence reconciliation and verification evidence

- S06/P2 Reconciliation: Authoritative digest is `0xCDAB2617` (established by K.8 report, direct C execution, and 10/10 deterministic replay). Prose grouping error corrected.
- CTest: 7/7 passed (100%):
  1. `reference_tests` (Passed)
  2. `host_experiment_replay` (Passed)
  3. `virtual_system_tests` (Passed)
  4. `virtual_demo_test` (Passed)
  5. `virtual_baseline_tests` (Passed)
  6. `virtual_ui_contracts_test` (Passed)
  7. `matched_baseline_validation_test` (Passed)
- Deterministic 100-run reproduction: 70 host runs + 30 demonstrator runs, 100% bit-for-bit identical digests with zero divergence.
- Runtime integrity verified: `ref_runtime.c` and `ref_runtime.h` 100% untouched.

### Exact next task: K.10 Final Software Packaging & Research Conclusion

1. Prepare final software-phase release and freeze documentation under the locked methodology boundaries.
2. Package research findings under locked evidence boundaries (no hardware claims, no superiority claims, no patent claims).
3. Conclude software phase prior to target-MCU validation.

K.10 has NOT been started.







