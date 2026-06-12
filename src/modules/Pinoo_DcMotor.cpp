/**
 * @file Pinoo_DcMotor.cpp
 * @brief DC Motor module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_DcMotor.h"

Pinoo_DcMotor::Pinoo_DcMotor(MotorChannel channel) {
#if defined(PINOO_BOARD_MOTO)
    _isRight = false;
    switch (channel) {
        case MOTOR1:
        case LEFT_MOTOR:
            _in1 = 0; _in2 = 1; break;
        case MOTOR2:
        case RIGHT_MOTOR:
            _in1 = 2; _in2 = 3; break;
        case MOTOR3: _in1 = 4; _in2 = 5; break;
        case MOTOR4: _in1 = 6; _in2 = 7; break;
        case MOTOR5: _in1 = 8; _in2 = 9; break;
        case MOTOR6: _in1 = 10; _in2 = 11; break;
        case MOTOR7: _in1 = 12; _in2 = 13; break;
        case MOTOR8: _in1 = 14; _in2 = 15; break;
        default: _in1 = 0; _in2 = 1; break;
    }
#else
    if (channel == LEFT_MOTOR) {
        _in1 = 11;
        _in2 = 10;
        _isRight = false;
    } else {
        _in1 = 5;
        _in2 = 6;
        _isRight = true;
    }
#endif
}

Pinoo_DcMotor::Pinoo_DcMotor(uint8_t in1, uint8_t in2) 
    : _in1(in1), _in2(in2), _isRight(false) {}

void Pinoo_DcMotor::begin() {
#if defined(PINOO_BOARD_MOTO)
    PinooMotoDriver::begin();
    stop();
#else
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    stop();
#endif
}

void Pinoo_DcMotor::setSpeed(int speed) {
    speed = constrain(speed, -255, 255);

    if (speed == 0) {
        stop();
        return;
    }

#if defined(PINOO_BOARD_MOTO)
    int val = map(abs(speed), 0, 255, 0, 4095);
    if (speed > 0) {
        PinooMotoDriver::setPWM(_in1, 0, 0);
        PinooMotoDriver::setPWM(_in2, 0, val);
    } else {
        PinooMotoDriver::setPWM(_in1, 0, 4095);
        PinooMotoDriver::setPWM(_in2, 0, 4095 - val);
    }
#else
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
#endif
}

void Pinoo_DcMotor::stop() {
#if defined(PINOO_BOARD_MOTO)
    PinooMotoDriver::setPWM(_in1, 0, 0);
    PinooMotoDriver::setPWM(_in2, 0, 0);
#else
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
#endif
}

void Pinoo_DcMotor::brake() {
#if defined(PINOO_BOARD_MOTO)
    PinooMotoDriver::setPWM(_in1, 0, 4095);
    PinooMotoDriver::setPWM(_in2, 0, 4095);
#else
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, HIGH);
#endif
}
