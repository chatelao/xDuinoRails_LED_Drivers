#ifndef XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H
#define XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H

#include "LedStrip.h"
#include <Arduino.h>

class LedCharliePlex : public LedStrip {
public:
    LedCharliePlex(const uint8_t* pins, uint8_t pinCount, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : LedStrip(groupId, indexInGroup), _pinCount(pinCount), _numLeds(pinCount * (pinCount - 1)) {
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
        show();
    }

    void off() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = {0, 0, 0};
        }
        show();
    }

    void setColor(const RgbColor& color) override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = color;
        }
        show();
    }

    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            _ledColors[pixelIndex] = color;
        }
    }

    void setBrightness(uint8_t brightness) override {
        LedStrip::setBrightness(brightness);
    }

    void show() override {
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
