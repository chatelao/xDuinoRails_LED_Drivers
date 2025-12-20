/**
 * @file Ws2811_3x1_Breathe.ino
 * @brief Example for the LedWs2811_3x1 driver.
 *
 * @details This sketch demonstrates how to use the LedWs2811_3x1 driver to create a
 * "breathing" effect. This driver is specifically for setups where a WS2811 IC
 * (normally used for RGB LEDs) drives three individual single-color LEDs.
 *
 * The `setColor()` method calculates the luminance of the passed `RgbColor` and
 * applies that brightness value to all three output channels (R, G, and B) of
 * the WS2811, effectively making it a 3-channel PWM driver for the single-color
 * LEDs.
 *
 * ### Hardware Setup:
 * - One or more WS2811 ICs.
 * - Each WS2811 IC connected to three single-color LEDs.
 * - The data line of the first WS2811 IC connected to Arduino pin 6.
 * - Provide appropriate power and ground.
 */
#include <ArduinoLedDriverHAL.h>

// Define the data pin and number of WS2811 ICs
#define LED_PIN 6
#define NUM_LEDS 5

ArduinoLedDriverHAL hal;
Led* leds;

void setup() {
    uint8_t pins[] = {LED_PIN};
    leds = hal.addLeds(WS2811_3x1, pins, 1, NUM_LEDS);
}

void loop() {
    // Create a breathing effect by smoothly changing the brightness.
    // Since this driver uses luminance, we pass a grayscale RgbColor where r=g=b.

    // Breathe in (fade from 0 to 255)
    for (int i = 0; i < 255; i++) {
        leds->setColor({(uint8_t)i, (uint8_t)i, (uint8_t)i});
        delay(5);
    }

    // Breathe out (fade from 255 to 0)
    for (int i = 255; i >= 0; i--) {
        leds->setColor({(uint8_t)i, (uint8_t)i, (uint8_t)i});
        delay(5);
    }
}
