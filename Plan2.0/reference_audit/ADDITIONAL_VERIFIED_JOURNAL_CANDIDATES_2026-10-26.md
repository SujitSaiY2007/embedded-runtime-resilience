# Verified Journal Literature Additions for Manuscript Audit

**Audit date:** 2026-10-26  
**Purpose:** Candidate additions to the existing bibliography for the embedded-runtime-resilience manuscript. These are not automatically approved final citations: first deduplicate them against the manuscript's current reference list, read the full papers, and cite only claims they actually support.

## High-relevance journal papers

### R1. External peripheral state and restoration
Rodriguez Arreola, A., Balsamo, D., Merrett, G. V., and Weddell, A. (2018). “RESTOP: Retaining External Peripheral State in Intermittently-Powered Sensor Systems.” *Sensors*, 18(1), Article 172. https://doi.org/10.3390/s18010172

- **Verified metadata source:** PubMed record and full-text PMC record.
- **Relevance:** Practical MCU middleware for retaining/restoring external peripheral configuration over SPI and I²C, with an empirical evaluation.
- **Use in paper:** Direct related-work comparison for peripheral state restoration and sensor-interface recovery.
- **Important distinction:** RESTOP addresses state restoration after power interruptions; do not imply it implements the proposed fault-to-event association or event-quarantine policy unless the paper demonstrates that.

### R2. I²C fault analysis and mitigation
Albalooshi, A., Jallad, A. H. M., and Marpu, P. R. (2023). “Fault Analysis and Mitigation Techniques of the I2C Bus for Nanosatellite Missions.” *IEEE Access*, 11, 34709–34717. https://doi.org/10.1109/ACCESS.2023.3262410

- **Verified metadata source:** IEEE Xplore record and UAEU research record.
- **Relevance:** I²C fault conditions, mitigation strategies, and experimental risk analysis.
- **Use in paper:** Protocol-level motivation and comparison for the BME280/I²C hardware demonstration.
- **Boundary:** It is not evidence that this project's controlled absent-address NACK is equivalent to a physically stuck SDA/SCL bus.

### R3. Broad embedded dependability survey
Solouki, M. A., Angizi, S., and Violante, M. (2024). “Dependability in Embedded Systems: A Survey of Fault Tolerance Methods and Software-Based Mitigation Techniques.” *IEEE Access*, 12, 180939–180967. https://doi.org/10.1109/ACCESS.2024.3509633

- **Verified metadata source:** NJIT research record identifies this as a peer-reviewed journal article and supplies volume, pages, authors, and DOI.
- **Relevance:** Recent taxonomy of embedded fault-tolerance and software/hardware mitigation.
- **Use in paper:** Position the work in the wider dependability landscape and organize the related-work section.

### R4. Fault tolerance under timing, power, energy, and thermal constraints
“ A Survey of Fault-Tolerance Techniques for Embedded Systems From the Perspective of Power, Energy, and Thermal Issues.” (2022). *IEEE Access*, 10, 12229–12251. https://doi.org/10.1109/ACCESS.2022.3144217

- **Verified metadata source:** IEEE DOI/publisher record.
- **Relevance:** Summarizes fault-tolerance techniques and their resource/timing trade-offs in embedded and real-time systems.
- **Use in paper:** Support discussion of bounded-resource trade-offs and identify performance metrics that this project has not yet measured.
- **Bibliographic action:** Before final manuscript inclusion, retrieve the publisher's author metadata and complete the author field; do not submit this abbreviated entry as final IEEE style.

### R5. Software fault tolerance and environmental recovery
Trivedi, K. S., Grottke, M., and Lopez, J. A. (2024). “Rethinking Software Fault Tolerance.” *IEEE Transactions on Reliability*, 73(1), 67–72. https://doi.org/10.1109/TR.2023.3330787

- **Verified metadata source:** University research record with journal, volume, issue, pages, authors, and DOI.
- **Relevance:** Discusses recovery via execution-environment changes, including retry, reboot, and failover.
- **Use in paper:** Conceptual framing for recovery actions and why action selection/context matters.

### R6. Transient-fault tolerance in embedded software
“Enhancing transient fault tolerance in embedded systems through an OS task level redundancy approach.” (2018). *Future Generation Computer Systems*, 87, 58–65. https://doi.org/10.1016/j.future.2018.04.049

- **Verified metadata source:** ScienceDirect result with title, journal, volume, pages, and DOI.
- **Relevance:** Software-based fault tolerance evaluated with software fault injection and a system prototype.
- **Use in paper:** Compare experimental methodology and task-level recovery scope with a peripheral/event-level policy.
- **Bibliographic action:** Verify full author metadata from the publisher before final IEEE formatting.

### R7. Data error detection and recovery in embedded systems
Thati, V. B., Vankeirsbilck, J., Boydens, J., and Pissoort, D. (2017). “Data Error Detection and Recovery in Embedded Systems: A Literature Review.” *Advances in Science, Technology and Engineering Systems Journal*, 2(3), 623–633. https://doi.org/10.25046/aj020380

- **Verified metadata source:** Journal landing page.
- **Relevance:** Focused review of data-flow error detection and recovery techniques in embedded systems.
- **Use in paper:** Background taxonomy; use alongside newer surveys rather than as the sole state-of-the-art source.

## Essential non-journal systems reference (retain even if the journal ratio is high)

Smith, R., and Rixner, S. (2015). “Surviving Peripheral Failures in Embedded Systems.” *Proceedings of the USENIX Annual Technical Conference (USENIX ATC 15)*, 125–137. https://www.usenix.org/conference/atc15/technical-session/presentation/smith

- **Verified metadata source:** Official USENIX conference paper page.
- **Relevance:** Phoenix is directly concerned with peripheral recovery on resource-constrained embedded systems.
- **Use in paper:** Mandatory close prior-art comparison. The proposed work must explain the precise differences from checkpointing/rollback and peripheral-state recovery rather than claiming peripheral recovery itself is new.

## How to integrate these candidates safely

1. Search each DOI/title in the manuscript's current bibliography and remove duplicates.
2. Retrieve the full paper or publisher metadata before finalizing any citation.
3. Map every retained reference to a specific related-work statement, design decision, or comparison in a traceability matrix.
4. Use the original paper—not its abstract alone—to support technical distinctions.
5. Do not claim that P0–P3 reproduce the cited systems. They are project-defined comparison policies unless a documented implementation lineage exists.
6. Report the journal percentage only after the complete bibliography is audited. State numerator, denominator, and whether conference papers, standards, patents, preprints, and websites are excluded.
7. This is a verified *addition shortlist*, not yet a complete audit of every pre-existing reference. The current manuscript bibliography must be located and deduplicated before claiming the bibliography overhaul is complete.

## Source verification links

- RESTOP / *Sensors*: https://pubmed.ncbi.nlm.nih.gov/29320441/ and https://pmc.ncbi.nlm.nih.gov/articles/PMC5795800/
- I²C fault analysis / IEEE Access: https://ieeexplore.ieee.org/abstract/document/10082916
- Embedded dependability survey / IEEE Access: https://researchwith.njit.edu/en/publications/dependability-in-embedded-systems-a-survey-of-fault-tolerance-met/
- Power/energy/thermal survey / IEEE Access: https://doi.org/10.1109/ACCESS.2022.3144217
- Software fault tolerance / IEEE Transactions on Reliability: https://doi.org/10.1109/TR.2023.3330787
- Task-level transient fault tolerance / Future Generation Computer Systems: https://www.sciencedirect.com/science/article/pii/S0167739X18300190
- Embedded data-error recovery review: https://www.astesj.com/v02/i03/p80/
- Phoenix / USENIX ATC: https://www.usenix.org/conference/atc15/technical-session/presentation/smith
