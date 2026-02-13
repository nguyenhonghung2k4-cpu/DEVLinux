#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Để khởi tạo seed cho random
#include "config.h"
#include "Controller/spws_controller.h"
#include "hal_buttons/hal_buttons.h"
#include "hal_sensors/hal_sensors.h"

void PrintMenu() {
    printf("\n================ CONTROL PANEL ================\n");
    printf("[1] Toggle Mode (Auto <-> Manual)\n");
    printf("[2] Trigger Manual Watering (5 seconds)\n");
    printf("[Enter] Tick (Advance 1 second)\n");
    printf("[q] Quit\n");
    printf("Command: ");
}

int main() {
    char cmd;
    
    // Khởi tạo bộ sinh số ngẫu nhiên theo thời gian thực
    srand(time(NULL));

    printf("=== SMART PLANT WATERING SYSTEM ===\n");
    SPWS_Init();

    while (1) {
        PrintMenu();
        
        cmd = getchar(); 
        if (cmd != '\n') {
            while (getchar() != '\n'); // Xóa buffer
        }

        switch (cmd) {
            case '1':
                SIM_PressButton1();
                // Không in thêm gì ở đây vì trong Controller đã in log rồi
                break;
            case '2':
                SIM_PressButton2();
                break;
            case 'q':
            case 'Q':
                return 0;
            case '\n':
                break; // Chỉ cần tick
            default:
                printf("Invalid command.\n");
        }

        printf("\n--- TIME TICK ---\n");
        SPWS_OneSecondTick();
        printf("-----------------\n");
    }

    return 0;
}