#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdbool.h>

/**
 * @brief Checks if Button 1 (Mode Toggle) was pressed.
 * @return true if pressed, false otherwise.
 */
bool HAL_IsButton1Pressed(void);

/**
 * @brief Checks if Button 2 (Manual Watering) was pressed.
 * @return true if pressed, false otherwise.
 */
bool HAL_IsButton2Pressed(void);

/* --- Simulation Helpers --- */

/**
 * @brief Simulates a physical press on Button 1.
 * Used for testing purposes via console input.
 */
void SIM_PressButton1(void);

/**
 * @brief Simulates a physical press on Button 2.
 * Used for testing purposes via console input.
 */
void SIM_PressButton2(void);

#endif // HAL_BUTTONS_H