#pragma once

// Tapping configuration
#define TAPPING_TERM 200  // 200ms tapping term

// RGB Matrix configuration
#define RGB_MATRIX_ENABLE
#define RGB_MATRIX_LED_COUNT 64  // Replace 64 with the actual number of LEDs
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR  // Default mode for RGB Matrix
#    define RGB_MATRIX_STARTUP_HUE 170                      // Default hue (blue)
#    define RGB_MATRIX_STARTUP_SAT 255                      // Default saturation
#    define RGB_MATRIX_STARTUP_VAL 255                      // Default brightness
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150               // Limit maximum brightness
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS                  // Enable framebuffer effects
#    define RGB_MATRIX_KEYPRESSES                           // Enable reactive effects based on keypresses
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4                  // Limit LED processing for performance
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26                   // Limit LED flush rate for performance
#endif

// OLED configuration
#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#endif
