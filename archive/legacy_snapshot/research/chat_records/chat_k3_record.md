# Chat K.3 — Final Evidence-Bounded Synthesis Record

**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Branch:** `experiment/host-p0-p4-corpus-2026-10-01`  
**Date:** 2026-10-01  
**Checkpoint:** K.3 — Final synthesis and repository packaging

## Startup continuity check

The mandatory K.3 startup documents were read in the requested order. Gates A-E remain frozen and normative. K.1 and K.2 are complete. No earlier gate was reopened or redesigned.

## Work completed

1. Audited the current evidence boundary and separated:
   - frozen design/specification evidence;
   - host/reference correctness evidence;
   - host corpus/reproducibility evidence;
   - absent MCU evidence;
   - absent physical fault/recovery evidence;
   - remaining ablation/capacity limitations.
2. Added `research/phase1_final_evidence_synthesis.md`.
3. Reconciled current project-state, handoff, continuity-protocol, manual, decision-log, and reference README status with K.1/K.2.
4. Preserved historical K.1/K.2 material and the explicit supersession relationship where older pending text existed.
5. Recorded D-085 for the K.3 evidence boundary and archive decision.

## Definitively established at this checkpoint

- Gates A-E remain frozen.
- The host/reference implementation and deterministic experiment harness have verified execution in the tested Windows/MSVC environment.
- CTest passed 2/2 during K.1.
- The host experiment checks passed for deterministic replay, matched-input equivalence, raw-input preservation, capacity-confound flagging, and ablation-contract flagging.
- K.2 validated the regenerated 70-run W01-W14 × P0-P4 corpus and found no concrete corpus-generation, serialization, or runtime defect in the inspected evidence.
- P0-P3 remain `ablation_contract_valid=0`; P4 is the only variant marked valid under the current implementation boundary.
- W09/W10 remain capacity-confounded.
- The evidence remains host/reference + deterministic software injection only.

## Not established

No MCU timing, RAM/Flash, MPU, interrupt, peripheral, energy, electrical fault, or physical recovery evidence is established. The host corpus does not establish statistical significance, external generalization, novelty, or patentability, and does not provide a clean causal quarantine ablation.

## K.3 stop condition

**K.3 COMPLETE.**

No MCU integration, physical validation, baseline redesign, or semantic change was performed merely because K.2 completed. Any resumed work must explicitly select a deferred validation objective.

Generated experiment outputs remain transient verification artifacts; the repository preserves the reproducibility inputs, harness, source/reference implementation, and continuity records rather than treating transient outputs as required committed artifacts.
