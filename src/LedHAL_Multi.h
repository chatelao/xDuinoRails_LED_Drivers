#ifndef XDUINORAILS_LED_DRIVERS_MULTI_H
#define XDUINORAILS_LED_DRIVERS_MULTI_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedMulti : public Led {
public:
    LedMulti(const uint8_t* pins, uint8_t pinCount, uint8_t groupId = 0, uint16_t indexInGroup = 0, bool isAnode = true)
        : Led(groupId, indexInGroup), _pinCount(pinCount), _isAnode(isAnode) {
        _pins = new uint8_t[pinCount];
        for (uint8_t i = 0; i < _pinCount; i++) {
            _pins[i] = pins[i];
            pinMode(_pins[i], OUTPUT);
        }
        off();
    }

    ~LedMulti() {
        delete[] _pins;
    }

    void on() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            if (_isAnode) {
                analogWrite(_pins[i], _brightness);
            } else {
                analogWrite(_pins[i], 255 - _brightness);
            }
        }
    }

    void off() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            digitalWrite(_pins[i], _isAnode ? LOW : HIGH);
        }
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
    uint8_t* _pins;
    uint8_t _pinCount;
    bool _isAnode;
};

#endif // XDUINORAILS_LED_DRIVERS_MULTI_H
