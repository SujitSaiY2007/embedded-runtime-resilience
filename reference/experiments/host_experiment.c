#include "ref_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPS 512
#define MAX_SCHEDULES 128
#define MAX_EVENT_IDS 256

typedef struct { int workload_id, seq; char op[16]; int a,b,c,d,e; } WorkOp;
typedef struct {
    int schedule_id, action_index, fault_class, association, target_event_id, transaction_id;
    int criticality, retry_safe, reinit_safe, degrade_safe, enabled;
} Schedule;

static WorkOp ops[MAX_OPS];
static size_t op_count;
static Schedule schedules[MAX_SCHEDULES];
static size_t schedule_count;

static int csv_int(char *s) { return (s && *s) ? atoi(s) : 0; }

static int load_workloads(const char *path) {
    FILE *f=fopen(path,"r"); char line[256];
    if(!f) return 0;
    op_count=0;
    while(fgets(line,sizeof(line),f)) {
        if(line[0]=='#' || line[0]=='\n' || line[0]=='\r') continue;
        char *p=strtok(line,",\n\r"); if(!p) continue;
        if(op_count>=MAX_OPS) { fclose(f); return 0; }
        WorkOp *o=&ops[op_count++];
        o->workload_id=csv_int(p);
        p=strtok(NULL,",\n\r"); o->seq=csv_int(p);
        p=strtok(NULL,",\n\r"); strncpy(o->op,p?p:"",sizeof(o->op)-1u); o->op[sizeof(o->op)-1u]='\0';
        o->a=o->b=o->c=o->d=o->e=0;
        p=strtok(NULL,",\n\r"); o->a=csv_int(p);
        p=strtok(NULL,",\n\r"); o->b=csv_int(p);
        p=strtok(NULL,",\n\r"); o->c=csv_int(p);
        p=strtok(NULL,",\n\r"); o->d=csv_int(p);
        p=strtok(NULL,",\n\r"); o->e=csv_int(p);
    }
    fclose(f); return 1;
}

static int load_schedules(const char *path) {
    FILE *f=fopen(path,"r"); char line[256];
    if(!f) return 0;
    schedule_count=0;
    while(fgets(line,sizeof(line),f)) {
        if(line[0]=='#' || line[0]=='\n' || line[0]=='\r') continue;
        if(schedule_count>=MAX_SCHEDULES) { fclose(f); return 0; }
        char *p=strtok(line,",\n\r"); if(!p) continue;
        Schedule *s=&schedules[schedule_count++];
        s->schedule_id=csv_int(p);
        p=strtok(NULL,",\n\r"); s->action_index=csv_int(p);
        p=strtok(NULL,",\n\r"); s->fault_class=csv_int(p);
        p=strtok(NULL,",\n\r"); s->association=csv_int(p);
        p=strtok(NULL,",\n\r"); s->target_event_id=csv_int(p);
        p=strtok(NULL,",\n\r"); s->transaction_id=csv_int(p);
        p=strtok(NULL,",\n\r"); s->criticality=csv_int(p);
        p=strtok(NULL,",\n\r"); s->retry_safe=csv_int(p);
        p=strtok(NULL,",\n\r"); s->reinit_safe=csv_int(p);
        p=strtok(NULL,",\n\r"); s->degrade_safe=csv_int(p);
        p=strtok(NULL,",\n\r"); s->enabled=csv_int(p);
    }
    fclose(f); return 1;
}

static const Schedule *find_schedule(int id, int action_index) {
    for(size_t i=0;i<schedule_count;i++)
        if(schedules[i].schedule_id==id && schedules[i].action_index==action_index) return &schedules[i];
    return NULL;
}

static PeripheralId periph(int v) { return (PeripheralId)v; }
static Criticality crit(int v) { return (Criticality)v; }
static DependencyKind depkind(int v) { return (DependencyKind)v; }

static int run_one(FILE *runs, FILE *trace, int workload_id, PolicyVariant variant, int run_id) {
    Runtime rt; runtime_init(&rt,variant);
    runtime_set_trace_metadata(&rt,(uint32_t)run_id,(uint8_t)workload_id,0u);
    EventRef refs[MAX_EVENT_IDS]; bool have_ref[MAX_EVENT_IDS]={0};
    unsigned admissions=0, admission_failures=0, queue_hwm=0, quarantine_hwm=0;
    OutcomeCode terminal=OUTCOME_NONE; int harness_ok=1; int last_trace_seq=0;

    for(size_t i=0;i<op_count;i++) {
        WorkOp *o=&ops[i];
        if(o->workload_id!=workload_id) continue;
        if(strcmp(o->op,"ADMIT")==0) {
            EventSlot e={0};
            e.type=EVT_PERIPHERAL_READ; e.producer_id=1u; e.service_id=(uint8_t)o->b; e.consumer_id=(uint8_t)o->b;
            e.peripheral=periph(o->c); e.criticality=crit(o->d); e.transaction_id=(uint16_t)o->e;
            e.degradable=e.criticality!=CRITICAL; e.shared_state_valid=true;
            OutcomeCode out=runtime_admit(&rt,&e,&refs[o->a]);
            if(out==OUTCOME_SUCCESS){have_ref[o->a]=true; admissions++;}
            else admission_failures++;
        } else if(strcmp(o->op,"DEPEND")==0) {
            if(!have_ref[o->a] || !have_ref[o->b]) harness_ok=0;
            else if(runtime_add_dependency(&rt,refs[o->a],refs[o->b],depkind(o->c),(EventState)o->d)!=OUTCOME_SUCCESS) harness_ok=0;
        } else if(strcmp(o->op,"START")==0) {
            const Schedule *s=find_schedule(o->a,0);
            if(!s) { harness_ok=0; continue; }
            runtime_set_trace_metadata(&rt,(uint32_t)run_id,(uint8_t)workload_id,(uint8_t)o->a);
            EventRef target=event_ref_invalid();
            if(s->target_event_id>=0) {
                if(!have_ref[s->target_event_id]) harness_ok=0;
                else target=refs[s->target_event_id];
            }
            OutcomeCode out=runtime_start_fault(&rt,(FaultClass)s->fault_class,(AssociationLevel)s->association,
                target,(uint16_t)s->transaction_id,(Criticality)s->criticality,
                s->retry_safe!=0,s->reinit_safe!=0,s->degrade_safe!=0);
            if(out==OUTCOME_EPISODE_FULL && workload_id!=10) harness_ok=0;
        } else if(strcmp(o->op,"REUSE_CHECK")==0) {
            if(!have_ref[o->a]) { harness_ok=0; continue; }
            EventRef old=refs[o->a], fresh;
            EventSlot e={0};
            e.type=EVT_PERIPHERAL_READ; e.producer_id=1u; e.service_id=(uint8_t)o->b; e.consumer_id=(uint8_t)o->b;
            e.peripheral=periph(o->c); e.criticality=crit(o->d); e.transaction_id=(uint16_t)o->e;
            e.degradable=e.criticality!=CRITICAL; e.shared_state_valid=true;
            if(runtime_admit(&rt,&e,&fresh)!=OUTCOME_SUCCESS ||
               fresh.slot_id!=old.slot_id || fresh.generation==old.generation ||
               event_ref_valid(&rt,old) || !event_ref_valid(&rt,fresh)) harness_ok=0;
        } else if(strcmp(o->op,"DRAIN")==0) {
            for(unsigned guard=0;guard<64u;guard++) {
                EventRef selected;
                if(!scheduler_select(&rt,&selected)) break;
                OutcomeCode out=runtime_execute_selected(&rt,selected,NULL,NULL);
                if(out!=OUTCOME_SUCCESS && out!=OUTCOME_FAILURE) { harness_ok=0; break; }
            }
        } else if(strcmp(o->op,"APPLY")==0) {
            unsigned next_action=(unsigned)rt.episode.attempt_count+1u;
            const Schedule *s=find_schedule(o->a,(int)next_action);
            FaultInjection fi={0};
            const FaultInjection *fp=NULL;
            if(s) {
                fi.fault_class=(FaultClass)s->fault_class;
                fi.target_ref=rt.episode.target_ref;
                fi.transaction_id=(uint16_t)s->transaction_id;
                fi.trigger_action_index=(uint8_t)s->action_index;
                fi.remaining_failures=0u;
                fi.enabled=s->enabled!=0;
                fp=&fi;
            }
            OutcomeCode out=runtime_apply_policy(&rt,fp);
            if(out==OUTCOME_TERMINAL_DEGRADE || out==OUTCOME_TERMINAL_ESCALATE) terminal=out;
            if(rt.episode.attempt_count>3u) harness_ok=0;
        }
        if(rt.queue_count>queue_hwm) queue_hwm=rt.queue_count;
        if(rt.quarantine_count>quarantine_hwm) quarantine_hwm=rt.quarantine_count;
    }

    if(rt.episode_in_use) terminal=OUTCOME_NONE;
    for(uint16_t i=0;i<rt.trace_count;i++) {
        const TraceRecord *t=&rt.trace[i];
        if((int)t->trace_seq<=last_trace_seq || t->run_id!=(uint32_t)run_id) harness_ok=0;
        last_trace_seq=(int)t->trace_seq;
        fprintf(trace,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (unsigned)run_id,(unsigned)variant,(unsigned)workload_id,
            (unsigned)t->run_id,(unsigned)t->trace_seq,(unsigned)t->fault_episode_id,
            (unsigned)t->event_ref.slot_id,(unsigned)t->event_ref.generation,
            (unsigned)t->transaction_id,(unsigned)t->observation_seq,(unsigned)t->action_index,
            (unsigned)t->state,(unsigned)t->action,(unsigned)t->outcome,(unsigned)t->correctness,
            (unsigned)(t->event_ref.slot_id<ACTIVE_MAX));
    }

    int capacity_confounded=(workload_id==9 || workload_id==10);
    int ablation_contract_valid=(variant==VAR_P4_INTEGRATED);
    const char *terminal_name=terminal==OUTCOME_TERMINAL_DEGRADE?"TERMINAL_DEGRADE":
        terminal==OUTCOME_TERMINAL_ESCALATE?"TERMINAL_ESCALATE":
        rt.episode_in_use?"ACTIVE":"NO_TERMINAL";
    fprintf(runs,"%d,%d,%d,%d,%d,%u,%u,%u,%u,%u,%u,%d,%s,%s,%s\n",
        run_id,(int)variant,workload_id,capacity_confounded,ablation_contract_valid,
        admissions,admission_failures,queue_hwm,quarantine_hwm,(unsigned)rt.trace_count,
        (unsigned)rt.episode.attempt_count,harness_ok,terminal_name,
        capacity_confounded?"CAPACITY_CONFOUNDED":"OK",
        ablation_contract_valid?"VALID_ABLATION_INPUT":"P0_P3_QUARANTINE_GAP");
    return harness_ok;
}

int main(int argc,char **argv) {
    if(argc!=5) { fprintf(stderr,"usage: host_experiment workloads.csv fault_schedules.csv runs.csv trace.csv\n"); return 2; }
    if(!load_workloads(argv[1]) || !load_schedules(argv[2])) { fprintf(stderr,"input load failed\n"); return 2; }
    FILE *runs=fopen(argv[3],"w"), *trace=fopen(argv[4],"w");
    if(!runs || !trace) { fprintf(stderr,"output open failed\n"); return 2; }
    fprintf(runs,"run_id,variant_id,workload_id,capacity_confounded,ablation_contract_valid,admissions,admission_failures,queue_hwm,quarantine_hwm,trace_records,recovery_attempts,harness_correctness,terminal_outcome,capacity_status,ablation_status\n");
    fprintf(trace,"run_id,variant_id,workload_id,trace_run_id,trace_seq,fault_episode_id,slot_id,generation,transaction_id,observation_seq,action_index,state,action,outcome,correctness,event_ref_slot_in_range\n");
    int all_ok=1, run_id=1000;
    int workloads_seen[256]={0};
    for(size_t i=0;i<op_count;i++) workloads_seen[ops[i].workload_id]=1;
    for(int w=1;w<256;w++) if(workloads_seen[w]) {
        for(int v=0;v<=4;v++) if(!run_one(runs,trace,w,(PolicyVariant)v,run_id++)) all_ok=0;
    }
    fclose(runs); fclose(trace);
    return all_ok?0:1;
}
