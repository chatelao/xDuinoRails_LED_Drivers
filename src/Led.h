/**
 * @file Led.h
 * @brief Defines the base class for all LED drivers and the RgbColor struct.
 */
#ifndef XDUINORAILS_LED_H
#define XDUINORAILS_LED_H

#include <stdint.h>

/**
 * @struct RgbColor
 * @brief Represents an RGB color with 8-bit values for red, green, and blue.
 */
struct RgbColor {
    uint8_t r; ///< Red component (0-255)
    uint8_t g; ///< Green component (0-255)
    uint8_t b; ///< Blue component (0-255)
};

/**
 * @class Led
 * @brief Abstract base class for all LED drivers in the library.
 *
 * This class provides a common interface for controlling LEDs, including turning them on/off,
 * setting their color, and adjusting their brightness. It also manages group and index information.
 */
class Led {
public:
    /**
     * @brief Constructor for the Led class.
     * @param groupId The identifier for the group this LED belongs to.
     * @param indexInGroup The index of this LED within its group.
     */
    Led(uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : _groupId(groupId), _indexInGroup(indexInGroup), _brightness(255) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~Led() {}

    /**
     * @brief Pure virtual function to turn the LED on.
     * Typically sets the LED to its maximum brightness or a default color.
     */
    virtual void on() = 0;

    /**
     * @brief Pure virtual function to turn the LED off.
     */
    virtual void off() = 0;

    /**
     * @brief Pure virtual function to set the color of the LED.
     * @param color The RgbColor to set.
     */
    virtual void setColor(const RgbColor& color) = 0;

    /**
     * @brief Sets the brightness of the LED.
     * @param brightness The brightness level (0-255).
     */
    virtual void setBrightness(uint8_t brightness) {
        _brightness = brightness;
    }

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
    uint8_t _groupId;       ///< Identifier for the group this LED belongs to.
    uint16_t _indexInGroup; ///< Index of this LED within its group.
    uint8_t _brightness;    ///< Brightness level of the LED (0-255).
};

#endif // XDUINORAILS_LED_H
