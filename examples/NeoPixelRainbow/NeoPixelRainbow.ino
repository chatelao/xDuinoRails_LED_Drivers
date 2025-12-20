/**
 * @file NeoPixelRainbow.ino
 * @brief Example sketch for the LedNeoPixel driver.
 *
 * @details This sketch demonstrates how to use the LedNeoPixel driver, which is a
 * wrapper around the Adafruit_NeoPixel library. It shows how to:
 * 1.  Instantiate a NeoPixel driver.
 * 2.  Cast the base `Led*` to a `LedNeoPixel*` to access specific methods
 *     like `numPixels()` and `ColorHSV()`.
 * 3.  Create a rainbow animation using the underlying library's utility functions.
 *
 * ### Hardware Setup:
 * - An Adafruit NeoPixel (WS2812B) strip with at least 10 pixels.
 * - Connect the NeoPixel data input pin to Arduino pin 6.
 * - Provide appropriate 5V power and ground to the strip.
 */
#include <ArduinoLedDriverHAL.h>

// Create the HAL factory
ArduinoLedDriverHAL ledHal;

// Define the pin for the NeoPixel strip
const uint8_t neoPixelPins[] = {6};
// Define the number of LEDs in the strip
const uint16_t numLeds = 10;

// Create a pointer for our NeoPixel object
LedNeoPixel* myStrip;

void setup() {
  // Create the LED driver using the factory
  // We cast the generic Led* pointer returned by addLeds to a LedNeoPixel*
  // so we can access the specific helper methods of the NeoPixel class.
  myStrip = static_cast<LedNeoPixel*>(ledHal.addLeds(NEOPIXEL, neoPixelPins, 1, numLeds));
}

void loop() {
  // Check if the strip object was created successfully
  if (myStrip) {
    rainbow(20);
  }
}

// A simple rainbow effect, adapted from the Adafruit_NeoPixel library examples.
void rainbow(int wait) {
  // Cycle through all 65536 hues
  for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    // Set the color of each pixel
    for (int i = 0; i < myStrip->numPixels(); i++) {
      // Calculate the hue for this pixel, spreading it across the strip
      int pixelHue = firstPixelHue + (i * 65536L / myStrip->numPixels());
      // The LedNeoPixel class exposes the underlying ColorHSV and gamma32 methods
      // from the Adafruit library for convenience.
      myStrip->setColor(i, myStrip->gamma32(myStrip->ColorHSV(pixelHue)));
    }
    // After setting all the pixel colors in the buffer, push them to the strip.
    myStrip->show();
    delay(wait);
  }
}
