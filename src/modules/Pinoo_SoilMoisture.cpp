/**
 * @file Pinoo_SoilMoisture.cpp
 * @brief Soil Moisture Sensor source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_SoilMoisture.h"

Pinoo_SoilMoisture::Pinoo_SoilMoisture(uint8_t pin) : _pin(pin) {}

void Pinoo_SoilMoisture::begin() {
    pinMode(_pin, INPUT);
}

int Pinoo_SoilMoisture::readValue() {
    return analogRead(_pin);
}

int Pinoo_SoilMoisture::getMoisturePercentage() {
    int raw = readValue();
    int percentage = map(raw, 1023, 0, 0, 100);
    return constrain(percentage, 0, 100);
}
