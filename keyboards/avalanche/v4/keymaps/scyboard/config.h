#pragma once

// Override the default RGBLight mode
#undef RGBLIGHT_DEFAULT_MODE
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT

// Tapping configuration
#define TAPPING_TERM 200  // 200ms tapping term

// RGB lighting configuration
#define RGBLIGHT_SAT_STEP 8    // Controls the saturation change step
#define RGBLIGHT_VAL_STEP 8    // Controls the value change step

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
#    define SPLIT_OLED_ENABLE
#endif
#define OLED_TASK_KB_OVERRIDE
