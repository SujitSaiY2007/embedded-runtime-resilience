#include "ref_runtime.h"
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

static EventRef ref_of(const EventSlot *e) { EventRef r={e->slot_id,e->generation}; return r; }
EventRef event_ref_invalid(void) { EventRef r={INVALID_SLOT,0u}; return r; }
bool event_ref_equal(EventRef a, EventRef b) { return a.slot_id==b.slot_id && a.generation==b.generation; }
static bool state_terminal(EventState s) { return s==ST_COMPLETED || s==ST_DISCARDED || s==ST_ESCALATED; }

bool event_ref_valid(const Runtime *rt, EventRef ref) {
    if (ref.slot_id>=ACTIVE_MAX) return false;
    const EventSlot *e=&rt->slots[ref.slot_id];
    return e->state!=ST_FREE && !state_terminal(e->state) && e->generation==ref.generation;
}

static uint8_t next_generation(Runtime *rt, uint8_t slot) {
    if (rt->generation_next[slot]==UINT8_MAX) return 0u;
    ++rt->generation_next[slot];
    if (rt->generation_next[slot]==0u) return 0u;
    return rt->generation_next[slot];
}

static void trace_event(Runtime *rt, const EventSlot *e, RecoveryAction action, OutcomeCode outcome) {
    if (rt->trace_count>=TRACE_EVENT_CAP) return;
    TraceRecord *t=&rt->trace[rt->trace_count++];
    t->run_id=rt->run_id;
    t->trace_seq=++rt->trace_seq;
    t->fault_episode_id=rt->active_fault_episode_id;
    t->event_ref=ref_of(e);
    t->transaction_id=e->transaction_id;
    t->observation_seq=rt->episode.observation_count;
    t->action_index=rt->episode.attempt_count;
    t->state=(uint8_t)e->state;
    t->action=(uint8_t)action;
    t->outcome=(uint8_t)outcome;
    t->correctness=(outcome==OUTCOME_NONE || outcome==OUTCOME_SUCCESS)?1u:0u;
}

void runtime_set_trace_metadata(Runtime *rt,uint32_t run_id,uint8_t workload_id,uint8_t fault_schedule_id){rt->run_id=run_id;rt->workload_id=workload_id;rt->fault_schedule_id=fault_schedule_id;}

void runtime_init(Runtime *rt, PolicyVariant variant) {
    memset(rt,0,sizeof(*rt)); rt->variant=variant;
    for(uint8_t i=0u;i<ACTIVE_MAX;++i){rt->slots[i].slot_id=i;rt->slots[i].state=ST_FREE;}
    rt->episode.target_ref=event_ref_invalid();
}

static int find_free_slot(const Runtime *rt) {
    for(uint8_t i=0u;i<ACTIVE_MAX;++i) if(rt->slots[i].state==ST_FREE || state_terminal(rt->slots[i].state)) return (int)i;
    return -1;
}
static int queue_pos(const Runtime *rt,uint8_t slot){for(uint8_t i=0u;i<rt->queue_count;++i)if(rt->queue[i]==slot)return (int)i;return -1;}
static void queue_remove(Runtime *rt,uint8_t slot){int p=queue_pos(rt,slot);if(p<0)return;for(uint8_t i=(uint8_t)p;i+1u<rt->queue_count;++i)rt->queue[i]=rt->queue[i+1u];--rt->queue_count;}
static void queue_append(Runtime *rt,uint8_t slot){assert(rt->queue_count<QMAX);rt->queue[rt->queue_count++]=slot;}

OutcomeCode runtime_admit(Runtime *rt,const EventSlot *spec,EventRef *out_ref){
    if(rt->queue_count>=QMAX)return OUTCOME_QUEUE_FULL;
    int idx=find_free_slot(rt);if(idx<0)return OUTCOME_QUEUE_FULL;
    uint8_t g=next_generation(rt,(uint8_t)idx);if(g==0u)return OUTCOME_STALE_REF;
    EventSlot *e=&rt->slots[idx];*e=*spec;e->slot_id=(uint8_t)idx;e->generation=g;e->state=ST_QUEUED;e->fault_associated=false;e->verification_ok=false;e->shared_state_valid=true;
    rt->queue[rt->queue_count++]=(uint8_t)idx;if(out_ref)*out_ref=ref_of(e);trace_event(rt,e,ACT_NONE,OUTCOME_NONE);return OUTCOME_SUCCESS;
}

OutcomeCode runtime_add_dependency(Runtime *rt,EventRef target,EventRef predecessor,DependencyKind kind,EventState acceptable_state){
    if(!event_ref_valid(rt,target)||!event_ref_valid(rt,predecessor))return OUTCOME_STALE_REF;
    EventSlot *e=&rt->slots[target.slot_id];if(e->dependency_count>=DMAX)return OUTCOME_INVALID_DEPENDENCY;
    e->dependencies[e->dependency_count].referenced=predecessor;e->dependencies[e->dependency_count].kind=kind;e->dependencies[e->dependency_count].acceptable_state=(uint8_t)acceptable_state;++e->dependency_count;return OUTCOME_SUCCESS;
}

static const EventSlot *slot_from_ref(const Runtime *rt,EventRef r){return event_ref_valid(rt,r)?&rt->slots[r.slot_id]:NULL;}
bool dependency_allows(const Runtime *rt,const EventSlot *event){
    for(uint8_t i=0u;i<event->dependency_count;++i){const DependencyEntry*d=&event->dependencies[i];const EventSlot*p=slot_from_ref(rt,d->referenced);if(p==NULL)return false;if(d->kind==DEP_ORDERED&&p->state!=(EventState)d->acceptable_state)return false;if(d->kind==DEP_COUPLED&&(!p->verification_ok||!p->shared_state_valid))return false;}return true;
}
bool ordinary_dispatch_allowed(const Runtime *rt,const EventSlot *event){return (event->state==ST_QUEUED||event->state==ST_ELIGIBLE)&&!event->fault_associated&&event->shared_state_valid&&dependency_allows(rt,event);}

bool scheduler_select(Runtime *rt,EventRef*selected){
    for(uint8_t i=0u;i<rt->queue_count;++i){EventSlot*e=&rt->slots[rt->queue[i]];if(e->state==ST_QUEUED&&dependency_allows(rt,e))e->state=ST_ELIGIBLE;if(ordinary_dispatch_allowed(rt,e)){if(selected)*selected=ref_of(e);return true;}}return false;
}

bool fault_injection_triggers(const FaultInjection*fault,EventRef ref,uint8_t action_index){return fault!=NULL&&fault->enabled&&event_ref_equal(fault->target_ref,ref)&&fault->trigger_action_index==action_index;}

OutcomeCode runtime_execute_selected(Runtime *rt,EventRef selected,const FaultInjection*fault,bool*faulted){
    if(faulted)*faulted=false;if(!event_ref_valid(rt,selected))return OUTCOME_STALE_REF;EventSlot*e=&rt->slots[selected.slot_id];if(!ordinary_dispatch_allowed(rt,e))return OUTCOME_INVALID_DEPENDENCY;e->state=ST_EXECUTING;
    if(fault_injection_triggers(fault,selected,0u)){e->state=ST_FAILED;if(faulted)*faulted=true;trace_event(rt,e,ACT_NONE,OUTCOME_FAILURE);return OUTCOME_FAILURE;}
    e->verification_ok=true;e->state=ST_COMPLETED;queue_remove(rt,e->slot_id);trace_event(rt,e,ACT_NONE,OUTCOME_SUCCESS);return OUTCOME_SUCCESS;
}

static bool precision_leq(AssociationLevel a,AssociationLevel evidence){return (uint8_t)a>=(uint8_t)evidence;}

PolicyDecision policy_decide(const Runtime*rt,const FaultContext*ctx){
    PolicyDecision d={ACT_NONE,ctx->association,false,false,false,false,ctx->attempt_count,0u};if(!ctx->active||ctx->episode_state==EP_TERMINAL)return d;
    bool ambiguity=ctx->association==ASSOC_UNKNOWN;
    switch(rt->variant){
    case VAR_P0_FIXED_RETRY:
        if(ctx->attempt_count<2u){d.action=ACT_RETRY;d.retry_authorized=true;d.reason_code=1u;}else{d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=2u;}break;
    case VAR_P1_FIXED_RETRY_RECOVERY:
        if(ctx->attempt_count<2u&&ctx->retry_safe){d.action=ACT_RETRY;d.retry_authorized=true;d.reason_code=3u;}else if(ctx->reinit_safe&&ctx->attempt_count<3u){d.action=ACT_REINIT_OR_RESET;d.reason_code=4u;}else if(ctx->degrade_safe){d.action=ACT_DEGRADE;d.terminal=true;d.reason_code=5u;}else{d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=6u;}break;
    case VAR_P2_CONTEXT_ONLY:
        if(ambiguity||!ctx->dependencies_safe||!ctx->shared_state_valid){d.action=ctx->degrade_safe?ACT_DEGRADE:ACT_ESCALATE;d.terminal=true;d.reason_code=7u;}else if((ctx->fault_class==FAULT_I2C_PERSISTENT||ctx->fault_class==FAULT_SPI_PERSISTENT)&&ctx->reinit_safe){d.action=ACT_REINIT_OR_RESET;d.reason_code=8u;}else if(ctx->retry_safe){d.action=ACT_RETRY;d.retry_authorized=true;d.reason_code=9u;}else if(ctx->degrade_safe){d.action=ACT_DEGRADE;d.terminal=true;d.reason_code=10u;}else{d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=11u;}break;
    case VAR_P3_CONTEXT_HISTORY:
        if(ambiguity||!ctx->dependencies_safe||!ctx->shared_state_valid){d.action=ctx->degrade_safe?ACT_DEGRADE:ACT_ESCALATE;d.terminal=true;d.reason_code=12u;}else if(ctx->attempt_count>=2u&&ctx->reinit_safe){d.action=ACT_REINIT_OR_RESET;d.reason_code=13u;}else if(ctx->retry_safe&&ctx->attempt_count<2u){d.action=ACT_RETRY;d.retry_authorized=true;d.reason_code=14u;}else if(ctx->degrade_safe){d.action=ACT_DEGRADE;d.terminal=true;d.reason_code=15u;}else{d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=16u;}break;
    case VAR_P4_INTEGRATED:
        if(ctx->association!=ASSOC_EXACT){d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=17u;}else if(ambiguity&&!ctx->degrade_safe){d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=18u;}else if(!ctx->dependencies_safe||!ctx->shared_state_valid){d.action=ctx->degrade_safe?ACT_DEGRADE:ACT_ESCALATE;d.terminal=true;d.reason_code=19u;}else if(ctx->attempt_count>=3u){d.action=ctx->degrade_safe?ACT_DEGRADE:ACT_ESCALATE;d.terminal=true;d.reason_code=20u;}else if(ctx->attempt_count>=2u){d.action=ctx->reinit_safe?ACT_REINIT_OR_RESET:(ctx->degrade_safe?ACT_DEGRADE:ACT_ESCALATE);d.terminal=d.action>=ACT_DEGRADE;d.reason_code=21u;}else if(ctx->retry_safe){d.action=ACT_RETRY;d.retry_authorized=true;d.reason_code=22u;}else if(ctx->reinit_safe){d.action=ACT_REINIT_OR_RESET;d.reason_code=23u;}else if(ctx->degrade_safe){d.action=ACT_DEGRADE;d.terminal=true;d.reason_code=24u;}else{d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=25u;}break;
    default:d.action=ACT_ESCALATE;d.terminal=true;d.reason_code=255u;break;}
    if(!precision_leq(d.target_scope,ctx->association))d.target_scope=ctx->association;return d;
}

OutcomeCode runtime_start_fault(Runtime*rt,FaultClass fault,AssociationLevel assoc,EventRef target,uint16_t tx_id,Criticality criticality,bool retry_safe,bool reinit_safe,bool degrade_safe){
    if(rt->episode_in_use)return OUTCOME_EPISODE_FULL;if(assoc==ASSOC_EXACT&&!event_ref_valid(rt,target))return OUTCOME_STALE_REF;rt->episode_in_use=true;rt->episode.active=true;
    if(rt->fault_episode_id_next==UINT32_MAX){rt->episode_in_use=false;rt->episode.active=false;return OUTCOME_EPISODE_FULL;}rt->active_fault_episode_id=++rt->fault_episode_id_next;
    rt->episode.episode_state=EP_ACTIVE;rt->episode.fault_class=fault;rt->episode.association=assoc;rt->episode.attempt_count=0u;rt->episode.criticality=criticality;rt->episode.retry_safe=retry_safe;rt->episode.reinit_safe=reinit_safe;rt->episode.degrade_safe=degrade_safe;rt->episode.dependencies_safe=true;rt->episode.shared_state_valid=true;rt->episode.target_ref=target;rt->episode.target_transaction=tx_id;rt->episode.service_id=event_ref_valid(rt,target)?rt->slots[target.slot_id].service_id:0u;rt->episode.peripheral=event_ref_valid(rt,target)?rt->slots[target.slot_id].peripheral:PERIPH_NONE;rt->episode.observation_count=1u;
    if(assoc==ASSOC_EXACT){EventSlot*e=&rt->slots[target.slot_id];if(rt->quarantine_count>=XMAX){rt->episode_in_use=false;rt->episode.active=false;rt->active_fault_episode_id=0u;return OUTCOME_QUARANTINE_FULL;}e->fault_associated=true;e->state=ST_QUARANTINED;queue_remove(rt,e->slot_id);++rt->quarantine_count;trace_event(rt,e,ACT_NONE,OUTCOME_FAILURE);}return OUTCOME_SUCCESS;
}

static void close_episode(Runtime*rt,EventState terminal_state){
    if(event_ref_valid(rt,rt->episode.target_ref)){EventSlot*e=&rt->slots[rt->episode.target_ref.slot_id];if(e->state==ST_QUARANTINED||e->state==ST_RETRY_PENDING){if(rt->quarantine_count>0u)--rt->quarantine_count;e->fault_associated=false;e->state=terminal_state;trace_event(rt,e,terminal_state==ST_DISCARDED?ACT_DEGRADE:ACT_ESCALATE,terminal_state==ST_DISCARDED?OUTCOME_TERMINAL_DEGRADE:OUTCOME_TERMINAL_ESCALATE);}}
    rt->episode.episode_state=EP_TERMINAL;rt->episode.active=false;rt->episode_in_use=false;rt->active_fault_episode_id=0u;
}

OutcomeCode runtime_apply_policy(Runtime*rt,const FaultInjection*fault){
    if(!rt->episode_in_use)return OUTCOME_NONE;PolicyDecision d=policy_decide(rt,&rt->episode);EventRef target=rt->episode.target_ref;if(d.action==ACT_NONE)return OUTCOME_NONE;
    if(d.action==ACT_RETRY||d.action==ACT_REINIT_OR_RESET){if(!event_ref_valid(rt,target))return OUTCOME_STALE_REF;EventSlot*e=&rt->slots[target.slot_id];e->state=d.action==ACT_RETRY?ST_RETRY_PENDING:ST_QUARANTINED;uint8_t action_index=(uint8_t)(rt->episode.attempt_count+1u);trace_event(rt,e,d.action,OUTCOME_NONE);bool failed=fault_injection_triggers(fault,target,action_index);++rt->episode.attempt_count;if(failed){e->state=ST_QUARANTINED;e->verification_ok=false;++rt->episode.observation_count;trace_event(rt,e,d.action,OUTCOME_FAILURE);return OUTCOME_FAILURE;}e->verification_ok=true;e->shared_state_valid=true;return runtime_verify_and_release(rt,true);}
    if(d.action==ACT_DEGRADE){close_episode(rt,ST_DISCARDED);return OUTCOME_TERMINAL_DEGRADE;}close_episode(rt,ST_ESCALATED);return OUTCOME_TERMINAL_ESCALATE;
}

OutcomeCode runtime_verify_and_release(Runtime*rt,bool verification_ok){
    if(!rt->episode_in_use)return OUTCOME_NONE;EventRef target=rt->episode.target_ref;if(!event_ref_valid(rt,target))return OUTCOME_STALE_REF;EventSlot*e=&rt->slots[target.slot_id];if(!verification_ok||!e->verification_ok||!e->shared_state_valid||!dependency_allows(rt,e))return OUTCOME_FAILURE;e->state=ST_QUEUED;e->fault_associated=false;if(rt->quarantine_count>0u)--rt->quarantine_count;queue_append(rt,e->slot_id);trace_event(rt,e,ACT_NONE,OUTCOME_SUCCESS);rt->episode.episode_state=EP_TERMINAL;rt->episode.active=false;rt->episode_in_use=false;rt->active_fault_episode_id=0u;return OUTCOME_SUCCESS;
}

static size_t append_u32(char*buf,size_t pos,size_t cap,uint32_t value){char tmp[10];size_t n=0u;do{tmp[n++]=(char)('0'+(value%10u));value/=10u;}while(value!=0u);while(n!=0u&&pos<cap)buf[pos++]=tmp[--n];return pos;}
size_t trace_write_csv(const Runtime*rt,int fd){
    static const char header[]="run_id,workload_id,fault_schedule_id,trace_seq,fault_episode_id,slot_id,generation,transaction_id,observation_seq,action_index,state,action,outcome,correctness\n";size_t written=0u;ssize_t n=write(fd,header,sizeof(header)-1u);if(n<0)return 0u;written+=(size_t)n;
    for(uint16_t i=0u;i<rt->trace_count;++i){const TraceRecord*t=&rt->trace[i];char line[192];size_t p=0u;p=append_u32(line,p,sizeof(line),t->run_id);line[p++]=',';p=append_u32(line,p,sizeof(line),rt->workload_id);line[p++]=',';p=append_u32(line,p,sizeof(line),rt->fault_schedule_id);line[p++]=',';p=append_u32(line,p,sizeof(line),t->trace_seq);line[p++]=',';p=append_u32(line,p,sizeof(line),t->fault_episode_id);line[p++]=',';p=append_u32(line,p,sizeof(line),t->event_ref.slot_id);line[p++]=',';p=append_u32(line,p,sizeof(line),t->event_ref.generation);line[p++]=',';p=append_u32(line,p,sizeof(line),t->transaction_id);line[p++]=',';p=append_u32(line,p,sizeof(line),t->observation_seq);line[p++]=',';p=append_u32(line,p,sizeof(line),t->action_index);line[p++]=',';p=append_u32(line,p,sizeof(line),t->state);line[p++]=',';p=append_u32(line,p,sizeof(line),t->action);line[p++]=',';p=append_u32(line,p,sizeof(line),t->outcome);line[p++]=',';p=append_u32(line,p,sizeof(line),t->correctness);line[p++]='\n';n=write(fd,line,p);if(n<0)break;written+=(size_t)n;}return written;
}
size_t runtime_slot_bytes(void){return sizeof(EventSlot);}size_t runtime_trace_bytes(void){return sizeof(TraceRecord)*TRACE_EVENT_CAP;}size_t runtime_static_bytes(void){return sizeof(Runtime);}
