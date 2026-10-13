# Reference Register — Embedded Runtime Resilience

**Updated:** 2026-10-13  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Purpose:** Auditable inventory of prior-art sources identified during the project. This register distinguishes references whose bibliographic identity was verified from additional leads that remain unresolved.

## Counting rule

- **Primary verified register:** A source has a stable source page/identifier and enough bibliographic or patent metadata to identify it unambiguously. “Verified” here means identity/metadata verified against the linked publisher, proceedings, institutional, official project, or patent-record page. It does **not** mean the full text or every claim has been independently audited.
- **Additional / unresolved:** The historical project records name a topic or candidate, but this pass did not recover enough reliable primary-source metadata to promote it to the primary count. These items are still counted in the overall inventory, but never represented as verified references.
- **Not counted twice:** Related patent publication/grant numbers in the same family are grouped under one family/source record where appropriate. A research area is not a paper. A repository/project homepage is not interchangeable with a peer-reviewed paper.
- The inventory is reconstructed from the repository's preserved notes plus source-level checks recorded below. It is not a claim that every item was read in full or cited in the manuscript.

## Part I — Primary verified source records (17)

### Academic papers and research systems

| ID | Bibliographic record | Stable source | Relevance to this project | Verification boundary |
|---|---|---|---|---|
| P-001 | Rebecca Smith and Scott Rixner. “Surviving Peripheral Failures in Embedded Systems.” *2015 USENIX Annual Technical Conference (USENIX ATC ’15)*, 2015, pp. 125–137. | [USENIX proceedings record and paper](https://www.usenix.org/conference/atc15/technical-session/presentation/smith) | Phoenix: embedded peripheral failure handling, checkpointing and recovery. | Proceedings metadata verified. Project K.10.3 records primary-paper inspection; recheck exact page/claim citations before manuscript use. |
| P-002 | Adriano Branco, Luca Mottola, Muhammad Hamad Alizai, and Junaid Haroon Siddiqui. “Intermittent Asynchronous Peripheral Operations.” *Proceedings of the 17th ACM Conference on Embedded Networked Sensor Systems (SenSys ’19)*, 2019. | [Paper PDF](https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf) | Karma: peripheral roll-forward combined with computation rollback at a rendezvous point. | PDF front matter confirms authors, title, venue and year. Exact proceedings DOI/pages should be added if required by the final citation style. |
| P-003 | Michael M. Swift, Muthukaruppan Annamalai, Brian N. Bershad, and Henry M. Levy. “Recovering Device Drivers.” *6th Symposium on Operating Systems Design and Implementation (OSDI ’04)*, 2004. | [USENIX proceedings record and paper](https://www.usenix.org/conference/osdi-04/recovering-device-drivers) | Driver fault containment and recovery using shadow drivers. | Official proceedings metadata verified. This is OS-level work, not a bare-metal MCU implementation. |
| P-004 | George Candea, Shinichi Kawamoto, Yuichi Fujiki, Greg Friedman, and Armando Fox. “Microreboot—A Technique for Cheap Recovery.” *OSDI ’04*, 2004, pp. 31–44. | [USENIX proceedings record and paper](https://www.usenix.org/conference/osdi-04/microreboot%E2%80%94-technique-cheap-recovery) | Fine-grained recovery of a faulty component while preserving other application activity. | Official proceedings metadata verified; system domain differs from resource-constrained MCU firmware. |
| P-005 | Thomas Reinbacher, Matthias Függer, and Jörg Brauer. “Runtime verification of embedded real-time systems.” *Formal Methods in System Design*, 44, 203–239 (2014). DOI: 10.1007/s10703-013-0199-z. | [Publisher record](https://link.springer.com/article/10.1007/s10703-013-0199-z) · [Open full text](https://pmc.ncbi.nlm.nih.gov/articles/PMC4699739/) | Resource-bounded online monitoring of past-time metric temporal logic. | Metadata, DOI and open full-text landing page verified. Runtime monitoring is adjacent evidence, not itself peripheral recovery policy. |
| P-006 | Brian Kempa, Pei Zhang, Phillip H. Jones, Joseph Zambreno, and Kristin Y. Rozier. “Embedding Online Runtime Verification for Fault Disambiguation on Robonaut2.” *Proceedings of FORMATS*, 2020. | [Institutional publication record and paper](https://rcl.ece.iastate.edu/publications/KemZha20A) | Resource-constrained fault disambiguation and mitigation triggering on a deployed robotic system. | Institutional metadata and paper attachment verified. Exact proceedings volume/pages/DOI can be added from the final proceedings record. |
| P-007 | John Regehr and Usit Duongsaa. “Preventing Interrupt Overload.” *Proceedings of the 2005 ACM SIGPLAN/SIGBED Conference on Languages, Compilers, and Tools for Embedded Systems (LCTES ’05)*, 2005, pp. 50–58. DOI: 10.1145/1070891.1065918. | [Bibliographic record](https://www.researchgate.net/publication/221655205_Preventing_interrupt_overload) | Interrupt-overload prevention in embedded systems. | Title, authors, venue, year, pages and DOI cross-identified in indexed bibliographic metadata. Prefer an ACM proceedings landing page for final formal citation. |

### Framework / technical documentation

| ID | Source | Stable source | Relevance | Verification boundary |
|---|---|---|---|---|
| P-008 | Quantum Leaps QP/C — QMPool Class Reference. | [Official QP/C QMPool documentation](https://www.state-machine.com/qpc/struct_q_m_pool.html) | Fixed-size memory pool, caller-provided storage, allocation and recycling semantics. | Official documentation page verified. This documents a pool with allocation/recycling; do not describe it as proof of the project's same-slot quarantine design. |

### Patent documents and families

Patent records are included as **patent prior-art documents**, not academic papers. Patent status labels on aggregators are not legal opinions. Claims, priority dates, prosecution history and family scope should be reviewed before any legal conclusion.

| ID | Verified patent record | Stable source | Relevance to the investigation | Counting note |
|---|---|---|---|---|
| P-009 | US 9,547,557 B2, “Peripheral bus error containment and recovery.” | [Patent record](https://patents.google.com/patent/US9547557B2/en) | Peripheral-bus error containment and recovery by bus-controller actions. | One patent family/source record. |
| P-010 | US 9,411,667 B2, “Recovery after input/output error-containment events.” | [Patent record](https://patents.google.com/patent/US9411667B2/en) | I/O error-containment event reporting and link recovery. | One patent family/source record. |
| P-011 | US 9,218,247 B2, “Multimaster serial single-ended system fault recovery.” | [Patent record](https://patents.google.com/patent/US9218247B2/en) | Serial/I²C-style bus and connected-device recovery, including line signaling and register verification. | Promoted from earlier lead after locating a record with matching title and identifier. |
| P-012 | US 10,921,871 B2, “BAS/HVAC control device automatic failure recovery.” | [Patent record](https://patents.google.com/patent/US10921871B2/en) | Automated fault/restart recovery for building-automation control devices. | One patent family/source record. |
| P-013 | US 10,331,522 B2, “Event failure management” (published as US 2018/0267859 A1). | [Patent publication record](https://patents.google.com/patent/US20180267859A1/en) | Failed-event management in distributed processing systems. | Related to the IBM failed-event line; counted as its own family only where the record establishes a distinct priority/application family. |
| P-014 | US 10,838,845 B2, “Processing failed events on an application server” (published as US 2018/0365126 A1). | [Patent record](https://patents.google.com/patent/US10838845B2/en) | Failed-event queue, failure reasons and replay/reprocessing. | Grant and A1 publication are the same family and count once. |
| P-015 | US 2025/0068503 A1, “Circuit for status monitoring, and fault recovery and isolation for inter-integrated circuit (I2C) bus, and method implemented by the same.” | [Patent publication record](https://patents.google.com/patent/US20250068503A1/en) | I²C status monitoring, fault recovery and isolation. | Exact title, identifier, inventor names and publication metadata verified on the patent record. |
| P-016 | US 2026/0030091 A1, “Data processing system peripheral device management and recovery.” | [Patent publication record](https://patents.google.com/patent/US20260030091A1/en) | Independent management controller identifies and restarts a faulty peripheral without restarting the whole system. | Exact title and publication identifier verified. |
| P-017 | US 2026/0030180 A1, “Management and recovery of data processing system peripheral devices.” | [Patent publication record](https://patents.google.com/patent/US20260030180A1/en) | Management-controller recovery actions intended to avoid disruption to unrelated operations. | Exact title, publication identifier and publication date verified. |

### Primary-count summary

- **17 primary verified source records**: 7 academic papers/research-system papers, 1 official framework-documentation source, and 9 patent source records/families.
- “Primary verified” means the source's identity and core metadata were verified. It does not mean all 17 were read cover-to-cover during this pass, that all are equally relevant, or that all belong in the final manuscript bibliography.
- Some patent families may contain multiple A1/B1/B2 publications. Count a family once in the source inventory unless the analysis specifically needs to compare distinct documents/claims.
- The 17 records above are not all equivalent to peer-reviewed journal/conference papers; patent records and framework documentation are explicitly separated.

## Part II — Additional unresolved leads (26)

These are included in the **overall inventory total** but excluded from the primary verified count until the exact source identity and bibliographic details are recovered. They came from the historical Phase 0 map, topic-freeze report, novelty reports and older register. A lead may later be promoted, merged into another record, or removed if it proves duplicate/incorrect.

| ID | Lead / historical label | Why it was retained | What remains unresolved |
|---|---|---|---|
| A-001 | RTLola runtime-monitoring language/system | Runtime monitoring and stream-based specification. | Recover the exact primary paper(s), authors, venue, year and DOI; distinguish project page from paper. |
| A-002 | Past-time temporal monitoring and runtime-contract checking | Established runtime property/contract monitoring. | No single canonical source identified; select specific papers rather than citing the topic. |
| A-003 | Windowed/hierarchical watchdogs and trusted recovery | Established liveness detection and recovery patterns. | Identify exact paper, standard or vendor source. |
| A-004 | Micro-recovery and recovery-conscious scheduling beyond the verified Microreboot paper | Related component recovery and scheduling. | Recover exact works and check overlap with P-004. |
| A-005 | Texas Instruments CTPL utilities | Embedded persistent-state restoration. | Exact manual title, revision, publication date and document number. |
| A-006 | Texas Instruments NVS utilities | Non-volatile storage and state restoration. | Exact device-family documentation and version. |
| A-007 | Event-driven workload scaling / interrupt-overload studies | Queue pressure and overload control. | Exact papers beyond P-007 not recovered. |
| A-008 | FSM-based adaptive sampling | Adjacent adaptive embedded behavior. | Exact paper and bibliographic metadata. |
| A-009 | ML-based adaptive sensing/scheduling | Adjacent resource-aware embedded scheduling. | Exact paper and bibliographic metadata. |
| A-010 | Automatic CAN bus-off recovery | Protocol-specific recovery behavior. | Exact ISO/CAN specification edition, vendor manuals and/or paper. |
| A-011 | AUTOSAR fault/event/driver mechanisms | Automotive software recovery context. | Exact standard release, document section and clause. |
| A-012 | Zephyr driver/device recovery mechanisms | Open-source RTOS comparison target. | Exact release/commit, source files and behavior audit. |
| A-013 | FreeRTOS fault/event/driver mechanisms | RTOS comparison target. | Exact release, documentation pages or source files and behavior audit. |
| A-014 | NuttX fault/event/driver mechanisms | RTOS comparison target. | Exact release/commit, source files and behavior audit. |
| A-015 | Herder et al., “Failure Resilience for Device Drivers” | MINIX 3/driver recovery lead. | Exact title, authors, publication and primary source not confirmed in this pass. |
| A-016 | “Falkirk Wheel” work, arXiv:1503.08877 | Referenced in old notes for selective rollback/logical-time recovery. | Recheck the arXiv record's exact title/authors and whether the cited mechanism actually supports the historical claim. |
| A-017 | Ahn et al., “Fault-Tolerant Service Robots” (2013 as recorded) | Robot fault tolerance/dependency handling. | Confirm exact authors, chapter/article type, publication and DOI metadata. |
| A-018 | US 2026/0228076, “Fault recovery of peripheral I/O lines” (identifier/title as recorded in historical notes) | Peripheral I/O-line fault monitoring/recovery. | Identifier/date/title mismatch risk; no promotion until an authoritative matching record is located. |
| A-019 | 2015 interrupt-overload comparison study | Historical note described a study comparing overload-prevention mechanisms. | Exact paper not identified; do not cite as a source. |
| A-020 | 2017 IEEE MECO execution-time-monitoring paper | Historical note described execution-time monitoring for embedded error detection. | Exact title/authors/pages/DOI not identified. |
| A-021 | NXP S32 Safety Software Framework | Industrial safety and restart/recovery mechanisms. | Exact versioned manual, document number and applicable sections. |
| A-022 | R2U2 project homepage and general project documentation | Runtime verification in resource-constrained systems. | The general homepage is not a substitute for a versioned paper or documentation snapshot; use P-006 for the verified Robonaut2 paper. |
| A-023 | Quantum Leaps QP/C QF framework documentation | Event framework, queueing and event lifecycle semantics. | A separate exact versioned page and the specific claims used in K.10.3 need to be attached; P-008 only verifies the QMPool page. |
| A-024 | microfsm embedded state-machine framework | Static/caller-owned state and no-heap implementation lead. | Pin a commit and inspect code/license/version before citing. |
| A-025 | Nooks / MINIX 3 / other OS driver recovery literature beyond P-003 | Driver isolation and recovery context. | Recover exact sources and prevent duplication with P-003 or P-015-style patent families. |
| A-026 | Safety-critical/aerospace/historical embedded recovery systems | Broader adjacent prior-art search area. | This is a search domain, not a citation; identify concrete sources before use. |

## Part III — Historical records that must not be silently promoted

1. The old Phase 0 research-space map contains inline search-result markers that are not durable bibliographic records. Those markers were not treated as citations by themselves.
2. The historical note “US 12,688,084 — Intelligent data flow control valve” was checked and found to concern an integration-layer failed-event queue. It is **not** the same as the earlier shorthand “paused-event retention” description. It must not be cited under that shorthand; add it only as a separate, accurately described patent-family record if the integration-layer comparison is retained.
3. US 2018/0365126 A1 and US 10,838,845 B2 are publication/grant documents from the same patent family and count once as P-014, not twice.
4. US 2018/0267859 A1 and US 10,331,522 B2 are the publication/grant forms of the event-failure-management family and count once as P-013.
5. The two 2026 Dell peripheral-management publications P-016 and P-017 have different application/publication records and are retained as separate patent records for comparison. Their legal relationship and claims must be checked before asserting independent inventions.
6. No source is deemed to have been read in full solely because its title or URL appeared in a prior project note.

## Overall count

**17 primary verified source records + 26 additional unresolved leads = 43 inventory entries.**

This is an inventory count, not 43 verified papers, not 43 full-text reads, and not the final manuscript bibliography. Of the 43 entries, 17 have verified source identity/metadata and 26 remain additional leads. The number of full-text sources inspected across the entire project month is **not reconstructable with certainty** from the preserved repository alone. The primary count can increase only after an unresolved lead is matched to a reliable source record and checked for duplication.

## Pre-submission controls

- [ ] For every manuscript citation, record the exact claim it supports and the source page/section/page number.
- [ ] Separate full-text review, abstract/metadata review and title-only leads.
- [ ] Verify all patent priority dates, claims and family relationships against authoritative records before legal comparison.
- [ ] Deduplicate publication/grant pairs and repeated search leads.
- [ ] Do not describe the 26 additional leads as verified sources.
- [ ] Do not interpret “not found in this inventory” as proof that no prior art exists.
