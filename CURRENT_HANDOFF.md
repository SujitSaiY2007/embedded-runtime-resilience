# Current Handoff

## Session status

Phase 0 topic validation and initial Phase 1 system-design preparation are complete. The development topic is frozen. The project is in **Phase 1E.1 — Experimental Design / Formalization Foundation**.

**Gate A — Exact Event Model and Dependency Semantics is COMPLETE and checkpointed.**  
**Gate B — Fault Model + Fault Association is COMPLETE and checkpointed.**

The next chat must begin **Gate C — Recovery Policy + Bounded State Machine**.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

**Short working title:** Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine

## Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Core invariants

1. **Quarantine safety** — a quarantined event cannot execute until an explicitly permitted transition.
2. **Fault association** — recovery uses the smallest defensible event/transaction scope; ambiguity is not silently converted into precision.
3. **Service preservation** — unrelated valid work remains eligible only when dependency, ordering, shared-state, and recovery-safety conditions permit it.
4. **Dependency safety** — dependent events cannot bypass an invalid/quarantined predecessor or shared state merely because they are not themselves fault-associated.
5. **Recovery termination** — each fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage** — queue, quarantine storage, history, and recovery state remain within fixed limits with no runtime heap growth.

## Gate A completed artifact

`research/phase1_gateA_event_model_final.md`

The original `research/phase1_event_model.md` remains retained as historical baseline material and was not deleted.

Gate A established the final semantic contract for event identity, event types, service ownership, peripheral association, criticality, explicit dependency classes, bounded dependency representation, admission/execution ordering, lifecycle, evidence-bounded fault association, quarantine, capacity, full-queue behavior, and preservation correctness.

Provisional host-model capacity parameters are `QMAX=16`, `XMAX=4`, and `DMAX=4`; Gate E must validate or revise them against the workload and report final values explicitly.

## Gate B completed artifact

`research/phase1_gateB_fault_model_final.md`

Gate B is accepted at the semantic/design level.

Key frozen decisions:

- The primary taxonomy is centered on observable I2C failure modes: NACK/non-acknowledge, timeout/no-progress, bus/protocol error, arbitration loss, and persistent no-progress/suspected peripheral-state failure.
- SPI has a deliberately reduced secondary taxonomy because SPI fault evidence is more implementation/device dependent and SPI has no universal NACK equivalent.
- Recurrence and persistence are history/episode attributes rather than separate instantaneous fault classes.
- Service/driver-level failure without sufficient peripheral evidence remains distinct from peripheral failure.
- Association levels are `EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS`.
- Peripheral equality alone never justifies event-level fault attribution.
- Fault association scope and dependency-blocking scope are distinct.
- Software injection is deterministic test stimulus, not equivalent to physical hardware failure.
- Physical/protocol fault injection candidates remain unvalidated until hardware acquisition, electrical safety review, and repeatability testing.
- The semantic fault record is fixed-size/static and retains only information needed for later policy decisions and metrics.
- A fault episode continues across qualifying repeated observations until verified success, degraded terminal handling, or escalation; a later post-terminal fault starts a new episode.

No physical measurements or hardware validation are claimed.

## Platform checkpoint

Primary platform direction remains **STM32U575ZI / NUCLEO-U575ZI-Q**.

Initial interface direction:

- I2C — primary experimental interface
- SPI — secondary interface
- UART/USART — diagnostic/control path

The retained MCU selection baseline is present at `research/phase1_mcu_board_selection.md`. This is a design recommendation, not acquisition confirmation.

## Next exact task — Gate C

### Recovery Policy + Bounded State Machine

Do not begin large-scale firmware implementation.

Use the completed Gate A and Gate B contracts to derive and freeze:

1. minimum fault-context variables that materially change recovery decisions;
2. minimum useful bounded recovery-history representation;
3. finite recovery action set, including whether reinitialization and peripheral reset are experimentally distinct on the final U575 path;
4. deterministic recovery decision table;
5. recovery behavior for each association-confidence level;
6. exact retry/reinitialization/degradation/escalation transitions;
7. bounded recovery transition budget;
8. interaction between recovery and event scheduling/quarantine/dependency blocking;
9. safe degraded-mode semantics for the reference services;
10. policy output record and its fixed-size storage semantics;
11. policy ablation variants needed to test whether context/history actually contributes value.

Gate C must challenge the provisional recovery-policy design in `research/phase1_recovery_policy_design.md` rather than copying it blindly.

## Subsequent gates

- **Gate D:** formal properties, transition-system reasoning, assertions/model-checking strategy where practical.
- **Gate E:** baselines, workload matrix, fault schedule, metrics, logging, repetitions, and reproducibility protocol.
- **Implementation:** only after A–E are sufficiently specified; build the smallest reference prototype.
- **Physical validation:** after hardware/testbed acquisition and safe fault-injection setup.
- **Evaluation:** matched baseline/proposed experiments.
- **Research synthesis:** analysis, limitations, novelty evidence, publication/patent pathway.

## Research honesty / non-claims

- Do not claim novelty for zero-heap, MPU, peripheral recovery, event queues, event quarantine, context-aware recovery, or formal invariants individually.
- Do not claim patentability.
- Do not fabricate physical measurements, hardware availability, benchmarks, or experimental outcomes.
- Host simulation is not equivalent to physical MCU validation.
- Do not treat software fault injection as proof of a physical fault mechanism.
- Do not turn an inferred physical cause into an observed fault class.
- Do not add unrelated resilience features or build a general-purpose framework.

## GitHub continuity

GitHub is the durable source of truth. Preserve historical material. Prefer additive updates and explicit supersession notes. At every gate boundary, checkpoint relevant research documentation plus `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, and `DECISION_LOG.md` before starting the next chat.

## Chat boundary

**Stop this chat after Gate B is checkpointed. The next chat is Gate C.**

Recommended future boundaries:

- Chat C: Gate C complete → checkpoint → new chat
- Chat D: Gate D complete → checkpoint → new chat
- Chat E: Gate E complete → checkpoint → new chat
- Chat F: minimal reference implementation complete → checkpoint → new chat
- Chat G: physical testbed bring-up complete → checkpoint → new chat
- Chat H: baseline experiments complete → checkpoint → new chat
- Chat I: proposed-policy experiments complete → checkpoint → new chat
- Chat J: evaluation/analysis complete → checkpoint → final synthesis chat

If a chat becomes unusually long before a gate boundary, stop at the nearest coherent sub-boundary after checkpointing the repository.
