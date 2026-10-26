# Hardware Screenshot Evidence Index

**Prepared:** 2026-10-26  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Purpose:** Trace the relevant original screenshot attachments shared in the ChatGPT conversation for manuscript evidence selection.

## Important status

The screenshots below were located in the current conversation's attachment records. They have **not yet been committed as binary image files to this repository**. This index is a traceability record, not a substitute for the images. Do not cite this index as visual evidence and do not claim the images are present in GitHub until the actual image files are committed and their paths verified.

## Relevant screenshots

| Original attachment filename | Observed content | Appropriate use | Boundaries |
|---|---|---|---|
| `image(20261026-091651).png` | STM32CubeIDE build console; 0 errors, 0 warnings; linker output reports text 12,948, data 112, BSS 12,704, total 25,764 bytes | Build evidence and reported linker-size snapshot | Not runtime RAM usage, stack high-water mark, energy, timing, or a hardware benchmark |
| `image(20261026-092203).png` | STM32CubeIDE debugger with policy/control arrays and sampled matrix entries visible | Debugger-state illustration for the observed hardware campaign | Only visible sampled variables; not a complete 80-entry matrix export |
| `image(20261026-092522).png` | Detailed debugger variable values including sampled matrix values, control post-read status, chip IDs, NACK observation, and selected result fields | Supplementary variable-level evidence | Interpret integer encodings only with the corresponding source enum definitions; do not infer unshown values |
| `image(20261026-093013).png` | Debugger values including runtime/release results, physical status array, baseline flags, and control NACK/post-read indicators | Supplementary evidence for the single observed matrix run and control checks | A debugger snapshot is not a repeated-trial result or a full raw log |
| `image(20261026-093158).png` | Cropped debugger values for post-read chip IDs, including values of 96 (decimal, 0x60) in visible entries | Illustration of the expected BME280 chip ID on visible entries | Cropped view; do not claim all five values are shown unless the original full screenshot confirms it |

## Related source and report

- Firmware diagnostic source: `Plan2.0/firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix_diagnostic.c`
- Hardware closure report: `research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md`
- Evidence ledger: `research/manuscript/EVIDENCE_LEDGER.md`
- Manuscript draft: `research/manuscript/DRAFT_MANUSCRIPT.md`

## Instructions for manuscript drafting

1. Search the complete repository for the actual screenshot files before concluding no screenshots exist.
2. Once the binary originals are committed, replace this index's filenames with repository-relative paths and link each item to its exact file.
3. Prefer a small number of legible original screenshots in a supplementary evidence directory; avoid using cropped screenshots as the only evidence when the full original exists.
4. Keep screenshots unaltered where possible. If cropping or annotation is needed for publication, preserve the untouched original and store a clearly named derivative separately.
5. Captions must state that these are debugger/build snapshots from the observed hardware campaign. Do not imply repeated independent policy trials, complete raw matrix export, stuck-bus testing, or runtime memory/energy measurements.
6. The visible physical outcome encoding in the project is status 7 = `R_TERMINAL`, status 1 = `R_PASS`; runtime result 4 = `OUTCOME_TERMINAL_ESCALATE`, not a processor crash. Verify these against the source before publication.
7. Keep this index marked incomplete until the original binary images are actually committed and their GitHub URLs have been checked.
