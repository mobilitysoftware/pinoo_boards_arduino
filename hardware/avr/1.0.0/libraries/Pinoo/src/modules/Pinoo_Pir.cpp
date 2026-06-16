/**
 * @file Pinoo_Pir.cpp
 * @brief PIR Motion Sensor source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Pir.h"

Pinoo_Pir::Pinoo_Pir(uint8_t pin) : _pin(pin) {}

void Pinoo_Pir::begin() {
    pinMode(_pin, INPUT);
}

int Pinoo_Pir::readValue() {
    return digitalRead(_pin);
}

bool Pinoo_Pir::isMotionDetected() {
    return (digitalRead(_pin) == HIGH);
}
