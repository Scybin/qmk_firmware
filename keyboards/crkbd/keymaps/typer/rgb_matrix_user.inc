// Declare the custom effect
RGB_MATRIX_EFFECT(BLUE_HEATMAP)

// Define the effect implementation
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "timer.h"

static uint8_t heatmap_values[DRIVER_LED_TOTAL] = { 0 }; // Array to store heatmap values for each LED
static uint16_t last_typing_time = 0;                 // Timestamp of the last keypress
static uint8_t typing_speed = 0;                      // Typing speed (keypresses per second)

static bool BLUE_HEATMAP(effect_params_t*params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Decrease heatmap values over time (cooling effect)
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        if (heatmap_values[i] > 0)
        {
            heatmap_values[i]--; // Gradually decrease heat
        }
    }

    // Update heatmap values for active LEDs
    for (uint8_t i = led_min; i < led_max; i++)
    {
        if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT))
        {
            heatmap_values[i] = 255; // Max heat for active LEDs
        }
    }

    // Calculate typing speed based on time since the last keypress
    uint16_t current_time = timer_read();
    uint16_t time_diff = current_time - last_typing_time;

    if (time_diff > 0 && time_diff < 1000)
    { // Ignore long idle times
        typing_speed = 1000 / time_diff; // Convert milliseconds to keypresses per second
    }
    last_typing_time = current_time;

    // Set LED colors based on heatmap values and typing speed
    for (uint8_t i = led_min; i < led_max; i++)
    {
        uint8_t heat = heatmap_values[i];

        // Adjust color gradient based on typing speed
        uint8_t blue = (typing_speed < 5) ? 255 - heat : 0; // Blue for slow typing
        uint8_t green = (typing_speed >= 5 && typing_speed < 10) ? 255 - heat : 0; // Green for moderate typing
        uint8_t red = (typing_speed >= 10) ? heat : 0; // Red for fast typing

        rgb_matrix_set_color(i, red, green, blue);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif
