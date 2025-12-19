/**
 * @file LedHAL_Multi.h
 * @brief Driver for multiple single-color LEDs controlled as a single unit.
 */
#ifndef XDUINORAILS_LED_DRIVERS_MULTI_H
#define XDUINORAILS_LED_DRIVERS_MULTI_H

#include "Led.h"
#include <Arduino.h>

/**
 * @class LedMulti
 * @brief Manages a group of single-color LEDs, treating them as a single entity.
 *
 * This class controls multiple LEDs connected to different pins, making them all
 * behave identically. They turn on, off, and change brightness together.
 * The class dynamically allocates memory for the pin array and cleans it up in the destructor.
 */
class LedMulti : public Led {
public:
    /**
     * @brief Constructor for the LedMulti class.
     *
     * @param pins A pointer to an array of Arduino pin numbers.
     * @param pinCount The number of pins in the `pins` array.
     * @param groupId The identifier for the group this LED assembly belongs to.
     * @param indexInGroup The index of this LED assembly within its group.
     * @param isAnode Set to true if the LEDs are common anode, false for common cathode.
     */
    LedMulti(const uint8_t* pins, uint8_t pinCount, uint8_t groupId = 0, uint16_t indexInGroup = 0, bool isAnode = true)
        : Led(groupId, indexInGroup), _pinCount(pinCount), _isAnode(isAnode) {
        _pins = new uint8_t[pinCount];
        for (uint8_t i = 0; i < _pinCount; i++) {
            _pins[i] = pins[i];
            pinMode(_pins[i], OUTPUT);
        }
        off();
    }

    /**
     * @brief Destructor. Frees the dynamically allocated memory for the pins.
     */
    ~LedMulti() {
        delete[] _pins;
    }

    /**
     * @brief Turns all LEDs on to the currently set brightness.
     */
    void on() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            if (_isAnode) {
                analogWrite(_pins[i], _brightness);
            } else {
                analogWrite(_pins[i], 255 - _brightness);
            }
        }
    }

    /**
     * @brief Turns all LEDs off completely.
     */
    void off() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            digitalWrite(_pins[i], _isAnode ? LOW : HIGH);
        }
    }

    /**
     * @brief Sets the brightness for all LEDs based on an RgbColor.
     *
     * Brightness is calculated as the average of the R, G, and B components.
     * @param color The RgbColor to use for brightness calculation.
     */
    void setColor(const RgbColor& color) override {
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        setBrightness(brightness);
    }

    /**
     * @brief Sets the brightness of all LEDs and applies it immediately.
     *
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
        if (brightness > 0) {
            on();
        } else {
            off();
        }
    }

private:
    uint8_t* _pins;     ///< Pointer to the dynamically allocated array of pins.
    uint8_t _pinCount;  ///< The number of pins (and LEDs).
    bool _isAnode;      ///< True for common anode, false for common cathode.
};

#endif // XDUINORAILS_LED_DRIVERS_MULTI_H
