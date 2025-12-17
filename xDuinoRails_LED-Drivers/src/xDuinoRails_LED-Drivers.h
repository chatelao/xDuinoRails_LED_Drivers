#ifndef XDUINORAILS_LED_DRIVERS_H
#define XDUINORAILS_LED_DRIVERS_H

#include <stdint.h>

// Define a structure for RGB colors
struct RgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Led {
public:
    virtual ~Led() {}

    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setColor(const RgbColor& color) = 0;
};

// Enum for different LED types
enum LedType {
    SINGLE_LED,
    DUAL_LED,
    TRIPLE_LED,
    RGB_LED,
    NEOPIXEL
};

class LedDriverHAL {
public:
    virtual ~LedDriverHAL() {}
    virtual Led* addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0) = 0;
};

#endif // XDUINORAILS_LED_DRIVERS_H
