# Current Handoff

## Session status

Phase 0 topic validation and initial Phase 1 system-design preparation are complete. The development topic is frozen. The project is in **Phase 1E.1 — Experimental Design / Formalization Foundation**.

**Gate A — Exact Event Model and Dependency Semantics is COMPLETE and checkpointed.**

The next chat must begin **Gate B — Fault Model + Fault Association**.

A ready-to-use continuation prompt is preserved at `NEXT_CHAT_PROMPT.md`.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

**Short working title:** Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine

## Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Six core invariants

1. **Quarantine safety** — a quarantined event cannot execute until an explicitly permitted transition.
2. **Fault association** — recovery uses the smallest defensible event/transaction scope; ambiguity is not silently converted into precision.
3. **Service preservation** — unrelated valid work remains eligible only when dependency, ordering, shared-state, and recovery-safety conditions permit it.
4. **Dependency safety** — dependent events cannot bypass an invalid/quarantined predecessor or shared state merely because they are not themselves fault-associated.
5. **Recovery termination** — each fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage** — queue, quarantine storage, history, and recovery state remain within fixed limits with no runtime heap growth.

These define the formal correctness boundary; they do not constitute a claim of full firmware formal verification.

## Gate A completed artifact

Primary final document:

`research/phase1_gateA_event_model_final.md`

The original `research/phase1_event_model.md` remains retained as historical design-baseline material and was not deleted.

Gate A froze/refined:

- `EventRef = {slot_id, generation}` for bounded non-ambiguous active identity;
- finite event types;
- producer/service semantics and optional distinct consumer endpoint;
- bounded peripheral association;
- finite criticality classes;
- explicit INDEPENDENT / ORDERED / COUPLED-TRANSACTIONAL dependency taxonomy;
- bounded explicit dependency entries rather than peripheral-wide inference;
- FIFO admission order separated from execution eligibility;
- explicit event lifecycle and recovery transitions;
- fault-association precision bounded by evidence;
- quarantine as retained non-executable state;
- bounded queue/quarantine capacity assumptions;
- deterministic full-queue behavior;
- preservation as correct verified execution rather than mere queue retention;
- quarantine-violation correctness metric.

Provisional host-model capacity parameters are `QMAX=16`, `XMAX=4`, and `DMAX=4`. Gate E must validate or revise them against the workload and report final values explicitly.

## Platform checkpoint

Primary platform direction remains **STM32U575ZI / NUCLEO-U575ZI-Q**.

Initial interface direction:

- I2C — primary experimental interface
- SPI — secondary interface
- UART/USART — diagnostic/control path

The retained MCU selection baseline is present at `research/phase1_mcu_board_selection.md`. This is a design recommendation, not acquisition confirmation.

## Next exact task

### Gate B — Fault Model + Fault Association

Do not begin large-scale firmware implementation.

Start Gate B by reading the repository continuity files and `research/phase1_gateA_event_model_final.md`, then freeze:

1. exact fault taxonomy for the selected experimental peripheral(s);
2. deterministic software fault-injection semantics;
3. hardware/protocol fault classes where safely reproducible;
4. bounded fault-record representation;
5. fault-to-event/transaction association rules;
6. association-confidence handling;
7. fault-episode boundaries and recurrence semantics;
8. evidence needed to distinguish event, service, peripheral, and ambiguous faults;
9. quarantine-scope implications of each association level.

The complete ready-to-paste next-chat prompt is in `NEXT_CHAT_PROMPT.md`.

## Subsequent gates

- **Gate C:** minimum context/history variables, bounded action set, recovery policy and state machine.
- **Gate D:** formal properties, transition-system reasoning, assertions/model-checking strategy where practical.
- **Gate E:** baselines, workload matrix, fault schedule, metrics, repetitions, logging, and reproducibility protocol.
- **Implementation:** only after A–E are sufficiently specified; build the smallest reference prototype.
- **Physical validation:** after hardware/testbed acquisition and safe fault-injection setup.
- **Evaluation:** matched baseline/proposed experiments.
- **Research synthesis:** analysis, limitations, novelty evidence, publication/patent pathway.

## Research honesty / non-claims

- Do not claim novelty for zero-heap, MPU, peripheral recovery, event queues, event quarantine, context-aware recovery, or formal invariants individually.
- Do not claim patentability.
- Do not fabricate physical measurements, hardware availability, benchmarks, or experimental outcomes.
- Host simulation is not equivalent to physical MCU validation.
- Do not add unrelated resilience features or build a general-purpose framework.

## GitHub continuity

GitHub is the durable source of truth. Preserve historical material. Prefer additive updates and explicit supersession notes. At every gate boundary, checkpoint relevant research documentation plus `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, and `DECISION_LOG.md` before starting the next chat.

## Chat boundary

**Stop this chat after Gate A is checkpointed.** The next chat is Gate B.

Recommended future boundaries remain:

- Chat B: Gate B complete → checkpoint → new chat
- Chat C: Gate C complete → checkpoint → new chat
- Chat D: Gate D complete → checkpoint → new chat
- Chat E: Gate E complete → checkpoint → new chat
- Chat F: minimal reference implementation complete → checkpoint → new chat
- Chat G: physical testbed bring-up complete → checkpoint → new chat
- Chat H: baseline experiments complete → checkpoint → new chat
- Chat I: proposed-policy experiments complete → checkpoint → new chat
- Chat J: evaluation/analysis complete → checkpoint → final synthesis chat

If a chat becomes unusually long before a gate boundary, stop at the nearest coherent sub-boundary after checkpointing the repository.
