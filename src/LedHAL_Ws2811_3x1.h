#ifndef XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
#define XDUINORAILS_LED_DRIVERS_WS2811_3X1_H

#include "xDuinoRails_LED-Drivers.h"
#include <Adafruit_NeoPixel.h>

class LedWs2811_3x1 : public Led {
public:
    LedWs2811_3x1(uint8_t pin, uint16_t numLeds, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : Led(groupId, indexInGroup), _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
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
        setBrightness(brightness);
    }

    void setPixel(uint16_t index, uint8_t brightness) {
        if (index < _numLeds) {
            _strip.setPixelColor(index, brightness, brightness, brightness);
        }
    }

    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
        for (uint16_t i = 0; i < _numLeds; i++) {
            setPixel(i, _brightness);
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
