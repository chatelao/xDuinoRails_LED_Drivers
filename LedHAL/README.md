# Arduino LED HAL Library

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

The library provides a base `Led` class with a common interface. You can create objects of the specific LED type you are using.

### Single LED

```cpp
#include <LedHAL_Single.h>

const int ledPin = 13;
LedSingle myLed(ledPin);

void setup() {
}

void loop() {
  myLed.on();
  delay(1000);
  myLed.off();
  delay(1000);
}
```

### RGB LED

```cpp
#include <LedHAL_Rgb.h>

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
LedRgb myRgbLed(redPin, greenPin, bluePin, false); // Common cathode

void setup() {
}

void loop() {
  myRgbLed.setColor({255, 0, 0}); // Red
  delay(1000);
  myRgbLed.setColor({0, 255, 0}); // Green
  delay(1000);
}
```

### NeoPixel LED Strip

**Note:** This class requires the [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) library to be installed.

```cpp
#include <LedHAL_NeoPixel.h>

const int dataPin = 6;
const int numLeds = 10;
LedNeoPixel myStrip(dataPin, numLeds);

void setup() {
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
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
