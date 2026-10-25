#include "stm32l476xx.h"
#include "ref_runtime.h"
#include <stdint.h>
#include <stdio.h>
/* Provided by the semihosting support library when rdimon is linked. */
extern void initialise_monitor_handles(void);
/*
 * BME280 controlled I2C transaction and reinitialization test.
 *
 * Hardware:
 *   STM32L476RG / NUCLEO-L476RG
 *   SCL = PB8 / AF4 / I2C1_SCL
 *   SDA = PB9 / AF4 / I2C1_SDA
 *   BME280 address = 0x76
 *   BME280 chip-ID register = 0xD0
 *   Expected chip ID = 0x60
 *
 * The test attempts address 0x77 as a controlled NACK stimulus.
 * It is accepted only if the I2C peripheral reports NACK.
 * This is transaction-level NACK/reinitialization testing, NOT
 * proof of recovery from a physically stuck bus.
 *
 * Semihosting:
 *   Build/link with --specs=rdimon.specs (not --specs=nosys.specs)
 *   and run under a debugger that supports semihosting.
 */
#define I2C_TIMEOUT          1000000U
#define BME280_ADDRESS       0x76U
#define NACK_TEST_ADDRESS    0x77U
#define BME280_REG_ID        0xD0U
#define BME280_EXPECTED_ID   0x60U
#define I2C_TIMING_VALUE     0x30420F13U
typedef enum
{
    TEST_NOT_STARTED = 0,
    BASELINE_PASSED = 1,
    NACK_CONFIRMED = 2,
    RECOVERY_PASSED = 3,
    BASELINE_FAILED = 4,
    NACK_NOT_CONFIRMED = 5,
    RECOVERY_FAILED = 6
} test_state_t;
typedef enum
{
    ERR_NONE = 0,
    ERR_NACK = -1,
    ERR_BUS = -2,
    ERR_TIMEOUT = -3,
    ERR_BAD_ID = -4,
    ERR_NOT_READY = -5
} test_error_t;
/* Debugger-visible evidence */
volatile uint32_t test_state = TEST_NOT_STARTED;
volatile uint32_t baseline_ok = 0U;
volatile uint32_t fault_attempted = 0U;
volatile uint32_t fault_nack_observed = 0U;
volatile uint32_t recovery_attempted = 0U;
volatile uint32_t post_recovery_read_ok = 0U;
/* Chat 08: debugger-visible policy-to-hardware integration evidence. */
volatile uint32_t policy_variant = VAR_P4_INTEGRATED;
volatile uint32_t policy_event_admit_result = OUTCOME_NONE;
volatile uint32_t policy_fault_start_result = OUTCOME_NONE;
volatile uint32_t policy_decision_action = ACT_NONE;
volatile uint32_t policy_decision_reason = 0U;
volatile uint32_t policy_action_attempted = 0U;
volatile uint32_t hardware_action_result = ERR_NOT_READY;
volatile uint32_t policy_release_result = OUTCOME_NONE;
volatile uint32_t policy_runtime_bytes = 0U;
volatile uint32_t policy_runtime_trace_count = 0U;
volatile uint32_t policy_event_slot = INVALID_SLOT;
volatile uint32_t policy_event_generation = 0U;
static Runtime policy_runtime;
static EventRef policy_sensor_event;
volatile uint8_t sensor_address = 0U;
volatile uint8_t sensor_chip_id = 0U;
volatile uint8_t sensor_found = 0U;
volatile uint8_t post_recovery_chip_id = 0U;
volatile uint8_t nack_test_chip_id = 0U;
volatile int sensor_error = 0;
volatile int fault_result = 0;
volatile int recovery_error = 0;
volatile int baseline_result = 0;
volatile int post_recovery_result = 0;
/* Diagnostic state: phase 1=TXIS, 2=TC, 3=RXNE, 4=STOPF. */
volatile uint32_t diagnostic_phase = 0U;
volatile uint32_t diagnostic_isr = 0U;
static void print_test_report(const char *heading)
{
    printf("\r\n");
    printf("========================================\r\n");
    printf(" BME280 I2C RECOVERY TEST REPORT\r\n");
    printf("========================================\r\n");
    printf("Result                  : %s\r\n", heading);
    printf("test_state              = %lu\r\n", (unsigned long)test_state);
    printf("baseline_ok             = %lu\r\n", (unsigned long)baseline_ok);
    printf("baseline_result         = %d\r\n", baseline_result);
    printf("fault_attempted         = %lu\r\n", (unsigned long)fault_attempted);
    printf("fault_nack_observed     = %lu\r\n", (unsigned long)fault_nack_observed);
    printf("fault_result            = %d\r\n", fault_result);
    printf("recovery_attempted      = %lu\r\n", (unsigned long)recovery_attempted);
    printf("recovery_error          = %d\r\n", recovery_error);
    printf("post_recovery_read_ok   = %lu\r\n", (unsigned long)post_recovery_read_ok);
    printf("policy_variant          = %lu\r\n", (unsigned long)policy_variant);
    printf("policy_event_admit      = %lu\r\n", (unsigned long)policy_event_admit_result);
    printf("policy_fault_start      = %lu\r\n", (unsigned long)policy_fault_start_result);
    printf("policy_decision_action  = %lu\r\n", (unsigned long)policy_decision_action);
    printf("policy_decision_reason  = %lu\r\n", (unsigned long)policy_decision_reason);
    printf("hardware_action_result  = %lu\r\n", (unsigned long)hardware_action_result);
    printf("policy_release_result   = %lu\r\n", (unsigned long)policy_release_result);
    printf("policy_runtime_bytes    = %lu\r\n", (unsigned long)policy_runtime_bytes);
    printf("policy_runtime_trace    = %lu\r\n", (unsigned long)policy_runtime_trace_count);
    printf("post_recovery_chip_id   = 0x%02X\r\n", (unsigned int)post_recovery_chip_id);
    printf("post_recovery_result    = %d\r\n", post_recovery_result);
    printf("sensor_address          = 0x%02X\r\n", (unsigned int)sensor_address);
    printf("sensor_chip_id          = 0x%02X\r\n", (unsigned int)sensor_chip_id);
    printf("sensor_error            = %d\r\n", sensor_error);
    printf("diagnostic_phase        = %lu\r\n", (unsigned long)diagnostic_phase);
    printf("diagnostic_isr          = 0x%08lX\r\n", (unsigned long)diagnostic_isr);
    printf("========================================\r\n");
    printf("End of report\r\n\r\n");
    fflush(stdout);
}
static void i2c_clear_flags(void)
{
    I2C1->ICR = I2C_ICR_NACKCF
              | I2C_ICR_STOPCF
              | I2C_ICR_BERRCF
              | I2C_ICR_ARLOCF
              | I2C_ICR_OVRCF
              | I2C_ICR_TIMOUTCF;
}
static int i2c_wait(uint32_t wanted_flag)
{
    uint32_t remaining = I2C_TIMEOUT;
    while (remaining-- != 0U)
    {
        uint32_t status = I2C1->ISR;
        diagnostic_isr = status;
        if ((status & I2C_ISR_NACKF) != 0U)
        {
            I2C1->ICR = I2C_ICR_NACKCF;
            return ERR_NACK;
        }
        if ((status & (I2C_ISR_BERR
                     | I2C_ISR_ARLO
                     | I2C_ISR_OVR
                     | I2C_ISR_TIMEOUT)) != 0U)
        {
            I2C1->ICR = I2C_ICR_BERRCF
                      | I2C_ICR_ARLOCF
                      | I2C_ICR_OVRCF
                      | I2C_ICR_TIMOUTCF;
            return ERR_BUS;
        }
        if ((status & wanted_flag) != 0U)
        {
            return ERR_NONE;
        }
    }
    diagnostic_isr = I2C1->ISR;
    return ERR_TIMEOUT;
}
static int i2c_init(void)
{
    uint32_t remaining;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    (void)RCC->AHB2ENR;
    RCC->CR |= RCC_CR_HSION;
    remaining = I2C_TIMEOUT;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0U)
    {
        if (remaining-- == 0U)
        {
            return ERR_TIMEOUT;
        }
    }
    RCC->CCIPR &= ~RCC_CCIPR_I2C1SEL;
    RCC->CCIPR |= (2U << RCC_CCIPR_I2C1SEL_Pos);
    /* PB8/PB9: alternate function 4, open-drain. */
    GPIOB->MODER &= ~((3U << (8U * 2U)) | (3U << (9U * 2U)));
    GPIOB->MODER |=  ((2U << (8U * 2U)) | (2U << (9U * 2U)));
    GPIOB->OTYPER |= (1U << 8U) | (1U << 9U);
    GPIOB->OSPEEDR &= ~((3U << (8U * 2U)) | (3U << (9U * 2U)));
    GPIOB->OSPEEDR |=  ((3U << (8U * 2U)) | (3U << (9U * 2U)));
    /* External I2C pull-ups are expected; internal pulls are disabled. */
    GPIOB->PUPDR &= ~((3U << (8U * 2U)) | (3U << (9U * 2U)));
    GPIOB->AFR[1] &= ~((0xFU << 0U) | (0xFU << 4U));
    GPIOB->AFR[1] |=  ((4U << 0U) | (4U << 4U));
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    (void)RCC->APB1ENR1;
    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C1RST;
    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C1RST;
    I2C1->CR1 = 0U;
    I2C1->TIMINGR = I2C_TIMING_VALUE;
    i2c_clear_flags();
    I2C1->CR1 = I2C_CR1_PE;
    return ERR_NONE;
}
static int read_register(uint8_t address, uint8_t reg, uint8_t *value)
{
    int result;
    diagnostic_phase = 0U;
    if (value == 0)
    {
        return ERR_NOT_READY;
    }
    if ((I2C1->CR1 & I2C_CR1_PE) == 0U)
    {
        return ERR_NOT_READY;
    }
    i2c_clear_flags();
    /* Phase 1: send register address. */
    I2C1->CR2 = ((uint32_t)address << 1U)
              | (1U << I2C_CR2_NBYTES_Pos)
              | I2C_CR2_START;
    diagnostic_phase = 1U;
    result = i2c_wait(I2C_ISR_TXIS);
    if (result != ERR_NONE)
    {
        return result;
    }
    I2C1->TXDR = reg;
    diagnostic_phase = 2U;
    result = i2c_wait(I2C_ISR_TC);
    if (result != ERR_NONE)
    {
        return result;
    }
    /* Phase 2: repeated START, then read one byte with AUTOEND. */
    I2C1->CR2 = ((uint32_t)address << 1U)
              | I2C_CR2_RD_WRN
              | (1U << I2C_CR2_NBYTES_Pos)
              | I2C_CR2_START
              | I2C_CR2_AUTOEND;
    diagnostic_phase = 3U;
    result = i2c_wait(I2C_ISR_RXNE);
    if (result != ERR_NONE)
    {
        return result;
    }
    *value = (uint8_t)I2C1->RXDR;
    diagnostic_phase = 4U;
    result = i2c_wait(I2C_ISR_STOPF);
    if (result != ERR_NONE)
    {
        return result;
    }
    I2C1->ICR = I2C_ICR_STOPCF;
    diagnostic_phase = 0U;
    return ERR_NONE;
}
static int i2c_recover(void)
{
    /* Peripheral reset/reinitialization only; not a physical bus reset. */
    return i2c_init();
}
static int policy_prepare_sensor_event(void)
{
    EventSlot spec = {0};
    OutcomeCode result;
    runtime_init(&policy_runtime, VAR_P4_INTEGRATED);
    runtime_set_trace_metadata(&policy_runtime, 8001U, 1U, 1U);
    policy_runtime_bytes = (uint32_t)runtime_static_bytes();
    spec.type = EVT_PERIPHERAL_READ;
    spec.producer_id = 1U;
    spec.service_id = 1U;
    spec.consumer_id = 1U;
    spec.peripheral = PERIPH_I2C0;
    spec.criticality = NORMAL;
    spec.transaction_id = 1U;
    spec.dependency_count = 0U;
    spec.degradable = false;
    result = runtime_admit(&policy_runtime, &spec, &policy_sensor_event);
    policy_event_admit_result = (uint32_t)result;
    if (result != OUTCOME_SUCCESS) return ERR_NOT_READY;
    policy_event_slot = policy_sensor_event.slot_id;
    policy_event_generation = policy_sensor_event.generation;
    return ERR_NONE;
}
static int policy_start_nack_episode(void)
{
    OutcomeCode result = runtime_start_fault(
        &policy_runtime, FAULT_I2C_NACK, ASSOC_EXACT, policy_sensor_event,
        1U, NORMAL,
        false, /* Do not blindly retry the controlled NACK. */
        true,  /* The bounded I2C peripheral reinitialization is safe. */
        false  /* This chip-ID test has no degraded sensor mode. */
    );
    policy_fault_start_result = (uint32_t)result;
    return (result == OUTCOME_SUCCESS) ? ERR_NONE : ERR_NOT_READY;
}
int main(void)
{
    uint8_t id = 0U;
    int result;
    /*
     * Requires linker semihosting support (--specs=rdimon.specs)
     * and a debugger that handles semihosting calls.
     */
    initialise_monitor_handles();
    printf("\r\nStarting BME280 I2C recovery test...\r\n");
    fflush(stdout);
    test_state = TEST_NOT_STARTED;
    baseline_ok = 0U;
    fault_attempted = 0U;
    fault_nack_observed = 0U;
    recovery_attempted = 0U;
    post_recovery_read_ok = 0U;
    policy_variant = VAR_P4_INTEGRATED;
    policy_event_admit_result = OUTCOME_NONE;
    policy_fault_start_result = OUTCOME_NONE;
    policy_decision_action = ACT_NONE;
    policy_decision_reason = 0U;
    policy_action_attempted = 0U;
    hardware_action_result = ERR_NOT_READY;
    policy_release_result = OUTCOME_NONE;
    policy_runtime_trace_count = 0U;
    policy_event_slot = INVALID_SLOT;
    policy_event_generation = 0U;
    sensor_address = 0U;
    sensor_chip_id = 0U;
    sensor_found = 0U;
    post_recovery_chip_id = 0U;
    nack_test_chip_id = 0U;
    sensor_error = 0;
    fault_result = 0;
    recovery_error = 0;
    baseline_result = 0;
    post_recovery_result = 0;
    diagnostic_phase = 0U;
    diagnostic_isr = 0U;
    /* Phase 1: initialize and establish a valid baseline. */
    result = i2c_init();
    if (result == ERR_NONE)
    {
        result = read_register(BME280_ADDRESS, BME280_REG_ID, &id);
    }
    baseline_result = result;
    if ((result != ERR_NONE) || (id != BME280_EXPECTED_ID))
    {
        sensor_error = (result != ERR_NONE) ? result : ERR_BAD_ID;
        test_state = BASELINE_FAILED;
        print_test_report("BASELINE FAILED");
        while (1) { __NOP(); }
    }
    baseline_ok = 1U;
    sensor_address = BME280_ADDRESS;
    sensor_chip_id = id;
    sensor_found = 1U;
    sensor_error = ERR_NONE;
    test_state = BASELINE_PASSED;
    /* Admit the exact sensor-read event before applying the controlled fault. */
    result = policy_prepare_sensor_event();
    if (result != ERR_NONE) {
        test_state = NACK_NOT_CONFIRMED;
        sensor_error = result;
        print_test_report("POLICY EVENT ADMISSION FAILED");
        while (1) { __NOP(); }
    }
    /* Phase 2: controlled address-NACK attempt. */
    fault_attempted = 1U;
    id = 0U;
    fault_result = read_register(NACK_TEST_ADDRESS, BME280_REG_ID, &id);
    nack_test_chip_id = id;
    if (fault_result != ERR_NACK)
    {
        test_state = NACK_NOT_CONFIRMED;
        recovery_error = fault_result;
        print_test_report("NACK NOT CONFIRMED");
        while (1) { __NOP(); }
    }
    fault_nack_observed = 1U;
    test_state = NACK_CONFIRMED;
    /* Phase 3: P4 selects the recovery action; this adapter executes it on I2C1. */
    result = policy_start_nack_episode();
    if (result != ERR_NONE) {
        test_state = RECOVERY_FAILED;
        recovery_error = result;
        print_test_report("POLICY FAULT EPISODE FAILED");
        while (1) { __NOP(); }
    }
    {
        PolicyDecision decision = policy_decide(&policy_runtime, &policy_runtime.episode);
        policy_decision_action = (uint32_t)decision.action;
        policy_decision_reason = (uint32_t)decision.reason_code;
        policy_action_attempted = 1U;
        if (decision.action == ACT_REINIT_OR_RESET) {
            recovery_attempted = 1U;
            hardware_action_result = (uint32_t)i2c_recover();
        } else if (decision.action == ACT_RETRY) {
            /* The fresh sensor read below is the retry operation. */
            hardware_action_result = (uint32_t)ERR_NONE;
        } else {
            hardware_action_result = (uint32_t)ERR_NOT_READY;
            test_state = RECOVERY_FAILED;
            recovery_error = ERR_NOT_READY;
            print_test_report("POLICY SELECTED NON-EXECUTABLE ACTION");
            while (1) { __NOP(); }
        }
        recovery_error = (int32_t)hardware_action_result;
        if (recovery_error != ERR_NONE) {
            test_state = RECOVERY_FAILED;
            print_test_report("HARDWARE RECOVERY ACTION FAILED");
            while (1) { __NOP(); }
        }
        /* A fresh physical read gates release of the quarantined runtime event. */
        id = 0U;
        post_recovery_result = read_register(BME280_ADDRESS, BME280_REG_ID, &id);
        post_recovery_chip_id = id;
        if ((post_recovery_result == ERR_NONE) && (id == BME280_EXPECTED_ID)) {
            post_recovery_read_ok = 1U;
            policy_runtime.slots[policy_sensor_event.slot_id].verification_ok = true;
            policy_runtime.slots[policy_sensor_event.slot_id].shared_state_valid = true;
            policy_release_result = (uint32_t)runtime_verify_and_release(&policy_runtime, true);
            policy_runtime_trace_count = policy_runtime.trace_count;
            if (policy_release_result == OUTCOME_SUCCESS) {
                test_state = RECOVERY_PASSED;
                print_test_report("P4 POLICY-DRIVEN HARDWARE RECOVERY PASSED");
            } else {
                test_state = RECOVERY_FAILED;
                recovery_error = ERR_NOT_READY;
                print_test_report("SENSOR READ PASSED BUT RUNTIME RELEASE FAILED");
            }
        } else {
            post_recovery_read_ok = 0U;
            policy_runtime.slots[policy_sensor_event.slot_id].verification_ok = false;
            policy_runtime.slots[policy_sensor_event.slot_id].shared_state_valid = false;
            policy_release_result = (uint32_t)OUTCOME_FAILURE;
            recovery_error = (post_recovery_result != ERR_NONE) ? post_recovery_result : ERR_BAD_ID;
            test_state = RECOVERY_FAILED;
            policy_runtime_trace_count = policy_runtime.trace_count;
            print_test_report("POST-RECOVERY SENSOR VERIFICATION FAILED");
        }
    }
    while (1) { __NOP(); }
}