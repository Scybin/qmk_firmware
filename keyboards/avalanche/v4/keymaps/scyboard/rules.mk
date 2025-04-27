# Feature configuration
MOUSEKEY_ENABLE = yes                # Enable mouse key support
TAP_DANCE_ENABLE = yes               # Enable tap dance functionality
RGBLIGHT_ENABLE = no                 # Disable RGB lighting
RGB_MATRIX_ENABLE = yes              # Enable RGB matrix effects
OLED_ENABLE = no                     # Disable OLED support

# Optimization settings
LINK_TIME_OPTIMIZATION_ENABLE = yes  # Enable link-time optimization for smaller firmware size
EXTRAFLAGS += -flto                  # Additional flags for link-time optimization

# Disable unused features
#define NO_ACTION_MACRO              # Disable macro actions
#define NO_ACTION_FUNCTION           # Disable function actions
