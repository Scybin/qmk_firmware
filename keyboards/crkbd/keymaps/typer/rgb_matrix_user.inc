// Declare the custom effect
RGB_MATRIX_EFFECT(BLUE_HEATMAP)

// Define the effect implementation
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t heatmap_values[DRIVER_LED_TOTAL] = { 54 }; // Array to store heatmap values for each LED

static bool BLUE_HEATMAP(effect_params_t*params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Decrease heatmap values over time
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        if (heatmap_values[i] > 0)
        {
            heatmap_values[i]--;
        }
    }

    // Handle keypress events
    for (uint8_t i = led_min; i < led_max; i++)
    {
        if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT))
        {
            if (g_rgb_frame_buffer[i])
            {
                heatmap_values[i] = 255; // Max heat for pressed keys
            }
        }
    }

    // Set LED colors based on heatmap values
    for (uint8_t i = led_min; i < led_max; i++)
    {
        uint8_t heat = heatmap_values[i];
        uint8_t blue = 255 - heat; // Blue decreases as heat increases
        uint8_t red = heat;        // Red increases as heat increases
        rgb_matrix_set_color(i, red, 0, blue);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif
