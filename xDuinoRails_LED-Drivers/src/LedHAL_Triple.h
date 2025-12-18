#ifndef XDUINORAILS_LED_DRIVERS_TRIPLE_H
#define XDUINORAILS_LED_DRIVERS_TRIPLE_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedTriple : public Led {
public:
    LedTriple(uint8_t pin1, uint8_t pin2, uint8_t pin3, bool isAnode = true) : _pin1(pin1), _pin2(pin2), _pin3(pin3), _isAnode(isAnode) {
        pinMode(_pin1, OUTPUT);
        pinMode(_pin2, OUTPUT);
        pinMode(_pin3, OUTPUT);
        off();
        _brightness = 255;
    }

    void on() override {
        analogWrite(_pin1, _isAnode ? _brightness : 255 - _brightness);
        analogWrite(_pin2, _isAnode ? _brightness : 255 - _brightness);
        analogWrite(_pin3, _isAnode ? _brightness : 255 - _brightness);
    }

    void off() override {
        digitalWrite(_pin1, _isAnode ? LOW : HIGH);
        digitalWrite(_pin2, _isAnode ? LOW : HIGH);
        digitalWrite(_pin3, _isAnode ? LOW : HIGH);
    }

    void setColor(const RgbColor& color) override {
        _color = color;
        if (color.r > 0 || color.g > 0 || color.b > 0) {
            on();
        } else {
            off();
        }
    }

    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
        on();
    }

private:
    uint8_t _pin1;
    uint8_t _pin2;
    uint8_t _pin3;
    bool _isAnode;
};

#endif // XDUINORAILS_LED_DRIVERS_TRIPLE_H
