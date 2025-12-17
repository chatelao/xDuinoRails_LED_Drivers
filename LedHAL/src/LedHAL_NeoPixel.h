#ifndef LED_HAL_NEOPIXEL_H
#define LED_HAL_NEOPIXEL_H

#include "LedHAL.h"
#include <Adafruit_NeoPixel.h>

// Note: This class requires the Adafruit NeoPixel library to be installed.

class LedNeoPixel : public Led {
public:
    LedNeoPixel(uint8_t pin, uint16_t numLeds) : _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
        _strip.begin();
        off();
    }

    void on() override {
        setColor({255, 255, 255});
    }

    void off() override {
        setColor({0, 0, 0});
    }

    // Sets the color of all pixels and calls show() to update the strip.
    void setColor(const RgbColor& color) override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, color.r, color.g, color.b);
        }
        _strip.show();
    }

    // Sets the color of a single pixel. Does NOT call show().
    // Call show() to update the strip.
    void setColor(uint16_t pixelIndex, const RgbColor& color) {
        if (pixelIndex < _numLeds) {
            _strip.setPixelColor(pixelIndex, color.r, color.g, color.b);
        }
    }

    void show() {
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

#endif // LED_HAL_NEOPIXEL_H
