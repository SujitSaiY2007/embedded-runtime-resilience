# Reference Audit

Date: 2026-10-26. Method: each reference was searched by exact title and authors; metadata was compared with publisher, proceedings, DOI or institutional pages that the search returned. Page-level claim checks against full text were **not** done. Nothing was added from memory without a flag.

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

**Journal share of the cited list:** journals [3], [5], [6], [8], [9], [10] = 6 of 10 = 60%. Conference papers: [1], [2], [4], [7]. This is below the supervisor's 75% target (OPEN_ISSUES O-17). With four non-journal items fixed, 75% needs 12 journal articles in total (6 more). No filler was added to reach the ratio.

## Candidates and leads (not cited)

| Source | Origin | Status | Use if verified |
|---|---|---|---|
| Kleeberger, *Computer-Aided Development of Robust Embedded Software* (TU München dissertation, 2019; publisher page seen via search) | New lead found this session | C, thesis; related journal and conference papers not searched | Likely the closest prior art on robustness to peripheral failures. Review before the gap statement (O-14) |
| Gao et al., fault diagnosis, Parts I and II (IEEE Trans. Ind. Electron.) | Reconstructed 20-reference plan | C | Only if the paper discusses diagnosis |
| Taleb et al., uncertainty in runtime verification | same | C | Association-uncertainty discussion |
| Vaidyanathan, Trivedi, software rejuvenation | same | C | Restart-decision discussion |
| Arlat et al., fault injection for dependability evaluation (IEEE Trans. Computers) | same | C | Fault-injection methodology; supports a journal-count increase with real relevance |
| Hsueh et al., fault injection techniques (IEEE Computer) | same | C | Magazine, not counted as journal |
| Solouki et al., dependability in embedded systems survey | same | C | Venue and type not checked |
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
