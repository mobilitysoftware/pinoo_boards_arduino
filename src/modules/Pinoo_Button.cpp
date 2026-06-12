/**
 * @file Pinoo_Button.cpp
 * @brief Button module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Button.h"

Pinoo_Button::Pinoo_Button(uint8_t pin) : _pin(pin) {
    #if defined(__AVR_ATmega328P__) || defined(ARDUINO_AVR_UNO)
        _isAnalogOnly = (pin == A6 || pin == A7);
    #else
        _isAnalogOnly = false;
    #endif
}

void Pinoo_Button::begin() {
    if (!_isAnalogOnly) {
        pinMode(_pin, INPUT);
    }
}

int Pinoo_Button::readValue() {
    if (_isAnalogOnly) {
        return (analogRead(_pin) > 500) ? HIGH : LOW;
    } else {
        return digitalRead(_pin);
    }
}

bool Pinoo_Button::isPressed() {
    return (readValue() == HIGH);
}
