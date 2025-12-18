#ifndef XDUINORAILS_LED_DRIVERS_RGB_H
#define XDUINORAILS_LED_DRIVERS_RGB_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedRgb : public Led {
public:
    enum RgbLedType { ANODE, CATHODE };
    LedRgb(uint8_t pinR, uint8_t pinG, uint8_t pinB, RgbLedType type = ANODE) : _pinR(pinR), _pinG(pinG), _pinB(pinB), _isAnode(type == ANODE) {
        pinMode(_pinR, OUTPUT);
        pinMode(_pinG, OUTPUT);
        pinMode(_pinB, OUTPUT);
        off();
        _brightness = 255;
    }

    void on() override {
        setColor({255, 255, 255});
    }

    void off() override {
        setColor({0, 0, 0});
    }

    void setColor(const RgbColor& color) override {
        _color = color;
        applyColor();
    }

    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
        applyColor();
    }

private:
    void applyColor() {
        uint8_t r = map(_brightness, 0, 255, 0, _color.r);
        uint8_t g = map(_brightness, 0, 255, 0, _color.g);
        uint8_t b = map(_brightness, 0, 255, 0, _color.b);

        if (_isAnode) {
            analogWrite(_pinR, 255 - r);
            analogWrite(_pinG, 255 - g);
            analogWrite(_pinB, 255 - b);
        } else {
            analogWrite(_pinR, r);
            analogWrite(_pinG, g);
            analogWrite(_pinB, b);
        }
    }

    uint8_t _pinR;
    uint8_t _pinG;
    uint8_t _pinB;
    bool _isAnode;
};

#endif // XDUINORAILS_LED_DRIVERS_RGB_H
