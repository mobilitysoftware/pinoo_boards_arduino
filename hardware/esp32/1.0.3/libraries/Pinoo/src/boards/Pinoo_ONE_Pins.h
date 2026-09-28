/**
 * @file Pinoo_ONE_Pins.h
 * @brief Dedicated pin mappings for the Pinoo ONE board.
 * 
 * This file defines the hardware pin constants for on-board components
 * and the RJ11 port interfaces of the Pinoo ONE microcontroller board.
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_ONE_PINS_H
#define PINOO_ONE_PINS_H

#include <Arduino.h>

// =============================================================================
// On-Board Internal Components
// =============================================================================

/** @brief On-board USER LED pin (connected to digital pin 13) */
#define PINOO_ONE_INTERNAL_LED     13

/** @brief On-board Infrared Receiver (IR-R) pin (connected to digital pin 12) */
#define PINOO_ONE_INTERNAL_IR      12

/** @brief On-board USER BUTTON pin (connected to analog pin A7) */
#define PINOO_ONE_INTERNAL_BUTTON  A7

/** @brief On-board LDR (Light Dependent Resistor) light sensor pin (connected to analog pin A6) */
#define PINOO_ONE_INTERNAL_LDR     A6

/** @brief On-board Passive Buzzer pin (connected to digital pin 9 / PWM capable) */
#define PINOO_ONE_INTERNAL_BUZZER  9


// =============================================================================
// RJ11 Ports Matrix (Digital & Analog Interfaces)
// =============================================================================

// Port 1 (Pink/Purple) -> Pin 4: D2
#define PINOO_ONE_PORT1_PIN4       2

// Port 2 (Pink/Purple) -> Pin 4: D3 (PWM/Interrupt)
#define PINOO_ONE_PORT2_PIN4       3

// Port 3 (Pink/Purple) -> Pin 4: D4
#define PINOO_ONE_PORT3_PIN4       4

// Port 4 (Pink/Purple) -> Pin 4: D7
#define PINOO_ONE_PORT4_PIN4       7

// Port 5 (Pink/Purple) -> Pin 4: D8
#define PINOO_ONE_PORT5_PIN4       8
#define PINOO_ONE_PORT5_PIN2       9

// Port 6 (Green/Red) -> Pin 4: D12, Pin 2: D13 (Dual Signal)
#define PINOO_ONE_PORT6_PIN4       12
#define PINOO_ONE_PORT6_PIN2       13

// Port 7 (Red) -> Pin 4: A0
#define PINOO_ONE_PORT7_PIN4       A0

// Port 8 (Red) -> Pin 4: A1
#define PINOO_ONE_PORT8_PIN4       A1

// Port 9 (Yellow/Red) -> Pin 4: A2, Pin 2: A3 (Dual Signal)
#define PINOO_ONE_PORT9_PIN4       A2
#define PINOO_ONE_PORT9_PIN2       A3

// Port 10 (White/Red) -> Pin 4: A4 (SDA), Pin 2: A5 (SCL) [Hardware I2C]
#define PINOO_ONE_PORT10_PIN4      A4
#define PINOO_ONE_PORT10_PIN2      A5

// =============================================================================
// RJ11 Port Compile-Time Type-Safe Abstraction System
// =============================================================================

struct PinooDoor1 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT1_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor2 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT2_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor3 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT3_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor4 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT4_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor5 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT5_PIN4;
    static constexpr uint8_t pin2 = PINOO_ONE_PORT5_PIN2;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true; // Pin 9 (pin2) is PWM capable
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor6 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT6_PIN4;
    static constexpr uint8_t pin2 = PINOO_ONE_PORT6_PIN2;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor7 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT7_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor8 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT8_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooDoor9 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT9_PIN4;
    static constexpr uint8_t pin2 = PINOO_ONE_PORT9_PIN2;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true; // Both A2 and A3 are analog
    static constexpr bool is_i2c = false;
};

struct PinooDoor10 {
    static constexpr uint8_t pin4 = PINOO_ONE_PORT10_PIN4;
    static constexpr uint8_t pin2 = PINOO_ONE_PORT10_PIN2;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true; // Both A4 and A5 are analog
    static constexpr bool is_i2c = true;
};

// Global constexpr door objects
constexpr PinooDoor1 DOOR1{};
constexpr PinooDoor2 DOOR2{};
constexpr PinooDoor3 DOOR3{};
constexpr PinooDoor4 DOOR4{};
constexpr PinooDoor5 DOOR5{};
constexpr PinooDoor6 DOOR6{};
constexpr PinooDoor7 DOOR7{};
constexpr PinooDoor8 DOOR8{};
constexpr PinooDoor9 DOOR9{};
constexpr PinooDoor10 DOOR10{};

#endif // PINOO_ONE_PINS_H
