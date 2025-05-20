// Include the default typing heatmap header
#include "quantum/rgb_matrix/animations/typing_heatmap_anim.h"

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(TYPER)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool TYPER(effect_params_t* params)
{
    // Run the default TYPING_HEATMAP effect
    return TYPING_HEATMAP (params);
}

#endif
