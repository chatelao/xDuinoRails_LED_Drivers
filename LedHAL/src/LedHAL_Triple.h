#ifndef LED_HAL_TRIPLE_H
#define LED_HAL_TRIPLE_H

#include "LedHAL.h"
#include <Arduino.h>

class LedTriple : public Led {
public:
    LedTriple(uint8_t pin1, uint8_t pin2, uint8_t pin3, bool isAnode = true) : _pin1(pin1), _pin2(pin2), _pin3(pin3), _isAnode(isAnode) {
        pinMode(_pin1, OUTPUT);
        pinMode(_pin2, OUTPUT);
        pinMode(_pin3, OUTPUT);
        off();
    }

    void on() override {
        digitalWrite(_pin1, _isAnode ? HIGH : LOW);
        digitalWrite(_pin2, _isAnode ? HIGH : LOW);
        digitalWrite(_pin3, _isAnode ? HIGH : LOW);
    }

    void off() override {
        digitalWrite(_pin1, _isAnode ? LOW : HIGH);
        digitalWrite(_pin2, _isAnode ? LOW : HIGH);
        digitalWrite(_pin3, _isAnode ? LOW : HIGH);
    }

    void setColor(const RgbColor& color) override {
        // Simplified for triple LEDs, treating them as a single color.
        if (color.r > 0 || color.g > 0 || color.b > 0) {
            on();
        } else {
            off();
        }
    }

private:
    uint8_t _pin1;
    uint8_t _pin2;
    uint8_t _pin3;
    bool _isAnode;
};

#endif // LED_HAL_TRIPLE_H
