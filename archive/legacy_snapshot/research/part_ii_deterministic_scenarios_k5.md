# K.5 — Deterministic Scenario Definitions

Status: Declarative definitions only; K.6 implements them.

## Scenario model

Each scenario fixes initial virtual peripheral state, workload/event admission sequence, dependencies, fault injection point, fault class, evidence/association level, deterministic recovery outcome schedule and expected runtime evidence class.

Expected recovery action is a verification target derived from the frozen C policy, not simulator logic.

## S01 — Independent preservation
I2C fault target + independent I2C event + independent UART event. Fault: I2C NACK, EXACT_EVENT. Expected: target quarantined; independent valid work remains selectable. Evidence: EventRef continuity and preservation trace.

## S02 — Ordered blocking
Predecessor + ordered successor + independent UART work. Fault predecessor by I2C timeout, EXACT_EVENT. Expected: successor blocked until acceptable predecessor state; independent work may execute. Evidence: dependency-safe blocking.

## S03 — Coupled containment
Two members of one coupled transaction. First member fails, EXACT_EVENT. Expected: second member not executed while coupled validity is unsafe. Evidence: no invalid partial transaction.

## S04 — Shared peripheral, non-causal event
Multiple events use I2C0 but have no dependency. Fault one exact event. Expected: same-peripheral events are not automatically quarantined. Evidence: no attribution leakage.

## S05 — Retry success
Exact I2C fault. First recovery retry succeeds. Expected: bounded retry followed by verification/release. Evidence: action index, verification and EventRef continuity.

## S06 — Retry/retry/reinit
Exact I2C fault. First two recovery attempts fail; reinitialization/reset succeeds. Expected: T1 -> T2 -> T3 within four-action bound. Evidence: bounded attempt progression.

## S07 — Terminal degradation
Deferable service with safe degradation. Persistent fault. Expected: terminal DEGRADE without recovery re-entry. Evidence: terminal state and unrelated-work preservation.

## S08 — Terminal escalation / ambiguous association
Critical or ambiguous case. Association may be UNKNOWN/PERIPHERAL_ONLY. Expected: no fabricated exact target; terminal outcome follows frozen policy. Evidence: association precision bound.

## S09 — Queue capacity boundary
Admit QMAX events, then one additional event. Expected: bounded queue-full outcome and no hidden expansion. Evidence: capacity flag.

## S10 — Quarantine/episode capacity boundary
Attempt multiple simultaneous fault episodes. Expected: EPMAX=1 produces OUTCOME_EPISODE_FULL; no hidden second episode.

## S11 — Stale EventRef
Reuse a slot after terminal completion and present the old generation. Expected: old reference fails closed and new generation remains distinct.

## S12 — Association precision matrix
Four cases: EXACT_EVENT_TRANSACTION, SERVICE_ONLY, PERIPHERAL_ONLY, UNKNOWN_AMBIGUOUS. Expected: target specificity never exceeds evidence.

## S13 — Criticality/degradability matrix
Repeat representative cases for CRITICAL, NORMAL and DEFERABLE. Expected: criticality/degradability affect policy inputs but never bypass dependency/quarantine safety.

## S14 — Mixed integrated workload
Combine independent work, ordered dependency, coupled transaction, exact peripheral fault and deterministic recovery schedule. Expected: independent valid work can progress, required dependents remain blocked, coupled work remains safe, and the actual C runtime produces the recovery/trace result.

## Replay identity

Each run is keyed by:
scenario_id + workload_id + fault_schedule_id + policy_variant + runtime_build_id

Repeated execution from the same key must produce the same runtime input sequence and equivalent authoritative trace.

## Scenario non-claims

Later execution establishes only software/host demonstrator behavior. It does not establish STM32U575 hardware behavior, physical fault response, performance superiority, novelty or patentability.
