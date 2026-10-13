# ACTIVE NEXT-CHAT PROMPT — K.11
## Final Software Synthesis & Hardware-Validation Handoff Protocol

**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Canonical branch:** `exp`  
**Active checkpoint:** K.11 (Subject to ChatGPT Prior Approval of K.10.4)  
**Checkpoint authority:** ChatGPT  
**Repository execution agent:** Antigravity only when explicitly invoked by ChatGPT  

> **Checkpoint Status & Transition Gate:**  
> K.10, K.10.1, K.10.2, and K.10.3 are formally approved and closed. K.10.4 implementation and research synthesis are complete, but K.10.4 remains **PENDING FORMAL CHATGPT APPROVAL**. ChatGPT must review the K.10.4 report (`research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md`) and grant explicit approval before K.11 execution is initiated. Do not sync `main`.

---

## 1. Startup and Integrity Verification

Before initiating K.11 work:

1. Confirm starting branch is `exp` based on the approved canonical HEAD.
2. Confirm `main` HEAD is `0bff0b32e24dccb1b94c20b6e305cb918a49ec6f` and remains untouched.
3. Preserve the original checkout's local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38`.
4. Verify the five protected Git blob SHAs:
   - `reference/src/ref_runtime.c`: `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`
   - `reference/include/ref_runtime.h`: `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`
   - `research/phase1_reference_implementation_design.md`: `b7fb120692756740bc969aa3412acaa89320c188`
   - `research/phase2_k9_methodology_lock.md`: `bd75f2c2c21c3964ec15b338eea99b386eff7aec`
   - `research/phase2_k9_2_p4_advantage_novelty_design.md`: `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d`
5. Inspect mandatory continuity documents:
   - `PROJECT_MANUAL.md`
   - `PROJECT_STATE.md`
   - `CURRENT_HANDOFF.md`
   - `DECISION_LOG.md`
   - `research/PART_II_CHAT_PLAN.md`
   - `research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md`
   - `research/chat_records/chat_k10_4_record.md`

---

## 2. K.11 Objective and Scope

Checkpoint K.11 synthesizes the completed K.10.x research campaign into the definitive software research closure package and establishes the target-MCU hardware-validation specification.

### Required Work:
1. **Software Research Synthesis:**
   - Package final architecture, mechanism, empirical evidence, and prior-art distinction into a coherent, publication-oriented results structure.
   - Enforce all empirical boundaries: 400 matched executions, bounded advantages in CF04/CF07 and CF05, shared quarantine preservation across P0–P4, baseline CF16 win (P2 1 attempt vs P4 3 attempts), capacity confounds (`QMAX=16`, `EPMAX=1`), and no universal superiority claims.
   - Enforce prior-art boundaries: single-reference anticipation refuted across PA-01–PA-10; C1 multi-reference combination risk unresolved; integrated contract framed as an evidence-bounded research hypothesis.
2. **Target-MCU Validation Specification:**
   - Define exact physical hardware requirements for the STM32U575ZI / NUCLEO-U575ZI-Q target platform.
   - Specify bare-metal toolchain (ARM GCC / Clang), CMSIS startup, clock tree, and peripheral driver integration requirements.
   - Specify MPU region configuration for execution isolation and fault containment.
   - Specify physical fault injection protocols (I2C/SPI bus disturbance, clock stretching timeouts, NACK stimulus) and physical instrumentation (logic analyzer, oscilloscope).
   - Formulate unambiguous hardware validation success criteria and falsification conditions.
3. **Professor-Facing Software Closure:**
   - Prepare the academic narrative and clear software-level closure summary for professor review prior to K.12 demonstration productization.

---

## 3. Frozen Boundaries and Restrictions

The following restrictions remain in full effect:
- **NO HARDWARE EXECUTION:** K.11 defines hardware specifications and protocols only. No physical MCU flashing, hardware testing, or physical measurements are authorized.
- **NO RUNTIME REDESIGN:** Do not alter Gates A–E, `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, `policy_decide()`, or `runtime_apply_policy()`.
- **NO EXPERIMENT RERUNS:** Do not rerun the 400-execution K.10 matrix.
- **NO LEGAL OPINIONS:** Do not claim legal novelty, non-obviousness, inventive step, or patentability.
- **NO `main` SYNCHRONIZATION:** `main` remains unsynchronized until K.12 demonstration and final software audit are complete.

---

## 4. Required Deliverables for K.11

1. Main report: `research/phase2_k11_final_software_synthesis_and_hardware_handoff.md`
2. Chat record: `research/chat_records/chat_k11_record.md`
3. Updated continuity artifacts (`CURRENT_HANDOFF.md`, `PROJECT_STATE.md`, `DECISION_LOG.md`, `research/PART_II_CHAT_PLAN.md`, `NEXT_CHAT_PROMPT.md` for K.12).