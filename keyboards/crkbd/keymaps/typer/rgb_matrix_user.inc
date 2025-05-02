RGB_MATRIX_EFFECT(BLUE_HEATMAP)

// Define the effect implementation
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "timer.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

#ifndef RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP
#    define RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP 32
#endif

#ifndef RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS
#    define RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS 25
#endif

static uint16_t heatmap_decrease_timer; // Timer to track heatmap cooling
static bool decrease_heatmap_values;    // Whether to decrease heatmap values

// --- Called on keypress to update the frame buffer ---
void process_rgb_matrix_blue_heatmap(uint8_t row, uint8_t col)
{
    if (g_led_config.matrix_co[row][col] != NO_LED)
    {
        g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP);
    }
}

// --- Heatmap effect render function ---
bool BLUE_HEATMAP(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0); // Initialize all LEDs to off
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer); // Clear the heatmap
    }

    // Update the timer and determine if we should decrease heatmap values
    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS;
        if (decrease_heatmap_values)
        {
            heatmap_decrease_timer = timer_read();
        }
    }

    // Render the heatmap for key LEDs
    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS && count < RGB_MATRIX_LED_PROCESS_LIMIT; col++)
        {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max)
            {
                count++;
                uint8_t val = g_rgb_frame_buffer[row][col];
                if (!HAS_ANY_FLAGS(g_led_config.flags[index], params->flags)) continue;

                // Convert heatmap value to a blue-to-red gradient
                hsv_t hsv = { 170 - qsub8(val, 85), 255, scale8((qadd8(170, val) - 170) * 3, 255) };
                rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);

                if (decrease_heatmap_values)
                {
                    g_rgb_frame_buffer[row][col] = qsub8(val, 1);
                }
            }
        }
    }

    // Set underglow LEDs to always-on hue 170 (blue)
    for (uint8_t i = led_min; i < led_max; i++)
    {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW))
        {
            hsv_t hsv = { 170, 255, 255 };
            rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
