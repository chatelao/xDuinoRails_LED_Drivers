#include <ArduinoLedDriverHAL.h>

// This example demonstrates the use of the LedWs2811_3x1 driver.
// It creates a "breathing" effect on a strip of single-color WS2811 LEDs.

#define LED_PIN 6
#define NUM_LEDS 8

ArduinoLedDriverHAL hal;
Led* leds;

void setup() {
    uint8_t pins[] = {LED_PIN};
    leds = hal.addLeds(WS2811_3x1, pins, 1, NUM_LEDS);
}

void loop() {
    // Breathe in
    for (int i = 0; i < 255; i++) {
        leds->setColor({(uint8_t)i, (uint8_t)i, (uint8_t)i});
        delay(5);
    }

    // Breathe out
    for (int i = 255; i >= 0; i--) {
        leds->setColor({(uint8_t)i, (uint8_t)i, (uint8_t)i});
        delay(5);
    }
}
