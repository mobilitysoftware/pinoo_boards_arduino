/**
 * @file Pinoo_Stepper.h
 * @brief Stepper motor module class. Handles direction, steps, and speed control.
 * 
 * Typically connected to the dedicated stepper motor port on Pinoo boards.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_STEPPER_H
#define PINOO_STEPPER_H

#include <Arduino.h>

class Pinoo_Stepper {
public:
    /**
     * @brief Constructor for Pinoo_Stepper.
     * @param in1 Stepper motor control pin 1 (defaults to 11).
     * @param in2 Stepper motor control pin 2 (defaults to 10).
     * @param in3 Stepper motor control pin 3 (defaults to 6).
     * @param in4 Stepper motor control pin 4 (defaults to 5).
     */
    Pinoo_Stepper(uint8_t in1 = 11, uint8_t in2 = 10, uint8_t in3 = 6, uint8_t in4 = 5);

    /**
     * @brief Initializes the stepper motor pins. Must be called in setup().
     */
    void begin();

    /**
     * @brief Rotates the stepper motor clockwise by a given number of steps.
     * @param steps Number of steps to rotate.
     * @param stepDelayMs Delay between each step sequence in milliseconds (default: 5).
     */
    void stepCW(int steps, int stepDelayMs = 5);

    /**
     * @brief Rotates the stepper motor counter-clockwise by a given number of steps.
     * @param steps Number of steps to rotate.
     * @param stepDelayMs Delay between each step sequence in milliseconds (default: 5).
     */
    void stepCCW(int steps, int stepDelayMs = 5);

    /**
     * @brief Turns off all coils to stop the motor and prevent overheating.
     */
    void stop();

private:
    uint8_t _in1;
    uint8_t _in2;
    uint8_t _in3;
    uint8_t _in4;
};

#endif // PINOO_STEPPER_H
