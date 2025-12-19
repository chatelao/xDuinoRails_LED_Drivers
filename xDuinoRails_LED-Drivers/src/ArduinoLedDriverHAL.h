#ifndef ARDUINO_LED_DRIVER_HAL_H
#define ARDUINO_LED_DRIVER_HAL_H

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
    Led* addLeds(LedType type, const uint8_t* pins, uint8_t pinCount, uint16_t numLeds = 0) override {
        switch (type) {
            case SINGLE_LED:
                if (pinCount >= 1) {
                    return new LedSingle(pins[0]);
                }
                break;
            case MULTI_LED:
                if (pinCount > 1) {
                    return new LedMulti(pins, pinCount);
                }
                break;
            case RGB_LED:
                if (pinCount >= 3) {
                    return new LedRgb(pins[0], pins[1], pins[2]);
                }
                break;
            case NEOPIXEL:
                if (pinCount >= 1 && numLeds > 0) {
                    return new LedNeoPixel(pins[0], numLeds);
                }
                break;
            case WS2811_3x1:
                if (pinCount >= 1 && numLeds > 0) {
                    return new LedWs2811_3x1(pins[0], numLeds);
                }
                break;
            case CHARLIEPLEX:
                if (pinCount > 1) {
                    return new LedCharliePlex(pins, pinCount);
                }
                break;
            case MATRIX:
                // For MATRIX type:
                // - numLeds: The number of rows in the matrix.
                // - pins: An array containing all row pins followed by all column pins.
                // - pinCount: The total number of pins (rows + columns).
                if (numLeds > 0 && pinCount >= numLeds) {
                    uint8_t rowCount = numLeds;
                    uint8_t colCount = pinCount - rowCount;
                    if (colCount > 0) {
                        const uint8_t* rowPins = pins;
                        const uint8_t* colPins = pins + rowCount;
                        return new LedMatrix(rowPins, rowCount, colPins, colCount);
                    }
                }
                break;
        }
        return nullptr; // Return null if pins are not configured correctly
    }
};

#endif // ARDUINO_LED_DRIVER_HAL_H
