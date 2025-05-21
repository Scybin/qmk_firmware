// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Heatmap configuration
#define CUSTOM_HEATMAP_INCREASE_STEP 32
#define CUSTOM_HEATMAP_DECREASE_DELAY_MS 25
#define CUSTOM_HEATMAP_SPREAD 40
#define CUSTOM_HEATMAP_AREA_LIMIT 16

// Framebuffer for heatmap values
static uint8_t custom_heatmap_framebuffer[MATRIX_ROWS][MATRIX_COLS] = { 0}
;
static uint16_t custom_heatmap_decrease_timer = 0;
static bool custom_decrease_heatmap_values = false;

static void process_custom_typing_heatmap(uint8_t row, uint8_t col)
{
    if (g_led_config.matrix_co[row][col] == NO_LED)
    {
        return; // Skip if the pressed key doesn't have an LED
    }

    for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++)
    {
        for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++)
        {
            if (g_led_config.matrix_co[i_row][i_col] == NO_LED)
            {
                continue; // Skip if the target key doesn't have an LED
            }

            if (i_row == row && i_col == col)
            {
                // Increase heatmap value for the pressed key
                custom_heatmap_framebuffer[row][col] = qadd8(custom_heatmap_framebuffer[row][col], CUSTOM_HEATMAP_INCREASE_STEP);
            }
            else
            {
                // Calculate distance between LEDs
                uint8_t distance = sqrt16(
                    ((int16_t)(g_led_config.point[g_led_config.matrix_co[row][col]].x -
                               g_led_config.point[g_led_config.matrix_co[i_row][i_col]].x) *
                     (int16_t)(g_led_config.point[g_led_config.matrix_co[row][col]].x -
                               g_led_config.point[g_led_config.matrix_co[i_row][i_col]].x)) +
                    ((int16_t)(g_led_config.point[g_led_config.matrix_co[row][col]].y -
                               g_led_config.point[g_led_config.matrix_co[i_row][i_col]].y) *
                     (int16_t)(g_led_config.point[g_led_config.matrix_co[row][col]].y -
                               g_led_config.point[g_led_config.matrix_co[i_row][i_col]].y)));

                if (distance <= CUSTOM_HEATMAP_SPREAD)
                {
                    uint8_t amount = qsub8(CUSTOM_HEATMAP_SPREAD, distance);
                    if (amount > CUSTOM_HEATMAP_AREA_LIMIT)
                    {
                        amount = CUSTOM_HEATMAP_AREA_LIMIT;
                    }
                    custom_heatmap_framebuffer[i_row][i_col] = qadd8(custom_heatmap_framebuffer[i_row][i_col], amount);
                }
            }
        }
    }
}

bool TYPER(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(custom_heatmap_framebuffer, 0, sizeof(custom_heatmap_framebuffer));
    }

    if (params->iter == 0) {
        custom_decrease_heatmap_values = timer_elapsed(custom_heatmap_decrease_timer) >= CUSTOM_HEATMAP_DECREASE_DELAY_MS;

        if (custom_decrease_heatmap_values)
        {
            custom_heatmap_decrease_timer = timer_read();
        }
    }

    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++)
    {
        for (uint8_t col = 0; col < MATRIX_COLS && count < RGB_MATRIX_LED_PROCESS_LIMIT; col++)
        {
            if (g_led_config.matrix_co[row][col] >= led_min && g_led_config.matrix_co[row][col] < led_max)
            {
                count++;
                uint8_t val = custom_heatmap_framebuffer[row][col];
                if (!HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[row][col]], params->flags))
                {
                    continue;
                }

                hsv_t hsv = {170 - qsub8(val, 85), rgb_matrix_config.hsv.s,
                             scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v)};
                rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(g_led_config.matrix_co[row][col], rgb.r, rgb.g, rgb.b);

                if (custom_decrease_heatmap_values)
                {
                    custom_heatmap_framebuffer[row][col] = qsub8(val, 1);
                }
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif
