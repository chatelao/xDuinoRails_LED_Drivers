#include <LedHAL_NeoPixel.h>

// Define the pin for the NeoPixel strip
const int dataPin = 6;
// Define the number of LEDs in the strip
const int numLeds = 10;

// Create a LedNeoPixel object
LedNeoPixel myStrip(dataPin, numLeds);

void setup() {
  // Nothing to do in setup, the LedNeoPixel constructor handles it.
}

void loop() {
  rainbow(20);
}

// A simple rainbow effect
void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for (int i = 0; i < myStrip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / myStrip.numPixels());
      myStrip.setColor(i, myStrip.gamma32(myStrip.ColorHSV(pixelHue)));
    }
    myStrip.show();
    delay(wait);
  }
}
