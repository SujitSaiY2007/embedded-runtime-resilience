# Phase 1E.1 — Gate E Final Experimental Protocol

**Gate:** E — Baselines + Experimental Protocol  
**Phase:** 1E.1 — Experimental Design / Formalization Foundation  
**Status:** ACCEPTED at the experimental-design/protocol level; implementation, MCU measurement, and physical validation remain deferred.  
**Date:** 2026-09-03

## 1. Purpose and acceptance boundary

Gate E freezes the smallest reproducible experimental protocol needed to evaluate the frozen research question using Gates A–D as normative contracts.

The protocol is designed to answer whether the integrated mechanism — zero-heap context-aware bounded recovery with dependency-aware event quarantine — provides measurable service-preservation benefit without unacceptable resource cost, relative to matched recovery baselines.

Gate E does **not** claim:

- firmware correctness on the STM32U575;
- physical fault-injection success;
- benchmark results;
- energy measurements;
- statistical significance;
- generalization beyond the tested workload/fault domain;
- novelty or patentability.

No Gate A–D semantic rule is silently changed by this protocol.

## 2. Normative inputs

The protocol treats the following as normative:

1. `research/phase1_gateA_event_model_final.md`
2. `research/phase1_gateB_fault_model_final.md`
3. `research/phase1_gateC_recovery_policy_final.md`
4. `research/phase1_gateD_formal_properties_final.md`

Historical baselines remain retained:

- `research/phase1_event_model.md`
- `research/phase1_peripheral_testbed_fault_model.md`
- `research/phase1_recovery_policy_design.md`

The platform direction remains **STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C primary, SPI secondary, and UART/USART diagnostic/control. Host execution is permitted before hardware acquisition; MCU and physical claims require later hardware evidence.

## 3. Experimental hypothesis and variables

### 3.1 Primary hypothesis

Compared with fixed retry/recovery baselines, the integrated policy can reduce collateral disruption to valid independent queued work during a peripheral/service fault while retaining bounded recovery behavior and acceptable CPU/RAM/Flash overhead.

### 3.2 Secondary hypotheses

1. Local fault context can select a more appropriate bounded action than fixed retry alone for heterogeneous fault classes.
2. Short episode history can distinguish transient recovery from persistent failure without requiring unbounded history.
3. Dependency-aware event quarantine can preserve valid independent work while correctly blocking ordered/coupled work that is unsafe to execute.
4. The integrated mechanism's correctness benefit is not explained merely by using larger queues or by aggressively blocking work.

### 3.3 Independent variables

- policy variant;
- fault class;
- association level;
- fault position within workload;
- dependency class;
- criticality class;
- recovery outcome schedule;
- queue/quarantine pressure condition;
- implementation target (host reference model versus later MCU prototype).

### 3.4 Controlled variables

Unless a scenario explicitly varies them, keep fixed:

- workload event sequence and event metadata;
- queue and quarantine capacities;
- dependency declarations;
- event/transaction identities;
- fault injection point;
- verification rules;
- scheduler selection rule;
- compiler/build configuration for a given measurement campaign;
- diagnostic logging format;
- reset/warm-up policy;
- test oracle and acceptance rules.

### 3.5 Dependent variables

Correctness, service-preservation, recovery, latency, occupancy, CPU, RAM, Flash, and later hardware-specific measurements defined in Section 8.

## 4. Baseline reconciliation and comparison matrix

Gate C defines the ablation sequence P0–P4. Earlier project planning also described fixed retry, fixed retry plus peripheral reset/reinitialization, and the proposed integrated mechanism. These descriptions are reconciled without deleting either history.

### 4.1 Frozen variants

| ID | Variant | Purpose |
|---|---|---|
| P0 | Fixed retry | Minimal recovery baseline. Repeats the declared retry action using a fixed retry policy; no context/history/quarantine intelligence. |
| P1 | Fixed retry + peripheral recovery | Stronger conventional baseline: fixed retry ladder followed by bounded peripheral reinitialization/reset when configured. |
| P2 | Context-only | Ablation: fault context changes the action selection, but no episode-history contribution and no dependency-aware quarantine contribution. |
| P3 | Context + episode history | Ablation: context plus bounded episode progression/history, without the full dependency-aware quarantine mechanism. |
| P4 | Integrated context + episode history + dependency-aware event quarantine | Proposed mechanism under test. Uses the full Gate A–D contract. |

P0–P4 are retained because they answer different questions. P0/P1 are the principal recovery baselines; P2/P3 are mechanism ablations; P4 is the integrated proposal.

### 4.2 Exact comparability rule

A comparison is valid only when the following are identical between variants:

- same workload event trace;
- same event/dependency metadata;
- same fault schedule and affected event/transaction;
- same association evidence presented to the variant, except where a variant intentionally lacks a policy feature;
- same verification oracle;
- same capacity configuration for the primary matched comparison;
- same scheduler and execution model;
- same logging boundaries for measured quantities.

A variant must not receive a hidden advantage through extra queue capacity, extra retries, different fault timing, or a different success oracle.

### 4.3 What the ablation establishes

P0 versus P1 isolates the value of bounded peripheral-local recovery beyond retry. P1 versus P2/P3/P4 shows whether adaptive policy context/history adds value over conventional recovery. P2 versus P3 isolates the contribution of episode history. P3 versus P4 isolates the contribution of dependency-aware event quarantine and its interaction with the integrated policy.

The results may show that an ablation is redundant or inferior; that is an experimental result, not a reason to remove the variant from the protocol.

## 5. Frozen workload matrix

All core workloads use a fixed, explicitly recorded event trace. Each event has Gate A metadata including `EventRef`, service, peripheral, criticality, dependency class, and transaction identity where applicable.

### W01 — Independent queue preservation

Queue multiple independent valid events sharing the same peripheral as a fault-associated event. Inject a fault into one exact event. The expected behavior is quarantine/containment of the fault-associated target while eligible independent events execute and verify correctly.

### W02 — Ordered dependency blocking

Create predecessor `E1 -> E2` with `ORDERED` dependency. Fault/quarantine `E1`. `E2` must remain blocked until its declared acceptable predecessor condition is reached. Independent events may proceed where eligible.

### W03 — Coupled transaction containment

Create a multi-event logical transaction. Fault one member. The other member(s) must not execute independently unless the transaction contract explicitly permits the transition. Invalid partial transaction execution is a correctness failure.

### W04 — Shared-peripheral non-causality

Queue several events using the same I2C peripheral but give them distinct transaction identities and explicit dependency relationships. Fault one event. Same-peripheral membership alone must not cause event-level attribution or indiscriminate quarantine.

### W05 — Transient NACK: retry success

Inject `F-I2C-01` at a declared event/transaction. Verification succeeds after the first permitted retry. This exercises `T1=RETRY #1` and successful release through Gate A eligibility.

### W06 — Repeated failure: retry then reinitialization/reset

Inject a fault schedule in which both retry verifications fail and the single `REINIT_OR_RESET` action succeeds. This exercises `T1 -> T2 -> T3` and verifies that release occurs only after action and event/service verification plus Gate A eligibility.

### W07 — Persistent failure: terminal degradation

Inject persistent no-progress/failure for a service with a declared safe degraded contract. The episode must terminate in `DEGRADE` within the four-action budget while unrelated safe work remains eligible.

### W08 — Persistent failure: terminal escalation

Inject persistent failure for a service with no safe degraded contract, or otherwise prohibit local recovery. The episode must terminate in `ESCALATE` within the four-action budget. Terminal state must not re-enter recovery.

### W09 — Queue capacity boundary

Exercise normal queue occupancy at, below, and above the selected `QMAX`. Record admission/rejection/defer outcomes. The scenario must distinguish legitimate overflow handling from recovery benefit.

### W10 — Quarantine capacity boundary

Exercise multiple simultaneous retained quarantined events up to `XMAX` and beyond. The test must expose the declared bounded behavior without silently allocating additional storage.

If the reference implementation supports only one active recovery episode, the workload must explicitly verify that this is a design constraint rather than accidentally depending on unbounded episode storage.

### W11 — Stale EventRef generation

Reuse a fixed event slot after terminal completion and present an old `{slot_id, generation}` reference. The old reference must fail closed and must not target the newly admitted event.

### W12 — Association ambiguity matrix

Exercise `EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS` cases. Verify that attribution/quarantine scope never becomes more precise than the evidence permits.

### W13 — Criticality and degradability

Repeat representative fault cases across `CRITICAL`, `NORMAL`, and `DEFERABLE` services. Verify that criticality constrains degradation/escalation behavior but does not bypass dependency, quarantine, or shared-state safety.

### W14 — Coupled/ordered plus independent mixed workload

Combine all three dependency classes in one bounded trace. Fault a transaction while unrelated independent work remains queued. This is the primary integrated service-preservation workload because it simultaneously tests selective execution and correct blocking.

## 6. Deterministic software fault schedule

The primary experimental stimulus is deterministic software injection. Each fault injection record contains:

```text
FaultScheduleEntry {
    run_id
    workload_id
    fault_class
    injection_point
    affected_event_ref
    transaction_id_or_none
    association_level
    workload_position
    recovery_variant
    expected_verification_outcome
    schedule_seed_or_none
}
```

### 6.1 Core fault classes

The primary I2C schedule covers:

- `F-I2C-01` NACK/non-acknowledge;
- `F-I2C-02` timeout/no-progress deadline expiry;
- `F-I2C-03` bus/protocol error;
- `F-I2C-04` arbitration/bus-ownership error as a secondary/conditional case;
- `F-I2C-05` persistent no-progress/suspected peripheral-state failure.

SPI cases are secondary and use only fault evidence that the implementation can actually expose. They do not silently inherit I2C-specific semantics.

### 6.2 Injection positions

For each applicable workload, inject at a predeclared position such as:

- before transfer start;
- after address phase;
- during data transfer;
- at completion/verification;
- during recovery verification.

The exact implementation injection hook must be fixed before a measurement campaign and recorded in the trace metadata.

### 6.3 Recovery outcome schedules

At minimum, use deterministic schedules for:

- retry succeeds on first retry;
- first retry fails, second retry succeeds;
- both retries fail, reinit/reset succeeds;
- all local recovery actions fail and terminal degradation is safe;
- all local recovery actions fail and escalation is required.

No run may alter the schedule after observing the result.

### 6.4 Later physical-fault mapping

Physical validation, if hardware is available and a safe fixture is established, maps observations to the same semantic classes rather than creating an uncontrolled second taxonomy. For example, a physically observed NACK maps to `F-I2C-01`; a controller-reported `BERR` maps to `F-I2C-03`; repeated no-progress across the declared recovery sequence maps to `F-I2C-05` only when the observable persistence criteria are satisfied.

A physical cause may be recorded separately as an evidence note. It must not replace the semantic fault class without supporting evidence.

## 7. Capacity and finite-history protocol

### 7.1 Queue/quarantine/dependency capacities

Gate A provisional values are promoted to **protocol test configurations**:

- `QMAX = 16`
- `XMAX = 4`
- `DMAX = 4`

These are not claimed to be universally optimal. Gate E freezes them because they form a finite, reproducible envelope that supports the core workload and explicit boundary tests.

Adequacy must be reported empirically: if a nominal workload overflows these capacities in a way unrelated to the mechanism under study, the workload result is classified as capacity-confounded rather than as recovery benefit. Any later capacity change requires an explicit protocol amendment with rerun requirements.

### 7.2 Episode capacity (`EPMAX`)

The host-model protocol uses a **single active recovery episode** as the normative decomposition inherited from Gate D. Therefore:

`EPMAX = 1` for the reference implementation/protocol unless a later implementation design demonstrates a need for simultaneous independent episodes.

A later design that permits multiple simultaneous episodes must declare a finite `EPMAX`, account for its RAM cost, and add corresponding capacity-boundary workloads before using that implementation in a matched experiment.

### 7.3 Generation policy

The reference implementation must use a concrete finite generation width and explicit wrap rule. The protocol requirement is:

- stale references fail closed;
- generation reuse cannot occur while an older reference can still be valid;
- generation wrap is either prevented within the experimental lifetime or explicitly tested under a bounded wrap model.

The exact integer width is an implementation parameter and is not silently treated as part of the semantic protocol.

### 7.4 History window

The normative policy history is the active episode state and bounded attempt progression. No unbounded event history is required. Diagnostic observation counts may be recorded in fixed fields, but they are not policy inputs unless an explicit later amendment establishes decision necessity.

## 8. Metrics and measurement methods

### 8.1 Correctness metrics

Every run records counts for:

1. quarantine violations;
2. stale-reference mis-targeting;
3. incorrect event-level attribution;
4. preserved independent events;
5. correctly blocked dependent events;
6. incorrectly blocked/lost valid independent events;
7. lost events;
8. duplicated events;
9. invalid coupled-transaction execution;
10. recovery-action bound violations;
11. premature release;
12. terminal-state re-entry into recovery.

Required correctness targets are zero for violations that represent explicitly forbidden behavior, including quarantine violation, stale-reference mis-targeting, invalid coupled execution, recovery-bound violation, premature release, and terminal re-entry.

### 8.2 Service-preservation metrics

For each fault-associated event `Ei`, compute:

`PreservationRate(Ei) = preserved valid independent events / total valid independent events`.

Also report the counts of `PRESERVED`, `CORRECTLY_BLOCKED`, and `INCORRECTLY_BLOCKED/LOST`. Correct blocking is not a preservation failure.

### 8.3 Recovery metrics

Record:

- recovery success/failure;
- selected action sequence;
- attempts consumed;
- fault-detection latency;
- service-restoration latency where restoration occurs;
- terminal degradation/escalation outcome;
- whole-system reset/escalation count.

An attempt is one recovery-action invocation plus its verification, exactly as frozen in Gate C.

### 8.4 Queue/quarantine metrics

Record:

- queue occupancy at each defined observation point;
- queue high-water mark;
- quarantine occupancy;
- quarantine high-water mark;
- admission overflow/rejection/defer events.

Capacity-confounded runs must be flagged rather than interpreted as mechanism success/failure.

### 8.5 CPU measurement

Host: use a deterministic instrumentation method such as instruction/cycle proxy or wall-clock measurement only when its resolution and environment are fixed and documented. Host CPU results are reported as host measurements, not MCU CPU overhead.

MCU later: use a fixed hardware timing source/cycle counter or equivalent supported measurement method, with logging overhead characterized separately. Report recovery-path and scheduler-path cost separately where practical.

### 8.6 RAM and Flash

MCU later: derive static RAM/Flash footprint from the same reproducible build configuration and toolchain, and report both total image footprint and incremental footprint attributable to the recovery/reference mechanism where the build system permits an honest comparison.

Host memory measurements are not substituted for MCU RAM claims.

### 8.7 Energy

Energy is **not a required Gate E metric**. It may be added only after a valid, reproducible measurement method and instrumentation are available. No energy result may be inferred from CPU time.

## 9. Logging and trace-correlation schema

Every run must emit a machine-readable or equivalently structured trace with stable identifiers.

Minimum records:

```text
RunHeader {
    run_id
    protocol_version
    variant_id
    workload_id
    fault_schedule_id
    build_id
    target_type
    seed_or_deterministic_schedule_id
    reset_policy_id
}

EventTrace {
    trace_seq
    run_id
    event_ref
    transaction_id_or_none
    event_type
    service_id
    peripheral_id
    criticality
    dependency_class
    lifecycle_state
    timestamp_or_cycle
}

FaultTrace {
    trace_seq
    run_id
    fault_episode_id
    observation_seq
    fault_class
    association_level
    event_ref_or_none
    transaction_id_or_none
    evidence_flags
}

RecoveryTrace {
    trace_seq
    run_id
    fault_episode_id
    action_index
    action
    target_scope
    precondition_result
    verification_result
    release_permitted
    reason_code
}

OutcomeTrace {
    trace_seq
    run_id
    event_ref
    final_state
    preservation_class
    correctness_flags
}
```

`run_id`, `fault_episode_id`, `event_ref`, and `trace_seq` provide the minimum correlation path from workload admission through fault observation, recovery, release, and final outcome.

## 10. Repetitions, deterministic scheduling, and randomization

The primary protocol uses **deterministic schedules**, not uncontrolled random faults. Each canonical workload/fault/variant combination is therefore exactly reproducible.

For initial development and correctness qualification, a single canonical execution is sufficient to establish whether a deterministic trace violates a hard invariant. It is not sufficient for statistical performance claims.

For later performance campaigns:

- use a predeclared repetition count chosen before inspecting results;
- if randomized workload order is added, generate a fixed seed list before the campaign;
- use the same seed list across compared variants;
- randomize run order only at the outer experiment level so variant execution order cannot explain a result;
- preserve raw traces for every valid run.

No post-hoc repetition increase is permitted solely because an observed effect is inconvenient or non-significant.

## 11. Reset and warm-up policy

### Host model

Each canonical run begins from a freshly initialized model state. No state, event queue, quarantine record, or recovery episode carries over from another run.

### MCU later

Each run begins from a defined reset state appropriate to the measurement. If a warm-up phase is needed for clocks, caches, peripherals, or instrumentation, its duration/iteration count must be fixed before the campaign and excluded from the measured interval consistently across variants.

A whole-system reset caused by the policy is an outcome to record, not a free reinitialization between measurements.

## 12. Invalid-run policy

A run is invalid only for a predeclared protocol/measurement reason, such as:

- corrupted trace;
- missing mandatory identifier;
- instrumentation failure;
- build mismatch;
- external host/MCU fault that prevents execution of the declared protocol;
- physical safety interruption.

A run is **not** invalid merely because the policy fails, loses an event, escalates, or produces an undesirable metric. Those are experimental outcomes.

Invalid runs must retain their available raw artifacts and reason code. They are excluded from the corresponding statistical estimate only under the predeclared rule and are reported in the run accounting.

## 13. Statistical and reproducibility treatment

Gate E does not prescribe a numerical effect-size threshold or p-value threshold in advance because the project has not yet established a justified variance model or sample-size basis.

Later analysis must report, at minimum:

- sample count and exclusions;
- central tendency appropriate to the metric;
- dispersion/uncertainty;
- paired comparison where the same workload/fault schedule is used across variants;
- effect size or absolute/relative difference where meaningful;
- raw trace availability and protocol/build identifiers.

Correctness-violation counts are treated as safety outcomes, not traded against a small performance gain.

## 14. Acceptance criteria and reporting format

### 14.1 Gate-level acceptance

Gate E is accepted when the repository contains:

- a frozen matched comparison matrix;
- a complete workload matrix covering required event/dependency/fault/recovery/capacity cases;
- a deterministic fault schedule definition;
- fixed protocol capacities and finite episode assumptions;
- correctness and performance/resource metrics with measurement methods;
- trace/logging identifiers;
- repetition/randomization and reset policy;
- invalid-run handling;
- explicit separation of host, MCU, and physical evidence;
- reporting requirements and evidence boundaries.

This acceptance is a **protocol-design acceptance**, not an experimental-result acceptance.

### 14.2 Later experiment reporting template

Each result table/figure must identify:

- variant;
- workload;
- fault schedule/class;
- target type;
- capacity configuration;
- repetitions/valid runs;
- correctness outcomes;
- latency/resource measurements;
- exclusions and reasons;
- uncertainty/paired-analysis method where applicable.

### 14.3 Minimum evidence before claims

**Performance claim:** requires MCU measurements from a reproducible build and timing/resource method, not host timing alone.

**Robustness claim:** requires repeated matched fault scenarios and correctness evidence; software injection alone supports only the tested semantic/software-fault domain.

**Physical-fault claim:** requires actual hardware execution and validated physical/protocol injection evidence.

**Generalization claim:** requires additional interfaces/workloads/fault conditions beyond the original canonical matrix.

**Novelty claim:** requires separate prior-art analysis; experimental success alone does not establish novelty.

## 15. Host versus MCU versus physical evidence boundary

| Evidence | What it can support | What it cannot support by itself |
|---|---|---|
| Host semantic/model execution | deterministic policy behavior, invariants, trace logic, capacity logic | MCU timing, actual RAM/Flash, peripheral electrical behavior |
| Host software fault injection | reproducible comparison of semantic fault handling | physical fault mechanism, electrical robustness |
| MCU software injection | actual implementation correctness/timing/resource behavior under injected conditions | physical reproduction of the injected fault |
| MCU physical/protocol fault injection | hardware-relevant behavior for the validated fixture and condition | universal fault coverage or arbitrary root-cause claims |
| Repeated matched experiments | empirical effect estimates within tested domain | universal/generalized resilience |

## 16. Experimental confound controls

The following are explicit threats to validity and must be checked during implementation/experiments:

1. **Capacity confounding:** a variant must not appear better simply because it has more storage.
2. **Blocking confounding:** aggressive blocking must not be scored as preservation.
3. **Fault-schedule confounding:** compared variants receive identical fault timing and outcomes.
4. **Logging overhead:** instrumentation must be fixed or separately characterized.
5. **Build confounding:** compiler/toolchain/configuration must be matched for comparable MCU measurements.
6. **Recovery-cost omission:** peripheral recovery time must be included in recovery latency when it is part of the tested policy path.
7. **Dependency leakage:** an event cannot be called independent merely because it lacks direct fault association.
8. **Attribution leakage:** same-peripheral membership cannot create false event-level association.
9. **Host/MCU substitution:** host results cannot be presented as MCU measurements.
10. **Physical overinterpretation:** a semantic fault injection cannot be described as a physical fault validation.

## 17. Decision freeze

Gate E freezes the following protocol decisions:

- five-variant comparison set P0–P4;
- P0/P1 as principal baselines and P2/P3 as ablations, with P4 as the integrated proposal;
- fourteen canonical workloads W01–W14;
- deterministic software fault scheduling as the primary repeatable stimulus;
- I2C as primary fault domain and SPI as secondary;
- `QMAX=16`, `XMAX=4`, `DMAX=4` as the reproducible protocol envelope;
- `EPMAX=1` for the normative reference prototype unless explicitly amended;
- bounded episode-state history rather than unbounded history;
- fixed trace identifiers and structured logging records;
- deterministic canonical schedules, with predeclared repetitions/seeds for later performance campaigns;
- fresh model state per run and fixed reset/warm-up policy;
- predeclared invalid-run handling;
- correctness targets and resource/latency metrics;
- explicit evidence boundaries between host, MCU, and physical validation.

Any later change to these decisions requires an explicit protocol amendment, rationale, affected experiments, and rerun requirements. It must not be made silently after results are observed.

## 18. Gate E conclusion

**GATE E — ACCEPTED at the experimental-design/protocol level.**

The project now has a frozen bridge from the semantic contracts of Gates A–D to a reproducible implementation/evaluation plan. The next step is the **Minimal Reference Implementation — smallest testable reference prototype**.

No firmware implementation, physical testbed bring-up, benchmark result, or physical-fault claim is part of Gate E completion.
