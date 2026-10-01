# K.6 Virtual Embedded System

This directory implements the K.5 virtual-system contracts around the same existing C reference runtime.

## Authority boundary

The virtual layer owns only bounded scenario/workload state, deterministic peripheral/environment state, immutable fault schedules, and wrapper-to-runtime correlation.

The C runtime remains authoritative for EventRef identity and generation, dependency eligibility, quarantine, recovery action selection, recovery attempt progression, verification/release, terminal outcome, and authoritative trace facts.

The virtual layer never accepts or computes a desired recovery action.

## Peripheral-action callback constraint

The existing runtime has no peripheral-action callback. K.6 therefore does not modify runtime_apply_policy(), policy_decide(), or the recovery mechanism.

During recovery, the virtual peripheral model mirrors the predeclared deterministic fault schedule only as an environmental observation. The runtime runtime_apply_policy() result remains authoritative.

## Boundedness

The implementation uses fixed-capacity arrays only. No runtime dynamic allocation is introduced.

Current bounds: event references ACTIVE_MAX (20); scenario steps 64; fault schedule records 32; wrapper/peripheral trace records 256.

## Determinism

A canonical scenario, policy variant, run ID and runtime build produce a deterministic runtime trace and wrapper trace. virtual_system_digest() is a replay check over both.

## K.6 coverage

Focused tests exercise S01, S02, S05, S06, S08 and S14, covering independent preservation, ordered blocking, recovery/release, bounded recovery progression, evidence-limited association and mixed dependency/replay correlation.

S03/S04/S07/S09-S13 remain represented by the K.5 scenario contracts and are not a K.6 comparative experiment.

This is software/host demonstrator infrastructure only. It is not STM32U575 hardware integration or physical fault injection.
