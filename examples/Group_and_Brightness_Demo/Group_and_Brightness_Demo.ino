/**
 * @file Group_and_Brightness_Demo.ino
 * @brief Demonstrates individual, group, and brightness control features.
 *
 * @details This sketch showcases several key features of the LedDriverHAL:
 * 1.  **Individual Control:** How to get a pointer to a specific Led object
 *     using `getLed()` and control it directly.
 * 2.  **Grouping:** How to assign different Led objects to groups using the
 *     `groupId` parameter in the `addLeds()` method.
 * 3.  **Group Control:** How to set the color and brightness for all LEDs
 *     in a group simultaneously using `setGroupColor()` and `setGroupBrightness()`.
 * 4.  **Brightness:** How `setBrightness()` works on both single-color and
 *     RGB LEDs.
 *
 * ### Hardware Setup:
 * - A single-color LED connected to pin 13.
 * - A common anode RGB LED with its R, G, B pins connected to 9, 10, and 11.
 * - Open the Serial Monitor to see the sequence of actions.
 */
#include <ArduinoLedDriverHAL.h>

ArduinoLedDriverHAL ledHal;

// Pin definitions
const uint8_t SINGLE_LED_PIN = 13;
const uint8_t RGB_LED_PINS[] = {9, 10, 11};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // --- Create LEDs and assign them to groups ---

  // Group 0: A single LED. The 5th parameter to addLeds is the groupId.
  ledHal.addLeds(SINGLE_LED, &SINGLE_LED_PIN, 1, 0, 0);

  // Group 1: An RGB LED.
  ledHal.addLeds(RGB_LED, RGB_LED_PINS, 3, 0, 1);

  Serial.println("LEDs created and assigned to groups.");
}

void loop() {
  // --- Individual LED Control ---
  Serial.println("Controlling LEDs individually by global index:");

  // Get a pointer to the first LED that was added (global index 0)
  Led* singleLed = ledHal.getLed(0);
  if (singleLed) {
    Serial.println("  - Turning on single LED.");
    singleLed->on();
    delay(1000);

    Serial.println("  - Setting single LED brightness to 50%.");
    singleLed->setBrightness(128);
    delay(1000);

    Serial.println("  - Turning off single LED.");
    singleLed->off();
    delay(1000);
  }

  // Get a pointer to the second LED that was added (global index 1)
  Led* rgbLed = ledHal.getLed(1);
  if (rgbLed) {
    Serial.println("  - Setting RGB LED to Red.");
    rgbLed->setColor({255, 0, 0});
    delay(1000);

    Serial.println("  - Setting RGB LED brightness to 25%.");
    rgbLed->setBrightness(64);
    delay(1000);

    Serial.println("  - Setting RGB LED to Blue.");
    rgbLed->setColor({0, 0, 255});
    delay(1000);
  }

  // --- Group Control ---
  Serial.println("Controlling LEDs by group:");

  // Set color for group 0
  Serial.println("  - Setting color for group 0 (Single LED).");
  // For a single LED, setting color sets its brightness based on luminance.
  ledHal.setGroupColor(0, {0, 255, 0}); // This will turn the single LED on
  delay(1000);

  // Set brightness for group 1
  Serial.println("  - Setting brightness for group 1 (RGB LED) to 100%.");
  ledHal.setGroupBrightness(1, 255);
  delay(1000);

  // Set color for group 1
  Serial.println("  - Setting color for group 1 (RGB LED) to Green.");
  ledHal.setGroupColor(1, {0, 255, 0});
  delay(1000);

  // Set brightness for all groups to a low level
  Serial.println("  - Setting brightness for all groups to 10%.");
  ledHal.setGroupBrightness(0, 25);
  ledHal.setGroupBrightness(1, 25);
  delay(2000);
}
