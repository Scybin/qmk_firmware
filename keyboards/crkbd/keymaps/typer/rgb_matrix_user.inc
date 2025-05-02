// !!! DO NOT ADD #pragma once !!! //

// Step 1: Declare your custom effect(s)
RGB_MATRIX_EFFECT(CUSTOM_HEATMAP)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Step 2: Configuration defaults
#ifndef RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP
#    define RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP 32
#endif
#ifndef RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS
#    define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
#endif
#ifndef RGB_MATRIX_TYPING_HEATMAP_SPREAD
#    define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40
#endif
#ifndef RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT
#    define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
#endif

// Step 3: Framebuffer effect tracking
static uint16_t heatmap_decrease_timer;
static bool decrease_heatmap_values;

// Step 4: Heatmap typing feedback logic
void process_rgb_matrix_custom_heatmap(uint8_t row, uint8_t col)
{
    if (g_led_config.matrix_co[row][col] == NO_LED) return;

    for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++)
    {
        for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++)
        {
            if (g_led_config.matrix_co[i_row][i_col] == NO_LED) continue;

            if (i_row == row && i_col == col)
            {
                g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP);
            }
            else
            {
#define LED_DISTANCE(a, b) sqrt16((int16_t)(a.x - b.x) * (int16_t)(a.x - b.x) + (int16_t)(a.y - b.y) * (int16_t)(a.y - b.y))
                uint8_t dist = LED_DISTANCE(g_led_config.point[g_led_config.matrix_co[row][col]], g_led_config.point[g_led_config.matrix_co[i_row][i_col]]);
#undef LED_DISTANCE

                if (dist <= RGB_MATRIX_TYPING_HEATMAP_SPREAD)
                {
                    uint8_t amount = qsub8(RGB_MATRIX_TYPING_HEATMAP_SPREAD, dist);
                    if (amount > RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT)
                    {
                        amount = RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT;
                    }
                    g_rgb_frame_buffer[i_row][i_col] = qadd8(g_rgb_frame_buffer[i_row][i_col], amount);
                }
            }
        }
    }
}

// Step 5: Custom Heatmap Effect Core
bool CUSTOM_HEATMAP(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
    }

    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS;
        if (decrease_heatmap_values) heatmap_decrease_timer = timer_read();
    }

    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS && count < RGB_MATRIX_LED_PROCESS_LIMIT; col++)
        {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index < led_min || index >= led_max) continue;
            if (!HAS_ANY_FLAGS(g_led_config.flags[index], params->flags)) continue;

            count++;
            uint8_t val = g_rgb_frame_buffer[row][col];

            hsv_t hsv = {
                .h = 170 - qsub8(val, 85),
                .s = rgb_matrix_config.hsv.s,
                .v = scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v),
            };
            rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);

            if (decrease_heatmap_values)
            {
                g_rgb_frame_buffer[row][col] = qsub8(val, 1);
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
