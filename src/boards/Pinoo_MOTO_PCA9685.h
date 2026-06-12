/**
 * @file Pinoo_MOTO_PCA9685.h
 * @brief Lightweight, self-contained I2C driver for the PCA9685 PWM chip.
 * 
 * Used internally on the Pinoo Moto board to control DC motors, stepper motors, and servos.
 * Eliminates external library dependencies like Adafruit_PWMServoDriver.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_MOTO_PCA9685_H
#define PINOO_MOTO_PCA9685_H

#include <Arduino.h>

class PinooMotoDriver {
public:
    /**
     * @brief Initializes the PCA9685 PWM chip. Safe to call multiple times.
     */
    static void begin();

    /**
     * @brief Sets the output PWM frequency (between 12Hz and 1024Hz).
     * @param freq The desired frequency in Hz.
     */
    static void setPWMFreq(float freq);

    /**
     * @brief Sets the PWM outputs for a specific channel.
     * @param channel The output channel (0 to 15).
     * @param on The step at which the signal transitions to HIGH (0 to 4095).
     * @param off The step at which the signal transitions to LOW (0 to 4095).
     */
    static void setPWM(uint8_t channel, uint16_t on, uint16_t off);

    /**
     * @brief Reads the currently set PWM frequency.
     * @return The current frequency in Hz.
     */
    static float getCurrentFreq();

private:
    static bool _initialized;
    static float _currentFreq;

    static void writeRegister(uint8_t reg, uint8_t val);
    static uint8_t readRegister(uint8_t reg);
};

#endif // PINOO_MOTO_PCA9685_H
