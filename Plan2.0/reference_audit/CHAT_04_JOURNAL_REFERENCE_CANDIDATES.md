# Chat 04 — Journal Reference Candidates

**Audit date:** 2026-10-20  
**Branch:** `main` only  
**Purpose:** Identify real journal articles to strengthen the manuscript's journal share without weakening source relevance or misrepresenting prior art.

**Status:** Candidate shortlist, not yet the final bibliography. Publisher pages were checked for the entries below. Bibliographic identity and publication venue can be checked from the linked publisher pages; full-text/page-level analysis must still be done before citing any paper for a specific technical claim.

## High-priority candidates

### J-C01 — Runtime verification for embedded real-time systems

Thomas Reinbacher, Matthias Függer, and Jörg Brauer, “Runtime verification of embedded real-time systems,” *Formal Methods in System Design*, vol. 44, pp. 203–239 (2014). DOI: [10.1007/s10703-013-0199-z](https://doi.org/10.1007/s10703-013-0199-z).

- **Already present:** P-005; do not add as a duplicate.
- **Use:** Resource-bounded runtime monitoring, formal properties, time/space complexity and embedded implementation context.
- **Fit:** High for the verification/traceability part of related work; not a peripheral recovery algorithm.
- **Publisher evidence:** [SpringerLink article](https://link.springer.com/article/10.1007/s10703-013-0199-z).

### J-C02 — Runtime verification for automotive embedded systems

Donal Heffernan, Ciaran MacNamee, and Padraig Fogarty, “Runtime verification monitoring for automotive embedded systems using the ISO 26262 Functional Safety Standard as a guide for the definition of the monitored properties,” *IET Software*, vol. 8, no. 5, pp. 193–203 (2014). DOI: [10.1049/iet-sen.2013.0236](https://doi.org/10.1049/iet-sen.2013.0236).

- **Use:** Runtime monitoring of selected safety properties in an embedded automotive system; useful to position monitoring versus recovery action.
- **Fit:** High/moderate, depending on whether the manuscript discusses fault observation, runtime verification or traceability.
- **Limitation:** It concerns monitored safety properties and a hardware-resident monitor, not the project's same-slot event quarantine mechanism.
- **Publisher evidence:** [Wiley/IET article page](https://ietresearch.onlinelibrary.wiley.com/doi/10.1049/iet-sen.2013.0236).

### J-C03 — Survey of fault-tolerance techniques for embedded systems

Sepideh Safari, Mohsen Ansari, Heba Khdr, Pourya Gohari-Nazari, Sina Yari-Karin, Amir Yeganeh-Khaksar, Shaahin Hessabi, Alireza Ejlali, and Jörg Henkel, “A Survey of Fault-Tolerance Techniques for Embedded Systems From the Perspective of Power, Energy, and Thermal Issues,” *IEEE Access*, vol. 10, pp. 12229–12251 (2022). DOI: [10.1109/ACCESS.2022.3144217](https://doi.org/10.1109/ACCESS.2022.3144217).

- **Use:** Broader taxonomy of fault-tolerance in real-time embedded systems, especially timing, energy, thermal constraints and scheduling.
- **Fit:** High for introduction and background framing; moderate for event-level peripheral recovery.
- **Limitation:** Survey focus is system-level fault-tolerance and mapping/scheduling, not specifically peripheral-event association or quarantine. The author list has now been checked against IEEE/metadata search results.
- **Publisher evidence:** [IEEE Xplore record](https://ieeexplore.ieee.org/document/9684471/).

### J-C04 — Software-based transient fault tolerance in embedded systems

Seyyed Amir Asghari, Mohammadreza Binesh Marvasti, and Amir M. Rahmani, “Enhancing transient fault tolerance in embedded systems through an OS task level redundancy approach,” *Future Generation Computer Systems*, vol. 87, pp. 58–65 (2018). DOI: [10.1016/j.future.2018.04.049](https://doi.org/10.1016/j.future.2018.04.049).

- **Use:** Software-level recovery and fault injection in a full-system prototype; a useful contrast with the project's event-level recovery model.
- **Fit:** High/moderate for fault-recovery background and evaluation comparison.
- **Limitation:** OS task-level redundancy is not the same as a bounded bare-metal event queue or peripheral-associated event quarantine.
- **Publisher evidence:** [Elsevier/ScienceDirect article page](https://www.sciencedirect.com/science/article/pii/S0167739X18300190).

### J-C05 — Fault tolerance in real-time critical embedded systems

Rodrigo Santos, Jorge Santos, and Javier Orozco, “Power saving and fault-tolerance in real-time critical embedded systems,” *Journal of Systems Architecture*, vol. 55, no. 2, pp. 90–101 (2009). DOI: [10.1016/j.sysarc.2008.09.001](https://doi.org/10.1016/j.sysarc.2008.09.001).

- **Use:** Real-time fault-tolerance trade-offs and deterministic slack/recomputation.
- **Fit:** Moderate; helps frame recovery costs and timing constraints.
- **Limitation:** It focuses on scheduling/slack and recomputation, not peripheral-specific event containment.
- **Publisher evidence:** [Elsevier/ScienceDirect article page](https://www.sciencedirect.com/science/article/abs/pii/S1383762108001410).

### J-C06 — Fault-tolerant scheduling for heterogeneous real-time systems

Sanjay Moulik and Yanshul Sharma, “FRESH: Fault-tolerant Real-time Scheduler for Heterogeneous multiprocessor platforms,” *Future Generation Computer Systems*, vol. 161, pp. 214–225 (2024). DOI: [10.1016/j.future.2024.07.008](https://doi.org/10.1016/j.future.2024.07.008).

- **Use:** Recent journal evidence on fault-tolerant real-time scheduling and recovery-oriented redundancy.
- **Fit:** Moderate/adjacent; use only if the related-work discussion covers scheduling and recovery resource trade-offs.
- **Limitation:** Heterogeneous multiprocessor scheduling is a different problem from a zero-heap MCU peripheral-event runtime.
- **Publisher evidence:** [Elsevier/ScienceDirect article page](https://www.sciencedirect.com/science/article/pii/S0167739X24003704).

### J-C07 — Fault-tolerant and self-adaptive networked embedded systems

Thilo Streichert, Dirk Koch, Christian Haubelt, and Jürgen Teich, “Modeling and Design of Fault-Tolerant and Self-Adaptive Reconfigurable Networked Embedded Systems,” *EURASIP Journal on Embedded Systems*, vol. 2006, article 042168 (2006). DOI: [10.1155/ES/2006/42168](https://doi.org/10.1155/ES/2006/42168).

- **Use:** Fault-tolerant/self-adaptive design in networked embedded systems.
- **Fit:** Moderate/adjacent; useful for architecture-level background if the full text supports the point.
- **Limitation:** The title/topic alone does not establish a specific event-quarantine or peripheral-recovery mechanism.
- **Publisher evidence:** [SpringerOpen article page](https://link.springer.com/article/10.1155/ES/2006/42168).

### J-C08 — Fault tolerance, timing and energy in embedded real-time systems

Yasmine Alishzadeh, Somayyeh Jafarali Jassbi, and Midia Reshadi, “Energy management of fault-tolerant real-time embedded systems through switching-activity-based techniques,” *Microprocessors and Microsystems*, vol. 102, article 104929 (2023). DOI: [10.1016/j.micpro.2023.104929](https://doi.org/10.1016/j.micpro.2023.104929).

- **Use:** Recent journal treatment of reliability, timing and energy trade-offs in fault-tolerant embedded real-time scheduling.
- **Fit:** Moderate/adjacent; include only if resource/timing/reliability trade-offs appear in the manuscript.
- **Limitation:** It addresses scheduling and energy optimization, not the project's fault-association/quarantine invariant.
- **Publisher evidence:** [Elsevier/ScienceDirect article page](https://www.sciencedirect.com/science/article/pii/S0141933123001734).

## Recommended selection order

1. Retain P-005 and evaluate J-C02 for the runtime-verification background.
2. Evaluate J-C03 as a broad fault-tolerance survey.
3. Evaluate J-C04 for software recovery and fault-injection comparison.
4. Select J-C05/J-C06/J-C08 only if timing, scheduling, resource or energy trade-offs are materially discussed.
5. Evaluate J-C07 if the manuscript discusses self-adaptive/networked embedded architectures.

Do **not** cite all candidates merely to raise the percentage. Read the full text and map each selected paper to a specific claim/paragraph first. The high-level publisher metadata is not a substitute for exact page-level evidence.

## Citation-ratio reminder

The current 43-row inventory is not the final bibliography and contains 17 broad unresolved research-topic leads. Calculate journal share from the final deduplicated sources actually cited in the manuscript. Target at least 75% journals as the stated minimum; the repository's earlier requirement asks to aim for approximately 90% when relevant literature supports it. Preserve indispensable reputable conference sources and do not mislabel them as journals.
