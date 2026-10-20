# Related-Work Gap Matrix — Journal-First Bibliography

**Audit date:** 2026-10-20  
**Branch:** `main` only  
**Basis:** Current 43-entry register, Chat 02 metadata audit, Chat 03 traceability and claim-evidence reports, and publisher-page discovery for additional journal candidates.

## Gap matrix

| Related-work theme | Existing evidence | Journal coverage now | Gap / next action |
|---|---|---|---|
| Embedded peripheral failure and recovery | Phoenix (P-001, refereed USENIX conference); Karma (P-002, SenSys proceedings, metadata still partial); patent comparators P-009–P-017 | No additional journal article in the current register directly equivalent to Phoenix/Karma | Retain essential primary conference sources. Search journal literature on peripheral error recovery, device/peripheral reset, driver recovery, and selective recovery. Do not claim a journal paper is equivalent without inspecting its method. |
| Driver fault containment/recovery | Recovering Device Drivers (P-003, OSDI conference); Failure Resilience for Device Drivers (A-015, conference) | No journal article explicitly classified in the register for this narrow theme | Add journal studies on software/driver fault containment only if they address the paper's actual claim. Preserve OS-level vs bare-metal distinction. |
| Runtime verification in embedded/real-time systems | P-005 journal article; P-006 and A-001/A-022 provide conference/project context | One journal article in the inventory | Strong opportunity: add peer-reviewed journal work on runtime monitoring, embedded real-time verification, fault disambiguation and monitoring of safety properties. P-005 alone is insufficient for a literature review. |
| Fault tolerance in real-time embedded systems | Several conference/patent/technical-source entries; broad A-series leads | No additional journal entries in the current register | Add relevant journal surveys and method papers on fault-tolerant real-time embedded systems, fault injection, software redundancy and recovery trade-offs. Distinguish scheduling/redundancy from peripheral-event recovery. |
| Evidence-bounded fault association and diagnosis | P-006 is a conference paper on runtime verification/fault disambiguation; broad monitoring leads A-001/A-002/A-022 | No journal article mapped directly to this precise integrated mechanism | Search journals on embedded fault diagnosis, fault isolation, runtime fault disambiguation and partial observability. Avoid suggesting these sources disclose the full proposal unless the source demonstrates it. |
| Event-level quarantine, dependency-aware scheduling and preservation of unrelated queued work | Gate A–C and C reference model define the project mechanism; K.10.3 records a credible combination challenge | No identified journal source directly mapped to the complete combination | Treat this as an open comparison question, not a proven novelty gap. Search journals and inspect exact papers for event retention, selective rollback, transaction isolation, dependency-aware recovery and queue preservation. |
| Bounded memory / zero-heap implementation | QP/C and RTOS documentation; event-driven systems conference literature | No journal source in the current register directly establishes the same contract | Search peer-reviewed journals on static-memory embedded software, bounded recovery state, memory-safe/real-time runtime design. Do not use framework manuals to claim peer-reviewed evidence. |
| Fault injection and empirical validation | K.10 host/reference-model campaign; source register contains several fault-tolerance leads | No journal article currently mapped to a directly comparable peripheral-level protocol | Add journal studies on fault-injection methodology and evaluation reporting, but keep the K.10 host model separate from physical MCU evidence. |
| Hardware demonstration and MCU-specific measurements | Hardware plan only; physical validation remains pending | No empirical journal evidence can substitute for this project's own hardware results | Complete the planned hardware gate and produce raw board-specific evidence. References do not establish that this project's hardware was tested. |

## Candidate journal sources discovered in this pass

See `CHAT_04_JOURNAL_REFERENCE_CANDIDATES.md` for bibliographic metadata, publisher links, relevance ratings, and limitations. Candidates cover embedded runtime verification, fault-tolerance surveys, task-level transient-fault recovery, fault-tolerant real-time scheduling, and self-adaptive networked embedded systems.

## Related-work writing implications

1. Organize related work by **technical theme**, not by a list of unrelated citations.
2. For each paragraph, identify the established problem/approach, cite exact primary sources, state the concrete limitation relevant to this project, and avoid implying that one paper lacks a feature until its text has been checked.
3. Keep the strongest direct embedded-peripheral papers even if conference-published; these are important primary comparators.
4. Use journal articles to broaden evidence on runtime verification, fault-tolerance, embedded/real-time recovery and empirical evaluation.
5. The proposed contribution should be described as an integrated engineering hypothesis under evaluation. Neither a high journal ratio nor a long bibliography establishes novelty.
6. A final ratio cannot be calculated until the actual manuscript bibliography is located and deduplicated.
