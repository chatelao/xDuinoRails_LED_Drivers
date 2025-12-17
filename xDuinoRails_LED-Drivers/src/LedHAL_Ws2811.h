#ifndef XDUINORAILS_LED_DRIVERS_WS2811_H
#define XDUINORAILS_LED_DRIVERS_WS2811_H

#include "xDuinoRails_LED-Drivers.h"
#include <Adafruit_NeoPixel.h>

// Note: This class requires the Adafruit NeoPixel library to be installed.

class LedWs2811 : public Led {
public:
    LedWs2811(uint8_t pin, uint16_t numLeds) : _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
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
        // For single color LEDs, we can use the brightness of the color
        // to set the brightness of the LED.
        // A simple approach is to average the R, G, and B values.
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, _strip.Color(brightness, brightness, brightness));
        }
        _strip.show();
    }

    // Sets the color of a single pixel. Does NOT call show().
    // Call show() to update the strip.
    void setColor(uint16_t pixelIndex, uint8_t brightness) {
        if (pixelIndex < _numLeds) {
            _strip.setPixelColor(pixelIndex, _strip.Color(brightness, brightness, brightness));
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

#endif // XDUINORAILS_LED_DRIVERS_WS2811_H
