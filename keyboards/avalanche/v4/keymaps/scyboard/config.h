#define TAPPING_TERM 200  // 200ms tapping term

#define RGBLIGHT_SAT_STEP 8    // Controls the saturation change step
#define RGBLIGHT_VAL_STEP 8    // Controls the value change step

#undef RGBLIGHT_MODE_BREATHING
#undef RGBLIGHT_MODE_RAINBOW_MOOD
#undef RGBLIGHT_MODE_RAINBOW_SWIRL
#undef RGBLIGHT_MODE_SNAKE
#undef RGBLIGHT_MODE_STATIC_GRADIENT
#undef RGBLIGHT_MODE_RGB_TEST
#undef RGBLIGHT_MODE_ALTERNATING

// Define the OLED driver and I2C addresses for both displays
#define OLED_DRIVER_TYPE SSD1306
#define OLED_I2C_ADDRESS_1 0x3C  // I2C address for the first OLED
#define OLED_I2C_ADDRESS_2 0x3D  // I2C address for the second OLED
#define SDA_PIN  PIN_D2  // SDA pin for I2C
#define SCL_PIN  PIN_D3  // SCL pin for I2C
