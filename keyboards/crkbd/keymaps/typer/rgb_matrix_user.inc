// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t TYPER_math(hsv_t hsv, uint16_t offset)
{
    // Adjust brightness based on offset
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

bool TYPER(effect_params_t* params)
{
    return effect_runner_reactive (params, &TYPER_math);
}

#endif
