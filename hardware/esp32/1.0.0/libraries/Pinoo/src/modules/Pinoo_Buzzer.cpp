/**
 * @file Pinoo_Buzzer.cpp
 * @brief Buzzer module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Buzzer.h"

Pinoo_Buzzer::Pinoo_Buzzer(uint8_t pin, BuzzerMode mode) : _pin(pin), _mode(mode) {}

void Pinoo_Buzzer::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Pinoo_Buzzer::turnOn() {
    if (_mode == ACTIVE_BUZZER) {
        digitalWrite(_pin, HIGH);
    } else {
        tone(_pin, 1000);
    }
}

void Pinoo_Buzzer::turnOff() {
    if (_mode == ACTIVE_BUZZER) {
        digitalWrite(_pin, LOW);
    } else {
        noTone(_pin);
    }
}

void Pinoo_Buzzer::playTone(unsigned int frequency) {
    if (_mode == PASSIVE_BUZZER) {
        tone(_pin, frequency);
    }
}

void Pinoo_Buzzer::playTone(unsigned int frequency, unsigned long duration) {
    if (_mode == PASSIVE_BUZZER) {
        tone(_pin, frequency, duration);
    }
}

void Pinoo_Buzzer::stop() {
    turnOff();
}
