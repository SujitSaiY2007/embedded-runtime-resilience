# Manuscript release index

**Status:** The revised manuscript files have been generated in the working conversation. The corrected K.10 evidence is now committed to the public `main` branch; the Word/PDF binaries still need to be uploaded by the author.

## Approved title

Bounded, Zero-Heap, Context-Aware Peripheral Recovery with Event Quarantine for Event-Driven Embedded Systems: A Host Evaluation and a Controlled I²C Hardware Demonstration

## Final manuscript files

Use the final files provided in the ChatGPT conversation:

- `Embedded_Runtime_Resilience_Manuscript_FINAL_2026-10-27.docx`
- `Embedded_Runtime_Resilience_Manuscript_FINAL_2026-10-27.pdf`

Upload both to this folder (or use the canonical repository names `Embedded_Runtime_Resilience_Manuscript.docx` and `Embedded_Runtime_Resilience_Manuscript.pdf`) using GitHub's web interface or the local Git clone. The final manuscript updates the data-availability statement to point to the now-committed K.10 evidence. Do not claim the binaries are hosted in this repository until the upload is verified.

## K.10 evidence — committed on main

The corrected-branch campaign artifacts are now available directly in the repository:

- [K.10 run-level results CSV](../audit_runs/20261027_112620/k10_runs.csv)
- [K.10 execution trace CSV](../audit_runs/20261027_112620/k10_traces.csv)
- [K.10 results report](../audit_runs/20261027_112620/k10_results.md)
- [Final runtime correction and K.10 audit](../closure/FINAL_RUNTIME_AND_K10_AUDIT_2026-10-27.md)

These are the existing campaign artifacts, not regenerated replacements. The reported campaign contains 400 executions (16 case families × five in-house variants × five repetitions), with 400 rows marked harness-valid and five matching repetitions in each of 80 family/variant groups for the fields checked by the author's validation script. These checks are not an independent reproduction or statistical generalization.

## Supporting research records

- [Evidence ledger](EVIDENCE_LEDGER.md)
- [Manuscript-ready results update (27 Oct 2026)](RESULTS_UPDATE_2026-10-27.md)
- [Manuscript revision log and artifact provenance (27 Oct 2026)](MANUSCRIPT_REVISION_LOG_2026-10-27.md)
- [Reference audit](REFERENCE_AUDIT.md)
- [Technical and evidence issue register](OPEN_ISSUES.md)
- [Final novelty and contribution audit](../../research/closure/FINAL_NOVELTY_AND_CONTRIBUTION_AUDIT_2026-10-26.md)
- [Hardware closure report](../../research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md)

## Integrity statement

The manuscript separates the frozen 400-execution host campaign from the corrected-branch 400-execution K.10 rerun, the physical NUCLEO-L476RG/BME280 demonstration, and the software-only UI demonstrator. It does not claim universal P4 superiority, stuck-bus recovery, MCU performance measurements, or a verified identity of the exact flashed binary. The host campaign and hardware demonstration are separate evidence paths.

The raw K.10 run CSV, trace CSV, and report were merged into `main` in PR #11 (merge commit `41a24fa55326c89cb0a772f34d187b6226a255ed`). The author-reported Windows CTest result was 8/8; it was not independently rerun in the manuscript-generation environment. The DOCX/PDF binaries are not yet committed here.
