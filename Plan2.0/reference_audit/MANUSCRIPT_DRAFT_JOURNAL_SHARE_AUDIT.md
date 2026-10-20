# Manuscript Draft — Journal Reference Share Audit

**Audit date:** 2026-10-20  
**Input reviewed:** User-provided `Manuscript Draft.pdf`, 12 pages; reference list on pages 11–12  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Repository write policy:** `main` only  
**Status:** Bibliography classification completed; manuscript itself not edited because only a PDF was supplied.

## 1. Result

The draft contains **24 numbered references** [1]–[24]. Under a broad bibliographic classification that treats the IEEE *Computer* article [12] as a journal/magazine article, **12 of 24 references (50%) are journal articles**. Under a stricter faculty rule that excludes magazine articles from the journal-article category, the count is **11 of 24 (45.8%)**.

Either way, the draft does **not** currently meet a 75% journal-article minimum.

| Measure | Count / result |
|---|---:|
| Unique numbered references in draft | 24 |
| Journal articles, broad classification | 12 |
| Broad journal share | 50.0% |
| Journal articles, strict classification excluding [12] | 11 |
| Strict journal share | 45.8% |
| Minimum journal articles needed at denominator 24 | 18 |
| Net journal-classified replacements needed to reach 75% at denominator 24 | 6 under broad classification; 7 under strict classification |

Formula: unique journal articles ÷ all unique references × 100. The professor's formal definition of “journal article” should govern the final count.

## 2. Classification of the current references

### Journal articles (12 under broad classification)

- [5] Solouki, Angizi, and Violante (2024), *IEEE Access*.
- [6] Safari et al. (2022), *IEEE Access*.
- [7] Reinbacher, Függer, and Brauer (2014), *Formal Methods in System Design*.
- [10] Avizienis et al. (2004), *IEEE Transactions on Dependable and Secure Computing*.
- [11] Vaidyanathan and Trivedi (2005), *IEEE Transactions on Dependable and Secure Computing*.
- [12] Hsueh, Tsai, and Iyer (1997), *Computer* (IEEE computer magazine/journal; ask faculty whether it qualifies for their specific quota).
- [13] Arlat et al. (1993), *IEEE Transactions on Computers*.
- [14] Gao et al. (2015), *IEEE Transactions on Industrial Electronics*.
- [15] Gao et al. (2015), *IEEE Transactions on Industrial Electronics*.
- [18] Wu, Guo, and Hu (2021), *IEEE Access*.
- [19] Aalund and Paglioni (2025), *IEEE Access*.
- [20] Taleb, Hallé, and Khoury (2023), *Computer Science Review*.

### Conference/proceedings papers (7)

- [1] Phoenix / USENIX ATC 2015.
- [2] KARMA / ACM SenSys 2019.
- [3] Recovering Device Drivers / USENIX OSDI 2004.
- [4] Microreboot / USENIX OSDI 2004.
- [8] Runtime verification for Robonaut2 / FORMATS 2020 proceedings.
- [9] Preventing Interrupt Overload / LCTES 2005.
- [16] Failure Mode Assumptions and Assumption Coverage / FTCS 1992.

### Other types (5)

- [17] Textbook.
- [21] Software/framework documentation.
- [22] Patent publication.
- [23] Patent publication.
- [24] Patent publication.

This classification is based on the venue/types stated in the manuscript's reference list. It is not a full metadata audit of every citation.

## 3. Relevance and preservation guidance

The manuscript's own related-work section uses [1]–[4] as direct primary sources for peripheral recovery, intermittent asynchronous peripheral operations, driver recovery, and microreboots. These are conference papers, but they should not be removed automatically merely to improve the ratio; they appear central to the stated comparison.

The manuscript uses journal references [5], [6], and [19] for broad embedded fault-tolerance context; [7], [8], and [20] for runtime verification and uncertainty; [10] for dependability concepts; [11] for software rejuvenation; [12]–[15] for fault injection and diagnosis; [18] for software transient-fault tolerance; and [21]–[24] for memory-pool and patent context. Final replacement decisions require checking each in-text claim against the source and considering whether a citation is essential.

The patent citations [22]–[24] should be retained only where the manuscript's prior-art discussion needs them. They must remain patents in the prior-art register and must never be counted as journal articles. Documentation [21] is appropriate for a specific implementation/API fact but does not count toward journal share. Essential conference primary sources may remain if the professor's policy permits mixed reference types.

## 4. Relevant journal candidates already discovered

These are candidates to assess, not automatic additions. Verify full text and map to a specific manuscript claim before citing:

1. Donal Heffernan, Ciaran MacNamee, and Padraig Fogarty, “Runtime verification monitoring for automotive embedded systems using the ISO 26262 Functional Safety Standard as a guide for the definition of the monitored properties,” *IET Software*, 8(5), 193–203 (2014), DOI: 10.1049/iet-sen.2013.0236.
2. Sepideh Safari, Mohsen Ansari, Heba Khdr, Pourya Gohari-Nazari, Sina Yari-Karin, Amir Yeganeh-Khaksar, Shaahin Hessabi, Alireza Ejlali, and Jörg Henkel, “A Survey of Fault-Tolerance Techniques for Embedded Systems From the Perspective of Power, Energy, and Thermal Issues,” *IEEE Access*, 10, 12229–12251 (2022), DOI: 10.1109/ACCESS.2022.3144217.
3. Seyyed Amir Asghari, Mohammadreza Binesh Marvasti, and Amir M. Rahmani, “Enhancing transient fault tolerance in embedded systems through an OS task level redundancy approach,” *Future Generation Computer Systems*, 87, 58–65 (2018), DOI: 10.1016/j.future.2018.04.049.
4. Rodrigo Santos, Jorge Santos, and Javier Orozco, “Power saving and fault-tolerance in real-time critical embedded systems,” *Journal of Systems Architecture*, 55(2), 90–101 (2009), DOI: 10.1016/j.sysarc.2008.09.001.
5. Sanjay Moulik and Yanshul Sharma, “FRESH: Fault-tolerant Real-time Scheduler for Heterogeneous multiprocessor platforms,” *Future Generation Computer Systems*, 161, 214–225 (2024), DOI: 10.1016/j.future.2024.07.008.
6. Thilo Streichert, Dirk Koch, Christian Haubelt, and Jürgen Teich, “Modeling and Design of Fault-Tolerant and Self-Adaptive Reconfigurable Networked Embedded Systems,” *EURASIP Journal on Embedded Systems*, vol. 2006, article 042168, DOI: 10.1155/ES/2006/42168.
7. Yasmine Alishzadeh, Somayyeh Jafarali Jassbi, and Midia Reshadi, “Energy management of fault-tolerant real-time embedded systems through switching-activity-based techniques,” *Microprocessors and Microsystems*, 102, article 104929 (2023), DOI: 10.1016/j.micpro.2023.104929.

The existing [7] Reinbacher et al. article is already a journal reference and must not be duplicated. The IEEE Access survey author list above was verified from publisher/metadata search results.

## 5. Required next steps before claiming bibliography compliance

1. Obtain an editable manuscript source (DOCX or LaTeX) or explicit approval to create a revised editable version from the PDF.
2. Confirm with the professor whether IEEE *Computer* [12] counts toward the “journal article” requirement.
3. Inspect full text of candidate articles and create a claim-to-source map; add only sources that genuinely support manuscript statements.
4. Preserve essential direct conference primary sources where necessary. Do not delete them only to make the percentage look higher.
5. Revise in-text citations and the numbered reference list together; remove any unused reference and verify all cross-references after renumbering.
6. Recompute the final percentage from unique cited sources and document numerator, denominator, and source-type rules.
7. Keep manuscript claims and results unchanged unless separately authorized; this audit does not validate the underlying software results or physical hardware claims.

## 6. Evidence boundary

The PDF supports counting and classifying the bibliography printed on pages 11–12. It does not itself provide an editable source file. No manuscript text or reference list has been altered by this audit. The repository's prior-art register is separate from the manuscript bibliography and must not be conflated with it.
