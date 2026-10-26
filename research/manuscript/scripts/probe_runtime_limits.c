/* Scratch probes of the protected runtime: (1) admit+complete until admission fails; (2) release into a full queue. Run with and without -DNDEBUG (see run_probes.sh). Host check only; the runtime is not modified. */
#include "ref_runtime.h"
#include <stdio.h>
static EventSlot spec(void){EventSlot s={0};s.type=EVT_PERIPHERAL_READ;s.peripheral=PERIPH_I2C0;s.criticality=NORMAL;s.service_id=1;return s;}
int main(void){
 printf("sizeof(Runtime)=%zu sizeof(EventSlot)=%zu trace_bytes=%zu (host build, not MCU)\n",runtime_static_bytes(),runtime_slot_bytes(),runtime_trace_bytes());
 /* Probe 1: generation exhaustion via repeated admit+complete */
 {Runtime rt;runtime_init(&rt,VAR_P4_INTEGRATED);int n=0;for(;n<1000;n++){EventSlot s=spec();EventRef r;OutcomeCode o=runtime_admit(&rt,&s,&r);if(o!=OUTCOME_SUCCESS){printf("probe1: admit #%d failed with outcome %d while queue_count=%u\n",n+1,o,rt.queue_count);break;}
   EventRef sel;bool f;if(scheduler_select(&rt,&sel))runtime_execute_selected(&rt,sel,0,&f);}
 }
 /* Probe 2: release into a full queue */
 {Runtime rt;runtime_init(&rt,VAR_P4_INTEGRATED);EventRef first,r;EventSlot s=spec();runtime_admit(&rt,&s,&first);
  for(int i=0;i<15;i++){s=spec();runtime_admit(&rt,&s,&r);}
  OutcomeCode o=runtime_start_fault(&rt,FAULT_I2C_NACK,ASSOC_EXACT,first,1,NORMAL,true,true,false);
  printf("probe2: start_fault=%d queue_count=%u\n",o,rt.queue_count);
  s=spec();o=runtime_admit(&rt,&s,&r);printf("probe2: refill admit=%d queue_count=%u\n",o,rt.queue_count);
  o=runtime_apply_policy(&rt,0);printf("probe2: apply_policy(retry then verify/release)=%d queue_count=%u\n",o,rt.queue_count);}
 return 0;}
