# Chat 03 — Research-Gap Analysis

**Audit date:** 2026-10-20  
**Repository:** [SujitSaiY2007/embedded-runtime-resilience](https://github.com/SujitSaiY2007/embedded-runtime-resilience)  
**Starting live `main` SHA:** `e71e8243a66200836d6c9069600d64e1838df7a7`  
**Scope:** Evidence-based gap classification and next-step recommendations. No manuscript/bibliography edits, protected source edits, test changes, experiment reruns, or hardware claims.

## 1. Executive assessment

The repository already defines and implements a bounded host/reference model for context-aware peripheral fault handling. Its strongest engineering distinction is the *combination* of explicit fault-association precision, generation-qualified event identity, retained event-level quarantine, dependency-aware scheduling, bounded recovery state/history, and deterministic traceability. However, the prior-art reports themselves identify a credible multi-reference challenge (especially Phoenix + failed-event queue + QP/C), and the source inventory is not comprehensive enough to support an absence-of-prior-art conclusion.

The evidence currently supports an **engineering hypothesis and host-model evaluation**, not a settled literature novelty claim or physical embedded-system result. The immediate work is therefore to improve claim/source traceability and full-text coverage without altering frozen artifacts; hardware validation is a separate gate requiring actual board, firmware and raw trace evidence.

## 2. Evidence chain

| Chain element | Current evidence | What can be said | What cannot be said |
|---|---|---|---|
| Existing literature/practice | Chat 02 has 9 metadata-verified, 17 partially verified and 17 unresolved rows out of 43; K.10.1–K.10.3 discuss close sources and combinations | Several constituent techniques are established and a multi-reference challenge is credible | The inventory does not establish exhaustive literature coverage or universal absence of prior art |
| What those sources establish | K.10 analyses and reference register describe Phoenix/peripheral recovery, Karma rollback/replay, driver containment, failed-event handling, static pools and monitoring frameworks | The project should compare exact teachings and technical differences, source by source | Metadata alone does not establish a paper's exact algorithm, claims, or all limitations |
| What remains unresolved | Full text/claims and official metadata gaps, broad A-series strands, no exact mapping for many references | A source-to-design relationship may remain unresolved or “no demonstrated influence” | It is not defensible to force every inventory row into a design decision |
| What the project addresses | Gate A–E contracts, C11 runtime, tests, matched P0–P4 host corpus, saved K.10 reports | A bounded reference model tests explicit semantics and selected fault/workload scenarios | It does not establish hardware performance, energy, timing, MPU behavior, or general deployment reliability |
| What remains untested | Broader prior art, full claim/passage mapping, independent replay of raw data, board selection and physical tests | A defined set of research and evaluation tasks remains | Novelty, non-obviousness, patentability, or universal superiority are not established |

## 3. Gap register

### G-LIT-01 — Source coverage and full-text evidence

- **Category:** Literature gap / evidence gap
- **Observed:** Chat 02 marks 9/43 source identities as verified, 17/43 partial and 17/43 unresolved. Some additional entries are topics, families or broad research strands rather than exact publications.
- **Current-project response:** The project has a 43-ID register and bounded K.10.1–K.10.3 prior-art analyses.
- **Remaining uncertainty:** The reviewed candidate set is not demonstrably comprehensive. Several exact source identities, publisher records, patent claims and full-text passages remain open.
- **Defensible statement:** “The inspected candidate set identifies relevant adjacent teachings and a credible combination challenge; broader coverage and several source-level checks remain incomplete.”
- **Do next:** Resolve exact source identity; inspect full text or patent claims; record section/page/claim and the inspected scope. Search new candidates by technical element, not only project vocabulary.
- **Do not claim:** “No prior art exists” or “the literature proves novelty.”

### G-LIT-02 — Multi-reference combination and technical distinction

- **Category:** Literature gap / open question
- **Observed:** K.10.3 identifies Phoenix + IBM failed-event queue + QP/C as a credible combination attack and lists differences between rollback/replay, separate failed-event queues, static pool storage and the project's same-slot quarantine/dependency predicate.
- **Current-project response:** K.10.2/3 decompose the candidate mechanism and compare inspected sources.
- **Remaining uncertainty:** The technical differences may be real but are not a legal conclusion. The review scope and completeness of primary claims/disclosures vary; additional sources may change the matrix.
- **Do next:** Build a feature-by-feature matrix with exact passage/claim citations and explicit combination rationale, friction, and remaining elements. Ask an appropriately qualified reviewer to assess legal questions if needed.
- **Do not claim:** That a combination is legally non-obvious or patentable based on a technical research report.

### G-ENG-01 — Explicit evidence-bounded fault-to-event association

- **Category:** Engineering gap / design hypothesis
- **Observed:** Gate B specifies association levels and an evidence-precision constraint; the runtime/header include association vocabulary; K.10 reports P4-specific handling for CF04/CF07.
- **Current-project response:** A finite association model is implemented in the host reference runtime and exercised in the saved scenario corpus.
- **Remaining uncertainty:** The model's observable inputs, assumptions and fail-closed transitions must be linked to exact code and test evidence. Real hardware drivers may expose less context or different error semantics.
- **Do next:** Trace each association level from input evidence through policy branch to terminal outcome, including ambiguous, stale and missing-context cases. On hardware, capture actual driver status/error fields and timestamp/counter evidence.
- **Do not claim:** The model identifies the physical root cause of a bus or peripheral failure where the driver only reports timeout/no-progress.

### G-ENG-02 — Same-slot quarantine with dependency-aware preservation

- **Category:** Engineering gap / technical distinction
- **Observed:** Gate A defines explicit INDEPENDENT, ORDERED and COUPLED dependencies; implementation design says the queue stores slot IDs and quarantine retains the same EventSlot; W01–W03 exercise preservation/blocking/coupled behavior.
- **Current-project response:** A fixed-capacity host model tests the semantics without copying the event record to a separate quarantine pool.
- **Remaining uncertainty:** Tests cover selected scenarios, not every state/identity/queue-pressure combination. Real peripheral operations may have side effects or dependencies not represented by current metadata.
- **Do next:** Map each invariant to exact tests and boundary conditions; document failure behavior when queue/quarantine/episode capacity is exhausted; add future tests only under a separately authorized test change.
- **Do not claim:** That the current test set is exhaustive proof of all workload correctness.

### G-EVAL-01 — Independent reproducibility and raw artifact linkage

- **Category:** Evaluation gap / evidence gap
- **Observed:** `reference/experiments/k10_experiment.c` defines the 16-family × 5-variant × 5-repeat harness; evaluator asserts 400 rows; K.10 report describes saved findings. This Chat 03 did not rerun the campaign or inspect raw output CSVs.
- **Current-project response:** Frozen result reports and experiment sources are retained.
- **Remaining uncertainty:** This audit has not independently confirmed raw output availability, file hashes, row-level values, or recomputed summaries from the current `main` tree.
- **Do next:** Without rerunning the 400 executions, inspect existing saved raw CSVs and traces if present, verify row counts/hashes and recompute derived summary metrics from the saved data only. Record exact commands and results in a separate authorized audit.
- **Do not do now:** Do not rerun or regenerate the campaign; this chat's instruction explicitly forbids it.

### G-EVAL-02 — Baseline fidelity and ablation attribution

- **Category:** Evaluation gap
- **Observed:** P0–P4 are internal policy variants (fixed retry; fixed retry+recovery; context only; context+history; integrated). No source-to-code evidence establishes them as faithful reproductions of named published systems.
- **Current-project response:** Gate E describes a matched comparison designed to isolate context/history and integrated-policy effects.
- **Remaining uncertainty:** Whether each observed outcome is attributable to the targeted component, and whether all relevant confounders are controlled, depends on the exact scenario matrix, source and result artifacts.
- **Do next:** State every baseline's exact implemented behavior and what it intentionally omits; distinguish ablation from external benchmark; preserve queue capacities/workloads and other controls.
- **Do not claim:** “Compared with Phoenix/Karma/FreeRTOS” unless an actual, defensible comparable implementation and protocol exists.

### G-EVAL-03 — Scope of measured benefit and cost

- **Category:** Evaluation gap
- **Observed:** K.10.4 reports localized advantages in CF04/CF07, six families with no measured advantage, and a CF16 cost where P2 uses one attempt versus P4's three.
- **Current-project response:** Saved reports preserve counterexamples and trade-offs rather than claiming universal P4 superiority.
- **Remaining uncertainty:** The breadth of scenarios, metrics and deterministic repetitions does not establish generalization or statistical significance beyond the tested host corpus.
- **Do next:** Keep results scenario-specific, report failures and negative controls, and explicitly state the finite deterministic test scope. Any new evaluation requires its own approved plan and must not alter frozen K.10 artifacts.
- **Do not claim:** Universal superiority, statistically significant population effects, energy savings, or broad real-world reliability.

### G-DEPLOY-01 — Board and silicon selection

- **Category:** Deployment/hardware gap
- **Observed:** Hardware planning notes an unresolved target mismatch between STM32U575ZI / NUCLEO-U575ZI-Q and NUCLEO-L476RG.
- **Current-project response:** A hardware demonstration plan specifies comparing capabilities before choosing and recording board/revision/toolchain/wiring.
- **Remaining uncertainty:** Actual board identity, MPU/security requirements, peripheral availability, debugger/toolchain, and hardware adapter design are not established by the planning document.
- **Do next:** Verify physical board markings and MCU, compare required capabilities and constraints, document the decision and obtain approval before firmware integration.
- **Do not claim:** The host reference model already runs on either board.

### G-DEPLOY-02 — Physical recovery and MCU-specific measurements

- **Category:** Deployment/hardware gap
- **Observed:** No physical build/flash trace, safe fault-injection log, successful post-recovery peripheral transaction, timing/resource measurements, or raw MCU trial bundle was verified in this audit.
- **Current-project response:** The hardware plan defines build/flash, healthy baseline, controlled failure, detection, policy decision, recovery action, fresh post-recovery operation and repeatability gates.
- **Remaining uncertainty:** Real driver status, fault-injection feasibility, recovery success, timing, RAM/Flash, energy, and repeatability.
- **Do next:** Follow the approved hardware gate and preserve raw logs, failed trials, binary hash, configuration and toolchain details.
- **Do not claim:** Hardware resilience or MCU performance based on virtual-system/UI or host C results.

### G-EVID-01 — Claim-to-artifact and source-to-passage links

- **Category:** Evidence gap
- **Observed:** The code, gates and reports contain many precise claims, but a consistent row-by-row map from every manuscript claim to source passage and project artifact is not yet present.
- **Current-project response:** Chat 03 adds traceability and claim-evidence reports, but these are documentation-level mappings and some links remain partial/unresolved.
- **Remaining uncertainty:** Several source claims lack page/claim-level primary evidence; raw experimental row/trace pointers have not been independently revalidated in this chat.
- **Do next:** Chat 04 should use the matrices as an editorial gate, cite only exact identified sources, preserve qualifiers and avoid upgrading an unresolved relationship into adoption.
- **Do not claim:** Every material claim is already publication-ready.

### G-NOV-01 — Novelty and legal status

- **Category:** Open question / evidence gap
- **Observed:** K.10.2 is bounded to inspected candidates; K.10.3 identifies a credible combination challenge; K.10.4 disclaims legal conclusions.
- **Current-project response:** The project has a working technical distinction hypothesis.
- **Remaining uncertainty:** Broader prior art, complete source/claim review, and legal standards are outside the evidence established here.
- **Do next:** Maintain a technical hypothesis, continue source-level comparison, and seek qualified legal review if a legal conclusion is required.
- **Do not claim:** Novelty, non-obviousness, patentability or freedom to operate as a finding of this research audit.

## 4. Priority order

1. **Before manuscript edits:** Resolve the most consequential primary-source gaps and map every material manuscript claim to exact source passages and project evidence.
2. **Before publication-quality result claims:** Audit existing raw K.10 artifacts without rerunning the campaign; ensure scenario-level values match the saved report and include counterexamples.
3. **Before any hardware claim:** Resolve board identity/capability and complete the documented physical acceptance sequence with raw evidence.
4. **Before any novelty/legal claim:** Expand and document the literature scope; keep legal questions explicitly outside the technical report.

## 5. Questions that must remain open

- Does any additional primary source disclose all or a material subset of the integrated association/quarantine/dependency/history mechanism?
- Do official primary records and full-text passages support each cited source's specific technical teaching?
- Are all raw K.10 output and trace files present in the current `main` tree, and can saved-only summaries be independently recomputed without re-execution?
- Does the eventual physical implementation preserve the host model's association, queue, dependency and terminal invariants under real driver behavior?
- Which exact board and silicon are selected, and can the planned safe fault-injection and measurements be executed repeatably?
- Which claims will be made in the final manuscript, and what exact evidence supports each one?

## 6. Final conclusion

The project has a credible **engineering problem and bounded host-model experiment**, and it has already identified significant adjacent prior art and a plausible multi-reference challenge. The research gaps are chiefly source coverage/full-text traceability, independent linkage of saved metrics to raw evidence, baseline-attribution clarity, and the complete absence of verified physical MCU evidence. These gaps do not invalidate the existing host-model work; they limit what may be claimed from it. The proper next step is evidence completion and careful claim qualification—not an unsupported novelty assertion or a premature hardware-success statement.
