/**
 * @file Pinoo_MOTO_PCA9685.cpp
 * @brief Adafruit_PWMServoDriver wrapper implementation for Pinoo Moto.
 *
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_MOTO_PCA9685.h"

// ---------------------------------------------------------------------------
// Static member definitions
// ---------------------------------------------------------------------------
bool                    PinooMotoDriver::_initialized = false;
float                   PinooMotoDriver::_currentFreq = 0.0f;
Adafruit_PWMServoDriver PinooMotoDriver::_pwm         = Adafruit_PWMServoDriver(0x40);

// ---------------------------------------------------------------------------
// begin()
// ---------------------------------------------------------------------------
void PinooMotoDriver::begin() {
    if (_initialized) return;
    _initialized = true;

    // Tell Adafruit driver the actual oscillator frequency of this board
    _pwm.setOscillatorFrequency(PINOO_MOTO_OSC_FREQ);

    // begin() resets the chip and calls setPWMFreq(1000) internally
    _pwm.begin();

    // Override with 1000 Hz explicitly so _currentFreq stays in sync
    _pwm.setPWMFreq(1000.0f);
    _currentFreq = 1000.0f;
}

// ---------------------------------------------------------------------------
// setPWMFreq()
// ---------------------------------------------------------------------------
void PinooMotoDriver::setPWMFreq(float freq) {
    if (!_initialized) begin();
    _pwm.setPWMFreq(freq);
    _currentFreq = freq;
}

// ---------------------------------------------------------------------------
// setPWM()
// ---------------------------------------------------------------------------
void PinooMotoDriver::setPWM(uint8_t channel, uint16_t on, uint16_t off) {
    if (!_initialized) begin();
    _pwm.setPWM(channel, on, off);
}

// ---------------------------------------------------------------------------
// getCurrentFreq()
// ---------------------------------------------------------------------------
float PinooMotoDriver::getCurrentFreq() {
    return _currentFreq;
}
