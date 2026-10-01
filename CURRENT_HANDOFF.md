# Current Handoff

## Session status

Gates A-E remain closed and normative. The **Minimal Reference Implementation — smallest testable host/reference checkpoint** is now complete and tested.

## Frozen topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Frozen platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**, I2C primary, SPI secondary, UART/USART diagnostic/control. Hardware acquisition is not assumed.

## Continuity check

- **Gate A:** exact event/dependency semantics are frozen, including `EventRef={slot_id,generation}`, explicit dependency classes, FIFO admission versus eligibility-driven execution, and retained quarantine.
- **Gate B:** observable fault taxonomy and evidence-bounded association are frozen; `association precision <= evidence precision`.
- **Gate C:** deterministic bounded recovery policy is frozen with RETRY, REINIT_OR_RESET, DEGRADE, ESCALATE and four recovery-action transitions.
- **Gate D:** formal safety/termination/boundedness/identity/release/transaction properties are specified; the 33,792-context audit remains model-level evidence.
- **Gate E:** P0-P4, W01-W14, deterministic injection, fixed capacities, trace schema, metrics, and evidence boundaries are frozen.

These gates are one chain: event semantics constrain fault association; fault context constrains policy; policy/recovery interacts with scheduler/quarantine semantics; formal properties define correctness; the experimental protocol makes those properties comparable and reproducible.

## What was implemented

Directory: `reference/`

- ISO C11 host reference.
- CMake build.
- Fixed `EventSlot[20]` storage (`QMAX=16`, `XMAX=4`).
- Queue stores slot IDs; quarantine retains the same event slot and does not duplicate records.
- Four fixed dependency entries per event (`DMAX=4`).
- One fixed recovery episode (`EPMAX=1`).
- 8-bit EventRef generation; generation wrap fails closed instead of recycling.
- Deterministic first-eligible scheduler scan.
- Fixed-size `PolicyDecision` and P0-P4 policy variants.
- Deterministic software fault injection keyed by EventRef/action index.
- W01-W14 executable correctness scenarios.
- Gate-D-oriented policy/property assertions.
- Stable trace identifiers and deterministic CSV trace serialization.
- Static resource accounting and allocator audit.

## Verification result

Host C11/CMake build passed. `ctest` passed the W01-W14 suite plus recovery-bound, policy-property, trace-metadata, and static-accounting checks.

Host layout observed in this build:

- Runtime: 8164 bytes
- EventSlot: 84 bytes
- TraceRecord: 24 bytes
- fixed trace pool: 6144 bytes

Allocator source/symbol audit found no runtime allocator path in the reference implementation/test executable.

## Important implementation qualification

The minimal prototype intentionally implements exact event/transaction recovery as the executable recovery target. For `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS`, it does not invent an event target; where broader recovery is not implemented safely, it fails closed to terminal escalation. This is an implementation boundary, not a change to Gate B/C semantics.

`EPMAX=1` is explicit. W10 tests the bounded second-episode outcome rather than hiding additional recovery storage.

## Exact next task

The next chat should **not** redesign Gates A-E. It should review the committed host reference implementation against the frozen contracts, close any concrete semantic/test contradictions, then prepare the next smallest checkpoint for reproducible host experiment execution if the reference remains consistent.

The next likely boundary is: **host reference experiment harness + frozen trace corpus + matched P0-P4 execution**, still without claiming MCU or physical evidence.

## Non-goals

Do not yet:

- integrate full STM32U575 firmware;
- claim MCU RAM/Flash/timing;
- perform physical fault injection;
- add RTOS/framework layers;
- add unrelated peripherals;
- optimize before correctness;
- claim novelty, patentability, robustness, generalization, or statistical significance.

## 2026-10-01 continuation

The required startup audit is complete. Gates A-E remain frozen.

The committed implementation review found one concrete ablation gap: exact-event quarantine is currently applied by `runtime_start_fault()` for P0-P4, although frozen Gate C/E define selective dependency-aware quarantine as the P4 mechanism. This is documented in `research/phase1_reference_implementation_audit.md` and in Decision Log D-076. No semantic patch was made.

The next host checkpoint now exists under `reference/experiments/`:

- declarative `workloads.csv`;
- deterministic `fault_schedules.csv`;
- `host_experiment.c` matched P0-P4 runner;
- `run_host_experiment.py` deterministic-replay/matched-input driver;
- CTest registration when Python 3 is available.

The runner flags W09/W10 as capacity-confounded and flags P0-P3 as not valid for a clean quarantine ablation until their baseline containment semantics are separately specified.

### Verification qualification

The code was inspected against the committed API and frozen protocol, but this chat environment could not clone/compile the repository because external network resolution was unavailable. Therefore the harness is **committed but not execution-verified here**. Do not cite generated results until the host build and replay test pass.

### Exact next task

Build `reference/`, run CTest, execute `python3 experiments/run_host_experiment.py --check`, inspect the generated corpus, and fix only concrete compile/runtime/input errors. Do not change Gate A-E semantics. After successful execution, commit the generated raw-input-preserved corpus and update this handoff with actual run/test results.

### Non-goals

No STM32U575 integration, MCU timing/RAM/Flash claims, physical fault injection, RTOS, unrelated peripherals, ML/weighted scoring, statistical significance, generalization, novelty, or patentability claims.

## Chat K.1 — 2026-10-01 verified host-experiment checkpoint

This section supersedes the earlier “execution verification pending” language above.

### Completed

The smallest reproducible host P0-P4 experiment harness was built and executed in the user-controlled Windows/MSVC environment.

- Commit: `949bd4c`
- Branch: `experiment/host-p0-p4-corpus-2026-10-01`
- Working tree: clean after commit and push.
- Build: successful; `reference_tests.exe` and `host_experiment.exe` present.
- CTest: **2/2 passed**.
- Host experiment check: **all five harness checks passed**.
- Corpus: **70 matched runs** across W01-W14 and P0-P4.
- W09/W10 capacity confounds are explicit.
- P0-P3 quarantine-ablation validity is explicitly false; P4 is valid under the current implementation.
- The exact-event quarantine semantic gap remains documented; no frozen contract was changed.

### Important artifact note

The generated `out/` and `out.replay/` directories were used for verification and inspection, then removed before the clean commit. Do not describe those generated files as currently committed artifacts.

### Chat K.2 exact next task

Regenerate and inspect the actual `runs.csv`, `trace.csv`, and `corpus_manifest.csv`. Determine whether the traces themselves provide the expected Gate-E evidence and identify any remaining measurement/evidence boundary. Only after that inspection should another code change be considered.

### Non-goals remain unchanged

No STM32U575 integration, physical fault injection, MCU resource/timing claims, RTOS, unrelated peripherals, ML/weighted scoring, statistical significance, generalization, novelty, or patentability claims.
