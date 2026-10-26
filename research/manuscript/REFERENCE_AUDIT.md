# Reference Audit

Date: 2026-10-26; updated after bibliography consolidation. Method: reference metadata was checked against publisher, journal, DOI, PubMed/PMC, or institutional pages. Some source abstracts/full-text passages were inspected for relevance. Page-level claim checks against the complete text of all references were **not** completed. Do not treat this audit as a substitute for final author verification.

**Verification tiers**
- **A** checked against an authoritative or institutional page in this session.
- **B** metadata taken from the repository's own audit (`Plan2.0/reference_audit/REFERENCE_REGISTER.csv`, `CHAT_04_JOURNAL_REFERENCE_CANDIDATES.md`); not re-fetched here. Re-check before submission.
- **C** candidate or lead; not cited in the draft.

## Cited in the draft

| # | Reference | Type | Tier | Evidence this session | Supports (draft) | Fit |
|---|---|---|---|---|---|---|
| [1] | Smith, Rixner. Surviving Peripheral Failures in Embedded Systems. USENIX ATC 2015 | Conference | A | USENIX presentation page: title, authors (Rice University), abstract (checkpointing, rollback, as little as 6 KB), BibTeX year. No page numbers on page | 2.1: checkpoint-based peripheral recovery on constrained targets | Direct comparator, conceptual |
| [2] | Branco, Mottola, Alizai, Siddiqui. Intermittent Asynchronous Peripheral Operations. SenSys 2019 | Conference | A | POLIMI repository record and paper front matter: DOI 10.1145/3356250.3360033, SenSys '19, Nov 10–13 2019; pages 55–67 from dblp (secondary). ACM DL page not opened | 2.1: peripheral consistency under intermittent power | Adjacent comparator |
| [3] | Swift, Annamalai, Bershad, Levy. Recovering Device Drivers. ACM TOCS 24(4), 333–360, 2006 | Journal | A (DOI missing) | University of Washington author copy header: TOCS vol. 24 no. 4, Nov 2006, pp. 333–360; abstract matches. OSDI '04 version (pp. 1–16) confirmed on USENIX | 2.1: driver-level recovery in operating systems | Conceptual comparator; journal version cited |
| [4] | Candea, Kawamoto, Fujiki, Friedman, Fox. Microreboot—A Technique for Cheap Recovery. OSDI 2004, pp. 31–44 | Conference | B | Repository register: "verified, official proceedings metadata" | 2.1: component restart | Conceptual comparator |
| [5] | Avizienis, Laprie, Randell, Landwehr. Basic Concepts and Taxonomy of Dependable and Secure Computing. IEEE TDSC 1(1), 11–33, 2004. doi:10.1109/TDSC.2004.2 | Journal | A | Newcastle ePrints record (journal, year, DOI); volume, issue and pages from VDU repository and a second index; abstract matches | 2.2: terminology | Foundational |
| [6] | Reinbacher, Függer, Brauer. Runtime verification of embedded real-time systems. Formal Methods Syst. Des. 44, 203–239, 2014. doi:10.1007/s10703-013-0199-z | Journal | B | Repository register: "verified, publisher record" | 2.2: resource-bounded monitoring | Context, not a recovery method |
| [7] | Kempa, Zhang, Jones, Zambreno, Rozier. Embedding Online Runtime Verification for Fault Disambiguation on Robonaut2. FORMATS 2020, LNCS 12288, 196–214. doi:10.1007/978-3-030-57628-8_12 | Conference | B | Repository register: "verified, official proceedings volume" | 2.2: fault disambiguation | Context |
| [8] | Safari et al. A Survey of Fault-Tolerance Techniques for Embedded Systems… IEEE Access 10, 12229–12251, 2022. doi:10.1109/ACCESS.2022.3144217 | Journal | B | Repository candidate list: IEEE Xplore record checked, author list checked | 2.2: survey context | Context |
| [9] | Heffernan, MacNamee, Fogarty. Runtime verification monitoring for automotive embedded systems… IET Software 8(5), 193–203, 2014. doi:10.1049/iet-sen.2013.0236 | Journal | B | Repository candidate list: publisher page checked | 2.2: monitoring of safety properties | Context |
| [10] | Asghari, Binesh Marvasti, Rahmani. Enhancing transient fault tolerance… OS task level redundancy. Future Gener. Comput. Syst. 87, 58–65, 2018. doi:10.1016/j.future.2018.04.049 | Journal | B | Repository candidate list: publisher page checked | 2.2: OS-level software recovery | Adjacent; cited sparingly |
| [11] | Rodriguez Arreola et al. RESTOP: Retaining external peripheral state in intermittently-powered sensor systems. Sensors 18(1), 172, 2018. doi:10.3390/s18010172 | Journal | A | PubMed/PMC and publisher-linked record; full-text page inspected for scope | 2.1: peripheral state restoration | Direct adjacent prior art; explicitly distinguishes power-interruption restoration from this project's fault/event policy |
| [12] | Albalooshi, Jallad, Marpu. Fault analysis and mitigation techniques of the I2C bus for nanosatellite missions. IEEE Access 11, 34709–34717, 2023. doi:10.1109/ACCESS.2023.3262410 | Journal | A | IEEE Xplore record checked | 2.1: I2C failure modes and mitigation context | Direct protocol-level context; does not equate address NACK with stuck-bus fault |
| [13] | Solouki, Angizi, Violante. Dependability in embedded systems: A survey of fault tolerance methods and software-based mitigation techniques. IEEE Access 12, 180939–180967, 2024. doi:10.1109/ACCESS.2024.3509633 | Journal | A | IEEE/institutional record checked | 2.2: embedded dependability taxonomy | Broad context |
| [14] | Trivedi, Grottke, Lopez. Rethinking software fault tolerance. IEEE Transactions on Reliability 73(1), 67–72, 2024. doi:10.1109/TR.2023.3330787 | Journal | A | University/publisher-linked bibliographic record checked | 2.2: retry/reboot/environmental recovery framing | Conceptual context; different system domain |
| [15] | Thati, Vankeirsbilck, Boydens, Pissoort. Data error detection and recovery in embedded systems: A literature review. Advances in Science, Technology and Engineering Systems Journal 2(3), 623–633, 2017. doi:10.25046/aj020380 | Journal | A | Journal landing page checked | 2.2: embedded error detection/recovery review | Broad context |
| [16] | Santos, Santos, Orozco. Power saving and fault-tolerance in real-time critical embedded systems. Journal of Systems Architecture 55(2), 90–101, 2009. doi:10.1016/j.sysarc.2008.09.001 | Journal | A | ScienceDirect record checked | 2.2: real-time recovery/resource trade-offs | Adjacent; context only |

**Final-draft reference count (current DRAFT_MANUSCRIPT.md):** 16 unique numbered references. **Strict journal count: 12/16 = 75.0%.** Conference/proceedings papers: 4 ([1], [2], [4], [7]). No magazine article, book, software documentation, or patent is included in this 16-reference list. The four conference papers are retained because they are core prior-art comparators; they should not be removed merely to improve the ratio. This is a finalized working-draft bibliography composition, not submission-ready finality: all 16 still require final claim-to-full-text/page checks, and [3] still needs its DOI confirmed.

## Candidates and leads (not cited)

| Source | Origin | Status | Use if verified |
|---|---|---|---|
| Kleeberger, *Computer-Aided Development of Robust Embedded Software* (TU München dissertation, 2019; publisher page seen via search) | New lead found this session | C, thesis; related journal and conference papers not searched | Likely the closest prior art on robustness to peripheral failures. Review before the gap statement (O-14) |
| Gao et al., fault diagnosis, Parts I and II (IEEE Trans. Ind. Electron.) | Reconstructed 20-reference plan | C | Only if the paper discusses diagnosis |
| Taleb et al., uncertainty in runtime verification | same | C | Association-uncertainty discussion |
| Vaidyanathan, Trivedi, software rejuvenation | same | C | Restart-decision discussion |
| Arlat et al., fault injection for dependability evaluation (IEEE Trans. Computers) | same | C | Fault-injection methodology; supports a journal-count increase with real relevance |
| Hsueh et al., fault injection techniques (IEEE Computer) | same | C | Magazine, not counted as journal |
| Solouki et al., dependability in embedded systems survey | same | Now cited as [13] | Removed from candidate list; check claim-to-full-text mapping before submission |
| Wu et al., software transient-fault tolerance for embedded systems | same | C | Check relevance |
| Regehr, Duongsaa, Preventing interrupt overload, SIGPLAN Notices 40(7), 50–58 | Register P-007 | C, partially verified | Only if interrupt overload is discussed |
| Streichert et al.; Santos et al.; Moulik, Sharma (FRESH); Alishzadeh et al. | CHAT_04 and reconstructed plan | C | Weak relevance (scheduling, networked or reconfigurable systems). Recommend dropping unless the paper discusses scheduling and energy trade-offs |
| Patent records P-009 to P-017 (and K.10 §7 list PA-02 to PA-06) | Register | C, aggregator data | Not citable as verified; legal review (O-15) |
| Project repository | — | Not literature | Mention only in the availability statement |

## Rules applied

1. No bibliographic field was invented. Missing fields are shown as missing ([3] DOI).
2. Conference papers are not counted as journals. IEEE *Computer* is excluded from the strict journal count.
3. A citation supports only the sentence it sits on. [6]–[10] are context and do not imply any overlap with P4.
4. The register's 43 rows are not a bibliography: 17 are broad topic leads and 9 are patent records.
