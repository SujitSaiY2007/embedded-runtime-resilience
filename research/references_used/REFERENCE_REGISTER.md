# Reference Register — Embedded Runtime Resilience

**Register status:** Initial reconstruction; requires final manuscript-level verification  
**Prepared:** 2026-10-13  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Basis:** Canonical `main` research records, particularly `research/novelty_investigation.md`, K.10.1–K.10.4 reports and chat records, and `research/phase2_k10_p4_advantage_novelty_results.md`.

## How to read this register

- **Inspected primary source** means a project checkpoint explicitly records inspection of the full paper, official patent text/claims, or official technical documentation. It does not mean every statement in that source has been independently rechecked in this register.
- **Metadata/abstract or partial review** means the record does not establish a full-text/claim-level audit.
- **Candidate / bibliographic verification required** means the item was mentioned as a lead, but its exact title, author list, publication data, claims, family, or primary source still needs checking.
- **Project relevance** describes why the source was investigated, not what it proves.
- Patent numbers are source identifiers, not academic papers. Multiple publications may belong to one family; do not count them as independent inventions without a family/priority review.

## A. Academic papers and research systems

| ID | Source as recorded | Type | Why it was investigated | Verification status in project records |
|---|---|---|---|---|
| RU-001 | Rebecca Smith and Scott Rixner, “Surviving Peripheral Failures in Embedded Systems,” USENIX ATC 2015 (Phoenix). [USENIX page](https://www.usenix.org/conference/atc15/technical-session/presentation/smith) · [PDF](https://www.usenix.org/system/files/conference/atc15/atc15-paper-smith.pdf) | Conference paper | Embedded peripheral recovery, checkpoint/rollback, redo logging, dependencies and fault handling. | **Inspected primary source** is recorded in K.10.3. Relevant sections/pages are noted in the K.10.3 chat record. |
| RU-002 | Branco et al., “Intermittent Asynchronous Peripheral Operations” (Karma), ACM SenSys 2019. [Repository record](https://re.public.polimi.it/handle/11311/1125033) · [Paper link recorded by project](https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf) | Conference paper | Peripheral operation state, scheduling, recovery and intermittent embedded execution. | **Full bibliographic/source recheck recommended.** Earlier project records identify the work; K.10.3's explicit primary-source inspection list does not list Karma among the sources inspected in that checkpoint. |
| RU-003 | Swift et al., “Recovering Device Drivers,” OSDI 2004. Search/reference details must be confirmed against the original proceedings. | Conference paper | Device-driver fault containment and recovery. | **Candidate / bibliographic verification required** in the prior-art records; verify original proceedings and exact author/title details before citation. |
| RU-004 | Herder et al., “Failure Resilience for Device Drivers.” Original publication metadata and exact title/author list must be checked. | Research paper | OS-level driver failure resilience and recovery. | **Candidate / bibliographic verification required.** |
| RU-005 | Ahn et al., “Fault-Tolerant Service Robots” (2013 reference as recorded). [SAGE/DOI landing page](https://journals.sagepub.com/doi/full/10.5772/54023) | Research article / chapter record | Severity/dependency-based fault containment and preservation of unaffected services. | **Metadata and exact bibliographic record require verification.** |
| RU-006 | “Falkirk Wheel” work, arXiv:1503.08877. [arXiv record](https://arxiv.org/abs/1503.08877) | Research paper/preprint | Selective rollback or preservation across event/logical-time domains, as described in project notes. | **Candidate / exact title, authors, and relevant claims require verification.** |
| RU-007 | Reinbacher et al., runtime verification / monitoring work. [Springer article recorded](https://link.springer.com/article/10.1007/s10703-013-0199-z) | Journal article | Runtime monitoring, fault diagnosis/disambiguation and temporal properties. | **Specific article metadata and relevant sections require verification before manuscript use.** |
| RU-008 | Kempa et al. / R2U2-related runtime monitoring publication. [Iowa State publication record](https://rcl.ece.iastate.edu/publications/KemZha20A) | Research publication | Resource-constrained runtime monitoring, trace/verdict evidence. | **Candidate; confirm exact citation and the paper's precise relevance.** |
| RU-009 | R2U2 project and documentation. [Official project site](https://r2u2.github.io/r2u2/) | Research system / technical documentation | Runtime monitoring in resource-constrained systems. | **Project documentation lead; cite a versioned technical paper or documentation page appropriate to the claim.** |

## B. Patents and patent-publication leads

These are **patent documents, not academic papers**. A patent citation should be checked against the official text, claims, publication/priority chronology and family data before it is used in a research paper.

| ID | Identifier / recorded source | Relevance in the project investigation | Verification status in project records |
|---|---|---|---|
| RU-010 | US 9,547,557 B2 — [Google Patents](https://patents.google.com/patent/US9547557B2/en) | Peripheral bus error containment/recovery; Dell source in K.10.3. | **Official patent text/claims inspected** is recorded in K.10.3. |
| RU-011 | US 9,411,667 B2 — [Google Patents](https://patents.google.com/patent/US9411667B2/en) | Recovery after I/O error-containment events; Intel source in K.10.3. | **Official patent text/claims inspected** is recorded in K.10.3. |
| RU-012 | US 8,510,592 B1 — [Google Patents](https://patents.google.com/patent/US8510592B1/en) | PCI/peripheral error resilience, recovery routines, reinitialization and escalation; NetApp source in K.10.3. | **Official patent text/claim 1 and abstract inspected** is recorded in K.10.3. |
| RU-013 | US 10,921,871 B2 — [Google Patents](https://patents.google.com/patent/US10921871B2/en) | History-informed recovery action selection; Trane source in K.10.3. | **Official patent text/claims inspected** is recorded in K.10.3. |
| RU-014 | US 10,331,522 B2 — [Google Patents](https://patents.google.com/patent/US10331522B2/en) | Event/resource failure management and related event-handling mechanisms; IBM source in K.10.3. | **Official patent text/selected claims inspected** is recorded in K.10.3. |
| RU-015 | US 10,929,373 B2 — [Google Patents](https://patents.google.com/patent/US10929373B2/en) | Related failed-event/resource-association lead in project notes. | **Family relationship, exact title and claim-level scope require recheck.** |
| RU-016 | US 2018/0365126 A1 — [Justia record](https://patents.justia.com/patent/20180365126) | Failed-event queue, corrective action and replay lead. | **Candidate lead; primary publication/claims and family chronology require verification.** |
| RU-017 | US 12,688,084 — [Justia record](https://patents.justia.com/patent/12688084) | Paused-event retention, retry, verification and release lead. | **Candidate lead; confirm official publication, dates, claims and exact source.** |
| RU-018 | US 10,838,845 B2 — [Google Patents](https://patents.google.com/patent/US10838845B2/en) | IBM failed-event queue / moving failed events to a separate queue, used in K.10.3 combination C1. | **Official patent text and selected claims inspected** is recorded in K.10.3. |

## C. Framework and technical-documentation sources

| ID | Source | Type | Why it was investigated | Verification status in project records |
|---|---|---|---|---|
| RU-019 | Quantum Leaps QP/C — [QMPool documentation](https://www.state-machine.com/qpc/struct_q_m_pool.html) | Framework documentation | Static storage, event-block allocation/recycling and memory-pool semantics. | **Official technical documentation inspected** is recorded in K.10.3. The register preserves the distinction between preallocated pool storage and dynamic allocation/recycling of blocks. |
| RU-020 | Quantum Leaps QP/C — [QF documentation](https://www.state-machine.com/qpc/class_q_f.html) | Framework documentation | Event framework, event pools, queueing and lifecycle semantics. | **Official technical documentation inspected** is recorded in K.10.3. |
| RU-021 | microfsm embedded state-machine framework. [GitHub repository](https://github.com/Vanderhell/microfsm) | Open-source implementation | Static/caller-owned state and zero-dynamic-allocation embedded event/state-machine practice. | **Repository lead** in the prior-art notes; record the exact commit/version and inspect relevant code before relying on it. |

## D. Additional search areas, not yet a verified bibliography

The project notes identify AUTOSAR-style fault/event management, Zephyr, FreeRTOS, NuttX, safety-critical and aerospace systems, and other embedded driver frameworks as **search targets/categories**. They are not counted here as verified references because a specific versioned source, standard clause, manual section, or implementation commit was not established in the retrieved records.

## E. Count interpretation

This register currently contains **21 source records** (RU-001–RU-021), of which:
- 9 are academic papers/research-system records;
- 9 are patent/publication records;
- 3 are framework/documentation records.

These are **inventory counts, not a verified count of all sources encountered over the month, not a count of sources read fully, and not a count of citations suitable for the final manuscript**. Some records are explicitly incomplete or require bibliographic verification; patent family duplication may also affect counts. The complete month-long total remains unverified until all historical checkpoint records, earlier literature notes and any locally held sources are reconciled into this register.

## F. Pre-submission checklist

- [ ] Verify exact title, authors, venue, year, pages, DOI and stable URL for each academic paper.
- [ ] Open original full text and record the exact sections/pages supporting every material related-work statement.
- [ ] Verify patent titles, assignees, publication and priority dates, claims, status and family relationships against authoritative patent records.
- [ ] Separate sources read in full from abstract/metadata-only leads.
- [ ] Deduplicate papers and patent families without erasing distinct publications.
- [ ] Add each source's intended manuscript use and the exact claim it supports.
- [ ] Build the final bibliography only from sources actually cited in the manuscript.
- [ ] Do not equate “not found in this inspected set” with “no prior art exists.”
