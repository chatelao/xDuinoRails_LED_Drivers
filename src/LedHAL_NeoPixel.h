/**
 * @file LedHAL_NeoPixel.h
 * @brief Driver for NeoPixel (WS2812B) addressable LED strips.
 */
#ifndef XDUINORAILS_LED_DRIVERS_NEOPIXEL_H
#define XDUINORAILS_LED_DRIVERS_NEOPIXEL_H

#include "LedStrip.h"
#include <Adafruit_NeoPixel.h>

/**
 * @class LedNeoPixel
 * @brief Manages a strip of NeoPixel (WS2812B) addressable LEDs.
 *
 * This class is a wrapper around the Adafruit_NeoPixel library, adapting it
 * to the `LedStrip` interface. It provides methods to control the entire strip
 * as a single unit or to set the color of individual pixels. It also exposes
 * some of the underlying library's utility functions like `ColorHSV`.
 */
class LedNeoPixel : public LedStrip {
public:
    /**
     * @brief Constructor for the LedNeoPixel class.
     *
     * @param pin The Arduino pin the NeoPixel strip is connected to.
     * @param numLeds The number of LEDs in the strip.
     * @param groupId The identifier for the group this strip belongs to.
     * @param indexInGroup The index of this strip within its group.
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
     * @brief Sets the color of the entire strip.
     *
     * @param color The RgbColor to set for all pixels.
     */
    void setColor(const RgbColor& color) override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _strip.setPixelColor(i, color.r, color.g, color.b);
        }
        _strip.show();
    }

    /**
     * @brief Sets the color of a single pixel in the strip's buffer.
     *
     * Note: This does not call `show()`. You must call `show()` to see the change.
     * @param pixelIndex The index of the pixel to set.
     * @param color The RgbColor for the pixel.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            _strip.setPixelColor(pixelIndex, color.r, color.g, color.b);
        }
    }

    /**
     * @brief Sets the color of a single pixel using a packed 32-bit color value.
     *
     * This is useful for compatibility with the Adafruit NeoPixel color utility functions.
     * Note: This does not call `show()`. You must call `show()` to see the change.
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
     *
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
        _strip.setBrightness(brightness);
        _strip.show();
    }

    /**
     * @brief Displays the buffered color data on the physical LED strip.
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
     * @brief Converts HSV color values to a 32-bit packed color.
     *
     * @param hue The hue value (0-65535).
     * @param sat The saturation value (0-255).
     * @param val The value (brightness) (0-255).
     * @return The 32-bit packed RGB color.
     */
    uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255) const {
        return _strip.ColorHSV(hue, sat, val);
    }

    /**
     * @brief Applies gamma correction to a 32-bit packed color.
     * @param color The input color.
     * @return The gamma-corrected color.
     */
    uint32_t gamma32(uint32_t color) const {
        return _strip.gamma32(color);
    }

private:
    uint16_t _numLeds;          ///< The number of LEDs in the strip.
    Adafruit_NeoPixel _strip;   ///< The underlying Adafruit_NeoPixel object.
};

#endif // XDUINORAILS_LED_DRIVERS_NEOPIXEL_H
