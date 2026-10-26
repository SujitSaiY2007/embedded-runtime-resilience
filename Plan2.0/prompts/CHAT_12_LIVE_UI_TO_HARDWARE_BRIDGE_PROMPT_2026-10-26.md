# Chat 12 — Live UI-to-NUCLEO Hardware Bridge and Matched Software Comparison

**Date:** 2026-10-26  
**Repository:** https://github.com/SujitSaiY2007/embedded-runtime-resilience  
**Branch policy:** `main` only.  
**Objective:** Extend the existing browser UI and Python bridge so the user can trigger a narrowly allowlisted test on the existing STM32L476RG + BME280 hardware over a local serial connection, then compare the observed physical result with the corresponding C reference-runtime/software result in the same UI.

## 1. Mission and non-negotiable accuracy

Implement a real, local, bounded hardware-control path in the existing UI. Do not create a replacement UI or claim a live physical connection until it is demonstrated.

**Important terminology:** The browser should not send arbitrary C source code to the MCU. It should send a structured, allowlisted test command to firmware that has already been built and flashed. The local Python bridge mediates USB virtual-COM/serial communication. Firmware flashing remains a separate, explicit CubeIDE step unless a later, separately approved, verified flash workflow is designed. Never silently compile or flash arbitrary code from a browser click.

The target hardware is the user's existing **ST NUCLEO-L476RG (STM32L476RG)** and **BME280 at I²C address 0x76**, previously demonstrated with chip ID `0x60`; current documented sensor wiring is PB8/I2C1_SCL and PB9/I2C1_SDA. Do not substitute STM32U575 or claim equivalence.

Read and reconcile current `Plan2.0/CURRENT_STATE.md`, `Plan2.0/EXECUTION_ROADMAP.md`, `Plan2.0/CHAT_PROTOCOL.md`, the current `demo/index.html` (the UI logic is embedded in this file unless inspection shows otherwise), `demo/server.py`, `docs/DEMONSTRATOR_GUIDE.md`, `Plan2.0/firmware/bme280_policy_integration/main.c` and README, the Chat 09/11 hardware reports, and `research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md`. Inspect the protected runtime APIs and existing build setup before designing adapters. Do not repeat completed baseline/hardware experiments just to rediscover known results.

## 2. Only include physically demonstrable cases

Keep the first version deliberately small. Implement only the cases below if the existing source and wiring audit confirms they are safe and genuinely supported:

1. **Hardware baseline:** read BME280 chip ID at address 0x76 and register 0xD0; expect 0x60.
2. **Controlled address-NACK recovery:** firmware attempts a read at absent address 0x77 and accepts the stimulus only if the MCU reports the expected NACK. Run the existing P4 decision/action path, execute only the supported I²C1 peripheral reinitialization action, perform a fresh chip-ID read at 0x76, and release the event only after verification succeeds.
3. **Optional control condition:** only if existing committed source and the previous control-trial evidence support it without inventing a new fault mechanism, show the documented controlled-NACK/post-read case without full `iinit()` as a separate labeled control. Do not make it a P4-policy result if it bypasses P4.

Do not expose arbitrary fault injection, electrical shorting, stuck-SDA/SCL claims, arbitrary peripheral actions, all-80-physical-case claims, or policy variants that are not implemented and safely testable on this hardware. No GPIO pin forcing, unsafe electrical faulting, or additional hardware is authorized.

## 3. Required architecture

Preserve the existing software mode and add a clearly separate hardware mode:

```
Existing software mode:
Browser UI → localhost Python bridge → existing C virtual-system CLI
            → protected C reference runtime → software result and trace

New physical mode:
Browser UI → localhost Python bridge → USB VCP/serial
            → pre-flashed STM32 firmware → BME280/I²C1
            → structured response + device run ID → UI

Comparison panel:
matched logical scenario/policy inputs
    ├─ software/reference-runtime result
    └─ physical MCU observation
       → compare corresponding fields, show match/mismatch/unsupported
```

The physical path must be real serial communication with the board, not a canned response, browser-side simulation, static screenshot, or output copied from a previous run. Label software results and physical observations with source/provenance, run ID, timestamp if available, and firmware/protocol version.

### Transport and local security

- First determine whether the NUCLEO ST-LINK USB Virtual COM Port is available and whether the user's cable/host exposes a data-capable serial port. Do not assume a COM number or baud rate.
- Inspect existing environment/dependencies before choosing a serial library. Do not purchase hardware or silently install new software/dependencies. If a necessary dependency is absent, assess a no-new-dependency option first; if none is practical, stop at that gate and explain the exact user approval needed rather than pretending the bridge works.
- Use a documented, versioned, line-framed request/response protocol with a request ID, bounded payload, response terminator, and timeout. A compact JSON-lines protocol is acceptable if the embedded implementation can parse it safely; a simple fixed command grammar is also acceptable and may be preferable on an MCU.
- Add an explicit port selection/status view. Do not assume the first serial device is the board; allow explicit selection and verify the firmware handshake/board identity.
- Keep the server bound to loopback only (`127.0.0.1`) for hardware-control use. Hardware actions must use POST or another explicit state-changing method, not GET. Reject unknown commands, invalid policy/scenario identifiers, malformed frames, stale responses, and concurrent hardware runs.
- Use one hardware transaction at a time, explicit timeouts, a clear disconnected/busy/error state, and a safe recovery from serial timeouts. Never report success based only on a successful write; require a valid response from the running firmware and a fresh sensor read.
- Do not allow arbitrary shell commands, source upload, or arbitrary firmware flashing from the web UI.

## 4. Matched software-vs-hardware comparison

The user's goal is to compare the *same logical test*, not to place unrelated results side by side and call them matched.

1. Inspect the current C runtime API and the existing virtual CLI to determine whether the controlled-NACK/P4 logical case can be represented through a non-invasive adapter.
2. Prefer a small new software-side scenario/adapter that links the existing protected reference runtime unchanged, if feasible. Do not edit `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, or frozen campaign code/results.
3. If the exact physical NACK event cannot be represented faithfully by the current software runtime, show two explicitly labeled outputs and an **unmatched/partial comparison** indicator. State which fields are comparable (e.g., P4 selected action, verification pass/fail, release/terminal outcome) and which are hardware-only (actual NACK flag, actual BME280 chip-ID read). Do not manufacture equivalence.
4. Do not claim that the MCU's result is computed by the host model. The host runtime decides the software-side action; the MCU firmware's runtime/action path is reported separately.
5. Preserve existing P0–P4 virtual scenarios and all frozen 400-run evidence. Do not rerun the 400-execution campaign.

## 5. Firmware changes and flashing workflow

- Inspect the current committed firmware candidate and exact runtime API. Extend it minimally to initialize the serial transport, accept only the supported command(s), run the selected bounded test, and return a structured report.
- Keep the existing BME280 transaction helper and P4 decision/action/verification/release flow authoritative. The actual hardware operation must be executed by firmware, not merely predicted by the Python bridge.
- Include at least: protocol version, device/board identifier, firmware build identifier if reliably available, request/run ID, baseline result, controlled NACK result, selected policy/action/reason if captured, recovery-action result, post-recovery chip ID, verification/release result, terminal status, and an explicit error code. Return only values actually measured or source-defined, with names and provenance clear.
- Add a watchdog/timeout or bounded loop behavior appropriate to the existing firmware design. No unbounded waits on serial input or I²C.
- Build using the user's existing STM32CubeIDE setup and exact required source/header files. Do not assume GitHub-side source inspection is a hardware build. Before any flash, explain the exact target, operation, and rollback/backup; request explicit user approval in the next chat before flashing. Preserve the user's existing working firmware and external backup.
- Do not commit generated IDE/startup/linker files or binaries unless a reviewed, reproducible need exists. Record source-to-binary identity if a hash can be generated reliably; otherwise mark it unresolved.

## 6. UI requirements

Reuse `demo/index.html` and existing design system. Do not replace the existing UI.

Add:
- **Mode switch:** Software Simulator / Physical Hardware / Compare.
- **Connection status:** disconnected, connecting, connected/identified, busy, timeout/error; show selected port and firmware protocol identity.
- **Allowed test selector:** only the safe cases accepted in Section 2.
- **Run Hardware Test** button with a confirmation step for the physical NACK/reinitialization test.
- **Software Result** and **Physical Result** panels, including provenance, run IDs, action/outcome, chip ID, verification/release status and errors.
- **Comparison** panel with field-by-field agreement and an explicit “partial/unmatched” result when scenario equivalence is not justified.
- **Raw serial response / trace disclosure** for debugging, but keep it bounded and escape text before inserting into the DOM.
- Clear text explaining that the browser triggers a pre-flashed, fixed firmware test; it does not upload arbitrary source code or flash the board.

No UI element may display stale hardware data as a current result. Clear or mark previous results when a new run begins. A disconnected board must show unavailable, never simulated success.

## 7. Test strategy and acceptance gates

Use layered acceptance; do not skip gates.

### Gate A — Host-only
- Preserve existing software UI and endpoints.
- Unit-test protocol parsing, allowlist, request IDs, malformed responses, timeouts, serial disconnection, and busy/concurrent-run handling with a fake transport.
- Run existing CTest and `python demo/test_ui_contracts.py` if the build artifacts/environment are available. Report honestly if not run.
- Confirm the server binds only to loopback for the hardware-enabled local mode.
- Confirm old software mode still behaves the same.

### Gate B — Firmware compile and protocol
- Build cleanly in the existing CubeIDE project.
- Verify only approved protocol commands are accepted and all responses are bounded.
- Keep source/build/download evidence distinct.

### Gate C — User-approved physical test
- Verify the board identity/serial handshake.
- Read baseline ID 0x60.
- Trigger only the controlled wrong-address NACK test.
- Require an observed NACK, an actual supported P4 decision/action, fresh ID 0x60, successful verification/release, and a response with matching request ID.
- Record failures honestly; do not loop/retry hardware tests automatically.

### Gate D — UI end-to-end
- Trigger a single test from the existing UI.
- Verify the response came from the connected board in that run and the ID is fresh.
- Compare against the corresponding software result and label all non-comparable fields.
- Disconnect/timeout negative test must show an error and must not display a false pass.

### Gate E — Documentation and reproducibility
- Update the demonstrator guide, hardware integration README, current state, roadmap, and top-level README as appropriate.
- Add a hardware protocol document and a test/evidence report template.
- Document port discovery, CubeIDE build/flash steps, launch commands, expected JSON/fields, troubleshooting, provenance, and rollback.
- Record actual commands run, test outcomes, commit SHA, changed files, open blockers, and next exact step.

## 8. Protected assets and scope

Do not modify or regenerate:
- `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`
- frozen K.10 400-execution results/raw data
- Gate A–E contracts and historical prior-art/evidence reports
- existing LD2 and BME280 screenshots/evidence records
- user's external firmware backup

Do not create branches; use `main` only. Before every write, re-fetch the current file and verify the branch/head. Never force-push. Keep the software runtime authoritative for the software comparison and the MCU firmware authoritative for the physical observation.

## 9. Required final deliverables

1. Existing UI extended with real hardware mode, not a replacement UI.
2. Local Python serial bridge and protocol tests.
3. Minimal firmware transport/test changes and source provenance.
4. Matched/partial comparison implementation with explicit evidence boundaries.
5. Updated guide, protocol, hardware report, current state, roadmap and README.
6. Exact host test results and, only after user approval, physical test results.
7. A final acceptance table marking each gate PASS / FAIL / BLOCKED with evidence and provenance.

**Do not mark this work complete just because code is committed.** End-to-end hardware connection is complete only when the existing UI triggers a real request, the connected MCU returns a matching response from a fresh physical run, the BME280 result is verified, and the software comparison accurately reports agreement or mismatch.
