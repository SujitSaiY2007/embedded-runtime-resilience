# Claude Master Prompt — Final Manuscript Drafting, Literature Audit, Figures, Reproducibility, and Word Deliverable

Repository: https://github.com/SujitSaiY2007/embedded-runtime-resilience
Working branch: `main` only.
Date/context: 26 October 2026.
**Scope lock: manuscript drafting and evidence/documentation only. No new software development, no runtime/policy code changes, no test campaigns, no hardware experiments, no rebuild/reflash, and no request for the user to repeat completed work.**

You are acting as (1) a rigorous embedded-systems research auditor, (2) a literature-review researcher, (3) a scientific manuscript writer, (4) a reproducibility/documentation editor, and (5) a publication-figure/table designer. The goal is a complete, coherent, submission-oriented manuscript and a Microsoft Word `.docx` version, backed by a verified bibliography and traceable evidence. Do not stop at an outline or recommendations: complete the manuscript, audit, figures/tables, reproducibility package documentation, and GitHub updates. Do not claim submission-ready until every stated gate is met; label any remaining author-only metadata clearly.

## 0. The user's priorities and fixed boundaries

- Focus on the project's achievements and contributions, and present them confidently, clearly, and prominently. Do not bury the contribution in a long limitations section or lead the abstract with caveats.
- Scientific accuracy is mandatory. Emphasize demonstrated successes, meaningful engineering decisions, comparative results, reproducibility, and practical significance. Do not hide material counterexamples, change denominators, inflate results, mislabel terminal outcomes as successful recovery, invent evidence, or imply a broader test than was performed.
- Keep limitations proportionate and concise: state the scope needed for a fair interpretation in Methods/Threats to Validity and one clear summary in Discussion. Do not repeat the same caveats in every section.
- No more coding or hardware. Existing source code, reports, result tables, screenshots, and the existing candidate-v2 campaign evidence may be inspected and documented; do not alter the runtime or run another campaign.
- Keep the protected `reference/` runtime, frozen K.10 evidence, historical reports, raw artifacts, existing hardware source and experimental records intact. No deletion, replacement, or regeneration of frozen evidence.
- Do not involve the professor or contact any author. Prepare a draft and a concise final author-confirmation checklist for the user's later review.
- Never ask the user to provide a setup photo as a blocker. Search the repository for existing hardware photos/screenshots first. If none are available, continue and add a clearly labeled placeholder in the figure plan; mention that the user may optionally supply a setup photo later.
- Use author–year in-text citations and an author–year reference list, not IEEE numeric citations. Deliver the final manuscript in Microsoft Word `.docx` format as well as an editable Markdown source. Use the target journal's current required style only after verifying its author guide; if the target journal requires numbered citations, explain the conflict and provide an author–year draft plus a separate conversion recommendation rather than silently changing the user's requested style.

## 1. Mandatory repository inspection and evidence inventory

Read the current `main` branch and relevant project files before editing. At minimum inspect:

- Root `README.md`, `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, `PROJECT_MANUAL.md`, `CHAT_CONTINUITY_PROTOCOL.md`, `NEXT_CHAT_PROMPT.md`, `research/PART_II_CHAT_PLAN.md`, and the research/novelty reports.
- Frozen K.10 host result report `research/phase2_k10_p4_advantage_novelty_results.md`, original runtime and experiment harness, and all available K.10/K.10.4/K.11/K.12 reports and Gate A–E contracts.
- Existing manuscript workspace: `research/manuscript/DRAFT_MANUSCRIPT.md`, `EVIDENCE_LEDGER.md`, `REFERENCE_AUDIT.md`, `FIGURE_TABLE_PLAN.md`, `OPEN_ISSUES.md`, `README.md`, scripts, derived data, and figures.
- Candidate v2 under `reference_v2/`, its tests and runner, plus the Phase 1 closure/validation record if present.
- Hardware firmware under `Plan2.0/firmware/bme280_policy_integration/`, `Plan2.0/results/`, `research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md`, hardware integration notes, all relevant project handoffs, and the saved evidence inventory.
- Existing citation register, reference audit files, novelty/prior-art audit, related-work candidates, and any existing references under the repository.
- All image assets and evidence directories. Locate actual hardware setup photos, STM32CubeIDE build/debugger screenshots, matrix/status screenshots, control-trial screenshots, and UI screenshots if they exist. Record exact path, what each image proves, and its evidence status.

Do not assume that a filename means the content has been checked. Open/read relevant files and inspect the exact source values. Maintain an inventory table with: artifact path, evidence type, relevant claims, reproducibility role, whether the artifact is present/complete, and whether it can be published.

### Screenshots and photos: preservation instructions

1. Search the entire repository and available project files for existing screenshots/photos before concluding that they are missing.
2. Preserve original image bytes and filenames when practical. Do not redraw a screenshot and call it an original, crop away context that affects interpretation, or create fake debugger values.
3. If useful screenshots exist in the repository but are poorly organized, add an index under `research/manuscript/evidence/hardware/README.md` linking to their existing locations. Avoid duplicating large files unnecessarily.
4. If the original screenshots are available in the current workspace or attached evidence and are not yet in GitHub, copy the original files into a dedicated additive path such as `research/manuscript/evidence/hardware/`, then add an index that records original filename, capture context if known, what it supports, and what it does not establish. Do not manufacture sandbox paths or assume an image is available if it is not.
5. If images cannot be accessed by Claude in its environment, record exactly which files are missing and leave a figure placeholder. Do not ask for a new run to recreate screenshots. The user may optionally provide the physical setup photo later; it is not a blocker.
6. Add useful setup photos only as supporting visual documentation, never as a substitute for electrical/firmware evidence. Caption the board, sensor, wiring, and visible components only when identifiable from the image. Do not infer pin connections that are not visible.

## 2. Canonical evidence and numerical facts

Keep these evidence streams separate in every table, figure, caption, and claim:

### A. Frozen host/reference campaign (P0–P4)
- The frozen K.10 report describes 16 case families × 5 policy variants (P0–P4) × 5 repetitions = 400 deterministic host executions.
- The original raw files `k10_runs.csv` and `k10_traces.csv` could not be found in any of the 15 remote branches or in the user's local search. The original report table is therefore the source of record for reported per-family values. Do not recreate raw files under their original names, claim to have inspected missing traces, or recalculate unavailable per-repetition data.
- P0–P3 are author-constructed in-house ablations, not independent replications of Phoenix, KARMA, shadow drivers, microreboots, or any other published method.
- Seven case families are reported as identical across all P0–P4; P4 is not better in every case. In one family P2 has a lower reported attempt count than P4. Preserve these counterexamples as evidence of trade-offs.
- CF01/P2 attempt count is contradictory in the frozen report (table versus narrative); omit that disputed numeric value unless primary records resolve it. CF08/P0 also contains a report conflict; show only what the data table supports and flag the mismatch in the evidence audit.
- Do not say the 400 runs were re-executed during this manuscript task.

### B. Candidate v2 software/code validation
- The additive candidate lives under `reference_v2/`; do not replace or conflate it with protected `reference/`.
- User-observed evidence reports CTest 1/1 passed and two 560-run campaigns (16 case families × 7 variants P0–P6 × 5 repetitions = 560 per campaign) with complete matrices, stable repetitions, deterministic replay, zero harness failures, and matching run/trace SHA-256 hashes. Find the exact phase-1 closure report and exact hash values in the repository before citing them. If a hash or artifact cannot be found, say so; do not invent one.
- These are software/host candidate-v2 results, not physical hardware results and not the original frozen 400-run P0–P4 campaign. Clearly explain why P5 reset-only and P6 exponential-backoff variants were added and which version of the runtime each campaign used.
- The original manuscript's primary comparison may still center on frozen P0–P4. Include v2 as a separate, versioned extension only if its exact records and report can be traced. Do not merge P0–P6 rows into one undifferentiated comparison.
- The user has explicitly said there are to be no more runs; do not request or launch any.

### C. Physical hardware evidence (Phase 2 CLOSED; no more experiments)
Target: ST NUCLEO-L476RG, board revision MB1136 C, STM32L476RG, BME280 at I²C address 0x76, expected chip ID 0x60. A wrong-address transaction at 0x77 is used to provoke a NACK. The physical evidence is distinct from the host campaign.

**Five control trials:** User-reported debugger values for all five control trials show NACK result -1 (= E_NACK), NACK observed=1, post-NACK read OK=1, chip ID=96 (0x60). In these controls, no full `iinit()` call occurred between the NACK probe and the next sensor read. Interpret narrowly: for this absent-address NACK scenario, a full peripheral initialization call was not necessary to obtain a successful subsequent sensor read in this setup. Do not say that no cleanup occurred at all: the transaction helper does local abort/flag cleanup.

**Single five-policy physical comparison run:** reported values P0–P4:
- `physical_status = [7, 1, 7, 7, 1]`; 7 = `R_TERMINAL`, 1 = `R_PASS`.
- `runtime_result = [4, 1, 4, 4, 1]`; protected runtime `OutcomeCode` maps 4 to `OUTCOME_TERMINAL_ESCALATE`.
- `release_result = [0, 1, 0, 0, 1]`.
- `post_chip_id = [0, 96, 0, 0, 96]`, where 96 = 0x60.
- The baseline checks were reported as successful for all five policy slots.
- Thus P1 and P4 passed the harness and read back the expected chip ID; P0, P2, and P3 ended in terminal escalation and did not yield successful post-fault reads. Do not portray terminal outcomes as recovery success, and do not imply a processor crash.
- This is one policy-comparison run, not five independent runs per policy. The five controls are five trials within the control execution, not five independent builds.
- Sampled `matrix_status` indices 0, 15, 16, 31, 32, 47, 48, 63, 64, 79 were shown as 1; index 79 showed action 4, reason 19, terminal 1, retry authorization 0, runtime start 1. A full readable 80-entry export is not available. The matrix is a software policy-decision matrix, not 80 physical injections.
- The committed diagnostic firmware is `Plan2.0/firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix_diagnostic.c`; the runtime enum is in `reference/include/ref_runtime.h`. The exact modified control source used in CubeIDE is not separately committed or hash-linked to the flashed ELF/binary. The user-supplied `hardware_exp.c` source hash previously recorded is `8d65294a7dbf8aca22cab9f2c56732bdb015bf7c3fab87cee6b555f7ae6a1ee8`; this is a source hash, not proof of binary identity.
- A build screenshot reports 0 errors and 0 warnings. Linker size output reports text=12,948 bytes, data=112 bytes, BSS=12,704 bytes, total=25,764 bytes. Do not misrepresent these as runtime stack, recovery latency, energy, or a complete target resource profile.
- Hardware phase closure report: `research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md`. The project has decided no further hardware runs will be performed. Treat this phase as closed for the planned scope.

### D. Explicitly unsupported hardware claims
Do not claim physically stuck SDA/SCL recovery, 80 physical fault injections, five independent physical runs per policy, statistically established reliability, a measured latency/stack/energy profile, exact flashed-binary identity, or universal P4 superiority. Keep these caveats concise and proportionate; they are not a reason to obscure the successful observed outcomes.

### E. Existing source-level findings and implementation caveats
The protected runtime audit identified source-level limitations such as queue-full release behavior, an 8-bit generation counter boundary, invalid-target episode handling, a fixed 256-record trace buffer, and a dead/unreachable P4 reason branch. These were observed in the protected source/probes and are relevant to the validity of the original P0–P4 comparisons. Do not change the code. Audit the manuscript's causal attribution carefully: if a P4 advantage partly arises from a runtime defect or episode leak in other variants, state that mechanism and narrow the claim. Do not present a defect-induced difference as definitive evidence that the integrated policy is universally superior. The candidate v2 changes are separate and must not be retroactively attributed to the frozen K.10 campaign.

## 3. Required scientific contribution audit — do this before final prose

Create/update `research/manuscript/CONTRIBUTION_CLAIM_AUDIT.md` with a table containing:
- proposed contribution/claim;
- exact evidence and repository path;
- evidence class (frozen host, candidate-v2 host, source inspection, hardware observation, literature synthesis, interpretation);
- closest related work;
- what is genuinely distinct in this project;
- strength rating (strongly supported / supported within scope / preliminary / unsupported);
- exact wording recommended for the manuscript;
- wording that must not be used;
- whether further coding or experiments would be needed (answer should not request any now).

Audit at least these potential contributions:
1. A statically allocated, zero-heap recovery runtime and its explicit resource capacities.
2. Context-aware policy decisions using fault class, association precision, attempt history and caller-supplied safety flags.
3. Exact-event quarantine and the event release/verification path.
4. Bounded recovery behavior/attempt limits and episode closure, including what source-level findings complicate attribution.
5. The frozen 400-execution P0–P4 host comparison and the nature/limitations of the in-house ablations.
6. The separate P0–P4 physical I²C NACK demonstration on STM32L476RG/BME280, including P1/P4 pass and P0/P2/P3 terminal outcomes.
7. The five no-full-`iinit()` control trials and what they establish in the narrow NACK scenario.
8. The additive P0–P6 candidate-v2 extension, 560-run campaign reproducibility and determinism, only if exact evidence/hashes are present.
9. The browser UI/software demonstrator that routes through the same C runtime; distinguish implementation integration from algorithmic novelty.
10. The reproducibility package: source, deterministic host harness, scripts, documented evidence and provenance.

Do not claim “first,” “novel,” “state of the art,” “best,” “outperforms existing methods,” or “superior to published methods” without direct evidence. A defensible contribution may be a reproducible integration, explicit design/ablation study, engineering method, bounded implementation, or an empirical characterization. Make a comparison matrix against related studies, not a false claim that the authors implemented those studies' systems.

## 4. Literature review and reference overhaul (author–year style)

Perform an actual, broad literature search. Prioritize publisher pages, DOI records/Crossref, ACM DL, IEEE Xplore, USENIX, Springer, Elsevier, institutional repositories, standards bodies and full texts. Use web search when available. Do not rely solely on the existing 10-item bibliography or the preliminary list of approximately 43 references.

Search and organize literature across:
- embedded peripheral and device-driver recovery;
- fault tolerance and dependability in embedded/real-time systems;
- hardware/software fault injection and evaluation methodology;
- context-aware recovery, retries, restart/reset, backoff and recovery decision policies;
- event queues, event quarantine, transaction/event isolation and dependency-aware recovery;
- runtime verification and safety context;
- constrained/zero-heap/static-memory runtime design;
- relevant recent journal studies and closest prior art, especially the Kleeberger line on robust embedded software/peripheral failures and related journal/conference publications.

For every cited source, verify:
- exact author names and order;
- title;
- year;
- journal/conference/book/report;
- volume, issue, pages or article number where applicable;
- DOI and stable publisher/institution URL;
- peer-reviewed status/type;
- the specific claim it supports, ideally checked against full text or a reliable abstract if full text is unavailable.
Record verification status and what was actually checked in `REFERENCE_AUDIT.md`. Never invent bibliographic details, DOI, quotes, results, or page ranges. Remove unverifiable, irrelevant, predatory, duplicate, or weak citations. Keep a reasonable balance of seminal foundational work and recent relevant work; meet the project's preference for a high journal-article share where relevant papers exist, but never add filler merely to hit a percentage.

**Author–year in-text examples:** (Smith and Rixner, 2015), (Branco et al., 2019), or narrative citations such as “Smith and Rixner (2015)”. Ensure every in-text citation matches exactly one reference-list item and every listed reference is cited in text unless explicitly labelled “Further reading.” Use author–year throughout all tables and figure captions too. Do not use numbered citations such as [1], [2] in the manuscript.
- Reference list alphabetized by first author's surname unless the verified target venue requires otherwise.
- If the user requires a “Word format,” the final primary deliverable must be `.docx`, with normal editable Word text, real tables, inserted figure assets, captions, headings, and author–year references. Also maintain Markdown source in GitHub. A PDF may be included as a preview only if practical; do not substitute PDF for DOCX.
- Check the current author guide for the recommended target journal from its official publisher website. The existing first-choice candidate is *Journal of Systems Architecture* (Elsevier), provisional only. Verify scope, article type, citation style, template, abstract and word limits, figure requirements and data/code policies. If its official requirements conflict with author–year citations, report that clearly and retain an author–year master as the user requested; do not misstate compliance.

Create/update:
- `research/manuscript/REFERENCE_AUDIT.md`
- `research/manuscript/RELATED_WORK_COMPARISON.md` (comparison matrix of studies, methods, assumptions, hardware/platform, evaluation, findings, relation to this work, and what is not directly comparable)
- `research/manuscript/CONTRIBUTION_CLAIM_AUDIT.md`
- `research/manuscript/OPEN_ISSUES.md` and `README.md` to match the actual state.

## 5. Manuscript: required structure and message

Write a coherent complete paper, not a project report. Adapt the section names to the verified target venue, while including:

1. Title (mark as proposed if not author-approved).
2. Abstract with problem, method, evidence types, strongest supported quantitative outcomes and contribution. Lead with the problem and what was accomplished, not a list of limitations.
3. Keywords.
4. Introduction: importance of peripheral faults in constrained event-driven firmware, practical problem, research questions, gap, and concise contribution bullets.
5. Background and related work: thematic synthesis, not a list of paper summaries. Compare existing approaches and explain where this project fits.
6. Research gap and novelty/contribution positioning: careful, evidence-backed wording, supported by the contribution audit.
7. System model, assumptions, fault/event model, context and association levels, safety flags, resource constraints.
8. Runtime architecture and policy definitions P0–P4; define precisely what differs among variants and what they share. Include candidate v2 P5/P6 only in a clearly separate subsection if verified and relevant.
9. Algorithm/state machine: policy selection, quarantine, retry/reinitialization, verification and release; explain boundedness from source without claiming unmeasured time complexity as measured latency.
10. Experimental methodology: host campaign design, case families, metrics, repetition scheme, evaluation script/report provenance, execution environment and evidence limitations.
11. Host results: correct tables/plots from committed source report; explain strongest results, cases where all policies tie, trade-offs and counterexamples. Never invent repetition-level distributions when raw CSVs are unavailable.
12. Hardware implementation and observations: board, MCU, BME280, I²C address, NACK injection, control trials, policy run outcomes, captured source/build details and figure references. Explain that the 80-entry decision matrix is not 80 physical fault injections.
13. Software demonstrator and integration: architecture and path to the same authoritative C runtime; avoid claiming UI implementation is algorithmic novelty.
14. Comparison with existing studies: explicit matrix plus narrative. Compare aims, fault model, recovery granularity, hardware/software, memory/runtime assumptions, evidence type, metrics, and reported outcomes. Mark “not reported/not comparable” rather than infer. Do not compare our attempt count to other papers' timing or different metrics as if equivalent.
15. Discussion: what results mean for embedded-system developers, what was learned, trade-offs and practical implications.
16. Threats to validity and limitations: concise, accurate, proportional; include only the main caveats necessary for interpretation and avoid repeating them in every section.
17. Reproducibility and artifact availability: detailed software and hardware reproduction instructions (below).
18. Conclusion: contributions and observed results, no universal-superiority claim.
19. Author declarations with explicit placeholders for unknown information; do not fabricate affiliations, emails, CRediT roles, funding, conflicts, ethics, AI disclosure, or data DOI.
20. Alphabetized author–year references.
21. Appendices/supplement: detailed policy definitions, complete variable/metric dictionary, experimental artifact inventory, reproduction checklist, and supplementary tables if useful.

## 6. Required comparisons and tables

At minimum prepare these tables, with clear captions and source provenance:
- Policy definitions P0–P4 (decision behavior, retry limits, association/context use, reinit/degrade/escalation behavior, shared runtime mechanisms).
- Experimental design and dataset/run matrix (host 400 executions and separate candidate-v2 560-run campaign if verifiable).
- Host results by family and policy using only frozen report values; mask/omit disputed CF01/P2 attempts and explain CF08 conflict.
- Summary of the key outcomes, ties, trade-offs and counterexamples (include cases where P4 has no advantage and where a baseline is cheaper).
- Hardware results: five control trials and single P0–P4 policy run in separate blocks/columns; clearly identify observed versus source-derived values.
- Comparison against prior studies using verified author–year citations; distinguish direct comparable metrics from conceptual context and not-comparable fields.
- Resource/capacity table with static source-defined capacities and the linker-size figures only if source/build evidence is present; label them accurately.
- Evidence/reproducibility table mapping each result to source files, scripts, evidence type, and reproduction command.
- Claim-to-evidence matrix or contribution audit summary.
Every table must be explained in the body; no orphan tables.

## 7. Required figures and diagrams

Create publication-quality figures, not just a list of figure ideas. Use vector output (SVG/PDF where supported) and high-resolution PNG previews. Use consistent monochrome/grayscale style suitable for print; modest accent colors may be used only where they improve distinction and the venue allows them. All figures must be readable at final print size and have complete captions.

Minimum set:
1. **System architecture diagram:** event queue, scheduler, runtime episode, policy engine, quarantine, peripheral adapter, verification and release, trace; clearly distinguish hardware path from host simulation path.
2. **Policy decision/recovery flowchart or state machine:** fault detection → association/safety context → policy action → retry/reinitialize/degrade/escalate → verify → release or terminal state.
3. **Experimental protocol diagram:** frozen 400-run host/reference campaign and physical hardware tests as separate streams, with candidate-v2 campaign shown separately only if verified.
4. **Host result matrix/heatmap:** 16 case families × P0–P4 from the frozen report, with a legend, explicit treatment of disputed values, and no inferred missing repetitions.
5. **Outcome comparison figure:** appropriate count or categorical comparison based strictly on report table values, explaining the denominator and what “advantage” means. Do not manufacture percentages or infer raw run-level distributions.
6. **Hardware transaction sequence diagram:** wrong-address NACK, runtime decision, policy-specific action, post-read/release for P1/P4, terminal escalation for P0/P2/P3, plus separate no-full-initialization control path.
7. **Hardware setup photograph panel:** include an existing original setup photo only if present and useful; otherwise a placeholder in the plan and continue without blocking.
8. **Reproducibility/artifact flow diagram:** source → build/run script → result files → validation/hash → derived tables/figures → manuscript.
9. Optional: static memory/layout diagram or bounded resource table visualization, only if it adds real explanatory value.

Generate figure files and maintain scripts for derived visualizations in `research/manuscript/figures/` and `research/manuscript/scripts/` where practical. Do not invent measured values. Use captions that state whether content is host-derived, source-derived, or physically observed. Each figure must be cited and explained in the manuscript. Update `FIGURE_TABLE_PLAN.md` with final filenames, provenance, generation command and status.

## 8. Reproducibility: software and host experiments

The paper must include a practical, step-by-step software reproduction section, with exact repository paths and commands that are verified against existing scripts/build files. Inspect actual CMake, Python, shell and test scripts before writing commands; never guess a command or dependency. Include:
- repository/branch/commit or tagged source version;
- prerequisites, OS/compiler/interpreter/build tools as recorded;
- how to build the protected host runtime/tests without modifying it;
- how to run the already-existing host test suite and manuscript derivation/figure scripts;
- how to regenerate derived tables and plots from committed source data;
- how to reproduce source-level probes if they are safe and already present;
- where outputs are written, which outputs are missing, and what is expected;
- deterministic replay/hash validation for candidate-v2 only using the already recorded outputs/scripts; document it, do not rerun it;
- evidence hashes and manifests when they are actually recorded;
- explicit statement that original K.10 raw CSVs are unavailable and the original host table is the source of record for that campaign;
- version boundaries between protected `reference/` P0–P4 and additive `reference_v2/` P0–P6;
- avoid any instructions that overwrite the frozen report or raw evidence.

Commands must be copied from actual scripts/README/CMake definitions and checked for path correctness. If a command has not been run during this manuscript task, label it “documented reproduction command, not executed during this task.” Do not say “fully reproducible” if required raw inputs are missing; say exactly which aspects are reproducible from the committed repository and which are only report-level reproducible.

## 9. Reproducibility: hardware and firmware

Provide a hardware reproduction appendix based only on committed source and the recorded setup. No experiment is to be run now. Include:
- board and MCU: ST NUCLEO-L476RG, STM32L476RG, MB1136 C where verified;
- BME280, address 0x76, expected ID 0x60; absent address 0x77 as the controlled NACK;
- exact source file path(s), required include paths, runtime source linkage and firmware project layout;
- toolchain/tool versions only where captured; clearly mark unknown versions;
- safe wiring/power notes only if documented in repository, otherwise ask the user to confirm before future use rather than inventing pinouts;
- how the project is opened/built in STM32CubeIDE, which file(s) to include, debugger variable names to inspect, and expected/observed result ranges;
- how the policy run and five control-trial evidence are documented, without requiring another run;
- linker output values with clear classification as build/linker sizes, not stack/timing/energy;
- how to preserve screenshots and source/binary provenance;
- exact source hash only if the source bytes are available and hash is in the repository; state explicitly that the hash does not prove which binary was flashed;
- a clear warning that no stuck-bus fault was tested and that this is not a generic peripheral recovery certification;
- how to reproduce the documented build/run in future if desired, but do not tell the user to rerun it now.

Never fabricate a full wiring diagram from a setup photo or claim the firmware has been rebuilt/reflashed during manuscript preparation. The physical setup photo is optional supporting context, not a reproducibility prerequisite.

## 10. Word deliverable and document quality

Produce:
- `research/manuscript/DRAFT_MANUSCRIPT.md` — full editable manuscript source, all author–year citations.
- `research/manuscript/DRAFT_MANUSCRIPT.docx` — fully editable Microsoft Word document with real Word headings, tables, figure images, captions, citations and reference list. Use a proper document-generation workflow; do not rename Markdown or HTML to `.docx`.
- `research/manuscript/CONTRIBUTION_CLAIM_AUDIT.md`
- `research/manuscript/RELATED_WORK_COMPARISON.md`
- `research/manuscript/REFERENCE_AUDIT.md`
- `research/manuscript/EVIDENCE_LEDGER.md`
- `research/manuscript/FIGURE_TABLE_PLAN.md`
- `research/manuscript/OPEN_ISSUES.md`
- `research/manuscript/README.md`
- `research/manuscript/evidence/hardware/README.md` if there are image assets to index; only commit image bytes if actually accessible.
- figures and generation scripts, where practical.
- optional PDF preview, only as a secondary deliverable.

Make Word formatting professional and consistent: title page/title block, abstract, keywords, heading hierarchy, page numbers, caption styles, table header rows, accessible figure captions/alt text where possible, readable tables that fit page width, consistent spacing, hanging-indent author–year references, no comments/placeholders that look like accidental editorial debris. Remove internal HTML ledger tags from the Word deliverable while keeping traceability in the ledger file. Keep a version-controlled Markdown source.

## 11. Citation and contribution integrity gates

Before declaring the draft complete:
- verify every cited work from an authoritative source and document verification tier;
- check the actual paper/full text for the strongest related-work claims where accessible;
- check author-year consistency in text, captions, tables and bibliography;
- ensure every empirical claim has a source path/evidence class in the ledger;
- ensure all table/figure numbers and values agree across abstract, results, discussion and conclusion;
- do not use “statistically significant” unless a valid statistical analysis exists;
- do not compare incomparable metrics;
- do not state a physical recovery success for P0/P2/P3;
- do not claim the hardware experiment validates all 16 × 5 host contexts;
- do not claim universal P4 superiority;
- do not claim candidate-v2 results are from the frozen P0–P4 reference campaign;
- do not state that all Claude-suggested changes or all tests were performed unless there is direct repository evidence;
- explicitly document any inaccessible screenshots and missing raw files, without blocking the draft.

## 12. Git and completion protocol

- Work on `main` only; preserve all branch and reference-runtime rules.
- Make only additive or manuscript-focused edits. Never alter the protected runtime, frozen host report, raw experimental evidence, or hardware source to improve the narrative.
- Commit the manuscript files, updated evidence/reproducibility docs, figure sources/outputs, and the Word file if file size and repository rules allow it.
- If image files cannot be uploaded or a binary document tool is unavailable, report the exact blocker and leave a correct reproducible source/workflow; do not fake the file.
- Do not claim that a citation audit, figure generation, document conversion, build, or test occurred unless it was actually performed.
- Final response must report: (1) files created/updated, (2) commit SHA(s), (3) verified reference count and verification tiers, (4) figures/tables completed, (5) DOCX path/link, (6) software and hardware reproducibility coverage, (7) screenshots preserved and those still missing, (8) claims strengthened/narrowed by the contribution audit, and (9) concise author-only decisions still needed.
- Finish the drafting task; do not return merely a plan asking for permission.

## Final instruction

Deliver the strongest clear, achievement-centered, comparison-rich, reproducible manuscript the evidence supports. Make the work look as significant as it truly is through careful explanation, relevant verified comparisons, high-quality visuals, and transparent provenance—not through exaggeration. No more code development or experiments: only manuscript, literature, evidence organization, reproducibility documentation, figures/tables and Word preparation.
