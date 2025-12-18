#include <ArduinoLedDriverHAL.h>

// Create the HAL instance
ArduinoLedDriverHAL ledHal;

// Define pins and LED counts
const uint8_t neoPixelPin[] = {6};
const uint16_t numLeds = 10;

const uint8_t singleLedPins[] = {9, 10, 11};

void setup() {
  // Add a NeoPixel strip to group 0
  ledHal.addLeds(NEOPIXEL, neoPixelPin, 1, numLeds, 0);

  // Add single LEDs to group 1
  ledHal.addLeds(SINGLE_LED, &singleLedPins[0], 1, 0, 1);
  ledHal.addLeds(SINGLE_LED, &singleLedPins[1], 1, 0, 1);
  ledHal.addLeds(SINGLE_LED, &singleLedPins[2], 1, 0, 1);
}

void loop() {
  // Set color and brightness for the NeoPixel strip (group 0)
  ledHal.setGroupColor(0, {255, 0, 0}); // Red
  ledHal.setGroupBrightness(0, 128);   // Half brightness
  delay(1000);

  // Turn on single LEDs (group 1)
  ledHal.groupOn(1);
  delay(1000);

  // Change color of the NeoPixel strip
  ledHal.setGroupColor(0, {0, 0, 255}); // Blue
  delay(1000);

  // Turn off all LEDs in group 1
  ledHal.groupOff(1);
  delay(1000);

  // Access a single LED by its global index
  Led* firstNeoPixel = ledHal.getLed(0);
  if (firstNeoPixel) {
    // This will set the color of the entire strip,
    // as the LedNeoPixel implementation applies the color to all pixels.
    firstNeoPixel->setColor({0, 255, 0}); // Green
  }
  delay(1000);
}
