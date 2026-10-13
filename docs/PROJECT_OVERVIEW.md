# Project Overview
## Embedded Runtime Resilience — Research Case Study

**State:** Software/research scope finalized · Hardware validation future work  
**Last reviewed:** 2026-10-13

## 1. Executive summary

This project studies a lightweight, deterministic, zero-heap recovery policy for event-driven embedded firmware. Its design combines fault/event context, bounded recovery history, recovery-action selection, and fault-associated event quarantine. The project evaluates five policy variants (P0–P4) using a fixed C reference runtime and a deterministic host/reference experiment campaign, then exposes the same runtime through a virtual-system adapter and browser-based demonstrator.

The completed deliverable is a **research case study plus executable software demonstration**. It is not a physical-board validation report.

## 2. Research question and hypothesis

**Question:** Can a compact recovery policy use peripheral-fault context and short recovery history to select a bounded action, isolate the fault-associated event, preserve unrelated queued work, and finish within explicit resource limits?

**Hypothesis:** An integrated policy can provide advantages in selected combined fault/context/history cases while preserving deterministic bounded operation. This is a scoped, falsifiable claim—not a claim that each mechanism is individually new.

## 3. System under study

- **Runtime:** protected C11 reference implementation.
- **Virtual environment:** bounded modeled I2C0, SPI0 and UART0 resources with registered deterministic scenarios.
- **Bridge:** Python standard-library HTTP server that validates requests and invokes the compiled C CLI.
- **UI:** HTML/CSS/vanilla JavaScript for scenario selection, stepping, playback, virtual link control, outcomes and traces.
- **Evidence:** frozen K.10 result reports and checkpoint-level audit/history.

The UI and Python bridge do not implement a competing recovery policy. They carry requests to the C execution path and display the returned records.

## 4. Experimental scope

The frozen K.10 campaign covers 16 case families (CF01–CF16), five policy variants (P0–P4), and five repetitions, totaling 400 executions in the deterministic host/reference model. Recorded variance was zero in that model.

The reports support **bounded advantages in selected cases**, not universal P4 superiority. They also record no-advantage controls, shared capabilities, and trade-offs. Exact-event quarantine is present across P0–P4, so it is not claimed as exclusive to P4. QMAX=16 and EPMAX=1 are important capacity limits when interpreting results.

### CF01 presentation treatment

CF01's frozen results table conflicts with later narrative on the P2 attempt count. The original raw run/trace records were unavailable during the final repository audit. For presentation, retain the uncontested outcomes—P0 terminal escalation, P2 success, P4 success—and omit CF01's P2 numerical attempt count from comparisons. Do not alter the frozen result table or rerun the matrix to force agreement. CF16 provides the separately documented P2-versus-P4 attempt trade-off.

## 5. What has been completed

- Gates A–E and the protected reference runtime.
- Deterministic host/reference experiment foundation and frozen K.10 campaign.
- K.10.1–K.10.4 adversarial prior-art/technical-distinction review and final evidence-bounded conclusion.
- K.11 software synthesis and proposed hardware-validation handoff.
- K.12 virtual-system integration and professor-facing UI.
- Local test and browser success reported by the user.
- Final presentation guide and main-branch integration record.

Local build/test/browser runs are recorded as user-reported. They were not independently reproduced by the remote GitHub connector or a verified CI run.

## 6. What is not claimed

The repository does not claim physical MCU flashing, board-level fault injection, timing/RAM/Flash/energy measurements, statistical generalization, formal proof of the complete implementation, universal superiority, or a legal novelty/patentability conclusion.

## 7. Future work

The proposed STM32U575ZI / NUCLEO-U575ZI-Q plan can guide a separately scoped hardware phase. Board pin assignments, clocking, timing, instrumentation and fault injection must be verified against the exact board revision before execution. Hardware is deliberately outside the completed software scope.

## 8. Key references

- [Architecture and repository map](ARCHITECTURE_AND_REPOSITORY_MAP.md)
- [Demonstrator guide](DEMONSTRATOR_GUIDE.md)
- [K.10 results](../research/phase2_k10_p4_advantage_novelty_results.md)
- [K.10.4 conclusion](../research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md)
- [K.11 synthesis](../research/phase2_k11_final_software_synthesis_and_hardware_handoff.md)
- [K.12 audit](../research/phase2_k12_professor_facing_software_demo_and_final_audit.md)
