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
| D-008 | Accepted | Treat the runtime-contract/recovery candidate as provisional and potentially too broad. | Phase 0 found substantial existing work in runtime verification, watchdogs, resource contracts, and local recovery. |
| D-009 | Accepted | Freeze the development topic as a lightweight context-aware peripheral recovery policy for resource-constrained event-driven MCU firmware. | Deep prior-art attack found the broad peripheral-recovery space crowded but identified a narrower, experimentally testable software-only policy hypothesis worth developing. |
| D-010 | Accepted | Treat context-aware recovery, selective peripheral restart, graceful degradation, and recovery state machines as established concepts rather than novelty claims. | Academic, industrial, and patent evidence contradicts broad novelty claims. |
| D-011 | Accepted | Define the provisional contribution around local fault context/history, bounded recovery-action selection, and explicit preservation of unrelated event-driven service. | This is the narrowest defensible hypothesis identified in the current investigation and supports measurable comparison against fixed retry/reset baselines. |
| D-012 | Accepted | Integrate a strict zero-heap constraint into the frozen development topic. | Static allocation is appropriate for deterministic resource-constrained MCU firmware; zero-heap itself is not claimed as novel. |
| D-013 | Accepted | Integrate event quarantine as a core recovery mechanism, while using formal invariants rather than claiming full formal verification. | Quarantining only the fault-associated event while preserving independent valid queued events directly operationalizes the service-preservation objective and creates measurable correctness properties. |
| D-014 | Accepted | Treat MPU support as a target-platform containment mechanism, not the invention itself. | MPU technology is established; it can strengthen isolation experiments without becoming a false novelty claim. |
| D-015 | Accepted | Require physical MCU hardware for final physical validation, while permitting laptop/PC simulation and development before hardware is obtained. | MPU behavior, peripheral-driver behavior, interrupt timing, and real hardware fault modes cannot be fully established by host-only simulation. |
| D-016 | Accepted | Transition to Phase 1 — System Design and Experimental Preparation. | Topic is frozen; remaining work is to design the smallest defensible system and reproducible evaluation before implementation. |
| D-017 | Accepted | Make MPU-capable MCU/board selection an immediate Phase 1 prerequisite. | Physical validation requires real MCU behavior; board choice affects architecture, peripherals, fault injection, and tooling. |
| D-018 | Accepted | Treat event model, fault model, recovery state machine, formal invariants, baselines, and experimental protocol as design gates before large-scale implementation. | Prevents framework-first development and keeps the project experimentally falsifiable. |
| D-019 | Accepted | Enter Phase 1E.1 conceptually with six explicit core invariants as the formal correctness boundary. | Establishes a precise correctness target before experimental implementation and prevents vague claims about recovery safety. |
| D-020 | Accepted | Make Gate A — exact Event Model and dependency semantics — the immediate next design task. | Quarantine safety, fault association, service preservation, dependency safety, recovery termination, and bounded resource usage all depend on unambiguous event/dependency semantics. |
| D-021 | Accepted | Restore the retained Phase 1 event/testbed/recovery design documents onto `main` without deleting newer main-branch continuity documents. | The earlier design branch contained important design baselines while `main` contained newer continuity/prior-art material; both need to remain available in the canonical branch. |
| D-022 | Accepted | Use phase/gate completion as the preferred chat handoff boundary and checkpoint the repository before opening the next chat. | Prevents loss of context as individual chat history grows and makes the repository the durable continuity layer. |
| D-023 | Accepted | Define Gate A as a semantic contract rather than a final C struct. | Preserves implementation flexibility while making the correctness boundary precise before byte-level optimization. |
| D-024 | Accepted | Use `EventRef = {slot_id, generation}` as the bounded active event identity. | Prevents ambiguity when fixed event slots are reused and avoids dependence on globally unbounded identifiers. |
| D-025 | Accepted | Define dependencies explicitly as INDEPENDENT, ORDERED, or COUPLED/TRANSACTIONAL and never infer them from peripheral equality. | Same-peripheral events can have different transaction/state semantics; dependency safety requires explicit evidence. |
| D-026 | Accepted | Separate FIFO admission order from execution eligibility. | Allows safe independent work to bypass a quarantined event without weakening explicit precedence constraints. |
| D-027 | Accepted | Define quarantine as retained non-executable state, not deletion or global queue flushing. | Directly operationalizes quarantine safety and service preservation. |
| D-028 | Accepted | Define preservation as correct verified execution and distinguish it from correct blocking. | Prevents aggressive blocking from being misreported as successful service preservation. |
| D-029 | Accepted | Use provisional host-model bounds `QMAX=16`, `XMAX=4`, `DMAX=4` pending Gate E workload validation. | Provides an explicit finite design envelope while avoiding premature claims that these values are experimentally optimal. |
| D-030 | Accepted | Accept Gate A as complete and advance the project to Gate B — Fault Model + Fault Association. | The event/dependency semantic contract is internally consistent, bounded, and sufficient to constrain the next design gate. |

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

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

### R-006 — Treat zero-heap, MPU use, or event quarantine individually as novel
**Status:** Rejected.

Each is an established technology/concept. The research contribution must come from the specific integrated mechanism and its demonstrated technical trade-offs.
