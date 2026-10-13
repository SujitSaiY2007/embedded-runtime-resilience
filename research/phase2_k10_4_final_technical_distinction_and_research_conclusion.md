# K.10.4 — Final Technical Distinction & Research Conclusion

> **Historical checkpoint note:** This report was authored during K.10.4. Current repository integration and software-demo status are tracked in [the project overview](../../docs/PROJECT_OVERVIEW.md) and [K.12 audit](phase2_k12_professor_facing_software_demo_and_final_audit.md). The software scope is now closed; physical MCU validation remains future work. Historical statements below are retained where they describe the checkpoint-time state.

**Final status:** APPROVED AND CLOSED BY CHATGPT (2026-10-13)  
**Date:** 2026-10-13  
**Branch:** `exp` (via isolated working branch `feature/k10-4-final-technical-conclusion-2026-10-13`)  
**Scope:** Research synthesis and technical distinction analysis only. Not a legal opinion on patentability, novelty, or non-obviousness.  
**Execution Authority:** Antigravity (repository operations and documentation). ChatGPT retains sole checkpoint approval and closure authority.  
**Protected Boundaries:** Gates A–E, `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, `policy_decide()`, `runtime_apply_policy()`, and the 400-execution K.10 empirical dataset remain 100% frozen and untouched. `main` branch remains unsynchronized.

---

## 1. Title, Status, Scope, and Date

* **Formal Title:** Final Technical Distinction & Evidence-Bounded Research Conclusion for the P4 Runtime Mechanism
* **Active Checkpoint:** K.10.4
* **Date:** 2026-10-13
* **Repository:** `SujitSaiY2007/embedded-runtime-resilience`
* **Parent Milestone:** Phase 2 Investigation Closure / Part II Research Sequence
* **Scope Boundary:** This document synthesizes the empirical evidence collected during K.10 with the adversarial prior-art reviews of K.10.1 (limitation decomposition L1–L12), K.10.2 (single-reference anticipation), and K.10.3 (multi-reference combinations). It provides an honest technical assessment of what has been experimentally proven, what remains a plausible design hypothesis, what is unproven, and what conditions would weaken or falsify the proposed contribution. It establishes the strict software-only handoff into K.11.

---

## 2. Executive Summary

This report concludes the multi-checkpoint P4 advantage and novelty investigation (K.10, K.10.1, K.10.2, K.10.3, K.10.4).

1. **Empirical Findings:** The host/reference experimental campaign (16 case families × 5 policy variants P0–P4 × 5 deterministic repetitions = 400 matched executions) confirms that the proposed P4 runtime exhibits genuine, attributable advantages in **non-exact fault-to-event association fail-closed containment** (CF04, CF07) and **bounded recovery-ladder termination under cascading recovery faults** (CF05).
2. **Attribution Boundaries:** The empirical campaign disproves any claim of universal P4 superiority. Specifically:
   - **Exact-event quarantine is shared across P0–P4** in the reference C runtime (`ref_runtime.c`) and is not a P4-exclusive innovation.
   - P4 demonstrates zero measured advantage over simpler baselines in 6 out of 16 case families (CF02, CF09, CF11, CF12, CF13, CF15).
   - In CF16 (known persistent bus fault), baseline P2 succeeds in **1 attempt** by immediate reinitialization, whereas P4 requires **3 attempts** due to its fixed retry progression, demonstrating an explicit software-model cost trade-off.
3. **Prior-Art Distinction Status:**
   - **Single-Reference Anticipation (K.10.2):** Refuted across all inspected candidate references (PA-01 through PA-10). Prior art bifurcates into low-level embedded recovery using execution checkpointing/rollback (e.g., Phoenix PA-01, Karma PA-02) and enterprise/cloud message queuing using separate dynamic failed-event queues or databases (e.g., IBM PA-08, IBM PA-07). No single reference discloses the complete L1–L12 integration.
   - **Multi-Reference Combination Risk (K.10.3):** Substantial and unresolved. The strongest combination challenge is **C1 (Phoenix + IBM PA-08 + Quantum Leaps QP/C)**, which presents a high technical-combination risk. While these sources do not explicitly teach the full integrated contract—specifically the evidence-bounded association lattice, same-slot in-pool quarantine without dynamic recycling, queue-level dependency dispatchability, and unified episode closure—an adversarial reviewer or patent examiner could plausibly argue that combining these ingredients represents routine engineering adaptation.
4. **Research Conclusion:** The contribution of P4 is not an individual mechanism (zero-heap allocation, retry counters, reset routines, quarantine, or tracing are all established in prior art), but rather the **narrow, tightly constrained integration** of an evidence-bounded association lattice, generation-qualified event references, same-slot in-pool quarantine, dependency-aware queue dispatchability, a bounded four-rung recovery ladder, and unified deterministic episode transition authority. Whether this integrated contract constitutes a legally non-obvious or inventive step is an unresolved question requiring professional patent counsel; technically, it remains a bounded, defensible research hypothesis supported by host-level empirical evidence.

---

## 3. Canonical Evidence Sources and Integrity Statement

All findings in this report are grounded strictly in the canonical repository evidence base:

* **Experimental Evidence:** [K.10 Results Report](phase2_k10_p4_advantage_novelty_results.md) and raw execution logs (`reference/experiments/out/k10_runs.csv`, `reference/experiments/out/k10_traces.csv`).
* **Experimental Methodology:** [K.9.2 Protocol Design](phase2_k9_2_p4_advantage_novelty_design.md) and [K.9 Methodology Lock](phase2_k9_methodology_lock.md).
* **Reference Implementation:** `reference/src/ref_runtime.c` (Git blob SHA: `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`) and `reference/include/ref_runtime.h` (Git blob SHA: `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`).
* **Design Contracts:** [Phase 1 Design Specification](phase1_reference_implementation_design.md) (Gates A–E).
* **Adversarial Reviews:** [K.10.1 Feature-Distinction Review](phase2_k10_1_adversarial_distinction_review.md), [K.10.2 Single-Reference Anticipation Review](phase2_k10_2_single_reference_anticipation_review.md), and [K.10.3 Multi-Reference Combination Review](phase2_k10_3_multi_reference_combination_review.md).
* **Historical Records:** [K.10 Chat Record](chat_records/chat_k10_record.md), [K.10.2 Chat Record](chat_records/chat_k10_2_record.md), and [K.10.3 Chat Record](chat_records/chat_k10_3_record.md).

**Integrity Declaration:** No runtime C code, header definitions, policy decision logic (`policy_decide()`), transition dispatch (`runtime_apply_policy()`), Gate A–E invariants, or experimental CSV trace files were modified, re-executed, or manipulated to produce this report. All comparisons reflect exact, reproducible host executions.

---

## 4. Exact K.10 Empirical Findings

The K.10 evaluation executed a matched, deterministic experimental matrix:
$$\text{Scope} = 16\text{ Case Families (CF01–CF16)} \times 5\text{ Policy Variants (P0–P4)} \times 5\text{ Repetitions} = 400\text{ Executions}$$

Across all 400 executions, variance was zero ($\sigma = 0$), confirming full determinism in fault injection, scheduling, and recovery progression.

### 4.1. Complete 16-Case-Family Matrix Summary

| Case Family | Target Scenario | P0 (Fixed Retry) | P1 (Retry + Reset) | P2 (Context Only) | P3 (Context + Hist) | P4 (Integrated) | Authoritative Empirical Finding |
|---|---|---|---|---|---|---|---|
| **CF01** | Persistent History | ESCALATE (att=2) | SUCCESS (att=3) | SUCCESS (att=1) | SUCCESS (att=3) | SUCCESS (att=3) | P0 fails (cannot reinit). P1, P3, P4 succeed on att 3. P2 succeeds on att 1 (baseline win). Shared recovery capability. |
| **CF02** | Queue Pressure | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | Target isolated; 15 background events complete across all variants. Shared quarantine mechanism. |
| **CF03** | Dependency Order | ESCALATE (att=2) | SUCCESS (att=3) | SUCCESS (att=3) | SUCCESS (att=3) | SUCCESS (att=3) | Dependents held in `ST_QUEUED` during quarantine across all variants; execute after predecessor recovery in P1–P4. |
| **CF04** | Association Ambiguity | STALE_REF (att=0, ACT) | STALE_REF (att=0, ACT) | STALE_REF (att=0, ACT) | STALE_REF (att=0, ACT) | ESCALATE (att=0, CLS) | **Genuine P4 Advantage:** P0–P3 attempt invalid target retry, emit `OUTCOME_STALE_REF`, leave episode unclosed (`ACT`). P4 fails closed (`CLS`). |
| **CF05** | Fault During Recovery | ESCALATE (att=2) | ESCALATE (att=3) | NO_TERM (att=4, ACT) | NO_TERM (att=4, ACT) | ESCALATE (att=3, CLS) | **Genuine P4 Advantage:** P2/P3 lack finite ladder bounds under repeated recovery faults (`att=4, ACT`). P4 terminates cleanly at attempt 3. |
| **CF06** | Recovery Failure | ESCALATE (att=2) | DEGRADE (att=3) | NO_TERM (att=4, ACT) | NO_TERM (att=4, ACT) | DEGRADE (att=3, CLS) | P0 escalates blindly. P1 and P4 degrade deferable work cleanly. Shared degradation capability. |
| **CF07** | Subsequent Fault Post-Ambiguity | EP_FULL (att=0, ACT) | EP_FULL (att=0, ACT) | EP_FULL (att=0, ACT) | EP_FULL (att=0, ACT) | SUCCESS (att=1, CLS) | **Genuine P4 Advantage:** Unclosed episode in CF04 locks P0–P3 pool (`OUTCOME_EPISODE_FULL`). P4 cleanly closed previous episode and recovers. |
| **CF08** | Critical vs Deferable | SUCCESS (att=1) | DEGRADE (att=0) | DEGRADE (att=0) | DEGRADE (att=0) | DEGRADE (att=0) | P0 escalates both. P1–P4 escalate critical and degrade deferable. Criticality awareness shared across P1–P4. |
| **CF09** | Repeated Contention | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | Negative control: All variants sequentially recover 3 transient faults cleanly without state leakage. |
| **CF10** | Reinit Followup | ESCALATE (att=2) | SUCCESS (att=3) | SUCCESS (att=3) | SUCCESS (att=3) | SUCCESS (att=3) | Followup peripheral operations succeed across all variants that recovered (P1–P4). |
| **CF11** | Alternating Classes | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | Negative control: Interleaved I2C + SPI faults isolated cleanly across all variants. |
| **CF12** | Queue Position | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | Position control: Head, middle, tail placement yields identical FIFO execution across all variants. |
| **CF13** | Low-Load Control | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | Low-load control: Single event under transient fault recovers in 1 attempt across P0–P4. |
| **CF14** | High-Load Control | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | High-load control: 15 background events preserved identically across P0–P4 under target quarantine. |
| **CF15** | Negative Control | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | SUCCESS (att=1) | Negative control: Pure transient fault recovers in 1 attempt across P0–P4 identically. |
| **CF16** | Baseline Lower Cost | ESCALATE (att=2) | SUCCESS (att=3) | SUCCESS (att=1) | SUCCESS (att=3) | SUCCESS (att=3) | **Baseline Win / Trade-off:** P2 succeeds in 1 attempt by immediate reinit. P4 takes 3 attempts due to retry ladder progression. |

---

## 5. Bounded P4 Advantages (CF04, CF07, CF05)

The empirical campaign isolates three specific, attributable advantages of P4 over the comparison baselines:

### 5.1. Ambiguous Fault Association & Fail-Closed Containment (CF04)
* **Observed Mechanism:** In CF04, an observable I2C bus error occurs where the fault cannot be attributed to a specific active transaction (`ASSOC_PERIPHERAL` or `ASSOC_UNKNOWN`).
* **Baseline Behavior (P0–P3):** P0–P3 fail to inspect or respect association precision. They attempt to execute retry actions against an unassociated or invalid target reference, generating `OUTCOME_STALE_REF` with `attempt_count=0` and leaving the recovery episode stuck in an open, unclosed state (`episode.active = true`).
* **P4 Behavior:** P4 enforces the Gate B evidence-precision invariant:
  $$\text{association\_precision} \le \text{evidence\_precision}$$
  When association is non-exact (`ctx->association != ASSOC_EXACT`), P4 recognizes that no valid event target exists to retry. It immediately selects `ACT_ESCALATE` with `is_terminal = true`, halts further unsafe execution on that peripheral, and cleanly closes the recovery episode (`episode.active = false`).
* **Attribution Finding:** **Genuine, attributable P4 advantage.** P4's fail-closed handling eliminates stale reference dereferences and prevents unclosed episode leaks.

### 5.2. Runtime Availability for Subsequent Faults (CF07)
* **Observed Mechanism:** CF07 evaluates the arrival of a subsequent valid fault episode following an earlier ambiguous fault incident.
* **Baseline Behavior (P0–P3):** Because P0–P3 left the recovery episode unclosed in CF04, the singleton recovery episode slot (`EPMAX=1`) remains occupied. When the subsequent fault arrives, the runtime rejects it immediately with `OUTCOME_EPISODE_FULL` (`attempt_count=0, active=true`), resulting in total recovery paralysis.
* **P4 Behavior:** Because P4 cleanly closed the prior ambiguous episode with terminal escalation, the recovery episode slot is free. The subsequent fault is admitted, processed, and successfully resolved via local retry in attempt 1 (`SUCCESS, attempt=1, closed=true`).
* **Attribution Finding:** **Genuine, attributable P4 advantage.** P4's clean episode lifecycle management preserves runtime availability for subsequent workloads.

### 5.3. Bounded Recovery Ladder Termination Under Repeated Faults (CF05)
* **Observed Mechanism:** In CF05, faults recur during the execution of recovery actions themselves (cascading recovery failure).
* **Baseline Behavior (P2, P3):** P2 (context-only) and P3 (context + history without finite ladder bounds) lack an immutable terminal rung when recovery actions repeatedly fail. In the tested harness, they cycle through recovery attempts without terminating cleanly, reaching `att=4` while remaining active (`NO_TERMINAL, att=4, ACT`).
* **P4 Behavior:** P4 strictly enforces the Gate C four-rung ladder:
  $$T_1: \text{RETRY \#1} \longrightarrow T_2: \text{RETRY \#2} \longrightarrow T_3: \text{REINIT\_OR\_RESET} \longrightarrow T_4: \text{TERMINAL\_ESCALATE}$$
  Under repeated recovery-action faults, P4 progresses deterministically through its budget and terminates at attempt 3 with `OUTCOME_TERMINAL_ESCALATE` and `closed=true`.
* **Attribution Finding:** **Genuine, attributable P4 advantage over P2 and P3.** P4 guarantees formal termination boundedness under cascading faults.

---

## 6. Shared Outcomes and Baseline Wins (Including CF16)

A rigorous research synthesis must document where the candidate mechanism provides **no advantage** or is **outperformed** by simpler baselines.

### 6.1. Baseline Win on Known Persistent Faults (CF16)
* **Observed Outcome:** CF16 evaluates an I2C bus lockup that is known a priori to be persistent (`FAULT_I2C_PERSISTENT`).
* **Baseline P2 Performance:** P2 (Context-Only) evaluates the fault class directly without history progression. It immediately selects `ACT_REINIT_OR_RESET` at attempt 0 and achieves successful peripheral recovery in **1 attempt**.
* **P4 Performance:** P4 enforces its fixed progression ladder ($T_1 \to T_2 \to T_3 \to T_4$). It retries twice before escalating to reinitialization at attempt 2, requiring **3 attempts** to achieve recovery.
* **Trade-Off Analysis:** P2 resolves the fault with lower latency and fewer wasted bus transactions. P4 incurs an **attempt lag cost** (2 superfluous retries) because its fixed ladder cannot bypass transient retry rungs even when persistence is deterministic.
* **Attribution Finding:** **Baseline win for P2.** Demonstrates that P4's fixed ladder imposes an operational cost penalty under known-persistent fault conditions.

### 6.2. Shared Capability: Work Preservation Under Quarantine (CF02, CF14)
* **Observed Outcome:** In CF02 and CF14, 15 background events execute to completion while the fault-associated event is quarantined.
* **Comparison:** Exactly 15 out of 15 background events are preserved across **all five variants (P0, P1, P2, P3, and P4)**.
* **Root Cause:** In the reference runtime (`ref_runtime.c`), `runtime_start_fault()` places the target event into `ST_QUARANTINED` for all variants. The scheduler scans queue admission order and dispatches eligible events around the quarantined slot regardless of which policy is active.
* **Attribution Finding:** **Shared runtime behavior.** Work preservation under quarantine cannot be claimed as an empirical advantage of P4.

### 6.3. Shared Capability: Persistent Fault Resolution (CF01, CF10)
* **Observed Outcome:** Under persistent I2C bus contention, P1, P2, P3, and P4 all successfully resolve the fault via peripheral reinitialization (`ACT_REINIT_OR_RESET`) on attempt 3 (or attempt 1 for P2). P0 fails because it lacks a reset action.
* **Attribution Finding:** **Shared capability among P1–P4.** Peripheral reset capability is common to all reset-capable variants, not unique to P4.

### 6.4. Shared Capability: Graceful Degradation (CF06, CF08)
* **Observed Outcome:** Under unrecoverable faults on deferable tasks, P1 and P4 cleanly degrade the task to `TERMINAL_DEGRADE` while preserving critical tasks via escalation.
* **Attribution Finding:** **Shared capability between P1 and P4.** Task degradation is not unique to P4.

### 6.5. Identical Control Outcomes (CF09, CF11, CF12, CF13, CF15)
In 6 of 16 case families, P4 exhibits bit-for-bit identical behavior to baselines:
* **CF09 (Repeated Contention):** All variants recover 3 sequential transient faults in 1 attempt each.
* **CF11 (Alternating Classes):** All variants isolate interleaved I2C and SPI faults identically.
* **CF12 (Queue Position):** Target position (head, middle, tail) has zero effect on scheduling order across all variants.
* **CF13 (Low Load) & CF15 (Transient Control):** Pure transient faults recover in 1 attempt across all variants.

---

## 7. Exact-Event Quarantine Attribution

The project history records an important implementation detail identified during the Phase 1 audit (Decision Log D-076):

> **Authoritative Attribution Rule:** Exact-event quarantine is implemented within the shared reference runtime (`ref_runtime.c`, function `runtime_start_fault()`). When a fault occurs on an exact event target, the runtime transitions that event slot to `ST_QUARANTINED` across all policy variants (P0–P4).

* **Scientific Implication:** The empirical preservation of background work observed in CF02 and CF14 is an architectural property of the **underlying event-driven scheduler**, not a policy property of **P4**.
* **Prohibited Claim:** It is strictly prohibited to present "quarantining failed events while preserving unrelated work" as an empirical win of P4 over P0–P3 in the K.10 results.
* **Permitted Claim:** The experimental data demonstrates that the reference runtime successfully isolates failed events in static memory without heap allocation, and that P4 operates safely within this shared quarantine framework without violating dependency invariants.

---

## 8. Capacity Confounds (W09/W10 and Reference Bounds)

The reference runtime is intentionally dimensioned with minimal static capacities:
$$\text{QMAX} = 16,\quad \text{XMAX} = 4,\quad \text{DMAX} = 4,\quad \text{EPMAX} = 1,\quad \text{ACTIVE\_MAX} = 20$$

These finite boundaries introduce structural behaviors that must be separated from policy differences:

1. **Episode Capacity Confound (`EPMAX=1` / W10 / CF07):**
   - The runtime supports exactly one active recovery episode at a time.
   - When baselines P0–P3 leave an episode unclosed in CF04, the subsequent fault in CF07 fails with `OUTCOME_EPISODE_FULL`. This failure is partly an artifact of the finite singleton episode constraint (`EPMAX=1`).
   - If the runtime allocated unbounded episode records, baselines might not experience `EPISODE_FULL`, though they would still leak memory or state. P4's advantage in CF07 is therefore conditioned on the bounded resource envelope.
2. **Queue Capacity Confound (`QMAX=16` / W09):**
   - In CF02, attempting to admit 17 events results in deterministic queue overflow rejection. This behavior is identical across all policies and reflects static capacity limits, not recovery intelligence.
3. **Dependency Capacity Confound (`DMAX=4`):**
   - Each event can track at most 4 explicit dependencies. Complex dependency graphs exceeding 4 edges are rejected at admission.

**Attribution Boundary:** Observed failures due to slot exhaustion or episode pool saturation must be attributed to defined capacity limits, not conflated with algorithmic policy flaws.

---

## 9. L1–L12 Feature and Limitation Synthesis

The K.10.1 review decomposed the candidate P4 runtime mechanism into twelve concrete technical limitations. The synthesis of their evidential and prior-art status is detailed below:

| ID | Technical Limitation / Mechanism | Implementation & Frozen Anchor | Prior-Art Status (K.10.2 / K.10.3) | Evidential Status (K.10) | Synthesis Assessment |
|---|---|---|---|---|---|
| **L1** | Resource-constrained event-driven MCU setting | Single physical address space, no MMU; Cortex-M bare metal | **Disclosed** in Phoenix (PA-01); Karma (PA-02) provides general MCU setting | Host simulation only; STM32U575 hardware unmeasured | Target domain alone is not distinguishing. |
| **L2** | Fixed-capacity zero-heap state | Static arrays (`EventSlot[20]`), no `malloc`/`free`, no dynamic pool recycling | **Partial overlap** in Quantum Leaps QP/C (static backing, but dynamic block allocation/recycling) | Verified via static symbol audit and memory layout | Standard embedded practice; weak alone. |
| **L3** | Evidence-bounded association lattice ($assoc \le evidence$) | Gate B: EXACT, SERVICE, PERIPHERAL, UNKNOWN; fail-closed rule | **Not found** in inspected art; partial in driver containment records | **Empirically verified** in CF04/CF07 | Key candidate technical distinction. |
| **L4** | Generation-qualified `EventRef` identity | Gate A: `EventRef = {slot_id, generation}`; wrap fails closed | Established general systems technique; absent from inspected MCU recovery art | Verified: prevents stale-reference aliasing across episodes | Component-level practice; weak alone, vital to contract. |
| **L5** | Same-slot in-pool non-executable quarantine | Gate A/D: event remains in original slot, marked non-executable; no queue movement | **Not found**; IBM PA-08 moves to separate queue; IBM PA-07 uses database | **Empirically verified** (shared runtime behavior across P0–P4) | Distinct from separate queues; shared across variants. |
| **L6** | Dependency-aware queue dispatchability predicate | Gate A/D: `is_dispatchable()`; blocks ORDERED/COUPLED, dispatches INDEPENDENT | **Partial overlap**; Phoenix re-executes dependent/rematerializes unrelated; lacks queue predicate | **Empirically verified** in CF03 | Conceptually pressured by Phoenix; queue predicate specific. |
| **L7** | Short recovery history conditions action selection | Gate C: episode attempt counter and progression ladder | **Disclosed conceptually** in Trane (PA-06); IBM PA-08 | **Empirically verified** in CF01/CF05/CF16 | Widely established concept in recovery systems. |
| **L8** | Fixed four-rung ladder with finite terminal rung | Gate C: $T_1 \text{ RETRY} \to T_2 \text{ RETRY} \to T_3 \text{ RESET} \to T_4 \text{ TERM}$ | **Partial overlap**; generic retry budgets and escalation ladders common | **Empirically verified** in CF05 | Established engineering pattern; specific sequence narrow. |
| **L9** | Verification precedes release; explicit terminal closure | Gates C/D: verification gate; runtime retains transition authority | **Partial overlap**; recovery handshakes and replay monitoring exist | **Empirically verified** in CF04/CF05/CF07 | Established principle; integrated execution specific. |
| **L10** | Fail-closed handling of ambiguous association | Gate B: no synthetic target generated for SERVICE/PERIPH/UNKNOWN | **Not found** in inspected art; systems typically guess or reset system | **Empirically verified** in CF04/CF07 | Key candidate technical distinction. |
| **L11** | Deterministic trace tying fault, episode, action, outcome | Gate E: fixed 24-byte `TraceRecord` CSV serialization | **Partial overlap**; logging and runtime verification common (R2U2 PA-11) | **Empirically verified** across 400 executions ($\sigma=0$) | Good engineering/verification practice; weak alone. |
| **L12** | Single bounded C runtime with decoupled policy authority | Architecture: `policy_decide()` computes decision; `runtime_apply_policy()` transitions state | **Not found** as single integrated contract; patterns individually common | **Empirically verified** in reference implementation | Architectural composition; weak alone. |

---

## 10. Candidate Integrated Technical Distinction

Based on the synthesis of L1–L12, the research contribution cannot be claimed around any individual mechanism:
* **Peripheral reset** is established (Phoenix, NetApp).
* **Quarantine / failed-event holding** is established (IBM PA-08, IBM PA-07).
* **Retry thresholds and escalation** are established (Trane, Dell, Intel).
* **Zero-heap static pools** are established (Quantum Leaps QP/C).
* **Dependency-aware replay/isolation** is established (Phoenix, Nooks).
* **Trace logging and verification** are established (R2U2, runtime monitoring).

### 10.1. The Conjoint Integration Hypothesis
The candidate technical distinction is strictly **conjunctive and integrated**:

> **Candidate Technical Distinction:**  
> In a resource-constrained, event-driven MCU firmware runtime operating without a heap or MMU, resilience is achieved through the unified interaction of:
> 1. An **evidence-bounded association lattice** that strictly enforces $\text{association\_precision} \le \text{evidence\_precision}$, failing closed without synthesizing false event targets when faults are ambiguous (L3, L10);
> 2. A **same-slot in-pool quarantine contract** that retains failed work in its assigned static slot without queue movement, dynamic pool recycling, or call-stack rollback (L2, L4, L5);
> 3. A **queue-level dependency dispatchability predicate** that allows independent queued work to execute while holding dependent, ordered, or transactional work (L6);
> 4. A **bounded, history-conditioned four-rung recovery ladder** ($T_1 \to T_2 \to T_3 \to T_4$) guaranteeing deterministic terminal closure under cascading recovery failures (L7, L8, L9); and
> 5. A **decoupled policy-decision and transition authority** within a single statically bounded C runtime generating deterministic trace records (L11, L12).

### 10.2. Evidential Tiers of the Candidate Distinction
* **Tier 1 — Individually Established Ingredients:** Static allocation, generation handles, peripheral reset routines, retry counters, trace logging.
* **Tier 2 — Experimentally Supported Interactions:** Fail-closed ambiguous association preventing episode pool lockup (CF04 $\to$ CF07); finite ladder termination under recovery faults (CF05); dependency-aware holding during quarantine (CF03).
* **Tier 3 — Unresolved Research Hypothesis:** Whether combining Tier 1 ingredients into the Tier 2 interaction represents an inventive, non-obvious engineering departure relative to multi-reference combinations (specifically C1), or whether it represents routine engineering optimization for bare-metal microcontrollers.

---

## 11. Single-Reference Anticipation Findings (K.10.2 Synthesis)

The K.10.2 audit inspected primary patent specifications, grant claims, and peer-reviewed conference publications for references PA-01 through PA-10.

### 11.1. Summary of Inspected References

1. **Phoenix (Smith & Rixner, USENIX ATC 2015, PA-01):**
   - *Target Domain:* Bare-metal ARM Cortex-M microcontrollers (matches L1).
   - *Mechanism:* Checkpoints register state before peripheral accesses; rolls back execution stack and replays peripheral access using a redo journal upon failure.
   - *Anticipation Finding:* **Not anticipated.** Relies on call-stack rollback and replay journals (~6 KB RAM overhead); does not operate on an asynchronous event queue; lacks in-pool quarantine, generation handles, or the Gate B association lattice.
2. **Karma (Branco et al., ACM SenSys 2019, PA-02):**
   - *Target Domain:* Intermittent energy-harvesting microcontrollers (MSP430).
   - *Mechanism:* Checkpoints execution state across power failures; rolls forward peripheral operations and rolls back compute.
   - *Anticipation Finding:* **Not anticipated.** Addressed to power failure checkpointing, not event-driven peripheral fault quarantine.
3. **Dell US 9,547,557 B2 (PA-03) & Intel US 9,411,667 B2 (PA-04):**
   - *Target Domain:* PCIe server and hypervisor architectures.
   - *Mechanism:* Disables PCIe data links upon fatal downstream error; creates error-containment records; reinstall drivers.
   - *Anticipation Finding:* **Not anticipated.** Enterprise PCIe link/driver management; lacks bare-metal MCU event queue contracts.
4. **NetApp US 8,510,592 B1 (PA-05):**
   - *Target Domain:* Storage server controllers.
   - *Mechanism:* Isolates failed adapter, fails over operations to backup adapter, runs recovery routines, migrates operations back.
   - *Anticipation Finding:* **Not anticipated.** Coarse physical adapter failover; no event-level quarantine or static MCU runtime.
5. **Trane US 10,921,871 B2 (PA-06):**
   - *Target Domain:* Commercial HVAC building automation controllers.
   - *Mechanism:* Tracks restart/restore counters; triggers recovery partition restore when threshold is exceeded.
   - *Anticipation Finding:* **Not anticipated.** Boot-level partition recovery threshold; lacks event-level scheduling or association lattices.
6. **IBM US 10,331,522 B2 (PA-07):**
   - *Target Domain:* Enterprise Service-Oriented Architecture (SOA).
   - *Mechanism:* Failed-event database associates failures with components/resources; retries work after resource modification; supports message quarantine.
   - *Anticipation Finding:* **Not anticipated.** Relies on database persistence and enterprise message brokers; no static zero-heap MCU runtime.
7. **IBM US 10,838,845 B2 (PA-08):**
   - *Target Domain:* WebSphere Application Server.
   - *Mechanism:* Deletes failed event from active queue and inserts into a *different* Failed-Event Queue (FEQ); executes corrective action; monitors replay.
   - *Anticipation Finding:* **Not anticipated.** Explicitly requires secondary queue movement; dynamic heap environment; lacks evidence-bounded association lattice.
8. **Oracle US 12,688,084 B2 (PA-09):**
   - *Target Domain:* Cloud data integration middleware.
   - *Mechanism:* Pauses integration data stream upon downstream error; resumes after error resolution.
   - *Anticipation Finding:* **Not anticipated.** Stream-level flow control; lacks event-level MCU recovery.
9. **Swift et al. / Herder et al. (Nooks / MINIX 3, PA-10):**
   - *Target Domain:* General-purpose OS kernels on x86 hardware with MMU.
   - *Mechanism:* Isolates device drivers into hardware page-table domains or user processes; restarts driver on crash; shadow driver replays requests.
   - *Anticipation Finding:* **Not anticipated.** Relies fundamentally on MMU address-space isolation and multi-process OS abstractions.

### 11.2. Authoritative Anticipation Conclusion
> **Finding:** No single reference in the inspected candidate set discloses the complete L1–L12 combination. Single-reference anticipation under 35 U.S.C. § 102 is refuted within the inspected candidate set.

---

## 12. Strongest Multi-Reference Attacks and K.10.3 Threat Ranking

While single-reference anticipation is refuted, K.10.3 established that the proposed mechanism faces substantial obviousness and combination pressure under 35 U.S.C. § 103.

### 12.1. Threat Ranking

```
+-------------------------------------------------------------------------------+
|                      K.10.3 MULTI-REFERENCE THREAT RANKING                    |
+-------------------------------------------------------------------------------+
|  RANK 1 — HIGH THREAT:                                                        |
|  Combination C1: Phoenix (PA-01) + IBM FEQ (PA-08) + QP/C Event Pools         |
|  -> Directly combines embedded peripheral reset, failed-event retention, and  |
|     static event pool architecture. Strongest attack path.                    |
+-------------------------------------------------------------------------------+
|  RANK 2 — MODERATE-TO-HIGH THREAT:                                            |
|  Combination C3: NetApp (PA-05) + IBM Event Failure Management (PA-07)        |
|  -> Combines peripheral isolation/recovery routines with event/resource       |
|     association and message quarantine.                                       |
+-------------------------------------------------------------------------------+
|  RANK 3 — MODERATE THREAT (Generic Recovery):                                 |
|  Combination C2: Trane (PA-06) + Dell (PA-03) / Intel (PA-04)                 |
|  -> Combines thresholded recovery policies with hardware link containment.   |
|     Less direct correspondence to event-level MCU queue contracts.            |
+-------------------------------------------------------------------------------+
```

### 12.2. Detailed Analysis of Combination C1 (The Primary Attack)
* **Starting Reference:** Phoenix (PA-01). Teaches peripheral fault detection, register checkpointing, peripheral reinitialization, and dependency-aware access re-execution/rematerialization on Cortex-M MCUs.
* **Secondary Reference 1:** IBM US 10,838,845 B2 (PA-08). Teaches failed-event retention, failure-reason recording, corrective-action invocation, and replay monitoring.
* **Secondary Reference 2:** Quantum Leaps QP/C (`QMPool` / `QF`). Teaches deterministic, zero-heap event queues backed by caller-supplied static storage for embedded microcontrollers.
* **Opposing Combination Rationale:** A skilled embedded engineer, seeking to eliminate Phoenix's 6 KB stack-rollback overhead while retaining peripheral recovery, would naturally look to QP/C for static event queues, and look to standard enterprise failed-event patterns (IBM) to hold failing events rather than aborting the application.
* **Technical Friction & Gaps Remaining in C1:**
  1. *Execution Semantics:* Phoenix requires thread stack rollback; IBM moves events to an external queue; QP/C dynamically allocates and recycles event blocks. None teaches **same-slot in-pool quarantine** where an event remains in its pre-allocated slot without queue reallocation or reference-counted recycling.
  2. *Association Precision:* None teaches the **evidence-bounded association lattice** ($assoc \le evidence$) with fail-closed rejection of synthetic targets.
  3. *Ladder Determinism:* IBM and Phoenix provide open-ended retries or generic recovery procedures; neither teaches the **exact four-rung finite ladder** ($T_1 \to T_2 \to T_3 \to T_4$) terminating cleanly under recovery faults.

---

## 13. Strongest Opposing-Reviewer Argument

A rigorous research conclusion must articulate the strongest counter-argument that a skeptical reviewer, academic referee, or patent examiner would formulate:

> **The Opposing Reviewer's Case:**  
> "The applicant's proposed contribution is an aggregation of known techniques applied to a standard microcontroller setting.
> 1. Peripheral resets upon bus failure are well-known in embedded firmware and fully documented in Phoenix (2015).
> 2. Quarantining or holding a failed request while allowing independent requests to proceed is the textbook definition of asynchronous queue fault isolation, as taught by IBM (US 10,838,845) and decades of message-queuing literature.
> 3. Dependency-aware scheduling is standard computer science, and Phoenix already demonstrates re-executing dependent operations while preserving unrelated ones.
> 4. Fixed retry thresholds, exponential backoffs, and reset escalation ladders are routine engineering heuristics, taught by Trane (US 10,921,871) and standard networking protocols.
> 5. Allocating queues in static arrays to avoid dynamic heap allocation is universally practiced in resource-constrained MCU firmware, as exemplified by Quantum Leaps QP/C.
>
> The applicant has merely taken these well-known techniques, implemented them in standard C on a bare-metal microcontroller, and observed the predictable operational benefits of isolation and bounded retries. The behavioral differences in CF04 and CF07 are simply the obvious result of adding a basic `if (target != NULL)` check before retrying. Furthermore, the applicant's own data shows that in 6 of 16 cases there is zero benefit, and in CF16 the proposed mechanism is actually worse than a simple context-aware baseline. There is no synergistic or unexpected technical effect here—only routine, predictable engineering."

### Rebuttal and Research Boundary
The defensible research response does **not** claim that the opposing reviewer is entirely wrong. The component mechanisms *are* established. The research defense rests on three precise observations:
1. **Architectural Co-Design:** In deeply constrained bare-metal MCUs without MMU or thread virtualization, achieving event isolation *without* stack rollback (Phoenix) and *without* dynamic memory allocation/queue reallocation (IBM) requires a tight invariant coupling between slot identity (`EventRef`), same-slot quarantine, and scheduler eligibility.
2. **Failure Path Completeness:** The empirical failure of baselines P0–P3 in CF04 and CF07 proves that conventional recovery implementations suffer from subtle, catastrophic failure modes (unclosed episode leaks and stale reference dereferences) when fault association is ambiguous. P4 provides an explicit formal contract ($assoc \le evidence$) that guarantees safe termination where conventional baselines freeze.
3. **Evidence Discipline:** The research does not claim universal superiority; it explicitly documents the attempt-lag trade-off in CF16 and the shared nature of quarantine preservation.

---

## 14. Trade-Off Register

The empirical and architectural trade-offs identified across the investigation are systematically cataloged below:

| Case / Mechanism | Observed Outcome | Measured Advantage | Incurred Cost or Trade-Off | Attribution Constraint | Evidence Strength | Unresolved Question |
|---|---|---|---|---|---|---|
| **CF04 (Ambiguity)** | P4 fails closed (`TERMINAL_ESCALATE, att=0, CLS`); P0–P3 emit `STALE_REF` and leave episode open | Prevents invalid dereferences and unclosed episode pool leak | Halts execution on affected peripheral; no recovery attempted | Attributable specifically to P4 association invariant | **Strong** (5/5 reps, $\sigma=0$) | Can partial recovery be achieved safely without exact event target? |
| **CF07 (Subsequent Fault)** | P4 recovers subsequent fault in 1 attempt; P0–P3 fail with `EPISODE_FULL` | Preserves runtime availability for subsequent workloads | Requires prior episode to have reached terminal closure | Conditioned on singleton episode capacity (`EPMAX=1`) | **Strong** (5/5 reps, $\sigma=0$) | How does behavior scale if `EPMAX > 1`? |
| **CF05 (Recovery Fault)** | P4 terminates at attempt 3 (`TERMINAL_ESCALATE`); P2/P3 cycle without termination (`att=4, ACT`) | Guarantees bounded termination under cascading faults | Escalates to terminal state; work is halted | Attributable to Gate C finite four-rung ladder | **Strong** (5/5 reps, $\sigma=0$) | What is optimal rung count for diverse peripheral types? |
| **CF16 (Known Persistent)** | P2 succeeds in 1 attempt; P4 takes 3 attempts (2 retries + 1 reinit) | None; baseline P2 wins | **Attempt lag:** P4 wastes 2 retry cycles before attempting reset | Attributable to rigid ladder progression in P4 | **Strong** (5/5 reps, $\sigma=0$) | Should ladder support adaptive bypass when persistence is deterministic? |
| **Exact Quarantine** | 15/15 background events complete during target quarantine across P0–P4 | Work preservation during peripheral recovery | Retained slot consumes static queue capacity during recovery | **Shared runtime mechanism;** not a unique P4 advantage | **Strong** (5/5 reps, $\sigma=0$) | Does in-pool quarantine cause head-of-line blocking under high queue depth? |
| **W09/W10 Capacities** | Queue rejects 17th event; episode rejects 2nd concurrent fault | Predictable zero-heap memory bounds | Static rejection of bursts exceeding capacity | Shared capacity boundary (`QMAX=16`, `EPMAX=1`) | **Strong** (structural design bound) | What are optimal buffer dimensions for target MCU applications? |
| **Dependency Dispatch** | Dependents held in `ST_QUEUED` during recovery; execute after reinit (CF03) | Prevents corrupted state execution on unrecovered peripheral | Delays dependent work execution until recovery verification | Attributable to Gate A/D dependency predicate | **Strong** (5/5 reps, $\sigma=0$) | Runtime overhead of scanning dependency lists on MCU hardware? |
| **Deterministic Tracing** | 24-byte `TraceRecord` generated per transition; 100% deterministic | Complete auditability of fault, episode, action, outcome | RAM footprint (6144 B trace pool) and CPU serialization overhead | Validation quality; not an operational policy advantage | **Strong** (verified in C layout) | Exact CPU cycle overhead of trace emission on Cortex-M33 hardware? |

---

## 15. Claim-Boundary Table

This table establishes the strict boundaries of what can and cannot be asserted in academic publications, technical presentations, or project documentation based on the current evidence:

| Proposed Statement | Can Claim Now? | Evidence Basis | Boundary or Qualification | Additional Evidence Needed |
|---|---|---|---|---|
| **1. 400-execution matched host experiment completed** | **YES** | `k10_runs.csv`, `k10_traces.csv`, K.10 Results Report | 16 case families × P0–P4 × 5 reps; host simulation only | None (software host evidence complete). |
| **2. Bounded P4 advantages observed in CF04, CF07, and CF05** | **YES** | Deterministic trace logs showing clean fail-closed closure and ladder bounds | Applies specifically to non-exact association and cascading recovery faults | Replication across additional peripheral fault models. |
| **3. P4 is universally superior to baselines** | **PROHIBITED** | Refuted by CF16 (P2 wins) and CF02/CF09/CF11–CF15 (no difference) | P4 has explicit attempt-lag costs and identical performance on simple faults | None; universal superiority is scientifically falsified. |
| **4. Exact-event quarantine is unique to P4** | **PROHIBITED** | `ref_runtime.c` implementation audit (D-076); CF02/CF14 traces | Quarantine is applied by `runtime_start_fault()` across P0–P4 | None; empirical uniqueness is falsified. |
| **5. Integrated P4 contract is technically distinctive** | **PARTIALLY (As Research Hypothesis)** | K.10.1 limitation matrix, K.10.2 anticipation review, K.10.3 combination review | Survives single-reference anticipation; vulnerable to C1 combination | Independent peer review; exhaustive multi-reference audit. |
| **6. P4 is legally novel, non-obvious, or patentable** | **PROHIBITED** | Legal standards require patent counsel evaluation under 35 U.S.C. §§ 102/103 | Technical review cannot provide legal opinions or bind patent offices | Formal patentability search and opinion by registered patent counsel. |
| **7. System is suitable for physical MCU deployment** | **PARTIALLY (Architecturally Only)** | Zero-heap C11 implementation, static resource accounting (8164 B runtime) | Architecture adheres to MCU constraints; no physical code compiled/flashed | Cross-compilation (ARM GCC) and bare-metal target execution. |
| **8. System has demonstrated MCU timing, RAM/Flash, or physical fault resilience** | **PROHIBITED** | Platform boundary frozen in `PROJECT_MANUAL.md` | Host C execution on x86/Windows only; no STM32U575 data | Physical MCU testbed, logic analyzer, oscilloscope, hardware fault injection. |

---

## 16. Limitations and Unresolved Questions

### 16.1. Prior-Art and Legal Limitations
1. **Search Exhausiveness:** The prior-art reviews (K.10.1–K.10.3) audited ten primary references and several secondary frameworks. This does not constitute an exhaustive global search of all patent jurisdictions, RTOS codebases (Zephyr, FreeRTOS, NuttX), automotive standards (AUTOSAR), or historical aerospace systems.
2. **Obviousness Subjectivity:** The boundary between routine engineering adaptation and an inventive technical combination under 35 U.S.C. § 103 cannot be resolved by software simulation or automated analysis. It remains an unresolved legal and technical risk.
3. **Unresolved Architectural Combinations:** While C1, C2, and C3 were evaluated, other combinations (e.g., FreeRTOS stream buffers + Linux device driver error containment) may exist in the literature.

### 16.2. Experimental and Architectural Limitations
1. **Host-Only Evidence:** All measurements reflect host C runtime simulation. Interrupt latency, cache behavior, DMA contention, bus lockup electrical characteristics, and hardware MPU fault triggers remain completely unmeasured.
2. **Artificial Stimulus:** Faults were generated via deterministic software fault injection (`runtime_inject_fault()`). Real physical peripheral faults (e.g., I2C bus capacitance degradation, noise spikes, clock stretching timeouts) may exhibit non-deterministic timing that challenges the state machine.
3. **Single Recovery Episode (`EPMAX=1`):** The reference runtime is constrained to one concurrent recovery episode. The behavior of multi-peripheral concurrent cascading failures remains unmodeled.
4. **Finite Capacity Limits:** Queue depth (`QMAX=16`) and dependency capacity (`DMAX=4`) represent small prototype envelopes. Scaling behavior under industrial telemetry workloads is uncharacterized.

---

## 17. Falsification and Weakening Conditions

To maintain scientific integrity, we explicitly define conditions that would weaken or falsify the project's claims:

### 17.1. Conditions that Would Falsify Empirical Findings
1. **Reproducibility Failure:** Failure to reproduce identical trace outcomes ($\sigma = 0$) across the 400 matched runs when executed from the canonical repository using the frozen CMake configuration.
2. **Attribution Invalidation:** Discovery that P4's advantages in CF04 or CF07 were caused by an uninitialized variable, memory corruption, or test-harness artifact rather than the declared policy logic.
3. **Baseline Parity:** Demonstrating that a minor, non-architectural configuration change to P1 or P2 yields identical fail-closed safety and episode closure in CF04/CF07 without adopting P4's association lattice.

### 17.2. Conditions that Would Weaken the Research Contribution
1. **Discovery of Anticipating Prior Art:** Identification of a single published paper, patent, or open-source RTOS driver prior to the project priority date that discloses in-pool event quarantine with evidence-bounded association in bare-metal MCU firmware.
2. **Obviousness Invalidation:** A finding by an expert reviewer or patent examiner that adapting IBM's failed-event queue and Phoenix's reset routine into a QP/C static event pool constitutes a predictable combination of familiar elements yielding predictable results (*KSR International Co. v. Teleflex Inc.*).
3. **Separability Demonstration:** Empirical proof that the integrated mechanisms are fully separable—i.e., that identical resilience is achieved by running standard independent components without the unified runtime contract.
4. **Hardware Non-Viability:** Target-MCU validation revealing that P4's decision logic or state tracking incurs CPU cycle latency or memory overhead that violates hard real-time deadlines on a Cortex-M33 processor.

---

## 18. Evidence-Bounded Final Conclusion

The K.10.4 synthesis answers four foundational questions:

### 18.1. What is demonstrated?
* **Empirical Reality:** The 400-execution matched experimental campaign demonstrates that P4 achieves **bounded, attributable advantages** in fail-closed ambiguous fault containment (CF04), subsequent fault availability (CF07), and bounded recovery termination (CF05).
* **Cost Reality:** The evaluation proves that P4 incurs an **attempt-lag cost penalty** in CF16 (3 attempts vs P2's 1 attempt) and provides zero benefit over simpler baselines on simple transient faults.
* **Shared Infrastructure:** The evaluation confirms that work preservation during quarantine is an architectural property of the shared reference runtime, not a P4 policy advantage.
* **Single-Reference Status:** Single-reference anticipation is refuted across all ten inspected primary candidate references (PA-01 through PA-10).

### 18.2. What is plausible but unproven?
* **System Hypothesis:** It is plausible that integrating an evidence-bounded association lattice, generation-qualified identities, same-slot in-pool quarantine, and a bounded recovery ladder into a single bare-metal runtime provides a compact, robust software resilience paradigm for resource-constrained microcontrollers.
* **Technical Distinction:** It is plausible that the friction involved in adapting enterprise queue patterns and stack-rollback systems into a unified zero-heap MCU runtime constitutes a technically meaningful departure from prior art.

### 18.3. What is not established?
* **No Universal Superiority:** P4 is not universally superior; it is a trade-off design optimized for safety and termination under ambiguity at the expense of retry latency.
* **No Legal Novelty or Patentability:** The project has not established that P4 is legally novel, inventive, non-obvious, or patentable under relevant patent statutes.
* **No Hardware Viability:** The project has not established physical execution timing, RAM/Flash footprint, energy efficiency, MPU hardware enforcement, or electrical fault recovery on STM32U575 hardware.

### 18.4. What happens next?
1. **Software Synthesis & Demonstration (K.11 & K.12):** Complete the software-level research synthesis (K.11) and prepare a clean, reproducible, professor-facing software demonstration of the runtime mechanism (K.12).
2. **Repository Mirroring:** Following K.12 completion and final audit, synchronize the validated `exp` research branch to `main`.
3. **Physical Hardware Validation (Separate Campaign):** If and when target hardware (NUCLEO-U575ZI-Q) and instrumentation are authorized and available, undertake a physical validation campaign to measure real hardware cycle latency, memory footprint, and electrical fault recovery.

---

## 19. K.11 Handoff and Acceptance Criteria

Checkpoint K.10.4 formally hands off to **K.11 — Final Software Synthesis + Hardware-Validation Handoff**.

### 19.1. K.11 Objective and Scope
* **Objective:** Synthesize the frozen empirical findings of K.10 and the prior-art distinction findings of K.10.1–K.10.4 into the definitive software research synthesis report, establish the publication-oriented structure, and specify the target-MCU hardware validation requirements and success criteria.
* **Scope Boundary:** Software synthesis and protocol documentation only. K.11 is strictly prohibited from running physical hardware experiments, altering runtime code, or synchronizing `main`.

### 19.2. K.11 Acceptance Criteria
1. Full synthesis of the 400-execution host dataset into a publication-ready results narrative.
2. Definitive documentation of the evidence boundaries, trade-offs, and limitations established in K.10.4.
3. Explicit specification of target-MCU validation requirements for STM32U575 (cross-compilation toolchain, MPU configuration, I2C/SPI testbed, hardware fault injection protocol, and success criteria).
4. internal consistency across all continuity artifacts (`CURRENT_HANDOFF.md`, `PROJECT_STATE.md`, `DECISION_LOG.md`, `research/PART_II_CHAT_PLAN.md`).
5. Preservation of all five protected Git blob SHAs.

---

## 20. Technical and Legal Scope Disclaimer

This report is a **technical research synthesis** prepared for academic and engineering evaluation.

* It does **not** constitute a formal legal opinion on patentability, novelty, non-obviousness, freedom-to-operate, or inventive step under United States patent law (35 U.S.C. §§ 101, 102, 103, 112), the European Patent Convention (EPC Articles 52, 54, 56), or any other intellectual property jurisdiction.
* Any assessment of patent potential must be conducted by a registered patent attorney or agent examining official prosecution histories, full claim constructions, and exhaustive prior-art searches across global patent databases.
* The terminology used herein (e.g., "anticipation," "combination risk," "distinction") reflects engineering and research comparisons against documented sources, not legal adjudications.
