/**
 * @file RgbLedCycle.ino
 * @brief Example sketch for the LedRgb driver.
 *
 * @details This sketch demonstrates the basic use of the LedRgb driver to control a
 * standard common anode or common cathode RGB LED. It cycles through a sequence
 * of primary and secondary colors.
 *
 * ### Hardware Setup:
 * - A common anode RGB LED.
 * - Connect the R, G, and B pins of the LED to Arduino pins 9, 10, and 11
 *   respectively, each through an appropriate current-limiting resistor.
 * - Connect the common anode pin to the Arduino's 5V pin.
 * - By default, the `addLeds` factory creates a common anode (`ANODE`) driver.
 *   To use a common cathode LED, you would need to modify the underlying
 *   `LedRgb` constructor call, though this is not shown in the HAL example.
 */
#include <ArduinoLedDriverHAL.h>

// Create the HAL factory
ArduinoLedDriverHAL ledHal;

// Define the pins for the RGB LED
const uint8_t rgbLedPins[] = {9, 10, 11}; // R, G, B

// Create a pointer for the LED object
Led* myRgbLed;

void setup() {
  // Create the LED driver using the factory
  myRgbLed = ledHal.addLeds(RGB_LED, rgbLedPins, 3);
}

void loop() {
  // Check if the LED object was created successfully
  if (myRgbLed) {
    // Cycle through some colors
    myRgbLed->setColor({255, 0, 0}); // Red
    delay(1000);
    myRgbLed->setColor({0, 255, 0}); // Green
    delay(1000);
    myRgbLed->setColor({0, 0, 255}); // Blue
    delay(1000);
    myRgbLed->setColor({255, 255, 0}); // Yellow
    delay(1000);
    myRgbLed->setColor({0, 255, 255}); // Cyan
    delay(1000);
    myRgbLed->setColor({255, 0, 255}); // Magenta
    delay(1000);
  }
}
