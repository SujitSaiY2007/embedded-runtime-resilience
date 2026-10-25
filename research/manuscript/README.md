# Manuscript Workspace

**Status:** Drafting instructions committed; manuscript not yet drafted or independently reviewed.  
**Repository:** [embedded-runtime-resilience](https://github.com/SujitSaiY2007/embedded-runtime-resilience)  
**Next action:** provide the repository URL and [Claude journal-manuscript prompt](CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md) to Claude.

## Purpose

Prepare a rigorous journal submission from the frozen research artifacts, software implementation, existing literature review, and bounded physical hardware demonstration. The manuscript must prioritize evidence traceability and scientifically defensible claims over aggressive novelty statements or citation volume.

## Evidence streams that must remain distinct

1. **Frozen host/reference campaign:** 16 case families × 5 policy variants × 5 repetitions = 400 deterministic executions.
2. **Software demonstrator:** browser UI and Python bridge calling the authoritative C reference runtime through the virtual-system/scenario path.
3. **Physical hardware demonstration:** one user-observed STM32L476RG/BME280 controlled wrong-address NACK and recovery/reinitialization run; P1/P4 post-recovery ID reads returned `0x60` and release result 1. P0/P2/P3 ended in terminal outcomes.
4. **Unresolved matrix detail:** the 80 embedded decision cases use provisional contexts. The user statement about the last matrix status conflicts with a screenshot showing `matrix_status[79]=1`; no complete readable array export is recorded.

## Drafting rules

- Preserve approved/frozen title and abstract if identified.
- Verify every citation against authoritative publisher, DOI, standards-body or institutional sources.
- Build a claim-to-evidence ledger and distinguish observation, source-derived expectation, inference, and unsupported claim.
- Never invent bibliographic metadata, affiliation, email, measurements, raw data, or trial counts.
- Do not modify protected runtime or frozen 400-execution evidence.
- Do not claim physical stuck-bus recovery, repeated-run reliability, MCU resource metrics, or universal P4 superiority.

See the full [Claude prompt](CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md) and [hardware evidence report](../../Plan2.0/results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md).
