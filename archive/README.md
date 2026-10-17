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
