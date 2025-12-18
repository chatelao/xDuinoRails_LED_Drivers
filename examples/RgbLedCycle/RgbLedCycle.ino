#include <ArduinoLedDriverHAL.h>

// Create the HAL factory
ArduinoLedDriverHAL ledHal;

// Define the pins for the RGB LED
const uint8_t rgbLedPins[] = {9, 10, 11};

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
