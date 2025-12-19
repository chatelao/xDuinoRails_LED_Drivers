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
    Led(uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : _groupId(groupId), _indexInGroup(indexInGroup), _brightness(255) {}
    virtual ~Led() {}

    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setColor(const RgbColor& color) = 0;
    virtual void setBrightness(uint8_t brightness) = 0;

    uint8_t getGroupId() const { return _groupId; }
    uint16_t getIndexInGroup() const { return _indexInGroup; }

protected:
    uint8_t _groupId;
    uint16_t _indexInGroup;
    uint8_t _brightness;
};

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
