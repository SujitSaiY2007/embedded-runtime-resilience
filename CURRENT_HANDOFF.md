# Current Handoff

## Last completed step

Phase 0 research-space decomposition, deep prior-art attack, topic selection, and integration review of the zero-heap and event-quarantine additions have been completed.

The development topic is now **frozen**.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Integration decisions

### Zero-heap

Accepted as a strict architectural constraint. No runtime dynamic allocation in the recovery manager/reference firmware. Static storage is used for recovery state, policy tables, and event queues.

Zero-heap itself is not claimed as novel.

### MPU

Accepted as a target-platform containment mechanism. The project should use an MPU-enabled MCU where practical, but MPU usage itself is not claimed as novel. If MPU experimentation proves impractical on the selected board, the core zero-heap recovery policy remains the primary contribution and MPU becomes a secondary configuration rather than a project blocker.

### Event quarantine

Accepted as an integrated mechanism. Formal terminology should be **event quarantine** rather than the informal phrase “queue poisoning prevention.” The mechanism will quarantine the fault-associated event/transaction context while preserving unrelated valid queued events subject to dependency and ordering rules.

### Formal reasoning

Full formal verification of the firmware is out of scope. The project will instead define and, where tractable, prove policy/queue invariants such as bounded capacity, no execution of quarantined events before release, preservation of unaffected events, bounded recovery transitions, and ordering preservation for independent events.

## Hardware clarification

The project is software-dominant, but a genuine MCU research validation cannot be reduced to a laptop/PC if the final claims include physical MPU behavior, interrupt timing, peripheral-driver behavior, or real hardware fault modes.

A laptop/PC can support development, simulation, emulation where available, fault-model testing, analysis, and data processing. A physical MCU development board is therefore a required validation resource for the strongest version of the project. No board is currently assumed to be available; board selection/acquisition is an immediate Phase 1 task.

## Immediate Phase 1 actions

1. Select an affordable MPU-enabled MCU development board.
2. Identify 2–3 peripherals suitable for reproducible fault injection.
3. Define event types, dependencies, and queue semantics.
4. Define the recovery state machine and contextual inputs.
5. Define queue/event invariants and formal properties.
6. Define baseline policies: fixed retry and fixed retry+reset/reinitialize.
7. Build a minimal firmware skeleton before expanding features.
8. Define metrics, workloads, and reproducibility protocol.

## Do not do yet

- Do not claim patentability.
- Do not claim that zero-heap, MPU isolation, event quarantine, or context-aware recovery is individually novel.
- Do not publish detailed implementation mechanics before the IP strategy is reviewed.
- Do not add unrelated features that turn the project into a generic embedded resilience framework.

## Continuation instruction

Future chats should read `PROJECT_MANUAL.md`, `PROJECT_STATE.md`, this file, `DECISION_LOG.md`, and `research/deep_prior_art_attack_topic_freeze.md` before substantive design work.
