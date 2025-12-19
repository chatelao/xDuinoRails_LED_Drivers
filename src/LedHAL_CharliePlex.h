/**
 * @file LedHAL_CharliePlex.h
 * @brief Driver for a Charlieplexed LED matrix.
 */
#ifndef XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H
#define XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H

#include "LedStrip.h"
#include <Arduino.h>

/**
 * @class LedCharliePlex
 * @brief Manages a matrix of LEDs using the Charlieplexing technique.
 *
 * This class controls a grid of `N * (N-1)` LEDs using only `N` IO pins.
 * It uses Persistence of Vision (POV) by rapidly lighting one LED at a time.
 * The `show()` method must be called continuously in a loop to maintain the display.
 * Note: This implementation treats single-color LEDs as white (RGB) and does not
 * support individual color control, only on/off status based on the stored color.
 * Brightness is simulated by adjusting the duration each LED is lit.
 */
class LedCharliePlex : public LedStrip {
public:
    /**
     * @brief Constructor for the LedCharliePlex class.
     *
     * @param pins A pointer to an array of Arduino pin numbers.
     * @param pinCount The number of pins (`N`) used for the matrix.
     * @param groupId The identifier for the group this matrix belongs to.
     * @param indexInGroup The index of this matrix within its group.
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
     * @brief Destructor. Frees dynamically allocated memory.
     */
    ~LedCharliePlex() override {
        delete[] _pins;
        delete[] _ledColors;
    }

    /**
     * @brief Turns all LEDs on to full brightness.
     */
    void on() override {
        setColor({255, 255, 255});
        show();
    }

    /**
     * @brief Turns all LEDs off and resets the buffer.
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
     * @brief Sets the state of all LEDs in the matrix.
     *
     * Since this driver is monochrome, any non-black color turns the LEDs on.
     * @param color The RgbColor to set. {0,0,0} for off, anything else for on.
     */
    void setColor(const RgbColor& color) override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            _ledColors[i] = color;
        }
        show();
    }

    /**
     * @brief Sets the state of a single LED in the buffer.
     *
     * Note: This does not call `show()`. The change will be visible on the next call to `show()`.
     * @param pixelIndex The index of the LED to set.
     * @param color The RgbColor to set. {0,0,0} for off, anything else for on.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _numLeds) {
            _ledColors[pixelIndex] = color;
        }
    }

    /**
     * @brief Sets the overall brightness of the matrix.
     *
     * Brightness is simulated by changing the delay in the `show()` method.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
    }

    /**
     * @brief Refreshes the display. This must be called repeatedly in a loop.
     *
     * It iterates through all LEDs, lighting each one that is turned on for a
     * brief period. The duration is controlled by the brightness setting.
     */
    void show() override {
        for (uint16_t i = 0; i < _numLeds; i++) {
            const auto& color = _ledColors[i];
            if (color.r > 0 || color.g > 0 || color.b > 0) {
                lightLed(i);
                delayMicroseconds(_brightness * 10);
            }
        }
        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }
    }

private:
    /**
     * @brief Lights a single specified LED.
     *
     * This method determines the correct anode and cathode pins for the given
     * LED index, sets their modes and states appropriately, and leaves the
     * other pins as high-impedance inputs.
     * @param ledIndex The index of the LED to light up.
     */
    void lightLed(uint16_t ledIndex) {
        uint8_t anodePinIndex = 0;
        uint8_t cathodePinIndex = 0;
        uint16_t currentIndex = 0;

        for (uint8_t i = 0; i < _pinCount; i++) {
            pinMode(_pins[i], INPUT);
        }

        for (uint8_t i = 0; i < _pinCount; i++) {
            for (uint8_t j = 0; j < _pinCount; j++) {
                if (i == j) continue;

                if (currentIndex == ledIndex) {
                    anodePinIndex = i;
                    cathodePinIndex = j;

                    pinMode(_pins[anodePinIndex], OUTPUT);
                    digitalWrite(_pins[anodePinIndex], HIGH);
                    pinMode(_pins[cathodePinIndex], OUTPUT);
                    digitalWrite(_pins[cathodePinIndex], LOW);
                    return;
                }
                currentIndex++;
            }
        }
    }

    uint8_t* _pins;         ///< Dynamically allocated array of pin numbers.
    uint8_t _pinCount;      ///< The number of pins used for the matrix.
    uint16_t _numLeds;      ///< The total number of LEDs in the matrix.
    RgbColor* _ledColors;   ///< Dynamically allocated array storing the state of each LED.
};

#endif // XDUINORAILS_LED_DRIVERS_CHARLIEPLEX_H
