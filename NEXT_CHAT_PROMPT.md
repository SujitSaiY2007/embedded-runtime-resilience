# Next Task — Publish Final Manuscript Artifacts

**Repository:** https://github.com/SujitSaiY2007/embedded-runtime-resilience  
**Branch:** `main` only. Keep `exp` protected and unchanged.

The manuscript drafting milestone is complete. Do not restart manuscript writing, ask the authors routine questions, or begin the previously proposed Chat 12 hardware bridge automatically.

## Task

1. Upload the author-supplied final Word manuscript and PDF to `research/manuscript/final/` using the canonical names:
   - `Embedded_Runtime_Resilience_Manuscript.docx`
   - `Embedded_Runtime_Resilience_Manuscript.pdf`
2. Verify that both files are present and openable from GitHub.
3. If needed, update [research/manuscript/README.md](research/manuscript/README.md) and [root README](README.md) so links point to the actual files.
4. Do not modify protected runtime source, the frozen 400-run evidence, hardware results, or the `exp` branch.
5. Do not claim that binary artifacts are uploaded until verified.

The available GitHub connector in the preceding cleanup exposed text-file operations but no binary upload operation. If running in an environment with direct GitHub web access, complete the upload there. If not, provide the user with the exact manual upload steps and stop.

## Current evidence limits

The host campaign is 16 families × 5 policies × 5 repetitions = 400 frozen executions. The physical NUCLEO-L476RG/BME280 policy comparison is one run; five control trials are separate. The browser demonstrator is software-only. Exact flashed-binary identity is unverified. No universal P4 superiority or MCU timing/energy/stack claim is made.
