/**
 * @file Pinoo_LineTracker.cpp
 * @brief Dual-channel Line Tracking sensor source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_LineTracker.h"

Pinoo_LineTracker::Pinoo_LineTracker(uint8_t leftPin, uint8_t rightPin) 
    : _leftPin(leftPin), _rightPin(rightPin) {}

void Pinoo_LineTracker::begin() {
    pinMode(_leftPin, INPUT);
    pinMode(_rightPin, INPUT);
}

int Pinoo_LineTracker::readLeft() {
    // PINOO_ANALOG_READ normalises the 12-bit ESP32 ADC to 10-bit (0-1023).
    return PINOO_ANALOG_READ(_leftPin);
}

int Pinoo_LineTracker::readRight() {
    return PINOO_ANALOG_READ(_rightPin);
}

void Pinoo_LineTracker::setThreshold(int threshold) {
    _threshold = constrain(threshold, 0, 1023);
}

bool Pinoo_LineTracker::isOnLineLeft() {
    return (readLeft() > _threshold);
}

bool Pinoo_LineTracker::isOnLineRight() {
    return (readRight() > _threshold);
}
