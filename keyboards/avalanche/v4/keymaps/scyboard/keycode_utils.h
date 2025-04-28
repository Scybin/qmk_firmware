   #ifndef KEYCODE_UTILS_H
   #define KEYCODE_UTILS_H

   #include QMK_KEYBOARD_H

   // Include layer and tap dance definitions
   enum layer {
       BASE,
       LIGHT,
       DEV,
       OSRS,
       LOWER,
       UPPER,
   };

   enum tap_dance {
       SHIFT_CAPS = 1,
       LOSRS,
       LBASE,
       LLIGHT,
   };

   const char* get_keycode_name(uint16_t keycode);

   #endif
