# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Gates A-E complete; Minimal Reference Implementation, K.1, K.2, and K.3 complete; integrated software demonstrator/methodology-lock phase active before MCU validation.  
**Project mode:** Solo software-dominant embedded-systems research project.

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C primary, SPI secondary, and UART/USART diagnostic/control. Hardware acquisition/physical validation is not assumed or claimed.

## Gates A-E

- **Gate A — COMPLETE:** `EventRef={slot_id,generation}`; explicit INDEPENDENT/ORDERED/COUPLED dependencies; FIFO admission versus eligibility-driven execution; retained non-executable quarantine; preservation as verified execution.
- **Gate B — COMPLETE:** evidence-bounded I2C fault taxonomy; four association levels; `association precision <= evidence precision`; recurrence/persistence as episode/history attributes; deterministic software injection as primary stimulus.
- **Gate C — COMPLETE:** minimum policy context; actions RETRY/REINIT_OR_RESET/DEGRADE/ESCALATE; exact ladder `T1 RETRY #1 -> T2 RETRY #2 -> T3 REINIT_OR_RESET -> T4 terminal`; `MAX_RECOVERY_ACTIONS=4`; P0-P4 ablations.
- **Gate D — COMPLETE:** quarantine, association, preservation/blocking, dependency, termination, resource, EventRef, release, transaction, and decision-table properties specified. The prior host abstract audit covered 33,792 bounded policy contexts; this remains model-level evidence.
- **Gate E — COMPLETE:** P0-P4 comparison set, W01-W14 workloads, deterministic fault schedules, `QMAX=16`, `XMAX=4`, `DMAX=4`, `EPMAX=1`, trace identifiers, metrics, reset/repetition rules, and evidence boundaries frozen.

Gates A-E form one chain: Gate A defines what work exists and what may execute; Gate B defines what failed and how precisely it can be associated; Gate C maps bounded context/history to recovery; Gate D states the correctness obligations; Gate E turns those obligations into reproducible comparisons and measurements.

## Minimal Reference Implementation checkpoint

Implemented under `reference/` as a deliberately small ISO C11 host reference with CMake.

### Fixed implementation decisions

- `ACTIVE_MAX = QMAX + XMAX = 20` fixed event slots.
- Normal queue stores slot IDs only; quarantined events remain in the same event-slot pool and leave the normal queue, so no event is double-counted.
- `DMAX=4` fixed dependency entries per event.
- `EPMAX=1` fixed active recovery episode; a second simultaneous episode returns an explicit bounded outcome.
- `EventRef` generation is 8-bit; it starts at 1 and fails closed rather than wrapping after `UINT8_MAX`.
- Scheduler scans queue admission order and selects the first event satisfying the Gate A dispatchability predicate.
- Exact event/transaction recovery is implemented. Broader association scopes never fabricate an event target; unsupported broader-scope recovery fails closed to terminal escalation in this minimal prototype.
- `PolicyDecision` is a fixed-size value result.
- Fault injection is deterministic and keyed by `EventRef` plus recovery action index.
- Trace records contain run/trace/episode identity, EventRef, transaction ID, observation sequence, action index, lifecycle state, action, outcome, and correctness; CSV serialization uses fixed local buffers and `write()`.

### Host verification performed

Local C11/CMake build completed successfully. `ctest` passed the W01-W14 correctness suite, bounded recovery test, policy-property checks, trace-metadata checks, and static-accounting checks.

Current host C-layout accounting:

- `sizeof(Runtime) = 8164` bytes
- `sizeof(EventSlot) = 84` bytes
- `sizeof(TraceRecord) = 24` bytes
- fixed trace pool = `6144` bytes

A source/symbol allocator audit found no `malloc/calloc/realloc/free` references in the reference implementation and no unresolved allocator symbols in the test executable.

These are host/reference observations only. They are **not** STM32U575 RAM/Flash/timing measurements.

## Current boundary

The smallest testable host/reference checkpoint is complete. Do not automatically proceed to full MCU integration or physical fault injection in the same phase merely because host tests pass.

## Explicit non-claims

No MCU performance/resource measurement, physical fault validation, energy measurement, statistical significance, generalization, novelty, or patentability claim is established by the host prototype.

## Continuation

`CURRENT_HANDOFF.md` contains the exact next continuation point. `research/phase1_reference_implementation_design.md` records implementation decisions. `reference/tests/canonical_workloads.md` maps W01-W14 to executable tests. Historical Gate A-E artifacts remain normative and preserved.

## 2026-10-01 host experiment checkpoint

The committed reference implementation was audited against Gates A-E before experiment work. Gates A-E remain unchanged.

A concrete implementation gap was recorded in `research/phase1_reference_implementation_audit.md`: `runtime_start_fault()` applies exact-event quarantine for every policy variant, while frozen Gate C/E reserve selective dependency-aware event quarantine as the P4 integrated mechanism. No runtime semantics were silently changed.

A smallest declarative experiment layer has been added under `reference/experiments/`:

- explicit workload operation corpus;
- explicit deterministic fault schedules;
- matched P0-P4 C harness;
- fixed CSV run/trace outputs;
- deterministic replay driver;
- matched-input/replay checks;
- explicit capacity-confounding flags;
- explicit P0-P3 ablation-validity flags.

The harness is host/reference evidence only. Generated corpus outputs must be produced by the committed build/run command before being treated as executed evidence. This environment could not execute the repository's committed binary directly, so no successful build/test result is claimed from this chat.

### Current implementation boundary

**Reference semantics:** unchanged.

**Experiment harness:** committed but execution verification is pending a host build/run.

**Trace corpus:** raw declarative inputs are committed; generated `runs.csv`/`trace.csv` are reproducibly generated artifacts and are not represented as already executed here.

**MCU/physical evidence:** none.

## 2026-10-01 Chat K.1 verified host-experiment checkpoint

Chat K.1 supersedes the earlier “execution verification pending” qualification.

### Verified in the user-controlled Windows/MSVC host environment

- Branch: `experiment/host-p0-p4-corpus-2026-10-01`
- Commit: `949bd4c`
- Build outputs included `reference_tests.exe` and `host_experiment.exe`.
- CTest: **2/2 tests passed**.
- Host experiment check: **PASS** for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- Matched execution: **70 runs = W01-W14 × P0-P4**.
- W09/W10: `capacity_confounded=1`.
- P0-P3: `ablation_contract_valid=0` because the current reference applies exact-event quarantine across all variants.
- P4: `ablation_contract_valid=1`.
- No remaining compile/runtime/test failure was reported at this checkpoint.

### Evidence boundary

This is **host/reference evidence only**. It does not establish STM32U575 timing, RAM, Flash, energy, electrical fault behavior, or physical recovery.

The generated `reference/experiments/out/` and `out.replay/` artifacts were inspected during verification but cleaned before commit. The committed reproducibility source is the declarative input corpus plus harness; Chat K.2 must validate the regenerated corpus contents rather than assuming the harness pass alone proves every Gate-E trace claim.

### Chat K.2 exact starting task

Regenerate and inspect the 70-run corpus from the clean branch. Check trace identifiers/lifecycle/action/outcome fields against Gate E, W01-W14 matched P0-P4 identity, capacity/ablation metadata, preservation/quarantine/recovery-bound evidence, and whether any result is only a harness property rather than a policy property.

Do not modify Gates A-E or start MCU integration during this checkpoint.


## 2026-10-01 Chat K.3 completed — final evidence-bounded synthesis

K.3 completed the final host/reference evidence synthesis and repository packaging.

- Gates A-E remain frozen and normative.
- K.1 and K.2 remain complete and their evidence is preserved.
- The current evidence boundary is host/reference + deterministic software injection only.
- P0-P3 remain `ablation_contract_valid=0` because exact-event quarantine is currently applied across all variants; P4 remains valid under the current implementation boundary.
- W09/W10 remain `capacity_confounded=1`.
- No MCU or physical-fault evidence is present.
- No statistical significance, generalization, novelty, or patentability claim is established.

See `research/phase1_final_evidence_synthesis.md` for the evidence matrix, interpretation boundaries, reproducibility entry point, and deferred-validation list.

**Current checkpoint: K.3 COMPLETE.** Any future work must explicitly select a deferred validation objective rather than being inferred from host completion.


## Historical K.2 record (preserved)

## 2026-10-01 Chat K.2 completed — host corpus validation

Chat K.2 regenerated and inspected the actual host corpus produced by the committed P0-P4 harness.

### Observed corpus evidence

- Corpus cardinality: **70 runs = W01-W14 × P0-P4**.
- `corpus_manifest.csv` reported:
  - `raw_input_preserved=PASS`
  - `matched_input_equivalence=PASS`
  - `capacity_confounds_explicit=PASS`
  - `ablation_contract_flagging=PASS`
  - `deterministic_replay=PASS`
  - `host_evidence_only=1`
  - `mcu_evidence=0`
  - `physical_fault_evidence=0`
- Representative `runs.csv` and `trace.csv` slices were inspected across W05-W08 and W11-W14, including recovery attempts, action/outcome fields, correctness, capacity metadata, and ablation metadata.
- No concrete corpus-generation, serialization, or runtime defect was found during K.2 validation.

### Interpretation boundary

K.2 validates reproducible host corpus generation and the declared trace/outcome metadata. It does not turn host/reference evidence into MCU or physical evidence, and it does not make P0-P3 clean quarantine ablations. The implementation limitation remains: `runtime_start_fault()` applies exact-event quarantine across all variants, so P0-P3 remain `ablation_contract_valid=0`.

### Current checkpoint

**K.2 — COMPLETE.**

The next checkpoint is **K.3 — Final synthesis and evidence-bounded project packaging**. Gates A-E remain frozen and normative; no MCU integration or physical validation has been started.


## Integrated Software Phase — 2026-10-01

**Objective:** construct a complete software-only demonstrator, re-verify and lock the research methodology, and produce a professor-facing conclusion that the mechanism is ready for target-MCU validation.

**Professor review is not a separate project stage.** It is the intended use of this integrated checkpoint.

### Locked software chain

`Gates A-E -> reference implementation -> K.1 host verification -> K.2 corpus validation -> K.3 synthesis -> software demonstrator -> methodology lock -> hardware-validation handoff`

### Current demonstrator

`demo/index.html` is the presentation layer. It exposes policy variants, fault scenarios, bounded recovery failures, association precision, and the expected decision/recovery path. The C reference under `reference/` remains the authoritative implementation; the UI is not a replacement specification.

### Re-verification status

The existing host evidence remains the verified basis: Windows/MSVC build, CTest 2/2, 70 matched W01-W14 × P0-P4 runs, deterministic replay, matched-input equivalence, raw-input preservation, explicit capacity-confound handling, and explicit ablation-contract handling.

### Locked limitations

- P0-P3 are not clean quarantine ablations because exact-event quarantine is currently shared across variants.
- W09/W10 are capacity-confounded.
- Host evidence is not MCU/physical evidence.
- Host C-layout values are not STM32U575 resource measurements.
- Novelty and patentability remain hypotheses/assessment targets, not established conclusions.

### Software-phase conclusion

The software mechanism is now sufficiently specified, implemented, reproducible, demonstrable, and evidence-bounded to justify proceeding to STM32U575 validation. The next empirical phase is hardware validation, not another redesign of Gates A-E.

---

## 2026-10-01 — Explicit Part Boundary

### Part I — K-Series Host/Reference Foundation — COMPLETE
K.1, K.2 and K.3 are COMPLETE. K.3 closes Part I as the final host/reference evidence-bounded synthesis checkpoint.

### Part II — Software Demonstrator, Novelty Investigation, and Methodology Lock — ACTIVE
K.4 onward is Part II.

Part II will construct and validate a software-only virtual embedded-system demonstrator around the existing C reference runtime. The UI is the face of the system; the virtual system is the controlled environment; the C reference runtime is the authoritative policy implementation; the trace is the evidence path.

### Part-II objective
Produce a coherent software proof of concept showing fault occurrence, evidence-bounded association, event quarantine, bounded context/history-aware recovery, verification and release/degrade/escalation, conditional preservation of unrelated valid work, traceable explanation and controlled baseline comparison.

### Part-II chat sequence
| Chat | Scope | Must not do |
|---|---|---|
| K.4 | Novelty re-research + conceptual demonstrator architecture lock | No implementation |
| K.5 | Virtual embedded-system technical design + interface contracts | No full UI or baseline experiment |
| K.6 | Virtual embedded-system implementation around the C reference runtime | No final UI polish or claims |
| K.7 | Professor-facing UI implementation | No recovery-policy redesign |
| K.8 | Matched baseline vs proposed software validation | No hardware claims or new mechanism |
| K.9 | Full software-chain re-verification + methodology lock | No hardware integration |
| K.10 | Final software conclusion + evidence package + hardware-validation handoff | No unsupported novelty/patentability conclusion |

A chat may report later-stage blockers but must not execute later-stage work unless explicitly re-authorized.

### Part-II branch rule
exp is the active reference branch. Work pattern: exp -> focused child branch -> checkpoint completion -> merge to exp -> PR/merge exp -> main.

### Current checkpoint
K.4 — Novelty Re-Research and Conceptual Architecture Lock.
Required end state: prior-art landscape refreshed, novelty hypothesis narrowed, conceptual demonstrator architecture locked, K.4 continuity record complete, next checkpoint K.5 precisely defined.

### Evidence boundary
No Part-II software result may be represented as STM32U575 timing/resource measurement, physical electrical fault evidence, physical MPU behavior, final patentability, or established novelty.


## Active K.4 Scope Update — 2026-10-01

All preceding state and historical checkpoint material is preserved.

Part I (K.1-K.3) is COMPLETE. Part II begins at K.4.

### Current checkpoint
K.4 — Novelty Re-Research + Conceptual Architecture Lock.

### Branch state
- exp = 1f3a471d2987b066ee995f4bf563fcdcbcd74d97
- main = e413a5986df9a486622bb4b34ef13ebc1e63ae80
- main is one merge commit ahead because of the older integrated-software-phase package.

K.4 work follows exp only.

### Novelty result
The broad framing is not defensible after adversarial re-research. The following are established or strongly overlapping: peripheral recovery/isolation; recovery history; event failure queues/quarantine; dependency-aware containment; selective rollback/preservation; constrained runtime fault disambiguation/trace monitoring; and zero-dynamic-allocation embedded execution.

Remaining hypothesis:

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

Status: UNRESOLVED.

Detailed record: research/novelty_investigation.md

### Architecture lock
UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI.

Authority:
- UI = presentation/scenario control.
- Virtual system = deterministic environment/workload/peripheral/fault model.
- C runtime = sole recovery-policy authority.
- Recovery Decision = observable C-runtime result, not a second component.
- Trace/Evidence = runtime-produced evidence.

Detailed record: research/part_ii_conceptual_architecture.md

### Documentation inconsistency
Historical K.4 integrated-software records remain in the repository and are preserved. They are superseded for active scope by research/PART_II_CHAT_PLAN.md and the Part-II scope override.

### Exact next checkpoint
K.5 — Virtual Embedded System Technical Design + Interface Contracts.

K.5 must not implement the simulator/UI and must not redesign the recovery policy.


## 2026-10-01 — Chat K.5 complete: virtual-system contracts

Part I (K.1-K.3) remains COMPLETE. Part II is ACTIVE.

K.4 is COMPLETE as prior-art re-research + conceptual architecture lock. Its narrowed novelty hypothesis remains UNRESOLVED; no novelty or patentability claim is made.

K.5 is COMPLETE at the technical-design/contract level. The virtual embedded system is now specified around the actual existing C reference runtime. The runtime remains the sole recovery-policy authority.

### K.5 completed
- deterministic virtual scheduler/environment boundary defined;
- virtual event/workload representation defined around existing EventSlot/runtime_admit();
- EventRef ownership and scenario-to-runtime identity correlation defined;
- INDEPENDENT/ORDERED/COUPLED dependency representation and ordering boundary defined;
- I2C/SPI/UART environmental contracts defined;
- deterministic fault-injection contract mapped to existing FaultInjection/runtime_start_fault();
- runtime input/output and ownership/lifetime boundaries defined;
- UI control versus runtime authority defined;
- authoritative trace/evidence boundary defined;
- S01-S14 deterministic scenarios defined for K.6;
- baseline boundary defined as existing Runtime.variant/P0-P4, with no second baseline engine;
- current runtime adapter limitation documented: no peripheral-action callback exists, so K.6 must not silently add one or modify recovery semantics.

### K.5 artifacts
- research/part_ii_virtual_system_technical_design.md
- research/part_ii_interface_contracts_k5.md
- research/part_ii_deterministic_scenarios_k5.md
- research/chat_records/chat_k5_record.md

### K.5 non-changes
Gates A-E, the existing C recovery mechanism, P0-P3 ablation qualification, W09/W10 capacity qualification, and all host/MCU/physical evidence boundaries remain unchanged.

### Next checkpoint
K.6 — Virtual Embedded System Implementation around the existing C reference runtime. K.6 may implement only the contracts defined by K.5; it must not introduce a second recovery policy or redesign the C runtime.


## 2026-10-01 — Chat K.6 complete: virtual-system implementation verified and merged

Part I (K.1-K.3) remains COMPLETE. Part II is ACTIVE.
K.4 (novelty re-research + conceptual architecture lock) and K.5 (technical design and interface contracts) are COMPLETE.

K.6 (virtual embedded system implementation) is VERIFIED AND MERGED into `exp` via PR #7 (merge commit `b161589`).

### K.6 verification summary
- CTest suite: 3/3 passed (100%): `reference_tests`, `host_experiment_replay`, `virtual_system_tests`.
- Scenarios verified: S01, S02, S05, S06, S08, S14 all passed.
- Deterministic replay digest verified:
  - S01: `0xB72131CB` == `0xB72131CB` (Equal: YES)
  - S02: `0xE8691374` == `0xE8691374` (Equal: YES)
  - S05: `0xBDC168BD` == `0xBDC168BD` (Equal: YES)
  - S06: `0xA123BB47` == `0xA123BB47` (Equal: YES)
  - S08: `0x5A52628A` == `0x5A52628A` (Equal: YES)
  - S14: `0x9185616C` == `0x9185616C` (Equal: YES)
- Authority preserved: `policy_decide()` remains sole recovery decider; `runtime_apply_policy()` remains authoritative transition.
- Runtime integrity preserved: `ref_runtime.c` and `ref_runtime.h` unchanged. No peripheral-action callback added. No second recovery policy created. No synthetic EventRefs fabricated.

### Canonical checkpoint status
- K.1–K.3: completed
- K.4: completed
- K.5: completed
- K.6: VERIFIED AND MERGED INTO EXP
- K.7: VERIFIED AND MERGED INTO EXP
- K.8: NOT STARTED
- K.9: NOT STARTED
- K.10: NOT STARTED

No K.8 or later implementation, experiment, or design execution was performed. Gates A-E remain unchanged.


## 2026-10-01 — Chat K.7 complete: professor-facing UI implementation verified and merged

K.7 implementation and verification are complete, audited, and merged into `exp` via PR #8 at commit `f1af4e1`.

### Implemented architecture
```text
Professor-Facing UI (demo/index.html)
       ↓
Local Bridge (demo/server.py) or Static Dataset (demo/scenarios_data.json)
       ↓
Virtual System Adapter & CLI (reference/virtual/src/virtual_demo_cli.c)
       ↓
SAME C Reference Runtime (reference/src/ref_runtime.c)
       ↓
Authoritative Decision (policy_decide, runtime_apply_policy)
       ↓
Correlated Inspectable Trace
```

### K.7 verification summary
- CTest suite: 5/5 passed (100%):
  1. `reference_tests` (Passed)
  2. `host_experiment_replay` (Passed)
  3. `virtual_system_tests` (Passed)
  4. `virtual_demo_test` (Passed)
  5. `virtual_ui_contracts_test` (Passed)
- Scenarios exposed and verified: S01, S02, S05, S06, S08, S14.
- Deterministic replay digests: verified equal across runs for all scenarios (S01: `0xB72131CB`, S02: `0xE8691374`, S05: `0xBDC168BD`, S06: `0xA123BB47`, S08: `0x5A52628A`, S14: `0x9185616C`).
- UI contract tests (`demo/test_ui_contracts.py`): verified scenario selection, step execution, policy authority, zero fabricated EventRefs on S08, trace sequence correlation, and pre-exported offline dataset completeness.
- Runtime authority: verified that `policy_decide()` and `runtime_apply_policy()` in `ref_runtime.c` remain the sole recovery engine. No peripheral-action callback added. No second recovery policy created. `ref_runtime.c` and `ref_runtime.h` unchanged.
- PR #8 merged into `exp` at commit `f1af4e1`.

### Current status
- K.1–K.3: completed
- K.4: completed
- K.5: completed
- K.6: VERIFIED AND MERGED INTO EXP
- K.7: VERIFIED AND MERGED INTO EXP
- K.8: VERIFIED AND MERGED INTO EXP
- K.9: NOT STARTED
- K.10: NOT STARTED


## 2026-10-01 — Chat K.8 complete: matched baseline validation verified and merged

K.8 implementation and verification are complete, audited, and merged into `exp` via PR #9 at merge commit `5590bf1`.

### Evaluated surface
1. **Host Experiment Corpus (70 runs):** 14 declarative workloads (W01–W14) evaluated across 5 policy variants (P0–P4).
2. **Virtual Demonstrator Matrix (30 runs):** 6 canonical scenarios (S01, S02, S05, S06, S08, S14) evaluated across P0–P4.
3. **Total evaluated runs:** 100 deterministic executions.

### Key findings
- **Persistent Faults (W06, S06):** Baseline P0 blindly retries twice and escalates to terminal failure (`OUTCOME_TERMINAL_ESCALATE`), while P1, P2, P3, and P4 progress to `ACT_REINIT_OR_RESET` on attempt 3, reinitialize the peripheral, and achieve recovery (`OUTCOME_SUCCESS`).
- **Ambiguous Association (W12, S08):** Baseline P0 blindly retries unmapped targets yielding `OUTCOME_STALE_REF` and leaves episodes unclosed; P4 enforces exact association (`ctx->association == ASSOC_EXACT`), immediately failing closed safely to `OUTCOME_TERMINAL_ESCALATE` with episode closed and zero synthetic EventRefs.
- **Graceful Degradation (W07):** P0 blindly escalates deferable work; P1–P4 cleanly transition deferable work to `TERMINAL_DEGRADE`.
- **Work Preservation & Blocking (W01/S01, W02/S02):** Unassociated work continues execution; dependent work remains blocked in `ST_QUEUED` during quarantine across all variants.

### Test suite status
- CTest suite: 7/7 passed (100%):
  1. `reference_tests` (Passed)
  2. `host_experiment_replay` (Passed)
  3. `virtual_system_tests` (Passed)
  4. `virtual_demo_test` (Passed)
  5. `virtual_baseline_tests` (Passed)
  6. `virtual_ui_contracts_test` (Passed)
  7. `matched_baseline_validation_test` (Passed)
- Runtime integrity verified: `ref_runtime.c` and `ref_runtime.h` remain completely unchanged.
- Post-merge verification on `exp`: 7/7 CTest passed; `evaluate_baselines.py --check` passed (100 runs); working tree clean.





