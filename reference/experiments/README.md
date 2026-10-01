# Host Experiment Harness

This directory is the smallest host-only reproducibility layer over the committed reference runtime.

## Inputs

- `workloads.csv` is the declarative workload operation stream.
- `fault_schedules.csv` is the deterministic fault/action schedule.
- Neither file is generated from test assertions at runtime.

## Build

From `reference/`:

```text
cmake -S . -B build
cmake --build build
```

## Run

```text
python3 experiments/run_host_experiment.py
```

The script:

1. copies the raw input schedules into a timestamp-independent corpus directory;
2. runs the C harness for P0-P4 over the same workload/fault inputs;
3. writes machine-readable run summaries and traces;
4. reruns the harness and compares SHA-256 hashes for deterministic replay;
5. writes `corpus_manifest.csv`.

## Outputs

`out/` contains:

- `raw/workloads.csv`
- `raw/fault_schedules.csv`
- `runs.csv`
- `trace.csv`
- `corpus_manifest.csv`

The harness records `capacity_confounded` for W09/W10 and `ablation_contract_valid` as 0 for P0-P3 because the current reference implementation applies exact-event quarantine to every variant. This is an implementation qualification, not an amendment to Gates A-E.

## Evidence boundary

All outputs are host/reference/software-injection evidence. They do not measure STM32U575 timing, RAM, Flash, energy, electrical fault behavior, or physical recovery.

## Verification checkpoint — 2026-10-01

Chat K.1 execution verification completed in the user-controlled Windows/MSVC environment.

- Build succeeded.
- CTest: **2/2 passed**.
- `py run_host_experiment.py --check`: all five checks **PASS**.
- Corpus cardinality during verification: **70 runs**.
- W09/W10: `capacity_confounded=1`.
- P0-P3: `ablation_contract_valid=0`.
- P4: `ablation_contract_valid=1`.

The generated `out/` and `out.replay/` directories were inspected during verification and then removed before the clean source checkpoint. Therefore the repository currently commits the reproducibility inputs/harness, not the transient generated CSV outputs.

**Chat K.2 must validate the regenerated CSV corpus itself before any policy-level interpretation is made.**


## Corpus validation checkpoint — Chat K.2 — 2026-10-01

The regenerated corpus was inspected after the K.1 execution checkpoint.

- **70 runs** were present for W01-W14 × P0-P4.
- `corpus_manifest.csv` reported PASS for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- The manifest explicitly reports host evidence only (`host_evidence_only=1`) and no MCU/physical evidence.
- Representative `runs.csv`/`trace.csv` slices were inspected for recovery attempts, action/outcome transitions, correctness, EventRef-related metadata, and capacity/ablation flags.
- No concrete corpus-generation, serialization, or runtime defect was found.

### Interpretation limits

K.2 validates corpus reproducibility and emitted evidence structure; it does not establish experimental superiority or cleanly isolate quarantine as an ablation. P0-P3 remain invalid clean quarantine ablations under the current reference semantics because exact-event quarantine is applied across variants. W09/W10 remain capacity-confounded.

The generated `out/` and `out.replay/` directories are transient verification outputs and should not be treated as required committed source artifacts.

**K.2 is complete.**


## Final K.3 boundary — 2026-10-01

K.3 packages the host/reference evidence without changing the harness semantics. The validated corpus remains 70 matched W01-W14 × P0-P4 runs. P0-P3 remain `ablation_contract_valid=0`, W09/W10 remain capacity-confounded, and the corpus remains host/reference + deterministic software-injection evidence only.

See `research/phase1_final_evidence_synthesis.md` for the final evidence matrix and deferred-validation boundary. No generated `out/` or `out.replay/` directory is required as a committed artifact.
