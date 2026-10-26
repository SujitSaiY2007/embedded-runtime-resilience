# Embedded Runtime Resilience

**Research project:** bounded, zero-heap, context-aware peripheral recovery for event-driven embedded systems.

**Current phase:** Plan 2.0 — bounded hardware demonstration recorded; manuscript drafting and evidence audit are next.

[![Plan](https://img.shields.io/badge/plan-2.0-315a9b)](Plan2.0/README.md)
[![Software](https://img.shields.io/badge/software-reference%20demo%20available-247a55)](#current-status)
[![Hardware](https://img.shields.io/badge/hardware-controlled%20recovery%20observed-247a55)](Plan2.0/results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md)
[![Branch policy](https://img.shields.io/badge/work-main%20only-6f42c1)](Plan2.0/CHAT_PROTOCOL.md)

## Current status — 25 October 2026

The repository contains the protected C reference runtime, frozen deterministic host/reference campaign (**16 case families × 5 policy variants × 5 repetitions = 400 executions**), virtual embedded system, Python bridge, browser demonstrator, and a user-observed STM32L476RG/BME280 controlled-NACK recovery run.

The latest five-policy diagnostic run reached `progress_stage=900`, `finished=1`, and `overall_code=1`. All five baseline error slots were zero and the controlled wrong-address read returned the source-defined `E_NACK=-1`. P1 and P4 reached `R_PASS`; their post-recovery reads succeeded and returned BME280 ID `0x60`. P0, P2 and P3 reached `R_TERMINAL`. This is one bounded transaction-level hardware run, not physically stuck-bus recovery, repeatability evidence, MCU performance measurement, or universal P4 superiority. The full 80-element matrix array has not been independently captured in a complete readable export; one user statement about the last entry conflicts with a screenshot showing `matrix_status[79]=1`. See the [detailed hardware evidence report](Plan2.0/results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md).

**Current user-authorized next implementation: live UI-to-hardware bridge (Chat 12).** Use the [Chat 12 implementation prompt](Plan2.0/prompts/CHAT_12_LIVE_UI_TO_HARDWARE_BRIDGE_PROMPT_2026-10-26.md) to extend the existing UI and Python bridge with a loopback-only serial path to the pre-flashed NUCLEO-L476RG, restricted to a baseline BME280 ID read and the controlled 0x77 NACK → P4 recovery → fresh ID verification case. The UI must compare the physical result with a corresponding software result and label any non-equivalence. The browser must not upload arbitrary C source or silently flash firmware. Preserve the frozen 400-run corpus and protected runtime. Manuscript drafting remains the subsequent priority after the bounded integration audit.

## Start here

| Need | Document |
|---|---|
| Plan 2.0 overview and rules | [Plan2.0/README.md](Plan2.0/README.md) |
| Current phase and evidence boundaries | [Plan2.0/CURRENT_STATE.md](Plan2.0/CURRENT_STATE.md) |
| Multi-chat roadmap | [Plan2.0/EXECUTION_ROADMAP.md](Plan2.0/EXECUTION_ROADMAP.md) |
| Reference audit requirements | [Plan2.0/REFERENCE_OVERHAUL.md](Plan2.0/REFERENCE_OVERHAUL.md) |
| Physical demonstration plan | [Plan2.0/HARDWARE_DEMONSTRATION.md](Plan2.0/HARDWARE_DEMONSTRATION.md) |
| Rules for each chat and handoff | [Plan2.0/CHAT_PROTOCOL.md](Plan2.0/CHAT_PROTOCOL.md) |
| Hardware compatibility audit | [Chat 05 audit](Plan2.0/hardware/CHAT_05_HARDWARE_COMPATIBILITY_AUDIT.md) |
| Chat 05.2 original zero-budget bring-up prompt | [Chat 05.2 prompt](Plan2.0/prompts/CHAT_05_2_ZERO_BUDGET_HARDWARE_BRINGUP_PROMPT.md) |
| Current status and handoff | [Chat 05.2 handoff](Plan2.0/handoffs/CHAT_05_2_HANDOFF.md) |
| Latest hardware continuation handoff | [Chat 05.3 handoff](Plan2.0/handoffs/CHAT_05_3_HANDOFF.md) |
| Next continuation — ST-LINK diagnostics | [Chat 05.3 prompt](Plan2.0/prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md) |
| Historical documentation snapshot | [Archive index](archive/README.md) |

## Latest physical-demo milestone (24 October 2026)\n\nThe user-provided CubeIDE screenshots show a clean local build (0 errors, 0 warnings), successful download verification, and debugger execution through a software-injected PA5 configuration fault and register-checked recovery. The local test observed event=1, fault=1, recovery=1, state=RECOVERED, GPIO mode=output, and output latch=high. See the [experiment record](Plan2.0/results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md). The local generated workspace project has not yet been reconciled as canonical version-controlled firmware; no sensor was wired/read and no MCU timing/stack/energy measurements were made.\n\n## Existing software demonstrator

The current software flow is:

```text
Browser UI
  → Python HTTP bridge
  → C virtual-system adapter and scenario runner
  → existing C reference runtime
  → runtime outcome, digest and trace records
  → UI state and correlated trace display
```

The C reference runtime remains authoritative for software recovery decisions.

### Run locally

Prerequisites: C11 compiler, CMake 3.16+, Python 3, and a modern browser.

```powershell
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
ctest --test-dir reference/build -C Debug --output-on-failure
python demo/test_ui_contracts.py
python demo/server.py 8000
```

Open http://localhost:8000/ while the server is running. See [Demo guide](docs/DEMONSTRATOR_GUIDE.md).

## Research evidence and limitations

- The 400-execution campaign is deterministic **host/reference-model** evidence, not MCU measurements.
- Findings support bounded advantages for P4 in selected cases, with trade-offs and no universal-superiority claim.
- Exact-event quarantine is shared across P0–P4; it is not a P4-exclusive feature.
- Resource caps and tested scenarios constrain interpretation.
- Existing frozen evidence and research records must not be rewritten to make a result appear stronger.
- Local test and browser success previously reported by the user is not the same as independently reproduced CI evidence.
- The project does not claim a legal determination of novelty, non-obviousness, or patentability.

## Repository layout

```text
.
├── README.md
├── Plan2.0/             # active reference/hardware multi-chat execution plan
├── archive/             # historical non-code snapshot; originals retained for safety
├── docs/                # curated project, architecture and demo documentation
├── demo/                # browser UI, Python bridge and UI contract tests
├── reference/           # C runtime, virtual system, tests and host experiments
└── research/            # frozen methods, results, conclusions and provenance
```

## Preservation and integrity rules

1. Work only on `main` for Plan 2.0.
2. Preserve the C reference runtime, test suite, Gate A–E contracts, frozen K.10 results, prior-art reviews, and historical records unless a separate, explicit research-change decision is approved.
3. The `archive/` snapshot is additive; the original paths are retained during initialization to avoid broken links and accidental loss. Do not treat archive copies as updated canonical state.
4. Do not claim a baseline was taken from a publication unless the exact relationship is verified.
5. Keep host-model evidence and physical MCU measurements separate in every report, figure, table, and presentation.
6. Each Plan 2.0 chat must record its commit, files changed, checks actually run, provenance, open questions, and the exact next-chat task.

## Citation and academic use

Use verified primary publication records for the literature overhaul. The repository itself is not a substitute for citing the original research. Before external publication, re-check all metadata, the source-to-design traceability, experimental artifacts, and institutional authorship requirements.


## Chat 06 source-preservation checkpoint — 24 October 2026

The three source files supplied after the successful local GPIO experiment are now preserved as plain C under [Plan 2.0 firmware source](Plan2.0/firmware/ld2_gpio_recovery/README.md): `main.c`, `err_runtime.c`, and `err_runtime.h`. This is a source record, not a complete CubeIDE project or an independently reproduced build. The user's external backup remains separate. The next task is to inspect the local project configuration and establish a safe reproducibility procedure. No generated startup/linker files, IDE metadata, binaries, sensor code, or protected reference-runtime files were added or changed.


## Latest hardware milestone — 25 October 2026

The user-provided STM32CubeIDE Expressions screenshot shows a successful BME280 chip-ID read on the NUCLEO-L476RG: `sensor_found=1`, I²C address `0x76`, chip ID `0x60`, `sensor_type=1`, `sensor_error=0`. The user-pasted ST-LINK log reports “Download verified successfully.” This verifies a baseline I²C register read, not full temperature/pressure/humidity sensing or fault recovery. See the [Chat 07 evidence report](Plan2.0/results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md).

**Next:** [Chat 07.1 — BME280 baseline and recovery prompt](Plan2.0/prompts/CHAT_07_1_BME280_BASELINE_AND_RECOVERY_PROMPT_2026-10-25.md). Preserve the successful LD2 experiment and all protected research evidence; next acceptance criterion is a fresh successful sensor transaction after a controlled, safe recovery test.


## Hardware milestone — Chat 07.1 (25 October 2026)

User-provided STM32CubeIDE evidence confirms the controlled BME280 address-NACK/reinitialization test reached `test_state=3 (RECOVERY_PASSED)`: baseline read succeeded, the test observed `fault_result=-1`, I²C reinitialization reported `recovery_error=0`, and a fresh post-recovery read returned chip ID `0x60`. The user reported a successful build with 0 errors and 0 warnings.

This is evidence for a controlled address-NACK followed by I²C peripheral reinitialization and a fresh successful sensor read. It does not demonstrate recovery from physically stuck SDA/SCL, all error classes, or a decision made by the protected reference runtime. Semihosting output was not visible; debugger Expressions values were used. The repository tools did not independently build or run the hardware.

- [Chat 07.1 detailed result](Plan2.0/results/CHAT_07_1_BME280_CONTROLLED_NACK_RECOVERY_2026-10-25.md)
- [Chat 08 next-chat prompt](Plan2.0/prompts/CHAT_08_RUNTIME_HARDWARE_INTEGRATION_PROMPT_2026-10-25.md)

**Next:** Chat 08 integrates the actual runtime decision/action path with the physical sensor in a staged, safe, user-approved workflow.


## Phase 4–5 conclusion — 26 October 2026

The prior-art/novelty assessment and software-to-hardware demonstration audit are documented without changing the frozen runtime or experiment corpus:

- [Phase 4 — Prior-Art and Novelty Conclusion](research/closure/PHASE4_PRIOR_ART_NOVELTY_CONCLUSION_2026-10-26.md): selected, attributable P4 advantages are supported by the frozen host campaign; universal superiority, definitive novelty, and patentability are not established.
- [Final Novelty and Meaningful Contribution Audit](research/closure/FINAL_NOVELTY_AND_CONTRIBUTION_AUDIT_2026-10-26.md): final evidence-bounded assessment of contributions, prior-art overlap, claim limits, and the current novelty status.
- [Phase 5 — Software-to-Hardware Demonstration and UI Integration Conclusion](research/closure/PHASE5_SOFTWARE_HARDWARE_UI_CONCLUSION_2026-10-26.md): the browser demonstrator is live against the virtual C runtime, and a separate physical BME280 NACK/recovery run is documented. A live browser-to-physical-MCU command/trace channel is not demonstrated, so the two paths must be presented separately.

**Current defensible project conclusion:** reproducible comparative software evidence plus bounded physical proof-of-concept evidence; full real-time UI-to-MCU integration and formal novelty/patentability remain unestablished. Frozen K.10 results, runtime code, and hardware evidence were not rewritten or regenerated.

## Next implementation — Chat 12: Live UI-to-hardware bridge

The next chat is scoped and authorized in the [Chat 12 prompt](Plan2.0/prompts/CHAT_12_LIVE_UI_TO_HARDWARE_BRIDGE_PROMPT_2026-10-26.md) and [execution roadmap](Plan2.0/EXECUTION_ROADMAP.md). It must reuse the existing `demo/index.html` and `demo/server.py`, keep software simulation working, and add a real USB serial request/response path to the already-flashed NUCLEO-L476RG firmware. The UI will trigger only the documented safe hardware cases and display physical evidence beside the C reference-runtime result. It must not present stale/canned output as a live result, or claim full UI-to-MCU integration until the end-to-end acceptance gates pass.
