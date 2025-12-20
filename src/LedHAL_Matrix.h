/**
 * @file LedHAL_Matrix.h
 * @brief Driver for a row/column scanned LED matrix.
 *
 * This file provides the implementation for controlling a standard LED matrix
 * by scanning through rows and driving columns with PWM. Like the charlieplexing
 * driver, it relies on Persistence of Vision (POV) and requires the `show()`
 * method to be called repeatedly in the main application loop.
 */
#ifndef XDUINORAILS_LED_DRIVERS_MATRIX_H
#define XDUINORAILS_LED_DRIVERS_MATRIX_H

#include "LedStrip.h"
#include <Arduino.h>
#include <string.h>

/**
 * @class LedMatrix
 * @brief Concrete class for a row/column scanned LED matrix.
 *
 * Implements the LedStrip interface to control a matrix of single-color LEDs.
 * The `show()` method drives the display by activating one row at a time and
 * setting the brightness of each LED in that row using `analogWrite` on the
 * column pins. For the matrix to be visible, `show()` must be called
 * continuously.
 */
class LedMatrix : public LedStrip {
public:
    /**
     * @brief Constructor for the LedMatrix driver.
     * @param rowPins A pointer to an array of pins connected to the matrix rows.
     * @param rowCount The number of rows.
     * @param colPins A pointer to an array of pins connected to the matrix columns.
     * @param colCount The number of columns.
     * @param groupId An optional ID for grouping LEDs.
     * @param indexInGroup An optional index within the group.
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
            digitalWrite(_rowPins[i], HIGH); // Deactivate all rows
        }
        for (uint8_t i = 0; i < _cols; i++) {
            pinMode(_colPins[i], OUTPUT);
            digitalWrite(_colPins[i], LOW); // Set all columns off
        }
    }

    /**
     * @brief Destructor that cleans up dynamically allocated memory.
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
        // Explicitly turn off hardware to prevent ghosting
        for (uint8_t i = 0; i < _rows; i++) {
            digitalWrite(_rowPins[i], HIGH);
        }
        for (uint8_t i = 0; i < _cols; i++) {
            digitalWrite(_colPins[i], LOW);
        }
    }

    /**
     * @brief Sets the brightness of the entire matrix based on a color.
     * @param color The RgbColor whose luminance will be used to set the brightness.
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
     * @brief Sets the brightness of a single LED in the matrix by row and column.
     * @param col The column of the LED.
     * @param row The row of the LED.
     * @param color The RgbColor to determine the brightness.
     */
    void setColor(uint8_t col, uint8_t row, const RgbColor& color) {
        if (row < _rows && col < _cols) {
            _buffer[row * _cols + col] = (color.r + color.g + color.b) / 3;
        }
    }

    /**
     * @brief Sets the brightness of a single LED by its linear index.
     * @param pixelIndex The linear index of the pixel (row * _cols + col).
     * @param color The RgbColor to determine the brightness.
     */
    void setPixelColor(uint16_t pixelIndex, const RgbColor& color) override {
        if (pixelIndex < _rows * _cols) {
            _buffer[pixelIndex] = (color.r + color.g + color.b) / 3;
        }
    }

    /**
     * @brief Sets the overall brightness for the matrix.
     * @param brightness The brightness level (0-255).
     */
    void setBrightness(uint8_t brightness) override {
        LedStrip::setBrightness(brightness);
    }

    /**
     * @brief Refreshes the display by scanning one row. Call this in a loop.
     * Deactivates the previous row, advances to the next row, sets the column
     * PWM values for that row from the buffer, and then activates the current row.
     */
    void show() override {
        // Deactivate the currently active row
        digitalWrite(_rowPins[_currentRow], HIGH);

        // Move to the next row
        _currentRow++;
        if (_currentRow >= _rows) {
            _currentRow = 0;
        }

        // Set column values for the new row
        for (uint8_t c = 0; c < _cols; c++) {
            // Brightness is applied by scaling the buffer value
            uint8_t val = map(_buffer[_currentRow * _cols + c], 0, 255, 0, _brightness);
            analogWrite(_colPins[c], val);
        }

        // Activate the new current row
        digitalWrite(_rowPins[_currentRow], LOW);
    }

private:
    uint8_t _rows;          ///< Number of rows in the matrix.
    uint8_t _cols;          ///< Number of columns in the matrix.
    uint8_t* _rowPins;      ///< Pointer to the array of row pins.
    uint8_t* _colPins;      ///< Pointer to the array of column pins.
    uint8_t* _buffer;       ///< Internal buffer storing the brightness of each LED.
    uint8_t _currentRow;    ///< The row currently being scanned.
};

#endif // XDUINORAILS_LED_DRIVERS_MATRIX_H
