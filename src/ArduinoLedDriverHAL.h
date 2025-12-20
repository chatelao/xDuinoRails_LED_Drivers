/**
 * @file ArduinoLedDriverHAL.h
 * @brief Concrete implementation of the LedDriverHAL for the Arduino framework.
 *
 * This file provides the Arduino-specific implementation of the hardware abstraction
 * layer. It manages the lifecycle of all created Led objects and uses a switch
 * statement to instantiate the correct concrete driver based on the LedType enum.
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
 * @brief Concrete LedDriverHAL implementation for the Arduino platform.
 *
 * This class implements the factory pattern to create and manage various types of
 * LED drivers. It maintains a vector of pointers to all created Led objects and
 * is responsible for their proper deallocation to prevent memory leaks.
 */
class ArduinoLedDriverHAL : public LedDriverHAL {
public:
    /**
     * @brief Destructor that cleans up all allocated Led objects.
     *
     * Iterates through the internal list of LED drivers and deletes each one
     * to free up dynamically allocated memory.
     */
    ~ArduinoLedDriverHAL() override {
        for (Led* led : _leds) {
            delete led;
        }
        _leds.clear();
    }

    /**
     * @brief Factory method to create and add a new LED driver instance.
     *
     * This method instantiates the appropriate concrete Led class based on the
     * `type` parameter and adds the new object to its internal management list.
     * It also calculates the `indexInGroup` for the new LED.
     *
     * @param type The type of LED driver to create (@see LedType).
     * @param pins An array of pin numbers. The required pins vary by driver.
     * @param pinCount The number of elements in the `pins` array.
     * @param numLeds The number of LEDs for strip or matrix drivers.
     * @param groupId An ID for grouping LEDs for simultaneous control.
     * @return A pointer to the newly created Led object. The HAL retains ownership.
     *         Returns `nullptr` if the parameters are invalid for the requested type.
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
     * @brief Retrieves a pointer to a specific LED driver by its global index.
     * @param globalIndex The zero-based index of the LED driver to retrieve.
     * @return A pointer to the Led object, or `nullptr` if the index is out of bounds.
     */
    Led* getLed(uint16_t globalIndex) override {
        if (globalIndex < _leds.size()) {
            return _leds[globalIndex];
        }
        return nullptr;
    }

    /**
     * @brief Sets the color for all LED drivers within a specified group.
     * @param groupId The ID of the group to control.
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
     * @brief Sets the brightness for all LED drivers within a specified group.
     * @param groupId The ID of the group to control.
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
    std::vector<Led*> _leds; ///< A vector to store pointers to all managed Led objects.
};

#endif // ARDUINO_LED_DRIVER_HAL_H
