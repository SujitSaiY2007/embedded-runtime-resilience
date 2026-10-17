# Reference Overhaul Protocol

## Objective

Replace an unverified or weakly supported preliminary bibliography with a rigorous, relevant, source-verified literature base suitable for a journal manuscript. Aim for approximately 90% peer-reviewed journal articles if the topic and available literature support it; do not force the ratio by excluding indispensable, reputable systems conferences or primary standards. Relevance, venue credibility, methodological fit, and verifiability take precedence over a cosmetic percentage.

## Required audit fields

For each preliminary reference, record:
- Stable ID and original bibliography entry.
- Verified title, authors, year, venue, volume/issue/pages or article number.
- DOI and publisher/official landing page where available.
- Publication type: journal, peer-reviewed conference, standard, book/chapter, preprint, patent, website, thesis, or other.
- Venue/publisher reputation evidence and peer-review/indexing status where verifiable.
- Topic relevance: fault detection, embedded/real-time resilience, recovery, event queues, quarantine/isolation, bounded memory, MPU/security, fault injection, empirical validation, or adjacent.
- Evidence strength and limitations.
- Project relationship: direct source, adapted mechanism, conceptual context, baseline/comparator, conflicting prior art, or not yet mapped.
- Exact design choice/claim supported and the project file/section.
- Action: retain, replace, supplement, or exclude—with reason.
- Verification status and date.

## Source hierarchy

Prefer primary publisher pages, DOI records, IEEE Xplore, ACM Digital Library, SpringerLink, Elsevier/ScienceDirect, Wiley, reputable primary systems proceedings, and official standards bodies. Use scholarly search engines for discovery only; confirm metadata against a primary record. Never invent DOI data or call a source peer-reviewed without evidence.

## Journal share

Report the actual percentage with numerator, denominator, and explicit inclusion rules. Do not count standards, patents, preprints, or websites as journal papers.

## Traceability categories

1. **Directly adopted:** an explicit algorithm, model, or method is implemented from the source; identify exactly what was adopted.
2. **Adapted:** a source idea was materially changed; explain original and adapted parts.
3. **Conceptually informed:** the source shaped problem framing but no method is directly implemented.
4. **Comparative prior art:** the source is used to compare or challenge the proposal.
5. **No demonstrated influence:** do not imply the project was inspired by this source; retain only if context warrants.

## Required outputs

- `Plan2.0/reference_audit/REFERENCE_REGISTER.csv` or equivalent table.
- `Plan2.0/reference_audit/REFERENCE_TO_DESIGN_TRACEABILITY.md`.
- `Plan2.0/reference_audit/RELATED_WORK_GAP_MATRIX.md`.
- `Plan2.0/reference_audit/REFERENCE_QUALITY_SUMMARY.md`.
- Updated manuscript bibliography only after audit and verification.

## Integrity constraints

P0–P3 are comparison policies/ablations, not automatically reproductions of specific published systems. Map a baseline to a source only where a real, documented implementation relationship exists. Do not describe P4 as novel merely because one search did not find the full combination. Novelty conclusions remain provisional pending deeper review.
