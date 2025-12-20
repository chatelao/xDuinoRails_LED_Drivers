/**
 * @file LedStrip.h
 * @brief Defines the base interface for addressable LED strip drivers.
 *
 * This file contains the LedStrip abstract class, which extends the base Led class
 * with functionality specific to addressable LED strips, such as setting individual
 * pixel colors and pushing the color data to the hardware.
 */
#ifndef XDUINORAILS_LED_STRIP_H
#define XDUINORAILS_LED_STRIP_H

#include "Led.h"

/**
 * @class LedStrip
 * @brief Abstract base class for addressable LED strip drivers.
 *
 * This class inherits from the Led class and provides a common interface for
 * drivers that control addressable LED strips (e.g., NeoPixel, WS2811). It
 * introduces methods to set the color of individual pixels and a `show()` method
 * to update the physical strip with the new color data.
 */
class LedStrip : public Led {
public:
    /**
     * @brief Inherits constructors from the Led base class.
     */
    using Led::Led;

    /**
     * @brief Sets the color of a single pixel on the strip.
     *
     * This pure virtual function must be implemented by concrete strip drivers to set
     * the color of a specific pixel in their internal buffer. The change is not sent
     * to the hardware until `show()` is called.
     *
     * @param pixelIndex The zero-based index of the pixel to set.
     * @param color The RgbColor to set the pixel to.
     */
    virtual void setPixelColor(uint16_t pixelIndex, const RgbColor& color) = 0;

    /**
     * @brief Pushes the current color data to the physical LED strip.
     *
     * This pure virtual function is responsible for transmitting the color data from
     * the driver's internal buffer to the hardware, making the color changes visible.
     */
    virtual void show() = 0;

    /**
     * @brief Sets the overall brightness for the entire strip.
     *
     * This method overrides the base class `setBrightness` to store the brightness
     * value. Concrete implementations should use this value to scale pixel colors
     * before sending them to the strip in their `show()` method.
     *
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
    }
};

#endif // XDUINORAILS_LED_STRIP_H
