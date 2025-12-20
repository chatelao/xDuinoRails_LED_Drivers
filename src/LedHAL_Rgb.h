/**
 * @file LedHAL_Rgb.h
 * @brief Driver for a standard 3-pin RGB LED.
 *
 * This file provides the implementation for controlling a common anode or common
 * cathode RGB LED using PWM pins.
 */
#ifndef XDUINORAILS_LED_DRIVERS_RGB_H
#define XDUINORAILS_LED_DRIVERS_RGB_H

#include "Led.h"
#include <Arduino.h>

/**
 * @class LedRgb
 * @brief Concrete class for controlling a standard RGB LED.
 *
 * This class implements the Led interface for a 3-pin RGB LED. It uses `analogWrite`
 * on the R, G, and B pins to produce a wide range of colors. Brightness is applied
 * by scaling the color values before writing them to the pins.
 */
class LedRgb : public Led {
public:
    /**
     * @enum RgbLedType
     * @brief Defines the wiring configuration of the RGB LED.
     */
    enum RgbLedType {
        ANODE,      ///< Common anode wiring (common pin to VCC).
        CATHODE     ///< Common cathode wiring (common pin to GND).
    };

    /**
     * @brief Constructor for the LedRgb driver.
     * @param pinR The Arduino pin connected to the red element.
     * @param pinG The Arduino pin connected to the green element.
     * @param pinB The Arduino pin connected to the blue element.
     * @param groupId An optional ID for grouping LEDs.
     * @param indexInGroup An optional index within the group.
     * @param type The wiring type of the LED, either ANODE or CATHODE.
     */
    LedRgb(uint8_t pinR, uint8_t pinG, uint8_t pinB, uint8_t groupId = 0, uint16_t indexInGroup = 0, RgbLedType type = ANODE)
        : Led(groupId, indexInGroup), _pinR(pinR), _pinG(pinG), _pinB(pinB), _isAnode(type == ANODE) {
        pinMode(_pinR, OUTPUT);
        pinMode(_pinG, OUTPUT);
        pinMode(_pinB, OUTPUT);
        off();
    }

    /**
     * @brief Turns the LED on to full white at the current brightness.
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
     * The color is scaled by the current brightness setting before being applied.
     * @param color The RgbColor to set.
     */
    void setColor(const RgbColor& color) override {
        _color = color;
        applyColor();
    }

    /**
     * @brief Sets the overall brightness of the LED.
     * This reapplies the current color, scaled by the new brightness level.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        _brightness = brightness;
        applyColor();
    }

private:
    /**
     * @brief Applies the stored color and brightness to the LED pins.
     * This internal method scales the R, G, and B values by the brightness and
     * calls `analogWrite`, inverting the logic for common anode LEDs.
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

    uint8_t _pinR;      ///< GPIO pin for the red element.
    uint8_t _pinG;      ///< GPIO pin for the green element.
    uint8_t _pinB;      ///< GPIO pin for the blue element.
    bool _isAnode;      ///< True if the LED is common anode.
    RgbColor _color;    ///< The currently set color.
};

#endif // XDUINORAILS_LED_DRIVERS_RGB_H
