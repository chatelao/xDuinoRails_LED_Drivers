#ifndef XDUINORAILS_LED_DRIVERS_MULTI_H
#define XDUINORAILS_LED_DRIVERS_MULTI_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedMulti : public Led {
public:
    LedMulti(const uint8_t* pins, uint8_t pinCount, bool isAnode = true) : _pinCount(pinCount), _isAnode(isAnode) {
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
            digitalWrite(_pins[i], _isAnode ? HIGH : LOW);
        }
    }

    void off() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            digitalWrite(_pins[i], _isAnode ? LOW : HIGH);
        }
    }

    void setColor(const RgbColor& color) override {
        // Simplified for multi LEDs, treating them as a single color.
        if (color.r > 0 || color.g > 0 || color.b > 0) {
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
