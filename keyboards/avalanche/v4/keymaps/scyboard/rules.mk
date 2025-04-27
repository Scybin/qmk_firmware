# Feature configuration
MOUSEKEY_ENABLE = yes                # Mouse key support
TAP_DANCE_ENABLE = yes               # Tap dance functionality
RGBLIGHT_ENABLE = yes                 # RGB lighting
OLED_ENABLE = yes                     # OLED support

# Optimization settings
LINK_TIME_OPTIMIZATION_ENABLE = yes  # Link-time optimization
EXTRAFLAGS += -flto                  # Additional flags

# Disable unused features
#define NO_ACTION_MACRO              # Macro actions
#define NO_ACTION_FUNCTION           # Function actions
