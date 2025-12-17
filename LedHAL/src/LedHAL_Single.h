#ifndef LED_HAL_SINGLE_H
#define LED_HAL_SINGLE_H

#include "LedHAL.h"
#include <Arduino.h>

class LedSingle : public Led {
public:
    LedSingle(uint8_t pin, bool isAnode = true) : _pin(pin), _isAnode(isAnode) {
        pinMode(_pin, OUTPUT);
        off();
    }

    void on() override {
        digitalWrite(_pin, _isAnode ? HIGH : LOW);
    }

    void off() override {
        digitalWrite(_pin, _isAnode ? LOW : HIGH);
    }

    void setColor(const RgbColor& color) override {
        // Not applicable for single color LEDs, but must be implemented.
        if (color.r > 0 || color.g > 0 || color.b > 0) {
            on();
        } else {
            off();
        }
    }

private:
    uint8_t _pin;
    bool _isAnode;
};

#endif // LED_HAL_SINGLE_H
