# Chat Record — K.10 P4 Advantage & Novelty Investigation

Date: 2026-10-01  
Checkpoint: K.10  
Branch: `exp`  
Status: **K.10 COMPLETE**

## 1. Objective
Execute **K.10: P4 Advantage & Novelty Investigation** to determine from controlled experiments and adversarial prior-art analysis:
1. Whether P4 demonstrates a measurable, reproducible, and attributable advantage over baselines P0–P3;
2. What trade-offs and costs P4 introduces;
3. Which observed differences are genuinely attributable to P4 rather than shared mechanisms;
4. Whether the proposed mechanism remains technically distinguishable under adversarial prior-art decomposition.

## 2. Experimental Execution
- **Harness:** `reference/experiments/k10_experiment.c` and `reference/experiments/evaluate_k10_advantage.py`.
- **Case Matrix:** 16 Case Families (CF01–CF16) covering persistent faults, queue pressure, dependencies, ambiguity, recovery failure, subsequent faults, criticality, load controls, negative controls, and baseline-cost controls.
- **Policies Executed:** P0, P1, P2, P3, P4.
- **Repetitions:** 5 deterministic repetitions per case family per variant = **400 matched executions**.
- **Determinism:** 100% bit-for-bit identical results across all 5 repetitions.
- **Test Suite Status:** Full CTest regression suite passing 8/8 tests (100%).
- **Raw Data Location:**
  - `reference/experiments/out/k10_runs.csv`
  - `reference/experiments/out/k10_traces.csv`

## 3. Key Findings

### 3.1. Genuine P4 Advantages
- **Association Ambiguity (CF04, CF07):** P4 strictly enforces `association == ASSOC_EXACT`, safely failing closed to `TERMINAL_ESCALATE` and closing the episode. Baselines P0–P3 attempt retry on invalid targets (`OUTCOME_STALE_REF`) and leave episodes unclosed (`ACTIVE`), causing subsequent faults to fail with `OUTCOME_EPISODE_FULL`.
- **Bounded Ladder Termination (CF05):** Under repeated recovery faults, P4 enforces the exact Gate C ladder ($T_1 \to T_2 \to T_3 \to T_4$) and terminates cleanly at attempt 3, avoiding unbounded reinit loops present in P2/P3.

### 3.2. Shared Mechanisms (No P4 Superiority)
- **Work Preservation (CF02, CF14):** Work preservation under quarantine is 100% identical across all variants (P0–P4) because `ref_runtime.c` applies exact-event quarantine across all variants.
- **Persistent Fault Recovery (CF01, CF10):** Recovery from persistent faults is achieved by P1, P2, P3, and P4 via peripheral reinitialization (`ACT_REINIT_OR_RESET`).

### 3.3. Measured Trade-Offs (Baseline Advantages)
- **Known Persistent Fault Cost (CF16):** When a fault is known persistent a priori, P2 (history-blind) immediately reinitializes on attempt 0 (1 attempt), whereas P4 retries twice first, taking 3 attempts.
- **Decision Overhead:** P0 evaluates 1 branch; P4 evaluates up to 6 conditions.

### 3.4. Negative Controls
- 6 out of 16 case families (CF02, CF09, CF11, CF12, CF13, CF15) demonstrated zero difference between P4 and baselines.

## 4. Adversarial Prior-Art Assessment
- Individual mechanisms (peripheral reset, retry ladder, message quarantine, dependency blocking, static pools) are all established in prior art (PA-01 through PA-10).
- No single reference discloses the complete zero-heap MCU runtime combination.
- Recombination/obviousness rejection remains technically plausible based on PA-01, PA-03, and PA-04.

## 5. Final Classifications
- **Experimental Performance:** `Demonstrated bounded advantage`
- **Integrated Prior Art:** `Potentially distinguishable combination — further legal/technical review required`

## 6. Runtime Integrity
- `reference/src/ref_runtime.c` and `reference/include/ref_runtime.h` were **100% untouched** (verified by SHA256 hashes and git diff).
- Gates A–E remain frozen.
- K.11 has NOT been started.


---

## Post-K.10 closure correction — 2026-10-02

The K.10 result is accepted as complete. The CF16 wording is treated as an attempt-count/software-model cost comparison, not physical speed. H4 is interpreted as confirmation that individual mechanisms/sub-combinations are established, not as confirmation that the complete P4 combination is anticipated.

The active next checkpoint is K.10.1. K.10.1-K.10.4 are intentionally inserted before K.11 so the unresolved technical distinction is attacked before final synthesis.
