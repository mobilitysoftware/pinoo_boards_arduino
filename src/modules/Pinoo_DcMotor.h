/**
 * @file Pinoo_DcMotor.h
 * @brief DC Motor module class. Handles direction and speed control for DC motors.
 * 
 * On Pinoo Moto, there are 8 independent outputs MOTOR1-MOTOR8 (no left/right);
 * they map to PCA9685 channels via PinooMotoDriver.
 * On Pinoo ONE / Shield / Bricky, LEFT_MOTOR / RIGHT_MOTOR map to direct PWM Arduino pins.
 * (LEFT_MOTOR / RIGHT_MOTOR still compile on Moto as aliases of MOTOR1 / MOTOR2,
 * only for code compatibility. Use MOTOR1..MOTOR8 on Moto.)
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_DC_MOTOR_H
#define PINOO_DC_MOTOR_H

#include <Arduino.h>
// Pinoo_Config.h must be included here so that the ARDUINO_PINOO_MOTO compiler
// flag (set by boards.txt build.board=PINOO_MOTO) is translated to
// PINOO_BOARD_MOTO before any #if defined(PINOO_BOARD_MOTO) checks in this
// header or its corresponding .cpp file.
#include "../Pinoo_Config.h"

enum MotorChannel {
    LEFT_MOTOR,
    RIGHT_MOTOR,
    MOTOR1,
    MOTOR2,
    MOTOR3,
    MOTOR4,
    MOTOR5,
    MOTOR6,
    MOTOR7,
    MOTOR8
};

class Pinoo_DcMotor {
public:
    /**
     * @brief Constructor for predefined motor channels.
     * @param channel Pinoo Moto: MOTOR1..MOTOR8. Pinoo ONE/Shield/Bricky: LEFT_MOTOR or RIGHT_MOTOR.
     */
    Pinoo_DcMotor(MotorChannel channel);

    /**
     * @brief Constructor for custom DC motor pin connections.
     * @param in1 Direction/Speed pin 1.
     * @param in2 Direction/Speed pin 2.
     */
    Pinoo_DcMotor(uint8_t in1, uint8_t in2);

    /**
     * @brief Initializes motor driver pins. Must be called in setup().
     */
    void begin();

    /**
     * @brief Sets the speed and direction of the DC motor.
     * @param speed Motor speed from -255 (full speed backward) to 255 (full speed forward).
     */
    void setSpeed(int speed);

    /**
     * @brief Stops the DC motor smoothly (coasts to a stop).
     */
    void stop();

    /**
     * @brief Actively brakes the DC motor (locks the shaft).
     */
    void brake();

private:
    uint8_t _in1;
    uint8_t _in2;
    bool _isRight;
};

#endif // PINOO_DC_MOTOR_H
