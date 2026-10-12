# ACTIVE NEXT-CHAT PROMPT — K.10.3
## Multi-Reference Combination & Technical Obviousness Analysis

Repository: `SujitSaiY2007/embedded-runtime-resilience`
Canonical research branch: `exp`
Active checkpoint: **K.10.3**
Checkpoint authority: ChatGPT
Repository execution agent: Antigravity, only when explicitly invoked by ChatGPT

**K.10.2 has been formally approved and closed by ChatGPT on 2026-10-12. K.10.3 is authorized to begin.** Do not ask the user to repeat this authorization. Do not synchronize `main`.

## 1. Mandatory startup audit

Start from the latest canonical `origin/exp`, not an assumed local checkout.

Read, in this order:
1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `research/PART_II_CHAT_PLAN.md`
6. `research/phase2_k10_1_adversarial_distinction_review.md`
7. `research/phase2_k10_2_single_reference_anticipation_review.md`
8. `research/chat_records/chat_k10_2_record.md`
9. `research/phase2_k9_methodology_lock.md`
10. `research/phase2_k9_2_p4_advantage_novelty_design.md`
11. `research/phase1_reference_implementation_design.md`

Verify the current `exp` HEAD and ancestry. Confirm that `main` remains unchanged and do not alter it. Preserve the original checkout's local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38`; never reset, overwrite, merge, or force-push that local history. Use a clean isolated worktree based on the latest `origin/exp` for repository changes.

Independently confirm the final K.10.2 correction:
- PA-01 (Phoenix) L1 remains `YES — EXPLICITLY DISCLOSED` for the resource-constrained event-driven MCU setting: the primary paper describes embedded systems as event-driven (Section 1, pp. 125–126), Owl as an embedded runtime running bare-metal (Section 3, pp. 128–129), and an evaluated application event loop (Section 6.2, p. 134). L1 is a setting limitation; it does not establish P4's separate queue-level dependency dispatchability or retained in-pool quarantine. The earlier FreeRTOS characterization was unsupported by the inspected paper and has been removed.
- PA-02 and PA-06 remain L1 = NO.
- PA-10/L6 remains NO.
- The report and matrix must agree.
- K.10.2 conclusion remains bounded: “No single reference in the inspected candidate set was found to disclose the complete L1–L12 combination, based on the reviewed evidence.” This is not a legal novelty, obviousness, or patentability conclusion.

Check protected Git blob SHAs against these frozen values:
- `reference/src/ref_runtime.c`: `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`
- `reference/include/ref_runtime.h`: `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`
- `research/phase1_reference_implementation_design.md`: `b7fb120692756740bc969aa3412acaa89320c188`
- `research/phase2_k9_methodology_lock.md`: `bd75f2c2c21c3964ec15b338eea99b386eff7aec`
- `research/phase2_k9_2_p4_advantage_novelty_design.md`: `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d`

If any status or hash disagrees, report the discrepancy and stop before substantive work. Do not modify Gates A–E, the protected runtime files, `policy_decide()`, `runtime_apply_policy()`, or K.10 experimental evidence.

## 2. K.10.3 objective

Conduct an adversarial, evidence-grounded technical analysis of whether the proposed P4 mechanism's integrated L1–L12 combination follows predictably from two or more prior-art references. Distinguish:
- the individual technical teaching of each reference;
- an explicit and technically supported reason to combine them;
- architectural compatibility and adaptation costs;
- whether the proposed combination actually supplies P4's full operational invariants;
- remaining missing mechanisms or unsupported inferential steps;
- an imaginable combination versus a combination supported by a plausible reason and predictable technical result.

This is technical research, **not** a legal opinion. Do not assert a legal conclusion under 35 U.S.C. § 103, legal non-obviousness, patentability, or guaranteed novelty. Use careful language such as “technical combination risk,” “plausible argument,” “not established by inspected evidence,” and “requires qualified legal review.”

## 3. Required adversarial combinations

Investigate at least these three combinations; add others only when the evidence justifies them.

### C1 — Embedded peripheral recovery + failed-event queue + static event pool
- Primary: Phoenix, Smith & Rixner, “Surviving Peripheral Failures in Embedded Systems,” USENIX ATC 2015 (PA-01).
- Secondary: IBM Failed Event Queue, US 10,838,845 B2 / US 2018/0365126 A1 (PA-08).
- Additional architectural reference: official Quantum Leaps QP/C documentation on static pool backing storage, dynamic allocation/recycling of event blocks, and reference-counted garbage collection.
- Test the argument that an embedded recovery system could adopt a known failed-event queue and a known statically preallocated event pool.
- Explicitly distinguish QP's caller-provided static pool buffer from dynamic allocation/recycling of event blocks within that pool. Do not call pool allocation general-purpose heap allocation, and do not claim it is identical to P4's fixed-slot `EventSlot[20]` lifecycle.

### C2 — Embedded equipment recovery + driver/link error containment
- Primary: Trane BAS/HVAC recovery, US 10,921,871 B2 (PA-06).
- Secondary: Dell US 9,547,557 B2 (PA-03) and/or Intel US 9,411,667 B2 (PA-04).
- Test whether combining equipment-level recovery with PCIe/link error containment contributes anything material to the event-level MCU contract, and identify the architecture/domain mismatch without dismissing the strongest overlap.

### C3 — Storage adapter recovery/migration + enterprise component/event association
- Primary: NetApp US 8,510,592 B1 (PA-05).
- Secondary: IBM US 10,331,522 B2 (PA-07).
- Analyze failure-to-component mapping, retries, adapter recovery and traffic migration against evidence-bounded event association, retained in-pool quarantine, dependency eligibility, and bounded recovery.

For every reference, verify the identity, publication/issue status and date where relevant, and technical teaching from primary-source text. Use the papers, patent specifications/claims, and official QP/C documentation. Record exact claim/section/page locators and links. Do not infer missing claim text from search snippets. Clearly label any inaccessible or unverified portions.

## 4. Required analytical method

For each combination:
1. Define the adversarial combination and starting reference.
2. Identify the exact teaching contributed by each secondary reference.
3. State the strongest plausible motivation/rationale to combine them.
4. Evaluate technical compatibility/friction in:
   - execution model: call-stack checkpoint/rollback versus asynchronous event dispatch;
   - event identity and lifecycle: generation-qualified slot identity versus queue movement/replay;
   - quarantine: retained non-executable event in the original fixed pool versus deletion/reinsertion into a secondary queue;
   - memory: fixed-capacity zero-heap runtime versus static backing storage with dynamic pool-block allocation/recycling;
   - fault association: evidence precision lattice and fail-closed `assoc <= evidence` invariant versus component/flow mapping or blind retry;
   - dependency-aware scheduling: explicit dependency classes and dispatchability predicate versus process isolation, FIFO, or unrelated service continuity;
   - recovery ladder, verification-before-release, episode closure/escalation, deterministic trace and sole runtime transition authority.
5. For each L1–L12 limitation, label the combination as explicitly supplied, partially overlapping, absent, or unresolved. Do not count a limitation as supplied merely because different references each mention adjacent concepts.
6. Determine whether the combined system would require routine adaptation, substantial redesign, or unsupported assumptions; explain the evidence for the classification.
7. Present the strongest argument against P4 and the strongest evidence-grounded response, then identify what remains vulnerable.
8. Keep technical assessment separate from legal standards and professional patent review.

Do not treat “three references can be listed together” as proof that their combination is motivated or predictable. Conversely, do not assume architecture differences automatically defeat a combination. Evaluate both sides.

## 5. Frozen boundaries

Do NOT:
- modify Gates A–E or the runtime/header;
- change `policy_decide()` or `runtime_apply_policy()`;
- redesign P4 to evade prior art;
- rerun, edit, or regenerate the K.10 experiment matrix or traces;
- claim that P4 is universally superior;
- issue a legal conclusion on obviousness, novelty, or patentability;
- start K.10.4, K.11, K.12, hardware validation, or `main` synchronization.

## 6. Required deliverables and repository updates

Create:
- `research/phase2_k10_3_multi_reference_combination_review.md`
- `research/chat_records/chat_k10_3_record.md`

Update, where necessary and only to reflect verified facts:
- `CURRENT_HANDOFF.md` opening current status;
- `PROJECT_STATE.md` authoritative current status;
- `DECISION_LOG.md` with K.10.3 decisions;
- `research/PART_II_CHAT_PLAN.md`;
- `NEXT_CHAT_PROMPT.md` with the complete K.10.4 continuation prompt only after K.10.3 is formally approved.

The report must include an executive summary, evidence/methodology boundary, source register, combination-by-combination analysis, limitation coverage matrix, strongest adversarial theory, technical friction and gaps, uncertainty/accessibility register, bounded conclusion, and exact K.10.4 handoff. The chat record must include exact start/end SHAs, files changed, sources inspected, verification performed, unresolved issues, and approval-gated status.

## 7. K.10.3 exit criteria

K.10.3 is complete only if:
- all required combinations are analyzed from primary-source evidence;
- the strongest technically plausible combination attack is fairly represented;
- all L1–L12 mappings distinguish exact disclosure from partial overlap and inference;
- technical friction is neither exaggerated nor ignored;
- all conclusions are consistent across the report, matrix, record and continuity files;
- protected hashes and branch ancestry are verified;
- K.10.4 is clearly bounded and its prompt is prepared;
- ChatGPT has independently reviewed and explicitly approved the checkpoint.

At completion, **stop and await ChatGPT approval**. Do not begin K.10.4 in this chat. Do not synchronize `main`.