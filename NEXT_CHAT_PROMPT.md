# ACTIVE NEXT-CHAT PROMPT — K.10.1
## Adversarial Prior-Art & Technical-Distinction Review

Repository: `SujitSaiY2007/embedded-runtime-resilience`

Branch: `exp`

You are ChatGPT conducting **K.10.1 only**.

K.10 is COMPLETE. Do not restart K.10 experiments. Do not begin K.10.2, K.10.3, K.10.4, K.11, K.12, or hardware validation.

## 1. Continuity check

Before substantive work, read:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `research/PART_II_CHAT_PLAN.md`
6. `research/phase2_k10_p4_advantage_novelty_results.md`
7. `research/chat_records/chat_k10_record.md`
8. the prior-art artifacts referenced by K.10.

Verify:
- current branch is `exp`;
- current HEAD;
- working-tree state;
- K.10 is actually recorded as COMPLETE;
- K.10 protected-runtime integrity remains intact.

If the live state conflicts with the continuity records, stop and reconcile before research work.

## 2. Objective

K.10.1 must adversarially test the **technical distinction** remaining after K.10.

Do not try to prove P4 novel.

Try to break the distinction.

The research question is:

> After decomposing P4 into concrete technical limitations, what is actually disclosed by the strongest prior art, what remains missing, and which distinctions are supported by evidence rather than by interpretation?

## 3. Freeze K.10

Do not modify:
- P4 semantics;
- Gates A-E;
- `reference/src/ref_runtime.c`;
- `reference/include/ref_runtime.h`;
- K.10 experimental results.

Do not reinterpret K.10's bounded experimental advantage as universal superiority.

## 4. Build the P4 limitation matrix

Decompose the complete proposed mechanism into concrete, testable limitations, including as applicable:

- evidence-bounded fault-to-event association;
- retained event-level quarantine;
- dependency/order-aware preservation of unrelated queued work;
- bounded history-conditioned recovery ladder;
- static/zero-heap bounded implementation;
- deterministic verification/release/escalation;
- peripheral-fault initiation;
- the interaction of these mechanisms in a constrained event-driven MCU runtime.

For every limitation record:
- precise definition;
- where it appears in the project;
- whether it is essential to the proposed combination;
- what evidence supports it.

Do not broaden the claim after seeing prior art.

## 5. Adversarial reference analysis

Use the strongest references already identified by K.10, then search for additional references specifically designed to challenge the remaining distinction.

For each reference record:

Reference
→ date/type
→ technical problem
→ disclosed mechanism
→ exact P4 overlap
→ partial overlap
→ missing P4 limitation
→ explicit disclosure versus inference
→ architectural/context mismatch
→ residual distinction
→ confidence/evidence note

Search across:
- academic papers;
- patents/patent applications;
- technical reports;
- standards/specifications;
- open-source embedded implementations;
- relevant commercial/industrial documentation.

Do not search only for supportive references.

## 6. Analyze mechanism levels separately

Perform four separate analyses:

A. Individual mechanisms.

B. Pairwise combinations.

C. Higher-order combinations.

D. Complete P4 combination.

Do not collapse these into one novelty statement.

## 7. Technical distinction test

For every apparent distinction ask:

1. Is it actually disclosed?
2. Is it merely implied?
3. Is it only a difference in terminology?
4. Is it only a difference in application domain?
5. Does the constrained MCU/zero-heap context materially affect implementation?
6. Does the association rule impose a concrete technical constraint?
7. Does the interaction between mechanisms produce behavior absent from the reference?
8. Is the distinction experimentally supported by K.10?

If a distinction is weak, say so.

## 8. No legal conclusion

Do not state that the project is patentable.

Do not state that a patent claim would be valid.

Do not provide a legal opinion.

You may identify technical evidence relevant to later professional legal review.

## 9. Antigravity rule

If repository execution/search automation is useful, Antigravity may be used only as the execution agent for this K.10.1 scope.

Antigravity MUST NOT:
- define the next chat;
- start K.10.2;
- redesign P4;
- modify the frozen runtime;
- rewrite the experimental conclusion.

ChatGPT remains the sequence owner and audit layer.

## 10. Repository outputs

Create/update only the K.10.1 research and continuity artifacts needed for this checkpoint.

At minimum produce:
- a complete P4 limitation/feature matrix;
- adversarial reference mapping;
- overlap/distinction analysis;
- unresolved evidence list;
- `research/chat_records/chat_k10_1_record.md`;
- updated `PROJECT_STATE.md`;
- updated `CURRENT_HANDOFF.md`;
- updated `DECISION_LOG.md` if a consequential decision is made;
- updated `NEXT_CHAT_PROMPT.md` with the complete K.10.2 prompt.

Do not delete historical K.10 records.

## 11. Exit criteria

K.10.1 is COMPLETE only when:
- the P4 limitation matrix is auditable;
- strongest prior-art overlaps are mapped;
- missing/uncertain disclosures are explicitly identified;
- no unsupported distinction is being treated as established;
- K.10 remains frozen;
- continuity is updated;
- K.10.2 has a complete continuation prompt.

If any of these are incomplete, report:

`K.10.1 INCOMPLETE — <specific reason>`

Otherwise report:

`K.10.1 COMPLETE`

## 12. Git boundary

Commit K.10.1 work to `exp`.

Before commit:
- inspect changed files;
- verify protected runtime files are unchanged;
- verify no secrets;
- run relevant repository checks;
- confirm working tree state.

Do not synchronize to `main` until the checkpoint is reviewed and explicitly approved.

## 13. Final response

Return:
- continuity check;
- exact branch/SHA;
- sources reviewed;
- limitation matrix status;
- strongest overlaps;
- strongest remaining distinctions;
- unresolved issues;
- tests/checks;
- changed files;
- commit SHA;
- K.10.1 status;
- exact next checkpoint: K.10.2.

STOP after K.10.1.
