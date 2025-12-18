#ifndef XDUINORAILS_LED_DRIVERS_SINGLE_H
#define XDUINORAILS_LED_DRIVERS_SINGLE_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedSingle : public Led {
public:
    LedSingle(uint8_t pin, bool isAnode = true) : _pin(pin), _isAnode(isAnode) {
        pinMode(_pin, OUTPUT);
        off();
        _brightness = 255;
    }

    void on() override {
        analogWrite(_pin, _isAnode ? _brightness : 255 - _brightness);
    }

    void off() override {
        digitalWrite(_pin, _isAnode ? LOW : HIGH);
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
    uint8_t _pin;
    bool _isAnode;
};

#endif // XDUINORAILS_LED_DRIVERS_SINGLE_H
