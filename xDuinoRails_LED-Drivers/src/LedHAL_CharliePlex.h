#ifndef XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H
#define XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>

class LedCharliePlex : public Led {
public:
    LedCharliePlex(const uint8_t* pins, uint8_t pinCount, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : Led(groupId, indexInGroup), _pinCount(pinCount), _numLeds(pinCount * (pinCount - 1)) {
        _pins = new uint8_t[pinCount];
        for (uint8_t i = 0; i < pinCount; i++) {
            _pins[i] = pins[i];
        }
        _ledColors = new RgbColor[_numLeds];
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = {0, 0, 0};
        }
        off();
    }

    ~LedCharliePlex() override {
        delete[] _pins;
        delete[] _ledColors;
    }

    void on() override {
        setColor({255, 255, 255});
    }

    void off() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = {0, 0, 0};
        }
    }

    void setColor(const RgbColor& color) override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = color;
        }
    }

    void setColor(uint16_t ledIndex, const RgbColor& color) {
        if (ledIndex < _numLeds) {
            _ledColors[ledIndex] = color;
        }
    }

    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
    }

    void show() {
        for (uint16_t i = 0; i < _numLeds; i++) {
            const auto& color = _ledColors[i];
            if (color.r > 0 || color.g > 0 || color.b > 0) {
                lightLed(i);
                delayMicroseconds(_brightness * 10);
            }
        }
        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }
    }

private:
    void lightLed(uint16_t ledIndex) {
        uint8_t anodePinIndex = 0;
        uint8_t cathodePinIndex = 0;
        uint16_t currentIndex = 0;

        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }

        for (uint8_t i = 0; i < _pinCount; i++) {
            for (uint8_t j = 0; j < _pinCount; j++) {
                if (i == j) continue;

                if (currentIndex == ledIndex) {
                    anodePinIndex = i;
                    cathodePinIndex = j;

                    pinMode(_pins[anodePinIndex], OUTPUT);
                    digitalWrite(_pins[anodePinIndex], HIGH);
                    pinMode(_pins[cathodePinIndex], OUTPUT);
                    digitalWrite(_pins[cathodePinIndex], LOW);
                    return;
                }
                currentIndex++;
            }
        }
    }

    uint8_t* _pins;
    uint8_t _pinCount;
    uint16_t _numLeds;
    RgbColor* _ledColors;
};

#endif // XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H
