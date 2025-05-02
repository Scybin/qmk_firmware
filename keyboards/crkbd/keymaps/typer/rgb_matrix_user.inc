// Declare the custom effect
RGB_MATRIX_EFFECT(BLUE_HEATMAP

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "timer.h"
#include "math.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

#ifndef RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP
#    define RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP 32
#endif

#ifndef RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS
#    define RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS 25
#endif

#define SPREAD_RADIUS 6.0f    // Max radius to affect surrounding LEDs
#define SPREAD_FALLOFF 1.5f   // Higher values = quicker dimming with distance

static uint16_t heatmap_decrease_timer;
static bool decrease_heatmap_values;

void process_rgb_matrix_blue_heatmap(uint8_t row, uint8_t col)
{
    uint8_t center_index = g_led_config.matrix_co[row][col];
    if (center_index == NO_LED) return;

    // Get physical position of keypress
    int8_t x0 = g_led_config.point[center_index].x;
    int8_t y0 = g_led_config.point[center_index].y;

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        int8_t dx = g_led_config.point[i].x - x0;
        int8_t dy = g_led_config.point[i].y - y0;
        float dist = sqrtf((float)(dx * dx + dy * dy));

        if (dist <= SPREAD_RADIUS)
        {
            uint8_t boost = (uint8_t)((1.0f - (dist / SPREAD_RADIUS)) * RGB_MATRIX_BLUE_HEATMAP_INCREASE_STEP);
            g_rgb_frame_buffer[i / MATRIX_COLS][i % MATRIX_COLS] = qadd8(g_rgb_frame_buffer[i / MATRIX_COLS][i % MATRIX_COLS], boost);
        }
    }
}

bool BLUE_HEATMAP(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
    }

    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_BLUE_HEATMAP_DECREASE_DELAY_MS;
        if (decrease_heatmap_values)
        {
            heatmap_decrease_timer = timer_read();
        }
    }

    uint8_t count = 0;
    for (uint8_t i = led_min; i < led_max && count < RGB_MATRIX_LED_PROCESS_LIMIT; i++)
    {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue;
        count++;

        uint8_t row = i / MATRIX_COLS;
        uint8_t col = i % MATRIX_COLS;
        uint8_t val = g_rgb_frame_buffer[row][col];

        // Convert value to blue-red gradient
        hsv_t hsv = { 170 - qsub8(val, 85), 255, scale8((qadd8(170, val) - 170) * 3, 255) };
        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

        if (decrease_heatmap_values)
        {
            g_rgb_frame_buffer[row][col] = qsub8(val, 1);
        }
    }

    // Underglow LEDs: always on at hue 170 (blue)
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
