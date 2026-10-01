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

| D-076 | Accepted | Audit the committed reference before experiment work and explicitly record the P0-P3 quarantine ablation gap rather than silently changing runtime semantics. | The frozen Gate C/E variant definitions reserve selective dependency-aware event quarantine for P4, while `runtime_start_fault()` currently applies exact-event quarantine for every variant. The gap must remain visible until baseline semantics are separately specified. |
| D-077 | Accepted | Use a declarative host experiment input corpus plus deterministic replay harness for the first P0-P4 matched-input checkpoint. | A line-oriented workload operation stream and deterministic fault schedules make inputs inspectable, preserve matched execution conditions, and avoid hidden behavior in the correctness harness. |

| D-078 | Accepted | Treat Chat K.1 as the verified host-experiment checkpoint: the committed harness builds under Windows/MSVC, CTest passes 2/2, and the host check passes for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging. | These results establish reproducible host execution of the harness, not MCU/physical evidence. |

| D-079 | Accepted | Treat the generated 70-run corpus as an inspectable evidence artifact that must be validated at the trace/outcome level before interpreting Gate-E policy results. | Harness-level PASS does not by itself establish that every emitted trace field or outcome demonstrates the intended Gate-E property. |

| D-080 | Accepted | Keep generated `out/` and `out.replay/` directories out of the committed source checkpoint; preserve the declarative inputs, harness, and checkpoint record instead. | The generated corpus is reproducible from committed inputs and code, while avoiding accidental commitment of transient host outputs before corpus-level validation. |


| D-081 | Accepted | Treat Chat K.2 as a completed host-corpus validation checkpoint: the regenerated corpus contains 70 matched W01-W14 × P0-P4 runs, the manifest reports the declared reproducibility/metadata checks as PASS, and no concrete corpus-generation or runtime defect was found in the inspected evidence. | This validates reproducibility and inspectability of the host evidence without claiming MCU/physical validation or experimental superiority. |
| D-082 | Accepted | Preserve the P0-P3 quarantine-ablation qualification and W09/W10 capacity-confound qualification in all later interpretation. | The current implementation applies exact-event quarantine across P0-P4, so P0-P3 are not clean quarantine ablations; W09/W10 exercise capacity-confounded conditions by protocol. |
| D-083 | Accepted | Keep generated `reference/experiments/out/` and `out.replay/` as transient verification artifacts rather than mandatory source-checkpoint files. | The committed declarative inputs and harness reproduce the corpus, while transient host outputs should not be mistaken for durable source artifacts. |
| D-084 | Accepted | Advance from Chat K.2 to Chat K.3 final synthesis without reopening Gates A-E. | K.2 found no concrete corpus defect requiring a semantic redesign; the remaining work is evidence-bounded synthesis, limitation reporting, and project packaging. |

| D-085 | Accepted | Treat Chat K.3 as the final host/reference synthesis checkpoint for the current stage and preserve an explicit evidence boundary: host reproducibility/correctness evidence is not MCU/physical evidence. | K.1/K.2 provide reproducible host evidence but leave MCU, physical, statistical, external-validity, and clean-ablation questions unresolved; the repository should stop at a coherent evidence-bounded checkpoint rather than imply completion of those validations. |


| D-086 | Accepted | Treat the software demonstrator, host re-verification, methodology lock, professor-facing demonstration, and software-phase conclusion as one integrated checkpoint. | This is the immediate software objective before target-MCU validation; professor verification is its intended use, not a separate gate. |


| D-087 | Accepted | Divide the project explicitly into Part I (K.1-K.3) and Part II (K.4 onward). | K.3 is a completed host/reference synthesis checkpoint while the objective continues into software demonstration, virtual-system work, novelty investigation and methodology lock. |
| D-088 | Accepted | Make exp the canonical active research/reference branch and main the integrated stable mirror. | Separates experimental development from stable project state while preserving an auditable synchronization path. |
| D-089 | Accepted | Require every Part-II chat to have a predefined scope and explicit out-of-scope boundary. | Prevents scope creep, accidental redesign and cross-chat task repetition. |
| D-090 | Accepted | Require every Part-II chat to emit a continuity record and exact next-checkpoint handoff. | The project must remain reconstructable without relying on conversation history. |
| D-091 | Accepted | Treat professor review as the intended use of Part II rather than a separate stage. | The software demonstrator is being constructed specifically to support professor-facing proof of concept and approval for hardware validation. |
| D-092 | Accepted | Do not claim novelty from individual ingredients; conduct a fresh element-by-element prior-art investigation of the integrated mechanism. | Current prior art covers peripheral recovery, checkpointing, selective recovery, fault containment and policy-driven recovery. The remaining question concerns the specific combination and constraints. |
| D-093 | Accepted | Preserve the C reference runtime as the sole authoritative recovery-policy implementation for the virtual demonstrator. | Prevents the UI/simulator from becoming a second competing specification. |
| D-094 | Accepted | Freeze the Part-II demonstrator architecture as UI -> Virtual Embedded System -> C Reference Runtime -> Recovery Decision -> Trace -> UI before implementation. | Keeps presentation, environment modelling, policy execution and evidence traceability distinct. |


## D-095 — K.4 narrow the novelty hypothesis after adversarial re-research
**Status:** Accepted

The broad novelty framing is not defensible because prior art separately and in meaningful combinations covers peripheral recovery/isolation, recovery history, failed-event quarantine, dependency-aware containment, selective rollback/preservation, constrained runtime fault disambiguation, and zero-dynamic-allocation execution.

**Decision:** retain only the narrower unresolved hypothesis concerning the combination of evidence-limited fault-to-event association, retained event quarantine, dependency/order-aware preservation, bounded history-conditioned recovery, and static bounded implementation in constrained event-driven MCU firmware.

**Reason:** avoids claiming novelty merely because no identical publication was found.

## D-096 — Lock Part-II conceptual authority boundaries before K.5
**Status:** Accepted

Freeze the conceptual chain as:

UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI

The C reference runtime is the sole recovery-policy authority. UI and virtual-system layers may present/request/model behavior but may not implement alternative recovery semantics. The trace layer records runtime-produced evidence and does not infer policy.

**Reason:** prevents architecture drift and a second competing recovery specification during K.5-K.7.

## D-097 — Preserve historical K.4 integrated-software records as superseded history
**Status:** Accepted

Retain the older integrated-software-phase K.4 record and methodology-lock document. Mark current continuity state as governed by the Part-II K.4 scope override rather than deleting or rewriting historical records.

**Reason:** preserves provenance and explains the project-scope reclassification without allowing stale material to control active work.

## D-098 — Treat main-ahead state as historical, not as active exp state
**Status:** Accepted

At K.4 entry, exp was 1f3a471d2987b066ee995f4bf563fcdcbcd74d97 while main was e413a5986df9a486622bb4b34ef13ebc1e63ae80, one merge commit ahead. The main-only merge contains the earlier integrated-software-phase package.

**Decision:** continue K.4 from exp, as required by the active-branch rule. Do not silently reset or force-update either branch.

**Reason:** the project protocol defines exp as the active research/reference branch; the main-only merge is preserved until the completed K.4 package is explicitly synchronized through the required PR path.


## D-099 — K.5 runtime API is the virtual-system integration boundary
**Status:** Accepted

K.6 will implement the virtual environment around the existing ref_runtime.h/ref_runtime.c API. The C runtime remains the sole recovery-policy authority.

**Reason:** prevents simulator/UI policy duplication and keeps the demonstrator tied to the actual reference implementation.

## D-100 — Virtual peripheral models remain environmental, not policy authorities
**Status:** Accepted

I2C/SPI/UART models may represent state, operation results and deterministic faults, but they do not select recovery actions, retry counts, quarantine targets or terminal outcomes.

**Reason:** preserves the locked K.4 architecture and single-policy-authority rule.

## D-101 — Do not add a peripheral-action callback during K.5/K.6
**Status:** Accepted for current checkpoint boundary

The current runtime has no callback for executing a virtual peripheral recovery action. K.5 therefore defines deterministic environmental action mirroring while keeping runtime_apply_policy()/runtime_verify_and_release() authoritative. Adding a callback would be a runtime/API design change and is outside K.5.

**Reason:** avoid silently redesigning the recovery mechanism merely to make the simulator more tightly coupled.

## D-102 — Scenario EventRef mappings are observational only
**Status:** Accepted

Scenario keys may map to EventRefs returned by runtime_admit(), but the virtual environment cannot allocate or fabricate EventRefs.

**Reason:** preserves generation safety and runtime ownership of identity.

## D-103 — K.5 deterministic scenarios are declarative
**Status:** Accepted

S01-S14 define workloads, dependencies, fault stimuli and evidence targets. They do not contain hidden recovery logic or hard-coded simulator recovery decisions.

**Reason:** ensures K.6 scenarios exercise the existing mechanism rather than becoming a second specification.


## D-104 — Keep K.6 environmental recovery mirroring observational

**Status:** Accepted for K.6.

K.6 implements deterministic environmental action mirroring from the immutable fault schedule but does not expose or invent a peripheral-action callback. The observed PolicyDecision comes from the existing C runtime, and the actual transition is performed by the existing runtime_apply_policy()/runtime_verify_and_release() path.

**Reason:** this satisfies the K.5 integration contract without changing recovery semantics or creating a second recovery policy. Any future callback boundary remains a separate design decision.

## D-105 — K.6 Virtual System Verification and Merge into exp

**Status:** Accepted

The K.6 virtual embedded system implementation was verified against the existing C reference runtime without modifying `ref_runtime.c` or `ref_runtime.h`. Verification confirmed:
1. CTest passed 3/3 (100%): `reference_tests`, `host_experiment_replay`, `virtual_system_tests`.
2. Deterministic execution of scenarios S01, S02, S05, S06, S08, and S14 passed.
3. Trace correlation between wrapper trace and authoritative runtime trace records confirmed.
4. Identical replay digests across repeated runs confirmed determinism (S01: 0xB72131CB, S02: 0xE8691374, S05: 0xBDC168BD, S06: 0xA123BB47, S08: 0x5A52628A, S14: 0x9185616C).
5. Zero synthetic EventRefs fabricated; no second recovery policy created; no peripheral callbacks introduced.
6. Pull Request #7 was cleanly merged into `exp` at commit `b161589`.

**Reason:** marks K.6 as verified and merged, locking the virtual embedded system foundation for the K.7 UI implementation.

## D-106 — K.7 Professor-Facing UI Architecture and Dual-Mode Delivery

**Status:** Accepted

The K.7 front-end demonstrator is implemented under `demo/` and connected directly to the C reference runtime via `virtual_demo_cli`:
1. **Zero-Authority UI:** The UI is purely an inspectable visualization and interactive control layer. It does not select recovery actions, duplicate `policy_decide()`, or manipulate runtime internal state.
2. **Dual-Mode Delivery:** The UI supports both:
   - *Live C Backend Mode:* `demo/server.py` proxies live execution requests to `virtual_demo_cli.exe` in real-time.
   - *Standalone Offline Mode:* `demo/index.html` loads pre-exported authoritative dataset `demo/scenarios_data.json` directly in any web browser without dependencies.
3. **Trace Linkage:** Interactive trace correlation highlights the exact `TraceRecord` sequences (`rt_first`..`rt_last`) corresponding to wrapper events.
4. **No-Fabricated-EventRef:** Verified on ambiguous fault scenario S08 (`INVALID_SLOT` / `255`).

**Reason:** provides a polished, interactive, professor-facing demonstrator while strictly preserving the single-policy authority of the existing C reference runtime.

## D-107 — K.7 Professor-Facing UI Merge into exp

**Status:** Accepted

The K.7 professor-facing UI implementation was verified, audited, and merged into `exp` via PR #8 at commit `f1af4e1`. Verification confirmed:
1. 5/5 CTest targets passed (100%): `reference_tests`, `host_experiment_replay`, `virtual_system_tests`, `virtual_demo_test`, `virtual_ui_contracts_test`.
2. All six canonical scenarios (S01, S02, S05, S06, S08, S14) passed with deterministic replay digests matching canonical records: S01 (`0xB72131CB`), S02 (`0xE8691374`), S05 (`0xBDC168BD`), S06 (`0xA123BB47`), S08 (`0x5A52628A`), S14 (`0x9185616C`).
3. Runtime authority preserved: `ref_runtime.c` and `ref_runtime.h` unchanged; no second recovery policy; no second scheduler; no EventRef fabrication in S08.
4. UI architecture confirmed as zero-authority presentation layer over K.6 Virtual Embedded System and C reference runtime.

**Reason:** locks the professor-facing UI layer onto `exp` and completes K.7, clearing the path to K.8 baseline validation.

## D-108 — K.8 Matched Baseline Validation and Empirical Metric Verification

**Status:** Accepted

The K.8 matched baseline validation was executed across 100 deterministic runs:
1. **Host Corpus (70 runs):** 14 canonical workloads (W01–W14) across 5 policy variants (P0–P4), recording completion rates, attempt counts, trace records, explicit capacity confounds (W09/W10), and ablation contract flags (P0–P3).
2. **Virtual Demonstrator Matrix (30 runs):** 6 canonical scenarios (S01, S02, S05, S06, S08, S14) across P0–P4, validating baseline progression, failure containment, and deterministic replay digests.
3. **Comparative Findings:**
   - **Persistent Fault Progression (W06, S06):** Baseline P0 blindly escalates after 2 retries without resetting; P1, P2, P3, and P4 progress to `ACT_REINIT_OR_RESET` on attempt 3 and recover.
   - **Ambiguous Association Safety (W12, S08):** P0 blindly retries unmapped targets yielding `OUTCOME_STALE_REF` and leaves episodes unclosed; P4 enforces exact association (`ctx->association == ASSOC_EXACT`), failing closed safely to `OUTCOME_TERMINAL_ESCALATE` with episode closed and zero synthetic EventRefs.
   - **Independent Work Preservation (W01, S01):** Unassociated events continue executing under exact quarantine across all variants.
   - **Dependency Blocking (W02, S02):** Dependent events remain blocked in `ST_QUEUED` while prerequisites are quarantined across all variants.
4. **Harness & Verification:** Added `reference/virtual/tests/test_virtual_baselines.c` and `reference/experiments/evaluate_baselines.py`. CTest expanded from 5 to 7 tests, all passing 100%.
5. **Runtime Integrity:** `ref_runtime.c` and `ref_runtime.h` remain 100% unchanged.

**Reason:** establishes controlled, reproducible comparative software evidence sufficient to evaluate the software resilience hypothesis prior to K.9 methodology lock.

## D-109 — K.8 Matched Baseline Validation Merge into exp

**Status:** Accepted

The K.8 matched baseline validation was audited, verified, and merged into `exp` via PR #9 at merge commit `5590bf1`. Post-merge verification confirmed:
1. Complete CTest suite passing 7/7 (100%): `reference_tests`, `host_experiment_replay`, `virtual_system_tests`, `virtual_demo_test`, `virtual_baseline_tests`, `virtual_ui_contracts_test`, `matched_baseline_validation_test`.
2. Deterministic execution of 100 runs (70 host runs + 30 demonstrator runs) verified identical to pre-merge evidence.
3. Stable scenario digests preserved across all runs:
   - S01: `0xB72131CB` (P0–P4)
   - S02: `0xE8691374` (P0–P4)
   - S05: `0xBDC168BD` (P0–P4)
   - S06: P0 `0xFD5C2BA8` (escalate), P1/P3/P4 `0xA123BB47` (reinit success), P2 `0xCDAB2617` (retry success)
   - S08: P0 `0x489DED5F` (stale ref), P1–P4 `0x5A52628A` (fail-closed escalate)
   - S14: `0x9185616C` (P0–P4)
4. Runtime integrity verified: `ref_runtime.c` and `ref_runtime.h` untouched; `policy_decide()` remains sole decider; `runtime_apply_policy()` remains authoritative transition; zero synthetic EventRefs.
5. Known qualifications retained: W09/W10 `capacity_confounded=1` and P0–P3 `ablation_contract_valid=0`.

**Reason:** locks the comparative baseline validation onto `exp` and formally closes K.8, clearing the path to K.9 full software re-verification and methodology lock.

## D-110 — K.9 Formal Software Experimental Methodology Lock

**Status:** Accepted

The experimental methodology, evaluation protocol, attribution boundaries, and interpretation constraints governing the software comparison between P4 and baselines P0–P3 are formally locked:
1. **Frozen Experimental Definitions (Items A–O):** Policy definitions (P0–P4), workload definitions (W01–W14), scenario definitions (S01–S14 with 6-scenario demonstrator subset), input/capacity conditions (`QMAX=16`, `XMAX=4`, `EPMAX=1`), fault taxonomy, recovery ladder ($T_1 \dots T_4$), EventRef association rules (`assoc == ASSOC_EXACT`), quarantine rules, attempt counting, terminal outcomes, trace-derived metrics, deterministic replay digests, confound handling, reproducibility protocol, and programmatic report generation are frozen in `research/phase2_k9_methodology_lock.md`.
2. **Quarantine Limitation Locked:** Exact-event quarantine is applied across all variants (P0–P4) in `ref_runtime.c`. No empirical work-preservation advantage resulting from quarantine may be claimed for P4 over P0–P3 in this software harness (`ablation_contract_valid=0` on P0–P3).
3. **S06 Limitation Locked:** P1, P2, P3, and P4 all achieve recovery (`OUTCOME_SUCCESS`; digests: P1/P3/P4 `0xA123BB47` via peripheral reinitialization, P2 `0xCDAB2617` via history-blind retry). P4 is not uniquely superior on persistent faults; the recovery advantage over P0 is attributable to peripheral recovery capability common to P1–P4.
4. **Capacity Confound Locked:** W09 and W10 outcomes reflect table capacity limits (`QMAX`, `EPMAX`) and remain explicitly flagged as `capacity_confounded=1`. They must not be cited as evidence of policy intelligence.
5. **Software-Only Boundary Locked:** Evidence is strictly host/virtual simulation. No claims regarding physical MCU cycle timing, STM32U575 RAM/Flash overhead, MPU fault hardware, electrical noise, or physical recovery are established.
6. **Prohibited Claims Locked:** Prohibits universal superiority claims, statistical significance claims, novelty claims, patentability claims, hardware validity claims, and universal generalization claims.
7. **Runtime Integrity Preserved:** `ref_runtime.c` and `ref_runtime.h` remain completely untouched.

**Reason:** ensures all empirical research claims are strictly bounded, defensible, reproducible, and methodologically controlled prior to K.10 final packaging.

## D-111 — K.9 Software Re-Verification, Methodology Lock, and Evidence Reconciliation Merge into exp

**Status:** Accepted

The K.9 software re-verification, evidence reconciliation, and formal methodology lock were audited, verified, and merged into `exp` via PR #10 at merge commit `d1e0dcb`. Post-merge verification confirmed:
1. Complete CTest suite passing 7/7 (100%): `reference_tests`, `host_experiment_replay`, `virtual_system_tests`, `virtual_demo_test`, `virtual_baseline_tests`, `virtual_ui_contracts_test`, `matched_baseline_validation_test`.
2. Deterministic execution of 100 runs (70 host runs + 30 demonstrator runs) verified identical with zero divergence.
3. S06/P2 authoritative digest reconciled to `0xCDAB2617` (while P1/P3/P4 is `0xA123BB47` and P0 is `0xFD5C2BA8`), correcting an earlier prose grouping note without altering historical K.8 evidence.
4. Runtime integrity verified: `ref_runtime.c` and `ref_runtime.h` 100% untouched; `policy_decide()` remains sole decider; `runtime_apply_policy()` remains sole authoritative transition; zero synthetic EventRefs.
5. All methodology limitations, attribution boundaries, and prohibited claims locked in `research/phase2_k9_methodology_lock.md`.
6. Canonical project state updated to `K.9: CLOSED`. K.10 has NOT started.

**Reason:** locks the re-verified methodology and reconciled empirical evidence onto canonical `exp` and formally closes K.9, clearing the path to K.10 final software packaging and research conclusion.












## D-112 — Insert K.9.2 Advantage & Novelty Investigation Design Lock before K.10
**Status:** Accepted

Do not move directly from K.9 methodology lock to a final software conclusion. Insert K.9.2 as a design/control checkpoint that systematically enumerates measurable P4 advantage dimensions, scenario combinations, trade-offs, negative controls, attribution rules, falsification criteria, and combination-level novelty search requirements.

K.10 is thereby redefined as execution of the locked P4 Advantage & Novelty Investigation, not a predetermined proof of superiority or novelty. Final synthesis/hardware-validation handoff occurs only after K.10 evidence is complete.

**Reason:** the K.8/K.9 evidence establishes reproducibility and bounded comparative observations but does not establish universal P4 superiority or novelty. A defensible research process must test meaningful alternatives including latency, transition cost, work preservation, resource cost, decision quality, compound conditions and trade-offs, while separately investigating prior art.

Historical K.1-K.9 records remain immutable; this is a forward-looking scope decision.


## D-113 — K.9.2 P4 Advantage & Novelty Investigation Design Lock completed
**Status:** Accepted

K.9.2 is complete as a design/audit checkpoint. The repository now locks:
1. a 21-dimension metric/advantage matrix;
2. admissible, instrumentable and inadmissible measurement classes;
3. W01-W14 and S01/S02/S05/S06/S08/S14 coverage and identified gaps;
4. compound-fault, history, load, queue-position, contention and alternating-fault case families for K.10;
5. negative/no-difference controls and baseline-advantage cases;
6. attribution locks for shared quarantine, S06/P2, capacity-confounded W09/W10 and host-only evidence;
7. the novelty search decomposition across individual, pairwise, higher-order and whole-combination disclosures;
8. falsification criteria for both performance advantage and integrated novelty.

No K.10 experiment or final prior-art conclusion is included in K.9.2.

**Reason:** K.9/K.8 evidence established reproducibility and bounded comparative observations but did not establish superiority or novelty. The project therefore requires a non-predetermined investigation before final synthesis.


## D-114 — Canonical K.10 starting point after K.9.2
**Status:** Accepted

The K.9.2 design/audit checkpoint is committed on `exp` at `04308f0fc797892da51e2265edfc57b810d0acd9`. This commit is the canonical starting point for K.10.

K.10 is strictly the P4 Advantage & Novelty Investigation. It must execute the locked matched scenarios, controls, admissible instrumentation and adversarial prior-art search without predetermining a positive result. Final synthesis/hardware-validation handoff remains downstream of the K.10 evidence.

**Reason:** removes ambiguity between historical K.10 packaging prompts and the current K.10 investigation scope and provides an exact auditable starting point for the next chat.


## D-115 — Post-K.10 checkpoint numbered K.11
**Status:** Accepted

The downstream checkpoint after K.10 is explicitly numbered **K.11 — Final Software Synthesis + Hardware-Validation Handoff**. K.10 remains the P4 Advantage & Novelty Investigation and is not itself the final conclusion.

K.11 will synthesize K.10 evidence, produce the evidence-bounded software-phase conclusion, package the final evidence, and define target-MCU hardware-validation requirements and success criteria. It must not redesign P4 or force a preferred outcome.

---

## D-116 — K.10 execution blocker in current environment
**Status:** Accepted

K.10 is not complete. The live repository was audited and the protected runtime remains unchanged, but the designated Antigravity execution agent is not available in the current ChatGPT tool environment and no repository-local/CI execution path is exposed. Therefore the decisive K.10 experiment matrix was not executed and no K.10 performance conclusion may be asserted.

Fresh prior-art research may be recorded as research-control evidence, but it cannot substitute for the required experiments. K.11 remains inactive until K.10's actual exit conditions are satisfied.

**Reason:** preserves research integrity and prevents fabricated execution, metrics, or superiority/novelty claims.
