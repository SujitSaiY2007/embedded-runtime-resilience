# K.10.3 — Multi-Reference Combination & Technical Obviousness Analysis

**Status:** Technical analysis complete; bounded result recorded; ChatGPT review/closure required.  
**Branch:** exp  
**Scope:** Technical research only. This is not a legal opinion on novelty, obviousness, inventive step, or patentability.  
**K.10 evidence:** Frozen — 16 case families × P0–P4 × 5 deterministic repetitions = 400 matched executions. No experiments were rerun.  
**Protected boundaries:** Gates A–E, reference runtime/header, policy_decide(), runtime_apply_policy(), and main remain untouched.

## 1. Executive finding

The multi-reference attack is credible, especially **C1: Phoenix + IBM Failed Event Queue + Quantum Leaps QP/C event-pool architecture**. The primary sources disclose substantial adjacent teachings: peripheral recovery with dependency-aware redo/rematerialization; failed-event removal, separate-queue retention, corrective action and replay; and statically supplied pool storage with deterministic allocation/recycling of fixed-size event blocks. A technically motivated combination argument can therefore be articulated without inventing the component teachings.

However, these sources do **not**, as inspected here, explicitly disclose the complete P4 contract as one integrated mechanism. Important distinctions remain between:
- rollback/re-execution of program and peripheral state versus retaining one existing EventSlot as quarantined, non-executable state;
- a separate failed-event queue or message quarantine versus in-pool retention without moving or duplicating the event record;
- general dependency-aware peripheral replay versus explicit queue dependency classes and a scheduler dispatchability predicate;
- component/resource or flow association versus the evidence-precision lattice and fail-closed invariant assoc <= evidence;
- recovery thresholds, retry counters, or repeated corrective action versus the specific fixed four-rung ladder and explicit episode closure/escalation;
- static backing storage for a pool versus P4's fixed EventSlot[20] lifecycle with no dynamic pool allocation/recycling.

**Bounded conclusion:** The inspected combinations create a material technical-combination risk and weaken any broad claim that the individual ingredients are distinctive. They do not, on the evidence reviewed in this checkpoint, establish that all L1–L12 invariants are supplied by the combinations without further design choices. This is not a conclusion that the combination is legally non-obvious, novel, or patentable. The narrow integrated hypothesis remains vulnerable and must be presented cautiously in K.10.4.

## 2. Method and evidence boundary

The analysis uses the identified primary paper, patent specifications/claims, and official QP/C reference documentation. A source's explicit teaching is separated from an adaptation inference. A missing feature in these inspected sources is not proof that no such feature exists anywhere. Patent metadata shown by Google Patents is treated as bibliographic context, not as a legal-status opinion.

The three combinations below were assessed for:
1. the exact teaching supplied by each source;
2. a plausible reason to combine;
3. architecture and semantic friction;
4. whether the combined teaching establishes each relevant P4 invariant;
5. the strongest argument against P4 and the remaining countervailing gaps.

## 3. Primary-source register

| ID | Primary source and locator | Teaching used in this analysis |
|---|---|---|
| PA-01 | Smith & Rixner, “Surviving Peripheral Failures in Embedded Systems,” USENIX ATC 2015, [official paper PDF](https://www.usenix.org/system/files/conference/atc15/atc15-paper-smith.pdf), Sections 1–3, 4.2.3, 6.2; printed pp. 125–131, 134 | Bare-metal Owl embedded runtime; peripheral-access checkpoints; program-state rollback; peripheral recovery; redo mode; programmer-specified peripheral dependencies; dependent accesses re-executed and unrelated accesses rematerialized; evaluated application with an event loop. |
| PA-08 | IBM, US 10,838,845 B2, [primary patent specification](https://patents.google.com/patent/US10838845B2/en), Claim 1; Claims 2, 4–5; specification's failed-event handler/replay discussion | On application-server failure, delete the failed event and flow ID from a first event queue and insert the event, flow/application and failure reason into a different failed-event queue; corrective action; replay monitoring and possible further corrective actions. |
| QP/C | Quantum Leaps, [QMPool Class Reference](https://www.state-machine.com/qpc/struct_q_m_pool.html), Detailed Description and QMPool_init/QMPool_get/QMPool_put; [QF Class Reference](https://www.state-machine.com/qpc/class_q_f.html), QF_poolInit, QF_newX_, QF_gc | Caller supplies pool storage; fixed-size blocks are dynamically allocated/recycled from that pool; QF_poolInit initializes pools for dynamic event allocation; QF_gc decrements reference count and returns eligible mutable events to their pool. |
| PA-06 | Trane, US 10,921,871 B2, [primary patent specification](https://patents.google.com/patent/US10921871B2/en), Claims 1–9; specification's restart/restore counter discussion | Fault-related restart/restore counters and thresholds; normal boot below threshold; recovery boot or restore from a recovery partition above threshold; supervisory restart of BAS components. |
| PA-03 | Dell, US 9,547,557 B2, [primary patent specification](https://patents.google.com/patent/US9547557B2/en), Claims 1–3 and specification summary | PCIe bus controller detects fatal downstream device error, disables data link/presence state, triggers driver removal and later driver reinstallation after a delay. |
| PA-04 | Intel, US 9,411,667 B2, [primary patent specification](https://patents.google.com/patent/US9411667B2/en), Claims 1, 4, 7–13 | Platform interrupt handler notifies OS/VMM of I/O error-containment event, creates an error-containment record and facilitates link recovery responsive to OS/VMM/driver direction. |
| PA-05 | NetApp, US 8,510,592 B1, [primary patent specification](https://patents.google.com/patent/US8510592B1/en), Claim 1 and Abstract | Isolates a failed peripheral, migrates operations to a backup peripheral, calls recovery and reinitialization routines, obtains results/policy codes, then migrates operations back after recovery. |
| PA-07 | IBM, US 10,331,522 B2, [primary patent specification](https://patents.google.com/patent/US10331522B2/en), Claims 1, 4, 6–7, 10, 12; specification around event failure manager and message quarantine | Failed-event database associates failures with components/resources; retry after component/resource modification; update based on retry outcome; identify event relationships; prevent a message from reaching an associated component/resource; optional message quarantine. |

### Source-grounded qualifications

- Phoenix explicitly addresses an event-driven embedded setting and an evaluated application event loop. Its L1 setting match does **not** mean it discloses P4's queue-level dependency scheduler or retained event quarantine.
- QP's pool memory is externally provided and can be statically backed. The framework still supports dynamic allocation and recycling of mutable event blocks within that pool. This is bounded pool allocation, not necessarily general-purpose malloc/free, but it is not the same lifecycle contract as P4's fixed EventSlot array.
- IBM PA-08 Claim 1 expressly requires deleting from one queue and inserting into a different failed-event queue. IBM PA-07 Claim 6 allows message quarantine. Neither disclosure, as inspected, expressly requires retaining the same event slot in the original fixed pool.
- Phoenix's dependency handling is a significant overlap: its recovery procedure re-executes the failed access and accesses to dependent peripherals, while rematerializing accesses to unrelated peripherals. This makes the broad idea of dependency-aware preservation less distinctive; the remaining question is whether the specific queue-level dispatchability contract and its integration matter technically.

## 4. Combination C1 — Phoenix + IBM Failed Event Queue + QP/C event pools

### Strongest combination argument

A skilled embedded-systems designer could start with Phoenix's known peripheral-failure detection, reset/recovery and redo semantics; adopt IBM's known failed-event isolation, failure metadata, corrective action and replay monitoring; and use a framework such as QP/C to provide bounded event-pool storage and event queues. The rationale is technically understandable: keep failed work from being repeatedly executed, associate it with a fault and recovery episode, and bound memory usage on an embedded target.

### What each source actually supplies

- **Phoenix:** peripheral failure recovery and re-execution; a checkpoint for each outstanding peripheral access; dependency-aware redo and rematerialization of unrelated peripheral accesses. It also uses journals, control-flow queues and rematerialization queues; the paper describes heap-backed Owl state and linked-list rematerialization queues (Section 4.2.3 and implementation/resource discussion). This is not P4's fixed-slot event lifecycle.
- **IBM PA-08:** explicit failed-event storage and replay. Claim 1 moves the failed event from the original queue to a *different* queue. Claims 2 and 4 add analysis/corrective action and replay monitoring. This is strong conceptual overlap with failed-work quarantine/retry, but the disclosed server/flow architecture is not a constrained MCU runtime.
- **QP/C:** deterministic fixed-block pool operations with caller-supplied pool storage. QF_poolInit is documented as initialization for dynamic event allocation; QF_newX_ allocates a mutable event from an event pool; QF_gc recycles a mutable event to its pool when its reference count reaches zero. Static backing storage therefore does not, by itself, establish P4's no-dynamic-pool-allocation lifecycle.

### Technical friction and missing steps

1. **Execution semantics:** Phoenix rolls program state back and re-executes a controlled region. P4 does not roll back the program's call stack; it retains a particular event slot as non-executable and makes a scheduler decision about other queued events. Adapting one model to the other requires semantic redesign, not just renaming a queue.
2. **Quarantine representation:** IBM explicitly removes an event from one queue and inserts it into another. P4's frozen contract keeps the same EventSlot record in the fixed pool and changes its lifecycle/executability. The sources do not prescribe that in-place lifecycle.
3. **Memory model:** QP's caller-supplied static buffer bounds the pool, but mutable event blocks are allocated/recycled within it. P4 instead uses a fixed array of EventSlot records and does not dynamically allocate/recycle event blocks. A no-pool-allocation configuration or separate static-event design could be chosen, but the reviewed QP pages do not prescribe P4's exact arrangement.
4. **Dependency contract:** Phoenix is a serious conceptual attack because it already distinguishes dependent and unrelated peripheral accesses. However, the inspected teaching is expressed through rollback/redo and peripheral dependencies, not the explicit P4 queue dependency classes (EVENT_DEP_NONE/FIFO/CAUSAL/DOMAIN) and is_dispatchable(event) predicate.
5. **Association precision:** None of these sources, as inspected, discloses the complete EXACT/SERVICE/PERIPHERAL/UNKNOWN lattice with the invariant assoc <= evidence and fail-closed handling when no safe event target exists.
6. **Recovery sequence and episode lifecycle:** The sources contain recovery, retry, corrective action and monitoring, but do not expressly supply P4's exact fixed four-rung sequence, generation-qualified EventRef rejection, and explicit episode terminal closure/escalation as one contract.

### C1 assessment

**Combination risk: HIGH.** This is the strongest attack because all three sources are close to important parts of the intended mechanism, and a rationale for combining them is readily expressible. It would be incorrect to dismiss C1 merely because the references originate in different domains.

**Complete L1–L12 combination: NOT ESTABLISHED by the inspected sources.** The combination still requires meaningful design choices for evidence-bounded association, generation-qualified identity, same-slot in-pool quarantine, queue-level dispatchability, exact bounded recovery progression, fail-closed handling and authoritative episode closure. These gaps preserve a technical distinction hypothesis, but they do not establish legal non-obviousness; an examiner or reviewer could argue that the adaptations are routine engineering choices. The evidence here does not settle that legal question.

## 5. Combination C2 — Trane recovery thresholds + Dell/Intel device/link containment

### Strongest combination argument

Trane contributes fault-related restart/restore counters and thresholds. Dell and Intel contribute hardware/driver-level error containment, link recovery and OS/VMM coordination. A plausible engineering rationale is to combine a thresholded recovery policy with a platform-level way to isolate and recover a failing peripheral or driver.

### What the sources actually supply

- Trane Claims 1–9 describe a restart/restore counter and threshold that select normal boot or recovery boot/restore behavior for BAS/HVAC control components.
- Dell Claim 1 disables the PCIe data link and changes presence state to trigger OS driver removal; Claim 2 later changes presence state to trigger driver installation.
- Intel Claims 1 and 4 describe notifying the OS/VMM and creating an error-containment record; other claims describe driver/OS-directed link recovery.

### Technical friction and missing steps

- The sources primarily operate at controller/driver, bootloader, OS/VMM or storage-partition level, not at an event-slot lifecycle inside a cooperative MCU scheduler.
- Trane's restart counter is a temporal restart threshold; it does not establish a short per-fault-episode history selecting P4's T1 retry, T2 retry, T3 reinitialization/reset, and T4 terminal outcome.
- Dell's link toggling and driver reinstallation are platform-specific PCIe operations, not portable I2C/SPI event recovery semantics.
- Intel's error-containment record identifies a port/device and recovery directive, but does not establish the evidence-precision lattice for mapping a fault to a specific queued event.
- None of these sources specifies generation-qualified EventRef identity, same-slot event quarantine, dependency dispatchability, or the complete L1–L12 integration.

### C2 assessment

**Combination risk: MODERATE for generic history-conditioned device recovery; LOW-to-MODERATE for the full P4 event-runtime contract.** The combination supports the proposition that counters, thresholds, isolation, recovery and verification are established techniques. It is a less direct route to P4 than C1 because additional event-level scheduling and identity semantics would need to be introduced. This is a technical-distance assessment, not a legal conclusion.

## 6. Combination C3 — NetApp peripheral recovery + IBM event failure management

### Strongest combination argument

NetApp supplies isolation of a failed peripheral, failover of operations to a backup peripheral, driver recovery/reinitialization and return of operations after recovery. IBM PA-07 supplies event/resource association, retry when a component/resource changes, outcome-based failure-record updates and optional message quarantine. A reasonable attack is that a designer could connect event failure records and quarantine with a known peripheral recovery routine, thereby retrying previously failed work after its associated device/resource is recovered.

### What the sources actually supply

- NetApp Claim 1 explicitly isolates the peripheral, migrates operations to a backup, calls recovery and reinitialization routines, receives recovery/reinitialization result codes, and migrates operations back.
- IBM PA-07 Claim 1 provides a failed-event database associating failures with components/resources, retries after resource modification, and updates records based on retry outcomes. Claim 6 expressly permits message quarantine; Claims 4 and 10 describe tracking retry outcomes.
- The combination is stronger than a generic “recovery is known” argument because it brings together component association, event failure handling, retry and peripheral recovery.

### Technical friction and missing steps

- NetApp's mechanism is a server/storage failover architecture with backup peripherals and OS/device-driver recovery domains. IBM's mechanism is a distributed event-management database and message-handling layer. Neither source supplies the MCU's bounded event-slot data model.
- IBM's component/resource association is not the same as P4's explicit evidence-precision levels and fail-closed invariant. The inspected claims do not establish the rule that association precision cannot exceed evidence precision.
- Message quarantine is not expressly the same as retaining the original event record in its original fixed slot with a generation-qualified identity.
- The combination does not establish dependency-class dispatchability or selective eligibility of independent queued work.
- Retry counts and result monitoring are relevant to recovery history, but they do not establish the exact fixed four-rung P4 ladder and its terminal closure rules.

### C3 assessment

**Combination risk: MODERATE-to-HIGH for event/resource association plus recovery/quarantine; MODERATE for the complete P4 contract.** C3 is a serious attack on broad claims around event failure association, retry, quarantine and device recovery. It does not establish the full set of constrained-runtime invariants in the inspected materials. The remaining difference is more specific than “combine events with peripheral recovery,” and must be described that narrowly.

## 7. Cross-combination L1–L12 coverage matrix

Legend: **E** = explicitly supplied by an inspected source in the combination; **P** = partial/conceptual overlap; **N** = not established by the inspected combination. These are technical mappings, not legal claim constructions.

| Limitation | C1: Phoenix + IBM PA-08 + QP/C | C2: Trane + Dell/Intel | C3: NetApp + IBM PA-07 |
|---|---|---|---|
| L1 Resource-constrained event-driven MCU setting | **E/P** — Phoenix supplies the MCU/event-driven setting; the combination as a whole spans unlike architectures | N | N |
| L2 Fixed-capacity zero-heap state | P — QP static backing is bounded, but event blocks can be dynamically allocated/recycled; Phoenix uses heap-backed state | N | N |
| L3 Evidence-bounded association, assoc <= evidence | N | P — device/port or component identity exists, but not the precision lattice | P — component/resource mapping, no evidence-precision invariant |
| L4 Generation-qualified EventRef | N | N | N |
| L5 Same-slot in-pool non-executable quarantine | P — failed-event queue/quarantine analogue, but IBM moves to a different queue | N | P — IBM message quarantine, but no same-slot lifecycle |
| L6 Dependency-aware queue dispatchability | P — Phoenix dependency-aware redo/rematerialization is strong overlap; explicit P4 queue predicate not supplied | N/P — service isolation, not queue dependency classes | P — preventing processing by associated resource, no dependency predicate |
| L7 Short history changes action selection | P — retry/corrective-action monitoring, but no exact P4 history rule | P — restart/restore counters and thresholds | P — retry after component change and failure records |
| L8 Fixed four-rung finite recovery ladder | P — recovery/replay exists, exact ladder absent | P — normal/recovery boot threshold, not P4 ladder | P — recovery/reinitialization/retry, exact ladder absent |
| L9 Verification before release and episode closure | P — replay is monitored, but no P4 episode-closure contract | P — reinstallation/recovery coordination, not event episode closure | P — return after recovery and retry outcomes, not P4 episode closure |
| L10 Fail-closed handling of ambiguous association | N | N | N |
| L11 Deterministic trace across fault, episode, action and outcome | P — failure metadata/replay records exist, not the complete deterministic trace contract | P — error/recovery records, not the full trace contract | P — event database records, not the full trace contract |
| L12 One bounded runtime with sole policy/transition authorities | N | N | N |

## 8. Overall threat ranking and bounded conclusion

1. **C1 — HIGH combination risk.** The strongest technical attack. Phoenix already has peripheral recovery and dependency-aware replay; IBM PA-08 has failed-event movement, corrective action and replay; QP/C has a deterministic fixed-block pool backed by supplied storage. The combination could be argued to provide a natural starting point for a bounded event recovery design. The exact P4 state/association/scheduler contracts remain not established by the inspected teachings.
2. **C3 — MODERATE-to-HIGH combination risk.** Strong for component/resource association, event failure handling, retry, quarantine and peripheral recovery. The same-slot bounded lifecycle, precision lattice and dependency predicate remain absent from the inspected combination.
3. **C2 — MODERATE generic recovery risk, lower direct P4 fit.** Thresholded recovery and device/link containment are established, but the combination is less directly tied to event-level MCU queue semantics.

### What can be said

- Recovery/reset, fault containment, retry thresholds, event/message quarantine, resource association, replay, dependency-aware selective recovery, static pool backing and bounded allocation are established ingredients in adjacent systems.
- The most credible threat is an integrated combination of those ingredients, not a single reference.
- The proposed technical distinction, if any, must be framed around the exact interaction of conservative evidence-bounded association, generation-qualified identity, retained same-slot quarantine, queue-level dependency dispatchability, fixed bounded recovery progression and explicit closure/trace—not around any one ingredient alone.
- The inspected combinations do not themselves establish every L1–L12 contract, but the required adaptations may be argued to be routine. The present analysis cannot settle that legal/technical dispute.
- K.10's software evidence demonstrates only bounded host/reference behavior and trade-offs; it does not establish physical MCU behavior or prove novelty.

### Final bounded conclusion

> The inspected multi-reference combinations create a substantial technical-combination risk for the broad P4 concept. C1 is the strongest attack, followed by C3 and then C2. The reviewed source texts do not explicitly supply the complete L1–L12 integration as one mechanism, but the remaining differences are narrow and may be characterized by an opposing reviewer as engineering adaptations. Therefore the integrated technical distinction remains unresolved and vulnerable; no conclusion on legal obviousness, non-obviousness, novelty, or patentability is made.

## 9. Unresolved evidence and K.10.4 handoff

- This is a bounded source-level combination analysis, not a global exhaustive search of every patent family, academic paper, standards version, RTOS implementation or open-source commit.
- Additional work may be needed to test whether an event-driven MCU implementation combining these known patterns exists in an implementation or documentation not inspected here.
- The exact boundary between ordinary engineering adaptation and a technically nontrivial integrated contract requires further evidence and, for legal questions, qualified patent counsel.
- K.10.4 must integrate the actual K.10 results, K.10.1 limitation decomposition, K.10.2 single-reference findings and this K.10.3 combination analysis. It must present both advantages and baseline wins/trade-offs, avoid a composite score, distinguish host evidence from hardware evidence, and state what remains unresolved.
- Do not modify the runtime or repeat experiments in K.10.4. Do not sync main until the final approved sequence permits it.

## 10. Integrity and governance

- K.10 experiment matrix: frozen; zero reruns in this checkpoint.
- Gates A–E, protected runtime/header and normative design artifacts: frozen.
- main: untouched.
- This checkpoint's report and chat record are documentation-only artifacts.
- K.10.3 status remains subject to ChatGPT's explicit closure decision; K.10.4 must not start until that approval is recorded.
