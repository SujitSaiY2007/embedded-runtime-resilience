# Current Handoff

## Last completed step

Phase 0 research-space decomposition and the requested deep prior-art attack have been completed.

The project topic is now frozen for development.

## Frozen development topic

> **Design and Implementation of a Lightweight Context-Aware Peripheral Recovery Policy for Resource-Constrained Event-Driven MCU Firmware**

## Research question

Can a compact software-only recovery policy, using observed peripheral fault context and recovery history, select bounded recovery actions and contain the affected service while preserving unrelated event-driven work, with lower service interruption and acceptable MCU overhead than fixed retry/reset strategies?

## Important status distinction

The topic is frozen as the development target. This is **not** a claim that the exact mechanism is novel or patentable.

The deep prior-art attack established that generic peripheral recovery, selective peripheral restart, context-aware recovery, graceful degradation, and recovery state machines are already known areas. The surviving contribution hypothesis is narrower: a small deterministic MCU-resident policy that combines local fault context/history with bounded recovery-action selection and explicit preservation of unrelated event-driven service.

## Important prior-art anchors

- Phoenix: peripheral rollback/recovery on resource-constrained embedded systems.
- Karma: asynchronous peripheral operation and recovery/state handling.
- Recovering Device Drivers / Failure Resilience for Device Drivers: driver isolation and policy-driven recovery.
- Context-aware embedded health management: context-dependent diagnosis/recovery.
- Recent patents on selective peripheral restart, I/O fault recovery, and peripheral isolation.

See `research/deep_prior_art_attack_topic_freeze.md` for the detailed attack record.

## Next phase

**Design and Experimental Planning**

### Immediate next actions

1. Define the exact technical contribution and policy state variables.
2. Select the MCU development board and a small peripheral testbed.
3. Define reproducible fault-injection mechanisms.
4. Specify baseline recovery policies.
5. Design the proposed recovery policy.
6. Define experimental workloads and primary/secondary metrics.
7. Establish reproducibility and data-recording procedures.
8. Review the exact mechanism once more for patent-sensitive disclosure before publishing implementation details.

## Do not do yet

- Do not claim patentability.
- Do not claim "first" or "novel" without an exact claim-level search.
- Do not implement a large framework before the policy and evaluation protocol are defined.
- Do not use Phoenix/Karma/etc. as straw-man baselines; compare against their relevant concepts fairly.

## Continuation instruction

Future chats should read `PROJECT_MANUAL.md`, `PROJECT_STATE.md`, this file, `DECISION_LOG.md`, and `research/deep_prior_art_attack_topic_freeze.md` before substantive design work.
