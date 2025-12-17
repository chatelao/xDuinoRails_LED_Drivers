#ifndef XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
#define XDUINORAILS_LED_DRIVERS_WS2811_3X1_H

#include "xDuinoRails_LED-Drivers.h"
#include <Adafruit_NeoPixel.h>

// Note: This class requires the Adafruit NeoPixel library to be installed.

class LedWs2811_3x1 : public Led {
public:
    LedWs2811_3x1(uint8_t pin, uint16_t numLeds) : _numLeds(numLeds), _strip(numLeds * 3, pin, NEO_GRB + NEO_KHZ800) {
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
            _strip.setPixelColor(i * 3, _strip.Color(color.r, 0, 0));
            _strip.setPixelColor(i * 3 + 1, _strip.Color(0, color.g, 0));
            _strip.setPixelColor(i * 3 + 2, _strip.Color(0, 0, color.b));
        }
        _strip.show();
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
