# Project Manual — Scope, Integrity and Research Rules

## Purpose

This repository is a research case study and software demonstrator for a lightweight, zero-heap, context-aware peripheral recovery policy with event quarantine for resource-constrained, event-driven MCU firmware.

## Current status

**Software/research scope finalized (2026-10-13).** K.10's matched investigation, K.10.1–K.10.4 adversarial review, K.11 synthesis, and K.12 software demonstration are closed. The UI executes registered scenarios through the Python bridge and C virtual adapter into the same C reference runtime. Physical MCU implementation and measurements are future work.

## Research discipline

1. Treat novelty as a hypothesis until supported by careful prior-art comparison.
2. State exactly which model and scenarios support each conclusion.
3. Preserve counterexamples, no-difference cases and resource limits.
4. Never imply host/virtual evidence is physical hardware evidence.
5. Do not claim universal superiority, legal non-obviousness or patentability.
6. Preserve frozen evidence and checkpoint records; correct reader-facing summaries without falsifying historical data.
7. If primary records do not resolve a numerical discrepancy, omit that number from comparative claims and explain the scope.

## Frozen boundaries

The following remain protected unless a separately authorized research checkpoint changes them:
- `reference/src/ref_runtime.c`
- `reference/include/ref_runtime.h`
- `research/phase1_reference_implementation_design.md`
- `research/phase2_k9_methodology_lock.md`
- `research/phase2_k9_2_p4_advantage_novelty_design.md`
- Gates A–E and frozen K.10 empirical results.

Do not rerun the 400-execution K.10 matrix to fix a writing inconsistency. Do not silently alter original reports or delete history.

## Branch policy

- `main` is the reader-facing integrated project.
- `exp` remains the preserved research baseline and must not be modified during documentation/presentation work.
- The historical feature branch remains preserved.
- Any future hardware work should use a new named branch and an explicit scope, without changing frozen evidence unless required by a separately reviewed protocol.

## Documentation policy

- Public entry point: `README.md`.
- Curated reader-facing guides: `docs/`.
- Normative research and results: `research/`.
- Executable software: `reference/` and `demo/`.
- Historical checkpoint records: `research/chat_records/`.
- Operational continuity: root `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, `NEXT_CHAT_PROMPT.md`, and `CHAT_CONTINUITY_PROTOCOL.md`.

Keep reader-facing material concise and navigable; retain detailed chronology in historical records rather than repeating stale status sections in the README.
