
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_CUSTOM_TYPING_HEATMAP)
RGB_MATRIX_EFFECT(CUSTOM_TYPING_HEATMAP)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#        include "print.h"

// #    ifndef RGB_MATRIX_CUSTOM_TYPING_HEATMAP_DECREASE_DELAY_MS
// #        define RGB_MATRIX_CUSTOM_TYPING_HEATMAP_DECREASE_DELAY_MS 25
// #    endif

#        ifndef RGB_MATRIX_CUSTOM_TYPING_HEATMAP_SPREAD
#            define RGB_MATRIX_CUSTOM_TYPING_HEATMAP_SPREAD 40
#        endif

#        ifndef RGB_MATRIX_CUSTOM_TYPING_HEATMAP_AREA_LIMIT
#            define RGB_MATRIX_CUSTOM_TYPING_HEATMAP_AREA_LIMIT 16
#        endif

void process_rgb_matrix_CUSTOM_TYPING_HEATMAP(uint8_t row, uint8_t col) {
#        ifdef RGB_MATRIX_CUSTOM_TYPING_HEATMAP_SLIM
//     // Limit effect to pressed keys
//     g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], 32);
#        else
    //     if (g_led_config.matrix_co[row][col] == NO_LED) { // skip as pressed key doesn't have an led position
    //         return;
    //     }
    // get the current key's led position
    uint8_t current_key_led_idx = g_led_config.matrix_co[row][col];
    for (uint8_t led_idx = 0; led_idx < RGB_MATRIX_LED_COUNT; led_idx++) {
        if (led_idx == current_key_led_idx) {
            g_rgb_frame_buffer_leds_hack[led_idx] = qadd8(g_rgb_frame_buffer_leds_hack[led_idx], 32);
        } else {
#            define LED_DISTANCE(led_a, led_b) sqrt16(((int16_t)(led_a.x - led_b.x) * (int16_t)(led_a.x - led_b.x)) + ((int16_t)(led_a.y - led_b.y) * (int16_t)(led_a.y - led_b.y)))
            uint8_t distance = LED_DISTANCE(g_led_config.point[current_key_led_idx], g_led_config.point[led_idx]);
#            undef LED_DISTANCE
            if (distance <= RGB_MATRIX_CUSTOM_TYPING_HEATMAP_SPREAD) {
                uint8_t amount = qsub8(RGB_MATRIX_CUSTOM_TYPING_HEATMAP_SPREAD, distance);
                if (amount > RGB_MATRIX_CUSTOM_TYPING_HEATMAP_AREA_LIMIT) {
                    amount = RGB_MATRIX_CUSTOM_TYPING_HEATMAP_AREA_LIMIT;
                }
                g_rgb_frame_buffer_leds_hack[led_idx] = qadd8(g_rgb_frame_buffer_leds_hack[led_idx], amount);
            }
        }
    }
#        endif
}

// A timer to track the last time we decremented all heatmap values.
static uint16_t heatmap_decrease_timer;
// Whether we should decrement the heatmap values during the next update.
static bool decrease_heatmap_values;

bool CUSTOM_TYPING_HEATMAP(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer_leds_hack, 0, sizeof(g_rgb_frame_buffer_leds_hack));
    }

    // The heatmap animation might run in several iterations depending on
    // `RGB_MATRIX_LED_PROCESS_LIMIT`, therefore we only want to update the
    // timer when the animation starts.
    if (params->iter == 0) {
        decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_CUSTOM_TYPING_HEATMAP_DECREASE_DELAY_MS;

        // Restart the timer if we are going to decrease the heatmap this frame.
        if (decrease_heatmap_values) {
            heatmap_decrease_timer = timer_read();
        }
    }

    // Render heatmap & decrease
    uint8_t count = 0;
    for (uint8_t led_idx = 0; led_idx < RGB_MATRIX_LED_COUNT; led_idx++) {
        count++;
        uint8_t val = g_rgb_frame_buffer_leds_hack[led_idx];
        if (!HAS_ANY_FLAGS(g_led_config.flags[led_idx], params->flags)) continue;

        HSV hsv = {170 - qsub8(val, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v)};
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_idx, rgb.r, rgb.g, rgb.b);

        if (decrease_heatmap_values) {
            g_rgb_frame_buffer_leds_hack[led_idx] = qsub8(val, 1);
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}
#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_CUSTOM_TYPING_HEATMAP)
