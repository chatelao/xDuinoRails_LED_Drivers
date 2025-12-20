/**
 * @file SingleLedBlink.ino
 * @brief The "Hello, World!" of LEDs, using the LedSingle driver.
 *
 * @details This sketch demonstrates the most basic use of the library: creating
 * a single LED driver and making it blink. It shows how to instantiate a
 * `SINGLE_LED` type and use the fundamental `on()` and `off()` methods.
 *
 * ### Hardware Setup:
 * - A single-color LED connected to Arduino pin 13. On most Arduino boards,
 *   this is the built-in LED.
 */
#include <ArduinoLedDriverHAL.h>

// Create the HAL factory
ArduinoLedDriverHAL ledHal;

// Define the pin the LED is connected to.
// This is an array even for a single pin to match the addLeds signature.
const uint8_t ledPins[] = {13};

// Create a pointer for the LED object
Led* myLed;

void setup() {
  // Create the LED driver using the factory
  myLed = ledHal.addLeds(SINGLE_LED, ledPins, 1);
}

void loop() {
  // Check if the LED object was created successfully
  if (myLed) {
    // Use the base class methods to control the LED
    myLed->on();
    delay(1000);
    myLed->off();
    delay(1000);
  }
}
