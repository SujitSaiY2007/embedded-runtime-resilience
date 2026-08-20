# Current Handoff

## Session status

Phase 0 topic validation is complete. The research-space was decomposed, six candidates were shortlisted, the leading candidates were attacked with academic/patent/vendor evidence, and the development topic was frozen. The proposed zero-heap and event-quarantine additions were then evaluated and integrated without changing the project's core problem.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

**Short working title:** Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine

This topic is frozen for development. Do not restart topic ideation unless new evidence makes the mechanism technically invalid or infeasible.

## Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Core architecture constraints

1. **Zero-heap:** no runtime dynamic allocation in the recovery manager/reference firmware; use static bounded memory.
2. **Context/history:** policy may use fault type, error/timeout pattern, recurrence, previous recovery outcome, service criticality, and event workload.
3. **Bounded actions:** retry, reinitialize, peripheral reset, controlled degradation/isolation, escalation.
4. **Event quarantine:** isolate the fault-associated event/transaction rather than indiscriminately flushing unrelated valid queued events, subject to dependency/order semantics.
5. **MPU:** target an MCU with usable MPU support where practical; use it for containment/isolation, not as a claimed invention.
6. **Event-driven firmware:** cooperative/resource-constrained reference architecture; avoid making a heavyweight OS the dependency of the contribution.
7. **Formal reasoning:** prove selected queue/recovery invariants where tractable; do not claim full formal verification of the firmware.

## Important prior-art lessons

The project must not claim novelty for any individual ingredient. Generic peripheral recovery, selective restart, context-aware health management, graceful degradation, watchdog/recovery, event queues, zero-heap allocation discipline, MPU isolation, and formal invariants are established concepts.

The surviving contribution hypothesis is the **specific integrated mechanism and measured trade-off**: a compact deterministic zero-heap MCU policy using local fault context/history and event quarantine to reduce collateral interruption of unrelated event-driven service.

See `research/deep_prior_art_attack_topic_freeze.md` for the detailed prior-art attack.

## Hardware reality

The project is software-dominant, but final physical embedded validation requires an actual MPU-capable MCU development board. A laptop/PC is sufficient for development, host simulation, fault modelling, formal reasoning, automated tests, and analysis; it cannot substitute for physical measurements of MCU MPU behavior, interrupt timing, peripheral behavior, and hardware-relevant faults.

**Current hardware status:** no physical MCU board is assumed available.

Therefore, selecting an affordable suitable board is an immediate Phase 1 task. Do not invent hardware measurements before a board exists.

## Immediate Phase 1 objective

**Design the smallest defensible system that can test the frozen hypothesis.**

### Required work in order

### 1. MCU/development-board selection

Evaluate candidate MPU-capable MCUs/boards against:

- MPU availability and software accessibility;
- sufficient RAM/Flash;
- timers/interrupts;
- at least two suitable peripherals/interfaces;
- accessible SDK/toolchain/debugger;
- affordability/availability;
- ability to reproduce faults safely;
- documentation quality;
- host-PC development compatibility.

Do not choose a board merely because it is popular; justify the choice against project requirements.

### 2. Peripheral testbed

Select a small set of peripherals that allow reproducible fault scenarios. Prefer 2–3 interfaces/devices rather than an unnecessarily broad platform.

Potential classes include I2C/SPI/UART/CAN, but exact selection must follow board availability and experimental controllability.

### 3. Fault model

Define explicit fault classes, for example:

- transaction timeout;
- peripheral non-response;
- repeated communication failure;
- stuck/bus error where safely reproducible;
- invalid peripheral state;
- event-triggered service failure.

Distinguish injected faults from naturally occurring hardware faults.

### 4. Event model

Define:

- event identity;
- event type;
- producer;
- consumer/service;
- dependency relation;
- priority/criticality;
- ordering requirements;
- fault association;
- quarantine state;
- release/retry rules.

### 5. Recovery-policy design

Define the minimum state machine and policy variables before writing a large framework.

Candidate states:

`NORMAL -> FAULT_DETECTED -> CLASSIFY -> QUARANTINE -> RECOVER -> VERIFY -> RELEASE/DEGRADE/ESCALATE`

This is only a starting abstraction; refine it from the requirements.

### 6. Formal properties

Define a small set of tractable invariants, such as:

- quarantined events cannot execute until release;
- unrelated valid events are preserved under an isolated single-event fault;
- queue capacity remains bounded;
- recovery transitions terminate within a declared bound;
- required ordering among independent events is preserved.

Determine whether lightweight state-machine reasoning, assertions, model checking, or another practical formal method is appropriate.

### 7. Baselines

At minimum:

- fixed retry;
- fixed retry + peripheral reset/reinitialization.

Add a vendor/protocol-specific recovery baseline where technically appropriate.

Do not misrepresent sophisticated prior systems such as Phoenix or Karma as simple baselines; use them for related-work comparison and conceptual positioning.

### 8. Experimental protocol

Define workloads, fault-injection schedule, repetitions, metrics, statistical treatment, logging format, and reproducibility requirements before interpreting results.

Primary metrics:

- detection latency;
- recovery/service-restoration latency;
- recovery success rate;
- whole-system reset count;
- unrelated-event preservation rate;
- quarantine correctness;
- lost/duplicated events;
- queue occupancy;
- CPU overhead;
- RAM/Flash footprint;
- energy where practical.

## Do not do in the next chat

- Do not restart topic selection.
- Do not add unrelated resilience features.
- Do not implement a large framework before the policy is specified.
- Do not claim novelty/patentability from the topic title.
- Do not claim physical measurements without physical hardware.
- Do not treat simulation as equivalent to MCU validation.
- Do not publish potentially patent-sensitive implementation details unnecessarily.

## Required continuity behavior

The next chat must first read, in order:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `research/deep_prior_art_attack_topic_freeze.md`
6. relevant Phase 0 research files

Then provide a concise continuity check before substantive design work.

## Exact next task

**Begin Phase 1 — System Design and Experimental Preparation, starting with a justified selection of an MPU-capable MCU development board and a minimal peripheral testbed, followed by the event model, fault model, recovery state machine, formal invariants, baselines, and experimental protocol.**
