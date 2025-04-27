#pragma once

// Tapping configuration
#define TAPPING_TERM 200  // 200ms tapping term

// RGB lighting configuration
#define RGBLIGHT_SAT_STEP 8    // Saturation change step
#define RGBLIGHT_VAL_STEP 8    // Value change step

// Disable unused RGB lighting modes
#undef RGBLIGHT_MODE_BREATHING
#undef RGBLIGHT_MODE_RAINBOW_MOOD
#undef RGBLIGHT_MODE_RAINBOW_SWIRL
#undef RGBLIGHT_MODE_SNAKE
#undef RGBLIGHT_MODE_STATIC_GRADIENT
#undef RGBLIGHT_MODE_RGB_TEST
#undef RGBLIGHT_MODE_ALTERNATING

// OLED configuration
#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE  // Enable dual OLED support for split keyboards
#endif
