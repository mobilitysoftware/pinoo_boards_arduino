/**
 * @file Pinoo_Servo.cpp
 * @brief Servo motor module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Servo.h"

Pinoo_Servo::Pinoo_Servo(uint8_t pin) : _pin(pin) {}

void Pinoo_Servo::begin() {
    if (!_servo.attached()) {
        _servo.attach(_pin);
    }
}

void Pinoo_Servo::write(int angle) {
    if (!_servo.attached()) {
        begin();
    }
    _servo.write(angle);
}

int Pinoo_Servo::read() {
    return _servo.read();
}

void Pinoo_Servo::detach() {
    if (_servo.attached()) {
        _servo.detach();
    }
}
