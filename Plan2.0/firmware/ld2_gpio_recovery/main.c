#include "err_runtime.h"
#include <stdint.h>

/*
 * Controlled LD2 GPIO fault-injection experiment.
 * Target: NUCLEO-L476RG, onboard green LED LD2 on PA5.
 */

#define RCC_AHB2ENR_ADDRESS  0x4002104CUL
#define GPIOA_MODER_ADDRESS  0x48000000UL
#define GPIOA_ODR_ADDRESS    0x48000014UL

#define LD2_PIN              5U
#define LD2_BIT              (1UL << LD2_PIN)
#define LD2_MODE_MASK        (3UL << (LD2_PIN * 2U))
#define LD2_OUTPUT_MODE      (1UL << (LD2_PIN * 2U))

#define REG32(address) \
    (*(volatile uint32_t *)(address))

/* Global volatile variables for debugger inspection. */
volatile uint32_t test_event_count = 0U;
volatile uint32_t test_fault_count = 0U;
volatile uint32_t test_recovery_count = 0U;
volatile uint32_t test_state = 0U;
volatile uint32_t test_recovered = 0U;
volatile uint32_t test_fault_injected = 0U;
volatile uint32_t test_gpio_mode = 0U;
volatile uint32_t test_gpio_output = 0U;

int main(void)
{
    bool recovered;
    uint32_t moder;
    err_runtime_status_t status;

    err_runtime_init();

    /* Enable GPIOA clock. */
    REG32(RCC_AHB2ENR_ADDRESS) |= (1UL << 0U);
    (void)REG32(RCC_AHB2ENR_ADDRESS);

    /* Configure PA5 as output and initially turn LD2 off. */
    moder = REG32(GPIOA_MODER_ADDRESS);
    moder &= ~LD2_MODE_MASK;
    moder |= LD2_OUTPUT_MODE;
    REG32(GPIOA_MODER_ADDRESS) = moder;

    REG32(GPIOA_ODR_ADDRESS) &= ~LD2_BIT;

    /*
     * Inject a software-controlled configuration fault:
     * change PA5 from output mode to input mode.
     */
    moder = REG32(GPIOA_MODER_ADDRESS);
    moder &= ~LD2_MODE_MASK;
    REG32(GPIOA_MODER_ADDRESS) = moder;

    test_fault_injected = 1U;

    /* Report the injected fault and attempt recovery. */
    err_runtime_report_fault(1U);
    recovered = err_runtime_recover(1U);

    /* Capture final runtime status. */
    status = err_runtime_get_status();

    test_event_count = status.event_count;
    test_fault_count = status.fault_count;
    test_recovery_count = status.recovery_count;
    test_state = (uint32_t)status.state;
    test_recovered = recovered ? 1U : 0U;

    /* Capture final GPIO configuration and output latch. */
    test_gpio_mode =
        (REG32(GPIOA_MODER_ADDRESS) & LD2_MODE_MASK)
        >> (LD2_PIN * 2U);

    test_gpio_output =
        ((REG32(GPIOA_ODR_ADDRESS) & LD2_BIT) != 0U)
        ? 1U : 0U;

    /* Hold results for debugger inspection. */
    while (1)
    {
        /* Inspect the global test_* variables in the debugger. */
    }
}
