#ifndef XDUINORAILS_LED_DRIVERS_SINGLE_H
#define XDUINORAILS_LED_DRIVERS_SINGLE_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedSingle : public Led {
public:
    LedSingle(uint8_t pin, uint8_t groupId = 0, uint16_t indexInGroup = 0, bool isAnode = true)
        : Led(groupId, indexInGroup), _pin(pin), _isAnode(isAnode) {
        pinMode(_pin, OUTPUT);
        off();
    }

    void on() override {
        if (_isAnode) {
            analogWrite(_pin, _brightness);
        } else {
            analogWrite(_pin, 255 - _brightness);
        }
    }

    void off() override {
        digitalWrite(_pin, _isAnode ? LOW : HIGH);
    }

    void setColor(const RgbColor& color) override {
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        setBrightness(brightness);
    }

    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
        if (brightness > 0) {
            on();
        } else {
            off();
        }
    }

private:
    uint8_t _pin;
    bool _isAnode;
};

#endif // XDUINORAILS_LED_DRIVERS_SINGLE_H
