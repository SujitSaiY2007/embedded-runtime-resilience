#ifndef VIRTUAL_SCENARIOS_H
#define VIRTUAL_SCENARIOS_H

#include "virtual_system.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const VirtualScenario scenario_S01;
extern const VirtualScenario scenario_S02;
extern const VirtualScenario scenario_S05;
extern const VirtualScenario scenario_S06;
extern const VirtualScenario scenario_S08;
extern const VirtualScenario scenario_S14;

typedef struct {
    const char *id;
    const char *name;
    const char *description;
    const VirtualScenario *scenario;
} ScenarioRegistryEntry;

const ScenarioRegistryEntry *virtual_scenario_get(size_t index);
size_t virtual_scenario_count(void);
const ScenarioRegistryEntry *virtual_scenario_find(const char *id);

#ifdef __cplusplus
}
#endif

#endif /* VIRTUAL_SCENARIOS_H */
