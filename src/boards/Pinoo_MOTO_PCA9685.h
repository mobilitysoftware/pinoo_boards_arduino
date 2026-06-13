/**
 * @file Pinoo_MOTO_PCA9685.h
 * @brief Lightweight wrapper around Adafruit_PWMServoDriver for the Pinoo Moto board.
 *
 * Exposes a static singleton API (PinooMotoDriver::begin / setPWM / setPWMFreq)
 * so that Pinoo_DcMotor, Pinoo_Stepper and Pinoo_Servo can use the driver
 * without holding their own Adafruit object.
 *
 * Hardware constants for Pinoo Moto V1.1:
 *   PCA9685 I2C address : 0x40 (default)
 *   On-board oscillator : 27 000 000 Hz
 *   Default PWM frequency: 1000 Hz (DC motors)
 *
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_MOTO_PCA9685_H
#define PINOO_MOTO_PCA9685_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

/** Oscillator frequency of the crystal fitted on the Pinoo Moto board (Hz). */
#define PINOO_MOTO_OSC_FREQ   27000000UL

class PinooMotoDriver {
public:
    /**
     * @brief Initializes the PCA9685 PWM chip. Safe to call multiple times;
     *        subsequent calls are no-ops.
     */
    static void begin();

    /**
     * @brief Sets the PWM output frequency for all channels.
     * @param freq Desired frequency in Hz (12 – 1600 Hz).
     */
    static void setPWMFreq(float freq);

    /**
     * @brief Sets the ON and OFF ticks for a single PCA9685 channel.
     * @param channel Output channel (0 – 15).
     * @param on      Step at which the output goes HIGH (0 – 4095).
     * @param off     Step at which the output goes LOW  (0 – 4095).
     */
    static void setPWM(uint8_t channel, uint16_t on, uint16_t off);

    /**
     * @brief Returns the currently configured PWM frequency.
     * @return Frequency in Hz.
     */
    static float getCurrentFreq();

private:
    static bool                    _initialized;
    static float                   _currentFreq;
    static Adafruit_PWMServoDriver _pwm;
};

#endif // PINOO_MOTO_PCA9685_H
