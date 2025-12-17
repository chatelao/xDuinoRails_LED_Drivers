#include <LedHAL_Single.h>

// Define the pin the LED is connected to
const int ledPin = 13;

// Create a LedSingle object
LedSingle myLed(ledPin);

void setup() {
  // Nothing to do in setup, the LedSingle constructor handles it.
}

void loop() {
  myLed.on();
  delay(1000);
  myLed.off();
  delay(1000);
}
