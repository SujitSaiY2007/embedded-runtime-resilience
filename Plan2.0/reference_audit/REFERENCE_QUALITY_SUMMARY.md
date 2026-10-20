# Reference Quality Summary — Journal Share Audit

**Audit date:** 2026-10-20  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Branch:** `main` only  
**Input:** `Plan2.0/reference_audit/REFERENCE_REGISTER.csv` (43 data rows; 17 columns)  
**Related audits:** Chat 02 primary-source verification; Chat 03 source-to-design traceability, claim-evidence audit, and research-gap analysis.

## Executive finding

**The preliminary inventory is not yet aligned with the professor's journal-reference target.** The current register contains only **one entry explicitly classified as a journal article** (P-005, *Runtime verification of embedded real-time systems*). It also includes conference papers, patent records, technical documentation, a preprint/project family, and broad unresolved research strands. This inventory is a prior-art research register, not the final submitted bibliography; therefore, its journal percentage must not be presented as the final manuscript's ratio.

The earlier Plan 2.0 requirement is to aim for approximately **90% peer-reviewed journal articles where the literature supports it**, while retaining indispensable reputable conference papers and primary standards. For the professor's currently stated threshold, use **at least 75% journal articles as a minimum target**, and aim closer to 90% if relevance and source quality allow. Do not pad the bibliography with weakly relevant papers to meet a percentage.

## What the current register establishes

| Classification | Count | Interpretation |
|---|---:|---|
| Total inventory entries | 43 | 17 P-series and 26 A-series |
| Explicitly classified journal articles | 1 | P-005 |
| Explicitly classified academic/research-system conference papers | 7 | P-001–P-004, P-006, P-007, A-015 |
| Patent records/families | 9 core P-series entries | Prior-art documents, not journal articles |
| Broad unresolved research-topic/source-family leads | 17 A-series rows | Not individual publications; cannot be counted as manuscript citations |
| Other entries | Remaining entries | Framework documentation, research project/software families, or preprint material; not journal articles by default |
| Verified identity/metadata | 9 | Does not imply full-text review |
| Partially verified | 17 | Material source/metadata checks remain |
| Unresolved | 17 | Exact source identity or publication not sufficiently established |

The classifications above summarize the current register and Chat 02 status report. The broad source-family leads and non-academic documents make the 43-entry denominator unsuitable for a final bibliography journal-share calculation.

## Correct ratio rule

Calculate the percentage only from the **actual, unique sources cited in the manuscript's final reference list**, after duplicates are removed and each source's publication type is verified.

\[
\text{Journal share} = \frac{\text{unique journal articles cited}}{\text{all unique references cited in the manuscript}} \times 100\%
\]

Do not count patents, websites, software/framework manuals, standards, theses, preprints, or conference proceedings as journal articles. If the professor uses a different denominator or permits review articles/transactions under a particular category, document that rule before calculating.

### Practical examples

- 12 journal articles out of 16 final references = 75%.
- 15 journal articles out of 20 final references = 75%.
- 18 journal articles out of 20 final references = 90%.

These are target examples, not a claim about the current manuscript.

## Quality and integrity rules

1. Relevance and primary-source verification come before ratio optimization.
2. Prefer peer-reviewed journal research articles and strong review/survey articles directly relevant to embedded fault handling, real-time resilience, runtime verification, fault detection/recovery, bounded resource use, and empirical fault-injection evaluation.
3. Retain essential conference papers such as Phoenix/Karma or driver-recovery work where they are the primary/seminal source for a technical mechanism. Do not mislabel them as journals.
4. Keep patent records in the prior-art register; cite them in the manuscript only where the legal/technical discussion needs them. They do not count toward journal share.
5. Do not convert broad A-series leads into citations until exact title, authors, venue, year, DOI/official page and relevant passage are verified.
6. Do not imply that a source influenced the implementation merely because it is cited as related work.
7. No manuscript bibliography file was found among the repository's tracked paths matching common manuscript/bibliography filenames in this audit. Thus the actual submitted-reference list and its current journal ratio remain **unverified**. Locate the manuscript/source document before claiming the final ratio or editing its bibliography.

## Decision

**Add relevant journal articles before bibliography closure.** Use the candidate list in `Plan2.0/reference_audit/CHAT_04_JOURNAL_REFERENCE_CANDIDATES.md` as a vetted starting point, then select sources according to the actual manuscript claims. The candidate list is not automatically the final bibliography; each selected citation still needs precise claim-to-source and full-text/page traceability.
