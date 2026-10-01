# Phase 1 — Final Evidence-Bounded Synthesis

**Checkpoint:** Chat K.3  
**Date:** 2026-10-01  
**Branch:** experiment/host-p0-p4-corpus-2026-10-01  
**Scope:** Final synthesis and repository packaging after K.1 host-experiment verification and K.2 host-corpus validation.

## 1. Executive status

The project has reached a coherent **host/reference final-synthesis checkpoint** for the current stage.

Gates A-E remain frozen and normative. The minimal ISO C11 host reference implementation and its deterministic P0-P4 experiment harness have been executed and inspected in the user-controlled Windows/MSVC environment. K.1 established successful build/test and matched harness execution; K.2 validated the regenerated corpus at the run/trace level.

This checkpoint does **not** establish MCU or physical validation.

## 2. Evidence matrix

| Evidence class | What is established | What it does not establish |
|---|---|---|
| Frozen design/specification | Gates A-E define event/dependency semantics, evidence-bounded fault association, bounded recovery policy, formal properties, and the experimental protocol. | It is not empirical evidence that the design performs as hypothesized on hardware. |
| Host/reference correctness | The committed reference builds under the verified Windows/MSVC environment; CTest passed 2/2; the reference exercises W01-W14, bounded recovery, trace metadata, and static-accounting checks. | Not proof of arbitrary firmware correctness, compiler/target equivalence, timing correctness, or hardware behavior. |
| Host corpus/reproducibility | 70 matched runs cover W01-W14 × P0-P4. K.1/K.2 verified deterministic replay, matched-input equivalence, raw-input preservation, explicit capacity-confound flagging, and ablation-contract flagging. Representative traces were internally coherent in the inspected fields. | Not statistical evidence, external validation, or proof that the integrated mechanism outperforms the baselines. |
| MCU evidence | **Absent.** | No STM32U575 timing, RAM/Flash, interrupt behavior, MPU behavior, peripheral-driver behavior, or MCU resource measurements are established. |
| Physical fault/recovery evidence | **Absent.** Faults were injected deterministically in software. | No electrical fault behavior, physical peripheral failure, physical recovery, energy, or board-level robustness is established. |
| Remaining ablation/evidence limitations | P0-P3 are not clean quarantine ablations; W09/W10 are capacity-confounded. P4 is the only variant marked valid under the current implementation boundary. | The current corpus cannot support a clean causal isolation of dependency-aware quarantine or an unconstrained interpretation of W09/W10. |

## 3. What the evidence supports

### 3.1 Implementation correctness vs research-hypothesis support

The current evidence supports the narrower statement that the **host reference implementation and experiment harness behave reproducibly under the tested deterministic scenarios and declared checks**.

It does not establish the broader research hypothesis that the integrated mechanism reduces collateral service disruption on a constrained MCU, nor does it establish acceptable MCU CPU/RAM/Flash cost. Those require target-specific experiments.

### 3.2 Harness correctness vs policy correctness

The K.1/K.2 PASS results primarily establish properties of the **experiment machinery**: matched inputs, deterministic replay, preservation of raw inputs, explicit confound metadata, and declared ablation-contract handling.

The reference tests and inspected traces provide additional evidence about modeled lifecycle, recovery, identity, dependency, and outcome behavior. However, a harness PASS must not be described as proof that P4 is superior, or as proof that every frozen Gate-E policy comparison is causally isolated.

### 3.3 Reproducibility vs external validity

The 70-run corpus is reproducible within the committed host/reference environment and deterministic input schedule. Reproducibility means the declared experiment can be regenerated consistently; it does not establish that the observations transfer to different workloads, compilers, processors, firmware timing regimes, peripherals, or physical fault mechanisms.

### 3.4 Model-level evidence vs hardware evidence

Gates A-D and the bounded host implementation provide model/design evidence. The host corpus provides executable reference evidence under software injection. Neither substitutes for MCU execution.

In particular, the documented host sizes (Runtime=8164, EventSlot=84, TraceRecord=24, trace pool 6144) are host C-layout observations only and must not be presented as STM32U575 RAM/Flash measurements.

## 4. Required qualifications

### P0-P3 ablation limitation

The current implementation's runtime_start_fault() applies exact-event quarantine across all policy variants. Therefore P0-P3 are **not clean quarantine ablations** under the frozen Gate C/E definitions.

The repository deliberately preserves this qualification:

- ablation_contract_valid=0 for P0-P3;
- ablation_contract_valid=1 for P4 under the current implementation boundary.

No variant semantics were redefined during K.3.

### W09/W10 capacity limitation

W09 and W10 are capacity-confounded by the declared fixed resource boundaries. They remain useful as explicit capacity-boundary scenarios, but they must not be treated as unconstrained policy comparisons.

### Host-only boundary

The corpus is host/reference + deterministic software-injection evidence only. No MCU or physical-fault evidence is present.

## 5. What remains unvalidated

1. STM32U575ZI/NUCLEO-U575ZI-Q build and execution.
2. Actual MCU RAM/Flash footprint.
3. MCU timing/latency and scheduling behavior.
4. MPU configuration and containment behavior on target hardware.
5. Real I2C/SPI/UART peripheral behavior under controlled faults.
6. Physical fault-injection and recovery observations.
7. Energy/power measurements if included in the eventual evaluation.
8. Clean implementation of the intended P0-P3/P4 semantic contrast, if causal ablation evidence is required.
9. Repetition and statistical analysis appropriate to a future empirical study.
10. External-validity testing across additional workloads/fault conditions.
11. Any defensible novelty or patentability assessment based on the final implementation and complete prior-art record.

None of these missing items is silently inferred from the host corpus.

## 6. Reproducibility entry point

From reference/:

    cmake -S . -B build
    cmake --build build
    ctest --test-dir build --output-on-failure
    python3 experiments/run_host_experiment.py

For the verified Windows/MSVC checkpoint, use the repository's documented Windows build/launcher path and run the harness with its --check validation mode as recorded in the K.1 continuity record.

The experiment inputs are committed in reference/experiments/workloads.csv and reference/experiments/fault_schedules.csv. Generated out/ and out.replay/ directories are transient verification artifacts and are not required committed source artifacts.

## 7. Final checkpoint interpretation

The defensible current claim is:

> The project has a frozen, internally documented Gates A-E design; a bounded zero-heap host/reference implementation; and a reproducible deterministic host corpus covering the declared W01-W14 × P0-P4 matrix, with explicit visibility of the P0-P3 ablation-contract limitation, W09/W10 capacity confounds, and the absence of MCU/physical evidence.

The project should not currently be described as hardware-validated, statistically established, externally generalized, novel, or patentable on the basis of this checkpoint.

## 8. Archive/continuation boundary

**K.3 COMPLETE — Final host/reference synthesis checkpoint.**

No further work is implied by this checkpoint. If the project is resumed, the next work should be selected explicitly from the deferred validation list rather than inferred as an automatic continuation.

Historical Gates A-E, K.1, and K.2 artifacts remain preserved.

## 9. 2026-10-01 Software-Phase Supersession

K.3 remains a completed historical checkpoint. The active continuation is now the integrated software demonstrator and methodology-lock phase recorded in `research/phase1_software_demonstrator_methodology_lock.md`. Professor verification is part of that integrated phase, not a separate stage.

The software-phase conclusion is bounded: the mechanism is sufficiently specified, implemented, reproducible, demonstrable, and evidence-bounded to justify target-MCU validation. Hardware performance, statistical superiority, final novelty, and patentability remain unvalidated.
