#ifndef ERR_RUNTIME_H
#define ERR_RUNTIME_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Embedded Runtime Resilience
 * Hardware integration interface
 */

typedef enum
{
    ERR_STATE_NORMAL = 0,
    ERR_STATE_FAULT_DETECTED,
    ERR_STATE_QUARANTINED,
    ERR_STATE_RECOVERING,
    ERR_STATE_RECOVERED,
    ERR_STATE_FAILED
} err_state_t;

typedef struct
{
    uint32_t event_count;
    uint32_t fault_count;
    uint32_t recovery_count;
    err_state_t state;
} err_runtime_status_t;

/* Initialize runtime state. */
void err_runtime_init(void);

/* Report a simulated peripheral fault. */
void err_runtime_report_fault(uint32_t peripheral_id);

/* Attempt bounded recovery. */
bool err_runtime_recover(uint32_t peripheral_id);

/* Read the current runtime status. */
err_runtime_status_t err_runtime_get_status(void);

#endif /* ERR_RUNTIME_H */
