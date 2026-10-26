#!/usr/bin/env python3
"""Compute the source-derived policy_decide() outcome for every (policy, firmware context) pair.

Reads  : Plan2.0/firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix_diagnostic.c (context table)
         reference/src/ref_runtime.c, reference/include/ref_runtime.h (protected, read only)
Writes : research/manuscript/derived/source_derived_decisions.csv
Needs  : python3 and gcc. Run from anywhere:  python3 research/manuscript/scripts/derive_source_decisions.py

This is a HOST computation of what the protected policy_decide() returns for the same
context table the firmware uses. It is NOT a hardware measurement.
"""
import re, subprocess, sys, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
FW = ROOT / "Plan2.0/firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix_diagnostic.c"
OUT = ROOT / "research/manuscript/derived/source_derived_decisions.csv"

DRIVER = r'''
#include "ref_runtime.h"
#include <stdio.h>
typedef struct{uint8_t fault,assoc,attempt,criticality;bool retry,reinit,degrade,deps,shared;uint8_t id;}Sc;
static const Sc cases[16]={
@CASES@
};
int main(void){
 puts("policy,scenario,fault,assoc,attempt,retry_safe,reinit_safe,degrade_safe,deps_safe,shared_valid,start_outcome,action,reason,terminal,retry_authorized");
 for(int p=0;p<5;p++)for(int s=0;s<16;s++){
  Runtime rt;EventSlot sp={0};EventRef er;const Sc*c=&cases[s];
  runtime_init(&rt,(PolicyVariant)p);
  sp.type=EVT_PERIPHERAL_READ;sp.producer_id=1;sp.service_id=1;sp.consumer_id=1;
  sp.peripheral=PERIPH_I2C0;sp.criticality=(Criticality)c->criticality;
  sp.transaction_id=(uint16_t)(900000+p*16+s);sp.degradable=c->degrade;
  OutcomeCode o=runtime_admit(&rt,&sp,&er);
  if(o==OUTCOME_SUCCESS)o=runtime_start_fault(&rt,(FaultClass)c->fault,(AssociationLevel)c->assoc,er,
      sp.transaction_id,(Criticality)c->criticality,c->retry,c->reinit,c->degrade);
  PolicyDecision d={0};
  if(o==OUTCOME_SUCCESS){rt.episode.attempt_count=c->attempt;rt.episode.dependencies_safe=c->deps;
      rt.episode.shared_state_valid=c->shared;d=policy_decide(&rt,&rt.episode);}
  printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",p,s,c->fault,c->assoc,c->attempt,c->retry,
      c->reinit,c->degrade,c->deps,c->shared,o,d.action,d.reason_code,d.terminal,d.retry_authorized);
 }
 return 0;}
'''

def main():
    src = FW.read_text(encoding="utf-8")
    m = re.search(r"cases\[SC\]=\s*\{(.*?)\n\};", src, re.S)
    if not m:
        sys.exit("context table not found in firmware source")
    rows = re.findall(r"\{([^{}]*)\}", re.sub(r"\s+", "", m.group(1)))
    if len(rows) != 16:
        sys.exit(f"expected 16 contexts, found {len(rows)}")
    with tempfile.TemporaryDirectory() as td:
        td = Path(td)
        (td / "drv.c").write_text(DRIVER.replace("@CASES@", ",\n".join("{" + r + "}" for r in rows)))
        exe = td / "drv"
        subprocess.run(["gcc", "-std=c11", "-w", f"-I{ROOT/'reference/include'}", str(td / "drv.c"),
                        str(ROOT / "reference/src/ref_runtime.c"), "-o", str(exe)], check=True)
        out = subprocess.run([str(exe)], check=True, capture_output=True, text=True).stdout
    OUT.write_text(out, encoding="utf-8")
    print(f"wrote {OUT} ({len(out.splitlines())-1} decision rows)")

if __name__ == "__main__":
    main()
