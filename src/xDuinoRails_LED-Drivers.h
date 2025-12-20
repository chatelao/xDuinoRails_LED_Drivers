/**
 * @file xDuinoRails_LED-Drivers.h
 * @brief Main header file for the xDuinoRails_LED-Drivers library.
 *
 * This file defines the main Hardware Abstraction Layer (HAL) interface for creating
 * and managing various types of LEDs. It includes the LedType enum for specifying
 * the LED driver to be used and the LedDriverHAL abstract class which defines the
 * core factory and control methods.
 */
#ifndef XDUINORAILS_LED_DRIVERS_H
#define XDUINORAILS_LED_DRIVERS_H

#include "Led.h"

/**
 * @enum LedType
 * @brief Defines the types of LED drivers supported by the library.
 *
 * This enumeration is used by the LedDriverHAL factory method to determine which
 * concrete Led driver class to instantiate.
 */
enum LedType {
    SINGLE_LED,     ///< For controlling a single, single-color LED. @see LedSingle
    MULTI_LED,      ///< For controlling a group of single-color LEDs as one unit. @see LedMulti
    RGB_LED,        ///< For controlling a standard RGB LED (common anode or cathode). @see LedRgb
    NEOPIXEL,       ///< For controlling Adafruit NeoPixel (WS2812B) addressable LED strips. @see LedNeoPixel
    WS2811_3x1,     ///< For a WS2811 IC driving three individual single-color LEDs. @see LedWs2811_3x1
    CHARLIEPLEX,    ///< For a charlieplexed matrix of LEDs. @see LedCharliePlex
    MATRIX          ///< For a row/column scanned LED matrix. @see LedMatrix
};

/**
 * @class LedDriverHAL
 * @brief Hardware Abstraction Layer for LED driver management.
 *
 * This abstract class defines the factory interface for creating and managing Led objects.
 * It provides a standardized way to add different types of LEDs to a project and to
 * control them, including group operations. Concrete implementations of this class
 * handle the specific hardware interactions.
 */
class LedDriverHAL {
public:
    /**
     * @brief Virtual destructor for the HAL.
     */
    virtual ~LedDriverHAL() {}

    /**
     * @brief Factory method to create and add a new LED driver instance.
     *
     * This pure virtual function is implemented by concrete HAL classes to instantiate
     * the correct Led object based on the provided LedType.
     *
     * @param type The type of LED driver to create, from the LedType enum.
     * @param pins An array of pin numbers required by the driver. The order and meaning
     *             of pins is specific to each driver.
     * @param pinCount The number of elements in the pins array.
     * @param numLeds For drivers that control multiple LEDs (like strips or matrices),
     *                this specifies the number of LEDs. For others, it can be omitted.
     * @param groupId An optional identifier to group multiple Led objects for simultaneous control.
     * @return A pointer to the newly created Led object. The HAL retains ownership.
     */
    virtual Led* addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0, uint8_t groupId = 0) = 0;

    /**
     * @brief Retrieves a pointer to a specific LED driver by its global index.
     *
     * @param globalIndex The zero-based index of the LED driver to retrieve.
     * @return A pointer to the Led object, or nullptr if the index is out of bounds.
     */
    virtual Led* getLed(uint16_t globalIndex) = 0;

    /**
     * @brief Sets the color for all LED drivers within a specified group.
     *
     * @param groupId The ID of the group to control.
     * @param color The RgbColor to set.
     */
    virtual void setGroupColor(uint8_t groupId, const RgbColor& color) = 0;

    /**
     * @brief Sets the brightness for all LED drivers within a specified group.
     *
     * @param groupId The ID of the group to control.
     * @param brightness The brightness level (0-255).
     */
    virtual void setGroupBrightness(uint8_t groupId, uint8_t brightness) = 0;
};

#endif // XDUINORAILS_LED_DRIVERS_H
