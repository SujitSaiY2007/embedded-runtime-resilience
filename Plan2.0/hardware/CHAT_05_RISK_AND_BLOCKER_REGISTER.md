# Chat 05 — Risk and Blocker Register

**Date:** 2026-10-22  
**Current decision:** Physical wiring `BLOCKED`; no additional purchases permitted.

Severity definitions: **Critical** = could damage equipment or create an unsafe electrical condition; **High** = could invalidate the demonstration or cause a misleading research claim; **Medium** = recoverable setup/documentation problem.

| Risk / blocker | Severity | Evidence required | Prevention / stop condition | Safe fallback |
|---|---|---|---|---|
| Board identity or revision differs from the assumed NUCLEO-L476RG / MB1136 | High | Clear board markings and matching ST documentation | Stop pin-map approval until identified | Keep software demo |
| Earlier NUCLEO-U575ZI-Q target conflicts with L476 board | High | Requirements-to-MCU capability comparison, including MPU/security and peripheral needs | Do not silently port or claim target equivalence | Document the target gap; host/reference model |
| BME280 module is a different breakout or pin order than assumed | Critical | Clear photo, module markings, manufacturer pinout | No wiring/power until exact module is identified | No sensor connection |
| Module supply voltage or logic level is incompatible | Critical | Module schematic/datasheet showing supply and I/O limits | Do not energize while unknown; never assume 5 V tolerance | Software-only demo |
| SDA/SCL mapping or board solder-bridge routing is wrong | Critical | UM1724 plus matching board revision schematic and firmware pin config | Do not wire until exact route confirmed | Software-only demo |
| I²C pull-ups absent, excessive, or connected to the wrong voltage | Critical | Breakout schematic, resistor values/rail, bus requirements | Do not connect unknown pull-ups or rely on assumptions | Software-only demo |
| Ground or power arrangement is incorrect | Critical | Exact module pinout and board power documentation | No power-on until full pin map reviewed | Software-only demo |
| Existing cable does not fit or is charge-only | Medium | Physical connector photos and data capability | Do not force connector; no replacement purchase | Use only if existing suitable cable is confirmed; otherwise report blocker |
| Resistor pack values unknown | Medium/High | Actual values/markings or verified measurement | Any design depending on a value stays blocked | Use verified MCU internal pulls only where appropriate |
| Button pin geometry unknown | Medium | Module/button pin arrangement evidence | Do not guess connected pins | Use onboard user button after firmware feasibility is established |
| Breadboard rails/layout or jumper ends misunderstood | Medium | Physical inspection and continuity/layout check | Verify before use; no assumed rail continuity | Avoid external circuit until verified |
| STM32 firmware toolchain/driver missing | High | Installed toolchain inventory and build evidence | Install no new dependencies without approval; no claim of firmware build | Existing C/reference/UI demonstrator |
| Recovery policy is not connected to actual sensor-driver path | High | Source trace, driver-boundary log and post-recovery read | Stop any claim of physical recovery if policy path is bypassed | Demonstrate software policy only |
| Fault trigger causes electrical damage or cannot be repeated | Critical | Written safe trigger and predeclared acceptance procedure | No shorts, overvoltage, unsafe hot-unplug or deliberate damage | Bounded software-injected driver error, labeled as such |
| Virtual traces are presented as MCU results | High | Provenance labels and raw physical traces | Keep host and hardware evidence in separate sections | Label results host/reference-only |
| Frozen evidence or protected runtime accidentally changes | High | Before/after commit/diff and protected blob hashes | Never alter protected files in this task; stop on unexpected changes | Reconcile repository state before proceeding |

## Current blockers

1. **BME280 breakout identity and electrical design unknown.**
2. **Actual cable connectors/data capability unknown.**
3. **Physical board markings and solder-bridge configuration not directly checked.**
4. **L476 versus previously planned U575 target discrepancy unresolved.**
5. **No hardware-specific sensor driver/STM32 adaptation was found in inspected repository paths.**
6. **No safe physical-path fault mechanism or real post-recovery transaction has been demonstrated.**

## Status summary

- Board family capabilities: `PARTIALLY VERIFIED`.
- BME280 compatibility: `UNVERIFIED`.
- Programming cable: `UNVERIFIED`.
- Exact wiring: `BLOCKED`.
- Physical execution: `BLOCKED`.
- Software/reference fallback: documented in repository; not rerun in Chat-05.
- Purchase prohibition: active; additional budget remains ₹0.
