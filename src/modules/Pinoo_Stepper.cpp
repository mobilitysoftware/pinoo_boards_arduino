/**
 * @file Pinoo_Stepper.cpp
 * @brief Stepper motor module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Stepper.h"

Pinoo_Stepper::Pinoo_Stepper(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
    : _in1(in1), _in2(in2), _in3(in3), _in4(in4) {}

void Pinoo_Stepper::begin() {
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_in3, OUTPUT);
    pinMode(_in4, OUTPUT);
    stop();
}

void Pinoo_Stepper::stepCW(int steps, int stepDelayMs) {
    if (stepDelayMs < 1) stepDelayMs = 1;
    for (int i = 0; i < steps; i++) {
        digitalWrite(_in4, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in4, LOW);
        digitalWrite(_in3, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in3, LOW);
        digitalWrite(_in2, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in2, LOW);
        digitalWrite(_in1, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in1, LOW);
    }
}

void Pinoo_Stepper::stepCCW(int steps, int stepDelayMs) {
    if (stepDelayMs < 1) stepDelayMs = 1;
    for (int i = 0; i < steps; i++) {
        digitalWrite(_in1, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in1, LOW);
        digitalWrite(_in2, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in2, LOW);
        digitalWrite(_in3, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in3, LOW);
        digitalWrite(_in4, HIGH);
        delay(stepDelayMs);
        digitalWrite(_in4, LOW);
    }
}

void Pinoo_Stepper::stop() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
}
