# ACTIVE NEXT-CHAT PROMPT — K.10.3
## Multi-Reference Combination & Technical Obviousness Analysis

Repository: `SujitSaiY2007/embedded-runtime-resilience`  
Canonical branch: `exp`  
Current checkpoint owner: ChatGPT  
Execution agent: Antigravity only when explicitly invoked by ChatGPT

**This prompt becomes active only after ChatGPT has reviewed and explicitly approved the K.10.2 checkpoint package.** If that approval is absent, do not start K.10.3. First report the approval gate and wait.

## 1. Current canonical state

- K.10 is COMPLETE. Do not rerun the 400-run experiment matrix.
- K.10.1 is COMPLETE (adversarial limitation decomposition established).
- K.10.2 is COMPLETE (single-reference anticipation refuted across all primary inspected references; PA-01 Phoenix, PA-02 Karma, PA-03 Dell, PA-04 Intel, PA-05 NetApp, PA-06 Trane, PA-07/PA-08 IBM, PA-09 Oracle, PA-10 Swift/Herder).
- The candidate technical distinction remains UNRESOLVED against multi-reference combination attacks.
- Read first: `PROJECT_MANUAL.md`, `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, `research/PART_II_CHAT_PLAN.md`, `research/phase2_k10_1_adversarial_distinction_review.md`, `research/phase2_k10_2_single_reference_anticipation_review.md`, and `research/chat_records/chat_k10_2_record.md`.
- Confirm current `exp` HEAD and compare protected runtime files with the K.10 baseline before research.
- `main` must not be synchronized until ChatGPT reviews and explicitly approves the checkpoint.

## 2. K.10.3 objective — multi-reference combination & technical obviousness attack

Evaluate whether the complete P4 combination follows predictably or naturally from combining two or more primary references. This is a technical research analysis, not a legal patent opinion.

Prioritize analyzing the primary multi-reference combinations identified in K.10.1 and K.10.2:
1. **Combination C1 (Embedded Recovery + Enterprise Failed-Event Queue):**
   - Primary: Phoenix (PA-01, Smith & Rixner 2015).
   - Secondary: IBM Failed Event Queue (PA-08, US 10,838,845 B2 / US 2018/0365126 A1).
   - Tertiary: Quantum Leaps QP (PA-10, Miro Samek / static zero-heap event pools).
   - Question: Would a PHOSITA in embedded systems combine Phoenix's peripheral reset with IBM's failed-event quarantine on QP static event queues? What is the technical friction (rollback elimination, in-pool non-executable retention, heap fragmentation avoidance)?
2. **Combination C2 (Embedded Equipment History + Driver Link Error Containment):**
   - Primary: Trane BAS/HVAC failure recovery (PA-06, US 10,921,871 B2).
   - Secondary: Dell / Intel peripheral error containment (PA-03 / PA-04).
3. **Combination C3 (Storage Peripheral Migration + Enterprise Component Association):**
   - Primary: NetApp PCIe error resilience (PA-05, US 8,510,592 B1).
   - Secondary: IBM event failure management (PA-07, US 10,331,522 B2).

## 3. Required method

For each combination:
- State the base reference and each modifying/secondary reference.
- Identify the exact technical teaching contributed by each reference.
- Formulate the adversarial examiner's rationale for combining them (e.g. routine substitution, known technique to improve similar system).
- Evaluate technical compatibility and adaptation friction:
  - Memory allocation model (dynamic heap vs static bounded array).
  - Execution boundary (call-stack rollback vs cooperative event dispatch).
  - Association precision model (fail-closed Gate B contract vs blind retry).
- Determine whether the combination achieves the full operational invariant set or leaves genuine technical gaps.
- Distinguish "theoretically imaginable combination" from "technically supported rationale with predictable result".

## 4. Frozen boundaries

Do NOT:
- modify Gates A–E;
- modify `reference/src/ref_runtime.c` or `reference/include/ref_runtime.h`;
- modify `policy_decide()` or `runtime_apply_policy()`;
- redesign P4 to artificially evade prior art;
- rerun or edit K.10 experiments/traces;
- start K.10.4 final synthesis, K.11, K.12, or hardware validation;
- claim legal non-obviousness or patentability;
- synchronize `main`.

## 5. Required deliverables

Create:
- `research/phase2_k10_3_multi_reference_combination_review.md`
- `research/chat_records/chat_k10_3_record.md`

Update only as warranted:
- `PROJECT_STATE.md` and `CURRENT_HANDOFF.md` opening current status;
- `DECISION_LOG.md` with relevant checkpoint decisions;
- `NEXT_CHAT_PROMPT.md` with the complete K.10.4 continuation prompt upon closure.

## 6. Exit criteria

K.10.3 is complete only when the multi-reference combinations are rigorously analyzed, the technical friction and non-obviousness arguments are objectively evaluated, and the remaining distinction is clearly bounded for K.10.4.
