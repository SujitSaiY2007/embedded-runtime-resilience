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
| D-031 | Accepted | Store the complete Gate B continuation prompt in `NEXT_CHAT_PROMPT.md`. | Makes the next-chat startup reproducible and reduces dependence on conversation history. |
| D-032 | Accepted | Make `main` the authoritative Gate A/Gate B handoff checkpoint and keep the design branch synchronized to it. | Prevents branch divergence at the chat boundary and preserves a single canonical continuation point. |
| D-033 | Accepted | Freeze a minimal observable fault taxonomy centered on I2C NACK, timeout/no-progress, bus/protocol error, arbitration loss, and persistent no-progress, with a reduced secondary SPI taxonomy. | Supports matched recovery experiments without pretending to characterize every possible peripheral fault. |
| D-034 | Accepted | Treat recurrence and persistence as history/episode attributes rather than instantaneous fault classes. | Repetition is a property over observations and recovery outcomes; separating it avoids an unnecessary combinatorial fault taxonomy. |
| D-035 | Accepted | Replace direct claims of "peripheral state-machine lockup" with the observable class "persistent no-progress / suspected peripheral-state failure." | Available controller/service evidence normally cannot prove the internal failure location. |
| D-036 | Accepted | Keep service/driver-level failure distinct from peripheral failure and retain an explicit ambiguous attribution outcome. | Prevents attribution bias and enforces evidence-bounded recovery scope. |
| D-037 | Accepted | Operationalize four association levels: `EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS`. | These levels match the Gate A identity model and prevent unsupported event-level causality. |
| D-038 | Accepted | Peripheral equality alone never justifies event-level fault attribution. | Multiple queued events may share one peripheral while having different transactions/dependencies. |
| D-039 | Accepted | Distinguish fault association scope from dependency-blocking scope. | A non-fault-associated event may still require blocking because it depends on quarantined/invalid state. |
| D-040 | Accepted | Make software fault injection the primary deterministic fault-generation mechanism and treat physical/protocol injection methods as unvalidated candidates until hardware testing. | Host/firmware experiments need repeatability, while physical mechanisms require actual hardware evidence and safety validation. |
| D-041 | Accepted | Define a fixed-size semantic fault record with episode identity, observation sequence, bounded timing, resource/fault context, conditional event/transaction identity, association confidence, evidence flags, recurrence/recovery context, and episode status. | Each field supports a later policy decision or experimental metric while preserving zero-heap constraints. |
| D-042 | Accepted | Define an episode as continuing across qualifying repeated observations until verified success, degraded terminal handling, or escalation; a post-terminal failure starts a new episode. | Supports bounded recovery history without treating every repeated status observation as a separate incident. |
| D-043 | Accepted | Do not make ARLO or multi-master physical injection a primary workload. | The minimal reference testbed is intended to remain simple/single-master; arbitration scenarios add complexity without directly strengthening the core hypothesis. |
| D-044 | Accepted | Accept Gate B at the semantic/design level and advance to Gate C. | The fault taxonomy, evidence boundary, association model, episode semantics, and bounded record are sufficient to derive a deterministic recovery policy; physical validation remains deferred. |
| D-045 | Accepted | Retain a separate Gate B learning summary as an educational companion to the normative fault-model artifact. | The project owner is learning embedded-systems concepts while building the research system; durable conceptual explanations improve continuity without altering the formal contract. |
| D-046 | Accepted | Freeze Gate C minimum policy context as `fault_class`, `association_level`, bounded `attempt_count`, `criticality`, bounded `recovery_safety` preconditions, and `episode_state`. | These variables can materially change recovery choice or safety; redundant history and scheduler-only state were removed. |
| D-047 | Accepted | Represent recurrence through bounded episode progression rather than a separate policy variable. | Recurrence is a temporal property already represented by attempt/episode state; a duplicate field adds RAM without independent decision value. |
| D-048 | Accepted | Remove `last_action` and `last_outcome` as independent policy inputs. | Explicit recovery state already determines the previous action/outcome needed for the next transition. |
| D-049 | Accepted | Keep service criticality as a constrained policy context, but do not use it as a priority score. | Criticality changes degradability/escalation safety but cannot override dependency or correctness rules. |
| D-050 | Accepted | Treat `pending_independent_work` as scheduler state, not recovery-policy state. | Recovery action selection should not depend on queue occupancy; Gate A eligibility already determines whether independent work may run. |
| D-051 | Accepted | Treat dependency status as an action/scheduling precondition rather than duplicating the dependency graph inside the recovery policy. | Prevents two inconsistent dependency models and preserves Gate A as the authoritative scheduler contract. |
| D-052 | Accepted | Freeze the logical recovery action set as `RETRY`, `REINIT_OR_RESET`, `DEGRADE`, and `ESCALATE`. | Four actions cover local retry, peripheral-local recovery, safe terminal degradation, and bounded terminal escalation without a general framework. |
| D-053 | Accepted | Represent peripheral reinitialization and peripheral reset as one logical policy action while retaining method-level distinction for later controlled implementation experiments. | Their policy role is the same, but their hardware/software scopes can differ; treating them as permanently identical or permanently separate would both be unjustified before implementation evidence. |
| D-054 | Accepted | Freeze at most two retry actions per fault episode before `REINIT_OR_RESET`. | Provides a deterministic transient-vs-repeated failure distinction while preventing retry loops. |
| D-055 | Accepted | Replace the underspecified provisional `Rmax=3` with an exact four-action recovery budget: two retries, one peripheral recovery action, then one terminal action. | The new definition makes attempt counting and termination auditable and ensures every path reaches a terminal state. |
| D-056 | Accepted | Count one recovery-action invocation plus its verification as one attempt; scheduler dispatches and repeated fault observations alone are not recovery attempts. | Prevents hidden or unrelated work from consuming the policy budget and makes experimental cost measurable. |
| D-057 | Accepted | Require successful action verification plus Gate A eligibility before releasing a quarantined event. | A successful peripheral operation alone does not prove that the original event/transaction is valid to execute. |
| D-058 | Accepted | Do not automatically retry coupled/transactional events unless the transaction contract explicitly establishes retry safety. | Member-level retry can violate transaction atomicity or shared-state consistency. |
| D-059 | Accepted | For `UNKNOWN_AMBIGUOUS`, use conservative containment without inventing event-level attribution; escalate if safe local containment cannot be established. | Preserves the evidence-bound association rule while providing a bounded safety response. |
| D-060 | Accepted | Use a common bounded degraded abstraction `ACTIVE -> DEGRADED -> TERMINAL` with service-specific safety contracts. | Avoids a general resilience framework while providing a uniform recovery-manager interface. |
| D-061 | Accepted | Freeze a fixed-size `PolicyDecision` output containing action, target scope, quarantine/retry/release flags, bounded attempt index, terminal flag, and reason code. | Gives implementation and experiments a compact deterministic interface without dynamic objects or free-form logging. |
| D-062 | Accepted | Freeze Gate C ablation variants P0–P4: fixed retry; fixed retry + peripheral recovery; context-only; context + episode history; integrated context/history + dependency-aware quarantine. | Allows the hypothesis to be falsified and separates the value of context/history/quarantine from baseline recovery. |
| D-063 | Accepted | Accept Gate C at the semantic/design level and advance to Gate D. | The minimum context, bounded history, action set, deterministic policy, state machine, association behavior, scheduling interaction, and termination budget are sufficiently specified for formal-property analysis. |
| D-064 | Accepted | Accept Gate D at the semantic/design-model level and advance to Gate E. | The six core invariants and supporting identity, release, dependency, transaction, termination, resource, and decision-table properties are explicitly formalized with practical checking strategies. |
| D-065 | Accepted | Use a layered finite-state checking strategy rather than claiming full firmware formal verification. | Policy decisions, EventRef lifecycle, dependency/scheduler interaction, recovery termination, and capacity boundaries can be checked in tractable bounded models while hardware/compiler behavior remains experimental. |
| D-066 | Accepted | Record the 33,792-context abstract policy-table audit as model-level evidence of totality/determinism, not as firmware or hardware validation. | The bounded cross-product was exhaustively enumerated and every encoded context produced exactly one policy outcome. |
| D-067 | Accepted | Treat generation-wrap handling and any simultaneous recovery-episode capacity beyond retained event slots as explicit implementation bounds that must be fixed before implementation. | Gate D can formalize the conditions, but the concrete generation width/wrap policy and any multi-episode `EPMAX` must be declared and resource-accounted in the implementation design. |
| D-068 | Accepted | Preserve all historical Gate A–C artifacts and earlier design baselines; update only the current continuity/checkpoint documents needed for the Gate D handoff. | Maintains an auditable research history and avoids unnecessary deletions or cosmetic rewrites. |
| D-069 | Accepted | Accept Gate E at the experimental-design/protocol level and advance to the Minimal Reference Implementation. | The comparison matrix, canonical workloads, deterministic fault schedule, finite capacity envelope, metrics, trace schema, repetition/reset policy, invalid-run rules, and evidence boundaries are now frozen without claiming experimental results. |
| D-070 | Accepted | Use P0/P1 as principal baselines, P2/P3 as mechanism ablations, and P4 as the integrated proposed mechanism. | Preserves both Gate C ablation terminology and the earlier fixed-retry/fixed-recovery comparison direction while keeping comparisons interpretable. |
| D-071 | Accepted | Freeze fourteen canonical workloads W01–W14 for the reference evaluation protocol. | Covers independent preservation, ordered/coupled safety, shared-peripheral non-causality, recovery outcomes, capacity boundaries, stale references, ambiguity, criticality, and integrated mixed execution. |
| D-072 | Accepted | Freeze deterministic software fault injection as the primary repeatable stimulus, with I2C primary and SPI secondary. | Reproducibility is required for matched comparisons; physical fault validation remains a later evidence layer. |
| D-073 | Accepted | Freeze `QMAX=16`, `XMAX=4`, `DMAX=4`, and `EPMAX=1` as the normative reference-prototype protocol envelope. | These values provide a finite reproducible test envelope while avoiding an unsupported claim of universal optimality; capacity confounding must be reported. |
| D-074 | Accepted | Require fixed trace identifiers and structured logging across workload, event, fault episode, recovery action, and final outcome. | Enables reproducible correlation from fault injection through recovery and preservation/correctness outcomes. |
| D-075 | Accepted | Require explicit separation of host, MCU, and physical evidence and prohibit host/software-injection results from being presented as physical validation. | Prevents overclaiming and keeps later performance, robustness, and hardware claims evidence-bounded. |

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

### R-007 — Treat repeated transient/persistent failure as separate top-level fault classes
**Status:** Rejected in favor of D-034.

These are temporal/history properties over a fault episode, not independent instantaneous observations.

### R-008 — Treat a controller NACK, timeout, or BERR as proof of a specific physical root cause
**Status:** Rejected.

The controller observation identifies a protocol/error condition but does not, by itself, establish why it occurred. The STM32U575/U585 errata further demonstrates that at least some bus-error observations can be spurious.

### R-009 — Treat same-peripheral membership as causal event association
**Status:** Rejected in favor of D-038.

Peripheral identity is resource context, not evidence that one queued event caused the observed failure.

### R-010 — Treat software fault injection as physical fault validation
**Status:** Rejected.

Software injection provides deterministic experimental stimuli but cannot establish physical electrical behavior.

### R-011 — Retain all eight earlier recovery-policy inputs as independent decision variables
**Status:** Rejected in favor of D-046 through D-051.

The Gate C challenge found redundancy and scheduler/policy boundary violations in `fault_recurrence`, `last_action`, `last_outcome`, `event_dependency_status`, and `pending_independent_work`.

### R-012 — Treat `Rmax=3` as a sufficient recovery bound without exact attempt semantics
**Status:** Rejected in favor of D-055 and D-056.

A numerical bound without a precise definition of an attempt/transition does not establish termination or comparable recovery cost.

### R-013 — Automatically retry every failed event, including coupled transactions
**Status:** Rejected in favor of D-058.

Retry safety depends on transaction semantics, not merely on fault class.

### R-014 — Treat ambiguity as permission for peripheral-wide event attribution
**Status:** Rejected in favor of D-059.

Ambiguity can justify conservative blocking when safety requires it, but cannot justify invented causal precision.

### R-015 — Make reinitialization and peripheral reset permanently separate policy actions before implementation evidence
**Status:** Rejected in favor of D-053.

They have potentially distinct mechanisms, but the policy-level role is one bounded peripheral-recovery action until controlled implementation experiments establish a reason to split them.
