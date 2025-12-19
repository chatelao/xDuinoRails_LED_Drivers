/**
 * @file xDuinoRails_LED-Drivers.h
 * @brief Main header file for the xDuinoRails_LED-Drivers library.
 *
 * This file defines the main abstract class `LedDriverHAL` for the LED driver Hardware Abstraction Layer (HAL).
 * It provides a unified interface to control various types of LEDs.
 */
#ifndef XDUINORAILS_LED_DRIVERS_H
#define XDUINORAILS_LED_DRIVERS_H

#include "Led.h"

/**
 * @enum LedType
 * @brief Defines the types of LED drivers supported by the library.
 */
enum LedType {
    SINGLE_LED,      ///< A single, single-color LED
    MULTI_LED,       ///< Multiple single-color LEDs controlled as a group
    RGB_LED,         ///< A single RGB LED (common anode or cathode)
    NEOPIXEL,        ///< Addressable RGB LEDs (WS2812B, etc.)
    WS2811_3x1,      ///< A WS2811 chip driving three individual single-color LEDs
    CHARLIEPLEX,     ///< A matrix of LEDs using charlieplexing
    MATRIX           ///< A row/column scanned LED matrix
};

/**
 * @class LedDriverHAL
 * @brief Abstract base class for the LED driver Hardware Abstraction Layer (HAL).
 *
 * This class defines the interface for creating and managing LED driver instances.
 * It follows the factory pattern to instantiate specific LED driver types.
 */
class LedDriverHAL {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~LedDriverHAL() {}

    /**
     * @brief Factory method to create and add a new LED driver.
     *
     * @param type The type of LED driver to create (from the LedType enum).
     * @param pins An array of pin numbers to be used by the driver.
     * @param pinCount The number of pins in the `pins` array.
     * @param numLeds The number of LEDs to be controlled (used by some drivers).
     * @param groupId A group identifier for the created LED driver.
     * @return A pointer to the created Led object.
     */
    virtual Led* addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0, uint8_t groupId = 0) = 0;

    /**
     * @brief Retrieves a pointer to an Led object by its global index.
     *
     * @param globalIndex The global index of the LED to retrieve.
     * @return A pointer to the Led object, or nullptr if not found.
     */
    virtual Led* getLed(uint16_t globalIndex) = 0;

    /**
     * @brief Sets the color for all LEDs in a specified group.
     *
     * @param groupId The identifier of the group to modify.
     * @param color The RgbColor to set.
     */
    virtual void setGroupColor(uint8_t groupId, const RgbColor& color) = 0;

    /**
     * @brief Sets the brightness for all LEDs in a specified group.
     *
     * @param groupId The identifier of the group to modify.
     * @param brightness The brightness level (0-255).
     */
    virtual void setGroupBrightness(uint8_t groupId, uint8_t brightness) = 0;
};

#endif // XDUINORAILS_LED_DRIVERS_H
