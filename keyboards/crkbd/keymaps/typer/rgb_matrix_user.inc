// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(BLUE_HEATMAP)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//#ifdef RGB_MATRIX_CUSTOM_USER
#   ifdef ENABLE_RGB_MATRIX_BLUE_HEATMAP

#       include "quantum/rgb_matrix/rgb_matrix.h" // Ensure required headers are included

#       ifndef RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP
#           define RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP 32
#       endif

#       ifndef RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS
#           define RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS 25
#       endif

#       ifndef RGB_MATRIX_BLUE_HEATMAP_SPREAD
#           define RGB_MATRIX_BLUE_HEATMAP_SPREAD 40
#       endif

#       ifndef RGB_MATRIX_BLUE_HEATMAP_AREA_LIMIT
#           define RGB_MATRIX_BLUE_HEATMAP_AREA_LIMIT 16
#       endif

// Ensure the function is only included in the correct context
#       if defined(MATRIX_ROWS) && defined(MATRIX_COLS) && defined(g_rgb_frame_buffer)

void process_rgb_matrix_blue_heatmap(uint8_t row, uint8_t col)
{
# ifdef RGB_MATRIX_BLUE_HEATMAP_SLIM
    g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP);
#else
if (g_led_config.matrix_co[row][col] == NO_LED)
{
    return;
}
for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++)
{
    for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++)
    {
        if (g_led_config.matrix_co[i_row][i_col] == NO_LED)
        {
            continue;
        }
        if (i_row == row && i_col == col)
        {
            g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP);
        }
        else
        {
#define LED_DISTANCE(led_a, led_b) sqrt16(((int16_t)(led_a.x - led_b.x) * (int16_t)(led_a.x - led_b.x)) + ((int16_t)(led_a.y - led_b.y) * (int16_t)(led_a.y - led_b.y)))
            uint8_t distance = LED_DISTANCE(g_led_config.point[g_led_config.matrix_co[row][col]], g_led_config.point[g_led_config.matrix_co[i_row][i_col]]);
#undef LED_DISTANCE
            if (distance <= RGB_MATRIX_BLUE_HEATMAP_SPREAD)
            {
                uint8_t amount = qsub8(RGB_MATRIX_BLUE_HEATMAP_SPREAD, distance);
                if (amount > RGB_MATRIX_BLUE_HEATMAP_AREA_LIMIT)
                {
                    amount = RGB_MATRIX_BLUE_HEATMAP_AREA_LIMIT;
                }
                g_rgb_frame_buffer[i_row][i_col] = qadd8(g_rgb_frame_buffer[i_row][i_col], amount);
            }
        }
    }
}
#            endif
}

static uint16_t blue_heatmap_decrease_timer;
static bool decrease_blue_heatmap_values;

bool BLUE_HEATMAP(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
    }

    if (params->iter == 0) {
        decrease_blue_heatmap_values = timer_elapsed(blue_heatmap_decrease_timer) >= RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS;

        if (decrease_blue_heatmap_values)
        {
            blue_heatmap_decrease_timer = timer_read();
        }
    }

    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS && RGB_MATRIX_LED_PROCESS_LIMIT; col++)
        {
            if (g_led_config.matrix_co[row][col] >= led_min && g_led_config.matrix_co[row][col] < led_max)
            {
                count++;
                uint8_t val = g_rgb_frame_buffer[row][col];
                if (!HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[row][col]], params->flags)) continue;

                hsv_t hsv = { 170, rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v) };
                rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(g_led_config.matrix_co[row][col], rgb.r, rgb.g, rgb.b);

                if (decrease_blue_heatmap_values)
                {
                    g_rgb_frame_buffer[row][col] = qsub8(val, 1);
                }
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#        endif // MATRIX_ROWS && MATRIX_COLS && g_rgb_frame_buffer

#    endif // ENABLE_RGB_MATRIX_BLUE_HEATMAP
#endif     // RGB_MATRIX_CUSTOM_USER
