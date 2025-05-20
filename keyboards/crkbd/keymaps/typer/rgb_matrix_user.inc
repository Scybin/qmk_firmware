// !!! DO NOT ADD #pragma once !!! //

// Step 1. Declare your custom RGB Matrix effect
RGB_MATRIX_EFFECT(TYPER_HEATMAP)

// Step 2. Define the effect
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#ifndef RGB_MATRIX_HEATMAP_INCREASE_STEP
#    define RGB_MATRIX_HEATMAP_INCREASE_STEP 32
#endif

#ifndef RGB_MATRIX_HEATMAP_DECREASE_DELAY_MS
#    define RGB_MATRIX_HEATMAP_DECREASE_DELAY_MS 25
#endif

#ifndef RGB_MATRIX_HEATMAP_SPREAD
#    define RGB_MATRIX_HEATMAP_SPREAD 40
#endif

#ifndef RGB_MATRIX_HEATMAP_AREA_LIMIT
#    define RGB_MATRIX_HEATMAP_AREA_LIMIT 16
#endif

static uint8_t g_heatmap_buffer[MATRIX_ROWS][MATRIX_COLS] = { 0}
;
static uint16_t heatmap_decrease_timer;
static bool decrease_heatmap_values;

void process_rgb_matrix_typer_heatmap(uint8_t row, uint8_t col)
{
    if (g_led_config.matrix_co[row][col] == NO_LED) return;

    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
    {
        for (uint8_t c = 0; c < MATRIX_COLS; c++)
        {
            if (g_led_config.matrix_co[r][c] == NO_LED) continue;

            if (r == row && c == col)
            {
                g_heatmap_buffer[r][c] = qadd8(g_heatmap_buffer[r][c], RGB_MATRIX_HEATMAP_INCREASE_STEP);
            }
            else
            {
                int16_t dx = g_led_config.point[g_led_config.matrix_co[r][c]].x - g_led_config.point[g_led_config.matrix_co[row][col]].x;
                int16_t dy = g_led_config.point[g_led_config.matrix_co[r][c]].y - g_led_config.point[g_led_config.matrix_co[row][col]].y;
                uint8_t dist = sqrt16(dx * dx + dy * dy);

                if (dist <= RGB_MATRIX_HEATMAP_SPREAD)
                {
                    uint8_t amt = qsub8(RGB_MATRIX_HEATMAP_SPREAD, dist);
                    if (amt > RGB_MATRIX_HEATMAP_AREA_LIMIT)
                    {
                        amt = RGB_MATRIX_HEATMAP_AREA_LIMIT;
                    }
                    g_heatmap_buffer[r][c] = qadd8(g_heatmap_buffer[r][c], amt);
                }
            }
        }
    }
}

static bool TYPER_HEATMAP(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_heatmap_buffer, 0, sizeof g_heatmap_buffer);
        heatmap_decrease_timer = timer_read();
    }

    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_HEATMAP_DECREASE_DELAY_MS;
        if (decrease_heatmap_values)
        {
            heatmap_decrease_timer = timer_read();
        }
    }

    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS && count < RGB_MATRIX_LED_PROCESS_LIMIT; col++)
        {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led < led_min || led >= led_max) continue;
            if (!HAS_ANY_FLAGS(g_led_config.flags[led], params->flags)) continue;

            count++;
            uint8_t heat = g_heatmap_buffer[row][col];

            hsv_t hsv = {
                .h = 170 - qsub8(heat, 85),
                .s = rgb_matrix_config.hsv.s,
                .v = scale8((qadd8(170, heat) - 170) * 3, rgb_matrix_config.hsv.v),
            };

            rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);

            if (decrease_heatmap_values)
            {
                g_heatmap_buffer[row][col] = qsub8(heat, 1);
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
