/**
 * @file Matrix.ino
 * @brief Example sketch for the LedMatrix driver.
 *
 * @details This sketch demonstrates how to use the LedMatrix driver to control a
 * row/column scanned LED matrix. It animates a single pixel moving through
 * each position in the matrix.
 *
 * ### Hardware Setup:
 * - Connect the row pins (e.g., 2, 3, 4, 5) and column pins (e.g., 6, 7, 8, 9)
 *   of your LED matrix to the specified Arduino pins.
 * - This example assumes the rows are connected to the anodes and the columns
 *   to the cathodes, which is a common configuration.
 *
 * ### Important:
 * The `show()` method for POV-based drivers like LedMatrix must be called on
 * every single iteration of the main `loop()` to refresh the display rapidly.
 * This scanning process creates the illusion of a stable image. All animation
 * logic should be handled with non-blocking timers (like `millis()`) to avoid
 * pausing the loop and causing flicker.
 */
#include <ArduinoLedDriverHAL.h>

#define ROWS 4
#define COLS 4

// Define the pins for the matrix rows and columns
uint8_t rowPins[ROWS] = {2, 3, 4, 5};
uint8_t colPins[COLS] = {6, 7, 8, 9};

ArduinoLedDriverHAL hal;
LedMatrix* matrix;

// --- Animation State ---
int currentRow = 0;
int currentCol = 0;
unsigned long lastUpdateTime = 0;
const int updateInterval = 100; // ms, speed of the animation

void setup() {
  // The LedMatrix driver expects a single array of pins, with all row pins
  // followed by all column pins. We create that here.
  uint8_t pins[ROWS + COLS];
  memcpy(pins, rowPins, ROWS);
  memcpy(pins + ROWS, colPins, COLS);

  // Create the matrix driver instance.
  // The 'numLeds' parameter for a MATRIX type is the number of rows.
  matrix = static_cast<LedMatrix*>(hal.addLeds(MATRIX, pins, sizeof(pins), ROWS));
  matrix->setBrightness(128); // Set a moderate brightness
}

void loop() {
  unsigned long currentTime = millis();

  // Use a non-blocking timer to update the animation at a fixed interval
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    // Turn off the previous LED in the sequence
    matrix->setColor(currentCol, currentRow, {0, 0, 0});

    // Move to the next LED
    currentCol++;
    if (currentCol >= COLS) {
      currentCol = 0;
      currentRow++;
      if (currentRow >= ROWS) {
        currentRow = 0;
      }
    }

    // Turn on the new current LED
    matrix->setColor(currentCol, currentRow, {255, 0, 0}); // Set it to red
  }

  // This is the most critical part: the display must be refreshed on
  // EVERY loop cycle for the Persistence of Vision effect to work.
  matrix->show();
}
