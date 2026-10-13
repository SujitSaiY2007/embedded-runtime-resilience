# Chat Record — K.12 Integrated Virtual Embedded-System Demonstration & Final Software Audit

**Date:** 2026-10-13  
**Checkpoint:** K.12  
**Authorized branch:** `feature/k10-4-final-technical-conclusion-2026-10-13`  
**K.12 verdict:** INCOMPLETE / BLOCKED — remote implementation committed; execution gate remains open.

## 1. Startup continuity and refs

The K.12 prompt in `NEXT_CHAT_PROMPT.md` was read from the authorized branch. K.10.4 closure commit `09c17a413c7fb0b48c3c5da4642e24a402edd970` is an ancestor of the working feature branch. At startup, `exp` was `ab766b47ce7bae2791028cea22b7915f8debc41c` and `main` was `0bff0b32e24dccb1b94c20b6e305cb918a49ec6f`; both remained unchanged throughout this work.

Protected artifacts were fetched and verified against the five SHA values frozen in `NEXT_CHAT_PROMPT.md` after the source changes:

- `reference/src/ref_runtime.c` — `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`
- `reference/include/ref_runtime.h` — `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`
- `research/phase1_reference_implementation_design.md` — `b7fb120692756740bc969aa3412acaa89320c188`
- `research/phase2_k9_methodology_lock.md` — `bd75f2c2c21c3964ec15b338eea99b386eff7aec`
- `research/phase2_k9_2_p4_advantage_novelty_design.md` — `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d`

The GitHub connector cannot verify the original local checkout, local uncommitted files, or local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38`; local preservation remains unverified.

## 2. Source changes committed on the feature branch

- Added/used `peripheral_connected[VIRTUAL_MAX_PERIPHERALS]` and `virtual_system_set_peripheral_connected()` in the virtual adapter. A setting may be changed only before the first step; disconnected resources are rejected before runtime admission; connection settings contribute to the virtual digest.
- Extended `virtual_demo_cli` with `--disconnect I2C0|SPI0|UART0`, adapter error fields in JSON, and `DISCONNECTED` peripheral status.
- Added a C unit test asserting disconnected I2C0 admission is rejected before runtime mutation and that the resulting digest differs from the connected configuration.
- Hardened `demo/server.py` with portable executable paths, scenario/variant/peripheral validation, a 10-second subprocess timeout, JSON authority checks and explicit API errors.
- Updated `demo/index.html` with a three-resource virtual workbench, frozen research evidence panel, CF01 conflict warning, pending hardware handoff, live config forwarding, and error handling that avoids silently substituting static output after a failed live request.
- Updated `demo/test_ui_contracts.py` to find platform-specific CLI binaries and check the disconnection contracts.
- Replaced the K.7-oriented `demo/README.md` with K.12 build, run, scenario, troubleshooting and limitation instructions.
- Updated `CURRENT_HANDOFF.md`, `PROJECT_STATE.md`, `DECISION_LOG.md`, and `research/PART_II_CHAT_PLAN.md` with the K.12 implementation/execution boundary.

## 3. Frozen research evidence and CF01 disposition

The dashboard preserves the frozen result interpretation: bounded P4 advantages in CF04/CF07 and CF05; exact-event quarantine shared across P0–P4; no measured P4 advantage in CF02, CF09, CF11, CF12, CF13 and CF15; CF16 P2 one attempt vs P4 three; and `QMAX=16` / `EPMAX=1` capacity confounds. It makes no universal-superiority or legal patentability claim.

CF01 P2 attempt count remains unresolved. The K.10 results report contains a P2 result-cell value of att=3 while its explanation says one attempt; K.10.4 says att=1. The complete remote feature tree was not truncated and contains neither `reference/experiments/out/k10_runs.csv` nor `reference/experiments/out/k10_traces.csv`. No K.10 rerun occurred and neither frozen result report was edited. The original raw K.10 run and trace records are the only specific evidence needed to attempt reconciliation; until provided, CF01 attempt count is excluded from comparative claims. The separate CF16 comparison is retained.

## 4. Verification and explicit limitation

The GitHub connector supports remote source read/write but did not provide an executing native compiler, CMake/CTest, local HTTP server/browser or interactive browser test environment. Therefore all execution checks below are **BLOCKED / NOT RUN**, not PASS:

- `cmake -S reference -B reference/build`
- `cmake --build reference/build --config Debug`
- `ctest --test-dir reference/build --output-on-failure`
- `reference/build/virtual/virtual_demo_cli --verify` (use actual executable path on Windows)
- `python demo/test_ui_contracts.py`
- launch `python demo/server.py 8000`, then GET `/api/status` and `/api/step?scenario=S01&step=1&variant=4&disconnect=I2C0`
- browser tests for connect/disconnect, reset/step, error feedback, trace provenance, responsive layout and keyboard/accessibility

An execution follow-up must confirm the test digest constants in `demo/test_ui_contracts.py` still match the current virtual digest, since the digest now includes the virtual connection configuration. Tests and source audits must not invoke or edit the frozen K.10 400-execution matrix.

## 5. Hardware and scope boundary

The UI shows proposed NUCLEO-U575ZI-Q / STM32U575ZI mapping as a future specification only: I2C1 PB8/PB9 100 kHz; SPI1 PA5/PA6/PA7 1 MHz mode 0 8-bit MSB-first; PD14 CS; MSI 16 MHz SYSCLK without PLL; 1 MHz timer tick where feasible; 10 ms initial transfer timeout. UART/USART pins must be checked against the actual board revision. **No firmware flashing, physical fault injection, measurements or hardware validation was performed.**

## 6. Closure gate

K.12 is **INCOMPLETE / BLOCKED** pending (1) clean build/CTest, (2) live CLI/HTTP/browser demonstration with observed output, (3) local diff/working-tree and local-only commit verification in the original checkout, and (4) optional CF01 raw-data reconciliation if original records are recoverable. No merge to `exp`, no `main` synchronization, no K.10 rerun, no protected runtime edits, and no physical hardware work are authorized.
