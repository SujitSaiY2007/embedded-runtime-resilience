# Phase 1 Host Evidence Freeze

Date: 2026-10-26
Branch: main
Git HEAD: 73bda25d964d048184c425c4335802ae38874d03

## Campaign validation

| Check | Campaign C | Campaign D |
|---|---:|---:|
| Runs | 560 | 560 |
| Matrix completeness | PASS | PASS |
| Repetition stability | PASS | PASS |
| Deterministic replay | PASS | PASS |
| Harness failures | 0 | 0 |

Run and trace CSV hashes must match the locally recorded values below.

## CSV SHA-256

### research/closure/k10_v2_run_2026-10-26_c

- `k10_v2_runs.csv`: `70240D46F4CDF1AF56DD9469195044069823CA6AC7F3BAC2EADEA3E68A6A172C`
- `k10_v2_traces.csv`: `7D89A66D9E685818D24C6AB8FC30AEBAB2E1480E24635D6984CF64B38B6785DC`

### research/closure/k10_v2_run_2026-10-26_d

- `k10_v2_runs.csv`: `70240D46F4CDF1AF56DD9469195044069823CA6AC7F3BAC2EADEA3E68A6A172C`
- `k10_v2_traces.csv`: `7D89A66D9E685818D24C6AB8FC30AEBAB2E1480E24635D6984CF64B38B6785DC`

## Accepted source SHA-256

- `reference_v2/src/ref_runtime.c`: `FD344F907BCA4EB75279960625B1CC9D585342F958B3D76C4832FB240F5A65B3`
- `reference_v2/include/ref_runtime.h`: `7A69FD7D351E93947F72DF5CB1C2BCD4208A0C10EBC1F588CF520DCC80F0A19C`
- `reference_v2/experiments/k10_v2_experiment.c`: `5AF4DE1DDB1A853911AF0180078309BDDDBCE471FE9247B848A4090DB541E790`
- `reference_v2/experiments/run_k10_v2.py`: `0E050CD9045D53254782206DFD2B43B787977B33BF6EB5B307538A25F08CDF35`

## Scope and limitations

- Evidence class: host reference-model experiments only.
- This record does not establish physical-hardware reliability.
- It does not establish universal superiority of P4.
- Earlier campaign outputs are retained as diagnostic evidence.
- Review the CF05/CF06 termination fix and regression tests against this source revision.
