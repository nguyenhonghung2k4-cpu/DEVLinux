#include "hal_buttons.h"

static bool s_btn1_pressed = false;
static bool s_btn2_pressed = false;

bool HAL_IsButton1Pressed(void) {
    if (s_btn1_pressed) {
        s_btn1_pressed = false; 
        return true;
    }
    return false;
}

bool HAL_IsButton2Pressed(void) {
    if (s_btn2_pressed) {
        s_btn2_pressed = false; 
        return true;
    }
    return false;
}

void SIM_PressButton1(void) {
    s_btn1_pressed = true;
}

void SIM_PressButton2(void) {
    s_btn2_pressed = true;
}