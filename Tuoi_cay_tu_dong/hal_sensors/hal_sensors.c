#include "hal_sensors.h"
#include <stdlib.h> 
float HAL_ReadSoilMoisture(void) {

    return (float)(rand() % 101);
}

float HAL_ReadTemperature(void) {
   
    return 20.0f + (rand() % 21);
}


void SIM_SetSoilMoisture(float moisture) { }
void SIM_SetTemperature(float temp) { }