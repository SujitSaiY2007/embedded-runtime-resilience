#include "virtual_system.h"
#include <string.h>

static EventRef invalid_ref(void) { return event_ref_invalid(); }

static int event_index(const VirtualSystem *vs, ScenarioEventKey key) {
    if (vs == NULL || vs->scenario == NULL) return -1;
    for (uint8_t i = 0u; i < vs->scenario->event_count; ++i) {
        if (vs->scenario->events[i].scenario_event_key == key) return (int)i;
    }
    return -1;
}

static const VirtualFaultSchedule *find_schedule(const VirtualSystem *vs,
                                                  uint16_t schedule_id,
                                                  uint8_t action_index) {
    const VirtualFaultSchedule *first_match = NULL;
    for (uint8_t i = 0u; i < vs->scenario->fault_schedule_count; ++i) {
        const VirtualFaultSchedule *s = &vs->scenario->fault_schedules[i];
        if (s->schedule_id == schedule_id) {
            if (first_match == NULL) first_match = s;
            if (s->action_index == action_index) return s;
        }
    }
    if (action_index == 0u) return first_match;
    return NULL;
}

static VirtualPeripheralStatus status_for_fault(FaultClass fault) {
    switch (fault) {
    case FAULT_I2C_NACK: return VPERIPH_NACK;
    case FAULT_I2C_TIMEOUT:
    case FAULT_SPI_TIMEOUT: return VPERIPH_TIMEOUT;
    case FAULT_I2C_BERR: return VPERIPH_PROTOCOL_ERROR;
    case FAULT_I2C_ARLO: return VPERIPH_ARBITRATION_ERROR;
    case FAULT_I2C_PERSISTENT:
    case FAULT_SPI_PERSISTENT: return VPERIPH_PERSISTENT_FAILURE;
    case FAULT_SPI_VERIFY: return VPERIPH_VERIFY_FAILURE;
    default: return VPERIPH_PROTOCOL_ERROR;
    }
}

static bool valid_peripheral(PeripheralId p) {
    return p == PERIPH_I2C0 || p == PERIPH_SPI0 || p == PERIPH_UART0;
}

static void append_peripheral_trace(VirtualSystem *vs, PeripheralId peripheral,
                                    EventRef ref, uint16_t tx,
                                    VirtualPeripheralStatus status,
                                    FaultClass fault) {
    if (vs->peripheral_trace_count >= VIRTUAL_MAX_ENV_TRACE) {
        vs->adapter_error = true;
        return;
    }
    VirtualPeripheralRecord *r = &vs->peripheral_trace[vs->peripheral_trace_count++];
    r->peripheral = peripheral;
    if (peripheral == PERIPH_NONE) {
        r->operation_sequence = 0u;
    } else {
        r->operation_sequence = ++vs->peripheral_sequence[(unsigned)peripheral - 1u];
    }
    r->status = status;
    r->fault_class = fault;
    r->transaction_id = tx;
    r->event_ref = ref;
}

static void append_wrapper_trace(VirtualSystem *vs, uint16_t step_sequence,
                                 ScenarioEventKey key, EventRef ref,
                                 PeripheralId peripheral, uint16_t tx,
                                 RecoveryAction action, OutcomeCode outcome,
                                 VirtualPeripheralStatus status,
                                 FaultClass fault, uint32_t runtime_first) {
    if (vs->trace_count >= VIRTUAL_MAX_ENV_TRACE) {
        vs->adapter_error = true;
        return;
    }
    VirtualTraceRecord *r = &vs->trace[vs->trace_count++];
    r->wrapper_sequence = ++vs->wrapper_sequence;
    r->runtime_trace_first = runtime_first;
    r->runtime_trace_last = vs->runtime.trace_count == 0u
        ? runtime_first : vs->runtime.trace[vs->runtime.trace_count - 1u].trace_seq;
    r->scenario_id = vs->scenario->scenario_id;
    r->step_sequence = step_sequence;
    r->scenario_event_key = key;
    r->event_ref = ref;
    r->peripheral = peripheral;
    r->transaction_id = tx;
    r->action = action;
    r->outcome = outcome;
    r->environmental_status = status;
    r->fault_class = fault;
    r->runtime_authoritative = true;
}

static OutcomeCode admit_event(VirtualSystem *vs, uint16_t event_index_value,
                               uint16_t step_sequence) {
    if (event_index_value >= vs->scenario->event_count) {
        vs->adapter_error = true;
        return OUTCOME_INVALID_DEPENDENCY;
    }
    const VirtualEventSpec *spec = &vs->scenario->events[event_index_value];
    if (!valid_peripheral(spec->peripheral)) {
        vs->adapter_error = true;
        return OUTCOME_INVALID_DEPENDENCY;
    }
    EventSlot e;
    memset(&e, 0, sizeof(e));
    e.type = spec->event_type;
    e.producer_id = spec->producer_id;
    e.service_id = spec->service_id;
    e.consumer_id = spec->consumer_id;
    e.peripheral = spec->peripheral;
    e.criticality = spec->criticality;
    e.transaction_id = spec->transaction_id;
    e.degradable = spec->degradable;
    e.shared_state_valid = true;
    EventRef ref = invalid_ref();
    OutcomeCode out = runtime_admit(&vs->runtime, &e, &ref);
    if (out == OUTCOME_SUCCESS) {
        vs->event_refs[event_index_value] = ref;
        vs->event_ref_valid[event_index_value] = true;
    }
    append_wrapper_trace(vs, step_sequence, spec->scenario_event_key, ref,
                         spec->peripheral, spec->transaction_id, ACT_NONE,
                         out, VPERIPH_READY, FAULT_NONE,
                         vs->runtime.trace_count == 0u ? 0u :
                         vs->runtime.trace[vs->runtime.trace_count - 1u].trace_seq);
    return out;
}

static OutcomeCode add_dependency(VirtualSystem *vs, uint16_t target_index,
                                  uint16_t predecessor_index,
                                  DependencyKind kind, EventState acceptable,
                                  uint16_t step_sequence) {
    if (target_index >= vs->scenario->event_count ||
        predecessor_index >= vs->scenario->event_count ||
        !vs->event_ref_valid[target_index] ||
        !vs->event_ref_valid[predecessor_index]) {
        vs->adapter_error = true;
        return OUTCOME_INVALID_DEPENDENCY;
    }
    const VirtualEventSpec *target = &vs->scenario->events[target_index];
    const EventRef target_ref = vs->event_refs[target_index];
    const EventRef predecessor_ref = vs->event_refs[predecessor_index];
    OutcomeCode out = runtime_add_dependency(&vs->runtime, target_ref,
                                             predecessor_ref, kind, acceptable);
    append_wrapper_trace(vs, step_sequence, target->scenario_event_key, target_ref,
                         target->peripheral, target->transaction_id, ACT_NONE,
                         out, VPERIPH_READY, FAULT_NONE,
                         vs->runtime.trace_count == 0u ? 0u :
                         vs->runtime.trace[vs->runtime.trace_count - 1u].trace_seq);
    return out;
}

static OutcomeCode start_fault(VirtualSystem *vs, uint16_t schedule_id,
                               uint16_t step_sequence) {
    const VirtualFaultSchedule *s = find_schedule(vs, schedule_id, 0u);
    if (s == NULL) {
        vs->adapter_error = true;
        return OUTCOME_INVALID_DEPENDENCY;
    }
    EventRef target = invalid_ref();
    PeripheralId peripheral = PERIPH_NONE;
    ScenarioEventKey key = VIRTUAL_MAX_EVENT_KEY;
    if (s->association == ASSOC_EXACT) {
        int idx = event_index(vs, s->target_key);
        if (idx < 0 || !vs->event_ref_valid[idx]) {
            vs->adapter_error = true;
            return OUTCOME_STALE_REF;
        }
        target = vs->event_refs[idx];
        peripheral = vs->scenario->events[idx].peripheral;
        key = s->target_key;
    } else {
        int idx = event_index(vs, s->target_key);
        if (idx >= 0) {
            peripheral = vs->scenario->events[idx].peripheral;
            key = s->target_key;
        }
    }
    OutcomeCode out = runtime_start_fault(
        &vs->runtime, s->fault_class, s->association, target,
        s->transaction_id, s->criticality, s->retry_safe,
        s->reinit_safe, s->degrade_safe);
    VirtualPeripheralStatus status = status_for_fault(s->fault_class);
    if (peripheral != PERIPH_NONE)
        append_peripheral_trace(vs, peripheral, target, s->transaction_id, status,
                                s->fault_class);
    append_wrapper_trace(vs, step_sequence, key, target, peripheral,
                         s->transaction_id, ACT_NONE, out, status,
                         s->fault_class,
                         vs->runtime.trace_count == 0u ? 0u :
                         vs->runtime.trace[vs->runtime.trace_count - 1u].trace_seq);
    return out;
}

static OutcomeCode drain(VirtualSystem *vs, uint16_t step_sequence) {
    OutcomeCode last = OUTCOME_SUCCESS;
    for (uint8_t guard = 0u; guard < VIRTUAL_MAX_EVENTS; ++guard) {
        EventRef selected = invalid_ref();
        if (!scheduler_select(&vs->runtime, &selected)) break;
        bool faulted = false;
        OutcomeCode out = runtime_execute_selected(&vs->runtime, selected, NULL, &faulted);
        const EventSlot *event = &vs->runtime.slots[selected.slot_id];
        VirtualPeripheralStatus status = faulted ? VPERIPH_PROTOCOL_ERROR : VPERIPH_SUCCESS;
        append_peripheral_trace(vs, event->peripheral, selected,
                                event->transaction_id, status,
                                faulted ? FAULT_SW_SERVICE : FAULT_NONE);
        append_wrapper_trace(vs, step_sequence, VIRTUAL_MAX_EVENT_KEY, selected,
                             event->peripheral, event->transaction_id, ACT_NONE,
                             out, status, faulted ? FAULT_SW_SERVICE : FAULT_NONE,
                             vs->runtime.trace_count == 0u ? 0u :
                             vs->runtime.trace[vs->runtime.trace_count - 1u].trace_seq);
        last = out;
        if (out != OUTCOME_SUCCESS) break;
    }
    return last;
}

static OutcomeCode apply_fault(VirtualSystem *vs, uint16_t schedule_id,
                               uint16_t step_sequence) {
    if (!vs->runtime.episode_in_use) {
        vs->adapter_error = true;
        return OUTCOME_NONE;
    }
    uint8_t action_index = (uint8_t)(vs->runtime.episode.attempt_count + 1u);
    const VirtualFaultSchedule *s = find_schedule(vs, schedule_id, action_index);
    if (s == NULL) {
        vs->adapter_error = true;
        return OUTCOME_INVALID_DEPENDENCY;
    }
    EventRef target = vs->runtime.episode.target_ref;
    PeripheralId peripheral = vs->runtime.episode.peripheral;
    ScenarioEventKey key = VIRTUAL_MAX_EVENT_KEY;
    for (uint8_t i = 0u; i < vs->scenario->event_count; ++i) {
        if (vs->event_ref_valid[i] && event_ref_equal(vs->event_refs[i], target)) {
            key = vs->scenario->events[i].scenario_event_key;
            break;
        }
    }
    PolicyDecision observed = policy_decide(&vs->runtime, &vs->runtime.episode);
    FaultInjection injection = {
        s->fault_class, target, s->transaction_id, s->action_index, 0u, s->enabled
    };
    uint16_t runtime_before = vs->runtime.trace_count;
    OutcomeCode out = runtime_apply_policy(&vs->runtime, &injection);
    RecoveryAction action = observed.action;
    VirtualPeripheralStatus status = s->enabled ? status_for_fault(s->fault_class)
                                                : VPERIPH_SUCCESS;
    append_peripheral_trace(vs, peripheral, target, s->transaction_id, status,
                            s->enabled ? s->fault_class : FAULT_NONE);
    append_wrapper_trace(vs, step_sequence, key, target, peripheral,
                         s->transaction_id, action, out, status,
                         s->enabled ? s->fault_class : FAULT_NONE,
                         runtime_before < vs->runtime.trace_count
                             ? vs->runtime.trace[runtime_before].trace_seq
                             : (vs->runtime.trace_count == 0u ? 0u :
                                vs->runtime.trace[vs->runtime.trace_count - 1u].trace_seq));
    return out;
}

void virtual_system_init(VirtualSystem *vs, const VirtualScenario *scenario,
                         PolicyVariant variant, uint32_t run_id) {
    memset(vs, 0, sizeof(*vs));
    vs->scenario = scenario;
    vs->run_id = run_id;
    runtime_init(&vs->runtime, variant);
    runtime_set_trace_metadata(&vs->runtime, run_id,
                               (uint8_t)(scenario == NULL ? 0u : scenario->scenario_id),
                               0u);
    for (uint8_t i = 0u; i < VIRTUAL_MAX_EVENTS; ++i)
        vs->event_refs[i] = invalid_ref();
}

OutcomeCode virtual_system_step(VirtualSystem *vs) {
    if (vs == NULL || vs->scenario == NULL || vs->step_index >= vs->scenario->step_count)
        return OUTCOME_NONE;
    const VirtualStep *step = &vs->scenario->steps[vs->step_index++];
    OutcomeCode out = OUTCOME_SUCCESS;
    switch (step->kind) {
    case VSTEP_ADMIT:
        out = admit_event(vs, step->a, step->sequence);
        break;
    case VSTEP_DEPEND:
        if (step->c > (uint16_t)DEP_COUPLED) {
            vs->adapter_error = true;
            out = OUTCOME_INVALID_DEPENDENCY;
        } else {
            out = add_dependency(vs, step->a, step->b,
                                 (DependencyKind)step->c,
                                 (EventState)step->d, step->sequence);
        }
        break;
    case VSTEP_START_FAULT:
        out = start_fault(vs, step->a, step->sequence);
        break;
    case VSTEP_DRAIN:
        out = drain(vs, step->sequence);
        break;
    case VSTEP_APPLY_FAULT:
        out = apply_fault(vs, step->a, step->sequence);
        break;
    default:
        vs->adapter_error = true;
        out = OUTCOME_INVALID_DEPENDENCY;
        break;
    }
    vs->last_outcome = out;
    return out;
}

OutcomeCode virtual_system_run(VirtualSystem *vs) {
    if (vs == NULL || vs->scenario == NULL) return OUTCOME_INVALID_DEPENDENCY;
    while (vs->step_index < vs->scenario->step_count) {
        (void)virtual_system_step(vs);
        if (vs->adapter_error) return OUTCOME_INVALID_DEPENDENCY;
    }
    return vs->last_outcome;
}

bool virtual_system_complete(const VirtualSystem *vs) {
    return vs != NULL && vs->scenario != NULL &&
           vs->step_index == vs->scenario->step_count &&
           !vs->adapter_error;
}

const EventRef *virtual_system_event_ref(const VirtualSystem *vs,
                                         ScenarioEventKey key) {
    int idx = event_index(vs, key);
    if (idx < 0 || !vs->event_ref_valid[idx] ||
        !event_ref_valid(&vs->runtime, vs->event_refs[idx])) return NULL;
    return &vs->event_refs[idx];
}

const VirtualTraceRecord *virtual_system_trace_at(const VirtualSystem *vs,
                                                  uint16_t index) {
    if (vs == NULL || index >= vs->trace_count) return NULL;
    return &vs->trace[index];
}

const VirtualPeripheralRecord *virtual_system_peripheral_trace_at(
    const VirtualSystem *vs, uint16_t index) {
    if (vs == NULL || index >= vs->peripheral_trace_count) return NULL;
    return &vs->peripheral_trace[index];
}

static uint32_t hash_byte(uint32_t h, uint8_t b) {
    h ^= (uint32_t)b;
    h *= 16777619u;
    return h;
}

static uint32_t hash_u32(uint32_t h, uint32_t v) {
    for (uint8_t i = 0u; i < 4u; ++i) {
        h = hash_byte(h, (uint8_t)(v & 0xFFu));
        v >>= 8u;
    }
    return h;
}

uint32_t virtual_system_digest(const VirtualSystem *vs) {
    if (vs == NULL) return 0u;
    uint32_t h = 2166136261u;
    h = hash_u32(h, vs->run_id);
    h = hash_u32(h, vs->runtime.trace_count);
    for (uint16_t i = 0u; i < vs->runtime.trace_count; ++i) {
        const TraceRecord *t = &vs->runtime.trace[i];
        h = hash_u32(h, t->trace_seq);
        h = hash_byte(h, t->event_ref.slot_id);
        h = hash_byte(h, t->event_ref.generation);
        h = hash_u32(h, t->fault_episode_id);
        h = hash_byte(h, t->action_index);
        h = hash_byte(h, t->action);
        h = hash_byte(h, t->outcome);
        h = hash_byte(h, t->correctness);
    }
    for (uint16_t i = 0u; i < vs->trace_count; ++i) {
        const VirtualTraceRecord *t = &vs->trace[i];
        h = hash_u32(h, t->wrapper_sequence);
        h = hash_u32(h, t->runtime_trace_first);
        h = hash_u32(h, t->runtime_trace_last);
        h = hash_byte(h, t->scenario_event_key);
        h = hash_byte(h, t->event_ref.slot_id);
        h = hash_byte(h, t->event_ref.generation);
        h = hash_byte(h, (uint8_t)t->action);
        h = hash_byte(h, (uint8_t)t->outcome);
        h = hash_byte(h, (uint8_t)t->environmental_status);
        h = hash_byte(h, (uint8_t)t->fault_class);
    }
    return h;
}
