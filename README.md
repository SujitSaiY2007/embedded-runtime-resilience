# Embedded Runtime Resilience

**Research:** Bounded, zero-heap, context-aware peripheral recovery with event quarantine for event-driven embedded systems.

**Project status:** Corrected K.10 evidence is committed to `main`. The revised manuscript files have been generated; their DOCX/PDF binaries still need to be committed by the author.

## Manuscript

**Approved title**

> Bounded, Zero-Heap, Context-Aware Peripheral Recovery with Event Quarantine for Event-Driven Embedded Systems: A Host Evaluation and a Controlled I²C Hardware Demonstration

- [Manuscript release index and artifact checklist](research/manuscript/README.md)
- [Evidence ledger](research/manuscript/EVIDENCE_LEDGER.md)
- [Reference audit](research/manuscript/REFERENCE_AUDIT.md)
- [Open technical and evidence issues](research/manuscript/OPEN_ISSUES.md)
- [Final novelty and contribution audit](research/closure/FINAL_NOVELTY_AND_CONTRIBUTION_AUDIT_2026-10-26.md)
- [Hardware closure report](research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md)
- [Final runtime correction and K.10 audit (27 Oct 2026)](research/closure/FINAL_RUNTIME_AND_K10_AUDIT_2026-10-27.md)

## Corrected K.10 evidence (on main)

The raw artifacts are now committed and available:

- [K.10 results report](research/audit_runs/20261027_112620/k10_results.md)
- [K.10 run-level CSV](research/audit_runs/20261027_112620/k10_runs.csv)
- [K.10 execution traces CSV](research/audit_runs/20261027_112620/k10_traces.csv)

These are the existing corrected-branch campaign artifacts merged in [PR #11](https://github.com/SujitSaiY2007/embedded-runtime-resilience/pull/11), merge commit `41a24fa55326c89cb0a772f34d187b6226a255ed`. The reported campaign covers 16 case families × five in-house variants × five repetitions = 400 executions. The author's validation reports 400 harness-valid rows and five matching repetitions in each of 80 family/variant groups for checked fields; independent replay is still pending.

The final editable Word manuscript and PDF must be committed under `research/manuscript/final/` before this repository can serve as their permanent download location. They were generated in the working conversation but are not yet in GitHub.

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

- Historical frozen host campaign: 16 case families × five in-house policy variants × five repetitions = 400 executions.
- Corrected-branch K.10 rerun: a separate 400-execution campaign; its raw CSVs and report are now public in the paths above.
- Physical demonstration: STM32 NUCLEO-L476RG with BME280 and controlled I²C address NACK/readback.
- Five additional control trials are a separate narrow NACK/readback procedure, not five repeated policy comparisons.
- The browser demonstrator exercises the virtual C runtime; live browser-to-physical-MCU integration is not established by the manuscript evidence.
- P0–P3 are in-house ablations, not published-algorithm implementations. Exact-event quarantine is shared across all five variants.
- The paper does not claim general P4 superiority. The author's reported CTest result was 8/8; it was not independently rerun in the manuscript-generation environment.
- The exact flashed firmware binary is not hash-linked to source. No MCU latency, energy, stack or complete resource profile is claimed.

## Preservation rules

1. Use `main` for current repository organization.
2. Keep the `exp` reference branch protected and unchanged.
3. Do not overwrite the frozen 400-run evidence or label regenerated data as original raw outputs.
4. Do not represent user-observed debugger screenshots as independently rerun experiments.
5. Keep historical prompts and superseded drafts in `archive/`; keep active source, build instructions and concise research navigation discoverable.
6. Check the current target journal's official author instructions before submission.
