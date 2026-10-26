# Phase 4 — Prior-Art and Novelty Conclusion

**Date:** 2026-10-26  
**Branch:** `main`  
**Status:** Technical novelty assessment completed at evidence-bounded level; legal novelty/patentability is not established.  
**Evidence basis:** Frozen K.10 result report, existing novelty investigation, current repository source records, and primary-source literature checks.

## Executive conclusion

The project has a **defensible, bounded research contribution hypothesis**, but it is not scientifically or legally justified to conclude that the overall method is definitively novel or patentable.

The strongest empirical contribution currently supported by the frozen software campaign is not “P4 is always better.” It is that an integrated policy combining evidence-bounded fault association and a finite recovery ladder behaves more safely in selected adversarial scenarios than the specific P0–P3 comparison policies. The frozen report identifies attributable advantages in CF04 (association ambiguity/fail-closed behavior), CF05 (fault during recovery/finite termination), and CF07 (subsequent fault handling after an ambiguous episode). It also records counterexamples and shared mechanisms: quarantine/background-work preservation is common across all policies, and P2 needs only one attempt in CF16 where P4 uses three.

The current hardware evidence is complementary but narrower: one user-observed policy diagnostic run showed P1 and P4 reaching a successful post-recovery BME280 chip-ID read after a controlled address NACK, while P0, P2, and P3 reached terminal/non-pass outcomes. This is one run, not independent repeated trials, and cannot establish general P4 superiority.

## What prior art establishes

### Directly relevant embedded peripheral recovery

Smith and Rixner's Phoenix system addresses peripheral failures in embedded systems using lightweight checkpointing to track internal program state and external peripheral state, then roll back to the failed access. It is a direct and important comparator, not evidence that the present project is already novel. Phoenix reports use of as little as 6 KB in its evaluated applications. Primary source: https://www.usenix.org/conference/atc15/technical-session/presentation/smith

### Fault recovery and automatic re-execution

Existing patents and literature also disclose peripheral error detection, recovery data, retry/re-execution, reinitialization, and escalation. For example, US Patent 11,301,328 describes microcontroller peripheral-process recovery using recovery data and another execution attempt. Patent-family and claim-level review is still needed before any legal conclusion. Public record: https://patents.justia.com/patent/11301328

### Broader fault-tolerance context

Surveys confirm that checkpointing, rollback, retry, and other fault-tolerance methods are established, with trade-offs in execution time, energy, memory, and reliability. See the IEEE Access survey, DOI: https://doi.org/10.1109/ACCESS.2022.3144217 and the 2024 dependability survey, DOI: https://doi.org/10.1109/ACCESS.2024.3509633.

### Combination-level hypothesis

The candidate distinction is the integrated constrained runtime sequence:

1. Evidence-bounded association between a fault and an event.
2. Zero-heap/static bounded runtime state.
3. Context/history-informed selection among a finite recovery ladder.
4. Event-level quarantine/retention and dependency-aware preservation.
5. Verification before release, or bounded terminal escalation.
6. Deterministic traces that expose the fault-to-decision-to-outcome path.

These ingredients and several sub-combinations are established in prior art. The project may be distinguishable through the exact integration and invariants, but the present review does not prove that no earlier paper, patent family, or implementation discloses the same combination. A multi-reference obviousness/recombination argument remains plausible.

## Claim-to-evidence conclusion

| Claim | Conclusion | Basis / boundary |
|---|---|---|
| The project implements a reproducible comparative framework | Supported | Frozen 16-family × 5-policy × 5-repeat host/reference campaign and preserved reports. |
| P4 has attributable advantages in selected software scenarios | Supported within the frozen model | CF04, CF05, and CF07 in K.10; not universal. |
| P4 uniquely provides general event quarantine or background-work preservation | Rejected | K.10 attributes this to shared runtime behavior across P0–P4. |
| P4 is always more efficient | Rejected | CF16: P2 succeeds in one attempt while P4 takes three; P4 also has more decision checks. These are model/attempt-count comparisons, not measured physical time. |
| The same recovery behavior has been observed on a physical MCU | Partially supported | One controlled NACK/BME280 run; P1 and P4 passed, P0/P2/P3 terminal/non-pass. Exact source-to-binary identity and repeatability remain unresolved. |
| The whole combination is novel | Not established | Existing prior art covers many ingredients; exhaustive source and claim mapping is incomplete. |
| The work is patentable | Not determined | Requires formal patentability analysis by qualified counsel and applicable jurisdiction-specific review. |

## Final Phase 4 decision

**Classification: empirically supported bounded contribution; potentially distinguishable integrated design; novelty and patentability unproven.**

For a paper, the defensible contribution statement is:

> This work implements and evaluates a deterministic, bounded recovery runtime for event-driven embedded workloads. In a frozen matched host/reference campaign, the integrated policy showed attributable advantages over the tested comparison policies in selected ambiguous-association and repeated-recovery-fault scenarios, while sharing quarantine behavior with the baselines and incurring a cost on known-persistent faults. A controlled STM32L476RG/BME280 address-NACK experiment provides initial physical evidence for selected recovery paths, but does not establish universal superiority or full hardware performance.

Do not use “first,” “unprecedented,” “proven novel,” “patentable,” or “universally superior” without additional evidence and expert review.

## Remaining limitation

This is a technical prior-art assessment, not a formal freedom-to-operate, patentability, or legal novelty opinion. The existing PA-01–PA-10 inventory should be retained, but each patent's official publication, claims, family, priority date, and legal status should be verified before publication or any patent filing. No frozen code, raw evidence, or historical report was modified to reach this conclusion.
