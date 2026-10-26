/* Exhaustively enumerates policy_decide() inputs (5 variants). Reports P4 reason-18 occurrences and any decision whose target_scope differs from association. Host check only. Built by run_probes.sh. */
#include "ref_runtime.h"
#include <stdio.h>
int main(void){
 unsigned long total=0,r18=0,scope_changed=0; unsigned seen[256]={0};
 for(int v=0;v<5;v++){Runtime rt;runtime_init(&rt,(PolicyVariant)v);
  for(int fc=0;fc<=FAULT_AMBIGUOUS;fc++)for(int as=0;as<4;as++)for(int at=0;at<=6;at++)for(int fl=0;fl<64;fl++)for(int es=0;es<3;es++)for(int act=0;act<2;act++){
   FaultContext c={0};c.fault_class=(FaultClass)fc;c.association=(AssociationLevel)as;c.attempt_count=(uint8_t)at;
   c.retry_safe=fl&1;c.reinit_safe=(fl>>1)&1;c.degrade_safe=(fl>>2)&1;c.dependencies_safe=(fl>>3)&1;c.shared_state_valid=(fl>>4)&1;c.criticality=(Criticality)((fl>>5)&1);
   c.episode_state=(EpisodeState)es;c.active=act;
   PolicyDecision d=policy_decide(&rt,&c);total++;if(v==4&&d.reason_code==18)r18++;if(v==4)seen[d.reason_code]++;
   if(d.target_scope!=c.association)scope_changed++;}}
 printf("contexts evaluated=%lu; P4 reason 18 occurrences=%lu; decisions whose target_scope != association=%lu\n",total,r18,scope_changed);
 printf("P4 reason codes seen:");for(int i=0;i<256;i++)if(seen[i])printf(" %d",i);printf("\n");return 0;}
