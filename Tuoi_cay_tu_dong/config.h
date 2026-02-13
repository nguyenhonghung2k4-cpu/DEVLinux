#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Defines the operating modes of the system.
 */
typedef enum {
    MODE_AUTO,      /**< System operates automatically based on sensor data. */
    MODE_MANUAL     /**< System operates based on user manual input. */
} SystemMode_t;

/**
 * @brief Represents the state of the water pump.
 */
typedef enum {
    PUMP_OFF,       /**< Pump is currently inactive. */
    PUMP_ON         /**< Pump is currently active. */
} PumpState_t;

/**
 * @brief Represents the various states of the LED indicator.
 */
typedef enum {
    LED_NORMAL,             /**< Green: System is idle and parameters are normal. */
    LED_WATERING,           /**< Yellow: Pump is currently running. */
    LED_LOW_MOISTURE_ALERT, /**< Red Blinking: Soil moisture is critically low. */
    LED_ERROR               /**< Red Solid: System encountered an error. */
} LedState_t;

/**
 * @brief Structure to hold the latest sensor readings.
 */
typedef struct {
    float soilMoisturePercent;      /**< Soil moisture level (0.0 - 100.0). */
    float airTemperatureCelsius;    /**< Ambient temperature in degrees Celsius. */
} SensorData_t;

/**
 * @brief Structure to hold configurable system thresholds and timings.
 */
typedef struct {
    float minMoistureThreshold;           /**< Moisture level below which watering starts (Auto mode). */
    float maxMoistureThreshold;           /**< Moisture level above which watering stops (Auto mode). */
    unsigned int maxWateringDuration_s;   /**< Safety timeout for watering in Auto mode (seconds). */
    unsigned int sensorReadInterval_s;    /**< Time interval between sensor polls (seconds). */
    unsigned int manualWateringDuration_s;/**< Duration for manual watering cycle (seconds). */
} SystemSettings_t;

/**
 * @brief Structure to manage the runtime state of the system.
 */
typedef struct {
    SystemMode_t currentMode;         /**< Current operating mode (Auto/Manual). */
    PumpState_t pumpState;            /**< Current state of the pump. */
    LedState_t ledState;              /**< Current state of the LED. */
    unsigned int wateringTimeCounter; /**< Counter tracking how long the pump has been running. */
    unsigned int sensorCheckCounter;  /**< Counter tracking time since last sensor read. */
} SystemState_t;

#endif // CONFIG_H