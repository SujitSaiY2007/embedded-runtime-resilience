# K.10.1 — Adversarial Prior-Art & Technical-Distinction Review

**Status:** K.10.1 research analysis complete at the documented-source level; technical distinction remains **unresolved and vulnerable to multi-reference recombination**.  
**Branch:** `exp`  
**Scope:** Technical research only; not a legal opinion or patentability assessment.  
**K.10 evidence frozen:** 16 case families × P0–P4 × 5 deterministic repetitions = 400 matched executions.  
**Protected boundaries:** Gates A–E; `reference/src/ref_runtime.c`; `reference/include/ref_runtime.h`; K.10 result/raw evidence. No experiment was rerun and no runtime or Gate semantics were changed.

## 1. Executive finding

The defensible contribution hypothesis is **not** “peripheral recovery,” “context-aware recovery,” “bounded retries,” “quarantine,” “dependency-aware scheduling,” “zero-heap execution,” or “preserving unrelated work” considered separately. Each has substantial precedent in embedded recovery, device-driver fault containment, event/message handling, real-time systems, or statically bounded embedded frameworks.

The remaining candidate distinction is narrower and conjunctive:

> In a resource-constrained, event-driven MCU reference runtime, a single statically bounded mechanism combines evidence-limited fault-to-event association (never claiming more precision than the evidence supports), retained event-level quarantine, dependency/order-aware eligibility and preservation of unrelated work, short recovery history selecting a fixed finite recovery ladder, and explicit verification/release or terminal closure, with deterministic trace evidence.

This is a **technical hypothesis**, not a finding of novelty. K.10.1 did not establish that no reference discloses the combination. The most credible attack is a multi-reference combination: embedded peripheral recovery + event/request isolation or failed-message retention + dependency-aware execution/preservation + history-based recovery selection + bounded embedded implementation. K.10.2 must test the strongest single-reference anticipation candidates individually before K.10.3 considers combinations.

## 2. Evidence boundary and project-specific evidence

K.10's result report records 400 matched executions over 16 case families, five variants P0–P4 and five deterministic repetitions. Reported differences are localized, not universal:

- CF04/CF07: P4's fail-closed handling of non-exact/ambiguous association avoids invalid stale references and unclosed episode-pool states observed in some baselines.
- CF05: P4's bounded recovery ladder terminates under repeated recovery-action faults; P2/P3 can lack a terminal outcome in the tested recovery-fault condition.
- CF02/CF14: preservation is shared across variants because exact-event quarantine is already shared in the C runtime. It must not be represented as a P4-exclusive benefit.
- CF16: P2 reaches success in one attempt in the known-persistent case while P4 uses three attempts. This is a real modeled cost/trade-off, not a physical timing ratio.
- Six of sixteen case families reportedly show no difference. Capacity confounds and ablation-validity constraints remain applicable.

Source of project evidence: [K.10 result report](phase2_k10_p4_advantage_novelty_results.md), [K.10 record](chat_records/chat_k10_record.md), and [K.9.2 locked design](phase2_k9_2_p4_advantage_novelty_design.md).

**Attribution lock:** The C runtime already applies exact-event quarantine across P0–P4. The K.10 results therefore do not establish that quarantine itself is a P4 invention or a P4-only advantage. P4-specific claims must be restricted to observed distinctions such as evidence-limited association handling and bounded recovery progression/closure where supported by the trace data.

## 3. P4 limitation/feature matrix

| ID | Technical limitation / behavior to test | Frozen specification anchor | Closest prior-art pressure | K.10 evidence / attribution | Preliminary distinction status |
|---|---|---|---|---|---|
| L1 | Resource-constrained event-driven MCU setting | Frozen topic; reference runtime | Phoenix; Karma; embedded driver recovery | Host/reference only; no target-MCU measurements | Context alone is not distinguishing |
| L2 | Fixed-capacity, zero-heap state | Gate E and C implementation constraints | Static allocation and bounded embedded frameworks are established practice | No heap claim is an implementation constraint, not novelty by itself | Weak alone |
| L3 | Fault-to-event association has explicit precision levels and cannot exceed evidence precision | Gate B; association levels exact/service/peripheral/unknown | Driver recovery, error-containment records, request/device association | CF04/CF07 are relevant to fail-closed handling; preserve exact trace evidence | Potentially relevant, requires close-reference review |
| L4 | Event identity is generation-qualified; stale references are rejected | Gate A; `EventRef={slot_id,generation}` | Generation counters/handles are common systems practice | P4 avoids some invalid stale-reference outcomes in tested cases | Weak alone; combination may matter |
| L5 | Fault-associated event is quarantined/retained rather than indiscriminately flushing all queued work | Gate A/D; retained non-executable quarantine | Failed-event queues, message quarantine, driver request queues, isolation/recovery systems | Exact-event quarantine is shared by P0–P4 in current runtime | Not P4-exclusive; combination-level only |
| L6 | Independent work can remain eligible while related/ordered/coupled work is blocked | Gate A/D; dependency classes and dispatchability predicate | Dependency-aware schedulers, fault-containment domains, selective rollback | Preservation in CF02/CF14 is shared; do not attribute to P4 alone | Plausible integration distinction, not established |
| L7 | Short recovery history changes action selection | Gate C; history/episode attributes | US10921871B2 and broader history-driven recovery control | CF01/CF05 show different outcomes and costs; P2 can win on CF16 | Established element; exact context integration unresolved |
| L8 | Fixed ladder has a finite terminal rung | Gate C: T1 retry, T2 retry, T3 reinit/reset, T4 terminal; MAX_RECOVERY_ACTIONS=4 | Retry budgets, circuit breakers, escalation ladders | CF05 supports termination under tested repeated recovery fault | Bounded escalation is common; exact composition requires comparison |
| L9 | Verification precedes release/continuation; failed recovery closes/escalates explicitly | Gates C/D; transition authority remains runtime | Recovery controllers commonly verify/reinitialize/escalate | Must be traced to exact K.10 evidence; no general superiority claim | Likely established subfeature |
| L10 | No fabricated target EventRef for service/peripheral/unknown association | Gate B; fail-closed association contract | Error-containment and request/device mapping practices | CF04/CF07 are the strongest current differentiating examples | Candidate technical distinction, needs anticipation attack |
| L11 | Deterministic trace ties fault, association, action, episode, lifecycle and outcome | Gate E; trace metadata | Runtime verification, fault monitoring, diagnostic logs | Determinism is validation quality, not inherently policy novelty | Weak alone |
| L12 | Entire mechanism is a single bounded C runtime with sole policy and transition authorities | Frozen authority split: `policy_decide()` and `runtime_apply_policy()` | Embedded runtimes, state machines, driver frameworks | Runtime is frozen; K.10.1 makes no implementation changes | Architecture may distinguish only if a reference lacks equivalent composition |

### Claim discipline

1. Do not call the complete combination “novel,” “unique,” “first,” “unanticipated,” or “patentable.”
2. Do not use “zero heap,” “bounded,” “event-driven,” “history-aware,” or “preservation” as a standalone novelty claim.
3. Do not claim all unrelated work is preserved under every condition. State the exact modeled condition and trace.
4. Do not present host/reference counts as MCU latency, RAM, Flash, energy, or electrical behavior.
5. Distinguish (a) an explicit disclosure in a source, (b) an inference needed to adapt it, and (c) a missing disclosure. Missing text in a preliminary search is not proof of absence.

## 4. Adversarial prior-art register

These are the strongest references identified or already cited by the repository's prior-art records. The summaries below are deliberately limited to what the identified source supports. K.10.2 must retrieve and inspect the full text/claims of the closest sources before making any single-reference anticipation determination.

| Ref | Source | What it puts in the attack space | What is not yet established from the source | Risk |
|---|---|---|---|---|
| PA-01 | Smith & Rixner, “Surviving Peripheral Failures in Embedded Systems,” USENIX ATC 2015, Phoenix. [USENIX source](https://www.usenix.org/conference/atc15/technical-session/presentation/smith) | Peripheral-failure recovery in resource-constrained embedded systems; checkpointing peripheral/program state and rollback after failed peripheral access. | The cited abstract does not establish the exact Gate-B evidence-precision association model, retained per-event quarantine with dependency-aware eligibility, or the exact fixed P4 ladder as one mechanism. Full paper review required. | **High** for domain/problem/recovery; medium for full combination |
| PA-02 | Branco et al., “Intermittent Asynchronous Peripheral Operations,” ACM SenSys 2019 (Karma). [Repository record](https://re.public.polimi.it/handle/11311/1125033) | Peripheral state representation, operation scheduling/recovery, peripheral roll-forward and computation rollback in bare-metal/resource-constrained intermittent systems. | The cited abstract does not show the exact fault-to-event precision rule or the K.10 event quarantine/preservation/ladder combination. | **High** for embedded peripheral/runtime recovery |
| PA-03 | US9547557B2, “Peripheral bus error containment and recovery.” [Google Patents](https://patents.google.com/patent/US9547557B2/en) | Peripheral bus fault containment, disabling a link and reinstalling a driver while the OS continues. | Different apparent platform/architecture; exact event-level association and fixed bounded event policy not established from abstract. Claims and family need inspection. | **High** for peripheral containment and continued service |
| PA-04 | US9411667B2, “Recovery after input/output error-containment events.” [Google Patents](https://patents.google.com/patent/US9411667B2/en) | Error-containment record, driver-level recovery, clearing errors and resuming an I/O link. | The abstract/snippet does not establish the complete event-driven MCU combination or evidence-limited association semantics. | **High** for error record + recovery/resumption |
| PA-05 | US8510592B1, “PCI error resilience” (referenced in the repository's prior-art work). | Policy-oriented PCI error containment, recovery routines, reinitialization/reset and escalation. | Full claim-level mapping to this project's event-level queue, bounded state and association precision has not been completed in K.10.1. | **High** for recovery policy and escalation |
| PA-06 | US10921871B2 (recovery-history-driven action selection, as recorded in the existing prior-art notes). | Prior recovery history informing a subsequent recovery action. | Exact application to peripheral fault/event association and retained dependency-aware event quarantine is not established. Exact claim and family mapping remains due. | **High** for history-conditioned selection |
| PA-07 | US10331522 / US10929373 (failed-event/resource association, retry, relationship analysis, and message quarantine, as listed in repository prior-art notes). | Potentially close event/message isolation, resource association and retry disclosures. | The precise claims, priority dates, family relationships and overlap with each L1–L12 limitation need primary-source review; do not treat these shorthand references as already verified claim charts. | **High** until primary claims reviewed |
| PA-08 | US20180365126A1 (failed-event queue, failure reason, corrective action and replay, as recorded in existing notes). | Retaining failed work and applying corrective action/replay. | MCU constraints, evidence-limited association, dependency-aware release and exact recovery ladder are not yet established. | **High** for queue/replay subcombination |
| PA-09 | US12688084 (paused event retention, failed-event queue, retry, verification and release, as recorded in existing notes). | Event retention through recovery and conditional retry/verification/release. | Full source/claims, chronology, jurisdiction and exact field applicability must be verified before reliance. | **High**; claim-level validation mandatory |
| PA-10 | Swift et al., “Recovering Device Drivers,” OSDI 2004; Herder et al., “Failure Resilience for Device Drivers” (referenced in repository notes). | Driver recovery and fault containment without assuming a peripheral failure should collapse all service. | Exact embedded cooperative-runtime semantics, Gate-B precision rule and bounded P4 ladder not established from the current citation-level record. | **Medium–high** |
| PA-11 | R2U2 and related runtime monitoring/diagnosis work; resource-constrained fault-disambiguation and trace-monitoring systems in existing notes. | Online observation, fault detection/disambiguation, temporal properties and bounded monitoring. | A monitor is not automatically a recovery policy; full combined event quarantine/recovery semantics need source-level proof. | **Medium** |
| PA-12 | AUTOSAR-style fault/event management, RTOS/MCU driver recovery, static-allocation frameworks, and safety-critical containment designs (search categories, not yet a claim-level reference set). | Standardized fault managers, retries, containment, bounded resources and event/task state transitions are likely combination ingredients. | K.10.1 has not completed a systematic standard-version/vendor-manual/OSS commit audit. | **Open search gap** |

**Source-quality caveat:** PA-05–PA-09 are candidate identifiers inherited from the project's existing notes. This checkpoint has not verified their exact claim text, legal status, priority/filing dates, or family members. They are adversarial leads, not adjudicated disclosures. K.10.2 must open each primary patent record and record the claims/paragraphs that support each mapped limitation. The existence of a patent result or an abstract is not sufficient for anticipation.

## 5. Combination attack map

The question is not whether a source uses the same project title. The question is whether its disclosed technical teachings, alone or in a plausible combination, make the proposed mechanism indistinguishable.

### 5.1 Individual limitations

- **Peripheral recovery / reset / escalation:** strongly established by Phoenix and the peripheral-bus error-containment patent family.
- **Recovery history informing action:** established as a broad concept by the cited history-driven recovery patent lead; exact MCU/runtime application remains to be inspected.
- **Event/message retention, retry, replay or quarantine:** several patent leads explicitly target failed-event queues or retained events. Do not claim event quarantine is new without claim-level comparison.
- **Dependency-aware blocking/preservation:** established in adjacent fault-containment, scheduling, and selective recovery domains; source-to-source transfer may be straightforward.
- **Static bounded memory / no heap:** conventional embedded engineering constraint, not a standalone contribution.
- **Traceability and verification:** routine in runtime monitoring and recovery control. The exact trace contract can support reproducibility, but not by itself novelty.

### 5.2 Pairwise attacks

| Combination | Strongest attack path | Preliminary assessment |
|---|---|---|
| Peripheral fault + recovery/reset/escalation | Phoenix + PA-03/PA-04/PA-05 | Very weak distinction |
| Recovery history + action selection | PA-06 + generic recovery controllers | Weak unless exact constrained event/peripheral context matters technically |
| Failed-event queue + retry/replay | PA-08/PA-09 + driver recovery | Weak |
| Quarantine + preserve unrelated service | PA-03/PA-04 + selective fault-containment/service continuity literature | Weak-to-moderate; exact event/dependency semantics require source-level review |
| Association precision + fail-closed handling | Error-containment records + explicit identity/handle validation practices | Potentially more specific, but generation handles and conservative mapping are familiar techniques |
| Bounded ladder + static memory | Embedded state machine + retry-budget/circuit-breaker patterns | Weak |
| Dependency/order-aware eligibility + retained quarantine | Queue/event scheduler + fault-containment work | Moderate only if the exact state transitions and invariants are not disclosed together |
| Verification/release + retained event | PA-08/PA-09 | Weak |
| Evidence-bounded association + retained quarantine | PA-07/PA-08/PA-09 plus driver/resource association | A central attack path; primary claims unresolved |

### 5.3 Higher-order combinations

**Attack H1 — Embedded peripheral recovery + rollback/recovery control + event isolation.**  
Phoenix and Karma make the target field and recovery context crowded. The potential distinction is not “a runtime recovers peripherals,” but whether a request/event-level quarantine and conservative association model handles ambiguous fault ownership without fabricating a target while preserving eligible unrelated work. Yet a reviewer may argue that per-event isolation is an obvious way to limit blast radius. Evidence needed: exact Phoenix/Karma design and claims, then source-level comparison of what state is rolled back versus retained.

**Attack H2 — Failed-event retention + association + retry/verification/release.**  
PA-07–PA-09 are the closest shorthand leads because their titles/notes mention failed-event queues, resource association, quarantine, replay, verification or release. If one source actually discloses association-aware event retention plus corrective action and release, the remaining distinction could collapse substantially. This is the highest-priority single-reference review for K.10.2.

**Attack H3 — History-conditioned recovery + finite ladder + static bounds.**  
History-based selection and finite retry/escalation are individually familiar. The candidate distinction would have to be a precise state-transition contract that constrains what evidence is admissible, when the target event is eligible, how the recovery episode advances, and how termination is guaranteed. K.10.1 does not establish that this composition is absent from prior art.

**Attack H4 — Dependency-aware service preservation + event quarantine + peripheral recovery.**  
This is the strongest conceptual system-level combination, but also vulnerable to obviousness/recombination reasoning: a designer recovering one peripheral has incentives to hold dependent requests while allowing independent work to proceed. The research must show a specific technical resolution of ambiguous association and bounded episode closure, not merely the expected engineering benefit of isolation.

**Attack H5 — All limitations under zero-heap C on a small MCU.**  
The target platform can constrain implementation choices but does not automatically make the logical combination distinctive. “Zero heap” should be described as an engineering constraint verified by code/build evidence, not a novel algorithmic feature. The runtime's fixed capacity can also create failure/capacity trade-offs that must be acknowledged.

### 5.4 Whole-combination attack

A plausible examiner/reviewer narrative is:

1. Start from a known embedded peripheral recovery system (Phoenix or Karma).
2. Use known error-containment/driver recovery to isolate a failed peripheral and restore service.
3. Apply known failed-event retention/quarantine and retry/verification/release to avoid replaying unsafe work.
4. Use known dependency or request association to prevent dependent work from proceeding while independent work continues.
5. Apply known recovery history and a bounded retry/reset/escalation policy.
6. Implement the state with static bounded storage for an MCU.

That narrative is **plausible and not refuted** by the evidence in this checkpoint. The strongest response hypothesis is the exact operational invariant set: association precision never exceeds evidence; no synthetic EventRef is created for broad/unknown association; quarantined work is retained but non-executable; eligibility follows frozen dependency/order rules; the fixed recovery ladder advances deterministically and terminates; release follows verification; the complete path is auditable in deterministic traces. Whether this invariant set is actually absent from the cited art remains open.

## 6. What K.10 evidence can and cannot support

| Finding | Admissible statement | Prohibited overstatement |
|---|---|---|
| CF04/CF07 ambiguity | In tested cases, P4's fail-closed path avoided specific invalid-reference/episode-pool failure modes present in some baselines | “P4 always handles ambiguity better” |
| CF05 recovery fault | In tested case conditions, P4 terminated through the bounded ladder while P2/P3 did not produce the same terminal outcome | “P4 guarantees all recovery termination in every system” |
| CF02/CF14 preservation | The implementation preserved the relevant unrelated work under these tests, but exact-event quarantine is shared across P0–P4 | “P4 uniquely preserves unrelated events” |
| CF16 | P2 used fewer modeled attempts in the known-persistent case; P4 incurred a modeled cost | “P2 is physically 3× faster” |
| 400 deterministic runs | The locked host experiment was reproducible under its stated conditions | “Statistical significance,” generalization or hardware validation |
| No single complete anticipation confirmed in K.10 report | Earlier review did not confirm a single-reference whole-combination disclosure | “No prior art exists,” “novel,” or “patentable” |

## 7. Gaps that remain open

1. **Claim-level patent chart:** obtain primary texts for PA-05–PA-09; verify titles, priority/filing dates, family, claims, relevant paragraphs and legal status.
2. **Phoenix full-paper chart:** map its fault model, recovery scope, state rollback, peripheral state, scheduling, event identity and resource overhead.
3. **Karma full-paper chart:** map operation stack/state machine, recovery sequence, rollback/roll-forward, event/request ownership and resource constraints.
4. **Driver-recovery literature:** inspect Swift et al. and Herder et al. at full text; distinguish OS-level driver restart from cooperative MCU event-runtime recovery.
5. **Standards and implementations:** check relevant AUTOSAR fault management, FreeRTOS/Zephyr/RIOT/Contiki driver and queue semantics, and public implementations. Record exact version/commit, not generic product names.
6. **Chronology:** before using any reference in a legal-priority argument, verify its effective publication/priority date and jurisdiction. K.10.1 makes no legal conclusion.
7. **Experimental trace grounding:** K.10.2 must point each claimed behavior to exact CF family and trace columns/rows in committed outputs, without rerunning K.10.
8. **No claim drafting yet:** do not convert the current matrix into patent claims or an abstract novelty assertion before K.10.2–K.10.4.

## 8. Recommended current wording

Use:

> “K.10 demonstrates reproducible, bounded host/reference differences in selected ambiguity and repeated-recovery-fault cases, with explicit baseline wins, no-difference cases, and implementation confounds. K.10.1 identifies a possible technical distinction in the precise integration of evidence-limited event association, retained quarantine, dependency-aware eligibility/preservation, and history-conditioned bounded recovery in a statically bounded event-driven MCU runtime. This distinction remains unresolved against the strongest single-reference and multi-reference prior-art attacks.”

Do not use “P4 is novel,” “P4 is superior overall,” “the combination is unprecedented,” or “patentable.”

## 9. Sources consulted / starting links

- Smith & Rixner, Phoenix, USENIX ATC 2015: https://www.usenix.org/conference/atc15/technical-session/presentation/smith
- Phoenix full proceedings PDF: https://atc.usenix.org/sites/default/files/atc15_full_proceedings_interior.pdf
- Branco et al., Karma, SenSys 2019 repository record: https://re.public.polimi.it/handle/11311/1125033
- Karma accessible paper: https://web.lums.edu.pk/~alizai/pubs/sensys19karma.pdf
- US9547557B2, peripheral bus error containment/recovery: https://patents.google.com/patent/US9547557B2/en
- US9411667B2, recovery after I/O error-containment events: https://patents.google.com/patent/US9411667B2/en
- Project's existing leads requiring primary-source claim verification: US8510592B1, US10921871B2, US10331522, US10929373, US20180365126A1, US12688084; Swift et al. (OSDI 2004); Herder et al. (device-driver failure resilience).

## 10. Checkpoint disposition

**K.10.1: research artifact prepared; distinction remains unresolved.** This is not approval to proceed autonomously. K.10.2 is the next authorized checkpoint only after ChatGPT reviews and approves this K.10.1 package. Do not modify Gates A–E or the protected runtime; do not rerun K.10; do not sync `main`.
