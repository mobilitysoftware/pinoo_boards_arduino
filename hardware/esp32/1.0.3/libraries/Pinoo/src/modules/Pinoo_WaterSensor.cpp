/**
 * @file Pinoo_WaterSensor.cpp
 * @brief Water Level Sensor source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_WaterSensor.h"

Pinoo_WaterSensor::Pinoo_WaterSensor(uint8_t pin) : _pin(pin) {}

void Pinoo_WaterSensor::begin() {
    pinMode(_pin, INPUT);
}

int Pinoo_WaterSensor::readValue() {
    // PINOO_ANALOG_READ normalises 12-bit ESP32 ADC to 10-bit for cross-platform consistency.
    return PINOO_ANALOG_READ(_pin);
}
