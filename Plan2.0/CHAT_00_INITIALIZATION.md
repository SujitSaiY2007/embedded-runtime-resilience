# Chat 00 — Plan 2.0 Initialization and Handoff

## Purpose

Initialize Plan 2.0 on `main`, clarify the active phase, preserve pre-existing source files, create a snapshot of prior non-code documentation and the preliminary reference register, and establish a multi-chat sequence.

## Initial truth

- Software/reference-model demonstrator exists.
- Frozen campaign contains 400 deterministic host/reference executions.
- Physical hardware validation is not complete.
- Preliminary bibliography (~43 entries) has not been fully audited for metadata, venue quality, relevance, and influence.
- No reference should be claimed as a direct implementation source without evidence.

## Initialization checklist

- [x] Top-level README links to Plan 2.0 and accurately describes status.
- [x] Roadmap, reference audit protocol, hardware plan, and chat protocol created.
- [x] Archive index created.
- [x] Legacy non-code documentation and preliminary reference register preserved as archive snapshots; original paths retained.
- [x] No source code, frozen results, or protected contracts modified by this commit.
- [ ] Verify actual commit SHA and live `main` head after commit.
- [ ] Chat 01 inventories every preliminary reference.

## Handoff to Chat 01

**Objective:** Inventory every entry in the preliminary reference register and create a verified audit table without revising the manuscript bibliography yet.

**Must read:** `Plan2.0/REFERENCE_OVERHAUL.md`, `Plan2.0/CURRENT_STATE.md`, `archive/README.md`, and the archived and original `research/references_used/REFERENCE_REGISTER.md`.

**Required output:** Entry-by-entry list with stable ID, original citation text, initial publication-type guess, verification status, and missing fields. Preserve original source wording. Do not remove or replace citations yet.

**Acceptance:** Every entry is accounted for; counts reconcile; no metadata is invented; unresolved entries are flagged. Close by updating `Plan2.0/handoffs/CHAT_01_HANDOFF.md` and preparing the exact Chat 02 prompt.
