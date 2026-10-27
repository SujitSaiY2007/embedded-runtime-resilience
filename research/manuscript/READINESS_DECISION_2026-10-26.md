# Manuscript Readiness Decision — 26 October 2026

## Decision

**Yes: manuscript drafting can proceed now. No: the paper is not yet ready for submission or for a final results freeze.** A full v0.1 draft already exists at `research/manuscript/DRAFT_MANUSCRIPT.md`. It should be treated as a working scientific draft with explicit limitations, not as a completed journal manuscript.

## Confirmed evidence available

1. Frozen host/reference report: 16 case families × 5 policies × 5 repetitions = 400 executions. Original raw K.10 CSVs are not in the repository and the user cannot locate them locally; existing host numbers must therefore remain tied to the frozen report table. The original campaign must not be overwritten or silently recreated.
2. Hardware observation: user-provided STM32CubeIDE debugger screenshots and the five-policy hardware harness show a controlled wrong-address I²C NACK at 0x77 and successful fresh BME280 ID reads (0x60 at 0x76) after the selected reinitialization path for P1 and P4 in one observed run. P0, P2 and P3 ended in terminal status. This is not a stuck-SDA/SCL test or a repeated-trial study.
3. Source provenance: user-supplied `hardware_exp.c` SHA-256 is `8d65294a7dbf8aca22cab9f2c56732bdb015bf7c3fab87cee6b555f7ae6a1ee8`. This identifies the supplied source bytes, not the flashed binary.
4. Local candidate test: user screenshot shows the additive `reference_v2` CTest target passed 1/1 test. This is user-run evidence and has not been independently reproduced in this environment.
5. Software demonstrator: documented architecture routes the UI through the Python bridge and C virtual-system adapter into the C reference runtime. Do not imply this is a physical MCU run.

## Work completed in the manuscript workspace

- Full v0.1 manuscript exists.
- Claim-to-evidence ledger exists and now records the supplied hardware source hash and the v2 test limitation.
- Reference audit, figure/table plan, and open-issues register exist.
- Manuscript README and open issues have been updated to reflect the latest local test, missing original CSVs, supplied hardware source, and binary-identity limitation.
- The research resolution register records the same provenance and decision boundaries.
- Protected canonical `reference/` source and frozen K.10 data have not been intentionally changed by this manuscript work.

## Mandatory gates before a submission-ready draft

### Gate A — Corrected candidate campaign
The v2 edge-test screenshot is not the corrected campaign. Build/test the exact current `main` state, then run the P0–P6 campaign in a fresh output directory. Required target matrix: 16 families × 7 policies × 5 repetitions = 560 run rows, plus deterministic replay and completeness checks. Do not use the campaign until the runner confirms full matrix coverage, valid harness status, and deterministic output. Keep all v2 outputs separate from frozen K.10 evidence. The campaign must not be described as completed until its output files are inspected.

### Gate B — Resource and hardware evidence
The current hardware run is useful proof-of-path only. No verified STM32L476RG Flash/RAM/stack/decision-latency measurements or repeated controlled runs are available. A no-reinitialization control is missing, so the data do not establish that reinitialization was necessary. These need new measurements at the user's board/toolchain; they cannot be honestly fabricated or completed by repository edits alone.

### Gate C — Literature
The current cited list has 6 journal articles among 10 citations (60%), below the recorded 75% target. The reference audit is partial: several entries are repository-derived rather than freshly checked, full-text claim checks are incomplete, and a systematic prior-art search has not been completed. Verify each cited record against publisher/DOI/institutional sources, review the directly relevant Kleeberger line of work and its related papers, and add only relevant verified sources. Do not pad the bibliography to meet a ratio.

### Gate D — Numerical discrepancies and artifact provenance
- Keep the CF01 P2 attempt count out of numerical comparisons unless primary records resolve the conflict.
- Preserve the CF08 P0 conflict and report it as unresolved; do not choose a convenient version.
- The full 80-entry hardware matrix has not been independently audited from a complete export. The harness aggregate code is not a substitute for inspecting all values.
- The exact flashed binary is not hash-linked to `hardware_exp.c`.
- Original K.10 CSVs remain unavailable; do not make up run-level traces.
- Confirm missing compiler/toolchain versions where available.

### Gate E — Author and venue approval
Before submission, authors must confirm author order/spelling, affiliations, corresponding-author email, CRediT roles, funding, conflicts, ethics/consent requirements, AI-use disclosure, and data/code availability wording. Re-check the selected journal's current official author guidelines and template. Journal fit is not guaranteed.

## Claims currently permissible

- The frozen host/reference report documents a 400-execution deterministic comparison across five in-house policies.
- The runtime source implements static bounded structures and contains the source-level limits documented in the draft.
- One user-observed physical run showed controlled address NACK and post-reinitialization BME280 chip-ID reads for P1 and P4.
- The software demonstrator invokes the same C reference runtime through its documented bridge/adapter architecture.
- The integrated P4 policy has selected-case advantages in the frozen report, with known trade-offs and code-level caveats.

## Claims not permissible yet

- Corrected P0–P6 superiority or any conclusion from the 560-run campaign.
- Universal P4 superiority, statistically generalizable reliability, or measured latency/resource advantages.
- Physical stuck-bus recovery, 80 physical fault injections, repeated-trial reliability, or a verified no-reinit control.
- A claim of novelty, first-of-kind status, patentability, or legal non-obviousness.
- A statement that the exact flashed binary was built from the supplied source hash.

## Bottom line

Drafting can continue immediately using the current evidence and clear limitations. Submission readiness requires Gates A–E above. The only items that cannot be completed by repository edits alone are user-machine execution, new physical measurements, missing original artifacts, and factual author approvals. No professor involvement is needed until the final review/approval stage, as requested.


## Execution order approved — software closure before hardware-only phase

The project execution order is now explicitly:

### Phase 1: Software and proof closure
1. Validate the exact current additive `reference_v2` candidate and all edge-case tests.
2. Run the corrected P0–P6 campaign in a fresh output directory: 16 scenario families × 7 policies × 5 repetitions = 560 executions.
3. Require full matrix completeness, successful harness status, deterministic replay, output-integrity checks, and inspection of the generated run/trace artifacts before accepting the campaign.
4. Investigate counterexamples and report trade-offs; do not pre-commit to P4 superiority.
5. Freeze accepted source, build/test instructions, output hashes, raw generated results, derived summaries, and a claim-to-evidence reconciliation in an additive, versioned evidence package. Keep the original 400-run report and protected `reference/` unchanged.
6. Mark the software/code-and-proof phase closed only when all gates pass or each remaining exception has an explicit, justified disposition. Do not claim execution complete based on source creation or screenshots alone.

### Phase 2: Hardware-only validation
After Phase 1 closes, shift the active work to the STM32L476RG/BME280 setup. Do not make unrelated policy/code changes. Run a documented control without reinitialization, collect repeated controlled-NACK trials, capture complete per-policy values and source/binary provenance, and measure target resource costs where feasible. Treat stuck-bus testing as a separate optional test requiring a safe protocol; address NACK alone is not stuck-bus evidence. Make only narrowly scoped code changes if a hardware result exposes a reproducible defect, then re-run the affected software gates and re-freeze the candidate.

### Phase 3: Claim and manuscript closure
Reconcile the frozen software results and completed hardware evidence, finish the primary-source reference audit and venue checks, and then ask authors to confirm authorship and submission metadata. Professor involvement remains deferred until the final review stage.

This sequence is a plan, not a claim that Phase 1 or Phase 2 has already been completed. The current 560-run campaign and new physical trials remain pending.


## Addendum — 27 October 2026 runtime correction and fresh K.10 rerun

The correction branch `audit/runtime-correction-2026-10-27` adds fixes for exhausted generation slots, queue-full recovery release, and stale-target episode cleanup. The user ran the repository's reference CTest suite on the cloned branch and reported **8/8 tests passing**.

A fresh local K.10 run was generated at `research/audit_runs/20261027_112620/`: 400 rows across 16 case families × five policy variants × five repetitions; the user's validation found 80/80 family/variant groups with five matching repetitions and `harness_ok=1` on all 400 rows. CF04 distinguishes P4's closed `TERMINAL_ESCALATE` from P0–P3's `STALE_REF` with active episodes. CF05 and CF06 show P2/P3 remaining active after four attempts while P4 terminates at three; CF06's terminal degradation is shared by P1 and P4. CF07 shows P0–P3 blocked by `EPISODE_FULL` while P4 completes the subsequent fault.

This new campaign is a separate, regenerated evidence set, not the missing original raw campaign. The raw CSV, trace CSV and generated report remain local and must be committed/uploaded before a third party can independently inspect the run-level data. The report generator contains authored interpretation strings, so the CSV and traces—not report wording alone—are the primary evidence. This addendum does not certify a new hardware run or measured MCU resource performance.

**Submission status remains conditional.** The text documentation is updated, but the Word/PDF manuscript binary has not been regenerated in this operation. Before submission, update the manuscript's results/limitations sections from the audited evidence, regenerate both DOCX and PDF, and review the final rendered figures, tables, references and pagination.