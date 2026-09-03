# Embedded Runtime Resilience

> **Research project — Phase 1E.1 / Gate D complete; Gate E next**

A solo software-dominant embedded-systems research project investigating a **Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**.

## Current status

The project is in **Phase 1 — System Design and Experimental Preparation**, specifically **Phase 1E.1 — Experimental Design / Formalization Foundation**.

### Completed

- **Gate A — Event Model + Dependency Semantics** — complete
- **Gate B — Fault Model + Fault Association** — complete
- **Gate C — Recovery Policy + Bounded State Machine** — complete
- **Gate D — Formal Properties + Proof/Check Strategy** — complete at the semantic/design-model level

### Next

- **Gate E — Baselines + Experimental Protocol**

Gate E will define the experimental baselines, workload/dependency scenarios, fault schedule, capacities, metrics, logging, repetitions, reproducibility treatment, and acceptance/reporting criteria.

**Large-scale firmware implementation has not started. Physical MCU validation has not started.** These remain downstream of the design and experimental gates.

## Research question

Can a compact, deterministic, software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Project progression

The project has two broad phases:

1. **Phase 0 — Research and topic selection:** research-space exploration, prior-art investigation, falsification of broad candidate ideas, and topic freeze.
2. **Phase 1 — Main engineering/research work:** system design, formalization, experimental protocol, reference implementation, physical testbed, experiments, analysis, and final synthesis.

Phase 1 currently progresses through the Gate A–E design/experimental checkpoints before implementation and validation.

## Current architecture direction

- **Target MCU/board:** STM32U575ZI / NUCLEO-U575ZI-Q
- **Primary interface:** I2C
- **Secondary interface:** SPI
- **Initial diagnostic/control path:** UART/USART
- **Recovery model:** zero-heap, statically bounded, deterministic
- **Core mechanism:** context/history-aware recovery with dependency-aware event quarantine
- **Logical actions:** `RETRY`, `REINIT_OR_RESET`, `DEGRADE`, `ESCALATE`
- **Recovery budget:** maximum 4 recovery actions per fault episode

The platform direction and design contracts remain subject to later implementation and physical validation where applicable.

## Research discipline

The project does **not** claim that zero-heap allocation, MPU isolation, peripheral recovery, event queues, event quarantine, context-aware recovery, or formal invariants are individually novel.

The research hypothesis concerns the **specific integrated mechanism and its measured technical trade-offs**.

Host-side modeling and exhaustive checks provide evidence about the defined model; they are not substitutes for firmware execution or physical hardware validation.

No physical measurements, benchmark results, patentability conclusions, or unsupported novelty claims should be inferred from the current repository state.

## Continuity

This repository is the project's canonical source of truth across development sessions.

Before substantive continuation, read:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. the relevant `research/` artifacts

`NEXT_CHAT_PROMPT.md` contains the current next-chat startup prompt. Historical design artifacts are retained rather than deleted merely to shorten the repository.

## Research rule

**Novelty is a hypothesis until demonstrated against prior art.**

The repository documents research decisions and evidence progressively; completion of a design gate does not by itself establish experimental superiority, novelty, or patentability.
