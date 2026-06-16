/**
 * @file Pinoo_Ldr.cpp
 * @brief Light Dependent Resistor (LDR) module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Ldr.h"

Pinoo_Ldr::Pinoo_Ldr(uint8_t pin) : _pin(pin) {}

void Pinoo_Ldr::begin() {
    pinMode(_pin, INPUT);
}

int Pinoo_Ldr::readValue() {
    return analogRead(_pin);
}

int Pinoo_Ldr::getLightPercentage() {
    int raw = readValue();
    int percentage = map(raw, 0, 1023, 0, 100);
    return constrain(percentage, 0, 100);
}
