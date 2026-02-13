#ifndef HAL_SENSORS_H
#define HAL_SENSORS_H

/**
 * @brief Reads the current soil moisture level from the sensor.
 * @return Float value representing moisture percentage (0.0 to 100.0).
 */
float HAL_ReadSoilMoisture(void);

/**
 * @brief Reads the current ambient temperature.
 * @return Float value in degrees Celsius.
 */
float HAL_ReadTemperature(void);

/* --- Simulation Helpers --- */

/**
 * @brief Sets the simulated soil moisture value.
 * @param moisture The target moisture percentage.
 */
void SIM_SetSoilMoisture(float moisture);

/**
 * @brief Sets the simulated temperature value.
 * @param temp The target temperature in Celsius.
 */
void SIM_SetTemperature(float temp);

#endif // HAL_SENSORS_H