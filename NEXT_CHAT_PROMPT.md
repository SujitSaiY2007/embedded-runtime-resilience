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
# Active Next-Chat Prompt — K.9 Merge & Transition to K.10 (Final Software Packaging & Research Conclusion)

Continue the canonical project in:

`SujitSaiY2007/embedded-runtime-resilience`

Start from the verified K.9 implementation branch:

`feature/k9-methodology-lock-2026-10-01`

Base exp commit: `9ebd84c`

Do not repeat K.6–K.9 implementation work and do not execute K.10 packaging or physical hardware deployment in this chat.

## Objective

1. Review, audit, and merge the verified K.9 Methodology Lock and Software Re-Verification into `exp` via PR.
2. Advance to K.10: Final Software Packaging & Research Conclusion.
3. In K.10, prepare the final software-phase release, freeze documentation, package the research findings under the locked evidence boundaries, and conclude the software phase prior to target-MCU validation.

## Read first

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `NEXT_CHAT_PROMPT.md`
7. `research/PART_II_CHAT_PLAN.md`
8. `research/phase2_k9_methodology_lock.md`
9. `research/chat_records/chat_k9_record.md`
10. `reference/include/ref_runtime.h`
11. `reference/src/ref_runtime.c`

## Critical constraints

- The C reference runtime remains the sole recovery-policy authority.
- Do NOT modify `ref_runtime.c` or `ref_runtime.h`.
- Do NOT perform physical hardware integration or physical fault injection.
- Gates A–E remain frozen and normative.
- Enforce the locked limitations (quarantine symmetry, S06 multi-policy recovery, capacity confounds, software-only scope, prohibited claims).






