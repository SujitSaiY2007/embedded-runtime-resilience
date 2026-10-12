# K.10.2 — Deep Single-Reference Anticipation Review (Evidence-Corrected)

**Status:** Complete at the single-reference level; single-reference anticipation **refuted** across all inspected primary candidates; technical distinction remains **unresolved and vulnerable to multi-reference combination (K.10.3)**.  
**Branch:** `exp`  
**Base Commit:** `598627d713687402f1982ebefbdec7cf0204de38`  
**Scope:** Technical research analysis only; not a legal opinion or patentability assessment.  
**K.10 Evidence Baseline:** Frozen (16 Case Families × P0–P4 × 5 deterministic repetitions = 400 matched executions).  
**Protected Boundaries:** Gates A–E, `reference/src/ref_runtime.c`, and `reference/include/ref_runtime.h` 100% untouched.

---

## 1. Executive Summary & Core Objective

The objective of **K.10.2** is strictly bounded:
> Determine whether any single reference, considered individually across its verified disclosure and claims, anticipates or materially discloses the complete candidate combination of the proposed P4 runtime mechanism (limitations L1 through L12).

### Bounded Conclusion
> **"No single reference in the inspected candidate set was found to disclose the complete L1–L12 combination, based on the reviewed evidence."**

This review does not assert universal absence of anticipating prior art across all existing literature, nor does it assert legal novelty or patentability.

Prior art separates into two distinct clusters:
1. **Embedded / Low-Level Recovery Cluster (PA-01, PA-02, PA-03, PA-04, PA-06, PA-10):**
   Addresses embedded peripheral recovery or driver crash containment, but relies fundamentally on **thread checkpointing, call-stack rollback, register redo-logging, MMU address space virtualization, or coarse subsystem power cycling**. None discloses in-pool event-level quarantine within a static zero-heap event array without execution rollback.
2. **Enterprise & Cloud Message Processing Cluster (PA-05, PA-07, PA-08, PA-09):**
   Discloses failed-event queues, component-failure associations, error holding, and retry/verification/release. However, all operate on **application servers, separate queue instantiations, or external databases**, unconstrained by bare-metal MCU timing and static memory contracts.

The candidate distinction therefore survives single-reference anticipation within the inspected candidate set. However, it remains **vulnerable to a multi-reference combination attack (obviousness under 35 U.S.C. § 103)** combining an embedded driver reset mechanism (e.g. Phoenix) with an enterprise failed-event queue paradigm (e.g. IBM). This combination attack is formally assigned to **K.10.3**.

---

## 2. P4 Limitation Reference Anchor (L1–L12)

As codified in `research/phase2_k10_1_adversarial_distinction_review.md`, the 12 limitations comprising the candidate combination are:

* **L1:** Resource-constrained event-driven MCU setting (Cortex-M bare metal, single address space).
* **L2:** Fixed-capacity, zero-heap state (static allocation; no `malloc`/`free`; bounded queue arrays; no dynamic pool recycling).
* **L3:** Fault-to-event association has explicit precision levels and cannot exceed evidence precision (`assoc <= evidence`; levels: EXACT, SERVICE, PERIPHERAL, UNKNOWN).
* **L4:** Event identity is generation-qualified; stale references are rejected (`EventRef={slot_id, generation}`).
* **L5:** Fault-associated event is quarantined/retained in-pool rather than indiscriminately flushing all queued work (retained non-executable state in original static pool).
* **L6:** Independent work remains eligible while related/ordered/coupled work is blocked (dependency classes and dispatchability predicate).
* **L7:** Short recovery history changes action selection (history/episode attributes condition next action).
* **L8:** Fixed ladder has an expressly disclosed fixed sequence with a finite terminal rung (Gate C: T1 retry $\to$ T2 retry $\to$ T3 reset $\to$ T4 terminal; `MAX_RECOVERY_ACTIONS=4`).
* **L9:** Verification precedes release/continuation; failed recovery closes/escalates explicitly (runtime retains transition authority).
* **L10:** No fabricated target `EventRef` for service/peripheral/unknown association (fail-closed association contract).
* **L11:** Deterministic trace ties fault, association, action, episode, lifecycle and outcome (structured event audit trace).
* **L12:** Entire mechanism is a single bounded C runtime with decoupled policy and transition authorities (`policy_decide()` vs `runtime_apply_policy()`).

---

## 3. Methodological Clarifications on Disclosed Mechanisms

To ensure strict evidentiary discipline:

### 3.1. Dynamic Memory vs. Static Allocation (Requirement B)
References targeting enterprise application servers or databases (e.g., PA-07, PA-08) are not assumed to require dynamic heap allocation unless explicitly specified in their text. We separate:
- **Expressly specified:** What the patent specification or claims literally state (e.g., "storing in a database", "inserting into a failed event queue").
- **Described implementation:** The exemplary embodiment described in the specification (e.g., IBM WebSphere Application Server running on general-purpose OS).
- **Platform typical:** Conventional engineering practice on that platform (e.g., Java virtual machines typically utilize garbage-collected heap memory).
- **Unknown / Unspecified:** The low-level memory allocation model (heap vs. static buffer) is left unconstrained by the patent claims.

### 3.2. Fixed Recovery Ladder vs. General Escalation (Requirement C)
For L8, a general retry count, backoff policy, or multi-stage escalation (e.g., retry $\to$ reset) is **not** classified as disclosing P4's ladder. L8 strictly requires an **expressly disclosed fixed sequence with a finite terminal rung** matching or functionally equivalent to Gate C ($T_1 \to T_2 \to T_3 \to T_4$).

### 3.3. In-Pool Quarantine vs. External Holding (Requirement D)
For L5, we strictly distinguish:
- **In-pool retention (P4 contract):** The failed event remains in its assigned slot within the fixed-capacity event array as non-executable, preserving its slot identity without queue reallocation or data movement.
- **Secondary queue movement:** Deleting or extracting an event from an active queue and inserting it into a separate failed-event queue (FEQ) or dead-letter queue.
- **Database persistence:** Writing failed event records to an external relational/NoSQL table.
- **I/O buffering:** Pausing or buffering incoming requests in a driver wrapper while restarting hardware.
Only the first mechanism satisfies L5.

### 3.4. Static State vs. Memory Pool Allocation (Requirement E)
For L2, preallocated memory pools (such as Quantum Leaps QP `QMPool`) are distinguished from P4's static-state contract. QP dynamically allocates event blocks from pools via `Q_NEW()` and recycles them back to the pool via automatic reference-counted garbage collection (`QF_gc()`). In contrast, P4's static contract binds each event to a fixed slot (`EventSlot[20]`) where it remains without runtime dynamic pool allocation, pointer recycling, or reference counting.

---

## 4. Audited Primary Sources & Evidence Locators

Every candidate reference was evaluated at primary-source level (full proceedings paper, official patent specification and claims, or published patent application):

### 4.1. PA-01: Phoenix (Smith & Rixner, USENIX ATC 2015)
* **Citation:** Rebecca Smith and Scott Rixner, *"Surviving Peripheral Failures in Embedded Systems,"* Proceedings of the 2015 USENIX Annual Technical Conference (USENIX ATC '15), Santa Clara, CA, July 8–10, 2015, pp. 125–137.
* **Primary URL:** `https://www.usenix.org/conference/atc15/technical-session/presentation/smith`
* **Architecture & Domain:** Bare-metal ARM Cortex-M microcontrollers (Stellaris LM3S8962, TI CC2538).
* **Mechanism:** Checkpoints program state at safe transaction boundaries, logs peripheral register writes in a circular redo log, detects peripheral stalls via hardware timers/interrupts, resets the peripheral controller, replays register logs, and **rolls back the CPU call stack to the checkpoint** to restart the failed transaction.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[EXPLICITLY DISCLOSED]** (Section 1 "Introduction", p. 125, and Section 4 "Implementation", pp. 129–130; evaluated on ARM Cortex-M3/M4 bare-metal microcontrollers).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (Section 5.3 "Memory Overhead", p. 133; requires ~6 KB RAM for dynamic shadow stacks, redo logs, and checkpoint buffers; not a fixed static-pool queue architecture).
  * **L3 (Evidence-bounded association):** **[NOT FOUND IN INSPECTED MATERIAL]** (Associates faults with currently executing driver thread context; no 4-tier precision lattice).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Operates on thread execution contexts, not generation-qualified `EventRef` handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Rolls back the CPU call stack to transaction boundary; does not retain failed events non-executably in-pool).
  * **L6 (Dependency-aware preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Calling task is suspended/rewound; independent RTOS tasks continue only via standard OS scheduling).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Static reset-and-replay policy; no history-conditioned action adaptation).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses retry/timeout counters, but lacks an expressly disclosed fixed sequence with finite terminal rung).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Section 3.2 "Recovery", p. 128, and Section 4.2 "Peripheral Reset and Replay", p. 130; polls peripheral status register until ready before resuming application execution; timeouts trigger fatal alert).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Phoenix addresses embedded MCU peripheral recovery, but relies fundamentally on **checkpointing, execution stack rollback, and redo logging**, incurring substantial RAM overhead. It does not disclose event-boundary quarantine or zero-heap static scheduling.

---

### 4.2. PA-02: Karma (Branco et al., ACM SenSys 2019)
* **Citation:** Arthur S. R. Branco, Luca Mottola, Muhammad Hamad Alizai, Junaid Haroon Siddiqui, *"Intermittent Asynchronous Peripheral Operations,"* Proceedings of the 17th ACM Conference on Embedded Networked Sensor Systems (SenSys '19), New York, NY, Nov 2019, pp. 248–261.
* **Primary URL:** `https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf`
* **Architecture & Domain:** Intermittently powered energy-harvesting microcontrollers (TI MSP430 with FRAM).
* **Mechanism:** Manages peripheral operations across power failures by recording non-volatile operation descriptors in FRAM, rolling forward completed hardware operations, and rolling back uncommitted computation tasks upon power restoration.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[EXPLICITLY DISCLOSED]** (Section 1 and Section 5, pp. 248, 254; evaluated on MSP430FR5969 microcontrollers).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (Allocates NVRAM descriptors for intermittent peripheral operations, but does not disclose a fixed-capacity zero-heap event runtime queue contract).
  * **L3–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Addresses power failures, not runtime peripheral faults; no fault association lattice or in-pool event quarantine).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Manages operation completion ordering across reboots, but does not disclose queue dependency classes or eligibility predicates).
  * **L7–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (No history-driven recovery action selection; deterministic roll-forward/rollback).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Section 3.3, p. 252; verifies peripheral ready status before releasing tasks).
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
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Abstract, lines 19–22, and Claim 1; verifies data link layer re-establishment before reinstalling OS device driver).
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
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Abstract, lines 19–21, and Claim 1; platform entity verifies link recovery before notifying OS/VMM of availability).
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
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Abstract, lines 19–21; verifies device recovery is complete before migrating operations back from backup peripheral).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Enterprise storage server failover to redundant hardware; lacks MCU constraints, zero-heap event queues, and in-pool event quarantine.

---

### 4.6. PA-06: US 10,921,871 B2 (Trane / Basterash et al.)
* **Citation:** Thomas Christopher Basterash, Mark Martin, Udhaya Kumar Dayalan, *"BAS/HVAC control device automatic failure recovery,"* US Patent 10,921,871 B2, assigned to Trane International Inc. Filed: May 17, 2019; Issued: Feb 16, 2021.
* **Primary URL:** `https://patents.google.com/patent/US10921871B2/en`
* **Architecture & Domain:** Building Automation Systems (BAS) and HVAC embedded controllers.
* **Mechanism:** Monitors component health (sensors, actuators, firmware modules) in building automation controllers. Selects recovery actions to repair software/firmware or hardware faults.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[EXPLICITLY DISCLOSED]** (Abstract, lines 19–21; BAS control device and HVAC control device embedded microcontrollers).
  * **L2–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Manages macroscopic physical equipment modules; no event queue or in-pool quarantine).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Zone isolation is macroscopic building automation behavior, not queue-level dependency scheduling).
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
* **Memory & Execution Model Analysis (Requirement B):**
  - *Expressly specified:* Storing failed events in a failed event database containing failed event information and associated components.
  - *Described implementation:* Enterprise database-backed event failure management facility.
  - *Platform typical:* Relational/NoSQL databases with dynamic heap allocations.
  - *Unknown / Unspecified:* The patent claims are silent on memory allocation mechanics (neither requiring dynamic heap nor specifying zero-heap static allocation).
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[NOT FOUND IN INSPECTED MATERIAL]** (Enterprise event management facility).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (The patent text does not specify a zero-heap static state contract).
  * **L3 (Evidence-bounded association):** **[EXPLICITLY DISCLOSED]** (Abstract, lines 19–21; "failed event database containing failed event information relating to failed events and one or more components associated with each of the failed events").
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses database primary keys/records, not generation ring handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Events are stored in an external "failed event database", not retained in their original fixed-capacity queue pool as non-executable; per Requirement D).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Does not disclose queue-level dependency classes or dispatchability predicates).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Updates database based on retry results, but does not disclose short episode history conditioning next action).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Retries failed events upon component modification; lacks an expressly disclosed fixed sequence with finite terminal rung; per Requirement C).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Abstract, lines 20–22; "Upon modification to a component associated with a failed event, the failed event is retried. Based on a result of retrying the failed event, failed event information of the failed event database is updated").
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Enterprise database-backed failed event management; lacks zero-heap MCU runtime constraints and in-pool queue retention.

---

### 4.8. PA-08: US 10,838,845 B2 / US 2018/0365126 A1 (IBM / Edwards et al.)
* **Citation:** Andrew S. M. Edwards, Doina L. Klinger, Martin A. Ross, Paul S. M. Thorpe, *"Processing failed events on an application server,"* US Patent 10,838,845 B2 (pre-grant publication US 2018/0365126 A1), assigned to IBM Corp. Filed: Jun 14, 2017; Issued: Nov 17, 2020.
* **Primary URL:** `https://patents.google.com/patent/US10838845B2/en`
* **Architecture & Domain:** Enterprise application servers (IBM WebSphere).
* **Mechanism:** When an event fails in an application flow, the server **deletes the event from the main event queue** and inserts it into a separate **Failed Event Queue (FEQ)** with linked failure reasons. Replay occurs after corrective action.
* **Memory & Execution Model Analysis (Requirement B):**
  - *Expressly specified:* An application server comprising an event queue, an event processor, and a failed event queue; deleting the event from the event queue and inserting it into the failed event queue.
  - *Described implementation:* Enterprise application server event processing software.
  - *Platform typical:* Middleware message queues running on general-purpose servers.
  - *Unknown / Unspecified:* The patent claims do not specify low-level memory allocation; dynamic heap vs. static buffer is an unconstrained implementation detail.
* **Limitation Mapping & Locators:**
  * **L1 (MCU setting):** **[NOT FOUND IN INSPECTED MATERIAL]** (Specifies an application server).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (Does not specify zero-heap static allocation).
  * **L3 (Evidence-bounded association):** **[EXPLICITLY DISCLOSED]** (Abstract, lines 20–22; links failed event to related software application, processing flow ID, and failure reasons).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses flow IDs, not generation ring handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Expressly discloses **"deletes the event... from the event queue, then inserts... into a failed event queue"**; moving an event to a secondary queue does not satisfy in-pool non-executable retention in the original fixed pool; per Requirement D).
  * **L6 (Dependency preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Unrelated flows continue processing, but does not claim queue-level dependency classes or dispatchability predicates).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Links failure reasons, but does not disclose history-driven action selection).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Moves event to FEQ upon failure; lacks an expressly disclosed fixed sequence with finite terminal rung; per Requirement C).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Replay from FEQ after error resolution).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Primary art for failed event queues, but relies on separate queue creation and event deletion/re-insertion, not in-pool static array retention on an MCU.

---

### 4.9. PA-09: US 12,688,084 B2 (Oracle / Muthulankkat & Paulsami)
* **Citation:** Mahesh Muthulankkat, Prabakar Paulsami, *"Intelligent data flow control valve,"* US Patent 12,688,084 B2, assigned to Oracle International Corp. Filed: Sep 30, 2024; Issued: Jul 21, 2026.
* **Architecture & Domain:** Cloud integration middleware and enterprise data streaming pipelines.
* **Mechanism:** Monitors activity stream; on recoverable downstream endpoint error, instructs upstream system to pause transmission; resumes upon error resolution.
* **Limitation Mapping & Locators:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Cloud platform middleware).
  * **L3 (Association):** **[EXPLICITLY DISCLOSED]** (Monitors stream between integration layer and downstream destination; identifies recoverable error with downstream system).
  * **L4–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (Pauses entire upstream stream; no in-pool quarantine or fixed ladder).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Monitors activity stream until error is resolved before signaling upstream resumption).
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
  * **L3–L4:** **[NOT FOUND IN INSPECTED MATERIAL]** (Coarse process-level crash containment).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Buffers pending I/O packets in shadow driver wrapper during driver restart; buffering I/O does not satisfy in-pool non-executable retention in a fixed-capacity event queue; per Requirement D).
  * **L6 (Dependency preservation):** **[EXPLICITLY DISCLOSED]** (Swift et al., Section 4, pp. 6–7: non-crashing drivers and unrelated applications continue execution; Herder et al., Section 3, pp. 3–4: isolated user-space processes prevent cascading failures).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Standard restart policy).
  * **L8 (Fixed ladder with finite terminal rung):** **[NOT FOUND IN INSPECTED MATERIAL]** (Discloses restart attempt threshold, but lacks an expressly disclosed fixed sequence with finite terminal rung; per Requirement C).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Swift et al., Section 4.3; verifies driver reinitialization and device state restoration before releasing held I/O).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Relies on MMU hardware memory protection and multi-process/shadow virtualization.

---

## 5. Master Limitation-by-Reference Anticipation Matrix (Evidence-Corrected)

| Ref ID | Primary Reference | Target Domain | L1 (MCU) | L2 (ZeroHeap) | L3 (Assoc) | L4 (GenRef) | L5 (InPoolQuaran) | L6 (DepPres) | L7 (Hist) | L8 (FixedLadder) | L9 (VerifyRelease) | L10 (FailClose) | L11 (Trace) | L12 (Decouple) | Anticipated? |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **PA-01** | Smith & Rixner (Phoenix, 2015) | MCU | **YES** | NO | NO | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-02** | Branco et al. (Karma, 2019) | MCU | **YES** | NO | NO | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-03** | US 9,547,557 B2 (Dell, 2017) | PCIe Server | NO | NO | NO | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-04** | US 9,411,667 B2 (Intel, 2016) | PCIe Hypervisor | NO | NO | NO | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-05** | US 8,510,592 B1 (NetApp, 2013) | Storage Server | NO | NO | NO | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-06** | US 10,921,871 B2 (Trane, 2021) | HVAC Controller | **YES** | NO | NO | NO | NO | NO | UNV | NO | UNV | NO | NO | NO | **NO** |
| **PA-07** | US 10,331,522 B2 (IBM, 2019) | Enterprise SOA | NO | NO | **YES** | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-08** | US 10,838,845 B2 (IBM, 2020) | App Server | NO | NO | **YES** | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-09** | US 12,688,084 B2 (Oracle, 2026) | Cloud Middleware | NO | NO | **YES** | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-10** | Swift / Herder (OSDI/DSN) | OS Kernel | NO | NO | NO | NO | NO | **YES** | NO | NO | **YES** | NO | NO | NO | **NO** |
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
   Discloses failed-event retention, component-level association, and retry verification.  
   *Why it fails single-reference anticipation:* Operates on **application servers and database persistence**, using separate queue instantiation. Failed events are deleted from the main queue rather than retained in-pool. It does not disclose bare-metal MCU static constraints (L1, L2).
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
6. Checkpoint Governance: K.10.2 corrections complete. **K.10.3 remains locked and gated until ChatGPT grants formal approval.**
