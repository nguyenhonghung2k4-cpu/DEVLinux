#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "../config.h"

/**
 * @brief Activates the water pump hardware.
 */
void HAL_TurnPumpOn(void);

/**
 * @brief Deactivates the water pump hardware.
 */
void HAL_TurnPumpOff(void);

/**
 * @brief Sets the system LED to a specific color/state.
 * @param state The target LED state defined in LedState_t.
 */
void HAL_SetLed(LedState_t state);

#endif // HAL_ACTUATORS_H