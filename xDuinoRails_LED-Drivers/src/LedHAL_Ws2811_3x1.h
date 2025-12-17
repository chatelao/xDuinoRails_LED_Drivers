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

    // Sets the brightness of the three LEDs connected to each WS2811 IC.
    // The r, g, and b components of the RgbColor struct are used to set the
    // brightness of the first, second, and third LED, respectively.
    void setColor(const RgbColor& color) override {
        uint16_t num_groups = _numLeds / 3;
        for (uint16_t i = 0; i < num_groups; i++) {
            _strip.setPixelColor(i * 3, _strip.Color(color.r, 0, 0));
            _strip.setPixelColor(i * 3 + 1, _strip.Color(0, color.g, 0));
            _strip.setPixelColor(i * 3 + 2, _strip.Color(0, 0, color.b));
        }

        // Turn off any remaining LEDs that don't form a full group of 3
        uint16_t remainder_start_index = num_groups * 3;
        for (uint16_t i = remainder_start_index; i < _numLeds; i++) {
            _strip.setPixelColor(i, 0); // set to black
        }

        _strip.show();
    }

    // Sets the color of a single LED. Does NOT call show().
    // Call show() to update the strip.
    void setPixel(uint16_t index, const RgbColor& color) {
        if (index < _numLeds) {
            _strip.setPixelColor(index, color.r, color.g, color.b);
        }
    }

    // Sets the brightness of a single LED. Does NOT call show().
    // This method reads the existing color of the pixel, scales it by the
    // brightness value, and then sets the new color.
    // Call show() to update the strip.
    void setPixelBrightness(uint16_t index, uint8_t brightness) {
        if (index < _numLeds) {
            uint32_t color = _strip.getPixelColor(index);
            uint8_t r = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t b = color & 0xFF;

            r = (uint8_t)((uint16_t)r * brightness / 255);
            g = (uint8_t)((uint16_t)g * brightness / 255);
            b = (uint8_t)((uint16_t)b * brightness / 255);

            _strip.setPixelColor(index, r, g, b);
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
