// Declare the custom effect
RGB_MATRIX_EFFECT(BLUE_HEATMAP)

// Define the effect implementation
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool BLUE_HEATMAP(effect_params_t*params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++)
    {
        // Set all LEDs to blue (R=0, G=0, B=255)
        rgb_matrix_set_color(i, 0, 0, 255);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif
