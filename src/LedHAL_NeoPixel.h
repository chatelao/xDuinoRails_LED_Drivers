#ifndef XDUINORAILS_LED_DRIVERS_NEOPIXEL_H
#define XDUINORAILS_LED_DRIVERS_NEOPIXEL_H

#include "LedStrip.h"
#include <Adafruit_NeoPixel.h>

class LedNeoPixel : public LedStrip {
public:
    LedNeoPixel(uint8_t pin, uint16_t numLeds, uint8_t groupId = 0, uint16_t indexInGroup = 0)
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
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, color.r, color.g, color.b);
        }
        _strip.show();
    }

    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            _strip.setPixelColor(pixelIndex, color.r, color.g, color.b);
        }
    }

    void setColor(uint16_t pixelIndex, uint32_t color) {
        if (pixelIndex < _numLeds) {
            _strip.setPixelColor(pixelIndex, color);
        }
    }

    void setBrightness(uint8_t brightness) override {
        LedStrip::setBrightness(brightness);
        _strip.setBrightness(brightness);
        _strip.show();
    }

    void show() override {
        _strip.show();
    }

    uint16_t numPixels() const {
        return _strip.numPixels();
    }

    uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255) const {
        return _strip.ColorHSV(hue, sat, val);
    }

    uint32_t gamma32(uint32_t color) const {
        return _strip.gamma32(color);
    }

private:
    uint16_t _numLeds;
    Adafruit_NeoPixel _strip;
};

#endif // XDUINORAILS_LED_DRIVERS_NEOPIXEL_H
