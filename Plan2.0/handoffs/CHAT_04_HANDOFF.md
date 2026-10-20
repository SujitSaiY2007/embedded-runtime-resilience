# Chat 04 Handoff — Journal-First Reference Quality Audit

**Date:** 2026-10-20  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Branch policy:** `main` only  
**Current scope status:** Chat-04 audit, editable manuscript reconstruction, reference-purpose mapping, and handoff are complete. The reconstructed DOCX is delivered in the conversation; the binary is not committed to GitHub. The user supplied a PDF, so the manuscript was rebuilt as a new editable draft rather than editing an original DOCX/LaTeX source.

## 1. Main answer to the professor's journal-reference requirement

The user-provided `Manuscript Draft.pdf` contains 24 numbered references on pages 11–12. The bibliography audit found:

- **12/24 (50.0%)** journal articles if IEEE *Computer* reference [12] is accepted in the professor's journal/magazine category.
- **11/24 (45.8%)** under a stricter rule that excludes [12] from the journal-article quota.
- At least **18/24 journal articles** are required to reach 75% with a fixed 24-reference denominator.
- The final policy must follow the professor's definition of “journal article”; either classification is below the 75% threshold.

The earlier 43-row Plan2.0 reference register is a prior-art inventory, not the manuscript bibliography. Its publication-type counts must not be substituted for the manuscript's journal-share calculation.

Plan2.0's prior target remains approximately **90% peer-reviewed journal articles where the literature supports it**. Treat 75% as the current minimum, without weakening relevance or misclassifying sources to meet a cosmetic percentage.

## 2. Files created or updated

1. `Plan2.0/reference_audit/REFERENCE_QUALITY_SUMMARY.md` — inventory classification, denominator rules and journal-share formula.
2. `Plan2.0/reference_audit/RELATED_WORK_GAP_MATRIX.md` — topic-by-topic gaps in peripheral recovery, driver recovery, runtime verification, fault tolerance, association/diagnosis, bounded memory, evaluation and hardware evidence.
3. `Plan2.0/reference_audit/CHAT_04_JOURNAL_REFERENCE_CANDIDATES.md` — eight journal candidates/entries including existing P-005; author metadata for the IEEE Access survey was subsequently verified.
4. `Plan2.0/reference_audit/MANUSCRIPT_DRAFT_JOURNAL_SHARE_AUDIT.md` — classification of the uploaded 24-reference manuscript bibliography, ratios under both counting interpretations, replacement guidance, candidate list, and remaining requirements.
5. `Plan2.0/reference_audit/RECONSTRUCTED_MANUSCRIPT_REFERENCE_PLAN.md` — reference-by-reference purpose and citation placement, ratio calculation, and verification boundaries.
6. `Plan2.0/handoffs/CHAT_04_HANDOFF.md` — this handoff.

## 3. Reconstructed manuscript and reference decision

Created `Reconstructed_Manuscript_Journal_First.docx` as a new editable manuscript based on the supplied 12-page PDF. It preserves the study's stated model, methods, case matrix, outcomes, threats to validity, and evidence limitations; it does not claim to rerun experiments. It adds an explicit reference-purpose/citation-placement appendix so each source has a stated role. The reconstructed bibliography contains 20 references: 15 journal articles and five conference papers, for a strict journal share of **15/20 = 75%**. The original IEEE *Computer* magazine article was replaced with the ACM *Computing Surveys* journal survey by Natella, Cotroneo, and Madeira on software fault injection (DOI 10.1145/2841425). Five direct conference sources are retained because they are primary technical comparators. The ratio meets the user's stated minimum, not the earlier aspirational ~90% target.

## 4. Manuscript reference classification

**Journal articles (12 under broad classification):** [5], [6], [7], [10]–[15], [18]–[20]. Reference [12], “Fault Injection Techniques and Tools,” is published in IEEE *Computer* and is treated as a journal/magazine item in broad classification, but faculty rules may exclude magazines from a journal-article quota.

**Conference/proceedings papers (7):** [1]–[4], [8], [9], [16].

**Other source types (5):** [17] textbook; [21] software/framework documentation; [22]–[24] patent publications.

See `MANUSCRIPT_DRAFT_JOURNAL_SHARE_AUDIT.md` for full titles, source-type rationale and claim-preservation guidance.

## 5. Journal candidate shortlist

- **Already cited:** Reinbacher, Függer & Brauer (2014), *Formal Methods in System Design*, reference [7]/register P-005. Do not duplicate.
- **Runtime verification:** Heffernan, MacNamee & Fogarty (2014), *IET Software*, DOI 10.1049/iet-sen.2013.0236.
- **Embedded fault-tolerance survey:** Safari et al. (2022), *IEEE Access*, DOI 10.1109/ACCESS.2022.3144217. The nine-author list is verified in the candidate report.
- **Software transient-fault tolerance:** Asghari, Binesh Marvasti & Rahmani (2018), *Future Generation Computer Systems*, DOI 10.1016/j.future.2018.04.049.
- **Real-time fault-tolerance trade-offs:** Santos, Santos & Orozco (2009), *Journal of Systems Architecture*, DOI 10.1016/j.sysarc.2008.09.001.
- **Fault-tolerant real-time scheduling:** Moulik & Sharma (2024), *Future Generation Computer Systems*, DOI 10.1016/j.future.2024.07.008.
- **Self-adaptive networked embedded systems:** Streichert et al. (2006), *EURASIP Journal on Embedded Systems*, DOI 10.1155/ES/2006/42168.
- **Timing/reliability/energy trade-offs:** Alishzadeh, Jassbi & Reshadi (2023), *Microprocessors and Microsystems*, DOI 10.1016/j.micpro.2023.104929.

These remain candidates until full text is inspected and each citation is mapped to a precise manuscript claim. Adjacent scheduling/energy work must not be presented as direct evidence of peripheral-event quarantine.

## 6. Completed validation

- Read current live `main` metadata and relevant Plan2.0/reference audit files, the Chat 02 handoff and the Chat 03 handoff.
- Parsed the 43-row, 17-column reference register for the initial inventory audit.
- Inspected the manuscript PDF's reference list on pages 11–12 and counted its 24 numbered references.
- Checked publisher/metadata search results for the journal candidate set and verified the complete author list for Safari et al. (2022).
- Kept the manuscript bibliography denominator separate from the repository's 43-entry prior-art inventory.
- Committed the audit reports and handoff to `main`; no branch was created.
- No code, tests, Gates A–E, frozen K.10 artifacts, raw experimental outputs, or protected implementation files were modified.

## 7. Remaining boundary and next action

The **Chat-04 audit and reconstruction deliverables are complete**. The reconstructed DOCX has a 75% strict journal-article share (15/20), but submission readiness is not established: full-text claim-to-source verification, professor confirmation of venue counting rules, author details, final citation cross-check, and reconciliation of results against frozen artifacts remain required.

Before submission, the user should review the reconstructed editable DOCX and then:

1. Confirm the professor accepts the strict classification of the 20-reference bibliography and the 75% minimum.
2. Inspect full text of proposed journal candidates and map them to claims.
3. Replace/add only sources that support the paper; retain essential primary conference work where justified.
4. Update in-text citations and bibliography together, check unused/duplicate references, and renumber consistently.
5. Recalculate the final journal ratio from the unique final cited references and document the numerator/denominator.
6. Keep the paper's claims and evidence boundary intact: the current manuscript describes host/reference software evaluation, not physical MCU validation.

No claim is made that the final manuscript bibliography already complies, that all candidate articles have passed page-level claim verification, or that journal percentage establishes novelty, non-obviousness or patentability.
