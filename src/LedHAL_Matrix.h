#ifndef XDUINORAILS_LED_DRIVERS_MATRIX_H
#define XDUINORAILS_LED_DRIVERS_MATRIX_H

#include "xDuinoRails_LED-Drivers.h"
#include <Arduino.h>
#include <string.h>

class LedMatrix : public Led {
public:
    LedMatrix(const uint8_t* rowPins, uint8_t rowCount, const uint8_t* colPins, uint8_t colCount, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : Led(groupId, indexInGroup), _rows(rowCount), _cols(colCount), _rowPins(nullptr), _colPins(nullptr), _buffer(nullptr), _currentRow(0) {

        _rowPins = new uint8_t[_rows];
        _colPins = new uint8_t[_cols];
        memcpy(_rowPins, rowPins, _rows * sizeof(uint8_t));
        memcpy(_colPins, colPins, _cols * sizeof(uint8_t));

        _buffer = new uint8_t[_rows * _cols];
        memset(_buffer, 0, _rows * _cols * sizeof(uint8_t));

        for (uint8_t i = 0; i < _rows; i++) {
            pinMode(_rowPins[i], OUTPUT);
            digitalWrite(_rowPins[i], HIGH);
        }
        for (uint8_t i = 0; i < _cols; i++) {
            pinMode(_colPins[i], OUTPUT);
            digitalWrite(_colPins[i], LOW);
        }
    }

    ~LedMatrix() {
        delete[] _rowPins;
        delete[] _colPins;
        delete[] _buffer;
    }

    void on() override {
        memset(_buffer, _brightness, _rows * _cols * sizeof(uint8_t));
    }

    void off() override {
        memset(_buffer, 0, _rows * _cols * sizeof(uint8_t));
        for (uint8_t i = 0; i < _rows; i++) {
            digitalWrite(_rowPins[i], HIGH);
        }
        for (uint8_t i = 0; i < _cols; i++) {
            digitalWrite(_colPins[i], LOW);
        }
    }

    void setColor(const RgbColor& color) override {
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        setBrightness(brightness);
        if (brightness > 0) {
            on();
        } else {
            off();
        }
    }

    void setColor(uint8_t col, uint8_t row, const RgbColor& color) {
        if (row < _rows && col < _cols) {
            _buffer[row * _cols + col] = (color.r + color.g + color.b) / 3;
        }
    }

    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
    }

    void show() {
        digitalWrite(_rowPins[_currentRow], HIGH);

        _currentRow++;
        if (_currentRow >= _rows) {
            _currentRow = 0;
        }

        for (uint8_t c = 0; c < _cols; c++) {
            analogWrite(_colPins[c], _buffer[_currentRow * _cols + c]);
        }

        digitalWrite(_rowPins[_currentRow], LOW);
    }

private:
    uint8_t _rows;
    uint8_t _cols;
    uint8_t* _rowPins;
    uint8_t* _colPins;
    uint8_t* _buffer;
    uint8_t _currentRow;
};

#endif // XDUINORAILS_LED_DRIVERS_MATRIX_H
