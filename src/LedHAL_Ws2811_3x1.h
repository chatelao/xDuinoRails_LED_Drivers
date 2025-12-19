/**
 * @file LedHAL_Ws2811_3x1.h
 * @brief Driver for single-color LEDs controlled by a WS2811-type driver IC.
 */
#ifndef XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
#define XDUINORAILS_LED_DRIVERS_WS2811_3X1_H

#include "LedStrip.h"
#include <Adafruit_NeoPixel.h>

/**
 * @class LedWs2811_3x1
 * @brief Manages single-color LEDs connected to a WS2811-style addressable driver.
 *
 * This class uses an RGB addressable LED library (Adafruit_NeoPixel) to control
 * single-color LEDs. It works by converting any incoming RGB color to a single
 * luminance (brightness) value and then sending that same value to all three
 * (R, G, B) channels of the driver IC. This makes it possible to control
 * individual single-color LEDs as if they were pixels in an addressable strip.
 */
class LedWs2811_3x1 : public LedStrip {
public:
    /**
     * @brief Constructor for the LedWs2811_3x1 class.
     *
     * @param pin The Arduino pin the driver IC is connected to.
     * @param numLeds The number of single-color LEDs (pixels) to control.
     * @param groupId The identifier for the group this strip belongs to.
     * @param indexInGroup The index of this strip within its group.
     */
    LedWs2811_3x1(uint8_t pin, uint16_t numLeds, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : LedStrip(groupId, indexInGroup), _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
        _strip.begin();
        off();
    }

    /**
     * @brief Turns all LEDs on to maximum brightness.
     */
    void on() override {
        setColor({255, 255, 255});
    }

    /**
     * @brief Turns all LEDs off.
     */
    void off() override {
        setColor({0, 0, 0});
    }

    /**
     * @brief Sets the brightness of all LEDs based on an RgbColor.
     *
     * A luminance value is calculated from the input color, and all LEDs are set to this brightness.
     * @param color The RgbColor to derive brightness from.
     */
    void setColor(const RgbColor& color) override {
        uint8_t brightness = (uint8_t)(((uint16_t)color.r * 77 + (uint16_t)color.g * 150 + (uint16_t)color.b * 29) >> 8);
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, brightness, brightness, brightness);
        }
        show();
    }

    /**
     * @brief Sets the brightness of a single LED based on an RgbColor.
     *
     * A luminance value is calculated from the input color, and the specified LED is set to this brightness.
     * @param pixelIndex The index of the LED to set.
     * @param color The RgbColor to derive brightness from.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            uint8_t brightness = (uint8_t)(((uint16_t)color.r * 77 + (uint16_t)color.g * 150 + (uint16_t)color.b * 29) >> 8);
            _strip.setPixelColor(pixelIndex, brightness, brightness, brightness);
            show();
        }
    }

    /**
     * @brief Sets all LEDs to a specific brightness level.
     *
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, _brightness, _brightness, _brightness);
        }
        _strip.show();
    }

    /**
     * @brief Displays the buffered data on the physical LEDs.
     */
    void show() override {
        _strip.show();
    }

    /**
     * @brief Gets the number of LEDs (pixels).
     * @return The number of LEDs.
     */
    uint16_t numPixels() const {
        return _strip.numPixels();
    }

private:
    uint16_t _numLeds;          ///< The number of LEDs being controlled.
    Adafruit_NeoPixel _strip;   ///< The underlying Adafruit_NeoPixel object.
};

#endif // XDUINORAILS_LED_DRIVERS_WS2811_3X1_H
