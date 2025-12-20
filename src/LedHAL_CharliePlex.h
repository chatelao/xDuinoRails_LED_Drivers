/**
 * @file LedHAL_CharliePlex.h
 * @brief Driver for a charlieplexed LED matrix.
 *
 * This file provides the implementation for controlling a matrix of LEDs using the
 * charlieplexing technique, which allows control of N * (N - 1) LEDs with N pins.
 * This driver relies on Persistence of Vision (POV) and requires the `show()`
 * method to be called repeatedly in the main loop.
 */
#ifndef XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H
#define XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H

#include "LedStrip.h"
#include <Arduino.h>

/**
 * @class LedCharliePlex
 * @brief Concrete class for a charlieplexed LED matrix.
 *
 * Implements the LedStrip interface to control a charlieplexed display. It works
 * by rapidly lighting one LED at a time, creating the illusion that multiple LEDs
 * are on simultaneously. The `show()` method must be called continuously in a loop
 * for the display to work correctly. Brightness is simulated by adjusting the
 * duration each LED is turned on.
 */
class LedCharliePlex : public LedStrip {
public:
    /**
     * @brief Constructor for the LedCharliePlex driver.
     * @param pins A pointer to an array of Arduino pin numbers used for the matrix.
     * @param pinCount The number of pins in the array.
     * @param groupId An optional ID for grouping LEDs.
     * @param indexInGroup An optional index within the group.
     */
    LedCharliePlex(const uint8_t* pins, uint8_t pinCount, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : LedStrip(groupId, indexInGroup), _pinCount(pinCount), _numLeds(pinCount * (pinCount - 1)) {
        _pins = new uint8_t[pinCount];
        for (uint8_t i = 0; i < pinCount; i++) {
            _pins[i] = pins[i];
        }
        _ledColors = new RgbColor[_numLeds];
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = {0, 0, 0};
        }
        off();
    }

    /**
     * @brief Destructor that cleans up dynamically allocated memory.
     */
    ~LedCharliePlex() override {
        delete[] _pins;
        delete[] _ledColors;
    }

    /**
     * @brief Turns all LEDs on to white.
     */
    void on() override {
        setColor({255, 255, 255});
        show();
    }

    /**
     * @brief Turns all LEDs off.
     */
    void off() override {
        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = {0, 0, 0};
        }
        show();
    }

    /**
     * @brief Sets the color of all LEDs in the matrix.
     * @param color The RgbColor to set.
     */
    void setColor(const RgbColor& color) override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = color;
        }
        show();
    }

    /**
     * @brief Sets the color of a single LED in the matrix.
     * Does not call `show()`. The change will be visible on the next `show()` call.
     * @param pixelIndex The index of the LED to set.
     * @param color The RgbColor to set.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            _ledColors[pixelIndex] = color;
        }
    }

    /**
     * @brief Sets the overall brightness for the matrix.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        LedStrip::setBrightness(brightness);
    }

    /**
     * @brief Refreshes the display. Call this method in a loop.
     * This method iterates through all the LEDs, quickly lighting each one that is
     * not off. The `_brightness` member controls the `delayMicroseconds` duration,
     * creating a dimming effect.
     */
    void show() override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            const auto& color = _ledColors[i];
            // For single-color charlieplexing, we just care if it's on or off.
            if (color.r > 0 || color.g > 0 || color.b > 0) {
                lightLed(i);
                // Adjust delay based on brightness to control perceived intensity
                delayMicroseconds(_brightness * 10);
            }
        }
        // Set all pins to INPUT to turn off all LEDs after the cycle
        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }
    }

private:
    /**
     * @brief Configures pins to light a single specified LED.
     * It determines the correct anode and cathode pins for the given `ledIndex`,
     * sets all other pins to high-impedance (INPUT), and drives the anode HIGH
     * and the cathode LOW.
     * @param ledIndex The index of the single LED to illuminate.
     */
    void lightLed(uint16_t ledIndex) {
        uint8_t anodePinIndex = 0;
        uint8_t cathodePinIndex = 0;
        uint16_t currentIndex = 0;

        // Set all pins to high-impedance state first
        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }

        // Find the anode/cathode pair for the requested LED index
        for (uint8_t i = 0; i < _pinCount; i++) {
            for (uint8_t j = 0; j < _pinCount; j++) {
                if (i == j) continue; // Skip same-pin pairs

                if (currentIndex == ledIndex) {
                    anodePinIndex = i;
                    cathodePinIndex = j;

                    // Drive the anode HIGH
                    pinMode(_pins[anodePinIndex], OUTPUT);
                    digitalWrite(_pins[anodePinIndex], HIGH);
                    // Drive the cathode LOW
                    pinMode(_pins[cathodePinIndex], OUTPUT);
                    digitalWrite(_pins[cathodePinIndex], LOW);
                    return; // Exit once the correct LED is lit
                }
                currentIndex++;
            }
        }
    }

    uint8_t* _pins;         ///< Pointer to the array of GPIO pins.
    uint8_t _pinCount;      ///< The number of pins used for the matrix.
    uint16_t _numLeds;      ///< The total number of addressable LEDs.
    RgbColor* _ledColors;   ///< Pointer to the array storing the color of each LED.
};

#endif // XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H
