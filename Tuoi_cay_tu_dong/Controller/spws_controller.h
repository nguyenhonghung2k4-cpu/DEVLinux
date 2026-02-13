#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H

/**
 * @brief Initializes the SPWS controller.
 * Sets default settings, resets system state, and initializes hardware actuators.
 */
void SPWS_Init(void);

/**
 * @brief Executes one tick of the system logic (assumed to be 1 second).
 * Handles sensor polling, state transitions, timeout checks, and actuator updates.
 */
void SPWS_OneSecondTick(void);

#endif // SPWS_CONTROLLER_H