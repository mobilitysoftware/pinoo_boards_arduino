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
    return digitalRead(_leftPin);
}

int Pinoo_LineTracker::readRight() {
    return digitalRead(_rightPin);
}

bool Pinoo_LineTracker::isOnLineLeft() {
    return (readLeft() == HIGH);
}

bool Pinoo_LineTracker::isOnLineRight() {
    return (readRight() == HIGH);
}
