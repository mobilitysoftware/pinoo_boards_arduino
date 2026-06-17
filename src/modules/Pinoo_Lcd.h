/**
 * @file Pinoo_Lcd.h
 * @brief I2C 1602 LCD Screen module class.
 * 
 * Supports compile-time validated I2C Port 10 structure or custom address config.
 * Wraps the standard LiquidCrystal_I2C library.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_LCD_H
#define PINOO_LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "../Pinoo_Config.h"

class Pinoo_Lcd {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (must be PORT10).
     * @param address I2C address of the LCD (defaults to 0x27).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_Lcd(PortType port, uint8_t address = 0x27) : _lcd(address, 16, 2), _cols(16), _rows(2) {
        PINOO_ASSERT_I2C(PortType);
    }

    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Lcd(PortType port, bool bypass, uint8_t address = 0x27) : _lcd(address, 16, 2), _cols(16), _rows(2) {
    }

    /**
     * @brief Constructor for raw connection.
     * @param address I2C address of the LCD (defaults to 0x27).
     * @param cols Number of columns (defaults to 16).
     * @param rows Number of rows (defaults to 2).
     */
    Pinoo_Lcd(uint8_t address = 0x27, uint8_t cols = 16, uint8_t rows = 2);

    /**
     * @brief Initializes the LCD screen. Must be called in setup().
     */
    void begin();

    /**
     * @brief Clears the screen and moves the cursor to (0,0).
     */
    void clear();

    /**
     * @brief Moves the cursor to (0,0).
     */
    void home();

    /**
     * @brief Sets the cursor position.
     * @param col Column index (0 to cols-1).
     * @param row Row index (0 to rows-1).
     */
    void setCursor(uint8_t col, uint8_t row);

    /**
     * @brief Prints text to the LCD screen.
     * @param str Null-terminated string to print.
     */
    void print(const char* str);

    /**
     * @brief Prints a string to the LCD.
     * @param str Arduino String object.
     */
    void print(const String& str);

    /**
     * @brief Prints an integer value.
     * @param value Integer value to print.
     */
    void print(int value);

    /**
     * @brief Turns on the LCD backlight.
     */
    void backlight();

    /**
     * @brief Turns off the LCD backlight.
     */
    void noBacklight();

private:
    LiquidCrystal_I2C _lcd;
    uint8_t _cols;
    uint8_t _rows;
};

#endif // PINOO_LCD_H
