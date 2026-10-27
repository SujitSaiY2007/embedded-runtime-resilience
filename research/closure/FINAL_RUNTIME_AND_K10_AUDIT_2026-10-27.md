# Final Runtime Correction and K.10 Evidence Audit — 27 October 2026

## Decision

**The runtime correction branch passes the repository's eight-test CTest suite and the fresh K.10 campaign reports 400 matched executions with deterministic repetition groups.** The branch is ready to be merged as a code-and-documentation correction, but the locally generated raw CSV files still need to be added to the repository for full run-level reproducibility. This audit does not claim that the manuscript's binary DOCX/PDF has been regenerated.

## Branch and validation provenance

- Branch: `audit/runtime-correction-2026-10-27`
- Base: `main` at the branch creation point
- User-run CTest result: **8/8 passed**, including `reference_tests`, `host_experiment_replay`, `k10_advantage_evaluation`, virtual-system/demo/baseline/UI tests, and `matched_baseline_validation_test`.
- Fresh K.10 output directory on the user's cloned repository: `research/audit_runs/20261027_112620/`.
- Run design: 16 case families × 5 policy variants (P0–P4) × 5 repetitions = **400 executions**.
- Observed rows: 400; each of the 80 family/variant groups contained five matching repetitions for the inspected outcome/state/attempt/work/trace fields.
- Harness validity: `harness_ok=1` for all 400 records.
- Local SHA-256:
  - `k10_runs.csv`: `6E37C8C278BE673DFB0F5E2C6E134CFDE1AE95FEA09F7F6FB7C3765EAFA13102`
  - `k10_traces.csv`: `50C41AADB7CFC2E2807806D642939D23107493631B744EB84058AA0DDEB659DC`
  - `k10_results.md`: `3EA52786ECB44F7DA0AFA510493A2D70EDBB005B6CD6C6E9064B1BB6FB56E361`

The above results are recorded from the user's Windows PowerShell output; this audit has not independently executed the Windows build. The raw CSVs and generated report are currently local artifacts and are **not included by this Markdown record**. The hashes identify the local files and should be rechecked after any copy or upload.

## Runtime corrections

The branch changes `reference/src/ref_runtime.c` and adds regression coverage in `reference/tests/test_reference.c` for:
1. skipping slots whose generation counter is exhausted;
2. returning `OUTCOME_SLOT_FULL` when no reusable slot remains;
3. refusing recovery release when the queue is full, without consuming an attempt or corrupting quarantine state; and
4. closing an episode and cleaning quarantine accounting when the target reference is stale.

The header's `OUTCOME_SLOT_FULL` definition was already present and was retained. No hardware flashing was performed for this correction.

## Fresh K.10 results: decisive families

The following results were shown in the generated run table and repetition check:

| Family | P0 | P1 | P2 | P3 | P4 | Evidence-bounded interpretation |
|---|---|---|---|---|---|---|
| CF04 association ambiguity | `STALE_REF`, active | `STALE_REF`, active | `STALE_REF`, active | `STALE_REF`, active | `TERMINAL_ESCALATE`, closed | P4 alone closes the episode under the tested ambiguous-association input. |
| CF05 fault during recovery | `TERMINAL_ESCALATE` at 2 attempts | `TERMINAL_ESCALATE` at 3 | `NO_TERMINAL`, active at 4 | `NO_TERMINAL`, active at 4 | `TERMINAL_ESCALATE` at 3 | P4 terminates in this tested sequence; P2/P3 do not terminate within the observed four attempts. |
| CF06 recovery failure | `TERMINAL_ESCALATE` at 2 | `TERMINAL_DEGRADE` at 3 | `NO_TERMINAL`, active at 4 | `NO_TERMINAL`, active at 4 | `TERMINAL_DEGRADE` at 3 | P4 supports terminal degradation for this deferable-work case; P1 shares that outcome. |
| CF07 subsequent fault | `EPISODE_FULL`, active | `EPISODE_FULL`, active | `EPISODE_FULL`, active | `EPISODE_FULL`, active | `SUCCESS`, closed | P4 services the subsequent fault where the other tested variants are blocked by an active episode. |

These are scenario-specific outcomes, not universal superiority claims. CF05 and CF06 are evidence for bounded termination against these tested variants, not proof that all alternatives are unbounded. The same campaign reports a trade-off in CF16: P2 succeeds in one attempt while P4 takes three. Work preservation is shared across variants and must not be presented as a P4-only advantage.

## Interpretation and reproducibility guardrails

- The K.10 report generator contains authored, per-family interpretation strings. The narrative labels are not themselves an independent statistical test; the CSV rows and trace data remain the primary run-level artifacts.
- The five repeated rows per group establish deterministic repetition for the fields checked by the user's script. They do not establish statistical generalization to unseen workloads.
- P0–P3 are in-house comparison variants, not independent implementations of published algorithms.
- The hardware evidence is separate: one controlled STM32L476RG/BME280 I²C address-NACK/readback demonstration and the documented control trials. The host K.10 campaign is not a physical-hardware experiment.
- No MCU latency, energy, stack high-water mark, complete RAM/Flash profile, stuck-bus recovery, or binary/source identity claim is added here.
- The frozen historical K.10 report is retained as historical evidence. This new run is recorded separately; do not silently replace frozen records with regenerated output.
- The manuscript's DOCX/PDF binary was not edited by this text-only GitHub update. The evidence ledger, readiness documentation, and manuscript release notes are updated to point to this audit.

## Merge recommendation

Merge the runtime correction and evidence-bound documentation from this branch after confirming the local clone still passes all eight tests. Preserve the local K.10 CSV/trace/report files and upload them to a dedicated evidence directory in a separate artifact commit when binary/text-artifact upload is available. Keep `exp` unchanged. Do not claim the manuscript binary has been revised until an updated DOCX/PDF is generated and committed.
