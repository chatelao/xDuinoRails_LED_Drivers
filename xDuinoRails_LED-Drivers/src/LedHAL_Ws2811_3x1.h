#ifndef XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
#define XDUINORAILS_LED_DRIVERS_WS2811_3X1_H

#include "xDuinoRails_LED-Drivers.h"
#include <Adafruit_NeoPixel.h>

// Note: This class requires the Adafruit NeoPixel library to be installed.

class LedWs2811_3x1 : public Led {
public:
    LedWs2811_3x1(uint8_t pin, uint16_t numLeds) : _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
        _strip.begin();
        off();
    }

    void on() override {
        setColor({255, 255, 255});
    }

    void off() override {
        setColor({0, 0, 0});
    }

    // Sets the brightness of all LEDs on the strip to a single value
    // derived from the luminance of the input color.
    void setColor(const RgbColor& color) override {
        // Calculate a single brightness value from the RGB color.
        // Using a common luminance formula with integer math (coefficients scaled to sum to 256).
        uint8_t brightness = (uint8_t)(((uint16_t)color.r * 77 + (uint16_t)color.g * 150 + (uint16_t)color.b * 29) >> 8);

        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, brightness, brightness, brightness);
        }
        _strip.show();
    }

    // Sets the brightness of a single LED. Does NOT call show().
    // Call show() to update the strip.
    void setPixel(uint16_t index, uint8_t brightness) {
        if (index < _numLeds) {
            _strip.setPixelColor(index, brightness, brightness, brightness);
        }
    }

    void show() {
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
