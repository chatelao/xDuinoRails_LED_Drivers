#include <ArduinoLedDriverHAL.h>

// Define the pins used for the Charlie-plexed matrix
const uint8_t pins[] = {9, 10, 11}; // 3 pins can control 3 * (3 - 1) = 6 LEDs
const uint8_t pinCount = sizeof(pins) / sizeof(pins[0]);

ArduinoLedDriverHAL driver;
LedCharliePlex* charliePlexLeds;

// Animation state
uint16_t currentLed = 0;
unsigned long lastUpdateTime = 0;
const int updateInterval = 100; // ms

void setup() {
    charliePlexLeds = static_cast<LedCharliePlex*>(driver.addLeds(CHARLIEPLEX, pins, pinCount));
    // Turn off all LEDs initially
    charliePlexLeds->off();
    charliePlexLeds->show();
}

void loop() {
    unsigned long currentTime = millis();

    // Update the animation state at a fixed interval
    if (currentTime - lastUpdateTime >= updateInterval) {
        lastUpdateTime = currentTime;

        // Turn off the previous LED
        charliePlexLeds->setColor(currentLed, {0, 0, 0});

        // Move to the next LED
        currentLed++;
        if (currentLed >= (pinCount * (pinCount - 1))) {
            currentLed = 0;
        }

        // Turn on the new current LED
        charliePlexLeds->setColor(currentLed, {255, 255, 255});
    }

    // Refresh the display on every loop iteration for POV
    charliePlexLeds->show();
}
