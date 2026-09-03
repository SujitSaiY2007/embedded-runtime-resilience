# Current Handoff

## Session status

Phase 0 topic validation and Phase 1 system-design preparation are complete. The development topic is frozen. Phase 1E.1 — Experimental Design / Formalization Foundation — is now complete through Gate E.

**Gate A — Exact Event Model and Dependency Semantics: COMPLETE.**  
**Gate B — Fault Model + Fault Association: COMPLETE.**  
**Gate C — Recovery Policy + Bounded State Machine: COMPLETE.**  
**Gate D — Formal Properties + Proof/Check Strategy: COMPLETE at the semantic/design-model level.**  
**Gate E — Baselines + Experimental Protocol: COMPLETE at the experimental-design/protocol level.**

The next chat must begin **Minimal Reference Implementation — smallest testable reference prototype**.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

**Short working title:** Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine

## Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Gates A–D remain normative

Gate A freezes `EventRef = {slot_id, generation}`, separate transaction identity, explicit `INDEPENDENT`/`ORDERED`/`COUPLED/TRANSACTIONAL` dependencies, FIFO admission versus eligibility-driven execution, retained non-executable quarantine, and preservation as verified execution.

Gate B freezes the primary I2C fault observations: NACK, timeout/no-progress, bus/protocol error, arbitration loss, and persistent no-progress/suspected peripheral-state failure. Association levels are `EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS`, under `association precision <= evidence precision`.

Gate C freezes minimum policy context (`fault_class`, `association_level`, bounded `attempt_count`, `criticality`, `recovery_safety`, `episode_state`), actions `RETRY`, `REINIT_OR_RESET`, `DEGRADE`, `ESCALATE`, and the exact four-action bound `T1=RETRY #1 -> T2=RETRY #2 -> T3=REINIT_OR_RESET -> T4=terminal`.

Gate D formalizes quarantine, association, preservation/blocking, dependency, termination, bounded resource, EventRef, release, transaction, and deterministic decision-table properties. Its host audit covered 33,792 bounded contexts with one deterministic outcome per encoded context; this remains model-level evidence only.

## Gate E checkpoint

Final artifact: `research/phase1_gateE_experimental_protocol_final.md`

Gate E freezes the experimental bridge from the semantic model to implementation/evaluation.

### Comparison variants

- **P0:** fixed retry baseline.
- **P1:** fixed retry + bounded peripheral recovery.
- **P2:** context-only ablation.
- **P3:** context + episode-history ablation.
- **P4:** integrated context + history + dependency-aware event quarantine.

P0/P1 are the principal baselines; P2/P3 isolate mechanism contributions; P4 is the proposed integrated mechanism. Historical baseline terminology is retained rather than silently collapsed.

### Canonical workloads

W01 independent queue preservation; W02 ordered dependency blocking; W03 coupled transaction containment; W04 shared-peripheral non-causality; W05 retry-success; W06 retry-failure then reinit/reset success; W07 terminal degradation; W08 terminal escalation; W09 queue-capacity boundary; W10 quarantine-capacity boundary; W11 stale EventRef generation; W12 association ambiguity; W13 criticality/degradability; W14 mixed ordered/coupled/independent integrated workload.

### Frozen protocol envelope

`QMAX=16`, `XMAX=4`, `DMAX=4`, and `EPMAX=1` for the normative reference prototype unless an explicit amendment is made. These are reproducible protocol parameters, not universal optimality claims. Capacity-confounded runs must be flagged rather than interpreted as recovery benefit.

Generation width/wrap remains an implementation detail that must be concretely fixed before implementation and must fail closed for stale references.

### Fault and outcome schedule

Deterministic software injection is the primary repeatable stimulus. Core I2C classes are F-I2C-01 NACK, F-I2C-02 timeout/no-progress, F-I2C-03 bus/protocol error, F-I2C-04 arbitration loss as secondary/conditional, and F-I2C-05 persistent no-progress. Recovery schedules cover first-retry success, second-retry success, reinit/reset success after two failed retries, terminal degradation, and terminal escalation.

### Metrics

Correctness includes quarantine violations, stale-reference mis-targeting, incorrect attribution, preserved independent events, correctly blocked dependent events, incorrect blocking/loss, lost/duplicated events, invalid coupled execution, recovery-bound violations, premature release, and terminal re-entry. Performance/resource metrics include detection/restoration latency, recovery success/failure, reset/escalation count, queue/quarantine occupancy, CPU, RAM, and Flash. Energy is optional only after valid instrumentation exists.

### Evidence boundary

Host results support model/software-fault behavior only. MCU results are required for actual implementation timing/resource claims. Physical-fault claims require hardware and validated physical/protocol injection. Generalization requires additional workloads/interfaces/fault conditions. Novelty/patentability require separate evidence and assessment.

## Exact next task — Minimal Reference Implementation

Do **not** redesign Gates A–E without identifying a genuine contradiction. Do not start by building a general resilience framework.

The next chat must:

1. reconstruct the repository from `main` and read the continuity documents;
2. define the smallest executable host/reference prototype implementing the frozen semantic contracts;
3. concretely choose and document the fixed storage layout, generation width/wrap behavior, scheduler selection rule, event/quarantine representation, episode record, and policy-decision interface;
4. implement deterministic software fault injection and the canonical workload traces needed for the Gate E correctness suite;
5. add host-side assertions/property tests for the Gate D obligations;
6. preserve zero-heap behavior and produce explicit static resource accounting;
7. keep MCU-specific code and physical bring-up separate from the host reference until the reference behavior is stable;
8. avoid premature optimization or framework expansion;
9. update state/handoff/decision documents only with consequential implementation decisions;
10. stop at the smallest testable reference checkpoint before broad MCU integration unless the next chat explicitly establishes a new stopping boundary.

The first implementation objective is **testability and traceability**, not feature breadth.

## Research honesty

Do not fabricate hardware availability, MCU measurements, benchmarks, energy measurements, physical fault injection, statistical significance, novelty, or patentability. Host simulation/software injection is not physical validation.

## Chat boundary

**Gate E is closed. This handoff stops before firmware implementation.**

The next chat begins:

**Minimal Reference Implementation — smallest testable reference prototype**
