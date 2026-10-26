# Reference v2 change log

## 2026-10-26 — Initial isolated candidate

- Copied canonical runtime source from blob `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81` and header from blob `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`.
- Added a capacity guard before event release to prevent `queue_append()` asserting when the queue is full.
- Added terminal episode cleanup when a policy action or release sees a stale/invalid target.
- Added focused regression test source for both defect paths.
- Canonical `reference/` and frozen host evidence were not modified.
- Tests have not yet been compiled or run; see `README.md`.
