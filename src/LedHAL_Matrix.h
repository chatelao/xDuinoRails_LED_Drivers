/**
 * @file LedHAL_Matrix.h
 * @brief Driver for a row-column scanned LED matrix.
 */
#ifndef XDUINORAILS_LED_DRIVERS_MATRIX_H
#define XDUINORAILS_LED_DRIVERS_MATRIX_H

#include "LedStrip.h"
#include <Arduino.h>
#include <string.h>

/**
 * @class LedMatrix
 * @brief Manages a matrix of single-color LEDs using row-column scanning.
 *
 * This class uses Persistence of Vision (POV) to control a matrix of LEDs by
 * activating one row at a time and setting the brightness of each LED in that
 * row via PWM on the column pins. The `show()` method must be called continuously
 * in a loop to scan through the rows and maintain the display.
 */
class LedMatrix : public LedStrip {
public:
    /**
     * @brief Constructor for the LedMatrix class.
     *
     * @param rowPins A pointer to an array of pin numbers for the rows.
     * @param rowCount The number of rows in the matrix.
     * @param colPins A pointer to an array of pin numbers for the columns.
     * @param colCount The number of columns in the matrix.
     * @param groupId The identifier for the group this matrix belongs to.
     * @param indexInGroup The index of this matrix within its group.
     */
    LedMatrix(const uint8_t* rowPins, uint8_t rowCount, const uint8_t* colPins, uint8_t colCount, uint8_t groupId = 0, uint16_t indexInGroup = 0)
        : LedStrip(groupId, indexInGroup), _rows(rowCount), _cols(colCount), _rowPins(nullptr), _colPins(nullptr), _buffer(nullptr), _currentRow(0) {

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

    /**
     * @brief Destructor. Frees dynamically allocated memory.
     */
    ~LedMatrix() {
        delete[] _rowPins;
        delete[] _colPins;
        delete[] _buffer;
    }

    /**
     * @brief Turns all LEDs in the matrix on to the current brightness.
     */
    void on() override {
        memset(_buffer, _brightness, _rows * _cols * sizeof(uint8_t));
    }

    /**
     * @brief Turns all LEDs in the matrix off.
     */
    void off() override {
        memset(_buffer, 0, _rows * _cols * sizeof(uint8_t));
        for (uint8_t i = 0; i < _rows; i++) {
            digitalWrite(_rowPins[i], HIGH);
        }
        for (uint8_t i = 0; i < _cols; i++) {
            digitalWrite(_colPins[i], LOW);
        }
    }

    /**
     * @brief Sets the brightness of all LEDs based on an RgbColor.
     * @param color The RgbColor to derive brightness from.
     */
    void setColor(const RgbColor& color) override {
        uint8_t brightness = (color.r + color.g + color.b) / 3;
        setBrightness(brightness);
        if (brightness > 0) {
            on();
        } else {
            off();
        }
    }

    /**
     * @brief Sets the brightness of a specific LED in the matrix buffer.
     * @param col The column of the LED.
     * @param row The row of the LED.
     * @param color The RgbColor to derive brightness from.
     */
    void setColor(uint8_t col, uint8_t row, const RgbColor& color) {
        if (row < _rows && col < _cols) {
            _buffer[row * _cols + col] = (color.r + color.g + color.b) / 3;
        }
    }

    /**
     * @brief Sets the brightness of a specific LED in the matrix buffer using a linear index.
     * @param pixelIndex The linear index of the pixel (row * num_cols + col).
     * @param color The RgbColor to derive brightness from.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _rows * _cols) {
            _buffer[pixelIndex] = (color.r + color.g + color.b) / 3;
        }
    }

    /**
     * @brief Sets the overall brightness for the matrix.
     * This brightness is used when `on()` is called.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        Led::setBrightness(brightness);
    }

    /**
     * @brief Refreshes the display by scanning the next row. Must be called repeatedly in a loop.
     *
     * It deactivates the previous row, advances to the next row, sets the column
     * brightnesses for the new row using PWM, and then activates the new row.
     */
    void show() override {
        // Deactivate the current row
        digitalWrite(_rowPins[_currentRow], HIGH);

        // Move to the next row
        _currentRow++;
        if (_currentRow >= _rows) {
            _currentRow = 0;
        }

        // Set column PWM values for the new current row
        for (uint8_t c = 0; c < _cols; c++) {
            analogWrite(_colPins[c], _buffer[_currentRow * _cols + c]);
        }

        // Activate the new current row
        digitalWrite(_rowPins[_currentRow], LOW);
    }

private:
    uint8_t _rows;              ///< Number of rows in the matrix.
    uint8_t _cols;              ///< Number of columns in the matrix.
    uint8_t* _rowPins;          ///< Array of pin numbers for rows.
    uint8_t* _colPins;          ///< Array of pin numbers for columns.
    uint8_t* _buffer;           ///< Internal buffer for LED brightness values.
    uint8_t _currentRow;        ///< The current row being scanned.
};

#endif // XDUINORAILS_LED_DRIVERS_MATRIX_H
