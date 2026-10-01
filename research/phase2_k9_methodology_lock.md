# Phase 2 — K.9 Formal Software Experimental Methodology Lock

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Phase:** Part II — Integrated Software Demonstrator & Methodology Lock  
**Stage:** K.9: Full Software Re-Verification + Methodology Lock  
**Status:** **METHODOLOGY LOCKED — FROZEN FOR SOFTWARE EVALUATION**  
**Canonical Base:** `exp @ 9ebd84c`  

---

## 1. Executive Purpose and Objective

The objective of K.9 is **Full Software Re-Verification and Methodology Lock**.

This document formally locks the software experimental methodology, evaluation protocol, attribution boundaries, and interpretation constraints governing the empirical comparison between the proposed recovery policy (**P4**) and the baseline/ablation policies (**P0–P3**).

The purpose of this lock is to guarantee that all empirical claims derived from the software demonstration are:
1. **Methodologically controlled:** Comparisons isolate only what the implementation actually distinguishes.
2. **Attribution-neutral:** No superiority is claimed where outcomes arise from common mechanisms, shared quarantine implementations, or capacity constraints.
3. **Reproducible:** All executions are deterministic and bit-for-bit replayable.
4. **Evidence-bounded:** Software simulation evidence is never conflated with target-MCU hardware evidence.

---

## 2. Frozen Experimental Methodology Specification (Items A–O)

Each component of the experimental pipeline is formally locked below:

```
[ A. Policy Definitions ]  ──┐
[ B. Workload Definitions ] ─┼─► [ D. Input Conditions ] ─► [ Reference Runtime & Virtual System ]
[ C. Scenario Definitions ] ─┘   [ E. Fault Conditions ]       │ (Enforces G, H, I, J)
                                                               │
[ K. Trace-Derived Metrics ] ◄── [ F. Recovery Conditions ] ◄──┘
[ L. Deterministic Replay ]
[ M. Confound Handling ]
[ N. Reproducibility ]
[ O. Report Procedure ]
```

### A. Policy Definitions
* **Canonical Definition:** Frozen in Gate C and `reference/include/ref_runtime.h`:
  * **P0 (Fixed Retry):** Retry $\le 2$, then blind terminal escalation (`ACT_ESCALATE`). No peripheral recovery or degradation.
  * **P1 (Fixed Retry + Peripheral Recovery):** Retry $\le 2$, reinitialization $\le 3$ (`ACT_REINIT_OR_RESET`), degrade if deferable, else escalate.
  * **P2 (Context-Only Ablation):** Context-aware action selection without attempt history bounds (history-blind).
  * **P3 (Context + History Ablation):** Context and attempt history without Gate C exact ladder bounds.
  * **P4 (Proposed Integrated Policy):** Full Gate C ladder ($T_1 \to T_2 \to T_3 \to T_4$), context awareness, short history tracking, exact-association quarantine requirement, and safe fail-closed behavior.
* **Implementation Enforcing:** Function `policy_decide()` in `reference/src/ref_runtime.c`.
* **Experiment/Report Consumer:** `reference/experiments/evaluate_baselines.py`, `reference/experiments/host_experiment.c`, `runs.csv`.
* **Locked Interpretation:** Policies are evaluated strictly through the ISO C11 reference implementation without external heuristics.
* **Known Limitation:** The reference runtime currently applies exact-event quarantine across all variants (see Section 3.1).

### B. Workload Definitions
* **Canonical Definition:** 14 declarative workloads (W01–W14) defined in Gate E and `reference/tests/canonical_workloads.md`:
  * W01: Single-event transient fault recovery.
  * W02: Independent work preservation under single fault.
  * W03: Ordered dependency blocking during quarantine.
  * W04: Coupled transaction failure containment.
  * W05: Same-peripheral unassociated work execution.
  * W06: Persistent fault escalation and peripheral reset.
  * W07: Deferable work graceful degradation.
  * W08: Critical work escalation.
  * W09: Queue capacity boundary (`QMAX=16`).
  * W10: Recovery episode concurrency boundary (`EPMAX=1`).
  * W11: Stale `EventRef` generation mismatch rejection.
  * W12: Ambiguous fault association fail-closed containment.
  * W13: Mixed criticality execution ordering.
  * W14: Chained multi-dependency deterministic execution.
* **Implementation Enforcing:** `reference/experiments/workloads.csv` and `reference/tests/test_reference.c`.
* **Experiment/Report Consumer:** `reference/experiments/host_experiment.c`, `reference/experiments/run_host_experiment.py`.
* **Locked Interpretation:** Workloads represent purposive stress patterns designed to verify specific safety and liveness invariants.
* **Known Limitation:** Workloads are synthetic unit stress sequences, not traces sampled from production embedded applications.

### C. Scenario Definitions
* **Canonical Definition:** 14 declarative conceptual scenarios (S01–S14) defined in `research/part_ii_deterministic_scenarios_k5.md`, with 6 canonical demonstrator scenarios (S01, S02, S05, S06, S08, S14) implemented in the virtual system (see Section 4).
* **Implementation Enforcing:** `reference/virtual/src/virtual_scenarios.c` and `reference/virtual/include/virtual_scenarios.h`.
* **Experiment/Report Consumer:** `virtual_system_tests`, `virtual_demo_cli`, `test_virtual_baselines.c`, `evaluate_baselines.py`.
* **Locked Interpretation:** Scenarios fix event admission, dependencies, stimulus, and validation criteria declaratively.
* **Known Limitation:** Virtual demonstrator scenarios use fixed deterministic step sequencing.

### D. Input Conditions
* **Canonical Definition:** Fixed static capacities: `QMAX=16` normal queue slots, `XMAX=4` quarantine reservation slots, `ACTIVE_MAX=20` total event pool slots, `DMAX=4` dependency entries per event, `EPMAX=1` active recovery episode.
* **Implementation Enforcing:** Array declarations and capacity checks in `ref_runtime.c`.
* **Experiment/Report Consumer:** `reference_tests`, `host_experiment_replay`.
* **Locked Interpretation:** Sizing is static and compile-time fixed; dynamic allocation is prohibited.
* **Known Limitation:** Fixed capacities bound the maximum concurrency and queue depth.

### E. Fault Conditions
* **Canonical Definition:** Gate B evidence-bounded fault taxonomy: `FAULT_I2C_NACK`, `FAULT_I2C_TIMEOUT`, `FAULT_I2C_BERR`, `FAULT_I2C_ARLO`, `FAULT_I2C_PERSISTENT`, `FAULT_SPI_TIMEOUT`, `FAULT_SPI_VERIFY`, `FAULT_SPI_PERSISTENT`, `FAULT_SW_SERVICE`, `FAULT_AMBIGUOUS`. Four association levels: `ASSOC_EXACT`, `ASSOC_SERVICE`, `ASSOC_PERIPHERAL`, `ASSOC_UNKNOWN`.
* **Implementation Enforcing:** `runtime_start_fault()` in `ref_runtime.c`, `fault_schedules.csv`, and `virtual_scenarios.c`.
* **Experiment/Report Consumer:** `reference_tests`, `host_experiment.c`, `evaluate_baselines.py`.
* **Locked Interpretation:** Fault stimulus is injected deterministically via software tables keyed by `EventRef` and action index.
* **Known Limitation:** Does not model physical electrical phenomena (glitches, bus capacitance, ground bounce).

### F. Recovery Conditions
* **Canonical Definition:** Gate C recovery ladder: Action budget `MAX_RECOVERY_ACTIONS=4`. Progression: Attempt 1 $\to$ `ACT_RETRY`, Attempt 2 $\to$ `ACT_RETRY`, Attempt 3 $\to$ `ACT_REINIT_OR_RESET`, Attempt 4 $\to$ Terminal (`ACT_DEGRADE` or `ACT_ESCALATE`).
* **Implementation Enforcing:** `runtime_apply_policy()` and `policy_decide()` in `ref_runtime.c`.
* **Experiment/Report Consumer:** `reference_tests`, `virtual_baseline_tests`, `evaluate_baselines.py`.
* **Locked Interpretation:** Recovery decisions originate exclusively from `policy_decide()`.
* **Known Limitation:** Peripheral reinitialization is simulated via environmental status mirroring.

### G. EventRef Association Rules
* **Canonical Definition:** Gate A/B invariant: `EventRef = {slot_id, generation}`. Generation is an 8-bit monotonic counter failing closed on wrap. Association precision must not exceed evidence precision: `association <= evidence`.
* **Implementation Enforcing:** `ref_runtime.c`: Exact event recovery is permitted only when `assoc == ASSOC_EXACT`. Non-exact association (`ASSOC_UNKNOWN`, `ASSOC_PERIPHERAL`) sets `target_slot = INVALID_SLOT` (`255`) and fails closed to `TERMINAL_ESCALATE`.
* **Experiment/Report Consumer:** Unit test S08 in `test_virtual_baselines.c` and `test_ui_contracts.py`.
* **Locked Interpretation:** Synthetic EventRefs are strictly prohibited.
* **Known Limitation:** Broader scopes (`SERVICE_ONLY`, `PERIPHERAL_ONLY`) do not dynamically synthesize group targets; they fail closed.

### H. Quarantine Rules
* **Canonical Definition:** Gate A: Quarantined events (`ST_QUARANTINED`, `ST_FAILED`, `ST_RETRY_PENDING`) leave the dispatchable queue but retain their event slot in the pool. Quarantined events are ineligible for ordinary dispatch (`ordinary_dispatch_allowed() == false`).
* **Implementation Enforcing:** `runtime_start_fault()`, `runtime_verify_and_release()`, and `ordinary_dispatch_allowed()` in `ref_runtime.c`.
* **Experiment/Report Consumer:** W02/S01 (independent preservation), W03/S02 (dependent blocking).
* **Locked Interpretation:** Work preservation is validated as execution of unassociated work while the target remains quarantined.
* **Known Limitation:** Applied uniformly across P0–P4 in current runtime (see Section 3.1).

### I. Recovery-Attempt Counting
* **Canonical Definition:** Monotonic 1-indexed counter `episode.attempt_count` incremented on each entry to `runtime_apply_policy()`. Saturated at `MAX_RECOVERY_ACTIONS=4`.
* **Implementation Enforcing:** `runtime_apply_policy()` in `ref_runtime.c`.
* **Experiment/Report Consumer:** `runs.csv`, `evaluate_baselines.py`.
* **Locked Interpretation:** Attempt count accurately tracks recovery progression.
* **Known Limitation:** None within single-episode scope.

### J. Terminal Outcome Definitions
* **Canonical Definition:** `OutcomeCode`:
  * `OUTCOME_SUCCESS`: Work complete, episode released cleanly.
  * `OUTCOME_TERMINAL_DEGRADE`: Deferable work safely discarded/degraded.
  * `OUTCOME_TERMINAL_ESCALATE`: Unrecoverable or ambiguous failure escalated.
  * `OUTCOME_STALE_REF`: Operation rejected due to generation mismatch or invalid slot.
  * `OUTCOME_QUEUE_FULL` / `OUTCOME_EPISODE_FULL`: Capacity saturation.
* **Implementation Enforcing:** `ref_runtime.c`.
* **Experiment/Report Consumer:** `runs.csv`, `evaluate_baselines.py`, `phase2_k8_matched_baseline_validation.md`.
* **Locked Interpretation:** Terminal states are absorbing; once reached, no further recovery actions occur.
* **Known Limitation:** Baseline P0 produces `OUTCOME_STALE_REF` on ambiguous targets leaving episode open, whereas P4 produces `OUTCOME_TERMINAL_ESCALATE` and closes episode.

### K. Trace-Derived Metrics
* **Canonical Definition:** Every state transition emits a fixed 24-byte `TraceRecord` containing: `run_id`, `trace_seq`, `fault_episode_id`, `event_ref`, `transaction_id`, `observation_seq`, `action_index`, `state`, `action`, `outcome`, `correctness`.
* **Implementation Enforcing:** `write_trace_record()` in `ref_runtime.c`.
* **Experiment/Report Consumer:** `trace.csv`, `evaluate_baselines.py`, UI trace inspector.
* **Locked Interpretation:** Metrics (attempt counts, preserved events, recovery outcomes) are extracted directly from trace records without extrapolation.
* **Known Limitation:** Trace buffer is fixed-capacity (`TRACE_RECORD_MAX=256`).

### L. Deterministic Replay Requirements
* **Canonical Definition:** A run is uniquely defined by the tuple `(scenario_id, workload_id, fault_schedule_id, variant, run_id)`. Re-execution under the same tuple must yield identical state transitions, identical trace sequences, and identical 32-bit FNV-1a digests.
* **Implementation Enforcing:** `virtual_system_digest()` in `virtual_system.c` and replay checks in `run_host_experiment.py`.
* **Experiment/Report Consumer:** CTest #2 (`host_experiment_replay`), CTest #4 (`virtual_demo_test`), CTest #5 (`virtual_baseline_tests`), CTest #7 (`matched_baseline_validation_test`).
* **Locked Interpretation:** Determinism is verified by bit-for-bit digest equivalence.
* **Known Limitation:** Determinism holds for single-threaded synchronous simulation; concurrent RTOS execution is not modeled.

### M. Qualification and Confound Handling
* **Canonical Definition:**
  * `capacity_confounded=1`: Flagged when outcome is forced by table capacity (`QMAX`, `EPMAX`).
  * `ablation_contract_valid=0`: Flagged for baselines P0–P3 due to shared quarantine implementation.
  * `ablation_contract_valid=1`: Flagged for P4 where integrated policy matches contract.
* **Implementation Enforcing:** `host_experiment.c` and `run_host_experiment.py`.
* **Experiment/Report Consumer:** `runs.csv`, `evaluate_baselines.py`, `phase2_k8_matched_baseline_validation.md`.
* **Locked Interpretation:** Confounded runs must never be cited as unconfounded policy differences.
* **Known Limitation:** Confound flags are binary metadata attributes.

### N. Reproducibility Requirements
* **Canonical Definition:** Automated CTest execution must reproduce the complete 100-run matrix without manual intervention, external networks, or proprietary toolchains.
* **Implementation Enforcing:** CMake / CTest configuration (`reference/CMakeLists.txt`, `reference/virtual/CMakeLists.txt`).
* **Experiment/Report Consumer:** Automated test harness.
* **Locked Interpretation:** A test pass requires 100% assertions satisfied across all 7 test suites.
* **Known Limitation:** Requires standard Python 3 and C11 compiler.

### O. Evidence and Report Generation Procedure
* **Canonical Definition:** The comparative validation report is reproducibly generated via:
  `python reference/experiments/evaluate_baselines.py --report research/phase2_k8_matched_baseline_validation.md`
* **Implementation Enforcing:** `reference/experiments/evaluate_baselines.py`.
* **Experiment/Report Consumer:** `research/phase2_k8_matched_baseline_validation.md`.
* **Locked Interpretation:** Report generation is programmatic and deterministic.
* **Known Limitation:** Manual edits to the generated markdown report are prohibited; changes must originate in the evaluation script.

---

## 3. Formal Lock of Identified Limitations and Attribution Boundaries

The following limitations are **strictly locked** as boundary constraints on all research claims:

### 3.1. Quarantine Attribution Limitation
> [!CRITICAL]
> **Quarantine Mechanism Limitation:**  
> In the current C reference implementation (`ref_runtime.c`), `runtime_start_fault()` places the target event into `ST_QUARANTINED` for **all** policy variants (P0–P4) whenever an exact event association exists.  
> **Attribution Lock:**  
> It is **STRICTLY PROHIBITED** to claim that the K.8 comparative software results demonstrate an empirical work-preservation advantage of P4 over P0–P3 resulting from quarantine. The empirical difference between P0 and P4 isolates **recovery action progression** (retry vs reinit vs degrade) and **association validation** (exact vs ambiguous fail-closed), but does **NOT** isolate quarantine vs non-quarantine.

### 3.2. S06 Multi-Policy Recovery Limitation
> [!CRITICAL]
> **Persistent Fault Recovery Limitation:**  
> On canonical scenario S06 (persistent I2C timeout):
> * P0 $\to$ `OUTCOME_TERMINAL_ESCALATE` (Digest: `0xFD5C2BA8`)
> * P1 $\to$ `OUTCOME_SUCCESS` (Digest: `0xA123BB47`)
> * P2 $\to$ `OUTCOME_SUCCESS` (Digest: `0xCDAB2617`)
> * P3 $\to$ `OUTCOME_SUCCESS` (Digest: `0xA123BB47`)
> * P4 $\to$ `OUTCOME_SUCCESS` (Digest: `0xA123BB47`)
> 
> **Attribution Lock:**  
> It is **STRICTLY PROHIBITED** to claim that P4 is uniquely superior on persistent faults. The recovery success on S06 is shared by P1, P2, P3, and P4 because all four implement peripheral reinitialization (`ACT_REINIT_OR_RESET`) on attempt 3. The advantage over P0 is attributable to **peripheral recovery capability**, not uniquely to P4's integrated policy.

### 3.3. W09 and W10 Capacity Confound
> [!IMPORTANT]
> **Capacity Confounding Lock:**  
> Workloads W09 and W10 explicitly record `capacity_confounded=1`:
> * W09 tests the `QMAX=16` admission boundary (`OUTCOME_QUEUE_FULL`).
> * W10 tests the `EPMAX=1` concurrency boundary (`OUTCOME_EPISODE_FULL`).
> 
> **Attribution Lock:**  
> Terminal outcomes in W09 and W10 reflect table capacity boundaries, not recovery intelligence. They must remain qualified as capacity-confounded and must not be cited as evidence of policy failure or policy superiority.

### 3.4. Software-Only Scope Boundary
> [!WARNING]
> **Hardware Non-Claims Lock:**  
> The current experimental evidence is generated exclusively within a host ISO C11 runtime and bounded virtual embedded simulation. The evidence **DOES NOT** establish:
> 1. Physical MCU cycle-level execution timing or latency.
> 2. STM32U575 physical RAM or Flash overhead.
> 3. Hardware MPU fault handling or memory protection boundaries.
> 4. Physical I2C/SPI bus arbitration, electrical noise, or clock-stretching phenomena.
> 5. Physical power consumption or energy profile.
> 6. Asynchronous interrupt preemption behavior.

### 3.5. Prohibited Research Claims
> [!CAUTION]
> **Prohibited Claims Lock:**  
> The following claims are formally prohibited from Part II conclusions:
> 1. **No Universal Superiority:** P4 must not be claimed as universally superior to P1–P3 across all embedded scenarios.
> 2. **No Statistical Significance Claims:** The 14 workloads and 6 scenarios are purposive deterministic test vectors; no inferential statistics (p-values, ANOVA, confidence intervals) may be claimed.
> 3. **No Novelty or Patentability Claims:** Software verification does not establish patentability, prior art clearance, or formal novelty.
> 4. **No Universal Generalization:** Results apply strictly to the evaluated workload/scenario matrix.

---

## 4. Scenario Scope Clarification: Full Set (S01–S14) vs Evaluated Subset (6 Scenarios)

The relationship between the 14 conceptual scenarios defined in Gate E/K.5 and the 6 virtual demonstrator scenarios evaluated in K.8 is formally clarified below:

### 4.1. The 14 Conceptual Scenarios (S01–S14)
Defined in `research/part_ii_deterministic_scenarios_k5.md`, S01 through S14 represent the comprehensive design space of fault scenarios. All 14 scenarios are covered in the **Host Experiment Corpus (W01–W14)**, which executes across all 5 policy variants (70 runs).

### 4.2. The 6 Canonical Virtual Demonstrator Scenarios
The K.8 virtual demonstrator comparison evaluates a focused subset of 6 canonical scenarios:

| Scenario | Name | Workload Mapping | Invariant Evaluated | Selection Rationale |
| :---: | :--- | :---: | :--- | :--- |
| **S01** | Independent Preservation | W02 | Gate A Work Preservation | Validates that unassociated events continue execution during quarantine. |
| **S02** | Ordered Dependency Blocking | W03 | Gate A Dependency Safety | Validates that dependent events remain safely blocked in `ST_QUEUED`. |
| **S05** | Transient Retry Recovery | W01 | Gate C Transient Recovery | Validates single-attempt transient fault recovery with 1:1 trace correlation. |
| **S06** | Persistent Fault Escalation | W06 | Gate C Multi-Attempt Progression | Differentiates blind retry (P0) from peripheral recovery (P1–P4). |
| **S08** | Ambiguous Association Isolation | W12 | Gate B/C Association Safety | Validates fail-closed termination without synthetic `EventRef` fabrication. |
| **S14** | Mixed Dependencies & Replay | W14 | Gate E Determinism & Replay | Combines chained dependencies and transient recovery to verify digest stability. |

### 4.3. Scope Alignment
* **Host Corpus:** 14 workloads (W01–W14) $\times$ 5 policies = **70 host runs**.
* **Virtual Demonstrator:** 6 canonical scenarios $\times$ 5 policies = **30 virtual runs**.
* **Total Software Evaluation Matrix:** Exactly **100 deterministic executions**.
* **Scope Guarantee:** Neither set has been silently modified. The 6 virtual demonstrator scenarios provide interactive, step-level visualization of the primary behavioral classes tested in the broader 14-workload host corpus.

---

## 5. Formal Attribution Matrix

Based on the locked methodology and empirical evidence, valid and invalid claims are codified below:

| Empirical Observation | Valid Attribution | Invalid / Prohibited Claim |
| :--- | :--- | :--- |
| **P0 escalates on persistent fault (W06/S06); P1–P4 succeed.** | Peripheral reinitialization (`ACT_REINIT_OR_RESET`) recovers from persistent bus errors where blind retry fails. | P4 is uniquely superior to P1–P3 on persistent faults. |
| **P0 yields `OUTCOME_STALE_REF` on ambiguous fault (W12/S08); P4 escalates cleanly.** | P4 enforces exact association (`assoc == ASSOC_EXACT`), failing closed safely and closing the episode without fabricating synthetic EventRefs. | P4 eliminates all ambiguous faults or recovers unassociated hardware errors. |
| **P0 escalates deferable work (W07); P1–P4 degrade.** | Policy awareness of criticality allows non-critical work to be degraded rather than halting the system. | Degradation is a mechanism unique to P4. |
| **Unassociated events execute during quarantine (W02/S01).** | Quarantine isolates the fault-associated event while ordinary dispatch continues for independent work. | P4 has superior work preservation over P0–P3 in this software harness. |
| **100/100 runs reproduce identical digests.** | The C reference runtime and virtual adapter exhibit deterministic, reproducible execution. | Real-time firmware running on physical silicon will be jitter-free or deterministic. |

---

## 6. Methodology Lock Sign-Off

* **Experimental Definitions:** Frozen across Items A through O.
* **Attribution Boundaries:** Formally locked in Section 3 and Section 5.
* **Scenario Scope:** Formally clarified in Section 4.
* **Authoritative Runtime:** Verified 100% unchanged (`ref_runtime.c`, `ref_runtime.h`).
* **Status:** **METHODOLOGY LOCKED — READY FOR FINAL RE-VERIFICATION**
