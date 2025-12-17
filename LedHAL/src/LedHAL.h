#ifndef LED_HAL_H
#define LED_HAL_H

#include <stdint.h>

// Define a structure for RGB colors
struct RgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Led {
public:
    virtual ~Led() {}

    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setColor(const RgbColor& color) = 0;
};

#endif // LED_HAL_H
