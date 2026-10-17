# Canonical Workload Trace Index

The executable correctness suite maps directly to the frozen Gate E workload IDs.

| ID | Reference test | Core assertion |
|---|---|---|
| W01 | `test_W01_independent_preservation` | quarantining one exact event does not flush eligible independent work |
| W02 | `test_W02_ordered_blocking` | ordered successor remains blocked |
| W03 | `test_W03_coupled_containment` | coupled member does not execute independently |
| W04 | `test_W04_shared_peripheral_noncausality` | same peripheral does not imply same fault target |
| W05 | `test_W05_retry_success` | first retry can restore the exact target |
| W06 | `test_W06_retry_retry_reinit` | two failed retries lead to reinit/reset path |
| W07 | `test_W07_degrade` | safely degradable persistent failure terminates in degradation |
| W08 | `test_W08_escalate` | unsafe/ambiguous critical failure terminates in escalation |
| W09 | `test_W09_queue_boundary` | QMAX overflow is explicit |
| W10 | `test_W10_quarantine_boundary` | EPMAX=1 is explicit; no hidden second episode |
| W11 | `test_W11_stale_generation` | slot reuse changes generation and stale ref fails closed |
| W12 | `test_W12_association_ambiguity` | non-exact evidence does not fabricate an event target |
| W13 | `test_W13_criticality_degradability` | criticality constrains terminal handling |
| W14 | `test_W14_mixed_and_capacity_constants` | ordered + coupled + independent semantics coexist under fixed bounds |

The workload scenarios are intentionally small host/reference slices. They are not performance campaigns and do not constitute MCU or physical evidence.
