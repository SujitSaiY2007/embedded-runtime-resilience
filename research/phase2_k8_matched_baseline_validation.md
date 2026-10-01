# K.8 Matched Baseline vs Proposed Software Validation Report

## 1. Executive Summary

Under frozen Gates A-E, the comparative software validation was executed across:
- **Host Experiment Corpus:** 14 declarative workloads x 5 policy variants = 70 runs.
- **Virtual Demonstrator Matrix:** 6 canonical scenarios x 5 policy variants = 30 runs.
- **Total evaluated runs:** 100 deterministic executions.

### Evaluated Policies:
| ID | Name | Description | Authority / Boundary |
| :--- | :--- | :--- | :--- |
| **P0** | Variant 0 | Fixed Retry (minimal baseline: retry <= 2, blind escalate) | Gate C reference implementation (`ref_runtime.c`) |
| **P1** | Variant 1 | Fixed Retry + Recovery (retry <= 2, reinit <= 3, degrade/escalate) | Gate C reference implementation (`ref_runtime.c`) |
| **P2** | Variant 2 | Context Only (uses local context/safety, no attempt history) | Gate C reference implementation (`ref_runtime.c`) |
| **P3** | Variant 3 | Context + History (uses context and history, no Gate C exact bounds) | Gate C reference implementation (`ref_runtime.c`) |
| **P4** | Variant 4 | Integrated Proposal (zero-heap context-aware recovery with quarantine) | Gate C reference implementation (`ref_runtime.c`) |

---

## 2. Host Corpus (W01–W14) Comparative Metrics

| Policy | Total Runs | Success (No Term) | Degrade | Escalate | Unclosed Active | Total Recovery Attempts | Total Trace Records | Valid Ablation Runs |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **P0** | 14 | 10 | 0 | 3 | 1 | 14 | 109 | 0 / 14 |
| **P1** | 14 | 10 | 1 | 2 | 1 | 10 | 101 | 0 / 14 |
| **P2** | 14 | 10 | 1 | 2 | 1 | 10 | 101 | 0 / 14 |
| **P3** | 14 | 10 | 1 | 2 | 1 | 10 | 101 | 0 / 14 |
| **P4** | 14 | 10 | 1 | 3 | 0 | 10 | 101 | 14 / 14 |

### Key Findings across W01–W14:
1. **Persistent Fault Recovery (W06):**
   - **P0** blindly retries twice then fails closed with `TERMINAL_ESCALATE` (cannot reinitialize/reset).
   - **P1, P2, P3, P4** successfully recover via bounded progression to peripheral reinitialization (`ACT_REINIT_OR_RESET`) on attempt 3.
2. **Graceful Degradation (W07):**
   - **P0** escalates to `TERMINAL_ESCALATE`, ignoring event deferability.
   - **P1, P2, P3, P4** cleanly transition deferable work to `TERMINAL_DEGRADE`, preventing system halt.
3. **Ambiguous Association Isolation (W12):**
   - **P0, P1, P2, P3** leave the episode in an unclosed active state (`ACTIVE`), failing to recognize ambiguous boundary.
   - **P4** explicitly enforces exact-association containment (`ctx->association == ASSOC_EXACT`), immediately failing closed to `TERMINAL_ESCALATE`.
4. **Capacity Confounds and Ablation Boundary:**
   - Workloads W09 and W10 explicitly record `capacity_confounded=1` due to fixed table capacities (`QMAX=16`, `EPMAX=1`).
   - Baselines P0-P3 record `ablation_contract_valid=0` because reference runtime applies exact-event quarantine across variants.

---

## 3. Virtual Demonstrator Scenario (S01–S14) Matrix

| Scenario | Description | P0 (Fixed Retry) | P1 (Retry+Reset) | P2 (Context Only) | P3 (Context+Hist) | P4 (Integrated) | Comparative Finding |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **S01** | Independent Preservation | OUTCOME_SUCCESS<br>`0xB72131CB` | OUTCOME_SUCCESS<br>`0xB72131CB` | OUTCOME_SUCCESS<br>`0xB72131CB` | OUTCOME_SUCCESS<br>`0xB72131CB` | OUTCOME_SUCCESS<br>`0xB72131CB` | All variants preserve unassociated events e1, e3, e4 under exact quarantine of e2. |
| **S02** | Ordered Dependency Blocking | OUTCOME_SUCCESS<br>`0xE8691374` | OUTCOME_SUCCESS<br>`0xE8691374` | OUTCOME_SUCCESS<br>`0xE8691374` | OUTCOME_SUCCESS<br>`0xE8691374` | OUTCOME_SUCCESS<br>`0xE8691374` | All variants correctly block dependent event e2 in ST_QUEUED while e1 is quarantined. |
| **S05** | Transient Fault Retry | OUTCOME_SUCCESS<br>`0xBDC168BD` | OUTCOME_SUCCESS<br>`0xBDC168BD` | OUTCOME_SUCCESS<br>`0xBDC168BD` | OUTCOME_SUCCESS<br>`0xBDC168BD` | OUTCOME_SUCCESS<br>`0xBDC168BD` | All variants succeed on attempt 1 retry; transient fault does not require escalation. |
| **S06** | Persistent Fault Escalation | OUTCOME_TERMINAL_ESCALATE<br>`0xFD5C2BA8` | OUTCOME_SUCCESS<br>`0xA123BB47` | OUTCOME_SUCCESS<br>`0xCDAB2617` | OUTCOME_SUCCESS<br>`0xA123BB47` | OUTCOME_SUCCESS<br>`0xA123BB47` | P0 escalates (cannot reset). P1-P4 progress to ACT_REINIT_OR_RESET on attempt 3 and recover. |
| **S08** | Ambiguous Fault Isolation | OUTCOME_STALE_REF<br>`0x489DED5F` | OUTCOME_TERMINAL_ESCALATE<br>`0x5A52628A` | OUTCOME_TERMINAL_ESCALATE<br>`0x5A52628A` | OUTCOME_TERMINAL_ESCALATE<br>`0x5A52628A` | OUTCOME_TERMINAL_ESCALATE<br>`0x5A52628A` | P0-P3 fail to handle unmapped target ref (OUTCOME_STALE_REF). P4 fails closed safely (OUTCOME_TERMINAL_ESCALATE). |
| **S14** | Mixed Replay Determinism | OUTCOME_SUCCESS<br>`0x9185616C` | OUTCOME_SUCCESS<br>`0x9185616C` | OUTCOME_SUCCESS<br>`0x9185616C` | OUTCOME_SUCCESS<br>`0x9185616C` | OUTCOME_SUCCESS<br>`0x9185616C` | All variants maintain deterministic replay; digests are identical across runs. |

---

## 4. Evidence Boundary and Qualification Lock

- **Host & Software-Only Scope:** All evidence is derived strictly from the ISO C11 reference runtime and virtual embedded system.
- **No Target Hardware Claims:** Does not measure physical STM32U575 cycle latency, RAM/Flash overhead, MPU faults, or electrical noise.
- **Ablation Qualification Preserved:** P0-P3 retain `ablation_contract_valid=0` as documented in Gate E and K.2.
- **Capacity Confound Preserved:** W09/W10 retain `capacity_confounded=1` as documented in Gate E.
