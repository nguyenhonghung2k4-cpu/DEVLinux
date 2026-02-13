#include "spws_controller.h"
#include "../config.h"
#include "../hal_sensors/hal_sensors.h"
#include "../hal_actuators/hal_actuators.h"
#include "../hal_buttons/hal_buttons.h"
#include <stdio.h>

static SystemSettings_t settings;
static SystemState_t state;
static SensorData_t sensorData;

void SPWS_Init(void) {
  
    settings.minMoistureThreshold = 30.0f;     
    settings.maxMoistureThreshold = 80.0f;    
    settings.maxWateringDuration_s = 5;        
    
    settings.manualWateringDuration_s = 5;     
    
    settings.sensorReadInterval_s = 1;         

 
    state.currentMode = MODE_AUTO;
    state.pumpState = PUMP_OFF;
    state.ledState = LED_NORMAL;
    state.wateringTimeCounter = 0;
    state.sensorCheckCounter = 0;

    HAL_TurnPumpOff();
    HAL_SetLed(LED_NORMAL);
    printf("--- SYSTEM INITIALIZED (Auto Random Mode) ---\n");
}

static void RunAutoLogic(void) {
  
    if (state.sensorCheckCounter >= settings.sensorReadInterval_s) {
        sensorData.soilMoisturePercent = HAL_ReadSoilMoisture();
        sensorData.airTemperatureCelsius = HAL_ReadTemperature();
        state.sensorCheckCounter = 0;

        printf("[SENSOR-AUTO] Random Soil: %.1f%% | Temp: %.1f C\n", 
               sensorData.soilMoisturePercent, sensorData.airTemperatureCelsius);

        if (state.pumpState == PUMP_OFF) {
          
            if (sensorData.soilMoisturePercent < settings.minMoistureThreshold) {
                printf("[LOGIC] Moisture LOW -> Pump ON (Auto)\n");
                HAL_TurnPumpOn();
                state.pumpState = PUMP_ON;
                state.ledState = LED_WATERING;
                state.wateringTimeCounter = 0;
            }
        } else {
          
            if (sensorData.soilMoisturePercent > settings.maxMoistureThreshold) {
                printf("[LOGIC] Moisture HIGH -> Pump OFF\n");
                HAL_TurnPumpOff();
                state.pumpState = PUMP_OFF;
                state.ledState = LED_NORMAL;
            }
        }
    }

   
    if (state.pumpState == PUMP_ON) {
        state.wateringTimeCounter++;
        if (state.wateringTimeCounter > settings.maxWateringDuration_s) {
            printf("[LOGIC] Auto Timeout (Safe Stop) -> Pump OFF\n");
            HAL_TurnPumpOff();
            state.pumpState = PUMP_OFF;
            state.ledState = LED_NORMAL;
        }
    }
}

static void RunManualLogic(void) {
   
    if (HAL_IsButton2Pressed()) {
        if (state.pumpState == PUMP_OFF) {
            printf("[INPUT] Button 2 -> Pump ON (Manual 5s)\n");
            HAL_TurnPumpOn();
            state.pumpState = PUMP_ON;
            state.ledState = LED_WATERING;
            state.wateringTimeCounter = 0;
        }
    }

    if (state.pumpState == PUMP_ON) {
        state.wateringTimeCounter++;
        printf("[MANUAL] Watering... %d/%d seconds\n", 
               state.wateringTimeCounter, settings.manualWateringDuration_s);
        
       
        if (state.wateringTimeCounter >= settings.manualWateringDuration_s) {
            printf("[LOGIC] Manual Timer Done (5s) -> Pump OFF\n");
            HAL_TurnPumpOff();
            state.pumpState = PUMP_OFF;
            state.ledState = LED_NORMAL;
        }
    }
}

void SPWS_OneSecondTick(void) {
    state.sensorCheckCounter++;

    if (HAL_IsButton1Pressed()) {
      
        if (state.currentMode == MODE_AUTO) {
            state.currentMode = MODE_MANUAL;
            printf("[INPUT] Button 1 -> Switched to MANUAL MODE\n");
            if (state.pumpState == PUMP_ON) {
                HAL_TurnPumpOff(); 
                state.pumpState = PUMP_OFF;
                state.ledState = LED_NORMAL;
            }
        } else {
            state.currentMode = MODE_AUTO;
            printf("[INPUT] Button 1 -> Switched to AUTO MODE\n");
        }
    }

    if (state.currentMode == MODE_AUTO) {
        RunAutoLogic();
    } else {
        RunManualLogic();
    }
    HAL_SetLed(state.ledState);
}