#pragma once

// Tapping configuration
#define TAPPING_TERM 200  // 200ms tapping term

// RGB Matrix configuration
#define RGB_MATRIX_ENABLE
#define RGB_DI_PIN D3  // This matches the "pin" defined in the `ws2812` section of your keyboard.json
#define RGBLED_NUM 64   // This matches the "led_count" defined in the `rgblight` section of your keyboard.json
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 10
#define RGB_MATRIX_KEYPRESSES  // Enable reactive effects
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_SPLIT {32, 32}  // Split configuration for 32 LEDs per side
#define SPLIT_TRANSPORT_MIRROR

// OLED configuration
#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#endif
