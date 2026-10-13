# Part II — Canonical Multi-Chat Execution Plan

**Status:** ACTIVE — canonical post-K.10 roadmap  
**Canonical research branch:** `exp`  
**Integrated mirror:** `main`  
**Chat sequence owner:** ChatGPT  
**Repository execution agent:** Antigravity, only when explicitly invoked inside a ChatGPT-defined checkpoint

> **Authority rule:** This file is the only active Part-II chat sequence. Earlier roadmap wording that conflicts with this document is historical/superseded. Historical chat records are retained for provenance and are not active instructions.

**Current checkpoint status (2026-10-13): K.10, K.10.1, K.10.2, and K.10.3 APPROVED AND CLOSED. K.10.4 — Final Technical Distinction & Research Conclusion — IMPLEMENTATION COMPLETE, PENDING CHATGPT APPROVAL.** The exact execution brief for the upcoming checkpoint is in `NEXT_CHAT_PROMPT.md` (K.11 software synthesis). K.11, K.12, hardware validation, and main synchronization remain gated until their own checkpoints are completed and explicitly approved.

## Global execution rules

1. Every new ChatGPT chat starts from the latest verified `exp` state.
2. Read `PROJECT_MANUAL.md`, `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, this file, and the latest checkpoint record before substantive work.
3. Every ChatGPT chat has exactly one numbered checkpoint scope.
4. ChatGPT owns the checkpoint sequence and decides when a checkpoint is closed.
5. Antigravity may execute repository work, experiments, searches, or documentation updates only within the current ChatGPT checkpoint.
6. Antigravity does not create or redefine the chat-wise sequence.
7. A checkpoint may remain open if evidence is incomplete; the next chat must not silently assume completion.
8. Each completed chat must update continuity artifacts and generate the exact continuation prompt for the next ChatGPT chat.
9. `exp` is the active research/integration branch.
10. `main` is the stable integrated mirror. Validated `exp` checkpoints are synchronized to `main` through the normal PR/merge path.
11. Historical feature/design/experiment branches are preserved as provenance. They are not active roadmap authorities.
12. Gates A–E, `policy_decide()`, `runtime_apply_policy()`, and the protected reference runtime remain frozen unless a future checkpoint explicitly authorizes a change.
13. No host/software-model result may be presented as physical MCU evidence.
14. No research stage may claim universal P4 superiority, novelty, inventive step, or patentability without evidence supporting that exact claim.
15. No checkpoint may execute work assigned to a later checkpoint merely because it becomes convenient.

---

# Part I — K.1–K.3

**COMPLETE.** Historical foundation containing the host/reference mechanism, Gates A–E, deterministic host corpus, and initial evidence synthesis.

# Part II — K.4–K.10

**COMPLETE.** Historical records are retained.

- K.4 — Novelty re-research + conceptual architecture lock
- K.5 — Virtual embedded-system technical design
- K.6 — Virtual embedded-system implementation
- K.7 — Professor-facing UI implementation
- K.8 — Matched baseline validation
- K.9 — Full software re-verification + methodology lock
- K.9.2 — P4 advantage/novelty investigation design lock
- K.10 — P4 advantage & novelty investigation

K.10's evidence-bounded result is:
- experimental classification: **Demonstrated bounded advantage**;
- prior-art classification: **Potentially distinguishable combination — further legal/technical review required**;
- no universal superiority claim;
- no legal patentability conclusion.

---

# Post-K.10 — Final Research/Development Sequence

## K.10.1 — Adversarial Prior-Art & Feature-Distinction Review

### Purpose
Attack the K.10 technical-distinction conclusion from the strongest opposing direction.

### Required work
- Freeze the K.10 experimental conclusion; do not redesign P4.
- Build a complete P4 feature/limitation decomposition.
- Map every limitation against the strongest identified references.
- Separate exact disclosure, partial overlap, absence, and unresolved evidence.
- Identify missing references through adversarial searches.
- Distinguish individual mechanisms, pairwise combinations, higher-order combinations, and the complete combination.
- Separate technical distinction from legal novelty, inventive step/non-obviousness, and patentability.
- Identify which distinctions are actually supported by the technical record.

### Out of scope
- P4 redesign.
- New recovery policy.
- New experiment matrix.
- Hardware validation.
- Legal opinion.
- Patent filing.
- K.10.2/K.10.3/K.10.4 execution.

### Required deliverables
- feature/limitation matrix;
- adversarial reference set;
- overlap/distinction table;
- missing-evidence list;
- K.10.1 record;
- updated continuity;
- exact K.10.2 continuation prompt.

### Exit
K.10.1 is complete only when the technical distinction matrix is auditable and the strongest known attack paths are documented. Otherwise mark INCOMPLETE.

---

## K.10.2 — Deep Single-Reference Anticipation Review

### Purpose
Determine whether any single reference actually discloses the complete relevant P4 combination.

### Required work
For each strongest reference:
- identify the exact disclosed elements;
- map them to P4 limitations;
- identify explicit versus inferred elements;
- identify architectural/context mismatches;
- determine whether the complete arrangement is actually disclosed;
- record unresolved evidence rather than filling gaps by inference.

### Required distinction
"Every ingredient exists somewhere" is not equivalent to "one reference discloses the complete combination."

### Out of scope
- Multi-reference obviousness conclusion.
- P4 redesign.
- Hardware.
- Patent/legal opinion.
- K.10.3/K.10.4 work.

### Exit
**APPROVED AND CLOSED (2026-10-12).** The final matrix retains PA-01/L1 = YES because Phoenix describes the event-driven embedded setting (Section 1, pp. 125–126), the bare-metal Owl runtime (Section 3, pp. 128–129), and an evaluated application event loop (Section 6.2, p. 134). This setting match does not establish P4's separate queue-level dependency/quarantine contract. No single reference in the inspected candidate set was found to disclose the complete L1–L12 combination based on reviewed evidence. This is not a legal novelty or patentability conclusion.

---

## K.10.3 — Multi-Reference Combination & Technical Obviousness Analysis

### Purpose
Attack the remaining distinction by asking whether the complete P4 combination follows naturally from multiple references.

### Required work
For each serious combination:
- identify the starting reference;
- identify the secondary reference(s);
- state the technical teaching contributed by each;
- identify the reason/motivation for combining them;
- check architectural compatibility;
- check whether the combination actually produces P4's claimed interaction;
- identify technical conflicts or missing steps;
- distinguish "possible to combine" from "supported reason to combine";
- identify combinations that reproduce only part of P4.

### Important
This remains a technical research analysis, not a legal opinion.

### Out of scope
- P4 redesign to evade references.
- New experiments unless a narrowly necessary verification is explicitly approved by ChatGPT.
- Hardware validation.
- K.10.4 conclusion.

### Exit
**APPROVED AND CLOSED (2026-10-12).** The report covers C1 (Phoenix + IBM PA-08 + QP/C), C2 (Trane + Dell/Intel), and C3 (NetApp + IBM PA-07), with source-grounded technical teachings, combination rationales, friction/gaps and an L1–L12 coverage matrix. C1 is the strongest technical-combination risk; C3 is next; C2 is a more distant generic-recovery attack. No legal obviousness or patentability conclusion is made.

---

## K.10.4 — Final Technical Distinction & Research Conclusion

### Purpose
Integrate K.10.1–K.10.3 with the actual K.10 experimental evidence.

### Required work
Produce one evidence-bounded final assessment covering:
1. experimental contribution;
2. technical distinction;
3. known prior art;
4. unresolved prior-art risks;
5. trade-offs;
6. limitations;
7. what can and cannot be claimed academically;
8. what requires professional patent/legal review.

### Possible outcomes
Do not force a positive result. The final technical conclusion may state:
- distinguishable under the investigated record;
- not distinguishable from identified prior art;
- partially distinguishable with material unresolved risk;
- inconclusive.

### Exit
**IMPLEMENTATION COMPLETE (Pending ChatGPT Approval, 2026-10-13).** The final report (`research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md`) and chat record (`research/chat_records/chat_k10_4_record.md`) have been authored and cross-audited. The research conclusion confirms bounded P4 advantages in CF04/CF07 and CF05, preserves shared quarantine preservation and the CF16 baseline win, confirms single-reference anticipation is refuted across PA-01–PA-10, and documents unresolved high technical-combination risk under C1 (Phoenix + IBM PA-08 + QP/C). K.11 is the authorized next checkpoint upon ChatGPT approval, focusing strictly on software synthesis and hardware validation protocol specification without initiating hardware execution.

---

# K.11 — Final Software Synthesis + Hardware-Validation Handoff

### Purpose
Synthesize the completed K.10.x research investigation and K.10 experiment evidence into the final software-phase research package.

### Required work
- final architecture summary;
- final mechanism description;
- final experimental evidence summary;
- final prior-art/distinction summary;
- explicit evidence boundaries;
- final limitations;
- publication-oriented results structure;
- target-MCU validation requirements;
- hardware-validation success criteria;
- professor-facing conclusion.

### Out of scope
- claiming completed hardware validation;
- silently redesigning P4;
- new novelty claims beyond K.10.x evidence;
- starting the physical MCU campaign.

### Exit
The software research phase is closed and the project has a clean, evidence-bounded handoff into the final implementation/demo phase.

---

# K.12 — Final Software Productization & Clean UI Demonstration

### Purpose
Prepare and demonstrate the complete project cleanly after the research conclusion is frozen.

### Required work
- reconcile UI with the final frozen research terminology;
- remove stale/duplicated UI messaging;
- ensure UI uses the authoritative C runtime and existing virtual system;
- ensure every displayed metric is traceable to committed evidence;
- present P0–P4 comparison without misleading ranking;
- clearly label software-model evidence versus future hardware evidence;
- clean scenario selection, trace visualization, fault injection, recovery decision, verification/release/escalation and evidence explanation;
- perform final reproducibility/build/test checks;
- create the final professor-facing demonstration path.

### Out of scope
- changing P4 to improve appearance or measured performance;
- introducing a second policy;
- inventing measurements;
- new research claims;
- hardware validation unless separately authorized.

### Exit
A clean, reproducible, complete software demonstration exists and is consistent with the final research conclusion.

---

# Final integration

After K.12:
1. verify `exp`;
2. verify protected runtime integrity;
3. verify tests and documentation;
4. perform final audit;
5. synchronize the validated final state to `main`;
6. record the exact source `exp` commit and merge;
7. do not continue speculative roadmap expansion unless a new research objective is explicitly approved.

---

# Chat-to-chat continuity contract

At the end of every checkpoint, the current chat MUST leave:

- checkpoint status;
- exact branch;
- exact starting/ending SHA;
- files changed;
- tests/checks;
- evidence produced;
- unresolved items;
- explicit prohibited next-stage work;
- exact next checkpoint;
- complete copy-paste continuation prompt in `NEXT_CHAT_PROMPT.md`.

The next ChatGPT chat begins by reading the repository state and that exact prompt.

**Antigravity execution never becomes the chat sequence. It is an execution tool inside the ChatGPT-defined checkpoint.**
