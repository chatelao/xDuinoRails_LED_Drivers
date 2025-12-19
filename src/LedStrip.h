#ifndef XDUINORAILS_LED_STRIP_H
#define XDUINORAILS_LED_STRIP_H

#include "Led.h"

class LedStrip : public Led {
public:
    using Led::Led; // Inherit constructors

    virtual void setPixelColor(uint16_t pixelIndex, const RgbColor& color) = 0;
    virtual void show() = 0;

    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
    }
};

#endif // XDUINORAILS_LED_STRIP_H
