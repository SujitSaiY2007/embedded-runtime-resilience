# K.12 — Integrated Virtual Embedded-System Demonstration & Final Software Audit

**Checkpoint verdict: INCOMPLETE / BLOCKED — remote source implementation committed; execution gate not yet satisfied.**

**Date:** 2026-10-13  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Authorized working branch:** `feature/k10-4-final-technical-conclusion-2026-10-13`  
**Initial K.12 remote HEAD:** `e67e1b00f44e30e8da70fbbd8c3fee8a1c964718`  
**K.10.4 closure ancestor:** `09c17a413c7fb0b48c3c5da4642e24a402edd970`  
**Canonical `exp` baseline:** `ab766b47ce7bae2791028cea22b7915f8debc41c`  
**Protected `main` baseline:** `0bff0b32e24dccb1b94c20b6e305cb918a49ec6f`

---

## 1. Executive outcome

K.12 has productized the existing HTML/JavaScript + Python standard-library bridge + bounded C virtual system + frozen C reference runtime into a more explicit professor-facing software demonstrator. The live path is wired to the same C CLI and reference runtime; the UI does not implement a second recovery algorithm. Virtual link availability is represented in the C adapter and included in the deterministic digest. A scenario event whose fixed virtual peripheral has been disconnected is rejected before event admission mutates reference-runtime state.

**K.12 is not approved and closed.** This session could inspect and write remote GitHub source but had no runnable local checkout/compiler/browser to execute CMake, CTest, the HTTP bridge, or a live browser flow. The remote-source edits and source-level contract checks are not substitutes for observed runtime output. Accordingly, those executions are marked NOT RUN / BLOCKED, and the required final audit gate is incomplete.

## 2. Remote repository and integrity startup audit

The authoritative prompt was read from `NEXT_CHAT_PROMPT.md` (initial blob `d23e353ebd804d4e0a1059cd1cb8adbe24a5d73c`). The prompt authorizes software-only K.12 and forbids changing Gates A–E, protected runtime, frozen K.10 empirical results, rerunning the 400-execution K.10 matrix, physical hardware activity, merge to `exp`, and synchronization of `main`.

At the K.12 baseline audit, the feature branch was `e67e1b00f44e30e8da70fbbd8c3fee8a1c964718`; K.10.4 closure commit `09c17a413c7fb0b48c3c5da4642e24a402edd970` was an ancestor. `exp` matched `ab766b47ce7bae2791028cea22b7915f8debc41c`; `main` matched `0bff0b32e24dccb1b94c20b6e305cb918a49ec6f`. Subsequent K.12 commits were made only to the authorized feature branch.

The five protected Git blob SHA values were checked against `NEXT_CHAT_PROMPT.md` and refetched remotely after implementation; all matched:

| Protected artifact | Required and observed blob SHA | Result |
|---|---|---|
| `reference/src/ref_runtime.c` | `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81` | PASS |
| `reference/include/ref_runtime.h` | `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198` | PASS |
| `research/phase1_reference_implementation_design.md` | `b7fb120692756740bc969aa3412acaa89320c188` | PASS |
| `research/phase2_k9_methodology_lock.md` | `bd75f2c2c21c3964ec15b338eea99b386eff7aec` | PASS |
| `research/phase2_k9_2_p4_advantage_novelty_design.md` | `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d` | PASS |

The original local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38` cannot be verified via remote GitHub inspection. Its state in the original local checkout remains unverified and must not be represented as preserved based on this report.

## 3. Implemented source changes

### Virtual C adapter and CLI

- `reference/virtual/include/virtual_system.h`: adds a fixed-size per-peripheral connection state and setter API.
- `reference/virtual/src/virtual_system.c`: initializes modeled peripheral links as connected, allows a connection change only before the first scenario step, rejects admission when the fixed scenario references a disconnected link, and includes connection state in the run digest.
- `reference/virtual/src/virtual_demo_cli.c`: accepts `--disconnect I2C0|SPI0|UART0`, reports adapter error state/message in JSON, and emits `DISCONNECTED` for the modeled resource. Unsupported names return an error.
- `reference/virtual/tests/test_virtual_system.c`: adds a contract test for disconnected-link rejection before runtime state mutation and verifies that the configured digest differs from the connected case.

These changes affect only the virtual/demo adapter and CLI. They do not change `ref_runtime.c`, `ref_runtime.h`, `policy_decide()`, `runtime_apply_policy()`, Gates A–E, or the frozen K.10 experiment files.

### Python bridge

`demo/server.py` now searches Windows and Unix executable candidate paths; validates supported scenarios, policy variants and peripheral IDs; passes link state to the C CLI; uses a bounded subprocess timeout; verifies the C JSON response; and returns explicit HTTP errors instead of serving static result JSON from an execution API route.

### Professor-facing UI and guide

`demo/index.html` adds:
- a three-resource virtual workbench for I2C0 (primary), SPI0 (secondary), and UART0 (diagnostic/control);
- connect/disconnect controls wired to the live C CLI, disabled when only exported offline data is available;
- a source-labelled summary of frozen K.10 findings and trade-offs;
- an explicit CF01 discrepancy warning;
- a planned STM32U575ZI / NUCLEO-U575ZI-Q mapping visibly labelled PENDING / NOT PERFORMED;
- error handling that does not silently present an old static timeline after a failed live request.

`demo/README.md` now documents prerequisites, build, launch, representative scenario walkthrough, CLI commands, limitations, and troubleshooting. `demo/test_ui_contracts.py` now discovers Windows/Unix CLI paths and has contracts for the disconnected-link CLI and expected source data.

**Configuration limit:** the workbench does not claim arbitrary electrical or pin-level wiring. Existing scenario event definitions continue to select their fixed virtual resources; a disconnect takes effect when a scenario step would admit an event through that resource. If a selected scenario does not reference the resource, its execution may continue.

## 4. Architecture and data flow

```text
Professor UI: demo/index.html
   | selects scenario, policy, modeled link availability, step
   v
Python standard-library HTTP bridge: demo/server.py
   | validates request; starts a fresh C CLI process per step/run
   v
virtual_demo_cli
   | parses scenario/policy/disconnect settings
   v
VirtualSystem adapter: reference/virtual/src/virtual_system.c
   | scenario, event admission, dependencies, deterministic faults
   v
Frozen C reference runtime: reference/src/ref_runtime.c
   | authoritative policy decision/application, state transitions, trace
   v
JSON response: outcome + slots + virtual peripheral state + runtime/wrapper traces
   v
UI rendering + separate frozen K.10 research evidence panel
```

The CLI reconstructs a new virtual scenario state for each request. The browser's step slider presents successive prefixes of that deterministic scenario; it does not persist a live C process in the Python server. Reset requests step zero, which constructs the initial state again.

### Virtual-to-target hardware mapping (planning only)

| Software model / proposed role | K.11 future validation mapping | Status |
|---|---|---|
| I2C0 primary modeled resource | Proposed I2C1 PB8/PB9 at 100 kHz | NOT PERFORMED |
| SPI0 secondary modeled resource | Proposed SPI1 PA5/PA6/PA7 at 1 MHz, mode 0, 8-bit MSB-first; PD14 chip select | NOT PERFORMED |
| UART0 diagnostic/control resource | Intended UART/USART diagnostics; actual pin/alternate-function mapping requires board-revision check | NOT PERFORMED |
| Timing plan | MSI 16 MHz SYSCLK without PLL; 1 MHz timer tick where feasible; initial 10 ms transfer timeout | NOT PERFORMED |
| MPU, electrical, recovery behavior | Target-specific physical verification and instrumentation | NOT PERFORMED |

These entries are proposed validation settings from K.11, not physical execution, measurements, or evidence of target-board behavior.

## 5. Frozen evidence and conclusion narrative

The UI reports the frozen findings separately from any currently selected virtual-demo run:

- Bounded P4 advantages were recorded in CF04 and CF07 for fail-closed ambiguous association and clean episode closure, and in CF05 for bounded termination under cascading recovery faults.
- Exact-event quarantine is shared across P0–P4 and is not a P4-exclusive contribution.
- The frozen report recorded no measured P4 advantage in CF02, CF09, CF11, CF12, CF13, and CF15.
- CF16 is a trade-off: P2 succeeds in one attempt while P4 requires three attempts in the reported case.
- `QMAX=16` and `EPMAX=1` are capacity confounds.
- Evidence is limited to the examined deterministic host/reference case set. No universal superiority, legal novelty, non-obviousness, inventive step, patentability, or physical MCU-performance claim is made.

### CF01 discrepancy

The frozen K.10 results report's CF01 P2 cell says `SUCCESS, att=3`, while its narrative says P2 succeeds in one attempt. K.10.4 records P2 as `SUCCESS (att=1)`. The complete remote Git tree was checked; the cited `reference/experiments/out/k10_runs.csv` and `reference/experiments/out/k10_traces.csv` are absent. No K.10 rerun was performed and neither frozen report was changed. **CF01 P2 attempt count remains unresolved and is excluded from comparative claims.**

Exact material needed to resolve this item: original K.10 raw run records and trace records corresponding to CF01, ideally the two cited CSVs from the generating checkout/artifact. Nothing else is needed from local history for the CF01 question.

## 6. Verification matrix

Because the GitHub connector does not execute CMake, native binaries or a browser, source review has not been counted as a test pass. The following exact procedures remain to execute in a normal clone after checkout of the final feature branch:

| Check | Exact command/procedure | Result here | Evidence required |
|---|---|---|---|
| Clean build | `cmake -S reference -B reference/build && cmake --build reference/build --config Debug` | BLOCKED / NOT RUN | Complete compiler/build output |
| Existing CTest suite | `ctest --test-dir reference/build --output-on-failure` | BLOCKED / NOT RUN | CTest summary including all tests |
| C virtual CLI scenarios | `reference/build/virtual/virtual_demo_cli --verify` (use actual `.exe` path on Windows) | BLOCKED / NOT RUN | Per-scenario outcome/digest output |
| C virtual unit tests | `reference/build/virtual/virtual_system_tests` (platform path as built) | BLOCKED / NOT RUN | Test process exit code/output |
| C baseline tests | `reference/build/virtual/virtual_baseline_tests` (platform path as built) | BLOCKED / NOT RUN | Test process exit code/output |
| CLI disconnected scenario | `reference/build/virtual/virtual_demo_cli --scenario S01 --step 1 --disconnect I2C0 --variant 4` | BLOCKED / NOT RUN | JSON shows adapter error, invalid dependency, empty admitted slots/runtime trace |
| CLI connected control | `reference/build/virtual/virtual_demo_cli --scenario S01 --step 1 --variant 4` | BLOCKED / NOT RUN | Connected case admits event; digest differs from disconnected case |
| Python UI contract suite | `python demo/test_ui_contracts.py` | BLOCKED / NOT RUN | Script output/exit code; verify stable-digest constants against actual fresh CLI outputs |
| HTTP bridge status | launch `python demo/server.py 8000`; GET `http://localhost:8000/api/status` | BLOCKED / NOT RUN | JSON shows `c_binary_found: true` |
| HTTP live scenario | GET `/api/step?scenario=S01&step=1&variant=4&disconnect=I2C0` | BLOCKED / NOT RUN | HTTP 200, JSON adapter error, no runtime admission mutation |
| UI connect/disconnect interaction | Browser: S01, live mode, disconnect I2C0, step once; reconnect/reset | BLOCKED / NOT RUN | Manual observation + console/network evidence |
| Responsive/accessibility review | Narrow viewport; keyboard, focus, labels, table overflow and status announcement inspection | BLOCKED / NOT RUN | Browser/manual checklist |
| Protected blobs | Re-fetch five paths and compare Git blob SHAs from K.12 prompt | PASS (remote) | Blob SHA report in this document |
| `exp` / `main` refs | GET each branch after final commit | PASS at final remote audit | Exact refs in chat record |
| Frozen K.10 matrix | No invocation permitted | NOT RUN (as required) | Review diff confirms no K.10 output edits/rerun |

**Additional issue to verify during local execution:** `demo/test_ui_contracts.py` contains digest constants copied from the prior known S01/S02/S05/S06/S08/S14 scenarios. Since the virtual digest now deliberately hashes link-configuration bits, those expected digest constants may change. Run the suite and update only demo-contract expectations based on two repeatable observed executions; never modify the frozen K.10 evidence.

## 7. Current remote deliverable/state table

| Path | Purpose | Current state |
|---|---|---|
| `demo/index.html` | Workbench, evidence, hardware handoff and trace UI | Updated in feature branch |
| `demo/server.py` | Validated bounded CLI bridge and virtual link configuration | Updated in feature branch |
| `reference/virtual/include/virtual_system.h` | Connection setting API/storage | Updated in feature branch |
| `reference/virtual/src/virtual_system.c` | Virtual connection semantics and digest | Updated in feature branch |
| `reference/virtual/src/virtual_demo_cli.c` | CLI configuration and JSON error/status | Updated in feature branch |
| `reference/virtual/tests/test_virtual_system.c` | Disconnected-link unit contract | Updated in feature branch; not executed here |
| `demo/test_ui_contracts.py` | Cross-platform C CLI/UI contracts | Updated in feature branch; not executed here |
| `demo/README.md` | Professor guide/build/troubleshooting | Updated in feature branch |
| `research/phase2_k12_professor_facing_software_demo_and_final_audit.md` | This K.12 audit and verification matrix | Current report |
| `research/chat_records/chat_k12_record.md` | Exact checkpoint record | Required companion record |
| `CURRENT_HANDOFF.md` | Active handoff status | Updated |
| `PROJECT_STATE.md` | Project state and K.12 gate | Updated |
| `DECISION_LOG.md` | Frozen boundaries/K.12 decision record | Updated |
| `research/PART_II_CHAT_PLAN.md` | Active roadmap and exit gate | Updated |

## 8. Final audit checklist

- [x] Read K.12 prompt and continuity/evidence documents remotely.
- [x] Confirm feature branch descends from K.10.4 closure.
- [x] Confirm K.11 deliverables exist and K.11 is approved/closed.
- [x] Confirm five protected Git blob SHAs before/after implementation.
- [x] Confirm `exp` and `main` preserved at the audited refs.
- [x] Keep frozen K.10 findings and the C reference runtime unchanged.
- [x] Investigate CF01 from the remote tree; record unresolved due to missing raw CSV files.
- [x] Add live-source virtual-link controls, config validation, evidence panel, hardware handoff, and demo instructions.
- [ ] Run clean build and CTest with observed output.
- [ ] Run CLI/bridge integration tests with observed output.
- [ ] Test real browser connection interaction, trace authority, responsive layout and accessibility.
- [ ] Verify digest assertions in `demo/test_ui_contracts.py` against the updated configuration-hashed digest.
- [ ] Verify final branch refs and complete final diff in a normal local checkout.
- [ ] Verify original local-only commit in the original local checkout.

## 9. Closure decision and exact remaining blockers

**K.12 verdict: INCOMPLETE / BLOCKED.** Remote-source implementation is committed, and protected blob/ref boundaries were preserved in the remote audit. This is not a test-passed or demo-validated release because no native build, CTest, live HTTP request, or browser execution has been observed here.

To finish without requesting an entire ZIP, the minimum missing evidence is:

1. A runnable clone/environment with a C11 compiler, CMake, Python 3, and a browser to execute the exact matrix above, inspect the complete diff, and verify the updated digest assertions.
2. The original K.10 raw run and trace CSVs if the CF01 P2 count is to be reconciled. If those records cannot be recovered, leave CF01 unresolved permanently in the published claims.
3. Access to the original local checkout only to verify local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38` and any uncommitted files; remote GitHub data cannot establish that local state.

Do not merge this feature branch to `exp`, move `main`, rerun K.10, modify protected runtime files, flash firmware, perform physical fault injection, or claim hardware validation as part of this blocked checkpoint.
