/**
 * @file Pinoo_Buzzer.cpp
 * @brief Buzzer module source implementation.
 * 
 * ## ESP32 Compatibility Note
 * 
 * AVR Arduino provides tone()/noTone() as built-in functions backed by a
 * hardware timer. On ESP32, the Arduino-ESP32 core (v2.x+) provides these
 * same functions via the LEDC peripheral, so tone()/noTone() work without
 * change. No conditional compilation is required.
 * 
 * If using an older ESP32 core (v1.x) that lacks tone() support, upgrade
 * to Arduino-ESP32 v2.0 or later.
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
        // tone() is available on both AVR and ESP32-Arduino core v2.x+
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
