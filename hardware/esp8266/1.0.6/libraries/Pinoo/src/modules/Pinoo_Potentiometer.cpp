/**
 * @file Pinoo_Potentiometer.cpp
 * @brief Potentiometer module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Potentiometer.h"

Pinoo_Potentiometer::Pinoo_Potentiometer(uint8_t pin) : _pin(pin) {}

void Pinoo_Potentiometer::begin() {
    pinMode(_pin, INPUT);
}

int Pinoo_Potentiometer::readValue() {
    // PINOO_ANALOG_READ normalises 12-bit ESP32 ADC to 10-bit for cross-platform consistency.
    return PINOO_ANALOG_READ(_pin);
}

int Pinoo_Potentiometer::getValuePercentage() {
    int raw = readValue(); // always 0-1023 after macro normalisation
    int percentage = map(raw, 0, 1023, 0, 100);
    return constrain(percentage, 0, 100);
}
