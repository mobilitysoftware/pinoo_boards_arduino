/**
 * @file Pinoo_Bricky_Pins.h
 * @brief Dedicated pin mappings for the Pinoo Bricky board.
 * 
 * This file defines the hardware pin constants for on-board components
 * and the RJ11 port interfaces of the Pinoo Bricky board.
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_BRICKY_PINS_H
#define PINOO_BRICKY_PINS_H

#include <Arduino.h>

// =============================================================================
// On-Board Internal Components
// =============================================================================

/** @brief On-board USER LED pin (connected to digital pin 13) */
#define PINOO_BRICKY_INTERNAL_LED     13

/** @brief On-board Infrared Receiver (IR-R) pin (connected to digital pin 12) */
#define PINOO_BRICKY_INTERNAL_IR      12

/** @brief On-board USER BUTTON pin (Not supported on Pinoo Bricky) */
#define PINOO_BRICKY_INTERNAL_BUTTON  -1

/** @brief On-board LDR light sensor pin (Not supported on Pinoo Bricky) */
#define PINOO_BRICKY_INTERNAL_LDR     -1

/** @brief On-board Passive Buzzer pin (Not supported on Pinoo Bricky) */
#define PINOO_BRICKY_INTERNAL_BUZZER  -1


// =============================================================================
// RJ11 Ports Matrix (Digital & Analog Interfaces)
// =============================================================================

// Port 1 (Pink/Purple) -> Pin 4: D2
#define PINOO_BRICKY_PORT1_PIN4       2

// Port 2 (Pink/Purple) -> Pin 4: D3 (PWM/Interrupt)
#define PINOO_BRICKY_PORT2_PIN4       3

// Port 3 (Pink/Purple) -> Pin 4: D4
#define PINOO_BRICKY_PORT3_PIN4       4

// Port 4 (Pink/Purple) -> Pin 4: D7
#define PINOO_BRICKY_PORT4_PIN4       7

// Port 5 (Pink/Purple) -> Pin 4: D8
#define PINOO_BRICKY_PORT5_PIN4       8
#define PINOO_BRICKY_PORT5_PIN2       9

// Port 6 (Green/Red) -> Pin 4: D12, Pin 2: D13 (Dual Signal)
#define PINOO_BRICKY_PORT6_PIN4       12
#define PINOO_BRICKY_PORT6_PIN2       13

// Port 7 (Red) -> Pin 4: A0
#define PINOO_BRICKY_PORT7_PIN4       A0

// Port 8 (Red) -> Pin 4: A1
#define PINOO_BRICKY_PORT8_PIN4       A1

// Port 9 (Yellow/Red) -> Pin 4: A2, Pin 2: A3 (Dual Signal)
#define PINOO_BRICKY_PORT9_PIN4       A2
#define PINOO_BRICKY_PORT9_PIN2       A3

// Port 10 (White/Red) -> Pin 4: A4 (SDA), Pin 2: A5 (SCL) [Hardware I2C]
#define PINOO_BRICKY_PORT10_PIN4      A4
#define PINOO_BRICKY_PORT10_PIN2      A5

// =============================================================================
// RJ11 Port Compile-Time Type-Safe Abstraction System
// =============================================================================

struct PinooBrickyDoor1 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT1_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor2 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT2_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor3 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT3_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor4 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT4_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor5 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT5_PIN4;
    static constexpr uint8_t pin2 = PINOO_BRICKY_PORT5_PIN2;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor6 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT6_PIN4;
    static constexpr uint8_t pin2 = PINOO_BRICKY_PORT6_PIN2;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor7 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT7_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor8 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT8_PIN4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor9 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT9_PIN4;
    static constexpr uint8_t pin2 = PINOO_BRICKY_PORT9_PIN2;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyDoor10 {
    static constexpr uint8_t pin4 = PINOO_BRICKY_PORT10_PIN4;
    static constexpr uint8_t pin2 = PINOO_BRICKY_PORT10_PIN2;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = true;
};

// Global constexpr door objects
constexpr PinooBrickyDoor1 DOOR1{};
constexpr PinooBrickyDoor2 DOOR2{};
constexpr PinooBrickyDoor3 DOOR3{};
constexpr PinooBrickyDoor4 DOOR4{};
constexpr PinooBrickyDoor5 DOOR5{};
constexpr PinooBrickyDoor6 DOOR6{};
constexpr PinooBrickyDoor7 DOOR7{};
constexpr PinooBrickyDoor8 DOOR8{};
constexpr PinooBrickyDoor9 DOOR9{};
constexpr PinooBrickyDoor10 DOOR10{};

#endif // PINOO_BRICKY_PINS_H
