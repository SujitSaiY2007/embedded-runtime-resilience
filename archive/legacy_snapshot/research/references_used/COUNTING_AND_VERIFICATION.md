# Counting and Contribution Notes

**Updated:** 2026-10-13  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Canonical register:** [REFERENCE_REGISTER.md](REFERENCE_REGISTER.md)

## Final inventory

| Classification | Count | Meaning |
|---|---:|---|
| Primary verified source records | **17** | Source identity and core metadata matched to stable publisher, institutional, proceedings, official documentation or patent-record pages. |
| Additional references used in the broader review | **26** | Additional source candidates, technical-source families and research strands whose contribution to the project's prior-art comparison is recorded in the register. |
| **Total inventory entries** | **43** | Primary records plus additional references/research strands, with known patent publication/grant duplicates grouped to avoid double counting. |

The 17 primary records comprise 7 academic/research-system papers, 1 official framework-documentation source, and 9 patent source records/families. The 26 additional entries cover runtime monitoring, watchdogs, micro-recovery, embedded persistence, interrupt overload, adaptive sensing, bus recovery, RTOS mechanisms, driver recovery, safety frameworks and related patent/source comparisons. They are included in the total inventory and each has its contribution documented in the register.

## How to report the counts accurately

Keep these measures distinct:
1. **Primary verified source records:** 17.
2. **Additional references/research strands recorded:** 26.
3. **Overall inventory entries:** 43.
4. **Full-text/claims inspected:** record only when supported by a specific checkpoint or source-inspection note.
5. **Sources cited in the final manuscript:** count only the sources actually cited in the submitted manuscript.

The first three numbers are the current inventory. The repository does not support a definitive month-long count of all full-text reads or final manuscript citations. Some additional entries are broad research strands or source families, rather than individual academic papers; their documented contribution should be used for research continuity, while final manuscript citations should point to exact source records.

## Deduplication and attribution decisions

- US 2018/0365126 A1 and US 10,838,845 B2 are the same IBM patent family and count once.
- US 2018/0267859 A1 and US 10,331,522 B2 are the publication/grant forms of one event-failure-management family and count once.
- US 12,688,084 is “Intelligent data flow control valve” and contributes an integration-layer failed-event-queue comparison, not a peripheral-specific embedded recovery reference.
- The historical identifier/title “Fault recovery of peripheral I/O lines” (US 2026/0228076 as recorded) is retained as an additional patent-search contribution and is not represented as a verified patent record.
- The two 2026 Dell peripheral-management publications have separate application/publication records and are retained separately for technical comparison; their legal family/claim relationship is not adjudicated here.

## Research-integrity boundary

The inventory records the sources and research strands that contributed to the prior-art investigation. It does not claim that every entry was read cover-to-cover, that every entry is an academic paper, or that all 43 are appropriate citations for the final manuscript. A source's presence does not establish anticipation, novelty, inventive step, patentability or freedom to operate.

## Maintenance rule

When a source strand is converted into a manuscript citation, capture the exact title, authors/inventors, venue or patent publication/grant, date, DOI/URL and version; identify the claim it supports; record the specific pages/claims inspected; and check duplicates and patent-family relationships. Keep the additional-reference contribution record intact so the research history remains auditable.
