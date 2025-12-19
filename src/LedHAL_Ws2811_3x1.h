#ifndef XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
#define XDUINORAILS_LED_DRIVERS_WS2811_3X1_H

#include "LedStrip.h"
#include <Adafruit_NeoPixel.h>

class LedWs2811_3x1 : public LedStrip {
public:
    LedWs2811_3x1(uint8_t pin, uint16_t numLeds, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : LedStrip(groupId, indexInGroup), _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
        _strip.begin();
        off();
    }

    void on() override {
        setColor({255, 255, 255});
    }

    void off() override {
        setColor({0, 0, 0});
    }

    void setColor(const RgbColor& color) override {
        uint8_t brightness = (uint8_t)(((uint16_t)color.r * 77 + (uint16_t)color.g * 150 + (uint16_t)color.b * 29) >> 8);
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, brightness, brightness, brightness);
        }
        show();
    }

    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            uint8_t brightness = (uint8_t)(((uint16_t)color.r * 77 + (uint16_t)color.g * 150 + (uint16_t)color.b * 29) >> 8);
            _strip.setPixelColor(pixelIndex, brightness, brightness, brightness);
            show();
        }
    }

    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, _brightness, _brightness, _brightness);
        }
        _strip.show();
    }

    void show() override {
        _strip.show();
    }

    uint16_t numPixels() const {
        return _strip.numPixels();
    }

private:
    uint16_t _numLeds;
    Adafruit_NeoPixel _strip;
};

#endif // XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
