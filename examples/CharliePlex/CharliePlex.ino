/**
 * @file CharliePlex.ino
 * @brief Example sketch for the LedCharliePlex driver.
 *
 * @details This sketch demonstrates how to use the LedCharliePlex driver to control
 * a charlieplexed LED matrix. It animates a single "chasing" pixel around the
 * matrix.
 *
 * ### Hardware Setup:
 * - Connect 3 Arduino pins (e.g., 9, 10, 11) to your LED matrix.
 * - With 3 pins, you can control up to 3 * (3 - 1) = 6 LEDs.
 * - For each pair of pins (A, B), connect one LED from A to B and another
 *   from B to A.
 *
 * ### Important:
 * The `show()` method for POV-based drivers like LedCharliePlex and LedMatrix
 * must be called on every single iteration of the main `loop()` to ensure the
 * display is refreshed rapidly enough to create the illusion of a stable image.
 * All animation logic should be handled with non-blocking timers (like `millis()`)
 * to avoid pausing the loop.
 */
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
    // Create a new CharliePlex driver instance
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
        charliePlexLeds->setPixelColor(currentLed, {0, 0, 0});

        // Move to the next LED
        currentLed++;
        if (currentLed >= (pinCount * (pinCount - 1))) {
            currentLed = 0;
        }

        // Turn on the new current LED
        charliePlexLeds->setPixelColor(currentLed, {255, 255, 255});
    }

    // Refresh the display on every loop iteration for POV
    charliePlexLeds->show();
}
