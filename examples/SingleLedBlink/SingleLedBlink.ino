#include <ArduinoLedDriverHAL.h>

// Create the HAL factory
ArduinoLedDriverHAL ledHal;

// Define the pin the LED is connected to
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
    myLed->on();
    delay(1000);
    myLed->off();
    delay(1000);
  }
}
