# Embedded Runtime Resilience

> **Research project — Gates A-E frozen; host validation complete; software demonstrator + methodology lock active**

A solo software-dominant embedded-systems research project investigating a **Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**.

## Current status

The project has completed the frozen design, host/reference implementation, K.1/K.2 host verification, and K.3 evidence synthesis checkpoints. It is now in the **integrated software proof-of-concept and methodology-lock phase**: build the professor-facing demonstrator, re-verify the complete software chain, lock the methodology, and prepare the hardware-validation handoff.

### Completed

- **Gate A — Event Model + Dependency Semantics** — complete
- **Gate B — Fault Model + Fault Association** — complete
- **Gate C — Recovery Policy + Bounded State Machine** — complete
- **Gate D — Formal Properties + Proof/Check Strategy** — complete at the semantic/design-model level
- **Gate E — Baselines + Experimental Protocol** — complete/frozen
- **Minimal Reference Implementation** — host checkpoint complete
- **Chat K.1 — matched P0-P4 host experiment harness** — execution verified

### Current integrated objective

- **Software demonstrator** — professor-facing proof of concept
- **Re-verification** — re-run/confirm the complete host/reference methodology
- **Methodology lock** — freeze the research chain and its evidence boundaries
- **Novelty showcase** — present the integrated mechanism as a research hypothesis supported by prior-art positioning, not as an already-proven patentability result
- **Conclusion** — establish the software phase as ready for target-MCU validation

**Hardware validation has not started.** The software phase is being completed deliberately before moving to the STM32U575 target.

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


## 2026-10-01 — Integrated software-phase objective

The current target is a complete software-only proof of concept for professor review. The UI demonstrates the end-to-end mechanism while the ISO C11 reference and host corpus remain the authoritative software evidence. See `research/phase1_software_demonstrator_methodology_lock.md`.

The software conclusion is intentionally bounded: the project has a specified, implemented, reproducible host mechanism suitable for hardware validation, but MCU performance, physical recovery, statistical evidence, and final novelty/patentability remain unverified.

---

# Project Structure — Two-Part Research Program

## Part I — K-Series Host/Reference Foundation — COMPLETE
K.1 -> K.2 -> K.3 is Part I. K.3 is a completed Part-I checkpoint, not the end of the overall project.

Part I established Gates A-E, the ISO C11 reference mechanism, deterministic host experiment infrastructure, K.1 execution verification, K.2 corpus validation, and K.3 evidence-bounded synthesis.

## Part II — Software Demonstrator, Novelty Investigation, and Methodology Lock — ACTIVE
Part II begins at K.4. Its purpose is to investigate the remaining novelty space, construct a software-only virtual embedded system, connect that environment to the same authoritative C reference runtime, build the professor-facing UI, perform matched software comparison, re-verify the software chain, and produce the hardware-validation handoff.

Professor review is the intended use of Part II, not a separate stage.

### Authoritative architecture
UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace -> UI

The UI is presentation/control only. The virtual system models the environment. The C reference runtime remains the authoritative recovery-policy implementation. A second competing recovery algorithm must not be created in the UI or simulator.

### Branch-control policy
- exp is the active research/reference branch.
- Focused child branches may be created from exp.
- Completed checkpoints return to exp.
- main is the integrated stable mirror and is synchronized from exp through explicit PR/merge.
- No active Part-II development is performed directly on main.
- Every main update identifies the source exp commit and checkpoint.

### Chat scope contract
Every Part-II chat has a predefined scope in research/PART_II_CHAT_PLAN.md. A chat must read continuity files, perform only its assigned checkpoint, record completed and incomplete work, update continuity, and stop at its boundary.
