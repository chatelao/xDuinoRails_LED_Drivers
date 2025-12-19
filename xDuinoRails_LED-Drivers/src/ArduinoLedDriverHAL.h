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

class ArduinoLedDriverHAL : public LedDriverHAL {
public:
    ~ArduinoLedDriverHAL() override {
        for (Led* led : _leds) {
            delete led;
        }
        _leds.clear();
    }

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

    Led* getLed(uint16_t globalIndex) override {
        if (globalIndex < _leds.size()) {
            return _leds[globalIndex];
        }
        return nullptr;
    }

    void setGroupColor(uint8_t groupId, const RgbColor& color) override {
        for (Led* led : _leds) {
            if (led->getGroupId() == groupId) {
                led->setColor(color);
            }
        }
    }

    void setGroupBrightness(uint8_t groupId, uint8_t brightness) override {
        for (Led* led : _leds) {
            if (led->getGroupId() == groupId) {
                led->setBrightness(brightness);
            }
        }
    }

private:
    std::vector<Led*> _leds;
};

#endif // ARDUINO_LED_DRIVER_HAL_H
