# Phase 1 — Peripheral Testbed and Fault Model

**Date:** 2026-08-20  
**Phase:** Phase 1 — System Design and Experimental Planning  
**Status:** Design baseline; subject to refinement after physical board acquisition.

## 1. Purpose

Define the smallest physical/software testbed capable of testing the frozen recovery hypothesis without prematurely expanding the project into a general resilience framework.

The testbed must support:

- event-driven transaction generation;
- reproducible peripheral faults;
- fault-associated event identification;
- bounded recovery actions;
- event quarantine;
- preservation measurement for unrelated valid events;
- CPU/RAM/Flash measurement on the MCU;
- host-side repeatability before physical acquisition.

## 2. Primary MCU platform

Primary platform: **STM32U575ZI on NUCLEO-U575ZI-Q**.

The STM32U575 family provides a Cortex-M33 with MPU and multiple I2C, SPI, USART/UART and timer resources. The NUCLEO-U575ZI-Q exposes the MCU through the Nucleo development-board ecosystem.

The board remains subject to acquisition verification. No physical measurements are claimed until the board is actually acquired and executed.

## 3. Minimal peripheral testbed

### Primary interface — I2C

I2C is the primary experimental interface because it supports transaction-level failure scenarios such as timeout/non-response and provides a clear association between a peripheral transaction and an event.

### Secondary interface — SPI

SPI provides a contrasting peripheral protocol so that the policy is not evaluated only as an I2C-specific recovery recipe.

### Initial diagnostic/control path — UART/USART

UART/USART is initially treated as a diagnostic/control channel rather than a purchased external peripheral. It can provide host-facing logs and control commands where the selected board/toolchain permits this without altering the research mechanism.

### Minimal external device strategy

Prefer one low-cost peripheral capable of both I2C and SPI for the first physical testbed where practical. The Bosch BMP280 is a candidate because the device natively supports both I2C and SPI. A final breakout/module choice must be verified for electrical compatibility, availability, and reproducible fault injection before purchase.

CAN is deferred. It is not required to establish the core hypothesis and would add transceiver/protocol complexity before evidence justifies it.

## 4. Fault classes

Faults are divided into three evidence levels.

### Level A — deterministic software-injected faults

Primary experimental mechanism:

1. transaction timeout;
2. forced non-response/error result;
3. repeated transaction failure;
4. invalid peripheral-state indication;
5. event-triggered service failure.

These faults are used for controlled repetitions and statistical comparison.

### Level B — hardware/protocol-relevant faults

After the software policy is stable:

- externally induced I2C non-response or bus-stuck condition where safely reproducible;
- controlled SPI peripheral unavailability/error;
- communication disruption relevant to the selected device.

Electrical fault injection must be designed to remain within board/device electrical limits.

### Level C — naturally occurring faults

Not required for the core experiment. Naturally occurring hardware failures are not sufficiently reproducible to serve as the primary experimental source.

## 5. Fault semantics

Every injected fault should carry a bounded fault record containing at minimum:

- fault ID;
- peripheral/service ID;
- event ID/transaction ID;
- fault class;
- timestamp/cycle count;
- recurrence count within the declared history window;
- recovery attempt count;
- previous recovery outcome;
- association confidence/state.

The exact packed representation will be determined during implementation and must remain statically allocated.

## 6. Event semantics required before implementation

An event must have enough information to determine whether another event can safely execute while the first event is quarantined.

Required conceptual fields:

- event identity;
- event type;
- producer;
- consumer/service;
- peripheral association;
- criticality class;
- dependency relation;
- ordering requirement;
- transaction identity where applicable;
- fault association;
- quarantine state;
- release/retry eligibility.

A dependency relation is preferable to a simple peripheral-wide block. A fault on one transaction must not automatically imply that every queued event for the peripheral is independent or safe.

## 7. Quarantine semantics — preliminary

For a fault-associated event Ei:

`Ei -> QUARANTINED`

means Ei is not executable until an explicit transition releases, retries, reclassifies, or permanently discards it according to the policy.

For an unrelated event Ej, preservation is allowed only when its dependency and ordering constraints permit independent execution.

Therefore the desired behavior is not unconditional queue filtering. It is **dependency-aware selective preservation**.

## 8. Experimental workload structure

Initial workload should contain a mixture of:

- independent peripheral reads;
- independent peripheral writes where safe;
- non-peripheral housekeeping events;
- at least one event with an explicit dependency on another event;
- controlled fault-associated transactions.

A representative sequence can be generated as:

`E1 -> E2 -> E3 -> E4 -> E5`

with one selected event associated with the injected fault and explicit dependency metadata for any events that cannot safely bypass it.

## 9. Baseline fault behavior

### Baseline 1 — Fixed retry

`FAULT -> RETRY N -> SUCCESS / ESCALATE`

No selective event quarantine is assumed beyond what is necessary to implement the baseline consistently.

### Baseline 2 — Fixed retry + peripheral reset/reinitialization

`FAULT -> RETRY N -> RESET/REINITIALIZE -> CONTINUE / ESCALATE`

The baseline must use the same workload and fault schedule as the proposed mechanism.

### Proposed mechanism

`FAULT -> CLASSIFY CONTEXT/HISTORY -> QUARANTINE ASSOCIATED EVENT -> SELECT BOUNDED ACTION -> VERIFY -> RELEASE / DEGRADE / ESCALATE`

The exact policy variables and action subset remain unfrozen until the event/fault semantics are completed.

## 10. Safety and reproducibility constraints

- Do not deliberately exceed MCU I/O voltage/current limits.
- Do not short supply rails or create uncontrolled electrical faults.
- Software fault injection is preferred for early experiments.
- Hardware fault injection must have a defined safe operating envelope.
- Each experiment must record fault type, event workload, injection position, recovery configuration, and outcome.
- Simulation/host results must never be presented as physical MCU measurements.

## 11. Evidence basis

The STM32U575 product documentation confirms Cortex-M33 MPU support and multiple I2C/SPI/USART/UART interfaces. Bosch documentation confirms BMP280 support for both I2C and SPI. These sources establish platform capability only; they do not establish novelty of the proposed recovery mechanism.

## 12. Open design questions

Before implementation, resolve:

1. Exact event record representation and maximum event size.
2. Static queue capacity and overflow semantics.
3. Dependency representation: explicit IDs, dependency masks, or another bounded representation.
4. Exact fault-association rule.
5. Minimum useful recovery-action subset.
6. Recovery-history window size.
7. Quarantine storage model under full-queue conditions.
8. MPU experiment configuration and whether it materially changes the measured mechanism.
9. Exact physical fault-injection apparatus after the board and peripheral are acquired.
