/**
 * @file LedHAL_Single.h
 * @brief Driver for a single, single-color LED.
 */
#ifndef XDUINORAILS_LED_DRIVERS_SINGLE_H
#define XDUINORAILS_LED_DRIVERS_SINGLE_H

#include "Led.h"
#include <Arduino.h>

/**
 * @class LedSingle
 * @brief Manages a single-color LED connected to a single digital/PWM pin.
 *
 * This class provides basic control over a single LED, including turning it on/off
 * and setting its brightness using `analogWrite`. It supports both common anode
 * and common cathode wiring configurations.
 */
class LedSingle : public Led {
public:
    /**
     * @brief Constructor for the LedSingle class.
     *
     * @param pin The Arduino pin the LED is connected to.
     * @param groupId The identifier for the group this LED belongs to.
     * @param indexInGroup The index of this LED within its group.
     * @param isAnode Set to true if the LED is common anode, false for common cathode.
     */
    LedSingle(uint8_t pin, uint8_t groupId = 0, uint16_t indexInGroup = 0, bool isAnode = true)
        : Led(groupId, indexInGroup), _pin(pin), _isAnode(isAnode) {
        pinMode(_pin, OUTPUT);
        off();
    }

    /**
     * @brief Turns the LED on to the currently set brightness.
     *
     * The `analogWrite` value is adjusted based on whether the LED is common anode or cathode.
     */
    void on() override {
        if (_isAnode) {
            analogWrite(_pin, _brightness);
        } else {
            analogWrite(_pin, 255 - _brightness);
        }
    }

    /**
     * @brief Turns the LED off completely.
     */
    void off() override {
        digitalWrite(_pin, _isAnode ? LOW : HIGH);
    }

    /**
     * @brief Sets the LED's brightness based on an RgbColor.
     *
     * The brightness is calculated as the average of the R, G, and B components of the color.
     * @param color The RgbColor to use for brightness calculation.
     */
    void setColor(const RgbColor& color) override {
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        setBrightness(brightness);
    }

    /**
     * @brief Sets the brightness of the LED and applies it immediately.
     *
     * If brightness is greater than 0, `on()` is called. Otherwise, `off()` is called.
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
    uint8_t _pin;    ///< The pin the LED is connected to.
    bool _isAnode;   ///< True for common anode, false for common cathode.
};

#endif // XDUINORAILS_LED_DRIVERS_SINGLE_H
