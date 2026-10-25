# Claude Task Prompt — Draft a Journal-Quality Research Manuscript from This Repository

Repository: https://github.com/SujitSaiY2007/embedded-runtime-resilience

You are the lead technical writer and critical research auditor for a serious embedded-systems manuscript. Your goal is a rigorous, submission-oriented, journal-quality draft—not marketing copy. Read the repository before drafting. Use the complete source tree, existing research reports, frozen experiment records, literature/prior-art reviews, hardware reports, code and UI documentation as the primary evidence base.

## Project and author context

Working research theme: a lightweight, zero-heap, context-aware peripheral recovery policy with bounded decision behavior and event quarantine for resource-constrained event-driven embedded systems. Five variants P0–P4 are compared. The integrated policy is P4. The repository also contains a browser demonstrator that routes requests through a Python bridge and C virtual-system adapter into the same C reference runtime.

Planned author line (verify spelling/ordering against repository records before finalizing):
- SUJIT SAI Y
- MITHUL RASHWANTH SR
- ROHIT MATHUR* (corresponding author)

Do not invent affiliations, emails, funding, ethics declarations, or author contributions. If missing, use clearly marked placeholders or ask in a final checklist. Do not change the approved project title/abstract if the repository identifies them as frozen/approved; if not found, propose alternatives separately and mark them as proposals.

## Mandatory first phase: repository and evidence audit

1. Inspect the current default branch and repository structure. Read the root README, project state/handoff/decision logs, project overview, architecture map, demonstrator guide, all final K.10/K.10.4/K.11/K.12 research reports, the Gate A–E contracts, the frozen host/reference result files, the prior-art/novelty reviews, the bibliography/reference-overhaul files, and all Plan2.0 hardware evidence reports relevant to the BME280 experiment.
2. Identify the canonical/frozen artifacts and their exact paths. Do not edit or regenerate them. In particular, preserve `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen 400-execution host evidence, historical records, and user-saved hardware screenshots.
3. Build an evidence ledger with each manuscript claim mapped to a repository path and evidence class:
   - frozen host/reference-model result;
   - source/code property;
   - user-observed physical hardware result;
   - source-derived expectation, not captured measurement;
   - interpretation/hypothesis;
   - not supported / missing.
4. Identify contradictions and caveats before drafting. Do not silently reconcile conflicting numerical reports. The existing CF01 P2-attempt discrepancy must be treated according to repository guidance; preserve the frozen source record and omit the disputed count from numerical claims unless primary evidence resolves it.
5. The new diagnostic hardware report records the following user-observed run: `finished=1`, `overall_code=1`, `progress_stage=900`; baseline error slots 0 and baseline checks shown successful; `nack_result[0..4]=-1` with source-defined `E_NACK=-1`; physical statuses P0–P4 = 7,1,7,7,1 where 7=`R_TERMINAL` and 1=`R_PASS`; `post_read_ok[1]=post_read_ok[4]=1`; `post_chip_id[1]=post_chip_id[4]=96=0x60`; `release_result[1]=release_result[4]=1`. The 80-row embedded decision matrix uses five policies × 16 provisional contexts. Its contexts are not yet established as identical to the frozen CF01–CF16 host families. The user said “all matrix statuses were 1 except the last,” but a screenshot visible in the conversation showed `matrix_status[79]=1`; report this discrepancy and do not claim a full 80-element array audit unless the repository contains a complete readable export. The harness reports `overall_code=1`, which is its own aggregate, not independent proof of every matrix slot. See `Plan2.0/results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md`.
6. Hardware evidence is one controlled wrong-address I²C NACK (test address 0x77), followed by I²C1 peripheral reinitialization/recovery and fresh BME280 ID read at 0x76. It supports post-recovery reads for P1 and P4 in this observed run. It does NOT prove physically stuck SDA/SCL recovery, 80 physical fault injections, repeatability, MCU timing/stack/Flash/RAM/energy metrics, or universal P4 superiority.
7. The frozen host/reference campaign is 16 case families × 5 policies × 5 repetitions = 400 deterministic executions. It is separate from hardware evidence. Do not present the 80 embedded decisions as a replication of the 400-run host campaign or as 80 physical tests.

## Literature and reference policy — critical

You have freedom to choose, add, or replace references when scientifically necessary, including recent primary literature, standards, technical reports and foundational sources. But:
- Verify every reference's existence, exact title, authors, year, venue/publisher and DOI/URL using authoritative publisher, DOI, standards-body or institutional sources.
- Use primary sources for technical claims wherever possible; use review papers to contextualize, not substitute for seminal primary evidence.
- Remove fabricated, unverifiable, irrelevant, predatory, or weakly connected references.
- Never invent DOI, page numbers, volume/issue, article numbers, standards editions, experimental values or quotations.
- Maintain a source-to-claim map and explain why each citation supports the sentence it accompanies.
- Distinguish direct adoption, adaptation, conceptual background, comparator and no demonstrated influence when discussing prior art.
- Search widely enough to establish a defensible research gap; do not declare “first,” “novel,” or “state of the art” unless the evidence truly warrants it.
- The repository may contain approximately 43 preliminary references, but that is not a quota. Retain the useful ones, correct only when verified, and add stronger sources if needed. Aim for a high-quality, relevant bibliography, not citation padding.
- Do not cite the project's GitHub repository as if it were peer-reviewed literature. It may be mentioned as a code/evidence availability location if appropriate and journal policy permits.
- Use IEEE numeric citations as the default only if consistent with the target venue. Recommend a realistic high-quality journal/venue and adapt the manuscript structure/style to its current author guidelines. Do not imply acceptance or guarantee a “top-grade” outcome.

## Required manuscript work

Produce a complete first draft with:
1. Title (respect approved/frozen title if located).
2. Abstract with quantified results only where the repository supports them.
3. Keywords.
4. Introduction, motivation and research question.
5. Background and related work, organized by technical themes rather than a paper-by-paper list.
6. Explicit research gap and carefully scoped contributions.
7. System model, assumptions, fault/event model, threat/validity boundaries where relevant.
8. P0–P4 policy definitions, runtime architecture and design rationale.
9. Recovery state machine/algorithm, quarantine semantics, boundedness and zero-heap claims, with source-level proof or caveat for each.
10. Experimental methodology: frozen host/reference campaign, case families, repetitions, metrics, baselines, environment and reproducibility details.
11. Results with correctly computed tables/figures from committed result data. Do not eyeball or fabricate numbers. Explain counterexamples, ties, trade-offs and resource bounds.
12. Physical hardware validation as a separate subsection: board/sensor/toolchain, controlled NACK method, actual observed values, successful P1/P4 post-read evidence, and all limits.
13. Software demonstrator/UI architecture and how it uses the authoritative C runtime.
14. Discussion, threats to validity, limitations and reproducibility.
15. Conclusion and specific future work.
16. Verified references and appendices/supplementary artifact inventory as appropriate.

Include a clear distinction among host results, source-level properties, and physical hardware evidence throughout. Do not turn expected source values into measured observations. Do not imply the MCU ran the frozen 400-execution experiment.

## Figures, tables, and presentation

- Plan figures/tables that materially improve the paper: architecture, policy comparison, recovery state machine, experimental protocol, host results, hardware transaction sequence, evidence/limitations table.
- Derive plots only from committed raw/result data and make scripts or data provenance explicit. No fabricated values or decorative charts.
- Use journal-compatible, legible figures and captions that state what is measured and what is modeled.
- Use consistent symbols, policy names, units, denominators, confidence/variance language and rounding.
- Explain every figure and table in the body.

## Deliverables

Create a new manuscript work area without overwriting frozen reports, for example:
- `research/manuscript/README.md` — manuscript status, chosen venue rationale, artifact map and open author metadata.
- `research/manuscript/DRAFT_MANUSCRIPT.md` — complete draft.
- `research/manuscript/EVIDENCE_LEDGER.md` — claim-to-evidence map, evidence class and caveats.
- `research/manuscript/REFERENCE_AUDIT.md` — verified reference table with authoritative links/DOIs, metadata status and claim relevance.
- `research/manuscript/FIGURE_TABLE_PLAN.md` — proposed visuals and exact source data.
- `research/manuscript/OPEN_ISSUES.md` — unresolved contradictions, missing details, and questions for authors.
- If appropriate, scripts and derived data for figures, without altering raw/frozen evidence.

Before writing the final draft, provide a concise audit summary of what you inspected and any evidence gaps. Then draft. If a required detail is missing, proceed with a marked placeholder rather than blocking the whole manuscript.

## Quality gates before completion

- Every empirical sentence has a traceable source.
- Every citation is verified and actually supports the claim.
- No unsupported novelty, superiority, physical reliability or resource claims.
- The 400 host executions and one observed hardware run are not conflated.
- The provisional 80-row firmware matrix is not misrepresented as physical experiments or exact replication of the host case families.
- Preserve the CF01 discrepancy handling rule and all frozen records.
- Methods are reproducible from documented artifacts; toolchain details are reported only when captured.
- Abstract, results, tables, conclusion and claims agree numerically.
- Include a final checklist of missing author metadata, venue-specific formatting steps, unresolved evidence questions and files that still require human confirmation.

## Git safety and scope

Work only on `main`, in keeping with repository policy. Never delete, rewrite, rerun or overwrite frozen evidence. Do not alter the protected runtime or prior-art records to make the narrative easier. Make manuscript artifacts additive and reviewable. Do not claim that a build, citation audit or test was run unless you actually ran it and record the environment. Finish with changed-file list, commit SHA, validation performed, limitations and next steps.

Target outcome: the strongest scientifically honest, well-supported, journal-ready draft possible from the available evidence. Rigor and traceability take precedence over length or aggressive claims.
