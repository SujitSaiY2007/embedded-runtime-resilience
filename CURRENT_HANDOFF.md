# Current Handoff

## Session status

Phase 0 topic validation and the initial Phase 1 system-design preparation are complete. The development topic is frozen. The project has now officially entered **Phase 1E.1 — Experimental Design / Formalization Foundation** conceptually.

The current project state must be continued from the repository checkpoint below; do not restart topic ideation or earlier design work.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

**Short working title:** Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine

## Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Frozen architecture constraints

1. Zero runtime heap allocation in the recovery manager/reference firmware.
2. Bounded local fault context and short recovery history.
3. Finite, deterministic recovery actions with explicit terminal escalation.
4. Dependency-aware event quarantine rather than global queue flushing.
5. MPU support used as a platform containment mechanism, not as the claimed invention.
6. Lightweight event-driven reference architecture.
7. Selected formal invariants/properties rather than a claim of full formal verification.

## Six core invariants established for Phase 1E.1

1. **Quarantine safety** — a quarantined event cannot execute until an explicitly permitted transition.
2. **Fault association** — recovery uses the smallest defensible event/transaction scope; ambiguity is not silently converted into precision.
3. **Service preservation** — unrelated valid work remains eligible only when dependency, ordering, shared-state, and recovery-safety conditions permit it.
4. **Dependency safety** — dependent events cannot bypass an invalid/quarantined predecessor or shared state merely because they are not themselves fault-associated.
5. **Recovery termination** — each fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage** — queue, quarantine storage, history, and recovery state remain within fixed limits with no runtime heap growth.

These six invariants define the current formal correctness boundary. They are not a claim that the complete firmware is already formally verified.

## Primary platform direction

Current design direction: **STM32U575ZI / NUCLEO-U575ZI-Q**.

Initial interface direction:

- I2C — primary experimental peripheral interface
- SPI — secondary interface
- UART/USART — initial diagnostic/control path

The physical board and final peripheral module must be verified before physical measurements or hardware claims are made.

## Repository documentation checkpoint

The main branch now contains the retained Phase 1 design baselines:

- `research/phase1_mcu_board_selection.md`
- `research/phase1_event_model.md`
- `research/phase1_peripheral_testbed_fault_model.md`
- `research/phase1_recovery_policy_design.md`

These were restored onto `main` from the earlier design branch without deleting the newer main-branch continuity documents.

## Exact next task

### Gate A — Exact Event Model and Dependency Semantics

Do not jump to firmware implementation.

First derive and freeze the semantic contract for:

1. bounded event identity;
2. event types;
3. producer/consumer/service roles;
4. peripheral association;
5. criticality;
6. independent vs ordered vs coupled/transactional dependency classes;
7. dependency representation and worst-case storage;
8. queue ordering vs execution-order constraints;
9. event lifecycle/state transitions;
10. fault-association state;
11. quarantine semantics;
12. bounded queue/quarantine capacity;
13. full-queue behavior;
14. event-preservation correctness metric.

Use `research/phase1_event_model.md` as the starting baseline, but **validate every semantic assumption before declaring Gate A complete**. Do not silently treat the existing document as final merely because it exists.

## Subsequent gates

After Gate A:

- **Gate B:** exact fault taxonomy, injection semantics, and fault-to-event association.
- **Gate C:** minimum context/history variables, bounded action set, recovery policy and state machine.
- **Gate D:** formal properties, transition-system reasoning, assertions/model-checking strategy where practical.
- **Gate E:** baseline definitions, workload matrix, fault schedule, metrics, repetitions, logging, and reproducibility protocol.
- **Implementation:** only after A–E are sufficiently specified; build the smallest reference prototype.
- **Physical validation:** after hardware/testbed acquisition and safe fault-injection setup.
- **Evaluation:** execute baselines and proposed mechanism under matched workloads/fault schedules.
- **Research synthesis:** analyze trade-offs, limitations, novelty evidence, publication/patent pathway.

## Experimental baseline direction

At minimum compare:

1. fixed retry;
2. fixed retry + peripheral reset/reinitialization;
3. proposed zero-heap context-aware recovery + dependency-aware event quarantine.

Use the same workload/fault schedule and report failures honestly. If the proposed mechanism does not outperform the baselines on a meaningful metric, record that result rather than forcing a positive conclusion.

## Important non-claims

- Do not claim novelty for zero-heap, MPU, peripheral recovery, event queues, event quarantine, context-aware recovery, or formal invariants individually.
- Do not claim patentability.
- Do not claim physical MCU measurements before actual execution on the hardware.
- Do not present host simulation as equivalent to physical validation.
- Do not add unrelated resilience features.
- Do not create a large framework before the research mechanism is specified.

## Chat continuity protocol

The repository is the durable source of truth. At the end of each substantial chat, update `CURRENT_HANDOFF.md`, `PROJECT_STATE.md`, and `DECISION_LOG.md` as needed, and commit the checkpoint before starting a new chat.

Use a new chat at **phase/gate boundaries**, not arbitrarily. Never wait until a long chat becomes impossible to reconstruct.

Recommended checkpoint boundaries:

- Chat A: Gate A complete → checkpoint → new chat
- Chat B: Gate B complete → checkpoint → new chat
- Chat C: Gate C complete → checkpoint → new chat
- Chat D: Gate D complete → checkpoint → new chat
- Chat E: Gate E complete → checkpoint → new chat
- Chat F: minimal prototype architecture/code complete → checkpoint → new chat
- Chat G: first physical testbed bring-up complete → checkpoint → new chat
- Chat H: baseline experiments complete → checkpoint → new chat
- Chat I: proposed-policy experiments complete → checkpoint → new chat
- Chat J: evaluation/analysis complete → checkpoint → final synthesis chat

If a chat becomes very long before the next listed boundary, stop at the nearest coherent sub-boundary, update the repository checkpoint, and start a new chat. The new chat must read the repository handoff before doing substantive work.
