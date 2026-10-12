# K.10.2 — Deep Single-Reference Anticipation Review (Evidence-Corrected)

**Status:** Complete at the single-reference level; single-reference anticipation **refuted** across all inspected primary candidates; technical distinction remains **unresolved and vulnerable to multi-reference combination (K.10.3)**.  
**Branch:** `exp`  
**Base Commit:** `7a5bcb099be66f55cc0a18acfe51af79413ddf68` (Starting HEAD: `51d351655d5b802f2f19437424fa04a7d5e61422`)  
**Scope:** Technical research analysis only; not a legal opinion or patentability assessment.  
**K.10 Evidence Baseline:** Frozen (16 Case Families × P0–P4 × 5 deterministic repetitions = 400 matched executions).  
**Protected Boundaries:** Gates A–E, `reference/src/ref_runtime.c`, and `reference/include/ref_runtime.h` 100% untouched.

---

## 1. Executive Summary & Core Objective

The objective of **K.10.2** is strictly bounded:
> Determine whether any single reference, considered individually across its verified disclosure and claims, anticipates or materially discloses the complete candidate combination of the proposed P4 runtime mechanism (limitations L1 through L12).

### Bounded Conclusion
> **"No single reference in the inspected candidate set was found to disclose the complete L1–L12 combination, based on the reviewed evidence."**

This review does not assert universal absence of anticipating prior art across all existing literature, nor does it assert legal novelty, patentability, or legal non-obviousness.

Prior art separates into two distinct clusters:
1. **Embedded / Low-Level Recovery Cluster (PA-01, PA-02, PA-03, PA-04, PA-06, PA-10):**
   Addresses embedded peripheral recovery or driver crash containment, but relies fundamentally on **thread checkpointing, call-stack rollback, register redo-logging, MMU address space virtualization, or coarse subsystem power cycling**. None discloses in-pool event-level quarantine within a static zero-heap event array without execution rollback.
2. **Enterprise & Cloud Message Processing Cluster (PA-05, PA-07, PA-08, PA-09):**
   Discloses failed-event queues, component-failure associations, error holding, and retry/verification/release. However, all operate on **application servers, separate queue instantiations, or external databases**, unconstrained by bare-metal MCU timing and static memory contracts.

The candidate distinction therefore survives single-reference anticipation within the inspected candidate set. However, it remains **vulnerable to a multi-reference combination attack (obviousness under 35 U.S.C. § 103)** combining an embedded driver reset mechanism (e.g. Phoenix) with an enterprise failed-event queue paradigm (e.g. IBM). This combination attack is formally assigned to **K.10.3**.

---

## 2. P4 Limitation Reference Anchor (L1–L12)

As codified in `research/phase2_k10_1_adversarial_distinction_review.md`, the 12 limitations comprising the candidate combination are:

* **L1:** Resource-constrained event-driven MCU setting (single address space without MMU; Cortex-M bare metal represents the illustrative target architecture).
* **L2:** Fixed-capacity, zero-heap state (static allocation; no `malloc`/`free`; bounded queue arrays; no dynamic pool recycling).
* **L3:** Fault-to-event association has explicit precision levels and cannot exceed evidence precision (`assoc <= evidence`; levels: EXACT, SERVICE, PERIPHERAL, UNKNOWN; Gate B contract).
* **L4:** Event identity is generation-qualified; stale references are rejected (`EventRef={slot_id, generation}`).
* **L5:** Fault-associated event is quarantined/retained in-pool rather than indiscriminately flushing all queued work (retained non-executable state in original static pool).
* **L6:** Independent work remains eligible while related/ordered/coupled work is blocked (queue-level dependency classes and dispatchability predicate; Gate A/D contract).
* **L7:** Short recovery history changes action selection (history/episode attributes condition next action).
* **L8:** Fixed ladder has an expressly disclosed fixed sequence with a finite terminal rung (Gate C: T1 retry $\to$ T2 retry $\to$ T3 reset $\to$ T4 terminal; `MAX_RECOVERY_ACTIONS=4`).
* **L9:** Verification precedes release/continuation; failed recovery closes/escalates explicitly (runtime retains transition authority; Gates C/D contract).
* **L10:** No fabricated target `EventRef` for service/peripheral/unknown association (fail-closed association contract).
* **L11:** Deterministic trace ties fault, association, action, episode, lifecycle and outcome (structured event audit trace).
* **L12:** Entire mechanism is a single bounded C runtime with decoupled policy and transition authorities (`policy_decide()` vs `runtime_apply_policy()`).

---

## 3. Methodological Clarifications on Limitation Semantics

To preserve strict evidentiary integrity:

### 3.1. Evidence-Bounded Association Semantics (L3)
A generic association between a failure and a component ID, software flow ID, or downstream endpoint (as found in PA-07, PA-08, PA-09) does **not** establish L3. L3 strictly requires:
- An explicit multi-tier association precision lattice (e.g., EXACT, SERVICE, PERIPHERAL, UNKNOWN); and
- The normative fail-closed invariant that **association precision cannot exceed evidence precision** (`association <= evidence`), preventing synthetic target generation during ambiguous fault scenarios.
Where a reference associates failures with components or flows, this is documented as partial conceptual overlap, but the complete limitation is classified as **NOT FOUND IN INSPECTED MATERIAL**.

### 3.2. Verification Before Release Semantics (L9)
L9 is not satisfied merely because a system records a retry result, updates a database status, or polls a hardware register. L9 strictly requires:
- An **explicit runtime verification gate** that validates recovery success before quarantined work is released for execution; and
- A runtime architecture where **failed recovery deterministically closes the episode or escalates to terminal action**, with the runtime retaining sole state transition authority.
General hardware readiness polling (Phoenix, Karma) or retry-result logging (IBM) represents partial conceptual overlap, but the complete L9 contract is classified as **NOT FOUND IN INSPECTED MATERIAL** (or **UNVERIFIED** where claims were not rendered).

### 3.3. Memory Allocation Terminology & Quantum Leaps QP (L2)
We distinguish three distinct memory management models:
1. **General-Purpose Heap Allocation:** Unconstrained dynamic allocation (`malloc()` / `free()`) prone to heap fragmentation and non-deterministic execution times.
2. **Preallocated Static Pools with Dynamic Block Allocation (Quantum Leaps QP `QMPool`):** Memory is preallocated in static buffer storage to eliminate heap fragmentation. However, event blocks are *dynamically allocated from and recycled back into the pool* at runtime via `Q_NEW()` and reference-counted garbage collection (`QF_gc()`).
3. **Fixed-Slot Static Array Contract (P4 `EventSlot[20]`):** Events are admitted directly into pre-indexed static slots. Each event *remains bound to its assigned static slot throughout its entire lifecycle* (admission, dispatch, in-pool non-executable quarantine, and terminal release). There is no dynamic pool allocation, no block recycling, and no reference counting.

### 3.4. In-Pool Quarantine vs. External Holding (L5)
We strictly distinguish:
- **In-pool non-executable retention (P4 contract):** The failed event remains in its assigned slot within the fixed-capacity event array as non-executable, preserving its slot identity without queue reallocation or data movement.
- **Secondary queue movement (e.g. IBM PA-08):** Deleting or extracting an event from an active queue and inserting it into a separate failed-event queue (FEQ) or dead-letter queue.
- **Database persistence (e.g. IBM PA-07):** Writing failed event records to an external relational/NoSQL table.
Only the first mechanism satisfies L5.

### 3.5. Resource-Constrained Event-Driven MCU Setting Semantics (L1)
As anchored in the frozen project topic and K.10.1 limitation matrix, L1 specifies a **resource-constrained event-driven MCU setting** (bare-metal microcontroller operating in a single physical address space without MMU, running an event-driven runtime architecture with an asynchronous event loop).
- **Illustrative Target Architecture vs. Mandatory Limitation:** Bare-metal ARM Cortex-M (specifically Cortex-M33 / STM32U575) is the repository's illustrative target platform and frozen reference platform direction, rather than an exclusive ISA restriction that would disregard an otherwise identical event-driven MCU runtime on another resource-constrained MCU architecture (e.g. RISC-V or MSP430).
- **Exact Architectural Correspondence vs. General Relevance:** However, to satisfy L1, a reference must disclose the actual elements established by primary evidence:
  - References evaluated on bare-metal Cortex-M microcontrollers (e.g. Phoenix, PA-01) establish *exact architectural correspondence* to the target MCU setting.
  - References evaluated on alternative microcontrollers (e.g. MSP430 in Karma, PA-02) establish *general MCU relevance*, but do not disclose Cortex-M architecture or an event-driven runtime architecture (Karma checkpoints sequential/threaded execution across energy outages).
  - References describing building automation equipment (e.g. Trane, PA-06) disclose commercial HVAC control devices (general embedded controller relevance), but do not disclose Cortex-M bare-metal microcontrollers or a resource-constrained event-driven MCU runtime.
Where a reference provides general MCU or embedded controller relevance without disclosing the complete resource-constrained event-driven MCU setting, this is documented as partial conceptual overlap, but the limitation is classified as **NOT FOUND IN INSPECTED MATERIAL**.

### 3.6. Queue Dependency Classes & Dispatchability Predicate Semantics (L6)
L6 strictly requires that independent work can remain eligible while related, ordered, or coupled work is blocked. As anchored in Gate A/D and implemented in `ref_runtime.c`, this requires:
- Explicit queue-level dependency classes (e.g. `EVENT_DEP_NONE`, `EVENT_DEP_FIFO`, `EVENT_DEP_CAUSAL`, `EVENT_DEP_DOMAIN`); and
- An event queue dispatchability predicate (`is_dispatchable(event)`) evaluated by the scheduler to hold dependent work while dispatching independent events from the shared pool.
Macroscopic OS process isolation (e.g. Nooks/MINIX 3 in PA-10), where independent user processes or driver processes continue running in separate address spaces via hardware MMU page tables and multi-threaded kernel scheduling across a driver crash, provides *partial conceptual overlap* with the principle of fault containment, but does **not** disclose queue-level dependency classes or dispatchability predicates. The complete limitation is classified as **NOT FOUND IN INSPECTED MATERIAL**.

---

## 4. Audited Primary Sources & Evidence Locators

Every candidate reference was evaluated at primary-source level:

### 4.1. PA-01: Phoenix (Smith & Rixner, USENIX ATC 2015)
* **Citation:** Rebecca Smith and Scott Rixner, *"Surviving Peripheral Failures in Embedded Systems,"* Proceedings of the 2015 USENIX Annual Technical Conference (USENIX ATC '15), Santa Clara, CA, July 8–10, 2015, pp. 125–137.
* **Primary URL:** `https://www.usenix.org/conference/atc15/technical-session/presentation/smith`
* **Architecture & Domain:** Bare-metal ARM Cortex-M microcontrollers (Stellaris LM3S8962, TI CC2538).
* **Mechanism:** Checkpoints program state at safe transaction boundaries, logs peripheral register writes in a circular redo log, detects peripheral stalls via hardware timers/interrupts, resets the peripheral controller, replays register logs, and **rolls back the CPU call stack to the checkpoint** to restart the failed transaction.
* **Limitation Mapping & Locators:**
  * **L1 (resource-constrained event-driven MCU setting):** **[EXPLICITLY DISCLOSED]** (Section 1, pp. 125–126 describes embedded systems as event-driven; Section 3, pp. 128–129 identifies Owl as an embedded runtime with a Python bytecode interpreter running bare-metal; Section 6.2, p. 134 describes an evaluated application whose event loop controls the car's movements. This supports the L1 *setting*. It does not establish P4's separate queue-level dependency dispatchability, retained in-pool quarantine, or evidence-bounded association limitations, which are assessed under L3–L6 and L10).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (Section 5.3 "Memory Overhead", p. 133; requires ~6 KB RAM for dynamic shadow stacks, redo logs, and checkpoint buffers; not a fixed static-pool queue architecture).
  * **L3 (Evidence-bounded association):** **[NOT FOUND IN INSPECTED MATERIAL]** (Associates faults with currently executing driver thread context; no 4-tier precision lattice).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Operates on thread execution contexts, not generation-qualified `EventRef` handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Rolls back the CPU call stack to transaction boundary; does not retain failed events non-executably in-pool).
  * **L6 (Dependency-aware preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Calling task is suspended/rewound; independent RTOS tasks continue only via standard OS scheduling).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Static reset-and-replay policy; no history-conditioned action adaptation).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses retry/timeout counters, but lacks an expressly disclosed fixed sequence with finite terminal rung).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Section 3.2 "Recovery", p. 128, and Section 4.2 "Peripheral Reset and Replay", p. 130; polls peripheral status register until ready before resuming thread execution; however, does not disclose event episode lifecycle closure or escalation authority).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Phoenix addresses embedded MCU peripheral recovery, but relies fundamentally on **checkpointing, execution stack rollback, and redo logging**, incurring substantial RAM overhead. It does not disclose event-boundary quarantine or zero-heap static scheduling.

---

### 4.2. PA-02: Karma (Branco et al., ACM SenSys 2019)
* **Citation:** Arthur S. R. Branco, Luca Mottola, Muhammad Hamad Alizai, Junaid Haroon Siddiqui, *"Intermittent Asynchronous Peripheral Operations,"* Proceedings of the 17th ACM Conference on Embedded Networked Sensor Systems (SenSys '19), New York, NY, Nov 2019, pp. 248–261.
* **Primary URL:** `https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf`
* **Architecture & Domain:** Intermittently powered energy-harvesting microcontrollers (TI MSP430 with FRAM).
* **Mechanism:** Manages peripheral operations across power failures by recording non-volatile operation descriptors in FRAM, rolling forward completed hardware operations, and rolling back uncommitted computation tasks upon power restoration.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[NOT FOUND IN INSPECTED MATERIAL]** (Section 1 and Section 5, pp. 248, 254; evaluated on Texas Instruments MSP430FR5969 microcontrollers. While MSP430 provides *general MCU relevance* as a resource-constrained microcontroller, it lacks exact architectural correspondence with the Cortex-M bare-metal target, and Karma's intermittent computing runtime checkpoints sequential/threaded execution across power outages rather than providing an event-driven MCU runtime).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (Allocates NVRAM descriptors for intermittent peripheral operations, but does not disclose a fixed-capacity zero-heap event runtime queue contract).
  * **L3–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Addresses power failures, not runtime peripheral faults; no fault association lattice or in-pool event quarantine).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Manages operation completion ordering across reboots, but does not disclose queue dependency classes or eligibility predicates).
  * **L7–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (No history-driven recovery action selection; deterministic roll-forward/rollback).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Section 3.3, p. 252; verifies peripheral ready status before releasing tasks; does not disclose event-level verification or episode closure/escalation).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Solves power-intermittency consistency, not runtime peripheral fault recovery, event quarantine, or association ambiguity.

---

### 4.3. PA-03: US 9,547,557 B2 (Dell / Bolen)
* **Citation:** Austin P. Bolen, *"Peripheral bus error containment and recovery,"* US Patent 9,547,557 B2, assigned to Dell Products LP. Filed: Nov 10, 2014; Issued: Jan 17, 2017.
* **Primary URL:** `https://patents.google.com/patent/US9547557B2/en`
* **Architecture & Domain:** Enterprise Information Handling Systems / PCIe servers (PCIe root ports, OS device drivers).
* **Mechanism:** Fatal bus error detected at downstream PCIe port $\to$ deactivates data link layer $\to$ triggers OS hot-plug service to uninstall device driver without OS crash $\to$ reactivates link $\to$ reinstalls driver without physical removal.
* **Limitation Mapping & Locators:**
  * **L1–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (Server architecture with PCIe bus, ACPI, and full OS memory; lacks event queues, zero-heap constraints, and ladder policies).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Abstract, lines 19–22, and Claim 1; data link layer training precedes driver reinstallation, but does not disclose an explicit runtime verification gate preceding event release or episode escalation).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Hardware/driver hot-plug error containment for enterprise servers.

---

### 4.4. PA-04: US 9,411,667 B2 (Intel / Jayakumar et al.)
* **Citation:** Sarathy Jayakumar, Mohan J. Kumar, Jose A. Vargas, *"Recovery after input/ouput error-containment events,"* US Patent 9,411,667 B2, assigned to Intel Corp. PCT Filed: Jun 6, 2012; Issued: Aug 9, 2016.
* **Primary URL:** `https://patents.google.com/patent/US9411667B2/en`
* **Architecture & Domain:** Computing devices with PCIe and virtual machine monitors (VMM/hypervisors).
* **Mechanism:** Platform interrupt handler isolates an I/O link upon error containment event, generates error record, notifies OS/VMM, and recovers link upon directive.
* **Limitation Mapping & Locators:**
  * **L1–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (Server hypervisor/PCIe hardware architecture; lacks MCU event queue concepts).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Platform entity facilitates link recovery before notifying OS/VMM; does not disclose event runtime verification or closure/escalation authority).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** PCIe root port isolation for hypervisors.

---

### 4.5. PA-05: US 8,510,592 B1 (NetApp / Chan)
* **Citation:** Johnny Kang-wing Chan, *"PCI error resilience,"* US Patent 8,510,592 B1, assigned to NetApp Inc. Filed: Sep 15, 2009; Issued: Aug 13, 2013.
* **Primary URL:** `https://patents.google.com/patent/US8510592B1/en`
* **Architecture & Domain:** Enterprise storage servers (NetApp Data ONTAP appliances).
* **Mechanism:** Detects error in peripheral adapter (HBA/NIC), isolates adapter to suppress interrupt storms, migrates active operations to a backup adapter, calls driver recovery and reinitialization routines, verifies device, and migrates operations back.
* **Limitation Mapping & Locators:**
  * **L1–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Storage server appliances; migrates operations to redundant hardware rather than in-pool quarantine).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses redundant physical backup hardware to continue I/O, not queue dependency scheduling).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Distinguishes recoverable vs unrecoverable errors, but does not disclose short episode history conditioning next action).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Calls recovery and reinitialization routines, but does not disclose an expressly disclosed fixed sequence with a finite terminal rung).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Abstract, lines 19–21; verifies device recovery before migrating traffic back, but does not disclose event episode verification and escalation authority).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Enterprise storage server failover to redundant hardware; lacks MCU constraints, zero-heap event queues, and in-pool event quarantine.

---

### 4.6. PA-06: US 10,921,871 B2 (Trane / Basterash et al.)
* **Citation:** Thomas Christopher Basterash, Mark Martin, Udhaya Kumar Dayalan, *"BAS/HVAC control device automatic failure recovery,"* US Patent 10,921,871 B2, assigned to Trane International Inc. Filed: May 17, 2019; Issued: Feb 16, 2021.
* **Primary URL:** `https://patents.google.com/patent/US10921871B2/en`
* **Architecture & Domain:** Building Automation Systems (BAS) and HVAC embedded controllers.
* **Mechanism:** Monitors component health (sensors, actuators, firmware modules) in building automation controllers. Selects recovery actions to repair software/firmware or hardware faults.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[NOT FOUND IN INSPECTED MATERIAL]** (Abstract, lines 19–21; describes BAS and HVAC control devices. While building automation equipment utilizes embedded controllers [general embedded controller relevance], the patent specification does not disclose ARM Cortex-M bare metal or a resource-constrained event-driven MCU runtime architecture).
  * **L2–L6:** **[NOT FOUND IN INSPECTED MATERIAL]** (Manages macroscopic physical equipment modules; no event queue, in-pool quarantine, or queue dependency scheduling).
  * **L7 (History changes action selection):** **[UNVERIFIED / INACCESSIBLE AT CLAIM LEVEL]** (Reported in repository notes to use failure history logs, but full claim text was not rendered in static scrape; not established from abstract alone).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Does not disclose an expressly disclosed fixed sequence with finite terminal rung).
  * **L9 (Verification precedes release):** **[UNVERIFIED / INACCESSIBLE AT CLAIM LEVEL]** (Abstract mentions automated repair; claim-level verification step not rendered in static scrape).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Operates at macroscopic equipment/firmware subsystem level, not microsecond event queue transactions.

---

### 4.7. PA-07: US 10,331,522 B2 & US 10,929,373 B2 (IBM / Allman et al.)
* **Citation:** Mark Allman, Andrew S. Edwards, Philip Jones, Doina L. Klinger, Martin A. Ross, Paul S. Thorpe, *"Event failure management,"* US Patent 10,331,522 B2 (Filed: Mar 17, 2017; Issued: Jun 25, 2019) and continuation US Patent 10,929,373 B2 (Filed: May 7, 2019; Issued: Feb 23, 2021), assigned to IBM Corp.
* **Primary URL:** `https://patents.google.com/patent/US10331522B2/en`
* **Architecture & Domain:** Enterprise message brokers and Business Process Management (BPM) middleware.
* **Mechanism:** Failed Event Database (FEDB) stores failed event payloads and associated failing component IDs. When a component is modified/restored, matching failed events are retried and the database is updated.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[NOT FOUND IN INSPECTED MATERIAL]** (Enterprise event management facility).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (The patent claims do not specify a zero-heap static state contract).
  * **L3 (Evidence-bounded association):** **[NOT FOUND IN INSPECTED MATERIAL]** (Abstract, lines 19–21; describes a "failed event database containing failed event information relating to failed events and one or more components associated with each of the failed events". While this provides *partial conceptual overlap* by associating events with failing component IDs, it does **not** disclose explicit association precision levels or the fail-closed invariant `assoc <= evidence`).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses database primary keys/records, not generation ring handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Events are stored in an external "failed event database", not retained in their original fixed-capacity queue pool as non-executable).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Does not disclose queue-level dependency classes or dispatchability predicates).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Updates database based on retry results, but does not disclose short episode history conditioning next action).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Retries failed events upon component modification; lacks an expressly disclosed fixed sequence with finite terminal rung).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Abstract, lines 20–22; "Based on a result of retrying the failed event, failed event information of the failed event database is updated". Recording retry outcomes in a database updates records, but does **not** disclose an explicit runtime verification gate preceding event release or episode closure/escalation authority).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Enterprise database-backed failed event management; lacks zero-heap MCU runtime constraints, evidence-bounded association lattice, and in-pool queue retention.

---

### 4.8. PA-08: US 10,838,845 B2 / US 2018/0365126 A1 (IBM / Edwards et al.)
* **Citation:** Andrew S. M. Edwards, Doina L. Klinger, Martin A. Ross, Paul S. M. Thorpe, *"Processing failed events on an application server,"* US Patent 10,838,845 B2 (pre-grant publication US 2018/0365126 A1), assigned to IBM Corp. Filed: Jun 14, 2017; Issued: Nov 17, 2020.
* **Primary URL:** `https://patents.google.com/patent/US10838845B2/en`
* **Architecture & Domain:** Enterprise application servers (IBM WebSphere).
* **Mechanism:** When an event fails in an application flow, the server **deletes the event from the main event queue** and inserts it into a separate **Failed Event Queue (FEQ)** with linked failure reasons. Replay occurs after corrective action.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[NOT FOUND IN INSPECTED MATERIAL]** (Specifies an application server).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (Does not specify zero-heap static allocation).
  * **L3 (Evidence-bounded association):** **[NOT FOUND IN INSPECTED MATERIAL]** (Abstract, lines 20–22; links failed events to related application flow IDs and failure reasons. While this provides *partial conceptual overlap* by mapping failures to flow IDs, it does **not** disclose explicit precision levels or the fail-closed rule `assoc <= evidence`).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses flow IDs, not generation ring handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Expressly discloses **"deletes the event... from the event queue, then inserts... into a failed event queue"**; moving an event to a secondary queue does not satisfy in-pool non-executable retention in the original fixed pool).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Unrelated flows continue processing, but does not claim queue-level dependency classes or dispatchability predicates).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Links failure reasons, but does not disclose history-driven action selection).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Moves event to FEQ upon failure; lacks an expressly disclosed fixed sequence with finite terminal rung).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Discloses replaying from FEQ after administrative or corrective intervention, but does not disclose a runtime verification gate preceding release or failed-recovery closure/escalation).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Primary art for failed event queues, but relies on separate queue creation and event deletion/re-insertion, not in-pool static array retention on an MCU.

---

### 4.9. PA-09: US 12,688,084 B2 (Oracle / Muthulankkat & Paulsami)
* **Citation:** Mahesh Muthulankkat, Prabakar Paulsami, *"Intelligent data flow control valve,"* US Patent 12,688,084 B2, assigned to Oracle International Corp. Filed: Sep 30, 2024; Issued: Jul 21, 2026.
* **Architecture & Domain:** Cloud integration middleware and enterprise data streaming pipelines.
* **Mechanism:** Monitors activity stream; on recoverable downstream endpoint error, instructs upstream system to pause transmission; resumes upon error resolution.
* **Limitation Mapping & Locators:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Cloud platform middleware).
  * **L3 (Association):** **[NOT FOUND IN INSPECTED MATERIAL]** (Identifies recoverable downstream error for an integration stream. Provides *partial conceptual overlap* by associating errors with downstream endpoints, but lacks an explicit multi-tier precision lattice and fail-closed evidence-bounded invariant).
  * **L4–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (Pauses entire upstream stream; no in-pool quarantine or fixed ladder).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Monitors activity stream until error resolution before resuming transmission; stream-level flow control does not disclose an event runtime verification gate or episode closure/escalation authority).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** High-level stream pause-and-resume valve in cloud integration; lacks embedded queue mechanisms.

---

### 4.10. PA-10: Swift et al. (OSDI 2004) & Herder et al. (DSN 2006 / MINIX 3)
* **Citation:** 
  * Michael M. Swift, Muthukaruppan Annamalai, Brian N. Bershad, Henry M. Levy, *"Recovering Device Drivers,"* Proceedings of the 6th USENIX OSDI, 2004.
  * Jorrit N. Herder, Herbert Bos, Ben Gras, Philip Homburg, Andrew S. Tanenbaum, *"Failure Resilience for Device Drivers,"* Proceedings of the 36th IEEE/IFIP DSN, 2006.
* **Architecture & Domain:** General-purpose OS kernels (Linux, MINIX 3) on MMU-equipped hardware (x86).
* **Mechanism:** Isolates device drivers into user-space processes (MINIX 3) or hardware page-table domains (Nooks). Shadow drivers / Reincarnation Servers detect driver crash, restart the driver process, replay state, and unblock held I/O requests.
* **Limitation Mapping & Locators:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Requires MMU page tables, separate address spaces, and heavy dynamic kernel structures).
  * **L3–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Process-level crash containment; buffering incoming I/O packets in shadow driver wrapper during driver restart is I/O buffering, not in-pool non-executable retention in a fixed-capacity event queue).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Swift et al., Section 4, pp. 6–7: non-crashing drivers and unrelated applications continue execution; Herder et al., Section 3, pp. 3–4: isolated user-space processes prevent cascading failures. While this provides *partial conceptual overlap* with fault containment via MMU hardware protection domains or microkernel process scheduling, it does **not** disclose queue-level dependency classes [e.g. `EVENT_DEP_NONE`, `EVENT_DEP_FIFO`, `EVENT_DEP_CAUSAL`, `EVENT_DEP_DOMAIN`] or an event queue dispatchability predicate [Gate A/D contract]).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Standard restart policy).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Discloses restart attempt threshold, but lacks an expressly disclosed fixed sequence with finite terminal rung).
  * **L9 (Verification precedes release):** **[NOT FOUND IN INSPECTED MATERIAL]** (Swift et al., Section 4.3; verifies driver reinitialization handshake before releasing held I/O; does not disclose event episode verification, runtime transition authority, or failed-recovery closure/escalation).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Relies on MMU hardware memory protection and multi-process/shadow virtualization.

---

## 5. Master Limitation-by-Reference Anticipation Matrix (Evidence-Corrected)

| Ref ID | Primary Reference | Target Domain | L1 (MCU) | L2 (ZeroHeap) | L3 (Assoc) | L4 (GenRef) | L5 (InPoolQuaran) | L6 (DepPres) | L7 (Hist) | L8 (FixedLadder) | L9 (VerifyRelease) | L10 (FailClose) | L11 (Trace) | L12 (Decouple) | Anticipated? |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **PA-01** | Smith & Rixner (Phoenix, 2015) | MCU | **YES** | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-02** | Branco et al. (Karma, 2019) | MCU | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-03** | US 9,547,557 B2 (Dell, 2017) | PCIe Server | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-04** | US 9,411,667 B2 (Intel, 2016) | PCIe Hypervisor | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-05** | US 8,510,592 B1 (NetApp, 2013) | Storage Server | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-06** | US 10,921,871 B2 (Trane, 2021) | HVAC Controller | NO | NO | NO | NO | NO | NO | UNV | NO | UNV | NO | NO | NO | **NO** |
| **PA-07** | US 10,331,522 B2 (IBM, 2019) | Enterprise SOA | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-08** | US 10,838,845 B2 (IBM, 2020) | App Server | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-09** | US 12,688,084 B2 (Oracle, 2026) | Cloud Middleware | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **PA-10** | Swift / Herder (OSDI/DSN) | OS Kernel | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | **NO** |
| **P4** | **Proposed Mechanism** | **MCU Runtime** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | — |

*Legend:*  
- **YES**: `[EXPLICITLY DISCLOSED]` supported by verified primary source page, section, or claim text.  
- **NO**: `[NOT FOUND IN INSPECTED MATERIAL]`.  
- **UNV**: `[UNVERIFIED / INACCESSIBLE AT CLAIM LEVEL]`.

---

## 6. Threat Ranking & Strongest Single-Reference Attack

### Threat Level Ranking:
1. **Rank 1 (Strongest Embedded Threat): PA-01 (Phoenix).**  
   Targets the identical problem domain (peripheral recovery on resource-constrained ARM Cortex-M MCUs).  
   *Why it fails single-reference anticipation:* Phoenix relies fundamentally on **thread checkpointing, stack frame rollback, and peripheral redo logging**, requiring ~6 KB RAM overhead. It does not operate at the asynchronous event boundary, has no in-pool quarantine, and lacks zero-heap static scheduling.
2. **Rank 2 (Strongest Queue/Quarantine Threat): PA-08 (IBM WebSphere FEQ) / PA-07 (IBM FEDB).**  
   Discloses failed-event retention, component-level failure mapping, and retry mechanisms.  
   *Why it fails single-reference anticipation:* Operates on **application servers and database persistence**, using separate queue instantiation. Failed events are deleted from the main queue rather than retained in-pool. It does not disclose bare-metal MCU static constraints (L1, L2) or the Gate B evidence-bounded association lattice (L3).
3. **Rank 3 (Strongest Recovery History Threat): PA-06 (Trane HVAC) / PA-05 (NetApp).**  
   Discloses recovery routines and automated component repair.  
   *Why it fails single-reference anticipation:* Operates at coarse physical subsystem / storage adapter levels, lacking event queue mechanics.

---

## 7. Unresolved Items & Handoff to K.10.3

While single-reference anticipation is refuted within the inspected candidate set:
* **The Obviousness Threat Persists (35 U.S.C. § 103):** An adversarial examiner can formulate a combination rejection combining Phoenix (PA-01, embedded peripheral reset) + IBM (PA-08, failed-event queue) + Quantum Leaps QP (static preallocated event pools).
* **Scope Boundary Enforced:** Analysis of combinatorial motivation, architectural compatibility friction, and non-obviousness arguments is strictly assigned to **K.10.3**. In accordance with the prompt boundaries, K.10.3 was **not** conducted in this session.

---

## 8. Protected Boundaries & Integrity Verification

1. `reference/src/ref_runtime.c`: **100% UNTOUCHED** (Git Blob: `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`, SHA-256: `9339FCC34C01...`).
2. `reference/include/ref_runtime.h`: **100% UNTOUCHED** (Git Blob: `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`, SHA-256: `131ACE749C9F...`).
3. Gates A–E Contract Documents: **100% UNTOUCHED**.
4. K.10 Empirical Evidence: **Frozen**; no tests rerun.
5. `main` Branch: **Untouched**.
6. Checkpoint Governance: **K.10.2 APPROVED AND CLOSED by ChatGPT on 2026-10-12** after the final PA-01/L1 source-grounded reconciliation. PA-01/L1 remains YES because Phoenix's primary paper establishes the resource-constrained event-driven MCU setting; its differing recovery mechanism remains mapped under other limitations. K.10.3 is the active next checkpoint; this approval authorizes technical analysis only, not any legal conclusion. `main` remains untouched.
