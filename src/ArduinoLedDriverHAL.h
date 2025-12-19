/**
 * @file ArduinoLedDriverHAL.h
 * @brief Concrete implementation of the LedDriverHAL for Arduino environments.
 */
#ifndef ARDUINO_LED_DRIVER_HAL_H
#define ARDUINO_LED_DRIVER_HAL_H

#include <vector>
#include "xDuinoRails_LED-Drivers.h"
#include "LedHAL_Single.h"
#include "LedHAL_Multi.h"
#include "LedHAL_Rgb.h"
#include "LedHAL_NeoPixel.h"
#include "LedHAL_Ws2811_3x1.h"
#include "LedHAL_CharliePlex.h"
#include "LedHAL_Matrix.h"

/**
 * @class ArduinoLedDriverHAL
 * @brief Provides a concrete implementation of the LedDriverHAL for the Arduino platform.
 *
 * This class manages a collection of `Led` objects. It acts as a factory to create
 * different types of LED drivers and provides methods to control them individually or in groups.
 * It is responsible for the lifecycle of the `Led` objects it creates.
 */
class ArduinoLedDriverHAL : public LedDriverHAL {
public:
    /**
     * @brief Destructor. Cleans up all created Led objects.
     */
    ~ArduinoLedDriverHAL() override {
        for (Led* led : _leds) {
            delete led;
        }
        _leds.clear();
    }

    /**
     * @brief Factory method to create and add a new LED driver.
     *
     * Instantiates the appropriate `Led` subclass based on the `type` parameter and adds it to the internal list.
     * The parameters `pins`, `pinCount`, and `numLeds` are interpreted differently based on the driver type.
     *
     * @param type The type of LED driver to create (from the LedType enum).
     * @param pins An array of pin numbers.
     * @param pinCount The number of pins in the `pins` array.
     * @param numLeds The number of LEDs. Its meaning varies by driver type (e.g., number of pixels in a strip, number of rows in a matrix).
     * @param groupId A group identifier for the new LED driver.
     * @return A pointer to the newly created Led object, or nullptr if creation failed.
     */
    Led* addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0, uint8_t groupId = 0) override {
        uint16_t indexInGroup = 0;
        for (const auto& led : _leds) {
            if (led->getGroupId() == groupId) {
                indexInGroup++;
            }
        }

        Led* newLed = nullptr;
        switch (type) {
            case SINGLE_LED:
                if (pinCount >= 1) {
                    newLed = new LedSingle(pins[0], groupId, indexInGroup);
                }
                break;
            case MULTI_LED:
                if (pinCount > 1) {
                    newLed = new LedMulti(pins, pinCount, groupId, indexInGroup);
                }
                break;
            case RGB_LED:
                if (pinCount >= 3) {
                    newLed = new LedRgb(pins[0], pins[1], pins[2], groupId, indexInGroup);
                }
                break;
            case NEOPIXEL:
                if (pinCount >= 1 && numLeds > 0) {
                    newLed = new LedNeoPixel(pins[0], numLeds, groupId, indexInGroup);
                }
                break;
            case WS2811_3x1:
                if (pinCount >= 1 && numLeds > 0) {
                    newLed = new LedWs2811_3x1(pins[0], numLeds, groupId, indexInGroup);
                }
                break;
            case CHARLIEPLEX:
                if (pinCount > 1) {
                    newLed = new LedCharliePlex(pins, pinCount, groupId, indexInGroup);
                }
                break;
            case MATRIX:
                if (numLeds > 0 && pinCount >= numLeds) {
                    uint8_t rowCount = numLeds;
                    uint8_t colCount = pinCount - rowCount;
                    if (colCount > 0) {
                        const uint8_t* rowPins = pins;
                        const uint8_t* colPins = pins + rowCount;
                        newLed = new LedMatrix(rowPins, rowCount, colPins, colCount, groupId, indexInGroup);
                    }
                }
                break;
        }

        if (newLed) {
            _leds.push_back(newLed);
        }
        return newLed;
    }

    /**
     * @brief Retrieves a pointer to an Led object by its global creation index.
     *
     * @param globalIndex The index of the LED object in the internal list.
     * @return A pointer to the Led object, or nullptr if the index is out of bounds.
     */
    Led* getLed(uint16_t globalIndex) override {
        if (globalIndex < _leds.size()) {
            return _leds[globalIndex];
        }
        return nullptr;
    }

    /**
     * @brief Sets the color for all LEDs in a specified group.
     *
     * Iterates through all managed `Led` objects and calls `setColor` on those matching the `groupId`.
     *
     * @param groupId The identifier of the group to modify.
     * @param color The RgbColor to set.
     */
    void setGroupColor(uint8_t groupId, const RgbColor& color) override {
        for (Led* led : _leds) {
            if (led->getGroupId() == groupId) {
                led->setColor(color);
            }
        }
    }

    /**
     * @brief Sets the brightness for all LEDs in a specified group.
     *
     * Iterates through all managed `Led` objects and calls `setBrightness` on those matching the `groupId`.
     *
     * @param groupId The identifier of the group to modify.
     * @param brightness The brightness level (0-255).
     */
    void setGroupBrightness(uint8_t groupId, uint8_t brightness) override {
        for (Led* led : _leds) {
            if (led->getGroupId() == groupId) {
                led->setBrightness(brightness);
            }
        }
    }

private:
    std::vector<Led*> _leds; ///< A vector storing pointers to all created Led objects.
};

#endif // ARDUINO_LED_DRIVER_HAL_H
