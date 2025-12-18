#include <ArduinoLedDriverHAL.h>

#define PIN 6
#define WIDTH 8
#define HEIGHT 8

ArduinoLedDriverHAL hal;
LedMatrix* matrix;

void setup() {
  uint8_t pins[] = {PIN, WIDTH, HEIGHT};
  matrix = static_cast<LedMatrix*>(hal.addLeds(MATRIX, pins, sizeof(pins)));
}

void loop() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      matrix->setColor(x, y, {255, 0, 0});
      matrix->show();
      delay(50);
      matrix->setColor(x, y, {0, 0, 0});
    }
  }
}
