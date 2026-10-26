# Archive — Historical Preservation

This directory holds a **read-only snapshot** of pre-Plan-2.0 non-code documentation and preliminary reference materials.

## Preservation decision

The initial Plan 2.0 setup copies existing documentation blobs into `archive/legacy_snapshot/` without deleting or rewriting their original paths. This preserves the historical record and avoids breaking links while the new workflow is established. The archive is not proof that every archived claim is current; use dated state documents and Plan 2.0 current state to distinguish history from present status.

## Contents

- `legacy_snapshot/`: snapshot copies of prior Markdown documentation, plans, research reports, decision/continuity documents, chat records, and preliminary reference register.
- `legacy_snapshot/research/references_used/REFERENCE_REGISTER.md`: snapshot of the preliminary reference list (approximately 43 entries; Chat 01 must count and reconcile the actual entries).
- `legacy_snapshot/research/references_used/COUNTING_AND_VERIFICATION.md`: previous reference-counting guidance, if present.

## Canonical source policy

- Existing code remains at its original path and is not copied into this archive.
- Existing frozen experimental evidence and source documents remain untouched in their original paths.
- Until an explicit, link-safe migration is approved, originals remain the source of truth; archive copies are preservation snapshots.
- Do not edit archive copies to update current status. Add new work under `Plan2.0/`.


## Manuscript release cleanup — 26 October 2026

The following files were preserved as historical artifacts during the manuscript release cleanup:

- `project/README_PRE_MANUSCRIPT_RELEASE_2026-10-26.md` — prior root landing page, superseded by the concise current `/README.md`.
- `manuscript/DRAFT_MANUSCRIPT_PRE_FINAL_2026-10-26.md` — earlier Markdown draft, superseded by the author-supplied DOCX/PDF release files.

Active source code and current evidence records were not moved or deleted. This avoids breaking experiment scripts and provenance links.
