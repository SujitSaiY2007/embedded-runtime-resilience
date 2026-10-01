# Software Demonstrator and Methodology Lock

**Checkpoint:** Integrated software proof-of-concept / methodology lock  
**Date:** 2026-10-01  
**Branch:** feature/software-demonstrator-methodology-lock-2026-10-01

## 1. Purpose

This checkpoint converts the completed Gates A-E design, host reference implementation, K.1/K.2 reproducibility evidence, and K.3 synthesis into a single professor-facing software proof-of-concept objective.

The professor verification/approval activity is **not a separate project stage**. It is the intended use of this integrated checkpoint: demonstrate the software mechanism, show the evidence and limitations, and present the research conclusion that justifies proceeding to hardware verification.

## 2. Methodology being locked

The research method is now treated as one continuous chain:

1. Define event and dependency semantics.
2. Define evidence-bounded fault association.
3. Define a deterministic, bounded recovery policy.
4. State safety, identity, dependency, release, termination, and resource obligations.
5. Freeze a reproducible experimental protocol.
6. Implement a minimal zero-heap host reference.
7. Re-verify build, tests, deterministic replay, matched inputs, trace metadata, and evidence boundaries.
8. Expose the end-to-end mechanism through a software demonstrator.
9. Present the mechanism and evidence with explicit non-claims.
10. Use the resulting software proof of concept as the basis for target-MCU validation.

Gates A-E remain frozen and normative. This checkpoint does not amend their semantics.

## 3. Software proof of concept

The demonstrator makes the following sequence visible:

**Fault observation -> context/history -> association -> event quarantine -> bounded recovery decision -> recovery action -> verification -> release/degrade/escalate -> trace explanation**

The UI is deliberately a presentation layer. The ISO C11 reference implementation and the committed experiment harness remain the authoritative software evidence.

## 4. Re-verification status

The locked software evidence consists of:

- Gates A-E: complete at their declared semantic/design/protocol levels.
- Reference implementation: host checkpoint complete.
- K.1: Windows/MSVC build and CTest 2/2 verified; 70 matched W01-W14 × P0-P4 runs; five declared harness checks passed.
- K.2: regenerated corpus inspected at run/trace level; no concrete corpus-generation, serialization, or runtime defect identified.
- K.3: evidence-bounded synthesis completed.
- Host evidence boundary: explicit and preserved.
- W09/W10 capacity-confound qualification: preserved.
- P0-P3 clean-quarantine ablation limitation: preserved.

The software demonstrator does not replace these checks; it makes their underlying mechanism understandable in a live presentation.

## 5. What can be demonstrated to a professor

The software package can demonstrate:

- why the fault-associated event is identified and quarantined;
- that quarantine is a retained, non-executable state rather than deletion;
- how local fault context and bounded recovery history affect the decision path;
- that the recovery action set is finite and bounded;
- that verification precedes release;
- that unrelated work is conceptually preserved when dependency/ordering conditions permit;
- that the implementation is statically bounded and zero-heap at the reference level;
- that the complete research chain is reproducible at the host/reference layer.

## 6. What must not be claimed

The software proof of concept does not prove:

- STM32U575 RAM/Flash usage;
- MCU timing or latency;
- MPU behavior on target;
- interrupt/peripheral-driver behavior;
- electrical fault behavior;
- physical recovery;
- energy impact;
- statistical superiority;
- external validity;
- final novelty;
- patentability.

## 7. Novelty showcase

The defensible novelty position is a **specific integrated-mechanism hypothesis**, not a declaration that the project is already novel.

The proposed combination is:

> a deliberately small, deterministic, zero-heap recovery policy for cooperative/event-driven MCU firmware that uses local fault context and short recovery history to choose a bounded recovery action while explicitly quarantining the fault-associated event and preserving unrelated valid event-driven service when dependency and ordering conditions allow it.

The individual ingredients are not claimed as novel. The research question is whether this integrated mechanism produces a useful measurable trade-off under constrained embedded conditions.

The software demonstrator therefore showcases the **mechanism and research logic**. Hardware experiments are required to test the remaining target-specific claims.

## 8. Ablation limitation remains locked

The current reference implementation applies exact-event quarantine through `runtime_start_fault()` across P0-P4. Therefore P0-P3 are not clean quarantine ablations and remain marked `ablation_contract_valid=0`.

This limitation is intentionally visible. It must not be hidden or redefined merely to make the proposed mechanism appear stronger.

If causal ablation evidence is later required, the baseline containment semantics must be specified as a separate research decision before implementation changes.

## 9. Capacity limitation remains locked

W09 and W10 are capacity-confounded under the frozen host protocol. They remain valid as explicit boundary/capacity scenarios but must not be interpreted as unconstrained policy comparisons.

## 10. Hardware handoff condition

The software phase is considered ready for a hardware-validation proposal when:

- the demonstrator is runnable;
- the Gates A-E chain is documented;
- host/reference re-verification remains reproducible;
- limitations are explicit;
- the professor-facing conclusion distinguishes software proof of concept from hardware proof.

The next research objective after this lock is therefore **target-MCU validation**, not another redesign of the research idea.

## 11. Final software-phase conclusion

The project has moved beyond an abstract idea: it now has a frozen research specification, a bounded executable host reference, reproducible host evidence, and a software demonstrator that exposes the proposed end-to-end mechanism.

The correct conclusion is not that hardware performance or novelty has already been proven.

The correct conclusion is:

> **The software proof of concept is sufficiently specified, implemented, reproducible, and evidence-bounded to justify testing the same mechanism on the intended MCU, while retaining explicit safeguards against overclaiming novelty or hardware performance.**

This is the methodology lock for the software phase.
