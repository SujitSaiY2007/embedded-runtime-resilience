#include "err_runtime.h"

/*
 * Embedded Runtime Resilience
 * Controlled GPIO recovery experiment.
 *
 * Target: STM32L476RG on NUCLEO-L476RG
 * Peripheral ID 1U: onboard LD2 green LED on PA5.
 *
 * This is a limited hardware-specific experiment,
 * not the complete research recovery policy.
 */

#define ERR_MAX_RECOVERY_ATTEMPTS  3U
#define ERR_LD2_PERIPHERAL_ID      1U

#define RCC_AHB2ENR_ADDRESS        0x4002104CUL
#define GPIOA_MODER_ADDRESS        0x48000000UL
#define GPIOA_ODR_ADDRESS          0x48000014UL
#define GPIOA_BSRR_ADDRESS         0x48000018UL

#define LD2_PIN                    5U
#define LD2_BIT                    (1UL << LD2_PIN)
#define LD2_MODE_MASK              (3UL << (LD2_PIN * 2U))
#define LD2_OUTPUT_MODE            (1UL << (LD2_PIN * 2U))

#define REG32(address) \
    (*(volatile uint32_t *)(address))

static err_runtime_status_t runtime_status;

void err_runtime_init(void)
{
    runtime_status.event_count = 0U;
    runtime_status.fault_count = 0U;
    runtime_status.recovery_count = 0U;
    runtime_status.state = ERR_STATE_NORMAL;
}

void err_runtime_report_fault(uint32_t peripheral_id)
{
    (void)peripheral_id;

    runtime_status.event_count++;
    runtime_status.fault_count++;
    runtime_status.state = ERR_STATE_FAULT_DETECTED;
}

bool err_runtime_recover(uint32_t peripheral_id)
{
    uint32_t attempt;
    uint32_t moder;

    if ((runtime_status.state != ERR_STATE_FAULT_DETECTED) &&
        (runtime_status.state != ERR_STATE_QUARANTINED))
    {
        return false;
    }

    runtime_status.state = ERR_STATE_RECOVERING;

    /* Reject peripheral IDs unsupported by this experiment. */
    if (peripheral_id != ERR_LD2_PERIPHERAL_ID)
    {
        runtime_status.state = ERR_STATE_FAILED;
        return false;
    }

    for (attempt = 0U;
         attempt < ERR_MAX_RECOVERY_ATTEMPTS;
         attempt++)
    {
        /* Enable the GPIOA peripheral clock. */
        REG32(RCC_AHB2ENR_ADDRESS) |= (1UL << 0U);
        (void)REG32(RCC_AHB2ENR_ADDRESS);

        /* Restore PA5 to general-purpose output mode. */
        moder = REG32(GPIOA_MODER_ADDRESS);
        moder &= ~LD2_MODE_MASK;
        moder |= LD2_OUTPUT_MODE;
        REG32(GPIOA_MODER_ADDRESS) = moder;

        /* Drive LD2 high. */
        REG32(GPIOA_BSRR_ADDRESS) = LD2_BIT;

        /* Verify the configuration and output data latch. */
        moder = REG32(GPIOA_MODER_ADDRESS);

        if (((moder & LD2_MODE_MASK) == LD2_OUTPUT_MODE) &&
            ((REG32(GPIOA_ODR_ADDRESS) & LD2_BIT) != 0U))
        {
            runtime_status.recovery_count++;
            runtime_status.state = ERR_STATE_RECOVERED;
            return true;
        }
    }

    runtime_status.state = ERR_STATE_FAILED;
    return false;
}

err_runtime_status_t err_runtime_get_status(void)
{
    return runtime_status;
}
