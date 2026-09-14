# Host Experiment Result Schema

The host harness emits one summary row per matched `(workload, fault schedule, policy variant)` execution.

| Field | Meaning |
|---|---|
| `run_id` | Stable execution identifier for this harness campaign. |
| `variant` | One of P0-P4. |
| `workload` | Canonical Gate E workload ID W01-W14. |
| `schedule` | Explicit fault schedule ID from `fault_schedules.txt`. |
| `scenario` | Human-readable scenario label from `workloads.txt`. |
| `event_count` | Requested workload event count. |
| `admitted` | Events actually admitted into the bounded host model. |
| `preserved` | Non-target events that executed successfully in the host run. |
| `correctly_blocked` | Explicit correctness checks such as stale-reference failure. |
| `incorrectly_blocked` | Non-target work blocked/failed without a declared dependency-safe reason in this harness slice. |
| `quarantine_count` | Retained quarantined event count at run completion. |
| `episode_active` | Whether a recovery episode remained active at run end. |
| `capacity_confounded` | `1` when QMAX/XMAX/EPMAX/capacity behavior prevents an honest mechanism comparison. |
| `trace_complete` | `0` when the fixed trace pool filled and additional records could not be retained. |
| `runtime_bytes` | Host `sizeof(Runtime)`. Host layout evidence only. |
| `event_slot_bytes` | Host `sizeof(EventSlot)`. Host layout evidence only. |
| `trace_pool_bytes` | Fixed host trace-pool size. Host layout evidence only. |
| `trace_count` | Number of trace records emitted for the run. |

The raw CSV traces retain the committed runtime trace identifiers. This schema is deliberately not a substitute for later MCU timing/RAM/Flash measurements.
