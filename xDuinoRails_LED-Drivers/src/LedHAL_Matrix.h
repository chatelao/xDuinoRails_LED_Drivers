#ifndef XDUINORAILS_LED_DRIVERS_MATRIX_H
#define XDUINORAILS_LED_DRIVERS_MATRIX_H

#include "xDuinoRails_LED-Drivers.h"
#include <Adafruit_NeoPixel.h>

class LedMatrix : public Led {
public:
    LedMatrix(uint8_t pin, uint8_t width, uint8_t height)
        : _width(width), _height(height), _strip(width * height, pin, NEO_GRB + NEO_KHZ800) {
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
        for (uint16_t i = 0; i < _strip.numPixels(); i++) {
            _strip.setPixelColor(i, color.r, color.g, color.b);
        }
        _strip.show();
    }

    void setColor(uint8_t x, uint8_t y, const RgbColor& color) {
        if (x < _width && y < _height) {
            _strip.setPixelColor(y * _width + x, color.r, color.g, color.b);
        }
    }

    void show() {
        _strip.show();
    }

private:
    uint8_t _width;
    uint8_t _height;
    Adafruit_NeoPixel _strip;
};

#endif // XDUINORAILS_LED_DRIVERS_MATRIX_H
