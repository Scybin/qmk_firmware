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

static hsv_t TYPER_math(hsv_t hsv, uint16_t offset)
{
#            ifdef RGB_MATRIX_TYPER_GRADIENT_MODE
    hsv.h = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 8) >> 4);
#            endif
    hsv.h += scale8(255 - offset, 64);
    return hsv;
}

bool TYPER(effect_params_t* params)
{
    return effect_runner_reactive (params, &TYPER_math);
}
}

#endif
