# K.10.2 — Deep Single-Reference Anticipation Review

**Status:** Complete at the single-reference level; single-reference anticipation **refuted** across all primary inspected candidates; technical distinction remains **unresolved and vulnerable to multi-reference combination (K.10.3)**.  
**Branch:** `exp`  
**Starting Commit:** `d281fb36487526309d70515c22f8a1e627dd7cea`  
**Scope:** Technical research analysis only; not a legal opinion or patentability assessment.  
**K.10 Evidence Baseline:** Frozen (16 Case Families × P0–P4 × 5 deterministic repetitions = 400 matched executions).  
**Protected Boundaries:** Gates A–E, `reference/src/ref_runtime.c`, and `reference/include/ref_runtime.h` 100% untouched.

---

## 1. Executive Summary & Core Objective

The objective of **K.10.2** is strictly bounded:
> Determine whether any single reference, considered individually across its full disclosure and claims, anticipates or materially discloses the complete candidate combination of the proposed P4 runtime mechanism (limitations L1 through L12).

### Core Finding
**Single-reference anticipation is REFUTED across all inspected primary candidates.** No single inspected reference discloses the full combination or an equivalent operational invariant set.

Prior art separates cleanly into two disjoint clusters, neither of which anticipates the proposed mechanism:
1. **Embedded / Low-Level Recovery Cluster (PA-01, PA-02, PA-03, PA-04, PA-06, PA-10):**
   Addresses embedded peripheral recovery or driver crash containment, but relies fundamentally on **thread checkpointing, call-stack rollback, register redo-logging, MMU address space virtualization, or coarse subsystem power cycling**. None discloses in-pool event-level quarantine within a static zero-heap event array without execution rollback.
2. **Enterprise & Cloud Message Processing Cluster (PA-05, PA-07, PA-08, PA-09):**
   Discloses failed-event queues, component-failure associations, error holding, and retry/verification/release. However, all operate exclusively on **dynamic heap memory, separate queue allocations, Java application servers, or external relational/NoSQL databases**, completely unconstrained by bare-metal MCU timing and memory limits.

The candidate distinction therefore survives single-reference anticipation. However, it remains **vulnerable to a multi-reference combination attack (obviousness under 35 U.S.C. § 103)** combining an embedded driver reset mechanism (e.g. Phoenix) with an enterprise failed-event queue paradigm (e.g. IBM). This combination attack is formally assigned to **K.10.3**.

---

## 2. P4 Limitation Reference Anchor (L1–L12)

As codified in `research/phase2_k10_1_adversarial_distinction_review.md`, the 12 limitations comprising the candidate combination are:

* **L1:** Resource-constrained event-driven MCU setting (Cortex-M bare metal, single address space).
* **L2:** Fixed-capacity, zero-heap state (static allocation; no `malloc`/`free`; bounded queue arrays).
* **L3:** Fault-to-event association has explicit precision levels and cannot exceed evidence precision (`assoc <= evidence`; levels: EXACT, SERVICE, PERIPHERAL, UNKNOWN).
* **L4:** Event identity is generation-qualified; stale references are rejected (`EventRef={slot_id, generation}`).
* **L5:** Fault-associated event is quarantined/retained in-pool rather than indiscriminately flushing all queued work (retained non-executable state in static pool).
* **L6:** Independent work remains eligible while related/ordered/coupled work is blocked (dependency classes and dispatchability predicate).
* **L7:** Short recovery history changes action selection (history/episode attributes condition next action).
* **L8:** Fixed ladder has a finite terminal rung (Gate C: T1 retry $\to$ T2 retry $\to$ T3 reset $\to$ T4 terminal; `MAX_RECOVERY_ACTIONS=4`).
* **L9:** Verification precedes release/continuation; failed recovery closes/escalates explicitly (runtime retains transition authority).
* **L10:** No fabricated target `EventRef` for service/peripheral/unknown association (fail-closed association contract).
* **L11:** Deterministic trace ties fault, association, action, episode, lifecycle and outcome (structured event audit trace).
* **L12:** Entire mechanism is a single bounded C runtime with decoupled policy and transition authorities (`policy_decide()` vs `runtime_apply_policy()`).

---

## 3. Audited Primary Sources & Limitation Mapping

Every candidate reference was evaluated at primary-source level (full proceedings paper, official patent specification and claims, or published patent application):

### 3.1. PA-01: Phoenix (Smith & Rixner, USENIX ATC 2015)
* **Citation:** Rebecca Smith and Scott Rixner, *"Surviving Peripheral Failures in Embedded Systems,"* Proceedings of the 2015 USENIX Annual Technical Conference (USENIX ATC '15), Santa Clara, CA, July 8–10, 2015, pp. 125–137.
* **Primary URL:** `https://www.usenix.org/conference/atc15/technical-session/presentation/smith`
* **Architecture & Domain:** Bare-metal ARM Cortex-M microcontrollers (Stellaris LM3S8962, TI CC2538).
* **Mechanism:** Checkpoints program state at safe transaction boundaries, logs peripheral register writes in a circular redo log, detects peripheral stalls via hardware timers/interrupts, resets the peripheral controller, replays register logs, and **rolls back the CPU call stack to the checkpoint** to restart the failed transaction.
* **Limitation Mapping:**
  * **L1 (MCU setting):** **[EXPLICITLY DISCLOSED]** (Targeted directly at resource-constrained Cortex-M MCUs).
  * **L2 (Zero-heap static state):** **[NOT FOUND IN INSPECTED MATERIAL]** (Requires dynamic memory allocations for checkpoint buffers, shadow stacks, and redo logs, consuming ~6 KB of RAM; not a static-pool queue architecture).
  * **L3 (Evidence-bounded association):** **[NOT FOUND IN INSPECTED MATERIAL]** (Associates faults with the currently executing driver thread; lacks multi-tier association precision lattice).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Operates on thread contexts, not generation-qualified `EventRef` handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Rolls back the execution stack; does not retain failed events non-executably in a queue pool).
  * **L6 (Dependency-aware preservation):** **[NOT FOUND IN INSPECTED MATERIAL]** (Entire calling task is suspended during rollback; independent RTOS tasks continue only via standard OS scheduling).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Applies static reset-and-replay policy; no multi-attempt escalation ladder).
  * **L8 (Fixed ladder with finite terminal rung):** **[NECESSARILY IMPLIED]** (Uses bounded retry counter before escalating to system panic).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Verifies peripheral ready flag following reset before resuming application execution).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Phoenix is the closest embedded peripheral recovery art, but relies on **checkpointing, execution rollback, and redo logging**, incurring substantial RAM overhead and latency. It does not disclose event-boundary quarantine or zero-heap static scheduling.

---

### 3.2. PA-02: Karma (Branco et al., ACM SenSys 2019)
* **Citation:** Arthur S. R. Branco, Luca Mottola, Muhammad Hamad Alizai, Junaid Haroon Siddiqui, *"Intermittent Asynchronous Peripheral Operations,"* Proceedings of the 17th ACM Conference on Embedded Networked Sensor Systems (SenSys '19), New York, NY, Nov 2019, pp. 248–261.
* **Primary URL:** `https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf`
* **Architecture & Domain:** Intermittently powered energy-harvesting microcontrollers (TI MSP430 with FRAM).
* **Mechanism:** Manages peripheral operations across power failures by recording non-volatile operation descriptors in FRAM, rolling forward completed hardware operations, and rolling back uncommitted computation tasks upon power restoration.
* **Limitation Mapping:**
  * **L1 (MCU setting):** **[EXPLICITLY DISCLOSED]** (Targeted at energy-harvesting MSP430 MCUs).
  * **L2 (Zero-heap static state):** **[EXPLICITLY DISCLOSED]** (Pre-allocated FRAM descriptor tables).
  * **L3–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Addresses power failures, not runtime peripheral faults; does not associate fault precision or quarantine events in-pool).
  * **L6 (Dependency preservation):** **[NECESSARILY IMPLIED]** (Enforces peripheral operation ordering across reboots).
  * **L7–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (No history-driven recovery action selection; deterministic roll-forward/rollback).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Verifies peripheral completion state before notifying tasks).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Solves power-intermittency consistency, not runtime peripheral fault recovery, event quarantine, or association ambiguity.

---

### 3.3. PA-03: US 9,547,557 B2 (Dell / Bolen)
* **Citation:** Austin P. Bolen, *"Peripheral bus error containment and recovery,"* US Patent 9,547,557 B2, assigned to Dell Products LP. Filed: Nov 10, 2014; Issued: Jan 17, 2017.
* **Primary URL:** `https://patents.google.com/patent/US9547557B2/en`
* **Architecture & Domain:** Enterprise Information Handling Systems / PCIe servers (PCIe root ports, OS device drivers).
* **Mechanism:** Detects fatal bus error at downstream PCIe port $\to$ deactivates data link layer $\to$ triggers OS hot-plug service to uninstall device driver without OS crash $\to$ reactivates link $\to$ reinstalls driver without physical removal.
* **Limitation Mapping:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Enterprise server with PCIe bus, ACPI, and full OS memory).
  * **L3–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Coarse physical port isolation; pending I/O packets are dropped or aborted).
  * **L6–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (Other PCIe ports continue operating; no multi-stage typed recovery ladder).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Verifies data link layer training before reinstalling driver).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Server PCIe link deactivation and driver hot-plug cycle; lacks event queues, zero-heap constraints, and ladder policies.

---

### 3.4. PA-04: US 9,411,667 B2 (Intel / Jayakumar et al.)
* **Citation:** Sarathy Jayakumar, Mohan J. Kumar, Jose A. Vargas, *"Recovery after input/ouput error-containment events,"* US Patent 9,411,667 B2, assigned to Intel Corp. PCT Filed: Jun 6, 2012; Issued: Aug 9, 2016.
* **Primary URL:** `https://patents.google.com/patent/US9411667B2/en`
* **Architecture & Domain:** Computing devices with PCIe and virtual machine monitors (VMM/hypervisors).
* **Mechanism:** Platform interrupt handler isolates an I/O link upon error containment event, generates error record, notifies OS/VMM, and recovers link upon directive.
* **Limitation Mapping:**
  * **L1–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (Server hypervisor/PCIe hardware architecture; lacks MCU event queue concepts).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Verifies link status after reset before notifying OS of availability).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** PCIe root port isolation for hypervisors.

---

### 3.5. PA-05: US 8,510,592 B1 (NetApp / Chan)
* **Citation:** Johnny Kang-wing Chan, *"PCI error resilience,"* US Patent 8,510,592 B1, assigned to NetApp Inc. Filed: Sep 15, 2009; Issued: Aug 13, 2013.
* **Primary URL:** `https://patents.google.com/patent/US8510592B1/en`
* **Architecture & Domain:** Enterprise storage servers (NetApp Data ONTAP appliances).
* **Mechanism:** Detects error in peripheral adapter (HBA/NIC), isolates adapter to suppress interrupt storms, migrates active operations to a backup adapter, calls driver recovery and reinitialization routines, verifies device, and migrates operations back.
* **Limitation Mapping:**
  * **L1–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (Enterprise storage OS; migrates operations to redundant hardware rather than in-pool quarantine).
  * **L6 (Dependency preservation):** **[NECESSARILY IMPLIED]** (Backup adapter processes storage requests while primary is repaired).
  * **L7 (History changes action selection):** **[EXPLICITLY DISCLOSED]** (Tracks error frequency to differentiate transient from permanent faults).
  * **L8 (Fixed ladder with finite terminal rung):** **[EXPLICITLY DISCLOSED]** (Recovery routine $\to$ reinitialization routine $\to$ permanent failover).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Verifies recovered device before migrating operations back).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Discloses progressive recovery ladder and operational migration in enterprise storage servers, but relies on redundant hardware and dynamic OS memory.

---

### 3.6. PA-06: US 10,921,871 B2 (Trane / Basterash et al.)
* **Citation:** Thomas Christopher Basterash, Mark Martin, Udhaya Kumar Dayalan, *"BAS/HVAC control device automatic failure recovery,"* US Patent 10,921,871 B2, assigned to Trane International Inc. Filed: May 17, 2019; Issued: Feb 16, 2021.
* **Primary URL:** `https://patents.google.com/patent/US10921871B2/en`
* **Architecture & Domain:** Building Automation Systems (BAS) and HVAC embedded controllers.
* **Mechanism:** Monitors component health (sensors, actuators, firmware modules). Maintains failure history log. Based on past occurrences, selects recovery actions (reboot, configuration rollback, firmware flash, or technician alarm).
* **Limitation Mapping:**
  * **L1 (MCU setting):** **[EXPLICITLY DISCLOSED]** (Embedded microcontroller BAS control boards).
  * **L2–L5:** **[NOT FOUND IN INSPECTED MATERIAL]** (No event queue or in-pool quarantine; manages physical equipment modules).
  * **L6 (Dependency preservation):** **[NECESSARILY IMPLIED]** (Healthy HVAC zones continue operation).
  * **L7 (History changes action selection):** **[EXPLICITLY DISCLOSED]** (Failure history log directly conditions next recovery action).
  * **L8 (Fixed ladder with finite terminal rung):** **[EXPLICITLY DISCLOSED]** (Multi-stage escalation terminating in lock-out/alarm).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Sensor feedback verified before restoring normal control loop).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Discloses history-conditioned escalation in embedded controllers, but operates at macroscopic equipment level, not microsecond event queue transactions.

---

### 3.7. PA-07: US 10,331,522 B2 & US 10,929,373 B2 (IBM / Allman et al.)
* **Citation:** Mark Allman, Andrew S. Edwards, Philip Jones, Doina L. Klinger, Martin A. Ross, Paul S. Thorpe, *"Event failure management,"* US Patent 10,331,522 B2 (Filed: Mar 17, 2017; Issued: Jun 25, 2019) and continuation US Patent 10,929,373 B2 (Filed: May 7, 2019; Issued: Feb 23, 2021), assigned to IBM Corp.
* **Primary URL:** `https://patents.google.com/patent/US10331522B2/en`
* **Architecture & Domain:** Enterprise message brokers and Business Process Management (BPM) middleware.
* **Mechanism:** Failed Event Database (FEDB) stores failed event payloads and associated failing component IDs. When a component is modified/restored, matching failed events are retried and the database is updated.
* **Limitation Mapping:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Enterprise server clusters, relational database persistence, dynamic Java heap).
  * **L3 (Evidence-bounded association):** **[EXPLICITLY DISCLOSED]** (Associates failed events with destination component IDs).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Uses database primary keys/UUIDs).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Moves events out of active queue into an external database table; not retained in-pool).
  * **L6 (Dependency preservation):** **[EXPLICITLY DISCLOSED]** (Main message bus continues processing independent event streams).
  * **L7 (History changes action selection):** **[EXPLICITLY DISCLOSED]** (FEDB tracks retry counts and failure causes).
  * **L8 (Fixed ladder with finite terminal rung):** **[EXPLICITLY DISCLOSED]** (Immediate retry $\to$ database holding $\to$ administrator alert).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Component repair triggers replay and verification).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Enterprise database-backed failed event management; completely lacks zero-heap MCU runtime constraints and in-pool queue retention.

---

### 3.8. PA-08: US 10,838,845 B2 / US 2018/0365126 A1 (IBM / Edwards et al.)
* **Citation:** Andrew S. M. Edwards, Doina L. Klinger, Martin A. Ross, Paul S. M. Thorpe, *"Processing failed events on an application server,"* US Patent 10,838,845 B2 (pre-grant publication US 2018/0365126 A1), assigned to IBM Corp. Filed: Jun 14, 2017; Issued: Nov 17, 2020.
* **Primary URL:** `https://patents.google.com/patent/US10838845B2/en`
* **Architecture & Domain:** Enterprise application servers (IBM WebSphere).
* **Mechanism:** When an event fails in an application flow, the server **deletes the event from the main event queue** and inserts it into a separate **Failed Event Queue (FEQ)** with linked failure reasons. Replay occurs after corrective action.
* **Limitation Mapping:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Enterprise application servers running on AIX/Linux; dynamic heap).
  * **L3 (Evidence-bounded association):** **[EXPLICITLY DISCLOSED]** (Links failure to specific software application flow ID).
  * **L4 (Generation-qualified event identity):** **[NOT FOUND IN INSPECTED MATERIAL]** (Flow IDs, not generation ring handles).
  * **L5 (In-pool event quarantine):** **[NOT FOUND IN INSPECTED MATERIAL]** (Explicitly discloses **deleting** the event from the main queue and inserting into a secondary queue; opposite of P4's in-pool non-executable retention).
  * **L6 (Dependency preservation):** **[EXPLICITLY DISCLOSED]** (Main event queue continues processing unrelated application flows).
  * **L7 (History changes action selection):** **[EXPLICITLY DISCLOSED]** (Tracks failure reasons and retry attempts in FEQ).
  * **L8 (Fixed ladder with finite terminal rung):** **[EXPLICITLY DISCLOSED]** (Retry threshold $\to$ FEQ quarantine $\to$ operator escalation).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Replay verified upon service readiness).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Primary art for failed event queues, but relies on separate queue creation and event deletion/re-insertion on dynamic heap memory, not in-pool static array retention on an MCU.

---

### 3.9. PA-09: US 12,688,084 B2 (Oracle / Muthulankkat & Paulsami)
* **Citation:** Mahesh Muthulankkat, Prabakar Paulsami, *"Intelligent data flow control valve,"* US Patent 12,688,084 B2, assigned to Oracle International Corp. Filed: Sep 30, 2024; Issued: Jul 21, 2026.
* **Primary URL:** Official USPTO Grant Record (US 12,688,084 B2).
* **Architecture & Domain:** Cloud integration middleware and enterprise data streaming pipelines.
* **Mechanism:** Monitors activity stream; on recoverable downstream endpoint error, instructs upstream system to pause transmission; resumes upon error resolution.
* **Limitation Mapping:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Cloud platform middleware).
  * **L3 (Association):** **[EXPLICITLY DISCLOSED]** (Associates downstream connector errors with active stream integration flows).
  * **L4–L8:** **[NOT FOUND IN INSPECTED MATERIAL]** (Pauses entire upstream stream; no in-pool quarantine or fixed ladder).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Monitors stream resolution before signaling resumption).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** High-level stream pause-and-resume valve in cloud integration; completely lacks embedded queue mechanisms.

---

### 3.10. PA-10: Swift et al. (OSDI 2004) & Herder et al. (DSN 2006 / MINIX 3)
* **Citation:** 
  * Michael M. Swift, Muthukaruppan Annamalai, Brian N. Bershad, Henry M. Levy, *"Recovering Device Drivers,"* Proceedings of the 6th USENIX OSDI, 2004.
  * Jorrit N. Herder, Herbert Bos, Ben Gras, Philip Homburg, Andrew S. Tanenbaum, *"Failure Resilience for Device Drivers,"* Proceedings of the 36th IEEE/IFIP DSN, 2006.
* **Architecture & Domain:** General-purpose OS kernels (Linux, MINIX 3) on MMU-equipped hardware (x86).
* **Mechanism:** Isolates device drivers into user-space processes (MINIX 3) or hardware page-table domains (Nooks). Shadow drivers / Reincarnation Servers detect driver crash, restart the driver process, replay state, and unblock held I/O requests.
* **Limitation Mapping:**
  * **L1–L2:** **[NOT FOUND IN INSPECTED MATERIAL]** (Requires MMU page tables, separate address spaces, and heavy dynamic kernel structures).
  * **L3–L4:** **[NOT FOUND IN INSPECTED MATERIAL]** (Coarse process-level crash containment).
  * **L5 (In-pool event quarantine):** **[NECESSARILY IMPLIED]** (Pending I/O requests held in shadow driver queue during driver restart).
  * **L6 (Dependency preservation):** **[EXPLICITLY DISCLOSED]** (Unrelated drivers and user processes continue execution).
  * **L7 (History changes action selection):** **[NOT FOUND IN INSPECTED MATERIAL]** (Standard restart policy).
  * **L8 (Fixed ladder with finite terminal rung):** **[EXPLICITLY DISCLOSED]** (Bounded restart attempts before declaring driver permanently failed).
  * **L9 (Verification precedes release):** **[EXPLICITLY DISCLOSED]** (Driver reinitialization handshake verified before releasing queued I/O).
  * **L10–L12:** **[NOT FOUND IN INSPECTED MATERIAL]**.
* **Anticipation Finding:** **NOT ANTICIPATED.** Relies on MMU hardware memory protection and multi-process/shadow virtualization.

---

## 4. Master Limitation-by-Reference Anticipation Matrix

| Ref ID | Primary Reference | Domain | L1 (MCU) | L2 (ZeroHeap) | L3 (Assoc) | L4 (GenRef) | L5 (Quaran) | L6 (DepPres) | L7 (Hist) | L8 (Ladder) | L9 (Verify) | L10 (FailClose) | L11 (Trace) | L12 (Decouple) | Anticipated? |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **PA-01** | Smith & Rixner (Phoenix, 2015) | MCU | **YES** | NO | NO | NO | NO | NO | NO | **IMP** | **YES** | NO | NO | NO | **NO** |
| **PA-02** | Branco et al. (Karma, 2019) | MCU | **YES** | **YES** | NO | NO | NO | **IMP** | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-03** | US 9,547,557 B2 (Dell, 2017) | Server | NO | NO | NO | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-04** | US 9,411,667 B2 (Intel, 2016) | Server | NO | NO | NO | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-05** | US 8,510,592 B1 (NetApp, 2013) | Storage | NO | NO | NO | NO | NO | **IMP** | **YES** | **YES** | **YES** | NO | NO | NO | **NO** |
| **PA-06** | US 10,921,871 B2 (Trane, 2021) | HVAC | **YES** | NO | NO | NO | NO | **IMP** | **YES** | **YES** | **YES** | NO | NO | NO | **NO** |
| **PA-07** | US 10,331,522 B2 (IBM, 2019) | Enterprise | NO | NO | **YES** | NO | NO | **YES** | **YES** | **YES** | **YES** | NO | NO | NO | **NO** |
| **PA-08** | US 10,838,845 B2 (IBM, 2020) | Enterprise | NO | NO | **YES** | NO | NO | **YES** | **YES** | **YES** | **YES** | NO | NO | NO | **NO** |
| **PA-09** | US 12,688,084 B2 (Oracle, 2026) | Cloud | NO | NO | **YES** | NO | NO | NO | NO | NO | **YES** | NO | NO | NO | **NO** |
| **PA-10** | Swift / Herder (OSDI/DSN) | OS Kernel | NO | NO | NO | NO | **IMP** | **YES** | NO | **YES** | **YES** | NO | NO | NO | **NO** |
| **P4** | **Proposed Mechanism** | **MCU** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | **YES** | — |

*Legend:*  
- **YES**: `[EXPLICITLY DISCLOSED]` in inspected primary material.  
- **IMP**: `[NECESSARILY IMPLIED]` by disclosed architecture.  
- **NO**: `[NOT FOUND IN INSPECTED MATERIAL]`.  
- *(All 12 limitations verified in P4 via reference implementation contracts).*

---

## 5. Threat Ranking & Strongest Single-Reference Attack

### Threat Level Ranking:
1. **Rank 1 (Strongest Embedded Threat): PA-01 (Phoenix).**  
   Targets the identical problem domain (peripheral recovery on resource-constrained ARM Cortex-M MCUs).  
   *Why it fails single-reference anticipation:* Phoenix relies fundamentally on **thread checkpointing, stack frame rollback, and peripheral redo logging**, requiring ~6 KB RAM overhead. It does not operate at the asynchronous event boundary, has no in-pool quarantine, and lacks zero-heap static scheduling.
2. **Rank 2 (Strongest Queue/Quarantine Threat): PA-08 (IBM WebSphere FEQ) / PA-07 (IBM FEDB).**  
   Discloses failed-event retention, component-level association, dependency-aware preservation of unrelated work, and retry verification.  
   *Why it fails single-reference anticipation:* Operates strictly on **enterprise application servers and relational databases with dynamic heap allocations**, using separate queue instantiation. It completely lacks bare-metal MCU static constraints (L1, L2).
3. **Rank 3 (Strongest Recovery History Threat): PA-06 (Trane HVAC) / PA-05 (NetApp).**  
   Discloses history-conditioned recovery action selection and multi-stage escalation ladders.  
   *Why it fails single-reference anticipation:* Operates at coarse physical subsystem / storage adapter levels, lacking event queue mechanics.

---

## 6. Unresolved Items & Handoff to K.10.3

While single-reference anticipation is cleanly defeated, the candidate technical distinction is **not proven novel**.

### The Looming Combinatorial Attack (The Examiner's Obviousness Rejection):
An adversarial examiner or reviewer will combine the teachings of multiple references:
> *"It would have been obvious to a Person Having Ordinary Skill in the Art (PHOSITA) in embedded systems to combine the embedded peripheral reset mechanism of Phoenix (PA-01) with the failed-event quarantine and dependency-aware preservation mechanism of IBM (PA-08), implemented using standard static zero-heap event pools (Quantum Leaps QP), to achieve bounded fault containment on an MCU."*

This combination attack cannot be resolved in K.10.2. It is the precise mandate of **K.10.3 (Multi-Reference Combination & Obviousness Analysis)**.

---

## 7. Protected Boundaries & Integrity Verification

1. `reference/src/ref_runtime.c`: **100% UNTOUCHED** (SHA-256: `9339FCC34C01...`).
2. `reference/include/ref_runtime.h`: **100% UNTOUCHED** (SHA-256: `131ACE749C9F...`).
3. Gates A–E Contract Documents: **100% UNTOUCHED**.
4. K.10 Empirical Evidence: **Frozen**; no tests rerun.
5. `main` Branch: **Untouched**.
6. Checkpoint Governance: K.10.2 closes the single-reference anticipation review. **K.10.3 remains locked and gated until ChatGPT grants formal approval.**
