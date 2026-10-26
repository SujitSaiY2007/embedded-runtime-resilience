# Embedded Runtime Resilience

**Research:** Bounded, zero-heap, context-aware peripheral recovery with event quarantine for event-driven embedded systems.

**Project status:** Manuscript package prepared; source code and evidence archive preserved. The frozen host campaign and hardware records are not being rewritten.

## Manuscript

**Approved title**

> Bounded, Zero-Heap, Context-Aware Peripheral Recovery with Event Quarantine for Event-Driven Embedded Systems: A Host Evaluation and a Controlled I²C Hardware Demonstration

- [Manuscript release index and artifact checklist](research/manuscript/README.md)
- [Evidence ledger](research/manuscript/EVIDENCE_LEDGER.md)
- [Reference audit](research/manuscript/REFERENCE_AUDIT.md)
- [Open technical and evidence issues](research/manuscript/OPEN_ISSUES.md)
- [Final novelty and contribution audit](research/closure/FINAL_NOVELTY_AND_CONTRIBUTION_AUDIT_2026-10-26.md)
- [Hardware closure report](research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md)

The editable Word manuscript and its PDF are the author-supplied release artifacts. They must be committed under `research/manuscript/final/` before this repository can serve as their permanent download location. The binary files were not included in the text-only GitHub updates made for this cleanup.

## Run the software

Requirements: a C11 compiler, CMake 3.16+, Python 3, and a modern browser.

```powershell
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
ctest --test-dir reference/build -C Debug --output-on-failure
python demo/test_ui_contracts.py
python demo/server.py 8000
```

Then open http://localhost:8000/. See the [demonstrator guide](docs/DEMONSTRATOR_GUIDE.md).

## Repository map

```text
.
├── README.md                 # concise project landing page
├── reference/                # C runtime, virtual system, tests and host experiments
├── demo/                     # browser UI, Python bridge and UI-contract tests
├── docs/                     # curated architecture and usage documentation
├── research/                 # manuscript, evidence, audits and results
├── Plan2.0/                  # hardware records and execution plans
└── archive/                  # superseded drafts and historical documentation
```

## Evidence boundaries

- Host evaluation: 16 case families × 5 in-house policy variants × 5 repetitions = 400 frozen executions.
- Physical demonstration: one five-policy comparison on an STM32 NUCLEO-L476RG with a BME280 and a controlled address NACK.
- Five additional control trials are a separate narrow NACK/readback procedure, not five repeated policy comparisons.
- The browser demonstrator exercises the virtual C runtime; live browser-to-physical-MCU integration is not established by the manuscript evidence.
- P0–P3 are in-house ablations, not published-algorithm implementations. Exact-event quarantine is shared by all five variants.
- Some frozen differences are affected by a known runtime defect; the paper does not claim general P4 superiority.
- The exact flashed firmware binary is not hash-linked to source. No MCU latency, energy, stack or complete resource profile is claimed.

## Preservation rules

1. Use `main` for current repository organization.
2. Keep the `exp` reference branch protected and unchanged.
3. Do not overwrite the frozen 400-run evidence or label regenerated data as original raw outputs.
4. Do not represent user-observed debugger screenshots as independently rerun experiments.
5. Keep historical prompts and superseded drafts in `archive/`; keep active source, build instructions and concise research navigation discoverable.
6. Check the current target journal's official author instructions before submission.
