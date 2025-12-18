#ifndef ARDUINO_LED_DRIVER_HAL_H
#define ARDUINO_LED_DRIVER_HAL_H

#include "xDuinoRails_LED-Drivers.h"
#include "LedHAL_Single.h"
#include "LedHAL_Dual.h"
#include "LedHAL_Triple.h"
#include "LedHAL_Rgb.h"
#include "LedHAL_NeoPixel.h"
#include "LedHAL_Ws2811_3x1.h"

class ArduinoLedDriverHAL : public LedDriverHAL {
public:
    int addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0, uint8_t groupId = 0) override {
        Led* newLed = nullptr;
        switch (type) {
            case SINGLE_LED:
                if (pinCount >= 1) {
                    newLed = new LedSingle(pins[0]);
                }
                break;
            case DUAL_LED:
                if (pinCount >= 2) {
                    newLed = new LedDual(pins[0], pins[1]);
                }
                break;
            case TRIPLE_LED:
                if (pinCount >= 3) {
                    newLed = new LedTriple(pins[0], pins[1], pins[2]);
                }
                break;
            case RGB_LED:
                if (pinCount >= 3) {
                    newLed = new LedRgb(pins[0], pins[1], pins[2]);
                }
                break;
            case NEOPIXEL:
                if (pinCount >= 1 && numLeds > 0) {
                    newLed = new LedNeoPixel(pins[0], numLeds);
                }
                break;
            case WS2811_3x1:
                if (pinCount >= 1 && numLeds > 0) {
                    newLed = new LedWs2811_3x1(pins[0], numLeds);
                }
                break;
        }

        if (newLed) {
            _leds.push_back(newLed);
            if (groupId >= _ledGroups.size()) {
                _ledGroups.resize(groupId + 1);
            }
            _ledGroups[groupId].push_back(newLed);
            return _leds.size() - 1;
        }

        return -1; // Return -1 if LED creation failed
    }
};

#endif // ARDUINO_LED_DRIVER_HAL_H
