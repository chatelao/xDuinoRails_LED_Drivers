/**
 * @file LedStrip.h
 * @brief Defines the abstract base class for addressable LED strips.
 */
#ifndef XDUINORAILS_LED_STRIP_H
#define XDUINORAILS_LED_STRIP_H

#include "Led.h"

/**
 * @class LedStrip
 * @brief Abstract base class for addressable LED strips.
 *
 * This class extends the `Led` base class to provide a common interface for
 * addressable LED strips that have individually controllable pixels.
 * It introduces methods for setting the color of a specific pixel and for
 * updating the physical strip to show the set colors.
 */
class LedStrip : public Led {
public:
    /**
     * @brief Inherit constructors from the Led base class.
     */
    using Led::Led;

    /**
     * @brief Pure virtual function to set the color of a specific pixel.
     *
     * This function sets the color of a single pixel in an internal buffer.
     * The change is not visible on the strip until `show()` is called.
     *
     * @param pixelIndex The index of the pixel to set (0-based).
     * @param color The RgbColor to set for the pixel.
     */
    virtual void setPixelColor(uint16_t pixelIndex, const RgbColor& color) = 0;

    /**
     * @brief Pure virtual function to display the buffered color data on the LED strip.
     *
     * This function sends the color data from the internal buffer to the physical LED strip,
     * making the changes set by `setPixelColor` visible.
     */
    virtual void show() = 0;
};

#endif // XDUINORAILS_LED_STRIP_H
