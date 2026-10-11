# ACTIVE NEXT-CHAT PROMPT — K.10.2
## Deep Single-Reference Anticipation Review

Repository: `SujitSaiY2007/embedded-runtime-resilience`  
Canonical branch: `exp`  
Current checkpoint owner: ChatGPT  
Execution agent: Antigravity only when explicitly invoked by ChatGPT

**This prompt becomes active only after ChatGPT has reviewed and explicitly approved the K.10.1 checkpoint package.** If that approval is absent, do not start K.10.2. First report the approval gate and wait.

## 1. Current canonical state

- K.10 is COMPLETE. Do not rerun the 400-run experiment matrix.
- K.10.1 analysis package is committed and its technical-distinction hypothesis remains UNRESOLVED.
- Read first: `PROJECT_MANUAL.md`, `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, `research/PART_II_CHAT_PLAN.md`, `research/phase2_k10_p4_advantage_novelty_results.md`, `research/phase2_k10_1_adversarial_distinction_review.md`, `research/chat_records/chat_k10_record.md`, and `research/chat_records/chat_k10_1_record.md`.
- Confirm the current `exp` HEAD and compare the protected runtime files with the K.10 baseline before research. Do not assume hashes or clean working-tree state from old messages.
- `main` is not to be synchronized until ChatGPT reviews and explicitly approves the relevant checkpoint.

## 2. K.10.2 objective — single-reference anticipation attack only

Determine whether any one reference, considered individually and in its relevant disclosure/claims, anticipates or materially discloses most or all of the remaining candidate technical combination. This is a technical research exercise, not a legal opinion.

Prioritize primary-source inspection of:
1. Phoenix — Smith & Rixner, “Surviving Peripheral Failures in Embedded Systems,” USENIX ATC 2015.
2. Karma — Branco et al., “Intermittent Asynchronous Peripheral Operations,” SenSys 2019.
3. US9547557B2 — peripheral bus error containment and recovery.
4. US9411667B2 — recovery after I/O error-containment events.
5. US8510592B1 — PCI error resilience.
6. US10921871B2 — recovery-history-driven action selection.
7. US10331522 and US10929373 — association/retry/quarantine leads.
8. US20180365126A1 — failed-event queue/corrective action/replay lead.
9. US12688084 — retained events/retry/verification/release lead.
10. Swift et al., “Recovering Device Drivers” (OSDI 2004), and Herder et al., “Failure Resilience for Device Drivers.”

These identifiers are research leads from prior notes, not pre-verified claim charts. Verify exact title, inventors/authors, publication/priority dates, family members, jurisdiction and primary source before relying on each.

## 3. Required method

For each source:
- Retrieve the full paper, patent specification and claims, or canonical technical document where accessible.
- Record exact bibliographic metadata and primary URL.
- For patents, record priority/filing/publication dates, family information and claim numbers/paragraphs supporting each relevant limitation. Do not treat a search snippet or abstract as sufficient.
- Map each L.1–L.12 limitation in `research/phase2_k10_1_adversarial_distinction_review.md` as:
  - **Explicitly disclosed** (quote or precisely summarize the source passage/claim);
  - **Necessarily implied** (explain why it necessarily follows, not merely why it would be sensible);
  - **Not found in the inspected material** (state which sections/claims were inspected);
  - **Unverified / inaccessible** (state the missing evidence).
- Keep “not found” distinct from “absent.” Do not conclude novelty from incomplete search.
- Test whether one reference discloses the complete combination or a materially equivalent operational invariant set, not merely whether it discusses peripheral recovery generally.
- Separate single-reference anticipation from obviousness/recombination, which belongs to K.10.3.
- Map the source's fault model, target architecture, event/request identity, association precision, queue retention/quarantine, dependency/order eligibility, recovery history, finite ladder, verification/release, bounded memory and traceability.
- Identify the strongest single-reference threat and explain which exact limitation(s), if any, remain unaccounted for by that source.

## 4. Frozen boundaries

Do NOT:
- modify Gates A–E;
- modify `reference/src/ref_runtime.c` or `reference/include/ref_runtime.h`;
- modify `policy_decide()` or `runtime_apply_policy()`;
- change P4 semantics, add variants or redesign the runtime;
- rerun or edit K.10 experiments/results/raw traces;
- conduct K.10.3 multi-reference combination analysis;
- start K.10.4, K.11, K.12, or hardware validation;
- claim novelty, non-obviousness, legal anticipation, or patentability;
- synchronize `main`.

## 5. Required artifacts and continuity

Create:
- `research/phase2_k10_2_single_reference_anticipation_review.md` — source-by-source limitation chart, primary-source citations, chronology, disclosure classification, threat ranking and unresolved gaps.
- `research/chat_records/chat_k10_2_record.md` — objective, exact starting/ending commit, source access limitations, files changed, checks and conclusion.

Update only as warranted:
- `PROJECT_STATE.md` and `CURRENT_HANDOFF.md` opening current status;
- `DECISION_LOG.md` only if a consequential research/governance decision is made;
- `NEXT_CHAT_PROMPT.md` with the complete K.10.3 prompt only if K.10.2 is actually closed and ChatGPT approves the checkpoint.

Preserve all historical records. Do not represent an inaccessible reference as reviewed. Include direct source links and claim/page/section locators.

## 6. Validation and reporting

- Confirm the exact `exp` HEAD before and after.
- Confirm both protected runtime files retain the exact K.10 baseline blob/content hashes.
- Confirm Gate-defining artifacts remain unchanged.
- Do not claim local tests or clean working tree unless actually run/observed in a repository checkout.
- Commit K.10.2 artifacts to `exp` only.
- Do not update `main`.

## 7. Exit criteria

K.10.2 can be marked complete only if the strongest accessible single-reference candidates have been examined at primary-source level, the limitation mapping is auditable, inaccessible material is clearly bounded, and the single-reference conclusion is evidence-supported. If not, mark **K.10.2 INCOMPLETE — [specific missing evidence]**.

End with:
- status;
- branch and exact starting/ending SHA;
- files changed;
- exact protected-file hash comparisons;
- tests/checks actually performed;
- strongest single-reference threat;
- remaining gaps;
- explicit stop at K.10.2.
