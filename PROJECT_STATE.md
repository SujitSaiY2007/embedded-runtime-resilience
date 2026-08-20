# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`
**Status:** Development topic frozen; Phase 1 board selection completed as a recommendation pending acquisition verification.
**Project mode:** Solo software-dominant embedded-systems project
**Primary ambition:** Research-grade implementation with publication potential and possible patent pathway if supported by evidence and professional assessment.

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

### Short working title

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Core research question

Can a compact, deterministic, software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Phase 1 board decision

**Primary recommendation:** STM32U575ZI on NUCLEO-U575ZI-Q.

**Fallback/alternative:** Renesas EK-RA6M5.

The primary recommendation is based on native Cortex-M33 MPU support, single-core execution, adequate but bounded memory, broad I2C/SPI/UART peripheral access, interrupt/timer resources, mature tooling, and low-power capability without introducing unnecessary multicore experimental variables.

The board is **not yet considered physically acquired**. Current price, Indian availability, genuine sourcing, and accessory availability remain acquisition-gate checks.

## Candidate comparison

- STM32U575ZI / NUCLEO-U575ZI-Q — primary recommendation.
- STM32H563ZI / NUCLEO-H563ZI — strong alternative; more performance than required.
- Renesas RA6M5 / EK-RA6M5 — strong alternative, especially for CAN FD and power measurement.
- NXP FRDM-MCXN947 — technically capable but rejected as primary because its dual-core architecture introduces unnecessary experimental complexity.

Detailed evidence and scoring are recorded in `research/phase1_mcu_board_selection.md`.

## Integration decisions already frozen

### Zero-heap

The recovery manager and reference firmware use no runtime dynamic allocation. State, queues, recovery records, and policy tables are statically bounded.

### Context-aware recovery

Policy variables may include fault type, timeout/error pattern, recurrence, recovery history, previous outcome, service criticality, and pending workload. Exact variables remain a design-stage decision.

### Bounded recovery

Candidate actions remain a finite set: retry, reinitialize, peripheral reset, controlled degradation/isolation, escalation. The minimum useful subset remains to be selected after the fault model is defined.

### Event quarantine

Use `event quarantine` / `fault-associated event quarantine` as formal terminology. Quarantine must respect dependency, transaction, and ordering semantics and must not indiscriminately flush unrelated valid work.

### MPU

MPU is a containment/isolation capability, not a claimed invention. The core policy must remain meaningful even if MPU-specific experimentation becomes secondary.

### Event-driven architecture

The reference architecture remains cooperative/event-driven and resource constrained. A heavyweight RTOS is not a mandatory dependency.

## Current phase gates

Completed:

- [x] Research-space decomposition
- [x] Candidate shortlist
- [x] Deep prior-art attack
- [x] Development topic selection
- [x] Zero-heap constraint decision
- [x] Event-quarantine decision
- [x] MPU scope decision
- [x] MCU/board candidate evaluation
- [x] Primary board recommendation

Remaining:

- [ ] Verify board acquisition availability/price/source
- [ ] Acquire primary board
- [ ] Define exact peripheral testbed
- [ ] Define fault model and safe injection method
- [ ] Define event model and dependency semantics
- [ ] Define recovery-policy state machine
- [ ] Define queue invariants
- [ ] Define formal properties/proof strategy
- [ ] Define baseline implementations
- [ ] Define experimental protocol
- [ ] Build minimal architecture before feature expansion

## Experimental direction

Compare:

1. fixed retry;
2. fixed retry + peripheral reset/reinitialization;
3. proposed zero-heap context-aware recovery + event quarantine.

Primary metrics include detection latency, service-restoration latency, recovery success rate, whole-system reset count, unrelated-event preservation, quarantine correctness, lost/duplicated events, queue occupancy, CPU overhead, RAM/Flash footprint, recovery-state count, and energy impact where practical.

## Hardware qualification

No physical measurements are valid until the actual board is acquired and firmware is executed on it. Host simulation results must be explicitly labelled as simulation/host results.

## Research contribution discipline

Do not claim novelty for zero-heap allocation, MPU isolation, peripheral recovery, event queues/quarantine, context-aware recovery, recovery state machines, or formal invariants individually. The research contribution remains the specific integrated mechanism and measured technical trade-off.
