// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void set_underglow(void)
{
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW)
        {
            // Set underglow to dark blue (R=0, G=0, B=50)
            rgb_matrix_set_color(i, 0, 0, 50);
        }
    }
}

bool TYPER(effect_params_t* params)
{
    // Run the default TYPING_HEATMAP effect
    bool result = TYPING_HEATMAP (params);

    // Add custom underglow logic
    set_underglow();

    return result;
}

#endif
