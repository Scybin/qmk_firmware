// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void process_rgb_matrix_typer(uint8_t row, uint8_t col)
{
    if (g_led_config.matrix_co[row][col] == NO_LED)
    {
        return; // Skip if the pressed key doesn't have an LED
    }

    // Set the pressed key to purple (hue 200)
    hsv_t hsv = { 200, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
    rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(g_led_config.matrix_co[row][col], rgb.r, rgb.g, rgb.b);
}

bool TYPER(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        // Set all LEDs to dark blue (hue 170)
        hsv_t hsv = { 170, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }

    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS && count < RGB_MATRIX_LED_PROCESS_LIMIT; col++)
        {
            if (g_led_config.matrix_co[row][col] >= led_min && g_led_config.matrix_co[row][col] < led_max)
            {
                count++;

                // Debugging: Check if the key is pressed
                if (HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[row][col]], params->flags))
                {
                    process_rgb_matrix_typer(row, col);
                }
                else
                {
                    // Debugging: Reset the key to dark blue
                    hsv_t default_hsv = { 170, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
                    rgb_t default_rgb = rgb_matrix_hsv_to_rgb(default_hsv);
                    rgb_matrix_set_color(g_led_config.matrix_co[row][col], default_rgb.r, default_rgb.g, default_rgb.b);
                }
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
