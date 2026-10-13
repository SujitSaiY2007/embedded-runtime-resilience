# Counting and Verification Notes

**Updated:** 2026-10-13  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Canonical register:** [REFERENCE_REGISTER.md](REFERENCE_REGISTER.md)

## Final inventory from this recovery pass

| Classification | Count | Meaning |
|---|---:|---|
| Primary verified source records | **17** | Source identity and core bibliographic/patent metadata matched to a stable publisher, institutional, proceedings, official documentation or patent-record page. |
| Additional unresolved leads | **26** | Historical candidate sources/topics that remain insufficiently identified or need exact source/version/claim verification. |
| Total inventory entries | **43** | Primary records plus additional leads, with patent families and known publication/grant duplicates grouped to avoid double counting. |

The 17 primary records comprise 7 academic/research-system papers, 1 official framework-documentation source, and 9 patent source records/families. The additional 26 are not verified papers. Some are concrete candidates; others are search topics that still need a specific paper, standard clause, source-code revision or manual.

## What “verified” means here

“Primary verified” means the source can be identified unambiguously and its core metadata was checked against the linked source record. It does **not** mean that every source was read cover-to-cover in this pass, that every claim was reviewed, that every source is appropriate for the final paper, or that the whole month’s reading history has been recovered.

Keep three separate counts in any later report:
1. **Identified source records** — sources with reliable identity and metadata.
2. **Full-text/claims inspected** — sources for which the actual paper, patent claims or technical sections were read and relevant passages recorded.
3. **Cited in the manuscript** — only sources actually cited and tied to a specific claim in the final manuscript.

These are different numbers and must never be merged into a single “papers read” count.

## Corrections and deduplication applied

- US 2018/0365126 A1 and US 10,838,845 B2 are the same IBM patent family and count once.
- US 2018/0267859 A1 and US 10,331,522 B2 are the publication/grant forms of one event-failure-management family and count once.
- US 12,688,084 is “Intelligent data flow control valve” and concerns an integration-layer failed-event queue. It was not promoted under the older shorthand that described it as a peripheral/embedded recovery source.
- The old identifier/title for “Fault recovery of peripheral I/O lines” (US 2026/0228076 as written in the historical notes) remains unresolved and is not in the primary count.
- The two 2026 Dell peripheral-management publications have separate application/publication records and are retained separately for technical comparison; their legal family/claim relationship is not adjudicated here.

## What remains unresolved

The full-month total of sources encountered, the exact number read in full, and the number cited in any manuscript cannot be reconstructed with certainty from the currently preserved repository. Historical Phase 0 search-result markers are not stable bibliographic records. The 26 additional leads are retained in the overall inventory, but are not promoted into the primary count until identified and checked.

This is a completed, evidence-bounded inventory pass, not a claim of an exhaustive global prior-art search. It does not establish novelty, inventive step, patentability or freedom to operate.

## Future update rule

When a lead is resolved:
1. Open and verify the primary source record.
2. Capture exact title, authors/inventors, venue or patent publication/grant, date, DOI/URL and version.
3. Check for duplicates and patent-family relationships.
4. Move it from the additional list into the primary verified list only after those checks.
5. Record whether full text/claims were actually inspected and the exact section/page supporting the research comparison.
6. Update both the primary, additional and total counts in this file and the register.
