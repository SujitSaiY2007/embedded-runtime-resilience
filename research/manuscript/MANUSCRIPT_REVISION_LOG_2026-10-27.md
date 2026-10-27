# Manuscript revision log — 27 October 2026

## Updated manuscript artifact

A revised manuscript has been generated in the ChatGPT work session as:
- `Embedded_Runtime_Resilience_Manuscript.docx`
- `Embedded_Runtime_Resilience_Manuscript.pdf`

The DOCX was updated from the author-provided revised manuscript; the PDF was regenerated with LibreOffice. The PDF is 17 A4 pages. Text extraction and visual spot checks were performed on pages 1, 10 and 17. Figures and tables were retained. A final journal-template check remains necessary before submission.

## Sections updated

- Abstract: distinguishes the historical 400-run campaign from the separate corrected-branch 400-run rerun and summarizes scoped CF04–CF07 findings.
- Introduction scope note: clarifies in-house baselines, shared quarantine, and corrected-branch rerun boundaries.
- Methods / host evaluation: records the 27 October run design, author-reported validation, and that raw run-level files were not available to the manuscript-generation environment.
- Reproducibility: records the author-reported 8/8 CTest result and rerun validation, without representing them as independently rerun here.
- Results: describes CF04–CF07 outcomes from the reported rerun and avoids general-superiority claims.
- Discussion and limitations: distinguishes deterministic repetition consistency from statistical generalization, identifies missing raw CSV/trace artifacts, and preserves hardware-evidence boundaries.
- Conclusion and future work: adds the corrected-branch rerun and identifies raw-artifact publication and independent replay as next actions.
- Data/code availability: points to the dated audit and states that raw rerun CSV/trace files are not yet committed.
- Evidence tables: updates the host-stream description and corrected-source SHA-256 values.

## Source hashes recorded in the updated manuscript

- `reference/src/ref_runtime.c`: `7bd1c21fa3f6e45489bcf49b80c617549280318014ff50e1e04bcbcc3a3739b0`
- `reference/include/ref_runtime.h`: `98916dff0c5c8dfa87979506353b5003387e6d12cca3703d0ef1df222f3c55a5`

## Evidence boundaries

The user's PowerShell output reports 400/400 valid harness rows and five matching repetitions for each of 80 family/variant groups for the checked fields. Key reported outcomes:

| Family | P0 | P1 | P2 | P3 | P4 |
|---|---|---|---|---|---|
| CF04 | `STALE_REF`, active | `STALE_REF`, active | `STALE_REF`, active | `STALE_REF`, active | `TERMINAL_ESCALATE`, closed |
| CF05 | `TERMINAL_ESCALATE`, 2 attempts | `TERMINAL_ESCALATE`, 3 | `NO_TERMINAL`, active at 4 | `NO_TERMINAL`, active at 4 | `TERMINAL_ESCALATE`, 3 |
| CF06 | `TERMINAL_ESCALATE`, 2 | `TERMINAL_DEGRADE`, 3 | `NO_TERMINAL`, active at 4 | `NO_TERMINAL`, active at 4 | `TERMINAL_DEGRADE`, 3 |
| CF07 | `EPISODE_FULL`, active | `EPISODE_FULL`, active | `EPISODE_FULL`, active | `EPISODE_FULL`, active | `SUCCESS`, closed |

Recorded local hashes from the user's output:
- `k10_runs.csv`: `6E37C8C278BE673DFB0F5E2C6E134CFDE1AE95FEA09F7F6FB7C3765EAFA13102`
- `k10_traces.csv`: `50C41AADB7CFC2E2807806D642939D23107493631B744EB84058AA0DDEB659DC`
- `k10_results.md`: `3EA52786ECB44F7DA0AFA510493A2D70EDBB005B6CD6C6E9064B1BB6FB56E361`

**Important:** The raw CSV/trace/report files were not present in the artifact workspace during manuscript update. The hashes are copied from the user's reported output, not recomputed here. Do not claim the raw files are committed until they are uploaded and verified. The revised DOCX/PDF are generated artifacts in the conversation workspace; their binary contents have not been uploaded to GitHub by this text-only repository update.
