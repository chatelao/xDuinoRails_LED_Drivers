#ifndef XDUINORAILS_LED_DRIVERS_H
#define XDUINORAILS_LED_DRIVERS_H

#include <stdint.h>
#include <vector>

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
    virtual void setBrightness(uint8_t brightness) = 0;
    virtual RgbColor getColor() const { return _color; }

protected:
    RgbColor _color;
    uint8_t _brightness;
};

// Enum for different LED types
enum LedType {
    SINGLE_LED,
    DUAL_LED,
    TRIPLE_LED,
    RGB_LED,
    NEOPIXEL,
    WS2811_3x1
};

class LedDriverHAL {
protected:
    std::vector<Led*> _leds;
    std::vector<std::vector<Led*>> _ledGroups;

public:
    virtual ~LedDriverHAL() {
        for (Led* led : _leds) {
            delete led;
        }
        _leds.clear();
        _ledGroups.clear();
    }

    virtual int addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0, uint8_t groupId = 0) = 0;

    Led* getLed(uint16_t index) {
        if (index < _leds.size()) {
            return _leds[index];
        }
        return nullptr;
    }

    void setGroupColor(uint8_t groupId, const RgbColor& color) {
        if (groupId < _ledGroups.size()) {
            for (Led* led : _ledGroups[groupId]) {
                led->setColor(color);
            }
        }
    }

    void setGroupBrightness(uint8_t groupId, uint8_t brightness) {
        if (groupId < _ledGroups.size()) {
            for (Led* led : _ledGroups[groupId]) {
                led->setBrightness(brightness);
            }
        }
    }

    void groupOn(uint8_t groupId) {
        if (groupId < _ledGroups.size()) {
            for (Led* led : _ledGroups[groupId]) {
                led->on();
            }
        }
    }

    void groupOff(uint8_t groupId) {
        if (groupId < _ledGroups.size()) {
            for (Led* led : _ledGroups[groupId]) {
                led->off();
            }
        }
    }
};

#endif // XDUINORAILS_LED_DRIVERS_H
