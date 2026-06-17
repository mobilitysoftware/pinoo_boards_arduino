/**
 * @file Pinoo_Led.cpp
 * @brief LED module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Led.h"

Pinoo_Led::Pinoo_Led(uint8_t pin) : _pin(pin), _state(false) {}

void Pinoo_Led::begin() {
    PINOO_PREPARE_GPIO(_pin);
    digitalWrite(_pin, LOW);
    _state = false;
}

void Pinoo_Led::turnOn() {
    PINOO_PREPARE_GPIO(_pin);
    digitalWrite(_pin, HIGH);
    _state = true;
}

void Pinoo_Led::turnOff() {
    PINOO_PREPARE_GPIO(_pin);
    digitalWrite(_pin, LOW);
    _state = false;
}

void Pinoo_Led::toggle() {
    if (_state) {
        turnOff();
    } else {
        turnOn();
    }
}

void Pinoo_Led::setBrightness(uint8_t brightness) {
    analogWrite(_pin, brightness);
    _state = (brightness > 0);
}

bool Pinoo_Led::isOn() const {
    return _state;
}
