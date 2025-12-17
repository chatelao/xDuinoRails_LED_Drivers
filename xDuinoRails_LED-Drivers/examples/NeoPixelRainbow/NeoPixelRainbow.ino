#include <ArduinoLedDriverHAL.h>

// Create the HAL factory
ArduinoLedDriverHAL ledHal;

// Define the pin for the NeoPixel strip
const uint8_t neoPixelPins[] = {6};
// Define the number of LEDs in the strip
const uint16_t numLeds = 10;

// Create a pointer for the NeoPixel object
LedNeoPixel* myStrip;

void setup() {
  // Create the LED driver using the factory
  // Cast the result to LedNeoPixel* to access strip-specific methods
  myStrip = static_cast<LedNeoPixel*>(ledHal.addLeds(WS2811_RGB, neoPixelPins, 1, numLeds));
}

void loop() {
  // Check if the strip object was created successfully
  if (myStrip) {
    rainbow(20);
  }
}

// A simple rainbow effect
void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for (int i = 0; i < myStrip->numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / myStrip->numPixels());
      myStrip->setColor(i, myStrip->gamma32(myStrip->ColorHSV(pixelHue)));
    }
    myStrip->show();
    delay(wait);
  }
}
