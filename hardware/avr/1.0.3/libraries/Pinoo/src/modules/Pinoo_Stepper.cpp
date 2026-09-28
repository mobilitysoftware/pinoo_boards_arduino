/**
 * @file Pinoo_Stepper.cpp
 * @brief Stepper motor module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Stepper.h"

#if defined(PINOO_BOARD_MOTO)
#include "../boards/Pinoo_MOTO_PCA9685.h"

static const int motorSteps[4][4] = {
  {1, 0, 0, 1},
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1}
};

Pinoo_Stepper::Pinoo_Stepper(StepperChannel channel) {
    _in1 = channel * 4;
}
#endif

Pinoo_Stepper::Pinoo_Stepper(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
    : _in1(in1), _in2(in2), _in3(in3), _in4(in4) {}

void Pinoo_Stepper::begin() {
#if defined(PINOO_BOARD_MOTO)
    PinooMotoDriver::begin();
    stop();
#else
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_in3, OUTPUT);
    pinMode(_in4, OUTPUT);
    stop();
#endif
}

void Pinoo_Stepper::stepCW(int steps, int stepDelayMs) {
    if (stepDelayMs < 1) stepDelayMs = 1;
#if defined(PINOO_BOARD_MOTO)
    for (int i = 0; i < steps; i++) {
        for (int step = 0; step < 4; step++) {
            for (int coil = 0; coil < 4; coil++) {
                if (motorSteps[step][coil] == 1) {
                    PinooMotoDriver::setPWM(_in1 + coil, 0, 4095);
                } else {
                    PinooMotoDriver::setPWM(_in1 + coil, 0, 0);
                }
            }
            delay(stepDelayMs);
        }
    }
#else
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
#endif
}

void Pinoo_Stepper::stepCCW(int steps, int stepDelayMs) {
    if (stepDelayMs < 1) stepDelayMs = 1;
#if defined(PINOO_BOARD_MOTO)
    for (int i = 0; i < steps; i++) {
        for (int step = 3; step >= 0; step--) {
            for (int coil = 0; coil < 4; coil++) {
                if (motorSteps[step][coil] == 1) {
                    PinooMotoDriver::setPWM(_in1 + coil, 0, 4095);
                } else {
                    PinooMotoDriver::setPWM(_in1 + coil, 0, 0);
                }
            }
            delay(stepDelayMs);
        }
    }
#else
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
#endif
}

void Pinoo_Stepper::stop() {
#if defined(PINOO_BOARD_MOTO)
    for (int i = 0; i < 4; i++) {
        PinooMotoDriver::setPWM(_in1 + i, 0, 0);
    }
#else
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
#endif
}
