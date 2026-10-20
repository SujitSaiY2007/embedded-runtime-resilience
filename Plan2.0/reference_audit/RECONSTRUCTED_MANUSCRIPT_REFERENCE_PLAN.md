# Reconstructed Manuscript — Reference Selection and Citation Audit

**Date:** 2026-10-20  
**Source manuscript:** user-supplied `Manuscript Draft.pdf` (12 pages)  
**Editable deliverable:** `Reconstructed_Manuscript_Journal_First.docx` created in the conversation; it is not committed as a binary repository artifact.  
**Repository branch policy:** `main` only.

## Decision

The draft was reconstructed as an editable manuscript with a curated **20-reference bibliography**. The selection preserves four essential direct conference sources for peripheral recovery and driver/component recovery, while using journal papers for dependability, embedded fault-tolerance, runtime verification, diagnosis, rejuvenation, fault injection, and adjacent recovery trade-offs.

### Journal share

| Counting rule | Journal articles | Total | Share |
|---|---:|---:|---:|
| Strict: exclude IEEE *Computer* magazine article [14] | 15 | 20 | 75% |
| Broad: count [14] as journal/magazine | 16 | 20 | 80% |

The strict ratio meets the stated 75% minimum, provided the professor accepts the listed journal venues under their rules. It does not reach the earlier aspirational ~90% target. The four conference papers are retained because they are direct primary sources for the narrowest technical comparators, not because conference papers are being treated as journals.

## Why references are included

| Ref. | Source / purpose | Placement |
|---|---|---|
| [1] Smith & Rixner, Phoenix | Direct peripheral checkpoint recovery and external peripheral state | Introduction; §2.1 |
| [2] Branco et al., KARMA | Intermittent asynchronous peripheral operations and consistency | Introduction; §2.1 |
| [3] Swift et al., shadow drivers | Driver-level recovery boundary | Introduction; §2.2 |
| [4] Candea et al., microreboots | Component restart/recovery boundary | Introduction; §2.2 |
| [5] Avizienis et al. | Dependability terminology and fault/error/failure distinction | §2.3 |
| [6] Reinbacher et al. | Embedded real-time runtime verification | Introduction; §2.3 |
| [7] Safari et al. | Embedded fault-tolerance survey: power, energy, thermal constraints | §2.3 |
| [8] Solouki et al. | Recent survey of embedded dependability and software mitigation | §2.3 |
| [9] Gao et al., Part I | Model-based and signal-based fault diagnosis | §2.3 |
| [10] Gao et al., Part II | Knowledge-based and hybrid/active fault diagnosis | §2.3 |
| [11] Taleb et al. | Uncertainty in runtime verification | §2.3 |
| [12] Vaidyanathan & Trivedi | Software rejuvenation and restart decisions | §2.4 |
| [13] Regehr & Duongsaa | Interrupt overload; direct mechanism-specific conference source | §2.4 |
| [14] Hsueh et al. | Fault-injection techniques; *Computer* magazine article, excluded from strict journal count | §2.4 |
| [15] Arlat et al. | Journal treatment of fault injection and dependability evaluation | §2.4 |
| [16] Asghari et al. | Task-level redundancy and transient fault tolerance; adjacent comparison only | §2.3 |
| [17] Wu et al. | Software transient-fault tolerance for embedded systems | §2.3 |
| [18] Heffernan et al. | Automotive embedded runtime monitoring of safety properties | §2.3 |
| [19] Streichert et al. | Fault-tolerant/self-adaptive networked embedded architecture; adjacent context | §2.3 |
| [20] Santos et al. | Fault-tolerance, power-saving, and real-time trade-offs; not direct peripheral-recovery evidence | §2.3 |

## Citation-integrity rules

- A citation is included to support a stated background/comparison point, not to imply that the cited source implements the complete integrated P4 policy.
- Four conference sources [1]–[4] are retained as primary comparators; [13] is another conference source used for interrupt-overload context. Accordingly, the strict denominator is 20 and the strict journal numerator is 15 (15/20 = 75%). **Correction to the table above:** because [13] is also a conference paper, the non-journal total is five conference papers plus the magazine item [14]; the strict count remains 15/20.
- No book, patent, or software documentation is included in the 20-item bibliography. Patents and documentation can remain in the broader prior-art/source register when relevant, but are not necessary to support the current manuscript's central experimental claims.
- The new citations [14], [16]–[20] are included in the in-text related-work discussion and mapped in Appendix A of the editable draft.
- The manuscript results were transcribed from the supplied PDF. This reconstruction did not rerun experiments or independently verify the frozen outcome table.
- The additional journal sources were selected using bibliographic/publisher metadata and topical fit. Full-text, page-level claim verification is still required before journal submission. Do not imply that every candidate has already passed detailed full-text review.

## Evidence boundary

The manuscript remains a host/reference software evaluation. It does not establish physical MCU deployment, target RAM/Flash, real timing, energy, or electrical recovery. The ratio calculation concerns the reconstructed 20-item bibliography, not the 43-row Plan2.0 prior-art inventory.
