/**
 * @file LedHAL_Multi.h
 * @brief Driver for a group of single-color LEDs controlled as a single unit.
 *
 * This file provides the implementation for controlling multiple single-color LEDs
 * simultaneously, treating them as a single logical LED.
 */
#ifndef XDUINORAILS_LED_DRIVERS_MULTI_H
#define XDUINORAILS_LED_DRIVERS_MULTI_H

#include "Led.h"
#include <Arduino.h>

/**
 * @class LedMulti
 * @brief Concrete class for controlling a group of single-color LEDs.
 *
 * This class implements the Led interface to control multiple LEDs connected to
 * different pins as if they were a single entity. All LEDs in the group are set
 * to the same brightness. It supports both common anode and common cathode wiring.
 */
class LedMulti : public Led {
public:
    /**
     * @brief Constructor for the LedMulti driver.
     *
     * Takes ownership of the pins array by creating a local copy.
     *
     * @param pins A pointer to an array of Arduino pin numbers.
     * @param pinCount The number of pins in the array.
     * @param groupId An optional ID for grouping LEDs.
     * @param indexInGroup An optional index within the group.
     * @param isAnode Set to true for common anode (pin HIGH for on), false for common cathode (pin LOW for on).
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
     * @brief Destructor that cleans up the dynamically allocated pins array.
     */
    ~LedMulti() {
        delete[] _pins;
    }

    /**
     * @brief Turns all LEDs in the group on to the currently set brightness.
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
     * @brief Turns all LEDs in the group off.
     */
    void off() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            digitalWrite(_pins[i], _isAnode ? LOW : HIGH);
        }
    }

    /**
     * @brief Sets the brightness of the group based on the luminance of an RGB color.
     * @param color The RgbColor to use for brightness calculation.
     */
    void setColor(const RgbColor& color) override {
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        setBrightness(brightness);
    }

    /**
     * @brief Sets the brightness for all LEDs in the group.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
        if (brightness > 0) {
            on();
        } else {
            off();
        }
    }

private:
    uint8_t* _pins;     ///< Pointer to the dynamically allocated array of GPIO pins.
    uint8_t _pinCount;  ///< The number of pins in the `_pins` array.
    bool _isAnode;      ///< True if the LEDs are common anode, false for common cathode.
};

#endif // XDUINORAILS_LED_DRIVERS_MULTI_H
