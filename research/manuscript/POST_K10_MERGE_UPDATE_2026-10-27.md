# Post-merge manuscript synchronization — 27 October 2026

## Repository update

The final manuscript files were revised in the working conversation after K.10 evidence was merged. This note synchronizes the repository's manuscript navigation with that evidence merge.

- K.10 evidence PR: [#11](https://github.com/SujitSaiY2007/embedded-runtime-resilience/pull/11)
- Evidence merge commit: `41a24fa55326c89cb0a772f34d187b6226a255ed`
- Run-level data: [k10_runs.csv](../audit_runs/20261027_112620/k10_runs.csv)
- Execution traces: [k10_traces.csv](../audit_runs/20261027_112620/k10_traces.csv)
- Generated report: [k10_results.md](../audit_runs/20261027_112620/k10_results.md)

## Manuscript claims retained

- The corrected-branch K.10 rerun is distinct from the historical frozen 400-execution campaign.
- The author reports 400 harness-valid rows and five matching repetitions in each of 80 family/variant groups for the checked fields.
- This recorded validation has not been independently reproduced in this manuscript-generation environment.
- P4 outcomes are scenario-specific; the manuscript does not claim universal superiority.
- The controlled STM32L476RG/BME280 NACK/readback demonstration remains separate from the host campaign.
- Target-side timing, energy, stack use, complete RAM/Flash profiling, stuck-bus recovery, and a hash-linked flashed firmware binary are not claimed.

## Binary manuscript upload status

The revised Word and regenerated PDF were generated in the working conversation as:

- `Embedded_Runtime_Resilience_Manuscript_FINAL_2026-10-27.docx`
- `Embedded_Runtime_Resilience_Manuscript_FINAL_2026-10-27.pdf`

**They are not yet committed to this GitHub repository.** The author should upload both files to `research/manuscript/final/` using the local clone or GitHub web interface. After upload, verify both paths on `main` and update the release index if the stored filenames differ.

This text note does not represent or substitute for the binary files.
