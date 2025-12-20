/**
 * @file Led.h
 * @brief Defines the base interface for all LED drivers in the library.
 *
 * This file contains the RgbColor struct for color representation and the Led
 * abstract base class, which defines the common interface that all concrete
 * LED driver classes must implement.
 */
#ifndef XDUINORAILS_LED_H
#define XDUINORAILS_LED_H

#include <stdint.h>

/**
 * @struct RgbColor
 * @brief Represents a color in 24-bit RGB format.
 *
 * This structure holds the red, green, and blue components of a color, with each
 * component being an 8-bit unsigned integer (0-255).
 */
struct RgbColor {
    uint8_t r;  ///< Red component (0-255).
    uint8_t g;  ///< Green component (0-255).
    uint8_t b;  ///< Blue component (0-255).
};

/**
 * @class Led
 * @brief Abstract base class for all LED drivers.
 *
 * This class defines the fundamental interface for controlling an LED. It includes
 * pure virtual methods for turning the LED on/off, setting its color, and adjusting
 * its brightness. All specific LED driver classes must inherit from this class and
 * implement these methods.
 */
class Led {
public:
    /**
     * @brief Constructor for the Led base class.
     * @param groupId An optional identifier for grouping LEDs.
     * @param indexInGroup An optional index within the group.
     */
    Led(uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : _groupId(groupId), _indexInGroup(indexInGroup), _brightness(255) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~Led() {}

    /**
     * @brief Turns the LED on.
     * For RGB LEDs, this typically sets the color to white at the current brightness.
     * For single-color LEDs, it sets them to their maximum brightness.
     */
    virtual void on() = 0;

    /**
     * @brief Turns the LED off.
     */
    virtual void off() = 0;

    /**
     * @brief Sets the color of the LED.
     * For single-color LEDs, the color's luminance is typically used to set brightness.
     * @param color The RgbColor to set.
     */
    virtual void setColor(const RgbColor& color) = 0;

    /**
     * @brief Sets the brightness of the LED.
     * @param brightness The brightness level (0-255).
     */
    virtual void setBrightness(uint8_t brightness) = 0;

    /**
     * @brief Gets the group ID of the LED.
     * @return The group ID.
     */
    uint8_t getGroupId() const { return _groupId; }

    /**
     * @brief Gets the index of the LED within its group.
     * @return The index within the group.
     */
    uint16_t getIndexInGroup() const { return _indexInGroup; }

protected:
    uint8_t _groupId;         ///< Identifier for grouping LEDs.
    uint16_t _indexInGroup;   ///< Index of this LED within its group.
    uint8_t _brightness;      ///< Current brightness level (0-255).
};

#endif // XDUINORAILS_LED_H
