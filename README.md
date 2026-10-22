# Embedded Runtime Resilience

**Research project:** bounded, zero-heap, context-aware peripheral recovery for event-driven embedded systems.

**Current phase:** Plan 2.0 — reference-quality overhaul and physical hardware demonstration planning.

[![Plan](https://img.shields.io/badge/plan-2.0-315a9b)](Plan2.0/README.md)
[![Software](https://img.shields.io/badge/software-reference%20demo%20available-247a55)](#current-status)
[![Hardware](https://img.shields.io/badge/hardware-validation%20pending-c88719)](Plan2.0/HARDWARE_DEMONSTRATION.md)
[![Branch policy](https://img.shields.io/badge/work- main%20only-6f42c1)](Plan2.0/CHAT_PROTOCOL.md)

## Current status — 22 October 2026

The C reference runtime, deterministic host experiments, virtual embedded system, Python bridge, and browser demonstrator are existing project assets. The frozen host/reference campaign contains **16 case families × 5 policy variants × 5 repetitions = 400 executions**.

The next phase is active planning, not completed validation:
- **Reference overhaul:** the preliminary bibliography (approximately 43 entries) still requires entry-by-entry metadata, venue, relevance, and influence verification.
- **Research traceability:** every claimed relationship between publications, baselines, design choices, and the proposed contribution must be explicitly evidenced.
- **Physical hardware:** Chat 05.2 is paused at ST-LINK/GDB initialization. Board-only USB detection, ST-LINK firmware update, and a generated CubeIDE empty-project build are user-verified; MCU connection, flashing, execution, sensor reads, recovery and MCU-specific measurements remain unverified. See [current hardware state](Plan2.0/CURRENT_STATE.md).
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

## Existing software demonstrator

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
