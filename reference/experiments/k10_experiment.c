#define _CRT_SECURE_NO_WARNINGS
#include "ref_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K10_REPETITIONS 5
#define K10_FAMILY_COUNT 16

typedef struct {
    int run_id;
    int family_id;
    char family_name[48];
    int variant_id;
    int rep;
    OutcomeCode terminal_outcome;
    bool episode_active;
    int recovery_attempts;
    int preserved_work;
    int blocked_work;
    int trace_records;
    uint8_t reason_code;
    RecoveryAction final_action;
    bool harness_ok;
} K10RunResult;

static void log_run(FILE *f_runs, const K10RunResult *r) {
    const char *term_str = "NO_TERMINAL";
    if (r->terminal_outcome == OUTCOME_SUCCESS) term_str = "SUCCESS";
    else if (r->terminal_outcome == OUTCOME_TERMINAL_DEGRADE) term_str = "TERMINAL_DEGRADE";
    else if (r->terminal_outcome == OUTCOME_TERMINAL_ESCALATE) term_str = "TERMINAL_ESCALATE";
    else if (r->terminal_outcome == OUTCOME_STALE_REF) term_str = "STALE_REF";
    else if (r->terminal_outcome == OUTCOME_EPISODE_FULL) term_str = "EPISODE_FULL";
    else if (r->terminal_outcome == OUTCOME_QUEUE_FULL) term_str = "QUEUE_FULL";

    fprintf(f_runs, "%d,%d,%s,%d,%d,%s,%d,%d,%d,%d,%d,%u,%u,%d\n",
        r->run_id, r->family_id, r->family_name, r->variant_id, r->rep,
        term_str, r->episode_active ? 1 : 0, r->recovery_attempts,
        r->preserved_work, r->blocked_work, r->trace_records,
        (unsigned)r->reason_code, (unsigned)r->final_action, r->harness_ok ? 1 : 0);
}

static void log_traces(FILE *f_trace, const Runtime *rt, int run_id, int family_id, int variant_id) {
    for (uint16_t i = 0u; i < rt->trace_count; ++i) {
        const TraceRecord *t = &rt->trace[i];
        fprintf(f_trace, "%d,%d,%d,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            run_id, family_id, variant_id,
            t->run_id, t->trace_seq, t->fault_episode_id,
            (unsigned)t->event_ref.slot_id, (unsigned)t->event_ref.generation,
            (unsigned)t->transaction_id, (unsigned)t->observation_seq,
            (unsigned)t->action_index, (unsigned)t->state,
            (unsigned)t->action, (unsigned)t->outcome, (unsigned)t->correctness);
    }
}

static void drain_queue(Runtime *rt, int *executed_count) {
    int count = 0;
    for (unsigned g = 0u; g < 64u; ++g) {
        EventRef sel;
        if (!scheduler_select(rt, &sel)) break;
        OutcomeCode out = runtime_execute_selected(rt, sel, NULL, NULL);
        if (out == OUTCOME_SUCCESS) count++;
        else break;
    }
    if (executed_count) *executed_count = count;
}

/* CF01: Persistent Fault + History */
static K10RunResult run_cf01(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 1, "CF01_PERSISTENT_HISTORY", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 1u, 1u);

    EventSlot e1 = { 0 }, e2 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = CRITICAL; e1.transaction_id = 101;
    e2.type = EVT_PERIPHERAL_READ; e2.peripheral = PERIPH_I2C0; e2.criticality = NORMAL; e2.transaction_id = 102;
    EventRef r1, r2;
    runtime_admit(&rt, &e1, &r1);
    runtime_admit(&rt, &e2, &r2);

    /* Fault e1 */
    runtime_start_fault(&rt, FAULT_I2C_PERSISTENT, ASSOC_EXACT, r1, 101, CRITICAL, true, true, false);

    /* Unassociated e2 executes during quarantine */
    drain_queue(&rt, &res.preserved_work);

    /* Injections: action 1 fails, action 2 fails, action 3 succeeds */
    OutcomeCode last_out = OUTCOME_NONE;
    for (int act = 0; act < 4; ++act) {
        if (!rt.episode_in_use) break;
        FaultInjection fi = { 0 };
        fi.enabled = (act < 2); /* actions 1 and 2 fail, action 3 succeeds */
        fi.fault_class = FAULT_I2C_PERSISTENT;
        fi.target_ref = r1;
        fi.trigger_action_index = (uint8_t)(act + 1);
        last_out = runtime_apply_policy(&rt, &fi);
    }
    res.terminal_outcome = last_out;
    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 1, (int)v);
    return res;
}

/* CF02: Queue Pressure */
static K10RunResult run_cf02(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 2, "CF02_QUEUE_PRESSURE", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 2u, 1u);

    EventRef refs[16];
    for (uint8_t i = 0u; i < 16u; ++i) {
        EventSlot e = { 0 };
        e.type = EVT_PERIPHERAL_READ; e.peripheral = PERIPH_I2C0; e.criticality = NORMAL; e.transaction_id = (uint16_t)(200 + i);
        runtime_admit(&rt, &e, &refs[i]);
    }
    /* Try 17th -> queue full */
    EventSlot overflow = { 0 };
    EventRef r_ovf;
    if (runtime_admit(&rt, &overflow, &r_ovf) != OUTCOME_QUEUE_FULL) res.harness_ok = false;

    /* Fault refs[0] */
    runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, refs[0], 200, NORMAL, true, true, true);
    drain_queue(&rt, &res.preserved_work); /* 15 events should execute */

    /* Recovery retry succeeds */
    FaultInjection fi = { 0 };
    fi.enabled = false;
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);
    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 2, (int)v);
    return res;
}

/* CF03: Dependency / Order Preservation */
static K10RunResult run_cf03(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 3, "CF03_DEPENDENCY_ORDER", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 3u, 1u);

    EventSlot e1 = { 0 }, e2 = { 0 }, e3 = { 0 }, e4 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = CRITICAL; e1.transaction_id = 301;
    e2.type = EVT_PERIPHERAL_WRITE; e2.peripheral = PERIPH_I2C0; e2.criticality = CRITICAL; e2.transaction_id = 302;
    e3.type = EVT_SERVICE; e3.peripheral = PERIPH_NONE; e3.criticality = CRITICAL; e3.transaction_id = 303;
    e4.type = EVT_HOUSEKEEPING; e4.peripheral = PERIPH_NONE; e4.criticality = NORMAL; e4.transaction_id = 304;

    EventRef r1, r2, r3, r4;
    runtime_admit(&rt, &e1, &r1);
    runtime_admit(&rt, &e2, &r2);
    runtime_admit(&rt, &e3, &r3);
    runtime_admit(&rt, &e4, &r4);

    runtime_add_dependency(&rt, r2, r1, DEP_ORDERED, ST_COMPLETED);
    runtime_add_dependency(&rt, r3, r1, DEP_COUPLED, ST_COMPLETED);

    /* Fault predecessor r1 */
    runtime_start_fault(&rt, FAULT_I2C_PERSISTENT, ASSOC_EXACT, r1, 301, CRITICAL, true, true, false);

    /* Drain before recovery: only r4 executes; r2 and r3 blocked */
    drain_queue(&rt, &res.preserved_work);
    res.blocked_work = 2;

    /* Recovery */
    for (int act = 0; act < 4; ++act) {
        if (!rt.episode_in_use) break;
        FaultInjection fi = { 0 };
        fi.enabled = (act < 2); /* action 3 succeeds */
        fi.fault_class = FAULT_I2C_PERSISTENT;
        fi.target_ref = r1;
        fi.trigger_action_index = (uint8_t)(act + 1);
        res.terminal_outcome = runtime_apply_policy(&rt, &fi);
    }
    /* Drain again if r1 completed: r2 and r3 can now execute */
    int post_drain = 0;
    drain_queue(&rt, &post_drain);
    res.preserved_work += post_drain;

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 3, (int)v);
    return res;
}

/* CF04: Association Ambiguity */
static K10RunResult run_cf04(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 4, "CF04_ASSOCIATION_AMBIGUITY", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 4u, 1u);

    EventSlot e1 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = CRITICAL; e1.transaction_id = 401;
    EventRef r1;
    runtime_admit(&rt, &e1, &r1);

    /* Ambiguous peripheral-level fault without exact target */
    EventRef unmapped = event_ref_invalid();
    runtime_start_fault(&rt, FAULT_AMBIGUOUS, ASSOC_PERIPHERAL_ONLY, unmapped, 401, CRITICAL, true, true, false);

    /* Apply policy */
    FaultInjection fi = { 0 };
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);
    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 4, (int)v);
    return res;
}

/* CF05: Fault During Recovery */
static K10RunResult run_cf05(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 5, "CF05_FAULT_DURING_RECOVERY", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 5u, 1u);

    EventSlot e1 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = CRITICAL; e1.transaction_id = 501;
    EventRef r1;
    runtime_admit(&rt, &e1, &r1);

    runtime_start_fault(&rt, FAULT_I2C_TIMEOUT, ASSOC_EXACT, r1, 501, CRITICAL, true, true, false);

    /* Every recovery action encounters a secondary fault */
    OutcomeCode last_out = OUTCOME_NONE;
    for (int act = 0; act < 4; ++act) {
        if (!rt.episode_in_use) break;
        FaultInjection fi = { 0 };
        fi.enabled = true; /* fails */
        fi.fault_class = FAULT_I2C_TIMEOUT;
        fi.target_ref = r1;
        fi.trigger_action_index = (uint8_t)(act + 1);
        last_out = runtime_apply_policy(&rt, &fi);
    }
    res.terminal_outcome = last_out;
    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 5, (int)v);
    return res;
}

/* CF06: Recovery Failure (Deferable Degradation) */
static K10RunResult run_cf06(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 6, "CF06_RECOVERY_FAILURE", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 6u, 1u);

    EventSlot e1 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = DEFERABLE; e1.transaction_id = 601;
    EventRef r1;
    runtime_admit(&rt, &e1, &r1);

    runtime_start_fault(&rt, FAULT_I2C_PERSISTENT, ASSOC_EXACT, r1, 601, DEFERABLE, true, true, true);

    OutcomeCode last_out = OUTCOME_NONE;
    for (int act = 0; act < 4; ++act) {
        if (!rt.episode_in_use) break;
        FaultInjection fi = { 0 };
        fi.enabled = true; /* All fail */
        fi.fault_class = FAULT_I2C_PERSISTENT;
        fi.target_ref = r1;
        fi.trigger_action_index = (uint8_t)(act + 1);
        last_out = runtime_apply_policy(&rt, &fi);
    }
    res.terminal_outcome = last_out;
    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 6, (int)v);
    return res;
}

/* CF07: Prior Escalation + Subsequent Fault */
static K10RunResult run_cf07(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 7, "CF07_PRIOR_ESCALATION_SUBSEQUENT", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 7u, 1u);

    EventSlot e1 = { 0 }, e2 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = CRITICAL; e1.transaction_id = 701;
    e2.type = EVT_PERIPHERAL_READ; e2.peripheral = PERIPH_I2C0; e2.criticality = NORMAL; e2.transaction_id = 702;
    EventRef r1, r2;
    runtime_admit(&rt, &e1, &r1);
    runtime_admit(&rt, &e2, &r2);

    /* Ambiguous fault first */
    runtime_start_fault(&rt, FAULT_AMBIGUOUS, ASSOC_PERIPHERAL_ONLY, event_ref_invalid(), 701, CRITICAL, true, true, false);
    FaultInjection fi = { 0 };
    runtime_apply_policy(&rt, &fi);

    /* Second fault arrives on r2 */
    OutcomeCode start_sub = runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, r2, 702, NORMAL, true, true, true);
    if (start_sub == OUTCOME_SUCCESS) {
        FaultInjection fi2 = { 0 };
        fi2.enabled = false; /* transient succeeds */
        res.terminal_outcome = runtime_apply_policy(&rt, &fi2);
    } else {
        res.terminal_outcome = start_sub; /* EPISODE_FULL on baselines! */
    }

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 7, (int)v);
    return res;
}

/* CF08: Critical vs Deferable Work */
static K10RunResult run_cf08(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 8, "CF08_CRITICAL_VS_DEFERABLE", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 8u, 1u);

    EventSlot e1 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = DEFERABLE; e1.transaction_id = 801;
    EventRef r1;
    runtime_admit(&rt, &e1, &r1);

    /* Deferable fault without recovery */
    runtime_start_fault(&rt, FAULT_I2C_PERSISTENT, ASSOC_EXACT, r1, 801, DEFERABLE, false, false, true);
    FaultInjection fi = { 0 };
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 8, (int)v);
    return res;
}

/* CF09: Repeated-Fault Contention */
static K10RunResult run_cf09(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 9, "CF09_REPEATED_CONTENTION", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 9u, 1u);

    EventRef refs[3];
    for (int i = 0; i < 3; ++i) {
        EventSlot e = { 0 };
        e.type = EVT_PERIPHERAL_READ; e.peripheral = PERIPH_I2C0; e.criticality = NORMAL; e.transaction_id = (uint16_t)(900 + i);
        runtime_admit(&rt, &e, &refs[i]);
    }

    /* 3 sequential transient faults */
    for (int i = 0; i < 3; ++i) {
        runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, refs[i], (uint16_t)(900 + i), NORMAL, true, true, true);
        FaultInjection fi = { 0 };
        res.terminal_outcome = runtime_apply_policy(&rt, &fi);
    }

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 9, (int)v);
    return res;
}

/* CF10: Reinitialization Follow-Up */
static K10RunResult run_cf10(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 10, "CF10_REINIT_FOLLOWUP", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 10u, 1u);

    EventSlot e1 = { 0 }, e2 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = CRITICAL; e1.transaction_id = 1001;
    e2.type = EVT_PERIPHERAL_READ; e2.peripheral = PERIPH_I2C0; e2.criticality = NORMAL; e2.transaction_id = 1002;
    EventRef r1, r2;
    runtime_admit(&rt, &e1, &r1);
    runtime_admit(&rt, &e2, &r2);

    /* E1 persistent fault requiring reinit */
    runtime_start_fault(&rt, FAULT_I2C_PERSISTENT, ASSOC_EXACT, r1, 1001, CRITICAL, true, true, false);
    for (int act = 0; act < 4; ++act) {
        if (!rt.episode_in_use) break;
        FaultInjection fi = { 0 };
        fi.enabled = (act < 2);
        fi.fault_class = FAULT_I2C_PERSISTENT;
        fi.target_ref = r1;
        fi.trigger_action_index = (uint8_t)(act + 1);
        res.terminal_outcome = runtime_apply_policy(&rt, &fi);
    }
    /* Subsequent E2 executes */
    drain_queue(&rt, &res.preserved_work);

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 10, (int)v);
    return res;
}

/* CF11: Alternating Fault Classes */
static K10RunResult run_cf11(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 11, "CF11_ALTERNATING_CLASSES", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 11u, 1u);

    EventSlot e1 = { 0 }, e2 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = NORMAL; e1.transaction_id = 1101;
    e2.type = EVT_PERIPHERAL_WRITE; e2.peripheral = PERIPH_SPI0; e2.criticality = NORMAL; e2.transaction_id = 1102;
    EventRef r1, r2;
    runtime_admit(&rt, &e1, &r1);
    runtime_admit(&rt, &e2, &r2);

    /* I2C fault */
    runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, r1, 1101, NORMAL, true, true, true);
    FaultInjection fi = { 0 };
    runtime_apply_policy(&rt, &fi);

    /* SPI fault */
    runtime_start_fault(&rt, FAULT_SPI_TIMEOUT, ASSOC_EXACT, r2, 1102, NORMAL, true, true, true);
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 11, (int)v);
    return res;
}

/* CF12: Queue-Position Controls */
static K10RunResult run_cf12(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 12, "CF12_QUEUE_POSITION", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 12u, 1u);

    EventRef refs[5];
    for (int i = 0; i < 5; ++i) {
        EventSlot e = { 0 };
        e.type = EVT_PERIPHERAL_READ; e.peripheral = PERIPH_I2C0; e.criticality = NORMAL; e.transaction_id = (uint16_t)(1200 + i);
        runtime_admit(&rt, &e, &refs[i]);
    }

    /* Fault target at middle position (index 2) */
    runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, refs[2], 1202, NORMAL, true, true, true);
    drain_queue(&rt, &res.preserved_work); /* Should execute other 4 events */

    FaultInjection fi = { 0 };
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 12, (int)v);
    return res;
}

/* CF13: Low-Load Control */
static K10RunResult run_cf13(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 13, "CF13_LOW_LOAD_CONTROL", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 13u, 1u);

    EventSlot e1 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = NORMAL; e1.transaction_id = 1301;
    EventRef r1;
    runtime_admit(&rt, &e1, &r1);

    runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, r1, 1301, NORMAL, true, true, true);
    FaultInjection fi = { 0 };
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 13, (int)v);
    return res;
}

/* CF14: High-Load Control */
static K10RunResult run_cf14(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 14, "CF14_HIGH_LOAD_CONTROL", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 14u, 1u);

    EventRef refs[16];
    for (int i = 0; i < 16; ++i) {
        EventSlot e = { 0 };
        e.type = EVT_PERIPHERAL_READ; e.peripheral = PERIPH_I2C0; e.criticality = NORMAL; e.transaction_id = (uint16_t)(1400 + i);
        runtime_admit(&rt, &e, &refs[i]);
    }

    /* Fault target at index 0 */
    runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, refs[0], 1400, NORMAL, true, true, true);
    drain_queue(&rt, &res.preserved_work); /* 15 events preserved */

    FaultInjection fi = { 0 };
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 14, (int)v);
    return res;
}

/* CF15: Explicit Negative Control */
static K10RunResult run_cf15(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 15, "CF15_NEGATIVE_CONTROL", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 15u, 1u);

    EventSlot e1 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = NORMAL; e1.transaction_id = 1501;
    EventRef r1;
    runtime_admit(&rt, &e1, &r1);

    runtime_start_fault(&rt, FAULT_I2C_NACK, ASSOC_EXACT, r1, 1501, NORMAL, true, true, true);
    FaultInjection fi = { 0 }; /* transient retry succeeds */
    res.terminal_outcome = runtime_apply_policy(&rt, &fi);

    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 15, (int)v);
    return res;
}

/* CF16: Baseline Lower Cost Control */
static K10RunResult run_cf16(PolicyVariant v, int rep, int run_id, FILE *f_trace) {
    K10RunResult res = { run_id, 16, "CF16_BASELINE_LOWER_COST", (int)v, rep, OUTCOME_NONE, false, 0, 0, 0, 0, 0, ACT_NONE, true };
    Runtime rt; runtime_init(&rt, v);
    runtime_set_trace_metadata(&rt, (uint32_t)run_id, 16u, 1u);

    EventSlot e1 = { 0 };
    e1.type = EVT_PERIPHERAL_READ; e1.peripheral = PERIPH_I2C0; e1.criticality = CRITICAL; e1.transaction_id = 1601;
    EventRef r1;
    runtime_admit(&rt, &e1, &r1);

    /* Fault is known persistent I2C fault */
    runtime_start_fault(&rt, FAULT_I2C_PERSISTENT, ASSOC_EXACT, r1, 1601, CRITICAL, true, true, false);

    /* P2 chooses reinit immediately on attempt 0! P4 retries twice first! */
    OutcomeCode last_out = OUTCOME_NONE;
    for (int act = 0; act < 4; ++act) {
        if (!rt.episode_in_use) break;
        FaultInjection fi = { 0 };
        /* If action is retry, it fails; if action is reinit, it succeeds */
        PolicyDecision d = policy_decide(&rt, &rt.episode);
        fi.enabled = (d.action != ACT_REINIT_OR_RESET);
        fi.fault_class = FAULT_I2C_PERSISTENT;
        fi.target_ref = r1;
        fi.trigger_action_index = (uint8_t)(act + 1);
        last_out = runtime_apply_policy(&rt, &fi);
    }
    res.terminal_outcome = last_out;
    res.episode_active = rt.episode_in_use;
    res.recovery_attempts = (int)rt.episode.attempt_count;
    res.trace_records = (int)rt.trace_count;
    log_traces(f_trace, &rt, run_id, 16, (int)v);
    return res;
}

int main(int argc, char **argv) {
    const char *runs_path = "reference/experiments/out/k10_runs.csv";
    const char *trace_path = "reference/experiments/out/k10_traces.csv";
    if (argc >= 3) {
        runs_path = argv[1];
        trace_path = argv[2];
    }

    FILE *f_runs = fopen(runs_path, "w");
    FILE *f_trace = fopen(trace_path, "w");
    if (!f_runs || !f_trace) {
        fprintf(stderr, "Failed to open K10 output CSVs\n");
        return 1;
    }

    fprintf(f_runs, "run_id,family_id,family_name,variant_id,repetition,terminal_outcome,episode_active,recovery_attempts,preserved_work,blocked_work,trace_records,reason_code,final_action,harness_ok\n");
    fprintf(f_trace, "run_id,family_id,variant_id,trace_run_id,trace_seq,fault_episode_id,slot_id,generation,transaction_id,observation_seq,action_index,state,action,outcome,correctness\n");

    int run_id = 5000;
    int total_runs = 0;

    for (int rep = 1; rep <= K10_REPETITIONS; ++rep) {
        for (int fam = 1; fam <= K10_FAMILY_COUNT; ++fam) {
            for (int v = 0; v <= 4; ++v) {
                PolicyVariant var = (PolicyVariant)v;
                K10RunResult r = { 0 };
                switch (fam) {
                case 1: r = run_cf01(var, rep, run_id, f_trace); break;
                case 2: r = run_cf02(var, rep, run_id, f_trace); break;
                case 3: r = run_cf03(var, rep, run_id, f_trace); break;
                case 4: r = run_cf04(var, rep, run_id, f_trace); break;
                case 5: r = run_cf05(var, rep, run_id, f_trace); break;
                case 6: r = run_cf06(var, rep, run_id, f_trace); break;
                case 7: r = run_cf07(var, rep, run_id, f_trace); break;
                case 8: r = run_cf08(var, rep, run_id, f_trace); break;
                case 9: r = run_cf09(var, rep, run_id, f_trace); break;
                case 10: r = run_cf10(var, rep, run_id, f_trace); break;
                case 11: r = run_cf11(var, rep, run_id, f_trace); break;
                case 12: r = run_cf12(var, rep, run_id, f_trace); break;
                case 13: r = run_cf13(var, rep, run_id, f_trace); break;
                case 14: r = run_cf14(var, rep, run_id, f_trace); break;
                case 15: r = run_cf15(var, rep, run_id, f_trace); break;
                case 16: r = run_cf16(var, rep, run_id, f_trace); break;
                default: break;
                }
                log_run(f_runs, &r);
                run_id++;
                total_runs++;
            }
        }
    }

    fclose(f_runs);
    fclose(f_trace);

    printf("K10 Experiment complete: executed %d matched runs across %d case families and 5 variants.\n", total_runs, K10_FAMILY_COUNT);
    return 0;
}
