#ifndef XDUINORAILS_LED_DRIVERS_RGB_H
#define XDUINORAILS_LED_DRIVERS_RGB_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedRgb : public Led {
public:
    LedRgb(uint8_t pinR, uint8_t pinG, uint8_t pinB, bool isAnode = false) : _pinR(pinR), _pinG(pinG), _pinB(pinB), _isAnode(isAnode) {
        pinMode(_pinR, OUTPUT);
        pinMode(_pinG, OUTPUT);
        pinMode(_pinB, OUTPUT);
        off();
    }

    void on() override {
        setColor({255, 255, 255});
    }

    void off() override {
        setColor({0, 0, 0});
    }

    void setColor(const RgbColor& color) override {
        if (_isAnode) {
            analogWrite(_pinR, 255 - color.r);
            analogWrite(_pinG, 255 - color.g);
            analogWrite(_pinB, 255 - color.b);
        } else {
            analogWrite(_pinR, color.r);
            analogWrite(_pinG, color.g);
            analogWrite(_pinB, color.b);
        }
    }

private:
    uint8_t _pinR;
    uint8_t _pinG;
    uint8_t _pinB;
    bool _isAnode;
};

#endif // XDUINORAILS_LED_DRIVERS_RGB_H
