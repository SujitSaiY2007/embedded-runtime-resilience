# Phase 5 — Software-to-Hardware Demonstration and UI Integration Conclusion

**Date:** 2026-10-26  
**Branch:** `main`  
**Status:** Evidence-bounded demonstrator established; full live UI-to-physical-MCU integration is not established and is not claimed.  
**Evidence basis:** Current software demonstrator source/guide, BME280 policy-integration source, Chat 11 hardware report, and Phase 2 hardware closure.

## Executive conclusion

The project has two working evidence paths, but they must not be conflated:

1. **Software demonstrator path:** Browser UI → Python HTTP bridge → compiled C virtual-system/scenario runner → protected C reference runtime → runtime result/digest/trace → UI.
2. **Physical hardware path:** STM32L476RG firmware → controlled I²C address-NACK stimulus → recovery decision/action → fresh BME280 chip-ID read → debugger-visible outcome.

The repository's current software UI executes against the virtual embedded system. The physical hardware experiments were performed through STM32CubeIDE and debugger-visible variables. The available repository evidence does not show a live communication channel in which the browser UI commands the physical board and receives its current trace directly. Therefore, a **fully integrated real-time UI-to-MCU demonstration cannot honestly be marked complete**.

A meaningful end-to-end *evidence story* is available: the UI demonstrates the software runtime and trace; the hardware evidence report documents a separate physical run. That is a coherent research demonstration, but it is not the same as one continuous live UI-to-hardware system.

## Evidence that exists

### A. Software demonstrator

The current `demo/server.py` serves the browser UI and proxies live execution requests to the compiled C virtual-system CLI. The code restricts requests to registered scenarios and P0–P4 variants; the C runtime remains authoritative for software decisions. `docs/DEMONSTRATOR_GUIDE.md` defines the build, run, and UI-contract test procedure.

This supports a live software/virtual-system demonstration when the local build and tests run successfully. The GitHub-side source inspection is not itself an independent build or browser test.

### B. Physical hardware demonstration

The saved hardware records report a successful CubeIDE build and a controlled BME280 transaction-level NACK test. In the five-policy diagnostic run, P1 and P4 reached `R_PASS`, returned the expected BME280 chip ID `0x60`, and reported successful release; P0, P2, and P3 reached terminal/non-pass outcomes. The separate five-control-trial record shows successful post-NACK chip-ID reads without a full peripheral initialization call between the controlled NACK and the subsequent read.

These are user-observed debugger outcomes. The experiment did not test physically stuck SDA/SCL, does not represent five independent physical runs per policy, and does not establish a complete hardware performance profile. The exact modified source used in the CubeIDE run is not hash-linked to the flashed binary.

### C. Resource figures

The Phase 2 closure records linker output: text 12,948 bytes, data 112 bytes, BSS 12,704 bytes, total 25,764 bytes. These are build/linker figures, not measured stack high-water mark, recovery latency, energy, or a complete resource profile. The BSS figure should not be described as the runtime's exact additional RAM cost without a matched baseline build and a defined accounting method.

## Integration acceptance matrix

| Acceptance item | Status | Reason |
|---|---|---|
| Browser UI invokes the software C reference runtime through the virtual adapter | Implemented in repository | Existing server and demonstrator architecture. |
| Runtime result and trace are returned to the UI for software scenarios | Implemented in repository design | Runtime-authoritative software path. |
| Physical BME280 NACK/recovery path is demonstrated through debugger-visible firmware state | User-evidence supported | Saved hardware report; narrow scenario and provenance limits apply. |
| Same browser UI sends a command to the physical MCU | Not demonstrated | No verified board transport/control endpoint is evidenced in the current integration records. |
| Same UI receives a live trace directly from the physical MCU | Not demonstrated | Physical observations were captured in STM32CubeIDE, not returned through the browser server. |
| Software and hardware records are correlated through a shared run ID/schema and provenance field | Not established | No verified end-to-end correlation protocol is documented as operational. |
| A disconnected peripheral and reconnection path is exercised through the browser UI on real hardware | Not demonstrated | Existing UI disconnection behavior applies to the virtual peripheral model. |
| Build/binary/source identity is reproducible for the flashed hardware artifact | Incomplete | Exact modified CubeIDE source and flashed binary hash are not linked in the evidence record. |

## Recommended final demonstration format

Given the current evidence and the project decision not to run more hardware experiments at this stage, present the demonstration as two clearly labeled panes or segments:

1. **Software mode:** run a registered scenario through the browser UI; show policy, C runtime outcome, digest, and correlated runtime/wrapper traces.
2. **Hardware evidence mode:** present the preserved CubeIDE screenshots and the hardware report for the controlled NACK run. Label it as a recorded physical experiment, not a live UI-controlled run.
3. **Evidence boundary:** explicitly show which output came from host/reference execution and which came from the physical board.

Do not make the UI simulate hardware status while implying that it is reading the real board. If a future live integration is pursued, it requires a real board transport (for example, a documented serial protocol), message framing, run IDs, timeouts, error states, provenance metadata, and an acceptance test proving that UI requests and returned values correspond to the same physical execution. That is a separate future implementation task and must not be inferred from the current screenshots.

## Final Phase 5 decision

**Classification: physical recovery behavior and a software demonstrator are separately evidenced; full live software-to-hardware UI integration is not complete.**

The project can be presented now as a software-first recovery research prototype with a bounded physical validation milestone. It cannot yet be presented as a single real-time UI that controls and observes the STM32 recovery runtime end to end.

No further hardware run, runtime modification, frozen-campaign rerun, or replacement of evidence is required to make this conclusion. This report records the current evidence boundary rather than creating new experimental claims.
