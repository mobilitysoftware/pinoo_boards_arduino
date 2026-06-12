/**
 * @file Pinoo_MOTO_PCA9685.cpp
 * @brief PCA9685 driver implementation using the standard Arduino Wire library.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_MOTO_PCA9685.h"
#include <Wire.h>

#define PCA9685_I2C_ADDR  0x40
#define REG_MODE1         0x00
#define REG_PRESCALE      0xFE
#define REG_LED0_ON_L     0x06

bool PinooMotoDriver::_initialized = false;
float PinooMotoDriver::_currentFreq = 0.0f;

void PinooMotoDriver::begin() {
    if (_initialized) return;
    
    Wire.begin();
    
    // Reset PCA9685 (Writes to MODE1)
    writeRegister(REG_MODE1, 0x80);
    delay(10);
    
    // Set a default frequency of 1000Hz for quiet DC motor operation
    setPWMFreq(1000.0f);
    
    _initialized = true;
}

void PinooMotoDriver::setPWMFreq(float freq) {
    begin();
    
    // Limit bounds
    if (freq < 12.0f) freq = 12.0f;
    if (freq > 1024.0f) freq = 1024.0f;
    
    // Prescale calculation: prescale = round(osc_value / (4096 * update_rate)) - 1
    float prescaleval = 25000000.0f; // Onboard oscillator is 25MHz
    prescaleval /= 4096.0f;
    prescaleval /= freq;
    prescaleval -= 1.0f;
    
    uint8_t prescale = (uint8_t)floor(prescaleval + 0.5f);
    
    uint8_t oldmode = readRegister(REG_MODE1);
    uint8_t newmode = (oldmode & 0x7F) | 0x10; // Sleep mode active to configure prescaler
    
    writeRegister(REG_MODE1, newmode);     // Enter sleep
    writeRegister(REG_PRESCALE, prescale); // Apply prescaler
    writeRegister(REG_MODE1, oldmode);     // Wake up
    delay(5);
    
    // Turn on auto-increment for efficient multi-byte transmission
    writeRegister(REG_MODE1, oldmode | 0xA0);
    
    _currentFreq = freq;
}

void PinooMotoDriver::setPWM(uint8_t channel, uint16_t on, uint16_t off) {
    begin();
    
    Wire.beginTransmission(PCA9685_I2C_ADDR);
    Wire.write(REG_LED0_ON_L + 4 * channel);
    Wire.write(on & 0xFF);
    Wire.write((on >> 8) & 0xFF);
    Wire.write(off & 0xFF);
    Wire.write((off >> 8) & 0xFF);
    Wire.endTransmission();
}

float PinooMotoDriver::getCurrentFreq() {
    return _currentFreq;
}

void PinooMotoDriver::writeRegister(uint8_t reg, uint8_t val) {
    Wire.beginTransmission(PCA9685_I2C_ADDR);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

uint8_t PinooMotoDriver::readRegister(uint8_t reg) {
    Wire.beginTransmission(PCA9685_I2C_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    
    Wire.requestFrom((uint8_t)PCA9685_I2C_ADDR, (uint8_t)1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0;
}
