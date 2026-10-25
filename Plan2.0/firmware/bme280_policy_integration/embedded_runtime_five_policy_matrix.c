/* Five-policy hardware/runtime matrix harness.
 * Uses the protected ref_runtime API. The 16 scenario rows remain provisional
 * and are NOT claimed to be identical to the frozen host corpus.
 * Hardware validation covers a controlled address NACK (0x77), then verifies
 * the real BME280 at 0x76 after any selected peripheral reinitialization.
 * Overall status: 1 = run complete with valid physical outcomes and all 80
 * decisions recorded; 2 = physical/hardware/runtime error; 3 = matrix incomplete.
 */
#include "stm32l476xx.h"
#include "ref_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#define I2C_TIMEOUT 1000000U
#define BME280_ADDRESS 0x76U
#define NACK_TEST_ADDRESS 0x77U
#define BME280_REG_ID 0xD0U
#define BME280_EXPECTED_ID 0x60U
#define I2C_TIMING_VALUE 0x30420F13U
#define PC 5U
#define SC 16U
#define RETRY_BOUND 3U
#define BASELINE_RETRIES 3U
#define BUS_RECOVERY_PULSES 9U
enum { E_OK=0,E_NACK=-1,E_BUS=-2,E_TIMEOUT=-3,E_ID=-4,E_READY=-5 };
enum { R_NOT_RUN=0,R_PASS=1,R_BASELINE_FAIL=2,R_NACK_FAIL=3,R_RUNTIME_FAIL=4,R_ACTION_FAIL=5,R_VERIFY_FAIL=6,R_TERMINAL=7,R_RETRY_LIMIT=8 };
enum { M_NOT_RUN=0,M_RECORDED=1,M_INVALID=2 };
typedef struct { uint8_t fault,assoc,attempt,criticality; bool retry,reinit,degrade,deps,shared; uint8_t id; } Scenario;
/* Provisional 16-context matrix; reconcile against the frozen host corpus before claiming exact correspondence. */
static const Scenario cases[SC]={
{FAULT_I2C_NACK,ASSOC_EXACT,0,NORMAL,0,1,0,1,1,0},
{FAULT_I2C_NACK,ASSOC_EXACT,1,NORMAL,1,1,0,1,1,1},
{FAULT_I2C_TIMEOUT,ASSOC_EXACT,0,NORMAL,1,1,0,1,1,2},
{FAULT_I2C_BERR,ASSOC_EXACT,1,NORMAL,1,1,0,1,1,3},
{FAULT_I2C_ARLO,ASSOC_EXACT,0,NORMAL,1,0,0,1,1,4},
{FAULT_I2C_PERSISTENT,ASSOC_EXACT,2,NORMAL,1,1,0,1,1,5},
{FAULT_I2C_PERSISTENT,ASSOC_EXACT,3,NORMAL,0,1,0,1,1,6},
{FAULT_SPI_TIMEOUT,ASSOC_EXACT,0,NORMAL,1,1,0,1,1,7},
{FAULT_SPI_VERIFY,ASSOC_EXACT,1,NORMAL,0,1,1,1,1,8},
{FAULT_SPI_PERSISTENT,ASSOC_EXACT,2,NORMAL,1,1,0,1,1,9},
{FAULT_SW_SERVICE,ASSOC_EXACT,0,NORMAL,1,0,1,1,1,10},
{FAULT_AMBIGUOUS,ASSOC_UNKNOWN,0,NORMAL,1,1,1,1,1,11},
{FAULT_I2C_NACK,ASSOC_SERVICE_ONLY,0,NORMAL,1,1,0,1,1,12},
{FAULT_I2C_TIMEOUT,ASSOC_PERIPHERAL_ONLY,1,NORMAL,1,1,0,1,1,13},
{FAULT_I2C_BERR,ASSOC_EXACT,1,NORMAL,0,0,0,0,1,14},
{FAULT_I2C_PERSISTENT,ASSOC_EXACT,2,NORMAL,0,1,0,1,0,15}};
volatile uint32_t finished=0, schema_version=1, overall_code=0;
volatile uint32_t physical_status[PC]={0}, baseline_ok[PC]={0};
volatile int32_t baseline_error[PC]={0}, nack_result[PC]={0}, reinit_result[PC]={E_READY};
volatile uint32_t nack_observed[PC]={0}, first_action[PC]={0}, first_reason[PC]={0};
volatile uint32_t retry_count[PC]={0}, reinit_attempted[PC]={0}, post_read_ok[PC]={0}, post_chip_id[PC]={0};
volatile uint32_t release_result[PC]={0}, terminal_action[PC]={0}, terminal_reason[PC]={0}, runtime_result[PC]={0};
volatile uint32_t matrix_status[PC*SC]={0}, matrix_policy[PC*SC]={0}, matrix_scenario[PC*SC]={0};
volatile uint32_t matrix_fault[PC*SC]={0}, matrix_assoc[PC*SC]={0}, matrix_action[PC*SC]={0}, matrix_reason[PC*SC]={0};
volatile uint32_t matrix_terminal[PC*SC]={0}, matrix_retry_authorized[PC*SC]={0}, matrix_runtime_start[PC*SC]={0};
volatile uint32_t diag_policy=0,diag_scenario=0,diag_phase=0,diag_isr=0,diag_gpio_idr=0;
static Runtime rt; static EventRef er;
static PolicyVariant variant(uint32_t p){static const PolicyVariant v[PC]={VAR_P0_FIXED_RETRY,VAR_P1_FIXED_RETRY_RECOVERY,VAR_P2_CONTEXT_ONLY,VAR_P3_CONTEXT_HISTORY,VAR_P4_INTEGRATED};return v[p];}
static void stop(void){finished=1;__BKPT(0);while(1){__NOP();}}
static void clr(void){I2C1->ICR=I2C_ICR_NACKCF|I2C_ICR_STOPCF|I2C_ICR_BERRCF|I2C_ICR_ARLOCF|I2C_ICR_OVRCF|I2C_ICR_TIMOUTCF;}
static int waitflag(uint32_t f){uint32_t n=I2C_TIMEOUT;while(n--){uint32_t s=I2C1->ISR;diag_isr=s;if(s&I2C_ISR_NACKF){I2C1->ICR=I2C_ICR_NACKCF;return E_NACK;}if(s&(I2C_ISR_BERR|I2C_ISR_ARLO|I2C_ISR_OVR|I2C_ISR_TIMEOUT)){clr();return E_BUS;}if(s&f)return E_OK;}diag_isr=I2C1->ISR;return E_TIMEOUT;}
/* Open-drain bus clear: only drives LOW or releases the lines. */
static int gpio_bus_clear(void){
    uint32_t n;
    const uint32_t pins=(1U<<8)|(1U<<9);
    RCC->AHB2ENR|=RCC_AHB2ENR_GPIOBEN;(void)RCC->AHB2ENR;
    /* Temporarily use GPIO open-drain outputs; ODR=1 means release. */
    GPIOB->MODER&=~((3U<<(8U*2U))|(3U<<(9U*2U)));
    GPIOB->OTYPER|=pins;
    GPIOB->PUPDR&=~((3U<<(8U*2U))|(3U<<(9U*2U)));
    GPIOB->MODER|=(1U<<(8U*2U))|(1U<<(9U*2U));
    GPIOB->BSRR=pins; /* release SCL/SDA */
    for(n=0;n<10000U;n++)__NOP();
    if((GPIOB->IDR&(1U<<8))==0U){
        /* SCL held low: do not force it high; cannot safely clock bus. */
        GPIOB->MODER&=~((3U<<(8U*2U))|(3U<<(9U*2U)));
        return E_BUS;
    }
    for(n=0;n<BUS_RECOVERY_PULSES && (GPIOB->IDR&(1U<<9))==0U;n++){
        GPIOB->BSRR=(1U<<(8U+16U)); /* SCL low */
        for(volatile uint32_t d=0;d<1000U;d++)__NOP();
        GPIOB->BSRR=(1U<<8); /* release SCL */
        for(volatile uint32_t d=0;d<1000U;d++)__NOP();
        if((GPIOB->IDR&(1U<<8))==0U)break;
    }
    /* Generate STOP: SDA low while SCL released, then release SDA. */
    GPIOB->BSRR=(1U<<(9U+16U));
    for(n=0;n<1000U;n++)__NOP();
    GPIOB->BSRR=(1U<<8);
    for(n=0;n<1000U;n++)__NOP();
    GPIOB->BSRR=(1U<<9);
    for(n=0;n<1000U;n++)__NOP();
    if((GPIOB->IDR&pins)!=pins){
        GPIOB->MODER&=~((3U<<(8U*2U))|(3U<<(9U*2U)));
        return E_BUS;
    }
    GPIOB->MODER&=~((3U<<(8U*2U))|(3U<<(9U*2U)));
    return E_OK;
}
static int iinit(void){uint32_t n;RCC->AHB2ENR|=RCC_AHB2ENR_GPIOBEN;(void)RCC->AHB2ENR;RCC->CR|=RCC_CR_HSION;n=I2C_TIMEOUT;while(!(RCC->CR&RCC_CR_HSIRDY))if(n--==0)return E_TIMEOUT;RCC->CCIPR&=~RCC_CCIPR_I2C1SEL;RCC->CCIPR|=(2U<<RCC_CCIPR_I2C1SEL_Pos);GPIOB->MODER&=~((3U<<16)|(3U<<18));GPIOB->MODER|=(2U<<16)|(2U<<18);GPIOB->OTYPER|=(1U<<8)|(1U<<9);GPIOB->OSPEEDR&=~((3U<<16)|(3U<<18));GPIOB->OSPEEDR|=(3U<<16)|(3U<<18);GPIOB->PUPDR&=~((3U<<16)|(3U<<18));GPIOB->AFR[1]&=~0xFFU;GPIOB->AFR[1]|=0x44U;RCC->APB1ENR1|=RCC_APB1ENR1_I2C1EN;(void)RCC->APB1ENR1;RCC->APB1RSTR1|=RCC_APB1RSTR1_I2C1RST;RCC->APB1RSTR1&=~RCC_APB1RSTR1_I2C1RST;I2C1->CR1=0;I2C1->TIMINGR=I2C_TIMING_VALUE;clr();I2C1->CR1=I2C_CR1_PE;return E_OK;}
static void abort_i2c_transfer(void){
    /* Abort a failed/ NACKed transaction before another attempt. */
    I2C1->CR2=0U;
    if((I2C1->ISR&I2C_ISR_BUSY)!=0U) I2C1->CR2=I2C_CR2_STOP;
    for(volatile uint32_t n=0;n<10000U;n++){
        if((I2C1->ISR&I2C_ISR_STOPF)!=0U)break;
    }
    clr();
    I2C1->CR1&=~I2C_CR1_PE;
    I2C1->CR1|=I2C_CR1_PE;
}
static int readreg(uint8_t a,uint8_t reg,uint8_t*v){int x;if(!v||!(I2C1->CR1&I2C_CR1_PE))return E_READY;clr();I2C1->CR2=((uint32_t)a<<1)|(1U<<I2C_CR2_NBYTES_Pos)|I2C_CR2_START;diag_phase=1;x=waitflag(I2C_ISR_TXIS);if(x){abort_i2c_transfer();return x;}I2C1->TXDR=reg;diag_phase=2;x=waitflag(I2C_ISR_TC);if(x){abort_i2c_transfer();return x;}I2C1->CR2=((uint32_t)a<<1)|I2C_CR2_RD_WRN|(1U<<I2C_CR2_NBYTES_Pos)|I2C_CR2_START|I2C_CR2_AUTOEND;diag_phase=3;x=waitflag(I2C_ISR_RXNE);if(x){abort_i2c_transfer();return x;}*v=(uint8_t)I2C1->RXDR;diag_phase=4;x=waitflag(I2C_ISR_STOPF);if(x){abort_i2c_transfer();return x;}I2C1->ICR=I2C_ICR_STOPCF;diag_phase=0;return E_OK;}
static int prepare(PolicyVariant v,uint32_t run,const Scenario*s){EventSlot sp={0};OutcomeCode o;runtime_init(&rt,v);runtime_set_trace_metadata(&rt,run,s->id,1);sp.type=EVT_PERIPHERAL_READ;sp.producer_id=1;sp.service_id=1;sp.consumer_id=1;sp.peripheral=PERIPH_I2C0;sp.criticality=(Criticality)s->criticality;sp.transaction_id=(uint16_t)run;sp.dependency_count=0;sp.degradable=s->degrade;o=runtime_admit(&rt,&sp,&er);if(o!=OUTCOME_SUCCESS)return o;o=runtime_start_fault(&rt,(FaultClass)s->fault,(AssociationLevel)s->assoc,er,sp.transaction_id,(Criticality)s->criticality,s->retry,s->reinit,s->degrade);if(o!=OUTCOME_SUCCESS)return o;rt.episode.attempt_count=s->attempt;rt.episode.dependencies_safe=s->deps;rt.episode.shared_state_valid=s->shared;return OUTCOME_SUCCESS;}
static void matrixcase(uint32_t p,uint32_t s){uint32_t k=p*SC+s;const Scenario*c=&cases[s];PolicyDecision d;diag_policy=p;diag_scenario=s;matrix_policy[k]=p;matrix_scenario[k]=c->id;matrix_fault[k]=c->fault;matrix_assoc[k]=c->assoc;matrix_status[k]=M_NOT_RUN;matrix_runtime_start[k]=prepare(variant(p),900000+k,c);if(matrix_runtime_start[k]!=OUTCOME_SUCCESS){matrix_status[k]=M_INVALID;return;}d=policy_decide(&rt,&rt.episode);matrix_action[k]=d.action;matrix_reason[k]=d.reason_code;matrix_terminal[k]=d.terminal;matrix_retry_authorized[k]=d.retry_authorized;matrix_status[k]=M_RECORDED;}
static void physical(uint32_t p){uint8_t id=0;int x=E_TIMEOUT;PolicyDecision d;const Scenario*c=&cases[0];diag_policy=p;physical_status[p]=R_NOT_RUN;
    /* Each policy begins with a clean peripheral and bounded baseline retries. */
    for(uint32_t attempt=0U;attempt<BASELINE_RETRIES;attempt++){
        x=iinit();
        if(x==E_OK){
            uint32_t pins=(GPIOB->IDR&((1U<<8)|(1U<<9)));
            if(pins!=((1U<<8)|(1U<<9))){
                (void)gpio_bus_clear();
                x=iinit();
            }
        }
        id=0U;
        if(x==E_OK)x=readreg(BME280_ADDRESS,BME280_REG_ID,&id);
        if(x==E_OK && id==BME280_EXPECTED_ID)break;
        /* Reset and clear the peripheral before the next bounded attempt. */
        (void)iinit();
    }
    baseline_error[p]=x;
    if(x||id!=BME280_EXPECTED_ID){physical_status[p]=R_BASELINE_FAIL;diag_gpio_idr=GPIOB->IDR;return;}
    baseline_ok[p]=1U;id=0;x=readreg(NACK_TEST_ADDRESS,BME280_REG_ID,&id);nack_result[p]=x;if(x!=E_NACK){physical_status[p]=R_NACK_FAIL;return;}nack_observed[p]=1;if(prepare(variant(p),8001+p,c)!=OUTCOME_SUCCESS){physical_status[p]=R_RUNTIME_FAIL;return;}d=policy_decide(&rt,&rt.episode);first_action[p]=d.action;first_reason[p]=d.reason_code;terminal_action[p]=d.action;terminal_reason[p]=d.reason_code;while(d.action==ACT_RETRY&&retry_count[p]<RETRY_BOUND){id=0;x=readreg(NACK_TEST_ADDRESS,BME280_REG_ID,&id);if(x!=E_NACK){physical_status[p]=R_ACTION_FAIL;goto done;}retry_count[p]++;if(rt.episode.attempt_count<UINT8_MAX)rt.episode.attempt_count++;if(rt.episode.observation_count<UINT8_MAX)rt.episode.observation_count++;d=policy_decide(&rt,&rt.episode);terminal_action[p]=d.action;terminal_reason[p]=d.reason_code;}if(d.action==ACT_RETRY){physical_status[p]=R_RETRY_LIMIT;runtime_result[p]=OUTCOME_FAILURE;goto done;}if(d.action==ACT_REINIT_OR_RESET){reinit_attempted[p]=1;reinit_result[p]=iinit();if(reinit_result[p]){physical_status[p]=R_ACTION_FAIL;goto done;}id=0;x=readreg(BME280_ADDRESS,BME280_REG_ID,&id);post_chip_id[p]=id;if(x||id!=BME280_EXPECTED_ID){physical_status[p]=R_VERIFY_FAIL;goto done;}post_read_ok[p]=1;rt.slots[er.slot_id].verification_ok=true;rt.slots[er.slot_id].shared_state_valid=true;release_result[p]=runtime_verify_and_release(&rt,true);if(release_result[p]!=OUTCOME_SUCCESS){physical_status[p]=R_VERIFY_FAIL;goto done;}physical_status[p]=R_PASS;runtime_result[p]=OUTCOME_SUCCESS;}else{runtime_result[p]=runtime_apply_policy(&rt,0);physical_status[p]=R_TERMINAL;}done:diag_gpio_idr=GPIOB->IDR;}
int main(void){
    finished=0U; overall_code=0U;
    for(uint32_t p=0U;p<PC;p++) physical(p);
    for(uint32_t p=0U;p<PC;p++) for(uint32_t s=0U;s<SC;s++) matrixcase(p,s);

    /* A terminal policy decision is a valid outcome, not a harness crash. */
    overall_code=1U;
    for(uint32_t p=0U;p<PC;p++) {
        if(physical_status[p]!=R_PASS && physical_status[p]!=R_TERMINAL)
            overall_code=2U;
    }
    for(uint32_t k=0U;k<PC*SC;k++) {
        if(matrix_status[k]!=M_RECORDED) { overall_code=3U; break; }
    }
    stop();
    return 0;
}
