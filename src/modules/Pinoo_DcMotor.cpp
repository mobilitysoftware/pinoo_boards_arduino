/**
 * @file Pinoo_DcMotor.cpp
 * @brief DC Motor module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_DcMotor.h"

Pinoo_DcMotor::Pinoo_DcMotor(MotorChannel channel) {
    if (channel == LEFT_MOTOR) {
        _in1 = 11;
        _in2 = 10;
        _isRight = false;
    } else {
        _in1 = 5;
        _in2 = 6;
        _isRight = true;
    }
}

Pinoo_DcMotor::Pinoo_DcMotor(uint8_t in1, uint8_t in2) 
    : _in1(in1), _in2(in2), _isRight(false) {}

void Pinoo_DcMotor::begin() {
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    stop();
}

void Pinoo_DcMotor::setSpeed(int speed) {
    speed = constrain(speed, -255, 255);

    if (speed == 0) {
        stop();
        return;
    }

    if (_isRight) {
        if (speed > 0) {
            digitalWrite(_in1, LOW);
            analogWrite(_in2, speed);
        } else {
            analogWrite(_in1, -speed);
            digitalWrite(_in2, LOW);
        }
    } else {
        if (speed > 0) {
            analogWrite(_in1, speed);
            digitalWrite(_in2, LOW);
        } else {
            digitalWrite(_in1, LOW);
            analogWrite(_in2, -speed);
        }
    }
}

void Pinoo_DcMotor::stop() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
}

void Pinoo_DcMotor::brake() {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, HIGH);
}
