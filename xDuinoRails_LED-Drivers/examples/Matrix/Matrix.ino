#include <ArduinoLedDriverHAL.h>

#define ROWS 4
#define COLS 4

uint8_t rowPins[ROWS] = {2, 3, 4, 5};
uint8_t colPins[COLS] = {6, 7, 8, 9};

ArduinoLedDriverHAL hal;
LedMatrix* matrix;

void setup() {
  uint8_t pins[ROWS + COLS];
  memcpy(pins, rowPins, ROWS);
  memcpy(pins + ROWS, colPins, COLS);

  matrix = static_cast<LedMatrix*>(hal.addLeds(MATRIX, pins, sizeof(pins), ROWS));
}

void loop() {
  // Turn on one LED at a time
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      matrix->setColor(c, r, {255, 0, 0});
      delay(100);
      matrix->setColor(c, r, {0, 0, 0});
    }
  }

  // Continuously refresh the display
  // In a real application, you would call this in a timer interrupt.
  // For this example, we'll just call it frequently.
  while(1) {
    matrix->show();
    delay(1); // Adjust this delay to control the refresh rate
  }
}
