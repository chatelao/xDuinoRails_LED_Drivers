/**
 * @file LedHAL_Ws2811_3x1.h
 * @brief Driver for a WS2811 IC controlling three individual single-color LEDs.
 *
 * This file provides an implementation for a specific hardware setup where a WS2811
 * addressable driver IC is used to control three separate single-color LEDs, treating
 * the R, G, and B channels of the WS2811 as three independent brightness controls.
 */
#ifndef XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
#define XDUINORAILS_LED_DRIVERS_WS2811_3X1_H

#include "LedStrip.h"
#include <Adafruit_NeoPixel.h>

/**
 * @class LedWs2811_3x1
 * @brief Concrete class for a WS2811 driving single-color LEDs.
 *
 * This class adapts the RGB-based Adafruit_NeoPixel library to control single-color
 * LEDs. When a color is set, its luminance is calculated and applied equally to the
 * R, G, and B channels of the underlying NeoPixel driver. This effectively treats
 * the WS2811 as a 3-channel PWM driver for three separate LEDs.
 */
class LedWs2811_3x1 : public LedStrip {
public:
    /**
     * @brief Constructor for the LedWs2811_3x1 driver.
     * @param pin The Arduino pin connected to the WS2811 data line.
     * @param numLeds The number of WS2811 ICs (pixels) in the chain.
     * @param groupId An optional ID for grouping LEDs.
     * @param indexInGroup An optional index within the group.
     */
    LedWs2811_3x1(uint8_t pin, uint16_t numLeds, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : LedStrip(groupId, indexInGroup), _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
        _strip.begin();
        off();
    }

    /**
     * @brief Turns all connected LEDs on to maximum brightness.
     */
    void on() override {
        setColor({255, 255, 255});
    }

    /**
     * @brief Turns all connected LEDs off.
     */
    void off() override {
        setColor({0, 0, 0});
    }

    /**
     * @brief Sets the brightness of all LEDs based on an RGB color's luminance.
     * The brightness is applied to all three channels of all WS2811 ICs.
     * @param color The RgbColor to use for brightness calculation.
     */
    void setColor(const RgbColor& color) override {
        uint8_t brightness = (uint8_t)(((uint16_t)color.r * 77 + (uint16_t)color.g * 150 + (uint16_t)color.b * 29) >> 8);
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, brightness, brightness, brightness);
        }
        show();
    }

    /**
     * @brief Sets the brightness of a single WS2811 IC's LEDs.
     * @param pixelIndex The index of the WS2811 IC to control.
     * @param color The RgbColor to use for brightness calculation.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            uint8_t brightness = (uint8_t)(((uint16_t)color.r * 77 + (uint16_t)color.g * 150 + (uint16_t)color.b * 29) >> 8);
            _strip.setPixelColor(pixelIndex, brightness, brightness, brightness);
            show();
        }
    }

    /**
     * @brief Sets the brightness for all LEDs connected to all ICs.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        LedStrip::setBrightness(brightness);
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, _brightness, _brightness, _brightness);
        }
        _strip.show();
    }

    /**
     * @brief Pushes the current color data to the physical WS2811 ICs.
     */
    void show() override {
        _strip.show();
    }

    /**
     * @brief Gets the number of WS2811 ICs (pixels) in the chain.
     * @return The number of pixels.
     */
    uint16_t numPixels() const {
        return _strip.numPixels();
    }

private:
    uint16_t _numLeds;          ///< The number of WS2811 ICs in the chain.
    Adafruit_NeoPixel _strip;   ///< The underlying Adafruit_NeoPixel object.
};

#endif // XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
