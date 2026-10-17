# Chat 01 Handoff — Reference Inventory

**Status:** Ready to start  
**Branch:** `main` only

## Task

Inventory the preliminary ~43 references from the archived and original `REFERENCE_REGISTER.md`. Preserve original citation text and create a stable, auditable entry per reference.

## Do not

- Edit manuscript bibliography yet.
- Assume publication type, peer review, venue prestige, DOI, or direct influence.
- Delete weak/unverified references; classify them first.
- Modify runtime code, frozen results, or Gate artifacts.

## Required output

Create `Plan2.0/reference_audit/REFERENCE_REGISTER.csv` and a short summary with exact counts, duplicates, missing metadata, and verification status. If the register has more or fewer than approximately 43 entries, report the actual count and counting method.

## Validation

Check every source entry maps to one row, no rows were silently dropped, and CSV escaping is valid. State which fields were verified against primary sources versus still unverified.

## Next chat

Chat 02: verify each source's bibliographic metadata, DOI/official landing page, publication type, peer-review status, and venue quality. Update audit fields; do not change manuscript prose until Chat 03 completes traceability/gap analysis.
