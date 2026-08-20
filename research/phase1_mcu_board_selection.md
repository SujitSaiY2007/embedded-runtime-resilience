# Phase 1 — MCU / Development Board Selection

**Date:** 2026-08-20
**Phase:** Phase 1 — Preparation / System Design and Experimental Planning
**Status:** Candidate evaluation completed; recommendation is the STM32U575ZI Nucleo-144 platform, subject to purchase/availability verification before treating hardware as acquired.

## 1. Selection objective

Select the smallest practical physical MCU platform that can support credible experiments for the frozen research hypothesis:

> Can a compact deterministic zero-heap recovery policy use peripheral fault context/history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, with acceptable CPU/RAM/Flash overhead on a resource-constrained MPU-enabled MCU?

The board is therefore evaluated as an experimental instrument, not merely as a programming board.

## 2. Required criteria

| Criterion | Importance | Reason |
|---|---:|---|
| Usable hardware MPU | Mandatory | Required for the strongest containment/isolation configuration. |
| Single-core/simple execution model | High | Reduces experimental confounders and keeps the event-driven reference architecture small. |
| Adequate but not excessive RAM/Flash | High | The platform should remain resource-constrained enough for meaningful overhead measurements. |
| I2C/SPI/UART availability | High | Enables reproducible peripheral fault experiments. |
| Timer/interrupt capability | High | Needed for timeout detection and latency measurements. |
| Accessible debug/programming | High | Repeatable fault injection and tracing require reliable debugging. |
| Mature vendor SDK/toolchain | High | Reduces board-specific engineering unrelated to the research contribution. |
| Fault-injection controllability | High | The experiment must distinguish reproducible injected faults from accidental hardware failures. |
| Expansion/prototyping access | Medium | External peripheral devices and fault fixtures must be attachable. |
| Cost/availability | High | Solo-project feasibility matters. |
| Documentation quality | High | Architecture and experimental reproducibility depend on primary documentation. |
| Power measurement support | Medium | Useful for energy overhead, but not a blocking criterion. |

## 3. Candidates

### Candidate A — STM32U575ZI / NUCLEO-U575ZI-Q

The STM32U575 is an Arm Cortex-M33 MCU up to 160 MHz with TrustZone, an MPU, up to 2 MB Flash and 786 KB SRAM. ST describes the MCU as ultra-low-power and provides a large peripheral set. This gives substantial room for the recovery manager while retaining a relatively constrained MCU architecture. [ST product page](https://www.st.com/en/microcontrollers-microprocessors/stm32u575zi.html)

**Strengths**

- Hardware MPU directly on the Cortex-M33.
- Single-core Cortex-M33, reducing experimental complexity.
- 2 MB Flash / 786 KB SRAM provides enough space for instrumentation, baselines, and fault logging without requiring external memory for the core experiment.
- Strong I/O/peripheral set and interrupt-capable GPIOs.
- Low-power architecture provides a credible optional energy-overhead experiment.
- STM32Cube ecosystem and broad tooling reduce non-research implementation effort.

**Weaknesses / risks**

- 786 KB SRAM is not extremely small; resource-overhead claims must therefore report absolute footprint and percentage of available memory rather than implying severe scarcity.
- The U5 feature set is richer than the minimum needed, so the experiment must deliberately constrain software resources.
- Physical board availability and local price must be verified at acquisition time.

**Assessment:** **Best overall fit.**

### Candidate B — STM32H563ZI / NUCLEO-H563ZI

The STM32H563 is a Cortex-M33 MCU up to 250 MHz with TrustZone, MPU, 2 MB Flash and 640 KB SRAM. ST's datasheet explicitly describes the MPU as useful for protecting critical code against misbehaving tasks. [ST product page](https://www.st.com/en/microcontrollers-microprocessors/stm32h563zi.html)

**Strengths**

- Hardware MPU and Cortex-M33.
- 2 MB Flash / 640 KB SRAM.
- Higher performance headroom makes timing instrumentation easier.
- Strong STM32 tooling and peripheral ecosystem.

**Weaknesses / risks**

- Higher performance can weaken the narrative that the tested firmware is genuinely resource constrained unless memory/CPU budgets are deliberately fixed.
- The H5 security/performance feature set is more than the research requires.
- The extra performance is not itself useful to the core hypothesis and can become a confounding factor when comparing overhead.

**Assessment:** **Strong alternative**, particularly if U575 availability is poor or if high-resolution timing instrumentation becomes a priority.

### Candidate C — Renesas RA6M5 / EK-RA6M5

The RA6M5 provides a 200 MHz Arm Cortex-M33 with Arm MPU support, up to 2 MB code Flash and 512 KB SRAM. The official evaluation kit provides on-board SEGGER J-Link debugging, CAN FD, Ethernet, I2C, SPI, UART, USB, native pin access, and current-measurement points. [Renesas RA6M5 datasheet](https://www.renesas.com/en/document/dst/ra6m5-group-datasheet) [EK-RA6M5](https://www.renesas.com/en/design-resources/boards-kits/ek-ra6m5)

**Strengths**

- Explicit MPU support.
- 512 KB SRAM makes resource overhead more visible than on U575.
- Excellent physical testbed connectivity, especially CAN FD and Ethernet.
- On-board J-Link and current-measurement points are valuable for reproducibility.
- Native headers and multiple expansion connectors simplify peripheral fault fixtures.

**Weaknesses / risks**

- More elaborate board connectivity than the minimum experiment needs.
- Renesas tooling/API ecosystem introduces a different software stack from the more familiar STM32 environment; this is not inherently negative, but it adds learning/porting cost.
- The richer communication testbed could tempt unnecessary scope expansion.

**Assessment:** **Best experimental-feature alternative** and arguably the strongest board if CAN FD or current measurement becomes central. It is not selected as primary because the project can achieve its core hypothesis with simpler I2C/SPI/UART experiments and should minimize platform-specific complexity.

### Candidate D — NXP FRDM-MCXN947

The MCX N94 family uses dual Cortex-M33 cores at 150 MHz, with 2 MB Flash and 512 KB SRAM according to NXP's current family documentation. The FRDM-MCXN947 has current MCUXpresso SDK support and a substantial industrial-IoT peripheral ecosystem. [NXP MCX N family](https://www.nxp.com/products/MCX-N94-N54-N53-N52-N24) [FRDM-MCXN947 SDK documentation](https://mcuxpresso.nxp.com/mcuxsdk/latest/html/boards/MCX/frdmmcxn947/index.html)

**Strengths**

- Cortex-M33 platform with modern security ecosystem.
- 512 KB SRAM / 2 MB Flash is appropriate for constrained-resource measurements.
- Strong peripheral and SDK support.
- Current NXP documentation and active SDK support.

**Weaknesses / risks**

- The N94 platform is **dual-core**, creating an unnecessary experimental variable for a research question whose reference architecture is deliberately small and cooperative/event-driven.
- Core-to-core interactions, scheduling, shared resources, and multicore debug can complicate attribution of CPU and recovery overhead.
- The project does not require the extra multicore capability.

**Assessment:** **Technically capable but rejected as primary** because multicore complexity conflicts with the project's smallest-defensible-system objective.

## 4. Comparative decision matrix

Scores are engineering judgments for this project, not vendor benchmarks. 5 = strong fit, 1 = poor fit.

| Criterion | STM32U575 | STM32H563 | RA6M5 | MCXN947 |
|---|---:|---:|---:|---:|
| MPU suitability | 5 | 5 | 5 | 4 |
| Experimental simplicity | 5 | 5 | 4 | 2 |
| Resource-constrained relevance | 4 | 4 | 5 | 5 |
| I2C/SPI/UART testability | 5 | 5 | 5 | 5 |
| Timing/interrupt capability | 5 | 5 | 5 | 5 |
| Debug/toolchain practicality | 5 | 5 | 4 | 4 |
| Fault-injection flexibility | 5 | 5 | 5 | 4 |
| Expansion/prototyping | 4 | 4 | 5 | 5 |
| Energy measurement potential | 4 | 3 | 5 | 3 |
| Scope-control suitability | 5 | 4 | 4 | 2 |
| **Overall fit** | **47/50** | **45/50** | **47/50** | **37/50** |

The numerical totals are not treated as objective proof. The decisive qualitative factor is that U575 achieves the required MPU + peripheral + debug combination without adding multicore complexity, while RA6M5 is the strongest alternative if CAN FD or power measurement becomes experimentally important.

## 5. Decision

### Recommended primary platform

**STM32U575ZI on the NUCLEO-U575ZI-Q development board.**

This is a **platform recommendation, not yet an acquisition confirmation**.

The selection is based on:

1. native Cortex-M33 MPU;
2. single-core execution model;
3. sufficient but not excessive RAM/Flash;
4. broad I2C/SPI/UART capability;
5. interrupt/timer resources;
6. mature development/debug ecosystem;
7. low-power capability for optional energy measurements;
8. ability to keep the experimental architecture small;
9. no requirement for an RTOS or external management controller.

### Secondary platform

**Renesas EK-RA6M5** remains the preferred fallback/alternative if acquisition, peripheral availability, or power-measurement requirements favor it.

### Explicit rejection of MCXN947 as primary

The dual-core N94 architecture introduces an unnecessary experimental dimension. The project is specifically trying to establish a small deterministic recovery policy on event-driven MCU firmware; a single-core platform provides cleaner attribution of recovery CPU overhead and event-queue behavior.

## 6. Important experimental qualification

The selected U575 platform does **not** make the research inherently "resource constrained." Its available memory is substantial. Therefore the eventual experiment must define an explicit software resource envelope, for example:

- fixed queue capacities;
- fixed event-record count;
- fixed recovery-history record count;
- fixed log-buffer capacity;
- fixed maximum recovery transitions;
- measured CPU time and memory footprint.

The research claim should be based on the mechanism's measured overhead under this declared envelope, not on the board's marketing classification.

## 7. Acquisition gate

Before declaring the hardware available, verify:

- exact board part number;
- physical availability in India;
- current price and delivery;
- genuine board/source;
- required USB/debug accessories;
- availability of compatible I2C/SPI/UART peripheral modules;
- ability to connect an external fault-injection fixture safely.

No physical measurements are valid until the board is actually acquired and executed.

## 8. Sources

Primary sources consulted for this selection:

- STMicroelectronics — STM32U575ZI product page and datasheet.
- STMicroelectronics — STM32H563ZI product page and datasheet.
- Renesas — RA6M5 Group Datasheet and EK-RA6M5 official board page.
- NXP — MCX N family product information and FRDM-MCXN947 MCUXpresso SDK documentation.

These sources establish device capabilities. They do **not** establish local retail price or availability; those remain acquisition-gate checks.
