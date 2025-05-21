// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void set_default_color(void)
{
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        // Set all LEDs to default color (e.g., white: R=50, G=50, B=50)
        rgb_matrix_set_color(i, 50, 50, 50);
    }
}

static void set_key_to_purple(uint8_t key)
{
    // Set the specific key's LED to purple (R=50, G=0, B=50)
    rgb_matrix_set_color(key, 50, 0, 50);
}

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
    // Set all LEDs to the default color
    set_default_color();

    // Add custom underglow logic
    set_underglow();

    // Check if any key is pressed
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
    {
        for (uint8_t j = 0; j < MATRIX_COLS; j++)
        {
            if (matrix_is_on(i, j))
            {
                // Get the LED index for the pressed key
                uint8_t led_index = g_led_config.matrix_co[i][j];
                if (led_index != NO_LED)
                {
                    set_key_to_purple(led_index);
                }
            }
        }
    }

    return true; // Indicate that the effect was applied
}

#endif
