/**
 * @file Pinoo_Lcd.cpp
 * @brief I2C 1602 LCD Screen source implementation.
 * 
 * Delegates all display and control functions directly to the standard LiquidCrystal_I2C library.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Lcd.h"

Pinoo_Lcd::Pinoo_Lcd(uint8_t address, uint8_t cols, uint8_t rows) 
    : _lcd(address, cols, rows) {}

void Pinoo_Lcd::begin() {
    _lcd.begin(); // Initialize the LCD screen (compatible with fdebrabander & marcoschwartz forks)
    _lcd.backlight(); // Turn on backlight by default
}

void Pinoo_Lcd::clear() {
    _lcd.clear();
}

void Pinoo_Lcd::home() {
    _lcd.home();
}

void Pinoo_Lcd::setCursor(uint8_t col, uint8_t row) {
    _lcd.setCursor(col, row);
}

void Pinoo_Lcd::print(const char* str) {
    _lcd.print(str);
}

void Pinoo_Lcd::print(const String& str) {
    _lcd.print(str);
}

void Pinoo_Lcd::print(int value) {
    _lcd.print(value);
}

void Pinoo_Lcd::backlight() {
    _lcd.backlight();
}

void Pinoo_Lcd::noBacklight() {
    _lcd.noBacklight();
}
