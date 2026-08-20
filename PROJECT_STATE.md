# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`
**Status:** Development topic selected; novelty/gap validation remains evidence-driven and may still force narrowing or rejection of the mechanism.
**Project mode:** Solo software-dominant embedded-systems project
**Primary ambition:** Research-grade implementation with publication potential and a possible patent pathway if supported by prior art and professional assessment.

## Selected development topic

**Design and Implementation of a Lightweight Context-Aware Peripheral Fault Recovery Mechanism for Resource-Constrained Event-Driven MCU Systems**

This is the topic selected for development from the Phase 0 opportunity map. It is deliberately narrower than the earlier lead candidate.

### What the project will investigate

The project will investigate whether a small MCU-resident recovery mechanism can detect common peripheral/service faults, classify the failure context, and select a bounded local recovery action—such as retry, reinitialization, peripheral reset, controlled degradation, or escalation—while minimizing collateral interruption to unrelated event-driven work.

The intended contribution is **not** a generic watchdog, generic retry loop, generic bus-recovery routine, or reproduction of Phoenix-style checkpoint/rollback.

The technical hypothesis is that a compact context-aware recovery policy, operating at the boundary between peripheral fault detection and event-driven service management, can reduce service interruption and unnecessary system-wide recovery compared with conventional fixed recovery sequences.

This hypothesis is not yet a demonstrated research gap or novelty claim.

## Evidence status

### Established evidence

- Embedded peripheral failures are a real problem and Phoenix demonstrated resource-constrained peripheral recovery using checkpointing and rollback. This makes generic peripheral recovery a crowded starting point.
- Runtime verification and embedded runtime monitoring are mature research areas, including R2U2 and embedded Rust work. This weakens the earlier broad runtime-contract framing.
- Existing patents also cover processor/watchdog recovery, fault containment, initialization recovery, and more recent peripheral-device recovery.

### Inference

A potentially useful remaining space is not “recover peripherals,” but the specific **policy and state-management problem of choosing a bounded recovery action from observed failure context while preserving unrelated event-driven service** on a small MCU.

### Hypothesis

A deliberately small recovery policy can outperform a fixed retry/reset baseline on selected fault classes without imposing unacceptable CPU, RAM, Flash, latency, or implementation complexity.

### Speculation

A sufficiently differentiated policy may eventually support a publication or patent pathway. No such conclusion is made at this stage.

## Course-guideline alignment

The supplied Embedded Systems Course Project guideline requires a real-world engineering problem, literature/existing-solution review, a research/technical gap, an embedded solution, algorithmic/software contribution where appropriate, measurable experimental validation, comparison with a reference method, and a research/patent component. The selected topic is designed to satisfy that structure without relying on a trivial sensor application.

The guideline explicitly emphasizes quantitative validation and comparison rather than merely demonstrating that a prototype works. The project will therefore use measurable recovery, service, timing, and resource metrics.

## Planned evaluation concept

Initial baseline candidates:

1. fixed retry policy;
2. fixed retry-then-reset policy;
3. vendor/protocol-standard recovery where applicable.

Proposed-policy measurements:

- fault detection latency;
- time to service restoration;
- recovery success rate;
- number of whole-system resets;
- unrelated-service interruption;
- lost/duplicated transactions;
- event-queue disruption;
- CPU overhead;
- RAM/Flash overhead;
- energy impact where practical.

Fault injection should be reproducible and include selected stuck/bus-error/timeout/peripheral-state fault scenarios appropriate to the chosen MCU and peripherals.

## Scope boundary

The first implementation should remain small: one MCU family, a limited number of peripheral interfaces, a bounded set of fault classes, and a deterministic event-driven firmware architecture. Cross-platform generality is not a requirement for the initial paper-quality prototype.

The exact MCU board, peripherals, fault-injection apparatus, recovery-state machine, and benchmark suite are **not frozen yet**.

## Phase status

**Phase 0 — Topic Validation / Development Topic Selection**

Completed:

- [x] Repository continuity infrastructure established
- [x] Project requirements and constraints documented
- [x] Research-space decomposed into 12 opportunity classes
- [x] Candidate shortlist created
- [x] Current literature/patent evidence used to eliminate the broad runtime-contract framing
- [x] Development topic selected

Still open:

- [ ] Systematic academic prior-art matrix for the selected topic
- [ ] Systematic patent-family search for the selected mechanism
- [ ] Commercial/vendor/open-source comparison
- [ ] Defensible explicit gap statement
- [ ] Novelty-risk assessment
- [ ] Exact architecture
- [ ] MCU/peripheral testbed selection
- [ ] Fault model and injection method
- [ ] Experimental protocol
- [ ] Final title freeze

## Important rule

The topic is now **selected for development**, because this is the primary project objective. However, the repository must not convert this selection into a false claim of novelty. If systematic prior-art work shows that the mechanism is already known, the topic must be narrowed, redesigned, merged with another opportunity, or rejected.

## Next exact task

Conduct a focused prior-art and patent investigation of the selected mechanism, specifically testing whether context-aware selection among retry/reinitialize/reset/degrade/escalate actions combined with preservation of unrelated event-driven service is already disclosed in closely related embedded systems.
