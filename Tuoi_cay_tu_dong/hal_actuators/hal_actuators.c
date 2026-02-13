#include "hal_actuators.h"
#include <stdio.h>

void HAL_TurnPumpOn(void) {
    printf("[HARDWARE] >>> PUMP ACTIVATED <<<\n");
}

void HAL_TurnPumpOff(void) {
    printf("[HARDWARE] PUMP STOPPED\n");
}

void HAL_SetLed(LedState_t state) {
    switch(state) {
        case LED_NORMAL: printf("[HARDWARE] LED: GREEN\n"); break;
        case LED_WATERING: printf("[HARDWARE] LED: YELLOW\n"); break;
        case LED_LOW_MOISTURE_ALERT: printf("[HARDWARE] LED: RED BLINK\n"); break;
        case LED_ERROR: printf("[HARDWARE] LED: RED SOLID\n"); break;
    }
}