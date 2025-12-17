#include <LedHAL_Rgb.h>

// Define the pins for the RGB LED
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

// Create a LedRgb object (assuming common cathode)
LedRgb myRgbLed(redPin, greenPin, bluePin, false);

void setup() {
  // Nothing to do in setup, the LedRgb constructor handles it.
}

void loop() {
  // Cycle through some colors
  myRgbLed.setColor({255, 0, 0}); // Red
  delay(1000);
  myRgbLed.setColor({0, 255, 0}); // Green
  delay(1000);
  myRgbLed.setColor({0, 0, 255}); // Blue
  delay(1000);
  myRgbLed.setColor({255, 255, 0}); // Yellow
  delay(1000);
  myRgbLed.setColor({0, 255, 255}); // Cyan
  delay(1000);
  myRgbLed.setColor({255, 0, 255}); // Magenta
  delay(1000);
}
