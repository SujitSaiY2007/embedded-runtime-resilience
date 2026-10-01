# Embedded Runtime Resilience

> **Research project — Gates A-E frozen; Chat K.2 host-corpus checkpoint complete; Chat K.3 final synthesis next**

A solo software-dominant embedded-systems research project investigating a **Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**.

## Current status

The project is in **Phase 1 — System Design and Experimental Preparation**, specifically **Phase 1E.1 — Experimental Design / Formalization Foundation**.

### Completed

- **Gate A — Event Model + Dependency Semantics** — complete
- **Gate B — Fault Model + Fault Association** — complete
- **Gate C — Recovery Policy + Bounded State Machine** — complete
- **Gate D — Formal Properties + Proof/Check Strategy** — complete at the semantic/design-model level
- **Gate E — Baselines + Experimental Protocol** — complete/frozen
- **Minimal Reference Implementation** — host checkpoint complete
- **Chat K.1 — matched P0-P4 host experiment harness** — execution verified

### Next

- **Chat K.3 — Final synthesis and evidence-bounded project packaging**

K.2 has completed the host-corpus validation checkpoint. The next task is final synthesis: consolidate demonstrated evidence, limitations, remaining validation gaps, and the final project package without converting host/reference evidence into MCU or physical claims.

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

## 2026-10-01 — Chat K.1 checkpoint

Chat K.1 completed the smallest reproducible host-experiment checkpoint.

- Branch: `experiment/host-p0-p4-corpus-2026-10-01`
- Commit: `949bd4c`
- The branch was pushed and the working tree was clean after commit.
- Windows/MSVC build produced `reference_tests.exe` and `host_experiment.exe`.
- CTest: **2/2 passed**.
- `py experiments/run_host_experiment.py --check`: **PASS** for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- Matched corpus size: **14 workloads × 5 variants = 70 runs**.
- W09/W10 are explicitly capacity-confounded.
- P0-P3 are explicitly marked `ablation_contract_valid=0`; P4 is marked valid under the current implementation boundary.
- The P0-P3 quarantine-ablation gap remains documented and unchanged.

The generated `out/` and `out.replay/` directories were inspected during verification and then cleaned before the checkpoint commit; the declarative input corpus and harness remain committed so the run is reproducible.

### Chat K.2 starting boundary

Do not rebuild or redesign the harness unless corpus inspection exposes a concrete defect. Start by regenerating/inspecting the corpus, validating trace/outcome semantics against Gate E, and recording any remaining evidence limitations.

## 2026-10-01 — Chat K.2 corpus-validation checkpoint

Chat K.2 completed the corpus-level validation of the regenerated host evidence.

- Branch: `experiment/host-p0-p4-corpus-2026-10-01`
- Regenerated corpus: **70 runs = W01-W14 × P0-P4**.
- `corpus_manifest.csv` reports PASS for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- Manifest evidence boundary reports host evidence only: `host_evidence_only=1`, `mcu_evidence=0`, `physical_fault_evidence=0`.
- Representative trace/run slices were inspected across recovery-heavy and later workloads; no concrete corpus-generation, serialization, or runtime defect was found.
- W09/W10 remain explicitly capacity-confounded.
- P0-P3 remain `ablation_contract_valid=0`; P4 remains valid under the current implementation boundary.
- The existing exact-event-quarantine implementation gap remains documented and unchanged.

The generated `out/` and `out.replay/` directories remain transient verification artifacts. The committed source of reproducibility is the declarative corpus, harness, and checkpoint documentation.

**K.2 is complete. K.3 is the next checkpoint.**
