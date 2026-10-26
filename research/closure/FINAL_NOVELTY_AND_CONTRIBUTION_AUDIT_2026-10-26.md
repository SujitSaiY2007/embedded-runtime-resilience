# Final Novelty and Meaningful Contribution Audit

**Project:** Embedded Runtime Resilience  
**Date:** 2026-10-26  
**Branch:** `main`  
**Status:** Final evidence-bounded technical audit for the current project scope  
**Authoritative records reviewed:** frozen K.10 results; `reference/src/ref_runtime.c` and header; `research/manuscript/EVIDENCE_LEDGER.md`; `research/manuscript/OPEN_ISSUES.md`; current manuscript and reference audit; Phase 2 hardware closure; Phase 4 prior-art conclusion; Phase 5 UI/hardware conclusion; prior-art investigation notes.  
**Scope rule:** this audit does not modify the protected runtime, re-run the frozen 400-execution campaign, repeat hardware experiments, or make a legal novelty/patentability determination.

## 1. Final verdict

The project has a **meaningful, technically defensible, bounded research contribution** in implementing and evaluating a small deterministic recovery-policy runtime, and in documenting where the integrated policy differs from the tested in-house variants. The evidence does **not** establish that P4 is universally superior, that any individual mechanism is new, that the complete combination is definitively novel, or that it is patentable.

**Final classification:**
- **Meaningful engineering/research contribution:** supported.
- **Attributable P4 advantages over the current in-house comparison policies:** supported for selected frozen scenarios, subject to the documented runtime defects and missing raw CSV traces.
- **General superiority or state-of-the-art superiority:** not established.
- **Combination-level research novelty:** plausible hypothesis, unresolved.
- **Legal novelty, non-obviousness, freedom to operate, and patentability:** not determined.

This is the final technical audit for the current evidence set. “Final” means the current project is being closed with a calibrated conclusion; it does not convert known evidence gaps into completed work.

## 2. What the work meaningfully contributes

### Contribution A — A concrete, statically bounded C recovery runtime

The reference runtime implements finite capacities for queued/quarantined events, dependencies, recovery episodes, and trace records. Source inspection found no `malloc`, `calloc`, `realloc`, or `free` calls in the protected runtime files. This is useful for deterministic embedded-runtime design and review.

**Strength:** meaningful implementation contribution.  
**Boundary:** no claim of measured MCU timing, stack high-water mark, energy, or complete resource overhead. Host `sizeof` values are not MCU measurements. The runtime also has documented edge cases: a full-queue release can overrun the queue in a release build, an 8-bit generation counter rejects admission after slot reuse reaches its limit, trace recording stops at its fixed capacity, and invalid-target actions can leave an episode open. These must remain visible in the manuscript and should not be hidden by the positive results.

### Contribution B — A five-policy comparative framework

P0–P4 are implemented as in-house policy variants in the same C reference runtime. This enables controlled comparison under common event models and scenarios. It is not a reproduction of the algorithms in Phoenix, KARMA, shadow drivers, microreboot, or other published systems.

**Strength:** a useful comparative experimental design and artifact.  
**Boundary:** P0–P3 are author-constructed baselines/ablations; the frozen record flags the ablation contract as invalid for P0–P3 because exact-event quarantine is shared across all variants. Therefore results do not isolate quarantine as a P4-only effect, and they do not establish superiority over independent published methods.

### Contribution C — Evidence-bounded policy behavior under selected adversarial cases

The frozen report records three clearest attributable distinctions:
- **CF04 — association ambiguity:** P4 fails closed and closes the episode where P0–P3 return stale-reference outcomes and leave it active.
- **CF05 — fault during recovery:** P4 terminates within its bounded ladder where P2/P3 remain active under the reported repeated-recovery-fault sequence.
- **CF07 — subsequent fault after an ambiguous episode:** P4 can process the later fault while P0–P3 are blocked by an unclosed episode.

These are valid *within the frozen model and tested policy implementations*. They are not evidence that every P4 design would outperform every alternative. In particular, source inspection identifies an invalid-target episode-leak path in the shared runtime that helps explain CF04/CF07; fixing that defect could narrow the measured advantage. CF05 supports bounded termination against the tested variants, not a general proof that P4 is safest.

**Counterevidence is part of the contribution:** seven families are reported as behaviorally identical across all five variants, and in CF16 P2 succeeds in one attempt while P4 uses three. Attempt count is not measured wall-clock latency or energy.

### Contribution D — A narrow physical MCU/sensor demonstration

User-observed STM32L476RG + BME280 debugger evidence records a controlled wrong-address I²C NACK (`E_NACK=-1`) followed by a successful fresh BME280 chip-ID read (`0x60`) and release for P1 and P4 in one policy comparison run. P0, P2, and P3 reached terminal/non-pass outcomes. Five control trials also read back `0x60` after the controlled absent-address NACK without a full `iinit()` call between the probe and read.

**Strength:** physical proof-of-concept evidence that selected firmware recovery paths can interact with a real I²C sensor and verify a subsequent read.  
**Boundary:** this is not stuck-SDA/SCL recovery, not 80 physical fault injections, not five independent policy repetitions, and not an MCU performance profile. The exact flashed binary is not hash-linked to the source; the full 80-entry matrix was not independently exported. The control does not exclude all local transaction-abort/flag cleanup.

### Contribution E — Evidence provenance and honest separation of demonstration paths

The project distinguishes the software path (browser UI → Python bridge → C virtual system/reference runtime) from the physical path (STM32 firmware/debugger → sensor NACK/recovery/readback). That separation prevents a UI simulation from being presented as a live physical-board trace.

**Strength:** reproducibility-oriented documentation and claim discipline.  
**Boundary:** full live browser-to-physical-MCU control/trace integration is not established by the current evidence and must not be claimed as complete.

## 3. Novelty audit against prior art

### Established prior art — not novelty claims

The following mechanisms are established independently or in adjacent domains:
- Peripheral fault recovery, checkpointing, and rollback (Phoenix).
- Handling intermittent asynchronous peripheral operations and peripheral-state consistency (KARMA).
- Peripheral-state restoration after power interruptions (RESTOP).
- Driver/component recovery and fine-grained restart (shadow drivers and microreboot).
- Fault containment, peripheral reinitialization, reset policies, and escalation in other system architectures, including the prior-art patent record US8510592B1.
- Selective robustness of hardware-abstraction-layer peripheral accesses in mixed-criticality systems (SeRoHAL).
- Runtime monitoring/fault disambiguation, embedded fault tolerance, bounded/static state, retries, resets, degradation, and event queues as individual techniques.

Additional adjacent literature checked for this audit includes PASAN (peripheral access concurrency bugs in bare-metal applications), host-compiled fault-injection approaches for embedded firmware, and recent embedded firmware fault-localization research. These works do not automatically anticipate this runtime, but they show why a broad claim such as “first event-based peripheral recovery” would be indefensible.

### Narrow combination-level hypothesis

The only defensible candidate distinction is the **specific implementation and evaluation of a combined mechanism** with:
1. caller-supplied fault-to-event association precision;
2. context and short attempt-history inputs to a finite action ladder;
3. statically bounded/zero-heap runtime state;
4. event-level quarantine/retention and dependency/order-aware handling;
5. verification before release or bounded terminal escalation; and
6. deterministic traceability of decisions and outcomes.

The search conducted is **not a systematic review** and has not completed claim-by-claim mapping of all relevant patents and publications. The candidate integration remains **unresolved, not proven novel**. A multi-reference obviousness/recombination argument remains plausible. The fact that no exact match was found in the searched set is not proof that none exists.

### Novelty matrix

| Claim or mechanism | Final finding | Why |
|---|---|---|
| Peripheral recovery/reinitialization | Established | Direct prior art |
| Retry, finite attempts, escalation/degradation | Established | Common recovery mechanisms |
| Zero heap/static bounded state | Established practice | Engineering constraint, not standalone novelty |
| Event queue and dependency/order handling | Established in adjacent systems | Cannot be claimed alone |
| Quarantine/background event preservation | **Shared in this implementation** | Frozen evidence shows it across P0–P4 |
| Context/history-aware recovery | Broadly established | Only the exact integration could distinguish |
| Fail-closed behavior when association is not exact | Attributable implementation distinction in current policy set; prior-art status unresolved | CF04/CF07 plus source behavior; related mechanisms exist |
| Bounded termination during repeated recovery faults | Attributable distinction over P2/P3 in CF05 | Limited to tested baselines and fault schedule |
| Whole combined method is new | Unresolved | Search is not exhaustive; combination challenge plausible |
| Patentability / freedom to operate | Not assessed legally | Requires qualified, jurisdiction-specific counsel |

## 4. Final claim-to-evidence and validity controls

| Proposed manuscript claim | Status | Required wording boundary |
|---|---|---|
| Frozen host campaign contains 400 executions | Supported by frozen report | Say 16 families × 5 policies × 5 repetitions; raw CSV/trace outputs are absent, so independent per-run verification is limited |
| P4 closes all 16 reported recovery episodes | Supported as reported in frozen table | Attribute only to this frozen model/campaign; retain report inconsistencies and do not imply universal safety |
| P4 is better than P0–P3 | Too broad | Say selected advantages in CF04, CF05 and CF07, with trade-offs and shared mechanisms |
| Quarantine is P4's unique contribution | Rejected | Quarantine is shared by P0–P4 |
| P4 is more efficient | Rejected | CF16 reports P2 at one attempt and P4 at three; no time/energy measurement |
| Hardware confirms policy-selected recovery | Partially supported | One policy comparison: P1/P4 pass; P0/P2/P3 terminal; controlled address NACK only |
| Five hardware trials validate P4 reliability | Rejected | Five trials are the no-full-initialization NACK control, not five independent policy comparisons |
| 80 hardware contexts were executed physically | Rejected | 80 entries are decision-matrix records, not 80 physical fault injections |
| Software UI is integrated live with the MCU | Not established | Describe virtual/software and recorded hardware paths separately |
| Complete combination is novel/patentable | Not established | No “first,” “unprecedented,” “proven novel,” “non-obvious,” or “patentable” claims |

## 5. Reference audit outcome

The manuscript bibliography contains **16 references, 12 journal articles (75.0%) and four conference papers**. The missing DOI for Swift et al., “Recovering Device Drivers,” has been resolved to **10.1145/1189256.1189257** and added to the draft. Metadata for the 16 references was checked against publisher, proceedings, DOI, or institutional records in the final pass. Full-text/page-level support for every individual sentence is not yet verified; this remains a pre-submission requirement. The four conference comparators should be retained rather than deleted to manipulate the ratio.

The prior-art search additionally examined the USENIX Phoenix record and paper, RESTOP full text, US8510592B1, SeRoHAL, PASAN, and other related sources. The bibliography is not the complete prior-art universe; patent families and claim scope still need qualified review if legal conclusions are sought.

## 6. Final meaningful contribution statement for the paper

> We implement and evaluate a statically bounded, zero-heap C recovery runtime with five policy variants for event-driven peripheral-fault workloads. In the frozen deterministic host/reference campaign, the integrated policy exhibits bounded, attributable advantages over the tested in-house variants in selected ambiguous-association and repeated-recovery-fault scenarios, while sharing event-quarantine behavior with the baselines and incurring a higher attempt count in at least one case. A controlled STM32L476RG/BME280 address-NACK demonstration provides narrow physical evidence of selected recovery and readback paths. These results establish a meaningful engineering and comparative-evaluation contribution, but do not establish universal superiority, a complete live UI-to-MCU system, or definitive scientific/legal novelty.

## 7. Final decision and closure

**Decision:** close the current novelty/contribution audit with the bounded classification above. Do not rerun the frozen 400-execution campaign or repeat hardware experiments as part of this audit. Do not change protected runtime or frozen results to strengthen the story. Keep the known runtime defects, missing raw CSVs, hardware provenance limitations, and unresolved literature/patent scope explicit.

**No further novelty conclusion is warranted from the current evidence.** Any later change to the runtime, corrected campaign, new baseline, systematic literature review, or patent analysis must be a separately versioned work package and must preserve this audit as the conclusion for the present evidence set.

## 8. Sources checked or revisited

- Phoenix — USENIX: https://www.usenix.org/conference/atc15/technical-session/presentation/smith
- KARMA — proceedings PDF: https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf
- Recovering Device Drivers — DOI 10.1145/1189256.1189257; related USENIX record: https://www.usenix.org/conference/osdi-04/recovering-device-drivers
- Microreboot — USENIX: https://www.usenix.org/conference/osdi-04/microreboot%E2%80%94technique-cheap-recovery
- RESTOP — full text: https://pmc.ncbi.nlm.nih.gov/articles/PMC5795800/
- SeRoHAL — Technical University of Munich: https://portal.fis.tum.de/en/publications/serohal-generation-of-selectively-robust-hardware-abstraction-lay/
- PASAN — project/publication page: https://www.cse.iitd.ernet.in/~viresh/publication/2021-usenix-pasan/
- US8510592B1 — PCI error resilience: https://patents.google.com/patent/US8510592/en
- Embedded dependability survey (2024): https://doi.org/10.1109/ACCESS.2024.3509633
- Manuscript reference and evidence ledgers: `research/manuscript/REFERENCE_AUDIT.md`, `research/manuscript/EVIDENCE_LEDGER.md`
