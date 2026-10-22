# Chat 05.2 — Zero-Budget Hardware Bring-Up and Evidence-Gated Validation

**Date:** 2026-10-22  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Branch:** `main` only  
**Purpose:** Safely identify, connect, build, flash, and validate only the already-owned hardware, if and only if every electrical and target-compatibility gate passes.  
**Additional budget:** ₹0. No purchases, borrowing, substitutions, or extra hardware.

## 1. Starting state from Chat 05

- STM32CubeIDE was installed and opened successfully.
- A generated STM32CubeIDE Empty Project named `Embedded-Runtime-Resilience` was created for the STM32L476RG family. Project tree included `Inc`, `Src`, `Startup`, and linker scripts `STM32L476RGTX_FLASH.ld` / `STM32L476RGTX_RAM.ld`.
- The user showed generated `main.c` with an infinite loop and a warning that the FPU is not initialized although the project is compiling for an FPU.
- The user showed a build console reporting **0 errors, 1 warning** and “Build Finished.” This is only a generated empty-project build. It does not prove that custom firmware, a sensor driver, a board flash, or hardware behavior works.
- The board had **not been connected** while the above IDE steps were performed.
- No firmware was flashed and no physical sensor/wiring test was performed in Chat 05.
- Do not assume the IDE project is the repository’s existing source tree. Its shown workspace location is under the user's STM32CubeIDE workspace. Do not overwrite, import over, or confuse it with the canonical GitHub repository.

## 2. Existing component inventory — no new purchases

Use this list as the starting inventory, then reconcile it against the photos already provided and any visible markings. Do not silently fill unknown details.

| Component | Quantity recorded | Current evidence / limitation |
|---|---:|---|
| STM32 Nucleo board, expected NUCLEO-L476RG | 1 | User selected STM32L476RG family in CubeIDE; confirm exact physical board silk-screen/product code and revision before wiring. Earlier Plan 2.0 records mention NUCLEO-U575ZI-Q; discrepancy must be explicitly assessed, not ignored. |
| BME280-labelled environmental sensor/module | 1 | Receipt/inventory label says BME280; exact chip/module/breakout, pin labels/order, supply range, regulator, level shifting and pull-ups are not yet verified. Do not assume it is BME280 rather than a visually similar BMP280. |
| MB-102 solderless breadboard, 830 tie points | 1 | Receipt inventory; rail layout/continuity and actual condition not independently tested. |
| 4-pin, 5 mm push-button packs, three buttons per pack | 2 packs | Receipt inventory; actual switch pin geometry and internal connectivity not established. Do not need these if the onboard Nucleo user button is sufficient. |
| Resistor packs | 4 packs | Receipt inventory; resistance values/tolerance not established. Do not use unknown resistors for pull-ups/current limiting. |
| Jumper-wire items/packs | 6 items/packs as recorded | Receipt count is not a count of individual wires. Male/female ends, exact count and condition must be visually checked. |
| USB programming cable described for Arduino Uno/Mega | 1 | Connector ends, fit to the Nucleo ST-LINK USB connector, and USB data capability are unverified. Never force a connector. |
| STM32CubeIDE | Installed | User showed IDE home and generated project. Exact IDE version/toolchain setup and installed packages should be recorded from the machine rather than guessed. |

**Recorded receipt total:** ₹739. **New spending allowed:** ₹0.

No other sensors, debugger, USB adapter, logic analyser, multimeter, resistor, cable, or replacement board may be assumed available. If an essential verification requires equipment or components not in the inventory, stop that branch of the task and report the blocker. Do not ask the user to purchase anything.

## 3. Non-negotiable safety gates

1. **Start with the board disconnected from USB and all external wiring removed.**
2. Photograph/read the exact board markings and revision; verify against official ST documentation and matching schematic/manual.
3. Inspect both ends of the already-owned cable and the actual ST-LINK connector. Connect only if the connector fits normally and the cable is known/verified to carry data. Never force it.
4. Identify the sensor module using its front/back photographs, all pin labels, PCB marking, packaging or existing purchase record. Use manufacturer documentation for the exact module. Appearance alone is insufficient.
5. Establish sensor supply-pin voltage, I/O logic limits, regulator/level shifter presence, I²C pull-up values/rail, and pin order. Bare-chip BME280 limits do not automatically apply to an unknown breakout.
6. Resolve the documented NUCLEO-U575ZI-Q versus physical NUCLEO-L476RG target mismatch against actual research requirements (MPU/security features, memory/peripherals and proposed claims). Do not silently port or claim equivalence.
7. Verify board-side I²C routing for the exact revision/configuration and relevant solder bridges before pin selection. PB9/D14 SDA and PB8/D15 SCL are only candidate routes from the NUCLEO-L476RG manual, not automatic permission to wire.
8. Never apply 5 V to an unidentified module or MCU pin. Never short pins, experiment with power pins, hot-unplug wires as a fault trigger, or use unknown resistors.
9. Do not connect sensor power/SDA/SCL until a complete, evidence-backed pin-by-pin wiring table has been reviewed and explicitly approved.
10. If any essential fact remains unknown, leave the sensor disconnected and continue only with safe IDE/repository analysis or the existing software demonstrator.

## 4. Firmware and repository safeguards

- Work on `main` only. Never create/switch to another branch, force-push, or merge.
- Before any repository write, inspect current `main` HEAD and re-fetch/reconcile if it has moved.
- Preserve `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen K.10 evidence, experiment configuration/sources, prior-art analyses, manuscript, and historical records. Do not modify protected files to make the hardware path fit.
- Do not rerun or regenerate the frozen 400-execution host/reference campaign.
- Do not install additional IDE packs, libraries, drivers, packages or dependencies without explicit approval; first inspect what is already installed and available.
- Do not copy the empty CubeIDE project's generated startup/linker files into the canonical repository without a reviewed source-to-target plan and explicit need.
- Do not assume a BME280 driver or STM32 adapter exists: inspect the current repository and document the exact source paths found or the absence of them.
- Any custom firmware must use a clearly documented, narrow adapter boundary. Reuse the authoritative policy logic where feasible, but do not claim it is the same runtime unless source-level equivalence is demonstrated.
- Separate software-injected driver errors from real hardware/I²C faults in every trace and report.

## 5. Required staged workflow

### Gate A — Inventory and physical identification
Record the actual board model/revision, sensor PCB markings and pin labels, cable ends, and wire types using available photos/markings. Mark every item VERIFIED / PARTIALLY VERIFIED / UNVERIFIED. Do not proceed on guesses.

### Gate B — Compatibility and target decision
Use official documentation for the exact board and module. Produce a pin-by-pin table including signal, board pin, module pin, electrical level, source and confidence. Check I²C routing, pull-ups and supply compatibility. Explicitly assess L476 versus U575 requirements. If any critical field is unresolved, STOP: no sensor wiring.

### Gate C — USB and board-only baseline
Only after connector and cable suitability are established, connect the board alone using the correct existing USB connector. Observe the IDE/debug probe/device detection without powering an external sensor. Record what is actually observed. If connection fails, stop and diagnose from evidence; do not suggest a new cable purchase. Do not flash until the target and project configuration are confirmed.

### Gate D — Generated-project and firmware audit
Inspect the generated project, MCU selection, clock/startup/FPU configuration, build output and warnings. Explain the FPU warning before changing configuration. A successful empty-project build is only a compiler/linker baseline. Check available installed compiler/debug tools without installing new components. Review the repository's runtime contract and driver boundary before writing code.

### Gate E — Wiring approval
Prepare the exact safe wiring map using only the inventory above. Include board pin names, sensor pin labels, ground, supply, SDA/SCL, pull-up analysis, and why each connection is electrically safe. Explicitly state which existing jumpers/breadboard are used. If any wire type, module pin, supply level or pull-up condition is unclear, do not connect. Ask the user to show the completed unpowered wiring for review before power is applied.

### Gate F — First powered baseline
Proceed only after Gates A–E pass. Use the lowest-risk sequence in the board and module manuals. First establish board-only behavior, then add only the verified sensor wiring with power removed during wiring changes. Capture raw IDE/build/debug/serial/I²C evidence. Do not claim sensor success from an LED blink or successful compilation alone.

### Gate G — Minimal sensor and event baseline
If compatible and driver implementation is feasible using existing tools, perform a bounded sensor identity/read test and record raw results. Only then test a button/event path. Prefer the onboard Nucleo user button and LED over the purchased buttons if they satisfy the demonstration need. Do not connect external buttons unnecessarily.

### Gate H — Recovery path (not automatic)
Do not inject faults until a stable healthy baseline, actual driver path, bounded timeout behavior and reversible safe trigger are established. Prefer a controlled software-injected driver-boundary error first and label it honestly. Do not short SDA/SCL, disconnect powered wires, create overvoltage, or damage hardware. A recovery pass requires a fresh successful sensor transaction after the recovery action; a reset log alone is not enough.

### Gate I — Evidence and handoff
Record source commit, project configuration, toolchain versions, board/module identity, raw output, test ID, expected behavior, actual behavior, failures/timeouts, recovery procedure and result. Keep host/reference results separate from MCU results. Record commands actually run; no unsupported “passed” claims.

## 6. Acceptance criteria

Chat 05.2 may close only with a truthful status for each gate. The final outcome may be BLOCKED if the existing hardware cannot safely satisfy requirements. No requirement exists to force a physical demo at the expense of safety or evidence quality.

- Board and sensor identity documented from actual evidence.
- Cable suitability determined without assuming data capability.
- Electrical compatibility and pin map verified before wiring.
- L476/U575 target discrepancy explicitly resolved or retained as a documented blocker.
- Existing tools only; zero new purchases and no unapproved installations.
- Build/flash claims backed by actual outputs; sensor reads backed by raw evidence.
- Recovery claims backed by a fresh successful post-recovery transaction.
- Protected runtime and frozen evidence unchanged.
- Updated current state and handoff with commit SHA, checks, raw artifact locations, remaining blockers, and exact next chat.

## 7. Exact starting instruction

Begin by reading:
- `Plan2.0/README.md`
- `Plan2.0/CURRENT_STATE.md`
- `Plan2.0/CHAT_PROTOCOL.md`
- `Plan2.0/EXECUTION_ROADMAP.md`
- `Plan2.0/hardware/CHAT_05_HARDWARE_COMPATIBILITY_AUDIT.md`
- `Plan2.0/hardware/CHAT_05_ZERO_BUDGET_DEMONSTRATION_PLAN.md`
- `Plan2.0/hardware/CHAT_05_RISK_AND_BLOCKER_REGISTER.md`
- `Plan2.0/handoffs/CHAT_05_HANDOFF.md`
- this Chat 05.2 prompt and handoff.

Then inspect the live `main` head and repository before acting. Use the component inventory above as the authoritative known starting point, and reconcile it with the already-uploaded photos in the prior conversation when available. Do not ask the user to repeat known information unless a specific critical marking is unreadable or missing. Do not wire or energize the sensor until the documented gates explicitly permit it.
