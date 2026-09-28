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

namespace {
    struct PinooLcdYes { char value[1]; };
    struct PinooLcdNo { char value[2]; };

    template <typename T>
    class PinooLcdApi {
        template <typename U>
        static PinooLcdYes hasInit(decltype(((U*)0)->init())*);
        template <typename>
        static PinooLcdNo hasInit(...);

        template <typename U>
        static PinooLcdYes hasBegin(decltype(((U*)0)->begin())*);
        template <typename>
        static PinooLcdNo hasBegin(...);

        template <typename U>
        static PinooLcdYes hasBeginWithSize(decltype(((U*)0)->begin((uint8_t)0, (uint8_t)0))*);
        template <typename>
        static PinooLcdNo hasBeginWithSize(...);

    public:
        enum {
            init = sizeof(hasInit<T>(0)) == sizeof(PinooLcdYes),
            begin = sizeof(hasBegin<T>(0)) == sizeof(PinooLcdYes),
            beginWithSize = sizeof(hasBeginWithSize<T>(0)) == sizeof(PinooLcdYes)
        };
    };

    template <typename LcdType>
    typename Pinoo::enable_if<PinooLcdApi<LcdType>::init>::type pinooLcdBegin(LcdType& lcd, uint8_t, uint8_t) {
        lcd.init();
    }

    template <typename LcdType>
    typename Pinoo::enable_if<!PinooLcdApi<LcdType>::init && PinooLcdApi<LcdType>::begin>::type pinooLcdBegin(LcdType& lcd, uint8_t, uint8_t) {
        lcd.begin();
    }

    template <typename LcdType>
    typename Pinoo::enable_if<!PinooLcdApi<LcdType>::init && !PinooLcdApi<LcdType>::begin && PinooLcdApi<LcdType>::beginWithSize>::type pinooLcdBegin(LcdType& lcd, uint8_t cols, uint8_t rows) {
        lcd.begin(cols, rows);
    }
}

Pinoo_Lcd::Pinoo_Lcd(uint8_t address, uint8_t cols, uint8_t rows) 
    : _lcd(address, cols, rows), _cols(cols), _rows(rows) {}

void Pinoo_Lcd::begin() {
    pinooLcdBegin(_lcd, _cols, _rows);
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
