# xDuinoRails_LED-Drivers

This is a Hardware Abstraction Layer (HAL) for controlling various types of LEDs with an Arduino. It provides a consistent interface for different LED configurations, making it easy to switch between them.

## Features

- **Single/Dual/Triple LEDs:** Support for single, dual, and triple LED configurations, with both cathode and anode drive.
- **RGB LEDs:** Control RGB LEDs connected directly to MCU pins.
- **Addressable LED Strips:** Control WS2811, WS2812, and other NeoPixel-compatible addressable LED strips.

## Installation

1.  Download this library as a ZIP file.
2.  In the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library...` and select the downloaded file.
3.  The library will be installed and ready to use.

## Usage

The library now uses a factory pattern to create LED driver instances. You create an instance of `ArduinoLedDriverHAL` and then use its `addLeds` method to create drivers for your LEDs.

### Example

```cpp
#include <ArduinoLedDriverHAL.h>

// Create the HAL factory
ArduinoLedDriverHAL ledHal;

// Define pins for a single LED
const uint8_t singleLedPins[] = {13};
Led* myLed;

// Define pins for an RGB LED
const uint8_t rgbLedPins[] = {9, 10, 11};
Led* myRgbLed;

// Define pins and settings for a NeoPixel strip
const uint8_t neoPixelPins[] = {6};
const uint16_t numLeds = 10;
LedNeoPixel* myStrip; // Cast to LedNeoPixel to access strip-specific methods

void setup() {
  // Create the LED drivers using the factory
  myLed = ledHal.addLeds(SINGLE_LED, singleLedPins, 1);
  myRgbLed = ledHal.addLeds(RGB_LED, rgbLedPins, 3);
  myStrip = static_cast<LedNeoPixel*>(ledHal.addLeds(NEOPIXEL, neoPixelPins, 1, numLeds));
}

void loop() {
  // Use the single LED
  myLed->on();
  delay(1000);
  myLed->off();
  delay(1000);

  // Use the RGB LED
  myRgbLed->setColor({255, 0, 0}); // Red
  delay(1000);
  myRgbLed->setColor({0, 255, 0}); // Green
  delay(1000);

  // Use the NeoPixel strip
  if (myStrip) {
    rainbow(20);
  }
}

// A simple rainbow effect for the NeoPixel strip
void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for (int i = 0; i < myStrip->numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / myStrip->numPixels());
      // Note: The setColor method used here is specific to LedNeoPixel
      myStrip->setColor(i, myStrip->gamma32(myStrip->ColorHSV(pixelHue)));
    }
    myStrip->show();
    delay(wait);
  }
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
