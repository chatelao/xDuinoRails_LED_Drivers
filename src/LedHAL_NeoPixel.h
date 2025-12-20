/**
 * @file LedHAL_NeoPixel.h
 * @brief Driver for Adafruit NeoPixel (WS2812B) addressable LED strips.
 *
 * This file provides a wrapper around the Adafruit_NeoPixel library to integrate
 * it with the LedDriverHAL framework.
 */
#ifndef XDUINORAILS_LED_DRIVERS_NEOPIXEL_H
#define XDUINORAILS_LED_DRIVERS_NEOPIXEL_H

#include "LedStrip.h"
#include <Adafruit_NeoPixel.h>

/**
 * @class LedNeoPixel
 * @brief Concrete class for controlling Adafruit NeoPixel strips.
 *
 * This class inherits from LedStrip and acts as a bridge to the Adafruit_NeoPixel
 * library. It allows NeoPixel strips to be treated like any other Led object in
 * the HAL, while also exposing some useful NeoPixel-specific utility functions.
 */
class LedNeoPixel : public LedStrip {
public:
    /**
     * @brief Constructor for the LedNeoPixel driver.
     * @param pin The Arduino pin connected to the NeoPixel data line.
     * @param numLeds The number of pixels in the strip.
     * @param groupId An optional ID for grouping LEDs.
     * @param indexInGroup An optional index within the group.
     */
    LedNeoPixel(uint8_t pin, uint16_t numLeds, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : LedStrip(groupId, indexInGroup), _numLeds(numLeds), _strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
        _strip.begin();
        off();
    }

    /**
     * @brief Turns the entire strip on to full white.
     */
    void on() override {
        setColor({255, 255, 255});
    }

    /**
     * @brief Turns the entire strip off (sets all pixels to black).
     */
    void off() override {
        setColor({0, 0, 0});
    }

    /**
     * @brief Sets the color of the entire strip to a single color.
     * @param color The RgbColor to set.
     */
    void setColor(const RgbColor& color) override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, color.r, color.g, color.b);
        }
        _strip.show();
    }

    /**
     * @brief Sets the color of an individual pixel.
     * Does not call `show()`. You must call `show()` separately to see the change.
     * @param pixelIndex The index of the pixel to set.
     * @param color The RgbColor to set.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            _strip.setPixelColor(pixelIndex, color.r, color.g, color.b);
        }
    }

    /**
     * @brief Sets the color of an individual pixel using a packed 32-bit color value.
     * Useful for compatibility with Adafruit_NeoPixel color utility functions.
     * Does not call `show()`.
     * @param pixelIndex The index of the pixel to set.
     * @param color The 32-bit packed color value (e.g., from `ColorHSV`).
     */
    void setColor(uint16_t pixelIndex, uint32_t color) {
        if (pixelIndex < _numLeds) {
            _strip.setPixelColor(pixelIndex, color);
        }
    }

    /**
     * @brief Sets the brightness of the entire strip.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        LedStrip::setBrightness(brightness);
        _strip.setBrightness(brightness);
        _strip.show();
    }

    /**
     * @brief Pushes the current color data to the physical LED strip.
     */
    void show() override {
        _strip.show();
    }

    /**
     * @brief Gets the number of pixels in the strip.
     * @return The number of pixels.
     */
    uint16_t numPixels() const {
        return _strip.numPixels();
    }

    /**
     * @brief Converts HSV color to a 32-bit packed RGB color.
     * A pass-through to the Adafruit_NeoPixel library function.
     * @param hue The hue value (0-65535).
     * @param sat The saturation value (0-255).
     * @param val The value (brightness) (0-255).
     * @return A 32-bit packed RGB color value.
     */
    uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255) const {
        return _strip.ColorHSV(hue, sat, val);
    }

    /**
     * @brief Applies gamma correction to a 32-bit packed color.
     * A pass-through to the Adafruit_NeoPixel library function.
     * @param color The 32-bit color to correct.
     * @return The gamma-corrected 32-bit color.
     */
    uint32_t gamma32(uint32_t color) const {
        return _strip.gamma32(color);
    }

private:
    uint16_t _numLeds;          ///< The number of LEDs in the strip.
    Adafruit_NeoPixel _strip;   ///< The underlying Adafruit_NeoPixel object.
};

#endif // XDUINORAILS_LED_DRIVERS_NEOPIXEL_H
