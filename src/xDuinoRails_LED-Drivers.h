#ifndef XDUINORAILS_LED_DRIVERS_H
#define XDUINORAILS_LED_DRIVERS_H

#include "Led.h"

// Enum for different LED types
enum LedType {
    SINGLE_LED,
    MULTI_LED,
    RGB_LED,
    NEOPIXEL,
    WS2811_3x1,
    CHARLIEPLEX,
    MATRIX
};

class LedDriverHAL {
public:
    virtual ~LedDriverHAL() {}

    virtual Led* addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0, uint8_t groupId = 0) = 0;
    virtual Led* getLed(uint16_t globalIndex) = 0;
    virtual void setGroupColor(uint8_t groupId, const RgbColor& color) = 0;
    virtual void setGroupBrightness(uint8_t groupId, uint8_t brightness) = 0;
};

#endif // XDUINORAILS_LED_DRIVERS_H
