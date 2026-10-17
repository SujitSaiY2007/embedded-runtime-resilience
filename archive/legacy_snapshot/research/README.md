# Research Library and Evidence Index

This directory contains the normative design gates, experimental method and results, final research interpretation, hardware handoff, and checkpoint history. Use this index to navigate; do not infer current status from the chronological order of old files.

## Research lifecycle

### 1. Problem framing and design foundation
- [Research-space map](phase0_research_space_map.md)
- [Event model](phase1_event_model.md)
- [Gate A — event model](phase1_gateA_event_model_final.md)
- [Gate B — fault model](phase1_gateB_fault_model_final.md)
- [Gate C — recovery policy](phase1_gateC_recovery_policy_final.md)
- [Gate D — formal properties](phase1_gateD_formal_properties_final.md)
- [Gate E — experimental protocol](phase1_gateE_experimental_protocol_final.md)
- [Reference implementation design](phase1_reference_implementation_design.md)
- [Software demonstrator methodology lock](phase1_software_demonstrator_methodology_lock.md)

### 2. Frozen method and results
- [K.9 methodology lock](phase2_k9_methodology_lock.md)
- [K.9.2 P4 advantage/novelty investigation design](phase2_k9_2_p4_advantage_novelty_design.md)
- [K.8 matched-baseline validation](phase2_k8_matched_baseline_validation.md)
- [K.10 frozen P0–P4 results](phase2_k10_p4_advantage_novelty_results.md)

### 3. Adversarial review and conclusion
- [K.10.1 adversarial distinction review](phase2_k10_1_adversarial_distinction_review.md)
- [K.10.2 single-reference anticipation review](phase2_k10_2_single_reference_anticipation_review.md)
- [K.10.3 multi-reference combination review](phase2_k10_3_multi_reference_combination_review.md)
- [K.10.4 final technical distinction and conclusion](phase2_k10_4_final_technical_distinction_and_research_conclusion.md)

### 4. Software demonstrator and future hardware
- [K.11 final software synthesis and hardware handoff](phase2_k11_final_software_synthesis_and_hardware_handoff.md)
- [K.12 professor-facing software demo and final audit](phase2_k12_professor_facing_software_demo_and_final_audit.md)
- [Main-branch integration audit](main_branch_readiness_audit.md)
- [Prior-art investigation](novelty_investigation.md)
- [Deep prior-art attack / topic freeze](deep_prior_art_attack_topic_freeze.md)

### 5. References used and prior-art source inventory
- [References Used folder](references_used/README.md) — consolidated register reconstructed from canonical research reports and checkpoint records.
- [Reference register](references_used/REFERENCE_REGISTER.md) — source records, relevance, and verification status.
- [Counting and verification notes](references_used/COUNTING_AND_VERIFICATION.md) — current inventory counts and explicit limits on what can be claimed about the full-month total.

### 6. Historical provenance
- [Checkpoint records](chat_records/) — original K.1–K.12 chat/checkpoint records retained for auditability.
- [Part-II checkpoint plan](PART_II_CHAT_PLAN.md) — roadmap and closure record; read its final status first.
- [Post-K.10 review plan](phase2_post_k10_review_plan.md).

## Evidence discipline

- The C runtime and frozen Gates A–E define the implementation/method contract.
- The K.10 report is the historical result record; do not rewrite it to make narratives agree.
- The K.10.4 report gives the final evidence-bounded interpretation.
- Exact-event quarantine is shared across P0–P4; do not claim it as P4-exclusive.
- P4's measured advantages are case-specific; no universal superiority claim.
- CF01's qualitative outcomes are usable, but its P2 attempt count is omitted from comparative claims due to a source-table/narrative conflict and unavailable raw records.
- QMAX=16 and EPMAX=1 are relevant resource-capacity limits.
- Host/reference results are not physical MCU evidence.
- Legal novelty, non-obviousness and patentability are not established by this repository.

## Citation practice

For any future report, cite the exact file and relevant section/table, include the repository commit used, and distinguish frozen observations from interpretation. The eventual standalone report should be generated from these linked primary sources, not by copying this index alone.
