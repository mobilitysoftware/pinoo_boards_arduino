/**
 * @file Pinoo_Tilt.cpp
 * @brief Tilt and Vibration Sensor source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Tilt.h"

Pinoo_Tilt::Pinoo_Tilt(uint8_t pin) : _pin(pin) {}

void Pinoo_Tilt::begin() {
    pinMode(_pin, INPUT);
}

int Pinoo_Tilt::readValue() {
    return digitalRead(_pin);
}

bool Pinoo_Tilt::isTilted() {
    return (digitalRead(_pin) == HIGH);
}
