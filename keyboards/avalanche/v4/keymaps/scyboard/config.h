#pragma once

// Override the default RGBLight mode
#undef RGBLIGHT_DEFAULT_MODE
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#define RGBLIGHT_DEFAULT_HUE 170  // Default hue (blue)

// Tapping configuration
#define TAPPING_TERM 200  // 200ms tapping term

// OLED configuration
#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#endif
#define OLED_TASK_KB_OVERRIDE
