# Chat 04 Handoff — Journal-First Reference Quality Audit

**Date:** 2026-10-20  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Branch policy:** `main` only  
**Starting head observed for this work:** `3c4310615b36f9e44295fcf25a639622dc219a31`  
**Status:** Journal-quality assessment and candidate shortlist committed. Final manuscript bibliography not edited because no tracked manuscript/bibliography file was identified in the live repository tree.

## 1. Main answer to professor's requirement

The current preliminary inventory is **not yet at the requested journal-share level**. The 43-row register explicitly classifies only one entry as a journal article (P-005). It includes conference papers, patent records, documentation, a preprint/project family and unresolved source leads. These 43 entries are a prior-art inventory, not the final bibliography; therefore the final manuscript's journal ratio remains unknown until the actual cited reference list is located.

Plan 2.0's existing protocol sets an approximate **90% peer-reviewed journal-article target where the literature supports it**. The user's current stated minimum is **75% or above**. Chat 04 recommends treating 75% as the minimum and aiming nearer 90% if relevance and primary-source evidence permit. Do not add weak sources or misclassify conference papers to meet a cosmetic ratio.

## 2. Files created

1. `Plan2.0/reference_audit/REFERENCE_QUALITY_SUMMARY.md` — current inventory type/status counts, denominator rules, journal-share formula, integrity constraints and decision.
2. `Plan2.0/reference_audit/RELATED_WORK_GAP_MATRIX.md` — theme-by-theme gap matrix for peripheral recovery, driver recovery, runtime verification, fault tolerance, fault association, event quarantine, bounded memory, evaluation and hardware evidence.
3. `Plan2.0/reference_audit/CHAT_04_JOURNAL_REFERENCE_CANDIDATES.md` — eight journal candidates/entries (including existing P-005, which must not be duplicated) with publisher links, relevance and limitations.
4. `Plan2.0/handoffs/CHAT_04_HANDOFF.md` — this handoff.

## 3. Journal candidate shortlist

- **Already registered:** Reinbacher, Függer & Brauer (2014), *Formal Methods in System Design*, P-005.
- **Runtime verification:** Heffernan, MacNamee & Fogarty (2014), *IET Software*, DOI 10.1049/iet-sen.2013.0236.
- **Survey:** *A Survey of Fault-Tolerance Techniques for Embedded Systems From the Perspective of Power, Energy, and Thermal Issues*, *IEEE Access* 10 (2022), pp. 12229–12251, DOI 10.1109/ACCESS.2022.3144217. Full author list still needs to be extracted before final formatted citation.
- **Software transient-fault tolerance:** Asghari, Binesh Marvasti & Rahmani (2018), *Future Generation Computer Systems* 87, pp. 58–65, DOI 10.1016/j.future.2018.04.049.
- **Real-time fault-tolerance trade-offs:** Santos, Santos & Orozco (2009), *Journal of Systems Architecture* 55(2), pp. 90–101, DOI 10.1016/j.sysarc.2008.09.001.
- **Fault-tolerant real-time scheduling:** Moulik & Sharma (2024), *Future Generation Computer Systems* 161, pp. 214–225, DOI 10.1016/j.future.2024.07.008.
- **Self-adaptive networked embedded systems:** Streichert, Koch, Haubelt & Teich (2006), *EURASIP Journal on Embedded Systems*, article 042168, DOI 10.1155/ES/2006/42168.
- **Timing/reliability/energy trade-offs:** Alishzadeh, Jassbi & Reshadi (2023), *Microprocessors and Microsystems* 102, article 104929, DOI 10.1016/j.micpro.2023.104929.

The candidate report explicitly marks the sources as candidates rather than automatically accepted manuscript citations. Full text/page-level claim mapping remains necessary, and the candidates do not disclose the project's complete integrated mechanism merely because their topics overlap.

## 4. Validation and limitations

- Read current live `main` metadata and fetched `Plan2.0/REFERENCE_OVERHAUL.md`, `Plan2.0/README.md`, `research/references_used/README.md`, `research/references_used/REFERENCE_REGISTER.md`, `research/references_used/COUNTING_AND_VERIFICATION.md`, `Plan2.0/reference_audit/REFERENCE_REGISTER.csv`, Chat 02 handoff/report and Chat 03 handoff.
- Parsed the 43-row CSV with its 17-column schema and counted publication-type/status labels.
- Checked publisher/official landing pages for journal candidates including Springer, Wiley/IET, IEEE and Elsevier pages. Exact author list for the IEEE Access survey remains an open bibliographic task in the candidate report.
- Inspected the live recursive Git tree (217 tracked paths); no path matching common manuscript/bibliography names or extensions was found. This means no tracked manuscript was located in that tree, not that no manuscript exists outside the repository.
- No manuscript bibliography or reference list was edited; no code, tests, Gates A–E, frozen K.10 artifacts or existing source register was changed.
- No runtime tests, experiment runs, raw CSV recomputation or hardware tests were performed.

## 5. Next required work

1. **Locate the actual manuscript and its bibliography.** If it is outside the repository, obtain the exact current file/version from the user rather than inventing a manuscript path.
2. Extract the unique cited references from that manuscript and classify each by publication type; then calculate the actual journal share.
3. Verify candidate metadata and full-text relevance. Retrieve the full IEEE Access survey author list; inspect the full text and exact sections/pages for every selected candidate.
4. Add only selected, verified journal articles to the manuscript and bibliography. Retain indispensable reputable conference papers as conference papers.
5. Update the canonical source register and claim/source traceability together, using stable IDs and exact DOI/official links. Preserve existing 43-row historical counts as historical counts rather than silently rewriting them.
6. Recalculate the final journal ratio from the final unique citations and report numerator, denominator, excluded source types and duplicate handling.
7. Keep prior-art conclusions bounded; a journal-heavy bibliography does not establish novelty, non-obviousness or patentability.

## 6. Integrity boundary

This handoff closes the **initial journal-quality assessment and candidate discovery** portion only. It does not claim the final bibliography meets 75% or 90%, because the manuscript's actual cited reference list was not found in the repository and candidate selection/full-text mapping is incomplete.
