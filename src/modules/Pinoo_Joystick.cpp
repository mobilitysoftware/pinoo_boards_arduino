/**
 * @file Pinoo_Joystick.cpp
 * @brief Joystick module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Joystick.h"

Pinoo_Joystick::Pinoo_Joystick(uint8_t xPin, uint8_t yPin, uint8_t btnPin) 
    : _xPin(xPin), _yPin(yPin), _btnPin(btnPin), _hasButton(btnPin != 0) {}

void Pinoo_Joystick::begin() {
    pinMode(_xPin, INPUT);
    pinMode(_yPin, INPUT);
    if (_hasButton) {
        pinMode(_btnPin, INPUT_PULLUP);
    }
}

int Pinoo_Joystick::getX() {
    return analogRead(_xPin);
}

int Pinoo_Joystick::getY() {
    return analogRead(_yPin);
}

bool Pinoo_Joystick::isButtonPressed() {
    if (!_hasButton) {
        return false;
    }
    return (digitalRead(_btnPin) == LOW);
}
