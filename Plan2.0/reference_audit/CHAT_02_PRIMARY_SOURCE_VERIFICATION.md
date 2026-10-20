# Chat 02 — Primary-Source Metadata and Publication-Quality Verification

**Audit date:** 2026-10-20  
**Repository:** [SujitSaiY2007/embedded-runtime-resilience](https://github.com/SujitSaiY2007/embedded-runtime-resilience)  
**Branch:** `main` only  
**Starting `main` SHA:** `4686aa178716fed5045b5aad3d72815c3a068005`  
**Starting tree SHA:** `315a30e9eafc107df76db4b35b2371887161e744`  
**Register schema:** unchanged at 17 columns  
**Inventory:** 43 stable IDs (17 P-series rows + 26 A-series entries)

## Executive result

All 43 rows were reviewed; that does **not** mean that all 43 were verified.

| Audit status | Count | IDs |
|---|---:|---|
| Core source identity and metadata verified against official primary/project record | 9 | P-001, P-003, P-004, P-005, P-006, P-008, A-005, A-006, A-016 |
| Partially verified / identified with material metadata or authority gaps | 17 | P-002, P-007, P-009, P-010, P-011, P-012, P-013, P-014, P-015, P-016, P-017, A-001, A-012, A-013, A-015, A-022, A-023 |
| Exact identity unresolved or not sufficiently established | 17 | A-002, A-003, A-004, A-007, A-008, A-009, A-010, A-011, A-014, A-017, A-018, A-019, A-020, A-021, A-024, A-025, A-026 |
| Total inventory rows | 43 | P-001–P-017 and A-001–A-026 |

These are operational evidence statuses, not quality scores, and are not a count of peer-reviewed papers or full-text reads. Source identity verification does not establish that an entire paper, method, result, patent claim, or family history has been inspected.

## Live starting point and inputs

The captured live ref was `refs/heads/main` = `4686aa178716fed5045b5aad3d72815c3a068005`, tree `315a30e9eafc107df76db4b35b2371887161e744`. Repository metadata reports default branch `main`. Chat 01 handoff's prior SHA is historical and was not used in place of live ref data.

The ten required inputs were fetched from `main`:
- `Plan2.0/README.md`
- `Plan2.0/CURRENT_STATE.md`
- `Plan2.0/EXECUTION_ROADMAP.md`
- `Plan2.0/REFERENCE_OVERHAUL.md`
- `Plan2.0/CHAT_PROTOCOL.md`
- `Plan2.0/reference_audit/REFERENCE_REGISTER.csv`
- `Plan2.0/reference_audit/CHAT_01_INVENTORY_AND_CONSISTENCY_AUDIT.md`
- `Plan2.0/handoffs/CHAT_01_HANDOFF.md`
- `research/references_used/REFERENCE_REGISTER.md`
- `research/references_used/COUNTING_AND_VERIFICATION.md`

## Per-entry outcomes and evidence

The register has a status, URL, missing-metadata statement, and evidence note for **each ID**. The original citation text in column `original_citation_text` is preserved verbatim. Representative record-level findings:

| ID | Findings | Evidence and limits |
|---|---|---|
| P-001 | Title, authors, 2015 USENIX ATC, pp. 125–137 verified; official session list labels refereed papers | [USENIX record](https://www.usenix.org/conference/atc15/technical-session/presentation/smith) · [ATC sessions](https://www.usenix.org/conference/atc15/technical-sessions). No DOI listed by the source |
| P-002 | Title/authors/2019/SenSys '19 identified from paper front matter and an institutional proceedings record | [Paper PDF](https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf) · [Politecnico di Milano record](https://re.public.polimi.it/handle/11311/1125033). Primary ACM DOI/pages still need confirmation |
| P-003 | Exact title/authors/year/OSDI proceedings and publisher confirmed | [USENIX proceedings](https://www.usenix.org/conference/osdi-04/recovering-device-drivers). Page range not exposed on retrieved summary page; no DOI listed |
| P-004 | Exact title/authors/year/OSDI venue and pp. 31–44 confirmed | [USENIX proceedings](https://www.usenix.org/conference/osdi-04/microreboot%E2%80%94-technique-cheap-recovery) · [paper page](https://static.usenix.org/event/osdi04/tech/candea.html). Application-server context is not identical to bare-metal MCU recovery |
| P-005 | DOI, authors, vol. 44, pp. 203–239, online publication date and 2014 issue year reconciled | [Springer publisher record](https://link.springer.com/article/10.1007/s10703-013-0199-z). First online 2013-11-07; issue year 2014 |
| P-006 | FORMATS 2020, LNCS 12288, pp. 196–214, DOI 10.1007/978-3-030-57628-8_12 recorded | [Springer volume](https://link.springer.com/book/10.1007/978-3-030-57628-8) · [Iowa State record](https://rcl.ece.iastate.edu/publications/KemZha20A). Metadata verification is not a fresh full-text review |
| P-007 | DOI, authors and pages corroborated via DOI-linked indexed metadata | [CiNii metadata](https://cir.nii.ac.jp/crid/1360292619878712064) · [ACM DOI target](https://dl.acm.org/doi/10.1145/1070891.1065918). Direct ACM record could not be retrieved; remains partial |
| P-008 | Official QP/C 8.1.5 QMPool API: fixed-size block pool, supplied storage, allocation/recycling | [Quantum Leaps API reference](https://www.state-machine.com/qpc/struct_q_m_pool.html). Vendor documentation, not a peer-reviewed paper; does not prove project-specific quarantine behavior |
| A-005/A-006 | Official TI CTPL and NVS utility families found | [TI CTPL](https://www.ti.com/tool/TIDM-FRAM-CTPL) · [TI FRAM utilities](https://www.ti.com/tool/MSP-FRAM-UTILITIES). Versions should be pinned for formal reproducible citation |
| A-015 | Herder et al., “Failure Resilience for Device Drivers,” DSN '07, 2007, DOI cross-reference 10.1109/DSN.2007.46; institutional repository states peer-reviewed | [VU Amsterdam record](https://research.vu.nl/en/publications/failure-resilience-for-device-drivers/) · [DOI record](https://doi.org/10.1109/DSN.2007.46). Page range / primary IEEE metadata remains open |
| A-016 | Exact arXiv identity confirmed: Isard and Abadi, “Falkirk Wheel: Rollback Recovery for Dataflow Systems,” arXiv:1503.08877, 2015 | [arXiv record](https://arxiv.org/abs/1503.08877). Preprint record does not itself demonstrate peer review |
| A-012/A-013/A-023 | Official Zephyr, FreeRTOS and QP/C documentation families identified | [Zephyr driver-model source](https://github.com/zephyrproject-rtos/zephyr/blob/main/doc/kernel/drivers/index.rst) · [FreeRTOS queues](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/02-Queues) · [QP/C](https://www.state-machine.com/qpc/). Live versions need pinning; docs alone do not prove generalized fault recovery |
| P-009–P-017 | Patent document/number titles remain partial because direct USPTO metadata/family checks were not completed | Aggregator links are retained only as discovery/cross-check records. Official next source: [USPTO Patent Public Search](https://www.uspto.gov/patents/search/patent-public-search) and [Patent Center](https://patentcenter.uspto.gov/). No legal status, scope, ownership, priority or patentability conclusion is made |

### Remaining 26-row leads

- **A-001:** RTLola project family identified, but no one paper was selected.
- **A-002–A-004, A-007–A-011:** broad research strands; relevant adjacent records are linked where grounded but no unique work is fabricated.
- **A-005/A-006:** TI CTPL/NVS official documentation families identified; version pinning remains.
- **A-012/A-013:** official Zephyr/FreeRTOS docs identified; no generic recovery mechanism is inferred.
- **A-014:** NuttX recovery source remains unresolved.
- **A-015:** separate 2007 paper; related topic to P-003 but not a duplicate work.
- **A-016:** exact arXiv preprint record resolved; peer review not established.
- **A-017:** “Fault-Tolerant Service Robots” / Ahn et al. (2013) remains unresolved.
- **A-018:** historical “US 2026/0228076 / Fault recovery of peripheral I/O lines” identity not matched in an official record.
- **A-019/A-020:** exact 2015 interrupt-overload study and 2017 IEEE MECO execution-time-monitoring paper remain unidentified; historical year/shorthand is not verified metadata.
- **A-021:** NXP S32 Safety Software Framework lacks a specific source/version.
- **A-022:** R2U2 project identity found, but no one paper/release selected.
- **A-023:** QF documentation family is distinct in scope from P-008's QMPool API page.
- **A-024:** canonical microfsm project unresolved.
- **A-025/A-026:** preserved as umbrella research leads/directions, not as papers.

## Publication type, peer-review and venue-quality criteria

1. **Publisher/issuing-body evidence:** the record is evaluated against its direct journal/proceedings publisher, issuing body, institutional repository, official product/framework documentation or official project page where available.
2. **Publication type:** journal article, refereed conference proceedings contribution, preprint, patent application/grant document, or software/vendor/standards documentation is kept distinct.
3. **Peer-review labels:** assigned only where the identified publication record or proceedings metadata supports them. No peer-review status is inferred for product documentation, broad topics, project homepages, patent documents or arXiv preprints.
4. **Venue/source quality:** the evidence is the exact publisher/issuing entity, explicit proceedings/session labels and completeness/reproducibility of the metadata. This is a bounded documentation-based assessment—not an impact-factor or numerical conference ranking.
5. **Relevance:** direct for embedded peripheral failures / interrupts; adjacent for runtime monitoring, OS driver recovery, distributed rollback, queues, persistent state or framework APIs; unresolved for generic topics without a single source.

No scalar “quality score” is assigned across incomparable journals, conferences, patents, preprints and manuals. Metadata verification is not a substitute for reading methods and results. No claims of novelty, non-obviousness, patentability, freedom to operate or absence of prior art follow from this pass.

## Duplicates, related works and patent-family accounting

- **Confirmed exact duplicate rows:** none established. All 43 IDs remain.
- **P-003 vs A-015:** distinct works (“Recovering Device Drivers,” 2004, and “Failure Resilience for Device Drivers,” 2007) with topical overlap; do not merge.
- **P-004 vs A-004:** related concept; A-004 explicitly says work beyond P-004 and no separate exact source was identified.
- **P-008 vs A-023:** QMPool class API vs QF framework documentation; related vendor docs, not a confirmed duplicate.
- **P-007 vs A-019:** 2005 paper versus an unresolved 2015-study lead; no substitution or merge.
- **Patent P-013/P-014:** likely publication/grant links in inherited notes are **not** treated as officially confirmed family identities here. A1 publications and B2 grants are different documents; count a family once only after official application/priority history confirms it.
- **P-016/P-017:** different application numbers as listed by aggregator; independent invention/legal-family conclusions are not made.
- **A-018:** unresolved; not added as a verified patent record.

## Missing metadata and open questions

1. Retrieve direct ACM records for P-002/P-007 and verify final DOI/page metadata.
2. Validate P-009–P-017 against official USPTO Patent Public Search/Patent Center records, including inventors, application numbers, filing/publication/grant dates, priority/application-family chains and current bibliographic/legal status as appropriate. Avoid legal conclusions unless reviewed by qualified counsel.
3. Recover originating source notes for A-017/A-019/A-020/A-024 and resolve A-018's number/title. Keep unresolved when evidence is missing.
4. Pin exact versions/releases and sections for TI, Zephyr, FreeRTOS, QP/C, NXP, NuttX and R2U2 references.
5. During Chat 03, establish the relation between sources and project designs/claims, identifying direct adoption, adaptation, conceptual context, comparison or no demonstrated influence. Metadata identity alone does not establish influence.

## Files and protected scope

Intended changed paths only:
- `Plan2.0/reference_audit/REFERENCE_REGISTER.csv`
- `Plan2.0/reference_audit/CHAT_02_PRIMARY_SOURCE_VERIFICATION.md`
- `Plan2.0/handoffs/CHAT_02_HANDOFF.md`

No manuscript content/bibliography, original research/reference register, protected C runtime, runtime tests, frozen K.10 experiment files/results/reports, Gate A–E contracts, prior-art/novelty analyses, or historical chat/research records are within scope.

## Validation checks actually run

- Repository metadata reported default branch `main`; starting live ref and tree were captured above.
- Required ten startup files were retrieved from live `main`.
- CSV parser check: 44 total rows including header, 17 columns each, 43 unique IDs covering P-001–P-017 and A-001–A-026.
- Original citation values were compared row-by-row before serialization; all remain unchanged. CSV escaping is reconstructed through a CSV-aware parser and writer.
- Evidence/status fields were checked for all rows; links and missing metadata are explicitly qualified. The source URLs above were inspected as described.
- A local Git CLI clone/check was unavailable due to external DNS/network resolution failure; no local `git diff`, test suite or local working-tree inspection is claimed.
- No runtime tests, hardware tests, frozen experiments, or 400-execution campaign were run.
- Report does not claim all 43 entries are verified. The patent primary-record limitation remains explicit.

## Exact next task

**Chat 03 — Source-to-Design Traceability and Research-Gap Analysis.** Map identified sources to actual repository design decisions, baselines, ablations, implementation details and claims. Classify each relation as directly adopted, adapted, conceptually informed, comparative prior art or no demonstrated influence. Identify claims supported, unsupported, broader than evidence, or needing full-text/page inspection. Preserve the distinction between identity verification and content inspection. Do not edit manuscript or bibliography prose—Chat 04 owns that revision. Work only on `main`, preserve frozen evidence and all protected assets, and finish with evidence-backed matrices plus a handoff.
