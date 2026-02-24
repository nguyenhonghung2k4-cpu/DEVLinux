#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Initializes a buffer for the LED strip with the given number of pixels.
 * * @param num_pixels The total number of pixels on the LED strip.
 * @return int 0 on success, -1 on failure (e.g., memory allocation failed).
 */
int led_init(size_t num_pixels);

/**
 * @brief Frees the memory allocated for the LED strip buffer.
 */
void led_shutdown(void);

/**
 * @brief Sets the color of a specific pixel at the given 'index'.
 * Uses 3 separate 8-bit values for Red, Green, and Blue.
 * Format is packed into a 32-bit integer: 0x00GGRRBB.
 * * @param index The index of the pixel (0 to num_pixels - 1).
 * @param r Red intensity (0-255).
 * @param g Green intensity (0-255).
 * @param b Blue intensity (0-255).
 */
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Fills the entire strip with a single color.
 * * @param r Red intensity (0-255).
 * @param g Green intensity (0-255).
 * @param b Blue intensity (0-255).
 */
void led_fill(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Turns off all pixels by setting their color to black (0, 0, 0).
 */
void led_clear(void);

/**
 * @brief Gets a constant (read-only) pointer to the data buffer.
 * This is primarily used for testing or transmitting the final buffer data.
 * * @return const uint32_t* Pointer to the LED data buffer.
 */
const uint32_t* led_get_buffer(void);

/**
 * @brief Gets the total number of pixels on the LED strip.
 * * @return size_t Number of initialized pixels.
 */
size_t led_get_pixel_count(void);

#endif /* LED_DRIVER_H */