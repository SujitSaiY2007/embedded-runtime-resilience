# Manuscript Results Update — 27 October 2026

**Purpose:** Insert-ready results text for the manuscript authors. This note records the corrected-branch validation and fresh K.10 rerun without silently replacing the historical frozen report. It is not itself the regenerated DOCX/PDF manuscript.

## Results: runtime regression validation

The corrected reference-runtime branch was built and tested in the author's Windows clone. The reported CTest suite completed with 8 of 8 tests passing. The suite covered the reference runtime, host experiment replay, K.10 advantage evaluation, virtual-system tests, virtual demonstration, virtual baseline, UI contracts, and matched-baseline validation. The correction addressed three edge-case classes: exhausted generation counters, stale recovery targets that could leave an episode active, and release into a full queue. These are host-side software regression results; no hardware flashing or new physical test was performed as part of this correction.

## Results: fresh matched K.10 evaluation

A separate K.10 run was generated locally on 27 October 2026 using 16 case families, five in-house policy variants (P0–P4), and five repetitions per family/variant combination. This yields 400 executions and 80 family/variant groups. The author's validation found five matching repetitions in every group for the inspected outcome/state/attempt/work/trace fields, and the harness marked all 400 rows valid. These checks support deterministic repeatability for the checked fields in this harness; they do not provide a statistical estimate of field reliability or generalization to unseen workloads.

| Case family | P0–P3 result pattern | P4 result | Scoped interpretation |
|---|---|---|---|
| CF04 — Association ambiguity | All four variants returned `STALE_REF` and left the episode active | `TERMINAL_ESCALATE`; episode closed | P4 alone failed closed for this tested ambiguous-association input. |
| CF05 — Fault during recovery | P0 escalated after 2 attempts; P1 after 3; P2/P3 remained active after 4 attempts | `TERMINAL_ESCALATE` after 3 attempts | P4 terminated within the tested recovery-fault sequence, unlike P2/P3 in this run. |
| CF06 — Recovery failure | P0 escalated after 2 attempts; P1 degraded after 3; P2/P3 remained active after 4 attempts | `TERMINAL_DEGRADE` after 3 attempts | P4 terminated by degradation for deferable work; this terminal behavior is shared with P1. |
| CF07 — Subsequent fault | All four variants returned `EPISODE_FULL` and retained an active episode | `SUCCESS`; episode closed | P4 processed the subsequent fault in this scenario while the other tested variants were blocked. |
| CF16 — Lower-cost baseline | P2 succeeded in 1 attempt | P4 succeeded in 3 attempts | P4 is not universally cheaper or faster by attempt count; policy integration has a measurable attempt-count trade-off in this case. |

## Interpretation

The results support a bounded claim: within the tested in-house policy variants and deterministic scenario matrix, P4 handled association ambiguity and subsequent-fault handling more safely in CF04 and CF07, and terminated the tested recovery-fault sequences in CF05 and CF06. The results do not establish universal superiority, nor do they isolate every mechanism as uniquely attributable to P4. Graceful degradation in CF06 is shared by P1 and P4; work preservation/quarantine is shared across variants; and P2 has a lower attempt count in CF16.

The K.10 report generator includes authored per-family interpretation text. Therefore, interpretation should be grounded in the generated run rows and traces rather than the narrative labels alone. The raw files from this rerun remain in the author's local `research/audit_runs/20261027_112620/` directory and are not yet committed in the repository. The audit record stores their SHA-256 hashes. Before submission, commit the raw CSV/trace artifacts (or deposit them in a persistent archive) and regenerate the DOCX and PDF from the approved manuscript source, then verify table numbering, references, figures, and pagination.

## Hardware evidence boundary

The K.10 executions are host-side policy experiments, not physical MCU trials. The separately documented STM32L476RG/BME280 controlled I²C address-NACK/readback demonstration remains a narrow proof-of-path result. This update adds no claim of stuck-bus recovery, MCU latency, energy, stack high-water mark, complete RAM/Flash overhead, or a hash-verified link between the flashed binary and source.
