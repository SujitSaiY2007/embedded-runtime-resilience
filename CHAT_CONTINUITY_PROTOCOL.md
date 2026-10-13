# Chat Continuity Protocol — Finalized Project

## Current status

As of 2026-10-13, the software/research scope of Embedded Runtime Resilience is finalized. K.10's frozen investigation, K.10.1–K.10.4 adversarial review, K.11 synthesis and K.12 software demonstrator are closed. Physical MCU implementation is future work.

## Canonical startup reading
1. `README.md`
2. `docs/PROJECT_OVERVIEW.md`
3. `docs/ARCHITECTURE_AND_REPOSITORY_MAP.md`
4. `docs/DEMONSTRATOR_GUIDE.md`
5. `research/README.md`
6. K.10 results, K.10.4 conclusion, K.11 synthesis and K.12 audit as relevant.
7. Root continuity files and `research/chat_records/` for historical provenance.

## Integrity rules
- Do not modify protected runtime/Gate artifacts without a separately approved scope.
- Do not rerun the frozen K.10 matrix to repair a documentation inconsistency.
- Preserve dated checkpoint records.
- Do not represent host/virtual results as physical MCU evidence.
- Mark user-run tests as user-reported unless a reproducible CI/run artifact is available.
- CF01: present P0 terminal escalation, P2 success and P4 success; omit the disputed P2 attempt count from comparisons.
- `exp` is the preserved research baseline; documentation-only work on `main` must not mutate it.

## Closeout format
Record the exact scope, files changed, validation actually performed, validation provenance, commit and branch refs, unresolved scientific limits, and future work. Keep the public README concise; place chronology in the checkpoint archive.
