# Next Chat Prompt — Chat K.2: Host Corpus Validation

Copy/paste the following prompt into the next ChatGPT chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

This is **Chat K.2**, continuing directly from **Chat K.1**. Do not restart the project.

## Mandatory startup reading

Read, in order:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `research/phase1_reference_implementation_audit.md`
7. `research/phase1_gateA_event_model_final.md`
8. `research/phase1_gateB_fault_model_final.md`
9. `research/phase1_gateB_learning_summary.md`
10. `research/phase1_gateC_recovery_policy_final.md`
11. `research/phase1_gateD_formal_properties_final.md`
12. `research/phase1_gateE_experimental_protocol_final.md`
13. `research/phase1_reference_implementation_design.md`
14. `reference/README.md`
15. `reference/docs/minimal_reference_implementation.md`
16. `reference/tests/canonical_workloads.md`
17. `reference/experiments/README.md`
18. relevant files under `reference/include`, `reference/src`, `reference/tests`, and `reference/experiments`

Then give a concise continuity check. Do not repeat the entire research history.

## Frozen state

Gates A-E are frozen and normative.

The reference implementation and host experiment harness are already committed on:

`experiment/host-p0-p4-corpus-2026-10-01`

Current checkpoint commit lineage begins with:

`949bd4c`

Chat K.1 already verified:

- Windows/MSVC build succeeds.
- `ctest --test-dir reference/build -C Debug --output-on-failure` passes 2/2.
- `py experiments/run_host_experiment.py --check` passes:
  - deterministic replay;
  - matched-input equivalence;
  - raw-input preservation;
  - capacity-confound flagging;
  - ablation-contract flagging.
- 70 matched runs were generated: W01-W14 × P0-P4.
- W09/W10 are capacity-confounded.
- P0-P3 are not valid clean quarantine ablations under the current reference semantics.
- P4 is marked valid under the current implementation boundary.

## ONLY TASK FOR CHAT K.2

Validate the **actual generated host corpus**, not merely the harness execution.

Regenerate the corpus from the committed source if necessary, then inspect:

`reference/experiments/out/runs.csv`  
`reference/experiments/out/trace.csv`  
`reference/experiments/out/corpus_manifest.csv`

Check at minimum:

1. Every W01-W14 workload has exactly matched P0-P4 executions.
2. Run identifiers, variant identifiers, workload identifiers, and trace metadata are consistent.
3. Trace EventRef/generation identity is coherent, including W11 stale-generation/slot-reuse behavior.
4. Recovery action sequences agree with the frozen Gate-C ladder.
5. Terminal outcomes and correctness fields are internally consistent.
6. W09/W10 capacity-confounded flags are explicit and correctly scoped.
7. P0-P3/P4 ablation-contract flags are explicit and correctly scoped.
8. Quarantine/preservation evidence visible in traces is consistent with the actual current reference semantics.
9. Distinguish harness correctness from policy correctness.
10. Identify any missing Gate-E evidence that must be addressed before interpreting experimental comparisons.

If a concrete defect is found, make the **smallest** evidence-preserving correction. Do not redesign Gates A-E or silently redefine P0-P4.

## Important semantic limitation

The audit already established:

`runtime_start_fault()` applies exact-event quarantine across all policy variants.

Therefore P0-P3 currently cannot be treated as clean quarantine ablations. Do not erase, weaken, or hide this limitation.

## Evidence boundary

Host/reference evidence only.

Do not claim:

- STM32U575 timing;
- MCU RAM/Flash;
- physical electrical fault behavior;
- energy measurements;
- physical recovery;
- statistical significance;
- generalization;
- novelty;
- patentability.

## Completion condition

Stop after the smallest reproducible corpus-validation checkpoint.

Update:

- `PROJECT_STATE.md`
- `CURRENT_HANDOFF.md`
- `DECISION_LOG.md`
- `research/chat_records/chat_k1_k2_record.md`
- relevant experiment documentation

Do not begin MCU integration in Chat K.2.

---