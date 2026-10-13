# Main Branch Integration and Presentation Audit

**Status:** Integrated; presentation overhaul in progress/recorded on `main`.  
**Last reconciled:** 2026-10-13.

## Integration history
Pull request [#9](https://github.com/SujitSaiY2007/embedded-runtime-resilience/pull/9) integrated the approved K.10.4–K.12 research and software-demonstrator work. Later commits reconciled the CF01 presentation rule and then replaced stale reader-facing status with a curated documentation structure under `docs/`.

## Branch policy
- `main` is the reader-facing integrated project.
- `exp` remains the frozen research baseline and was not changed by this presentation overhaul.
- The historical K.12 feature branch is preserved for provenance.
- Query live branch refs before relying on any recorded SHA; this document is an audit record, not a live API.

## Protected-file check
The following file blobs were verified identical to `exp` during the final integration audit:

| File | Blob SHA |
|---|---|
| `reference/src/ref_runtime.c` | `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81` |
| `reference/include/ref_runtime.h` | `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198` |
| `research/phase1_reference_implementation_design.md` | `b7fb120692756740bc969aa3412acaa89320c188` |
| `research/phase2_k9_methodology_lock.md` | `bd75f2c2c21c3964ec15b338eea99b386eff7aec` |
| `research/phase2_k9_2_p4_advantage_novelty_design.md` | `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d` |

## Final reader-facing structure
- `README.md`: short public landing page and quick start.
- `docs/`: project overview, architecture/repository map, and demonstrator guide.
- `demo/`: browser UI, Python bridge and UI contract tests.
- `reference/`: protected C runtime, experiments, and virtual system.
- `research/`: normative gates, frozen results, final conclusions, and checkpoint history.
- Root continuity files remain for project governance; the curated docs are the reader-facing source.

## Evidence rules
- K.10 results are frozen; no matrix rerun was performed for the editorial discrepancy.
- CF01's qualitative outcomes can be described; its disputed P2 attempt count is omitted from comparisons.
- Local test/browser success was user-reported and not independently CI-verified.
- Physical MCU implementation and measurement remain future work.
