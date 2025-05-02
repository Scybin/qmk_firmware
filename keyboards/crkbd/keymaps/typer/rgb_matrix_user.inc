// !!! DO NOT ADD #pragma once !!! //

// Include necessary headers
#include "rgb_matrix.h" // Ensures effect_params_t and related macros are defined

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(TYPING_HEATMAP_WITH_UNDERGLOW)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// A timer to track the last time we decremented all heatmap values.
static uint16_t heatmap_decrease_timer = 0; // Initialize to 0 to avoid undefined behavior
// Whether we should decrement the heatmap values during the next update.
static bool decrease_heatmap_values = false; // Initialize to false

// Define the TYPING_HEATMAP_WITH_UNDERGLOW effect
static bool TYPING_HEATMAP_WITH_UNDERGLOW(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);

        // Initialize underglow LEDs
        for (uint8_t i = led_max; i < DRIVER_LED_TOTAL; i++)
        {
            rgb_matrix_set_color(i, 0, 0, 255); // Set underglow to blue as an example
        }
    }

    // The heatmap animation might run in several iterations depending on
    // `RGB_MATRIX_LED_PROCESS_LIMIT`, therefore we only want to update the
    // timer when the animation starts.
    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS;

        // Restart the timer if we are going to decrease the heatmap this frame.
        if (decrease_heatmap_values)
        {
            heatmap_decrease_timer = timer_read();
        }
    }

    // Render heatmap & decrease
    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS && count < RGB_MATRIX_LED_PROCESS_LIMIT; col++)
        {
            if (g_led_config.matrix_co[row][col] >= led_min && g_led_config.matrix_co[row][col] < led_max)
            {
                count++;
                uint8_t val = g_rgb_frame_buffer[row][col];
                if (!HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[row][col]], params->flags)) continue;

                hsv_t hsv = { 170 - qsub8(val, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v) };
                rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(g_led_config.matrix_co[row][col], rgb.r, rgb.g, rgb.b);

                if (decrease_heatmap_values)
                {
                    g_rgb_frame_buffer[row][col] = qsub8(val, 1);
                }
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
