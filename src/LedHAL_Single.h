/**
 * @file LedHAL_Single.h
 * @brief Driver for a single, single-color LED.
 *
 * This file provides the implementation for controlling a standard single-color LED
 * connected to a digital/PWM pin.
 */
#ifndef XDUINORAILS_LED_DRIVERS_SINGLE_H
#define XDUINORAILS_LED_DRIVERS_SINGLE_H

#include "Led.h"
#include <Arduino.h>

/**
 * @class LedSingle
 * @brief Concrete class for controlling a single-color LED.
 *
 * This class implements the Led interface to control a single LED. It uses
 * `digitalWrite` to turn the LED on/off and `analogWrite` (PWM) to control its
 * brightness. It supports both common anode and common cathode wiring.
 */
class LedSingle : public Led {
public:
    /**
     * @brief Constructor for the LedSingle driver.
     * @param pin The Arduino pin the LED is connected to.
     * @param groupId An optional ID for grouping LEDs.
     * @param indexInGroup An optional index within the group.
     * @param isAnode Set to true for common anode (pin HIGH for on), false for common cathode (pin LOW for on).
     */
    LedSingle(uint8_t pin, uint8_t groupId = 0, uint16_t indexInGroup = 0, bool isAnode = true)
        : Led(groupId, indexInGroup), _pin(pin), _isAnode(isAnode) {
        pinMode(_pin, OUTPUT);
        off();
    }

    /**
     * @brief Turns the LED on to the currently set brightness.
     * Uses `analogWrite` to control the LED's brightness via PWM.
     */
    void on() override {
        if (_isAnode) {
            analogWrite(_pin, _brightness);
        } else {
            analogWrite(_pin, 255 - _brightness);
        }
    }

    /**
     * @brief Turns the LED off.
     */
    void off() override {
        digitalWrite(_pin, _isAnode ? LOW : HIGH);
    }

    /**
     * @brief Sets the LED's brightness based on the luminance of an RGB color.
     * The average of the R, G, and B components is calculated and used to set
     * the brightness.
     * @param color The RgbColor to use for brightness calculation.
     */
    void setColor(const RgbColor& color) override {
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        setBrightness(brightness);
    }

    /**
     * @brief Sets the brightness of the LED.
     * If the brightness is greater than 0, the LED is turned on. Otherwise, it is
     * turned off.
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
    uint8_t _pin;     ///< The GPIO pin connected to the LED.
    bool _isAnode;    ///< True if the LED is common anode, false for common cathode.
};

#endif // XDUINORAILS_LED_DRIVERS_SINGLE_H
