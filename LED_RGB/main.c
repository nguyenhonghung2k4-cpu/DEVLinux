#include <stdio.h>
#include <stdbool.h>
#include "led_driver.h"

int main() {
    if (led_init(10) != 0) {
        printf("Failed to initialize LED strip.\n");
        return -1;
    }
    printf("1. Initialized LED strip with 10 pixels.\n");

    const uint32_t* buffer = led_get_buffer();
    size_t count = led_get_pixel_count();
    bool is_cleared = true;
    for (size_t i = 0; i < count; i++) {
        if (buffer[i] != 0) {
            is_cleared = false;
            break;
        }
    }
    
    if (is_cleared) {
        printf("2. Check passed: Buffer initialized to 0.\n");
    } else {
        printf("2. Check failed: Buffer not 0.\n");
    }

    led_set_pixel_color(0, 255, 0, 0);
    printf("3. Set pixel 0 to Red.\n");

    led_set_pixel_color(9, 0, 0, 255);
    printf("4. Set pixel 9 to Blue.\n");

    led_set_pixel_color(4, 255, 255, 255);
    printf("5. Set pixel 4 to White.\n");

    buffer = led_get_buffer();
    printf("6. Retrieved pointer to data buffer.\n");

    printf("7. Hex values verification:\n");
    printf("   - Index 0: 0x%08X (Expected: 0x0000FF00)\n", buffer[0]);
    printf("   - Index 4: 0x%08X (Expected: 0x00FFFFFF)\n", buffer[4]);
    printf("   - Index 9: 0x%08X (Expected: 0x000000FF)\n", buffer[9]);

    led_fill(0, 255, 0);
    printf("8. Called led_fill(0, 255, 0) to set all to Green.\n");

    bool all_green = true;
    for (size_t i = 0; i < count; i++) {
        if (buffer[i] != 0x00FF0000) {
            all_green = false;
            break;
        }
    }
    
    if (all_green) {
        printf("9. Check passed: All 10 pixels are 0x00FF0000.\n");
    } else {
        printf("9. Check failed: Not all pixels are green.\n");
    }

    led_shutdown();
    printf("10. Called led_shutdown() to free memory.\n");

    return 0;
}