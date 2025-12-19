/**
 * @file LedHAL_Rgb.h
 * @brief Driver for a standard RGB LED.
 */
#ifndef XDUINORAILS_LED_DRIVERS_RGB_H
#define XDUINORAILS_LED_DRIVERS_RGB_H

#include "Led.h"
#include <Arduino.h>

/**
 * @class LedRgb
 * @brief Manages a standard RGB LED with separate pins for Red, Green, and Blue.
 *
 * This class controls a common anode or common cathode RGB LED. It allows setting
 * a specific color, which is then scaled by the overall brightness setting.
 */
class LedRgb : public Led {
public:
    /**
     * @enum RgbLedType
     * @brief Defines the wiring configuration of the RGB LED.
     */
    enum RgbLedType { ANODE, CATHODE };

    /**
     * @brief Constructor for the LedRgb class.
     *
     * @param pinR The Arduino pin for the Red component.
     * @param pinG The Arduino pin for the Green component.
     * @param pinB The Arduino pin for the Blue component.
     * @param groupId The identifier for the group this LED belongs to.
     * @param indexInGroup The index of this LED within its group.
     * @param type The type of the LED (ANODE or CATHODE).
     */
    LedRgb(uint8_t pinR, uint8_t pinG, uint8_t pinB, uint8_t groupId = 0, uint16_t indexInGroup = 0, RgbLedType type = ANODE)
        : Led(groupId, indexInGroup), _pinR(pinR), _pinG(pinG), _pinB(pinB), _isAnode(type == ANODE) {
        pinMode(_pinR, OUTPUT);
        pinMode(_pinG, OUTPUT);
        pinMode(_pinB, OUTPUT);
        off();
    }

    /**
     * @brief Turns the LED on to full white.
     */
    void on() override {
        setColor({255, 255, 255});
    }

    /**
     * @brief Turns the LED off (sets color to black).
     */
    void off() override {
        setColor({0, 0, 0});
    }

    /**
     * @brief Sets the color of the LED.
     *
     * The color is stored and then displayed by calling `applyColor()`.
     * @param color The RgbColor to set.
     */
    void setColor(const RgbColor& color) override {
        _color = color;
        applyColor();
    }

    /**
     * @brief Sets the overall brightness of the LED.
     *
     * The new brightness is applied to the currently stored color.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
        applyColor();
    }

private:
    /**
     * @brief Applies the stored color and brightness to the LED pins.
     *
     * This method scales the R, G, and B values of the stored color by the
     * overall brightness and then drives the pins using `analogWrite`.
     * It handles the logic for both common anode and common cathode LEDs.
     */
    void applyColor() {
        uint8_t r = map(_color.r, 0, 255, 0, _brightness);
        uint8_t g = map(_color.g, 0, 255, 0, _brightness);
        uint8_t b = map(_color.b, 0, 255, 0, _brightness);

        if (_isAnode) {
            analogWrite(_pinR, 255 - r);
            analogWrite(_pinG, 255 - g);
            analogWrite(_pinB, 255 - b);
        } else {
            analogWrite(_pinR, r);
            analogWrite(_pinG, g);
            analogWrite(_pinB, b);
        }
    }

    uint8_t _pinR;      ///< Pin for the Red component.
    uint8_t _pinG;      ///< Pin for the Green component.
    uint8_t _pinB;      ///< Pin for the Blue component.
    bool _isAnode;      ///< True for common anode, false for common cathode.
    RgbColor _color;    ///< The currently set color.
};

#endif // XDUINORAILS_LED_DRIVERS_RGB_H
