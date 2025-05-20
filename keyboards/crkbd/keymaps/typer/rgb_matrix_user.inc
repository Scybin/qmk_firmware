// Include the default typing heatmap header
#include "quantum/rgb_matrix/animations/typing_heatmap_anim.h"

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void set_underglow_blue(void)
{
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW)
        {
            rgb_matrix_set_color(i, 0, 0, 255); // Set to blue (R=0, G=0, B=255)
        }
    }
}

bool TYPER(effect_params_t* params)
{
    // Run the default TYPING_HEATMAP effect
    bool result = TYPING_HEATMAP (params);

    // Add custom underglow logic
    set_underglow_blue();

    return result;
}

#endif
