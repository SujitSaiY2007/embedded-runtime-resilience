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

## Rejected/Deferred decisions

### R-001 — Premature topic freeze
**Status:** Rejected.

We will not declare the current candidate as the final invention before systematic prior-art investigation.

### R-002 — Immediate large-scale implementation
**Status:** Deferred.

Implementation begins after the problem, gap, architecture, and evaluation strategy have sufficient evidence.

### R-003 — Treat the broad runtime-contract/recovery framework as already novel
**Status:** Rejected.

The Phase 0 evidence scan indicates substantial prior art around runtime verification, watchdog/recovery, resource contracts, and fine-grained recovery. Any surviving version must be narrowed to a specific technical mechanism and tested against the closest prior art.
