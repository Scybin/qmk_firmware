#pragma once

// Override the default RGBLight mode
#undef RGBLIGHT_DEFAULT_MODE
#define RGBLIGHT_ANIMATIONS            // Enable RGB animations (required for static mode)
#define RGBLIGHT_DEFAULT_MODE 1T
#define RGBLIGHT_DEFAULT_HUE 170       // Default hue (blue)
#define RGBLIGHT_DEFAULT_SAT 255       // Default saturation (maximum)
#define RGBLIGHT_DEFAULT_VAL 255       // Default brightness (maximum)
#define RGBLIGHT_SLEEP                 // Turn off RGB lighting when the host goes to sleep
#define RGBLIGHT_SAT_STEP 8            // Controls the saturation change step
#define RGBLIGHT_VAL_STEP 8            // Controls the value change step

// Tapping configuration
#define TAPPING_TERM 200  // 200ms tapping term

// OLED configuration
#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#endif
#define OLED_TASK_KB_OVERRIDE
