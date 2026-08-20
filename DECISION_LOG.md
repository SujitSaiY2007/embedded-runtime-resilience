# Decision Log

| ID | Status | Decision | Reason |
|---|---|---|---|
| D-001 | Accepted | Use `SujitSaiY2007/embedded-runtime-resilience` as the canonical project repository. | Provides durable project continuity across chats and sessions. |
| D-002 | Accepted | Keep the final topic unfrozen until prior-art research is completed. | Prevents confirmation bias and unsupported novelty claims. |
| D-003 | Accepted | Restrict the target implementation to software-based embedded systems. | Core project constraint. |
| D-004 | Accepted | Treat publication and patent potential as evaluation goals, not guarantees. | Novelty and patentability must be established through evidence and professional assessment. |
| D-005 | Accepted | Maintain explicit handoff/state documents in the repository. | Enables continuation from future chats without reconstructing the project from conversation history. |
| D-006 | Accepted | Insert a formal research-space decomposition step before candidate-specific prior-art selection. | Prevents anchoring on the current lead and makes alternative opportunity classes comparable. |
| D-007 | Accepted | Advance six opportunity classes to systematic prior-art investigation, with OC-02, OC-01, and OC-10 as the initial investigation order. | They combine real embedded problems, feasible MCU implementation, measurable baselines, and plausible research depth; this ranking is not a novelty claim. |
| D-008 | Accepted | Treat the current runtime-contract/recovery candidate as provisional and potentially too broad. | Phase 0 found substantial existing work in runtime verification, watchdogs, resource contracts, and local recovery. |
| D-009 | Accepted | Freeze the development topic as **Design and Implementation of a Lightweight Context-Aware Peripheral Recovery Policy for Resource-Constrained Event-Driven MCU Firmware**. | Deep prior-art attack found the broad peripheral-recovery space crowded but identified a narrower, experimentally testable software-only policy hypothesis worth developing. |
| D-010 | Accepted | Treat context-aware recovery, selective peripheral restart, graceful degradation, and recovery state machines as established concepts rather than novelty claims. | Academic, industrial, and patent evidence contradicts broad novelty claims. |
| D-011 | Accepted | Define the provisional contribution around local fault context/history, bounded recovery-action selection, and explicit preservation of unrelated event-driven service. | This is the narrowest defensible hypothesis identified in the current investigation and supports measurable comparison against fixed retry/reset baselines. |

## Rejected/Deferred decisions

### R-001 — Premature topic freeze
**Status:** Superseded by D-009 after the requested deep prior-art attack.

The topic is now frozen for development, but not certified novel or patentable.

### R-002 — Immediate large-scale implementation
**Status:** Deferred.

Implementation begins after the exact architecture, fault model, baselines, and experimental methodology are defined.

### R-003 — Treat the broad runtime-contract/recovery framework as already novel
**Status:** Rejected.

The Phase 0 evidence scan indicates substantial prior art around runtime verification, watchdog/recovery, resource contracts, and fine-grained recovery.

### R-004 — Treat generic peripheral recovery as the invention
**Status:** Rejected.

Phoenix, Karma, driver-recovery research, vendor recovery frameworks, and patent activity show that generic peripheral recovery and selective recovery are established.

### R-005 — Freeze a broad claim of context-aware selective recovery
**Status:** Rejected.

Context-aware health management and recent selective peripheral-recovery patents make the broad concept insufficiently differentiated.
