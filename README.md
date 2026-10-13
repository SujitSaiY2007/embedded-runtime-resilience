# Embedded Runtime Resilience
### Research case study · Deterministic embedded recovery · Live software demonstrator

[![Research status](https://img.shields.io/badge/research-software%20phase%20complete-247a55)](#project-status)
[![Runtime](https://img.shields.io/badge/runtime-C11-blue)](reference/)
[![UI](https://img.shields.io/badge/demo-HTML%20%2B%20Python-orange)](demo/)
[![Hardware](https://img.shields.io/badge/hardware-future%20work-lightgrey)](docs/PROJECT_OVERVIEW.md)

**Embedded Runtime Resilience** investigates a bounded, zero-heap, context-aware peripheral-recovery policy for event-driven MCU firmware, with event quarantine and recovery-history-aware decisions. The repository combines a protected C reference runtime, deterministic host experiments, a virtual embedded-system adapter, a browser UI, and an auditable research record.

> **Project state (13 October 2026):** The software research and professor-facing demonstrator are complete for the current scope. The live UI is intended to exercise the same C reference runtime used by the project. Physical MCU implementation, fault injection, and hardware measurements are future work—not completed results.

## Start here

| If you want to… | Go to |
|---|---|
| Understand the project, contribution, evidence, limits, and roadmap | [Project overview](docs/PROJECT_OVERVIEW.md) |
| Run the live software demonstrator | [Demo setup and operating guide](docs/DEMONSTRATOR_GUIDE.md) |
| Understand the source tree and runtime data flow | [Architecture and repository map](docs/ARCHITECTURE_AND_REPOSITORY_MAP.md) |
| Read the final evidence-bounded conclusion | [K.10.4 research conclusion](research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md) |
| Review the matched experiments | [K.10 results](research/phase2_k10_p4_advantage_novelty_results.md) |
| Review final software synthesis and hardware handoff | [K.11 synthesis](research/phase2_k11_final_software_synthesis_and_hardware_handoff.md) |
| Review the final software demo audit | [K.12 audit](research/phase2_k12_professor_facing_software_demo_and_final_audit.md) |
| Understand historical decisions and checkpoints | [Research archive index](research/README.md) · [Decision log](DECISION_LOG.md) |

## Project status

- **Research conclusion:** finalized within the tested host/reference-model scope.
- **K.12 software demonstrator:** user-reported local build/tests and browser run succeeded; remote repository integration is complete. These local executions were not independently reproduced by CI.
- **Main branch:** contains the approved software/research deliverables and current project-navigation documents.
- **`exp` branch:** retained unchanged as the canonical frozen research baseline.
- **Physical hardware:** not implemented or measured; documented as future work.
- **CF01:** the reported qualitative outcomes are retained; its conflicting P2 attempt count is omitted from comparative claims. Frozen historical records are preserved.

## Research question

Can a compact deterministic recovery policy use peripheral-fault context and short recovery history to select a bounded action, isolate the fault-associated event, preserve unrelated valid queued work, and terminate within explicit resource limits?

## What this repository demonstrates

The interactive software path is:

```text
Browser UI
  → Python HTTP bridge
  → C virtual-system adapter and scenario runner
  → existing C reference runtime
  → runtime outcome, digest and trace records
  → UI state and correlated trace display
```

The UI is a control/presentation layer, not a second recovery implementation. The C reference runtime remains authoritative for recovery decisions.

## Evidence-bounded findings

The frozen K.10 campaign covers **16 case families × 5 policy variants × 5 repetitions = 400 executions** in a deterministic host/reference model. The reports describe bounded P4 advantages in selected case families, important no-difference cases, and trade-offs—including a lower-attempt P2 result in CF16. Exact-event quarantine is shared across P0–P4 and is not a P4-exclusive capability. Resource caps such as QMAX=16 and EPMAX=1 constrain interpretation.

These results do **not** establish universal superiority, physical MCU performance, statistical generalization, legal novelty, non-obviousness, or patentability.

## Quick start

Prerequisites: C11 compiler, CMake 3.16+, Python 3, and a modern browser. No API keys or paid cloud service are required.

From the repository root:

```powershell
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
ctest --test-dir reference/build -C Debug --output-on-failure
python demo/test_ui_contracts.py
python demo/server.py 8000
```

Open [http://localhost:8000/](http://localhost:8000/) while the server is running. See the [full demo guide](docs/DEMONSTRATOR_GUIDE.md) for platform notes and the acceptance checklist.

## Repository map

```text
.
├── README.md                         # public-facing project entry point
├── docs/                             # curated project and demo documentation
├── demo/                             # browser UI, Python bridge, UI contract tests
├── reference/                        # authoritative C runtime and virtual system
└── research/                         # frozen methods, results, conclusions and history
    └── chat_records/                 # checkpoint provenance; retained as history
```

The historical root continuity files remain for auditability and ongoing maintenance. The curated docs linked above are the preferred entry points for readers and evaluators.

## Reproducibility and integrity

- The C reference runtime is the software authority for decisions and trace records.
- The K.10 evidence is frozen; do not regenerate the matrix to repair a documentation inconsistency.
- Historical reports remain intact for provenance; final presentation avoids unsupported CF01 attempt-count comparisons.
- Hardware planning is explicitly labeled as proposed, not performed.
- The `main` branch contains the finalized presentation layer; `exp` remains unchanged.

## Citation and academic use

This repository is a research case study and software demonstration. Cite the repository commit or release used in any report. Before external publication, re-check references, experimental artifacts, and institutional authorship requirements. The repository does not claim a legal patentability determination.
