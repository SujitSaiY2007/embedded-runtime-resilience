# Next Chat Prompt — Chat K.3: Final Synthesis

Copy/paste the following prompt into the next ChatGPT chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

This is **Chat K.3**, continuing directly from **Chat K.2**. Do not restart the project or repeat K.1/K.2 execution work.

## Mandatory startup reading

Read, in order:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `research/phase1_reference_implementation_audit.md`
7. `research/phase1_host_corpus_validation.md`
8. `research/phase1_gateA_event_model_final.md`
9. `research/phase1_gateB_fault_model_final.md`
10. `research/phase1_gateB_learning_summary.md`
11. `research/phase1_gateC_recovery_policy_final.md`
12. `research/phase1_gateD_formal_properties_final.md`
13. `research/phase1_gateE_experimental_protocol_final.md`
14. `research/phase1_reference_implementation_design.md`
15. `reference/README.md`
16. `reference/docs/minimal_reference_implementation.md`
17. `reference/tests/canonical_workloads.md`
18. `reference/experiments/README.md`
19. `research/chat_records/chat_k1_k2_record.md`

Then give a concise continuity check. Do not repeat the entire research history.

## Frozen state

Gates A-E are frozen and normative.

The current host checkpoint branch is:

`experiment/host-p0-p4-corpus-2026-10-01`

Chat K.1 verified:

- Windows/MSVC build succeeds.
- CTest passes 2/2.
- The host experiment check passes all five reproducibility/metadata checks.
- 70 matched runs exist: W01-W14 × P0-P4.

Chat K.2 then regenerated and inspected the corpus and recorded:

- manifest PASS for deterministic replay;
- matched-input equivalence PASS;
- raw-input preservation PASS;
- capacity-confound flagging PASS;
- ablation-contract flagging PASS;
- host-only evidence boundary;
- no concrete corpus-generation, serialization, or runtime defect in the inspected evidence.

## Important limitations that MUST remain visible

1. **P0-P3 are not clean quarantine ablations.**
   `runtime_start_fault()` applies exact-event quarantine across all variants. Therefore P0-P3 remain `ablation_contract_valid=0`; P4 is the only variant marked valid under the current implementation boundary.

2. **W09/W10 are capacity-confounded.**
   Preserve that qualification in any later analysis.

3. **Host/reference evidence is not MCU/physical evidence.**
   Do not convert the corpus into claims about STM32U575 timing, RAM/Flash, energy, electrical fault behavior, or physical recovery.

4. Do not claim statistical significance, generalization, novelty, or patentability merely from the current host corpus.

## ONLY TASK FOR CHAT K.3

Perform the **final evidence-bounded synthesis and repository packaging**.

### 1. Evidence audit

Create a concise evidence matrix separating:

- frozen design/specification evidence;
- host/reference correctness evidence;
- host corpus/reproducibility evidence;
- MCU evidence: absent;
- physical fault/recovery evidence: absent;
- remaining ablation/evidence limitations.

Do not rank or score the project. Do not manufacture missing measurements.

### 2. Research interpretation

Determine exactly what can and cannot be concluded from the current evidence.

In particular, distinguish:

- implementation correctness vs research hypothesis support;
- harness correctness vs policy correctness;
- reproducibility vs external validity;
- model-level evidence vs hardware evidence.

### 3. Final repository consistency review

Check that the continuity documents agree on:

- K.1 completion;
- K.2 completion;
- current branch/checkpoint;
- P0-P3 ablation limitation;
- W09/W10 capacity limitation;
- host-only evidence boundary;
- K.3 scope.

Do not rewrite historical artifacts unnecessarily. Prefer additive corrections and explicit supersession.

### 4. Final project-facing documentation

Prepare the minimum necessary final documentation for the current stage, such as:

- final project status;
- evidence/limitations summary;
- reproducibility instructions;
- known limitations and deferred validation;
- final continuation/archive note.

Do not create fake experimental measurements or imply that hardware validation occurred.

### 5. Do NOT do these things

Do not:

- redesign Gates A-E;
- change P0-P4 semantics just to improve comparisons;
- integrate the MCU solely because K.2 is complete;
- add unrelated features;
- fabricate performance numbers;
- claim a novelty winner or patentability conclusion;
- delete historical research artifacts.

## Completion condition

Stop at a coherent final-synthesis checkpoint.

Update only the necessary repository documents and add a K.3 continuity record.

Then report:

1. what is definitively established;
2. what remains unvalidated;
3. any repository inconsistencies found and fixed;
4. whether any local commit/push is still required.

---
