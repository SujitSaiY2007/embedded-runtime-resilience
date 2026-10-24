# Embedded Runtime Resilience

**Research project:** bounded, zero-heap, context-aware peripheral recovery for event-driven embedded systems.

**Current phase:** Plan 2.0 — reference-quality overhaul and physical hardware demonstration planning.

[![Plan](https://img.shields.io/badge/plan-2.0-315a9b)](Plan2.0/README.md)
[![Software](https://img.shields.io/badge/software-reference%20demo%20available-247a55)](#current-status)
[![Hardware](https://img.shields.io/badge/hardware-validation%20pending-c88719)](Plan2.0/HARDWARE_DEMONSTRATION.md)
[![Branch policy](https://img.shields.io/badge/work-main%20only-6f42c1)](Plan2.0/CHAT_PROTOCOL.md)

## Current status — 22 October 2026

The C reference runtime, deterministic host experiments, virtual embedded system, Python bridge, and browser demonstrator are existing project assets. The frozen host/reference campaign contains **16 case families × 5 policy variants × 5 repetitions = 400 executions**.

The next phase is active planning, not completed validation:
- **Reference overhaul:** the preliminary bibliography (approximately 43 entries) still requires entry-by-entry metadata, venue, relevance, and influence verification.
- **Research traceability:** every claimed relationship between publications, baselines, design choices, and the proposed contribution must be explicitly evidenced.
- **Physical hardware:** Chat 05.3 now has user-supplied evidence of a successful local CubeIDE firmware download/debug session and a narrow software-injected GPIO recovery experiment on LD2/PA5 (all eight expected debugger values observed). This is not physical peripheral-damage recovery. Sensor reads, repeatability, MCU performance measurements and target-equivalence questions remain open. See [current hardware state](Plan2.0/CURRENT_STATE.md) and the [GPIO experiment report](Plan2.0/results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md).
- **Branch policy:** all Plan 2.0 work is performed **only on `main`**. Do not create or write to another branch.

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
