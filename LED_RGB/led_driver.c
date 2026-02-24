#include "led_driver.h"
#include <stdlib.h>

static uint32_t *led_buffer = NULL;
static size_t pixel_count = 0;

int led_init(size_t num_pixels) {
    if (num_pixels == 0) {
        return -1;
    }
    
    if (led_buffer != NULL) {
        led_shutdown();
    }

    led_buffer = (uint32_t*)calloc(num_pixels, sizeof(uint32_t));
    if (led_buffer == NULL) {
        return -1;
    }

    pixel_count = num_pixels;
    return 0;
}

void led_shutdown(void) {
    if (led_buffer != NULL) {
        free(led_buffer);
        led_buffer = NULL;
    }
    pixel_count = 0;
}

void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b) {
    if (led_buffer == NULL || index >= pixel_count) {
        return;
    }

    uint32_t color = ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
    led_buffer[index] = color;
}

void led_fill(uint8_t r, uint8_t g, uint8_t b) {
    if (led_buffer == NULL) {
        return;
    }
    
    uint32_t color = ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
    for (size_t i = 0; i < pixel_count; i++) {
        led_buffer[i] = color;
    }
}

void led_clear(void) {
    led_fill(0, 0, 0);
}

const uint32_t* led_get_buffer(void) {
    return led_buffer;
}

size_t led_get_pixel_count(void) {
    return pixel_count;
}