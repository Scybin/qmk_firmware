// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t TYPER_math(hsv_t hsv, uint16_t offset)
{
    // Set hue to purple when a key is pressed
    hsv.h = 200; // Purple hue
    hsv.v = scale8(255 - offset, hsv.v); // Adjust brightness based on offset
    return hsv;
}

bool TYPER(effect_params_t* params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        // Set all LEDs to blue (hue 170) as the default
        hsv_t default_hsv = { 170, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
        rgb_t default_rgb = rgb_matrix_hsv_to_rgb(default_hsv);
        rgb_matrix_set_color_all(default_rgb.r, default_rgb.g, default_rgb.b);
    }

    // Apply the reactive effect for pressed keys
    return effect_runner_reactive (params, &TYPER_math);
}

#endif
