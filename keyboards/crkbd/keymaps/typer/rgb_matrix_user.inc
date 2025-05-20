// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool TYPER(effect_params_t* params)
{
    // Run the default TYPING_HEATMAP effect
    return TYPING_HEATMAP (params);
}

#endif
