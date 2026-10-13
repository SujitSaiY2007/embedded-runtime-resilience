# Reference Register — Embedded Runtime Resilience

**Updated:** 2026-10-13  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Purpose:** Auditable inventory of prior-art sources identified during the project. This register distinguishes references whose bibliographic identity was verified from additional leads that are retained as additional entries.

## Counting rule

- **Primary verified register:** A source has a stable source page/identifier and enough bibliographic or patent metadata to identify it unambiguously. “Verified” here means identity/metadata verified against the linked publisher, proceedings, institutional, official project, or patent-record page. It does **not** mean the full text or every claim has been independently audited.
- **Additional / additional-source:** The historical project records name a topic or candidate, but this pass did not recover enough reliable primary-source metadata to promote it to the primary count. These items are still counted in the overall inventory, but never represented as verified references.
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

## Part II — Additional references used in the broader prior-art review (26)

The following references, technical-source families and research strands were used to broaden the comparison beyond the primary register. Their contribution is recorded here so that their role in the research is visible. Some entries are research areas or source families rather than a single manuscript-ready citation; where a specific publication, release or clause is not named, use the entry as a record of the review direction and do not invent bibliographic details.

| ID | Additional reference / research strand | Contribution to the project's prior-art review |
|---|---|---|
| A-001 | RTLola runtime-monitoring language/system | Provided the stream-based runtime-monitoring comparison: monitoring specifications and verdict generation are established techniques, so monitoring alone is not the claimed contribution. |
| A-002 | Past-time temporal monitoring and runtime-contract checking | Established the surrounding design space for checking temporal properties and runtime contracts; informed the distinction between detecting a violation and safely executing peripheral recovery. |
| A-003 | Windowed/hierarchical watchdogs and trusted recovery | Contributed the watchdog/liveness baseline: missed deadlines or lack of progress can trigger recovery, but this is distinct from evidence-qualified event association and same-slot quarantine. |
| A-004 | Micro-recovery and recovery-conscious scheduling beyond the verified Microreboot paper | Broadened comparison with component-level recovery and scheduling methods; highlighted that local restart and preserving unrelated work are established goals. |
| A-005 | Texas Instruments CTPL utilities | Contributed an embedded persistence/restore comparison, particularly recovery of application state after power-loss or reset conditions. |
| A-006 | Texas Instruments NVS utilities | Contributed the non-volatile storage and state-restoration perspective; helped separate persistent-state recovery from live peripheral-event quarantine. |
| A-007 | Event-driven workload scaling and interrupt-overload studies | Contributed queue-pressure and interrupt-burst context; reinforced the need to treat finite capacity and overload rejection as explicit bounds, not as unique P4 benefits. |
| A-008 | FSM-based adaptive sampling | Contributed an adjacent finite-state adaptation pattern for embedded operation; provided context for distinguishing general state-machine adaptation from fault-association safety contracts. |
| A-009 | ML-based adaptive sensing/scheduling | Contributed an adjacent adaptive resource-allocation comparison; helped bound the project away from claiming novelty for adaptation in general. |
| A-010 | Automatic CAN bus-off recovery | Contributed protocol-specific recovery context and the reminder that bus fault recovery is established; comparisons should be made at the protocol and state-transition level. |
| A-011 | AUTOSAR fault/event/driver mechanisms | Added automotive fault-management and recovery concepts to the combination-risk review, beyond a single paper or patent. |
| A-012 | Zephyr driver/device recovery mechanisms | Added an open-source RTOS implementation comparison target for driver lifecycle, device reset and error paths. |
| A-013 | FreeRTOS fault/event/driver mechanisms | Added an RTOS comparison target for queueing, event delivery and application-defined peripheral recovery patterns. |
| A-014 | NuttX fault/event/driver mechanisms | Added a further RTOS comparison target for device-driver lifecycle and peripheral error handling. |
| A-015 | Herder et al., “Failure Resilience for Device Drivers” / MINIX 3 driver recovery | Contributed the OS-level driver-restart and fault-containment comparison; complements the verified “Recovering Device Drivers” work without implying identical architecture. |
| A-016 | “Falkirk Wheel” work, arXiv:1503.08877 | Contributed a selective rollback/logical-time recovery comparison as described in the historical research notes; the specific technical claims should be tied to the actual arXiv paper before manuscript citation. |
| A-017 | Ahn et al., “Fault-Tolerant Service Robots” (2013 as recorded) | Contributed system-level robot fault-tolerance and dependency-handling context; widened the comparison beyond microcontroller peripheral drivers. |
| A-018 | US 2026/0228076, “Fault recovery of peripheral I/O lines” (identifier/title as recorded in historical notes) | Contributed a targeted patent-search direction on detecting I/O-line faults and initiating recovery. The historical identifier is retained exactly as recorded pending a matching official record. |
| A-019 | 2015 interrupt-overload comparison study noted in project records | Contributed a research direction on comparing overload-prevention strategies and informed the treatment of queue/interrupt pressure as established work. |
| A-020 | 2017 IEEE MECO execution-time-monitoring paper noted in project records | Contributed an execution-time-monitoring research direction relevant to embedded error detection and timing-aware fault handling. |
| A-021 | NXP S32 Safety Software Framework | Contributed industrial safety-framework context for fault analysis, degraded operation and restart/recovery behavior. |
| A-022 | R2U2 project and general project documentation | Contributed a constrained-runtime-verification system comparison; helped frame monitoring and trace/verdict evidence as established components. |
| A-023 | Quantum Leaps QP/C QF framework documentation | Contributed event-framework, queueing and event-lifecycle context alongside the separately listed QMPool documentation. |
| A-024 | microfsm embedded state-machine framework | Contributed an implementation-level example of small embedded state machines and static/caller-owned state, relevant to zero-heap design context. |
| A-025 | Nooks / MINIX 3 / other OS driver-recovery literature beyond P-003 | Contributed broader driver isolation and recovery context, helping test whether the system-level recovery concept was already established outside bare-metal firmware. |
| A-026 | Safety-critical, aerospace and historical embedded recovery systems | Contributed a broader systems-search direction for safety-oriented recovery, escalation and fault-containment designs. This is a research strand, not a claim that one specific paper was identified. |

## Part III — Additional source-attribution and contribution notes

1. The old Phase 0 research-space map preserves search-result markers and topic notes. Those records contributed to the scope of the broader review; they are not substituted for stable source citations in a manuscript.
2. The historical note “US 12,688,084 — Intelligent data flow control valve” contributed an integration-layer failed-event-queue comparison. Its contribution is queue-level failure handling, not peripheral-specific embedded recovery; preserve that distinction if it is discussed in the manuscript.
3. US 2018/0365126 A1 and US 10,838,845 B2 are publication/grant documents from the same patent family and count once as P-014, not twice.
4. US 2018/0267859 A1 and US 10,331,522 B2 are the publication/grant forms of the event-failure-management family and count once as P-013.
5. The two 2026 Dell peripheral-management publications P-016 and P-017 have different application/publication records and are retained as separate patent records for comparison. Their legal relationship and claims must be checked before asserting independent inventions.
6. A source's inclusion records its contribution to the prior-art review; it does not, by itself, establish full-text inspection.

## Overall inventory count

**17 primary verified source records + 26 additional references used in the broader review = 43 inventory entries.**

This is an inventory count, not 43 verified papers, not 43 full-text reads, and not the final manuscript bibliography. Of the 43 entries, 17 have verified source identity/metadata and 26 remain additional leads. The number of full-text sources inspected across the entire project month is **not reconstructable with certainty** from the preserved repository alone. The 26 additional entries document the contribution of the wider research sweep; they should not be counted as 26 verified academic papers.

## Pre-submission controls

- [ ] For every manuscript citation, record the exact claim it supports and the source page/section/page number.
- [ ] Separate full-text review, abstract/metadata review and title-only leads.
- [ ] Verify all patent priority dates, claims and family relationships against authoritative records before legal comparison.
- [ ] Deduplicate publication/grant pairs and repeated search leads.
- [ ] Do not describe the 26 additional leads as verified sources.
- [ ] Do not interpret “not found in this inventory” as proof that no prior art exists.
