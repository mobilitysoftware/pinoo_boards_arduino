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
    // PINOO_ANALOG_READ normalises 12-bit ESP32 ADC to 10-bit for cross-platform consistency.
    return PINOO_ANALOG_READ(_pin);
}

int Pinoo_Ldr::getLightPercentage() {
    int raw = readValue(); // always 0-1023 after macro normalisation
    int percentage = map(raw, 0, 1023, 0, 100);
    return constrain(percentage, 0, 100);
}
