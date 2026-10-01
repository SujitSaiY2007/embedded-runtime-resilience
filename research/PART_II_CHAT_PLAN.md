# Part II — Multi-Chat Execution Plan

Part I: K.1-K.3 — COMPLETE
Part II: K.4-K.10 — ACTIVE
Reference branch: exp
Integrated mirror: main

## Global rules
1. Every chat starts from the latest exp state.
2. Every chat begins with a Continuity Check.
3. Every chat has exactly one checkpoint scope.
4. A chat must not execute work assigned to a later checkpoint.
5. Gates A-E are frozen and normative.
6. The C reference runtime remains authoritative.
7. UI and simulator layers must not implement a second recovery policy.
8. Every chat ends with a continuity record and exact next-chat handoff.
9. Completed checkpoints merge into exp.
10. Completed exp checkpoints are synchronized to main through an explicit PR/merge.
11. No software-only result is presented as hardware evidence.
12. Novelty remains a hypothesis until element-by-element prior-art analysis supports a defensible distinction.

## K.4 — Novelty Re-Research + Conceptual Architecture Lock
Objective: refresh prior art and lock the conceptual demonstrator architecture before coding.
Allowed: papers, patents, standards, products, open-source searches; claim-element matrix; overlap/differentiator analysis; simulator/runtime/UI boundaries; trace ownership; rejected novelty framings.
Out of scope: simulator implementation, UI implementation, Gates A-E changes, recovery-policy changes, hardware work, baseline experiments.
Deliverables: novelty investigation, conceptual architecture record, K.4 chat record, continuity updates.
Exit: bounded novelty hypothesis and architecture documented; otherwise explicitly incomplete.

## K.5 — Virtual Embedded System Technical Design
Objective: turn K.4 into implementable contracts.
Allowed: virtual MCU/peripheral models, I2C/SPI/UART models, event/workload model, deterministic fault injection API, simulator-to-C-runtime adapter, simulator-to-UI API/schema, trace/metrics schema, baseline interface boundary.
Out of scope: full implementation, UI polish, final comparison, hardware integration, recovery-policy redesign.
Deliverables: technical design, interfaces, scenarios, K.5 record, continuity.

## K.6 — Virtual Embedded System Implementation
Objective: implement the virtual system and connect it to the existing C reference runtime.
Allowed: virtual scheduler, peripherals, workloads, fault injection, runtime adapter, traces, focused tests.
Out of scope: full UI, new recovery logic, baseline superiority claims, hardware support.
Exit: a controlled fault travels through the actual C recovery runtime and produces an inspectable trace.

## K.7 — Professor-Facing UI Implementation
Objective: build the UI as the face of the working demonstrator.
Allowed: topology/status, queue view, fault controls, recovery action, verification/release/degrade/escalation, trace/explanation, metrics, scenarios, simulator integration.
Out of scope: recovery-policy changes, hidden recovery logic in UI, hardware claims, baseline experiment implementation.
Exit: the full software mechanism is observable without source-code inspection.

## K.8 — Matched Baseline vs Proposed Software Validation
Objective: compare proposed and baseline mechanisms under matched software workloads/fault schedules.
Allowed: baseline behavior, matched scenarios, recovery time, attempts, resets, events lost/delayed, quarantine, correctness, trace analysis, failure cases.
Out of scope: hardware claims, new mechanism design, uncontrolled comparisons, unsupported statistical claims.
Exit: controlled comparative evidence sufficient to evaluate the software hypothesis.

## K.9 — Full Software Re-Verification + Methodology Lock
Objective: re-verify the complete chain and freeze the software methodology.
Allowed: clean build/test, reference checks, simulator determinism/replay, UI integration, trace integrity, matched comparison checks, documentation reconciliation, evidence-boundary lock.
Out of scope: MCU integration, physical fault injection, hardware measurements, Gates A-E redesign.
Exit: software path is reproducible, demonstrable, traceable, and internally consistent.

## K.10 — Final Software Conclusion + Hardware-Validation Handoff
Objective: package the software proof of concept and establish the exact hardware-validation next step.
Allowed: final conclusion, professor-facing evidence summary, architecture documentation, bounded novelty statement, hardware-validation requirements and success criteria, final continuity.
Out of scope: final novelty/patentability claim; unproduced hardware evidence; hardware implementation unless separately authorized.
Exit: Part II is complete as a software proof-of-concept and methodology-lock phase.

## Scope escalation rule
If a later dependency is discovered: document it, do not implement it, add it to the next handoff, and stop at the current boundary.

## K.5 completion update — 2026-10-01

K.5 is COMPLETE at the technical-design/contract level. The virtual system, peripheral contracts, deterministic fault injection, C-runtime adapter boundary, runtime I/O, UI authority boundary, ownership rules and S01-S14 deterministic scenarios are documented.

K.6 is now the active implementation checkpoint. It may implement only the K.5 contracts around the existing C reference runtime.

K.6 must not modify the recovery policy, add a second recovery engine, or silently add a peripheral-action callback to the C runtime. The current runtime API remains the integration boundary unless a separate design decision explicitly authorizes a change.


## K.6 completion update — 2026-10-01

K.6 is COMPLETE, VERIFIED, and MERGED into `exp` via PR #7 (merge commit `b161589`).

Verified surface:
- bounded virtual scenario/workload structures;
- I2C/SPI/UART environmental records;
- immutable fault schedules;
- existing-runtime adapter using unchanged `ref_runtime.h`/`ref_runtime.c`;
- EventRef/dependency mapping with no synthetic EventRefs;
- correlated wrapper/runtime trace records;
- deterministic replay digest equality;
- focused S01/S02/S05/S06/S08/S14 tests passed under CTest (3/3 passed).

Status:
- K.1–K.3: completed
- K.4: completed
- K.5: completed
- K.6: VERIFIED AND MERGED INTO EXP
- K.7: VERIFIED AND MERGED INTO EXP
- K.8: VERIFIED AND MERGED INTO EXP
- K.9: CLOSED AND MERGED INTO EXP
- K.10: NOT STARTED

## K.7 completion and merge update — 2026-10-01

K.7 Professor-Facing UI is VERIFIED AND MERGED into `exp` (PR #8, merge commit `f1af4e1`).

Implemented surface:
- `demo/index.html`: Web front-end demonstrator with scenario selection, execution controls, pipeline indicator, live event slot inspector, peripheral mirror, and interactive trace correlation.
- `demo/server.py`: Lightweight Python local server proxying requests to the compiled C binary.
- `demo/scenarios_data.json`: Offline authoritative dataset allowing instant in-browser demonstration without external tooling.
- `reference/virtual/src/virtual_demo_cli.c`: CLI tool for JSON state serialization, step execution, and verification.
- `reference/virtual/include/virtual_scenarios.h` & `src/virtual_scenarios.c`: Canonical scenario registry for S01, S02, S05, S06, S08, S14.
- `demo/test_ui_contracts.py`: Comprehensive test suite verifying contract integrity, policy authority, trace correlation, and determinism.
- CTest suite passing 5/5 targets (100%).

K.7 preserves single-policy authority in `ref_runtime.c`. No recovery logic or peripheral callback was added to the UI.

## K.8 completion and merge update — 2026-10-01

K.8 Matched Baseline vs Proposed Software Validation is VERIFIED AND MERGED into `exp` (PR #9, merge commit `5590bf1`).

Implemented surface:
- `reference/experiments/evaluate_baselines.py`: Comprehensive comparative evaluation harness for 70 host runs (W01–W14 × P0–P4) and 30 virtual demonstrator runs (S01–S14 × P0–P4) = 100 total runs.
- `reference/virtual/tests/test_virtual_baselines.c`: C11 unit assertions testing baseline progression, persistent fault escalation vs reinit recovery, stale ref handling vs fail-closed escalation, unassociated work preservation, and deterministic replay.
- `research/phase2_k8_matched_baseline_validation.md`: Structured comparative evidence report documenting metric tables, scenario matrices, and qualification locks.
- CTest suite expanded to 7 targets (100% passing).
- Authority preserved: `ref_runtime.c` and `ref_runtime.h` unchanged.

Next checkpoint: K.9 (Full Software Re-Verification + Methodology Lock).

## K.9 completion and merge update — 2026-10-01

K.9 Full Software Re-Verification + Methodology Lock is CLOSED AND MERGED into `exp` (PR #10, merge commit `d1e0dcb`).

Implemented surface:
- `research/phase2_k9_methodology_lock.md`: Formal methodology lock freezing experimental dimensions A through O, locking limitations (quarantine symmetry, S06 multi-policy recovery, capacity confounds, software-only scope, prohibited claims), and clarifying scenario scope (S01–S14 vs 6-scenario demonstrator subset).
- `research/chat_records/chat_k9_record.md`: Canonical chat record for K.9.
- `DECISION_LOG.md`: Added architectural decisions `D-110` and `D-111`.
- S06/P2 Reconciliation: Authoritative digest `0xCDAB2617` confirmed across 100-run baseline validation and 10/10 independent replay runs.
- Complete CTest suite passing 7/7 (100%).
- Full 100-run baseline reproduction verified with zero divergence.
- Authority preserved: `ref_runtime.c` and `ref_runtime.h` 100% unchanged.

Next checkpoint: K.10 (Final Software Packaging & Research Conclusion).











## Active Scope Override — K.9.2 (2026-10-01)

K.9 is historically CLOSED and remains unchanged. The previous K.10 “Final Software Conclusion + Hardware-Validation Handoff” definition is **superseded as the active next-step definition**.

### K.9.2 — P4 Advantage & Novelty Investigation Design Lock
Objective: systematically determine **where meaningful P4 advantage could exist** before any final research conclusion, and lock the experimental/measurement/prior-art design without predetermining the outcome.

Required dimensions:
- outcome resilience;
- recovery attempts/actions/redundant retries;
- recovery latency where faithfully measurable;
- state-transition cost;
- scheduler/context-switch cost only if the software model can validly expose it;
- work preservation/re-execution/lost or delayed work;
- fault containment;
- escalation quality;
- resource/CPU/step/storage/communication cost where valid;
- memory/static overhead;
- policy-decision cost where valid;
- resilience overhead per recovery;
- decision accuracy;
- adaptability across transient/persistent/intermittent/recurring faults;
- workload, dependency, criticality and queue-pressure effects;
- compound-fault interactions;
- graceful degradation;
- worst-case behavior;
- determinism/predictability as a validation property;
- complexity-vs-benefit trade-offs.

K.9.2 must enumerate the scenario/fault/history/workload/resource/association combinations that can meaningfully differentiate P4 from P0-P3, including negative/no-advantage cases. Compound cases are a priority because integrated context/history behavior may only become observable under interactions.

K.9.2 must also lock the novelty-search decomposition: individual elements, pairwise combinations, higher-order combinations, and whole-combination disclosures across papers, patents, standards and technical systems. Novelty and inventive step/non-obviousness remain separate questions.

K.9.2 does **not** run the decisive advantage matrix or make a superiority/novelty conclusion.

### K.10 — P4 Advantage & Novelty Investigation
K.10 follows K.9.2 and executes the locked design:
- implement only approved non-invasive measurement/instrumentation changes;
- run matched advantage/interaction experiments;
- analyze P4 vs P0-P3 at metric level, including trade-offs and baseline-advantage cases;
- perform the deeper adversarial prior-art search;
- produce evidence-bounded findings.

K.10 is **not** a predetermined proof of P4 superiority or novelty.

### Later conclusion boundary
A later checkpoint, after K.10 evidence is complete, will perform final synthesis and hardware-validation handoff. Do not move that conclusion into K.9.2 or K.10 merely for convenience.

### Antigravity execution rule
ChatGPT is the research-control/audit layer. Antigravity is the repository execution agent. Each chat must give Antigravity an exact bounded scope, require repository inspection from latest `exp`, preserve historical records, and return exact branch/commit/test/working-tree status. Antigravity must not invent new P4 behavior or a new policy merely to manufacture a measurable advantage.
