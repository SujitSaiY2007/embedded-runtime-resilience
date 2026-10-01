# Phase 1 Host Corpus Validation — Chat K.2

**Date:** 2026-10-01  
**Branch:** `experiment/host-p0-p4-corpus-2026-10-01`  
**Checkpoint:** Chat K.2  
**Evidence class:** host/reference + deterministic software injection

## Purpose

Validate the actual generated P0-P4 corpus at the run/trace level after the Chat K.1 harness execution checkpoint. This document records corpus evidence without reopening Gates A-E.

## Corpus result

The regenerated corpus contained **70 matched runs**, corresponding to:

`W01-W14 × P0-P4`

The generated output set contained:

- `out/raw/workloads.csv`
- `out/raw/fault_schedules.csv`
- `out/runs.csv`
- `out/trace.csv`
- `out/corpus_manifest.csv`

## Manifest evidence

The observed manifest reported:

- `raw_input_preserved=PASS`
- `matched_input_equivalence=PASS`
- `capacity_confounds_explicit=PASS`
- `ablation_contract_flagging=PASS`
- `deterministic_replay=PASS`
- `run_count=70`
- `host_evidence_only=1`
- `mcu_evidence=0`
- `physical_fault_evidence=0`

## Trace/run inspection

Representative slices were inspected across W05-W08 and W11-W14.

The inspected records showed internally coherent:

- run/variant/workload identifiers;
- trace sequence and fault-episode fields;
- action indices and emitted actions;
- lifecycle state and outcome fields;
- correctness fields;
- recovery-attempt and terminal-outcome fields;
- capacity-confounding metadata;
- ablation-contract metadata.

No concrete corpus-generation, serialization, or runtime defect was identified during this checkpoint.

## Important qualifications

### P0-P3 ablation qualification

The current reference implementation applies exact-event quarantine across all P0-P4 variants through `runtime_start_fault()`. Therefore:

- P0-P3 are **not clean quarantine ablations**.
- `ablation_contract_valid=0` for P0-P3 is expected and must remain visible.
- P4 is marked valid under the current implementation boundary.

This is an implementation/evidence limitation, not a reason to silently redefine the frozen Gate C/E protocol.

### Capacity confounds

W09/W10 remain explicitly marked as capacity-confounded. Their results must not be interpreted as unconstrained policy comparisons.

### Host-only evidence

The corpus demonstrates reproducible behavior of the host reference model under deterministic software injection. It does not establish:

- STM32U575 timing;
- MCU RAM/Flash consumption;
- energy;
- electrical fault behavior;
- physical recovery;
- statistical significance;
- generalization;
- novelty;
- patentability.

## K.2 conclusion

**K.2 is complete.**

No Gates A-E were changed. No MCU integration was started. Generated `out/` and `out.replay/` directories remain transient verification artifacts rather than required source-checkpoint files.

The next checkpoint is **Chat K.3 — Final synthesis and evidence-bounded project packaging**.
