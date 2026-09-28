/**
 * @file Pinoo_Servo.cpp
 * @brief Servo motor module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Servo.h"

#if defined(PINOO_BOARD_MOTO)
#include "../boards/Pinoo_MOTO_PCA9685.h"
#endif

Pinoo_Servo::Pinoo_Servo(uint8_t pin) : _pin(pin), _angle(90) {}

void Pinoo_Servo::begin() {
#if defined(PINOO_BOARD_MOTO)
    PinooMotoDriver::begin();
    PinooMotoDriver::setPWMFreq(50.0f); // Servos require a 50Hz refresh rate
#else
    if (!_servo.attached()) {
        _servo.attach(_pin);
    }
#endif
}

void Pinoo_Servo::write(int angle) {
    angle = constrain(angle, 0, 180);
#if defined(PINOO_BOARD_MOTO)
    begin();
    // Map 0..180 degrees to 102..512 pulse length out of 4096 (approx. 500us to 2500us at 50Hz)
    int val = map(angle, 0, 180, 102, 512);
    PinooMotoDriver::setPWM(_pin, 0, val);
    _angle = angle;
#else
    if (!_servo.attached()) {
        begin();
    }
    _servo.write(angle);
#endif
}

int Pinoo_Servo::read() {
#if defined(PINOO_BOARD_MOTO)
    return _angle;
#else
    return _servo.read();
#endif
}

void Pinoo_Servo::detach() {
#if defined(PINOO_BOARD_MOTO)
    PinooMotoDriver::setPWM(_pin, 0, 0); // Release motor output
#else
    if (_servo.attached()) {
        _servo.detach();
    }
#endif
}
