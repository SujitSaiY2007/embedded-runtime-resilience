# Next Chat Prompt — K.4: Integrated Software Proof of Concept and Methodology Lock

Continue the canonical project in:

SujitSaiY2007/embedded-runtime-resilience

Do not restart Gates A-E or repeat K.1/K.2/K.3 work.

## Read first

1. PROJECT_MANUAL.md
2. PROJECT_STATE.md
3. CURRENT_HANDOFF.md
4. DECISION_LOG.md
5. CHAT_CONTINUITY_PROTOCOL.md
6. research/phase1_software_demonstrator_methodology_lock.md
7. research/phase1_final_evidence_synthesis.md
8. research/phase1_reference_implementation_audit.md
9. research/phase1_host_corpus_validation.md
10. research/phase1_gateA_event_model_final.md
11. research/phase1_gateB_fault_model_final.md
12. research/phase1_gateC_recovery_policy_final.md
13. research/phase1_gateD_formal_properties_final.md
14. research/phase1_gateE_experimental_protocol_final.md
15. reference/README.md
16. reference/experiments/README.md
17. demo/README.md

## Current objective

Build and finalize the complete software-only proof of concept that will be shown to the professor.

Professor verification is NOT a separate project stage. It is the intended use of this integrated software checkpoint.

The desired chain is:

Gates A-E
-> reference implementation
-> host verification
-> corpus validation
-> software demonstrator
-> re-verification
-> methodology lock
-> final software-phase conclusion
-> target-MCU validation

## What the demonstrator must show

Make the mechanism understandable end-to-end:

fault observation
-> evidence-bounded association
-> event quarantine
-> context/history-aware bounded recovery
-> verification
-> release/degrade/escalate
-> trace/explanation

Keep the C reference implementation authoritative. Do not silently create a competing specification in the UI.

## Re-verification requirements

Re-run or confirm:

- clean CMake build;
- CTest;
- host experiment --check;
- deterministic replay;
- matched-input equivalence;
- raw-input preservation;
- capacity-confound flagging;
- ablation-contract flagging;
- representative trace/outcome inspection;
- software demonstrator scenario coherence.

## Locked limitations

1. P0-P3 are not clean quarantine ablations because exact-event quarantine is currently shared across variants.
2. W09/W10 are capacity-confounded.
3. Host/reference evidence is not MCU/physical evidence.
4. Host C-layout values are not STM32U575 RAM/Flash measurements.
5. Novelty and patentability are not established merely by the software checkpoint.

Do not hide or redefine these limitations to make the project appear stronger.

## Required conclusion

End this checkpoint with a clear software-phase conclusion:

The mechanism is sufficiently specified, implemented, reproducible, demonstrable, and evidence-bounded to justify target-MCU validation.

Do NOT say that hardware performance, statistical superiority, final novelty, or patentability has already been proven.

## Repository requirement

Update all necessary current-state documentation, preserve historical records, identify genuinely redundant files before deletion, and ensure main can represent the most defensible integrated state.

When complete, verify the branch and merge/push the software-phase package to main if the user has authorized that action.

---
# Part-II K.4 Active Scope Override

Part I (K.1-K.3) is COMPLETE. Part II begins at K.4.

The active K.4 scope is **Novelty Re-Research + Conceptual Architecture Lock**. Do not implement the virtual system or UI in K.4. Do not alter Gates A-E or the recovery policy.

Use the current Part-II plan in research/PART_II_CHAT_PLAN.md as the scope authority.

Branch rule: exp is the active reference branch; main is the integrated mirror synchronized through PR/merge.

At K.4 completion, the next checkpoint is K.5 — Virtual Embedded System Technical Design + Interface Contracts.


---
# Active Next-Chat Override — K.5

The earlier K.4 prompt above is preserved as historical project planning.

The next chat must execute **K.5 — Virtual Embedded System Technical Design + Interface Contracts** only.

Read first:
1. PROJECT_MANUAL.md
2. PROJECT_STATE.md
3. CURRENT_HANDOFF.md
4. DECISION_LOG.md
5. CHAT_CONTINUITY_PROTOCOL.md
6. NEXT_CHAT_PROMPT.md
7. research/PART_II_CHAT_PLAN.md
8. research/novelty_investigation.md
9. research/part_ii_conceptual_architecture.md
10. research/chat_records/chat_k4_record.md

K.5 allowed:
- virtual scheduler/environment design;
- virtual I2C/SPI/UART contracts;
- deterministic fault-injection API;
- simulator-to-C-runtime adapter contract;
- runtime input/output schemas;
- UI-facing state/trace schema;
- baseline interface boundary;
- deterministic scenario contracts;
- ownership/identity/resource boundaries.

K.5 prohibited:
- simulator implementation;
- UI implementation;
- recovery-policy redesign;
- Gates A-E changes;
- hardware integration;
- K.6/K.7/K.8/K.9/K.10 execution.

Required K.5 outputs:
1. virtual-system technical design;
2. interface/contract document;
3. deterministic scenario definitions;
4. research/chat_records/chat_k5_record.md;
5. PROJECT_STATE.md;
6. CURRENT_HANDOFF.md;
7. DECISION_LOG.md when needed;
8. NEXT_CHAT_PROMPT.md for K.6.

Exit only when K.6 has an unambiguous implementation starting point.


---
# Active Next-Chat Prompt — K.6

Continue the canonical project in:

SujitSaiY2007/embedded-runtime-resilience

Start from the latest exp state after K.5 has been merged back to exp. Do not repeat K.5 design work and do not execute K.7 or later work.

## Read first
1. PROJECT_MANUAL.md
2. PROJECT_STATE.md
3. CURRENT_HANDOFF.md
4. DECISION_LOG.md
5. CHAT_CONTINUITY_PROTOCOL.md
6. NEXT_CHAT_PROMPT.md
7. research/PART_II_CHAT_PLAN.md
8. research/part_ii_conceptual_architecture.md
9. research/part_ii_virtual_system_technical_design.md
10. research/part_ii_interface_contracts_k5.md
11. research/part_ii_deterministic_scenarios_k5.md
12. research/chat_records/chat_k5_record.md
13. reference/include/ref_runtime.h
14. reference/src/ref_runtime.c
15. reference/tests/test_reference.c

## K.6 objective
Implement the bounded virtual embedded system and connect it to the SAME existing C reference runtime using the K.5 contracts.

## Allowed
- virtual scheduler/environment implementation;
- bounded workload/scenario representation;
- virtual I2C/SPI/UART environmental models;
- immutable deterministic fault schedules;
- runtime adapter using existing ref_runtime.h API;
- EventRef/dependency mapping;
- deterministic trace correlation;
- focused K.6 tests and replay checks.

## Explicitly prohibited
- recovery-policy redesign;
- new recovery algorithm;
- new policy variant;
- UI implementation/polish;
- baseline comparison experiment;
- hardware/STM32U575 integration;
- physical fault injection;
- Gates A-E changes;
- K.7-K.10 execution.

## Critical implementation constraint
The current runtime has no peripheral-action callback. Do NOT silently modify runtime_apply_policy(), policy_decide(), or the recovery mechanism to create one. If K.6 needs environmental action visualization, mirror the predeclared deterministic outcome schedule while keeping the C runtime authoritative for policy transition and verification. If a true callback boundary is judged necessary, document the issue and stop rather than redesigning the runtime.

## Runtime authority
The C runtime remains authoritative for EventRef identity, dependency eligibility, quarantine, recovery action selection, attempt progression, verification/release, terminal outcome, and trace facts.

## Required K.6 exit
A controlled deterministic scenario must travel through the virtual environment, the existing C runtime, and back to an inspectable correlated trace without introducing a second recovery policy.

At the end update PROJECT_STATE.md, CURRENT_HANDOFF.md, DECISION_LOG.md if new decisions arise, research/chat_records/chat_k6_record.md, and NEXT_CHAT_PROMPT.md. Preserve K.5 history.


---
---
---
# Active Next-Chat Prompt — K.10: Final Software Packaging & Research Conclusion

Continue the canonical project in:

`SujitSaiY2007/embedded-runtime-resilience`

Start from the canonical merged and closed K.9 `exp` checkpoint:

`exp @ d1e0dcb`

Do not restart Gates A–E, repeat K.1–K.9 work, or alter the C reference runtime.

## Objective

Execute **K.10 — Final Software Packaging & Research Conclusion**.

Package the complete software proof of concept, freeze canonical software-phase documentation, synthesize the research findings under the locked evidence boundaries, and establish the exact handoff to target-MCU validation.

## Read first

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `NEXT_CHAT_PROMPT.md`
7. `research/PART_II_CHAT_PLAN.md`
8. `research/phase2_k9_methodology_lock.md`
9. `research/phase2_k8_matched_baseline_validation.md`
10. `research/chat_records/chat_k9_record.md`
11. `reference/include/ref_runtime.h`
12. `reference/src/ref_runtime.c`

## Allowed in K.10

- Final software-phase release packaging and documentation freeze;
- Synthesis of software evidence across 100 deterministic runs (W01–W14, S01–S14, P0–P4);
- Bounded novelty and differentiation statement based strictly on software findings;
- Definition of target-MCU hardware-validation requirements, testbed specification, and success criteria;
- Final Part II continuity and repository closure.

## Explicitly Prohibited in K.10

- Physical MCU hardware experiments, acquisition assumptions, or physical fault injection;
- Altering Gates A–E or modifying `ref_runtime.c` / `ref_runtime.h`;
- Introducing new recovery policies or a second scheduler;
- Claiming universal superiority of P4;
- Claiming novelty or patentability beyond bounded software differentiation;
- Removing or redefining locked qualifications (`capacity_confounded=1`, `ablation_contract_valid=0`, S06 multi-policy recovery, software-only scope).

## Required K.10 Conclusion

Conclude with a clear, evidence-based software-phase conclusion:
"The mechanism is sufficiently specified, implemented, reproducible, demonstrable, and evidence-bounded to justify target-MCU validation."











---

# ACTIVE NEXT-CHAT PROMPT — K.9.2

Continue the canonical project in:

`SujitSaiY2007/embedded-runtime-resilience`

Start from the latest `exp` state. At the time this prompt was prepared, the K.9 canonical closure was `72edc4f86986c868b2e7102c192441d069c6dba7`; first verify the actual latest `exp` head before doing anything.

## Mission

Execute **K.9.2 — P4 Advantage & Novelty Investigation Design Lock** ONLY.

This chat exists because K.9 methodology lock is not a final proof of P4 superiority or novelty. We must first determine every defensible place where P4 could have a meaningful advantage, including non-success metrics, interactions, trade-offs and compound cases, and lock the novelty-search strategy.

## Mandatory startup

Use **Antigravity** as the repository execution agent.

Antigravity MUST:
1. inspect the latest `exp` branch and working tree first;
2. read:
   - `PROJECT_MANUAL.md`
   - `PROJECT_STATE.md`
   - `CURRENT_HANDOFF.md`
   - `DECISION_LOG.md`
   - `CHAT_CONTINUITY_PROTOCOL.md`
   - `research/PART_II_CHAT_PLAN.md`
   - `research/phase2_k9_methodology_lock.md`
   - `research/phase2_k8_matched_baseline_validation.md`
   - `research/phase2_k9_2_p4_advantage_novelty_design.md`
   - `research/chat_records/chat_k9_record.md`
   - existing experiment/virtual-system source and reports needed to assess measurement availability;
3. verify that `reference/src/ref_runtime.c` and `reference/include/ref_runtime.h` remain unchanged;
4. report the exact starting commit before modifications.

## K.9.2 work to perform

### A. Build the P4 Advantage Matrix
For each candidate dimension, classify:
- measurable now;
- measurable with non-invasive instrumentation;
- not faithfully measurable in the current model;
- existing evidence available;
- new K.10 experiment required;
- possible P4 advantage;
- possible baseline advantage;
- possible trade-off;
- no expected differentiator.

Required dimensions:
1. outcome resilience;
2. recovery attempts/actions/redundant retries;
3. detection/decision/recovery latency where valid;
4. state-transition count/cost;
5. scheduler/context-switch cost only if genuinely represented;
6. work preserved, re-executed, lost/delayed;
7. fault containment;
8. retry efficiency;
9. escalation quality;
10. CPU/step/resource cost;
11. memory/static/trace overhead;
12. policy decision cost if valid;
13. resilience overhead per successful recovery;
14. decision accuracy;
15. adaptability across fault classes;
16. workload/queue/dependency/criticality effects;
17. compound-fault interactions;
18. graceful degradation;
19. worst-case behavior;
20. determinism/predictability;
21. complexity-vs-benefit trade-off.

### B. Exhaust the scenario-combination space
Map current coverage and identify valid missing cases across:
- transient/persistent/intermittent/recurring faults;
- first/repeated/consecutive/alternating faults;
- prior success/prior failure/prior escalation;
- low/high load and queue pressure;
- dependency chains and independent work;
- mixed critical/deferable work;
- early/middle/late queue position;
- peripheral/event/resource faults;
- recovery-resource contention;
- exact/ambiguous/invalid/stale association;
- fault during recovery;
- fault after previous recovery;
- compound combinations.

Prioritize combinations where context/history integration can actually differ from P0-P3. Include explicit no-difference/negative controls. Do not cherry-pick only favorable cases.

### C. Preserve attribution locks
Do not attribute the following to unique P4 advantages:
- shared exact-event quarantine;
- S06 persistent-fault recovery, because P1/P2/P3/P4 also succeed;
- W09/W10 capacity-bound outcomes;
- any metric not supported by the actual model.

Keep P2's S06 path distinct: authoritative digest `0xCDAB2617`.

### D. Novelty investigation design
Decompose P4 into:
- context-aware decision;
- bounded recovery history;
- fixed recovery ladder;
- peripheral recovery;
- evidence-bounded fault-to-event association;
- event-level quarantine/retention;
- dependency/order-aware preservation;
- deterministic verification/release/escalation;
- zero-heap/static bounded implementation;
- their specific integrated interaction.

Define the K.10 search across:
- academic papers;
- patents/patent families;
- standards/technical systems;
- embedded/RTOS/bare-metal implementations;
- driver/transaction/event/message quarantine;
- safety-critical fault management.

Search individual, pairwise, higher-order and whole-combination disclosures. Treat the existing novelty record as a starting point, not a conclusion.

### E. Define falsification
K.9.2 must explicitly allow:
- no P4 advantage;
- conditional P4 advantage;
- P4 advantage with overhead;
- baseline advantage on some metrics;
- prior art that materially weakens the integrated novelty hypothesis.

## Hard prohibitions

DO NOT:
- run the decisive K.10 advantage experiment matrix;
- perform the final prior-art investigation intended for K.10;
- modify Gates A-E;
- modify `ref_runtime.c` or `ref_runtime.h`;
- redesign P4;
- add a new policy variant;
- add a second recovery engine/scheduler;
- fabricate MCU timing, RAM/Flash, context switches, energy or physical hardware metrics;
- claim superiority, novelty, patentability or universal generalization.

If a measurement is impossible, record it as unavailable and define the closest defensible software-level alternative. Do not change the mechanism merely to make it measurable.

## Required outputs

Create/update:
1. `research/phase2_k9_2_p4_advantage_novelty_design.md`
2. `research/chat_records/chat_k9_2_record.md`
3. `research/PART_II_CHAT_PLAN.md`
4. `CURRENT_HANDOFF.md`
5. `PROJECT_STATE.md`
6. `DECISION_LOG.md` if a new decision is required
7. `NEXT_CHAT_PROMPT.md` with the K.10 execution prompt

Preserve all historical K.1-K.9 records exactly; do not rewrite history to reflect the new roadmap.

## Exit condition

K.9.2 is complete only when the repository contains an auditable, non-predetermined K.10 design answering:
- What could make P4 meaningfully better?
- What could make P4 worse or equivalent?
- Which metrics can actually be measured?
- Which scenario combinations can reveal an interaction?
- What controls prevent cherry-picking?
- What exactly will be searched for in prior art?
- What evidence would falsify the P4 advantage or novelty hypothesis?

Then commit/push the K.9.2 work and report:
- branch;
- exact commit;
- files changed;
- tests/checks performed;
- `ref_runtime.c/.h` integrity;
- working-tree status;
- exact K.10 starting point.

STOP. Do not begin K.10 in this chat.


# ACTIVE NEXT-CHAT PROMPT — K.10: P4 Advantage & Novelty Investigation

Continue the canonical project in:

`SujitSaiY2007/embedded-runtime-resilience`

Start from the exact post-K.9.2 `exp` commit reported by the previous chat. Do not restart K.1-K.9. Do not execute any later final-synthesis/hardware-handoff checkpoint.

## Mission

Execute **K.10 — P4 Advantage & Novelty Investigation** only.

K.9.2 established a non-predetermined design. K.10 must now test it. A positive P4 result is not assumed.

## Read first

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `research/PART_II_CHAT_PLAN.md`
7. `research/phase2_k9_methodology_lock.md`
8. `research/phase2_k8_matched_baseline_validation.md`
9. `research/phase2_k9_2_p4_advantage_novelty_design.md`
10. `research/chat_records/chat_k9_record.md`
11. `research/chat_records/chat_k9_2_record.md`
12. `research/novelty_investigation.md`
13. `reference/include/ref_runtime.h`
14. `reference/src/ref_runtime.c`
15. relevant host/virtual experiment and scenario sources

## Antigravity execution requirement

Use **Antigravity as the repository execution agent**.

Before any modification Antigravity must:
- verify latest `exp` HEAD and working-tree state;
- report the exact starting commit;
- read the K.9.2 lock and continuity files;
- verify `ref_runtime.c/.h` integrity;
- identify the minimum instrumentation required.

Antigravity must not invent P4 behavior, alter shared semantics merely to improve a metric, or create a second recovery policy.

## A. Execute the approved measurement plan

Use the K.9.2 classifications.

### Execute directly where already supported
- terminal outcomes;
- recovery attempts/actions;
- authoritative trace transitions;
- stale/association outcomes;
- deterministic replay;
- host/reference static accounting;
- virtual step counts where explicitly labelled as model metrics.

### Add only non-invasive instrumentation where required
Potential additions:
- explicit logical transition counters;
- logical stage-distance counters;
- work-disposition accounting;
- policy-decision operation counters;
- scenario oracle labels.

Do not convert any of these into MCU timing, RTOS context-switch, RAM/Flash, energy or electrical claims.

### Do not implement
- hardware timing;
- physical fault models;
- RTOS context-switch counters not represented by the model;
- MCU resource claims;
- a redesigned P4 policy;
- a new baseline mechanism.

## B. Run the locked matched scenario families

At minimum include:
1. persistent fault + repeated history + dependent queued work;
2. persistent fault + high queue load;
3. intermittent same-resource fault + prior recovery;
4. prior recovery failure + new fault;
5. prior escalation + new fault;
6. ambiguous association + high workload;
7. fault during recovery + dependency chain;
8. mixed critical/deferable work + persistent fault;
9. repeated fault + recovery/resource contention;
10. fault after successful reinitialization;
11. alternating fault classes;
12. early/middle/late queue-position controls;
13. low-load/high-load matched controls;
14. explicit no-difference controls;
15. baseline-advantage/cost controls.

Preserve W09/W10 `capacity_confounded=1`.

## C. Attribution rules

Do not claim a P4 advantage from:
- shared exact-event quarantine;
- S06 persistent-fault recovery alone;
- capacity-confounded W09/W10;
- deterministic behavior shared by all policies;
- any metric unsupported by the software model.

P2 S06 must retain digest `0xCDAB2617`.

Classify every result only as:
- P4 advantage;
- P4 neutral;
- P4 trade-off/cost;
- baseline advantage;
- inconclusive.

Do not create an overall score, ranking, tier or composite winner.

## D. Compound interaction analysis

Prioritize interactions among:
- history × fault persistence;
- history × queue pressure;
- association ambiguity × workload;
- fault during recovery × dependency;
- recovery failure × subsequent fault;
- criticality × persistent fault;
- resource contention × repeated fault.

Use matched controls to determine whether the interaction actually changes policy behavior.

## E. Novelty/prior-art investigation

Perform the deeper adversarial search across:
- academic literature;
- patents/patent families;
- standards/technical systems;
- embedded/RTOS/bare-metal implementations;
- peripheral/driver recovery;
- event/message/transaction quarantine;
- safety-critical fault management.

Search:
1. individual elements;
2. pairwise combinations;
3. three-or-more-element combinations;
4. whole-combination disclosures.

For each relevant reference record:
- what elements it discloses;
- what it does not disclose;
- technical environment;
- overlap;
- whether it weakens/falsifies the integrated hypothesis.

Do not treat “no identical reference found” as proof of novelty. Keep novelty separate from inventive step/non-obviousness and legal patentability.

## F. Required outputs

Update/create:
- `research/phase2_k10_p4_advantage_novelty_results.md`;
- `research/chat_records/chat_k10_record.md`;
- `research/PART_II_CHAT_PLAN.md`;
- `PROJECT_STATE.md`;
- `CURRENT_HANDOFF.md`;
- `DECISION_LOG.md` if required;
- `NEXT_CHAT_PROMPT.md` for the downstream final synthesis/hardware-validation checkpoint.

Preserve K.1-K.9.2 historical records exactly.

## Hard stop

Do not:
- claim universal P4 superiority;
- claim novelty/patentability as established;
- perform hardware experiments;
- modify Gates A-E;
- modify `ref_runtime.c/.h` unless a separately approved defect is proven and the checkpoint is explicitly re-scoped;
- begin final software packaging/hardware handoff.

K.10 is complete only when the repository contains auditable metric-level results, compound-interaction analysis, adversarial prior-art evidence, explicit limitations, and falsification outcomes.

Then report exact branch, commit, tests/checks, runtime integrity, working-tree status and the exact downstream starting point. STOP.


---

# ACTIVE CONTINUITY NOTICE — K.10 STARTING POINT (2026-10-01)

The **active K.10 prompt is the final section above this notice** and supersedes all earlier/historical K.4–K.10 prompts retained in this file for continuity. Do not follow the obsolete earlier “K.10 Final Software Packaging & Research Conclusion” prompt.

Canonical K.9.2 completion commit on `exp`:
`04308f0fc797892da51e2265edfc57b810d0acd9`

K.10 scope: **P4 Advantage & Novelty Investigation only**. Execute the locked measurement/experiment matrix and adversarial prior-art investigation. Do not predetermine superiority or novelty. Do not perform final synthesis or hardware validation in K.10.

Antigravity is the repository execution agent. It must verify the live `exp` HEAD equals the expected K.9.2 starting point (or explicitly reconcile any legitimate intervening commit), inspect the working tree and protected runtime integrity, read the K.9.2 design/continuity files first, and return exact branch/commit/test/status information.


---

# DOWNSTREAM CHECKPOINT TEMPLATE — K.11 (ACTIVATES ONLY AFTER K.10 COMPLETES)

Continue the canonical project in:

SujitSaiY2007/embedded-runtime-resilience

Branch: `exp`. Use the latest K.10-complete commit as the starting state. Do not execute this checkpoint until K.10 has produced its auditable advantage/interaction results and adversarial prior-art evidence.

## K.11 — Final Software Synthesis + Hardware-Validation Handoff

Read first:
1. PROJECT_MANUAL.md
2. PROJECT_STATE.md
3. CURRENT_HANDOFF.md
4. DECISION_LOG.md
5. CHAT_CONTINUITY_PROTOCOL.md
6. research/PART_II_CHAT_PLAN.md
7. research/phase2_k10_p4_advantage_novelty_results.md
8. research/chat_records/chat_k10_record.md
9. all relevant K.9/K.9.2 methodology and evidence records

### Mission
K.11 is the final software-phase synthesis and hardware-validation handoff. It must derive the conclusion from K.10 evidence rather than manufacture a preferred result.

### Required work
- reconcile K.10 metric-level results, interaction findings, trade-offs, baseline advantages and inconclusive cases;
- reconcile the adversarial prior-art findings and distinguish technical novelty from inventive step/non-obviousness and legal patentability;
- produce the evidence-bounded final software conclusion;
- prepare the professor-facing final evidence/architecture package;
- define target-MCU hardware-validation requirements, testbed specification, instrumentation, scenarios, controls, success/failure criteria, and evidence boundaries;
- update continuity/state/decision records and produce the next hardware-validation/refinement handoff.

### Hard boundaries
- do not redesign P4 merely to improve K.10 results;
- do not retroactively change K.10 methodology to force a conclusion;
- do not claim hardware results before hardware validation;
- do not claim universal superiority, novelty, patentability, or statistical generalization unless the evidence actually supports the precisely stated claim;
- do not modify Gates A-E or protected reference runtime unless separately defect-approved and re-scoped.

### Antigravity
Use Antigravity as the repository execution agent. It must inspect the latest `exp` state, preserve historical records, verify protected runtime integrity, make only K.11 documentation/synthesis/handoff changes, and return exact branch/commit/tests/status.

### Exit
K.11 is complete when the final software-phase conclusion is evidence-bounded, the professor-facing package is coherent, the target-MCU validation plan is reproducible, all continuity files are updated, and the exact next hardware-validation/refinement starting point is recorded.

STOP after K.11. Do not begin hardware implementation in K.11 unless explicitly re-scoped.
