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
- K.6: VERIFIED AND MERGED
- K.7: NOT STARTED

K.7 is now the active checkpoint: Professor-Facing UI Implementation.

