#ifndef XDUINORAILS_LED_DRIVERS_RGB_H
#define XDUINORAILS_LED_DRIVERS_RGB_H

#include "Led.h"
#include <Arduino.h>

class LedRgb : public Led {
public:
    enum RgbLedType { ANODE, CATHODE };

    LedRgb(uint8_t pinR, uint8_t pinG, uint8_t pinB, uint8_t groupId = 0, uint16_t indexInGroup = 0, RgbLedType type = ANODE)
        : Led(groupId, indexInGroup), _pinR(pinR), _pinG(pinG), _pinB(pinB), _isAnode(type == ANODE) {
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
        _color = color;
        applyColor();
    }

    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
        applyColor();
    }

private:
    void applyColor() {
        uint8_t r = map(_color.r, 0, 255, 0, _brightness);
        uint8_t g = map(_color.g, 0, 255, 0, _brightness);
        uint8_t b = map(_color.b, 0, 255, 0, _brightness);

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
    RgbColor _color;
};

#endif // XDUINORAILS_LED_DRIVERS_RGB_H
