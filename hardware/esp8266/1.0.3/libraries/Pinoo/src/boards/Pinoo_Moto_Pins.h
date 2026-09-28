/**
 * @file Pinoo_Moto_Pins.h
 * @brief Dedicated pin mappings for the Pinoo Moto board.
 * 
 * This file defines the hardware pin constants for on-board components,
 * single jumper pins, and the RJ11 port interfaces of the Pinoo Moto board.
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_MOTO_PINS_H
#define PINOO_MOTO_PINS_H

#include <Arduino.h>

// =============================================================================
// On-Board Internal Components
// =============================================================================

/** @brief On-board USER LED pin (connected to digital pin 13) */
#define PINOO_MOTO_INTERNAL_LED       13

/** @brief On-board Passive Buzzer pin (connected to digital pin 8) */
#define PINOO_MOTO_INTERNAL_BUZZER    8

/** @brief On-board WS2812 RGB LED pin (connected to digital pin 9 / NeoPixel chain) */
#define PINOO_MOTO_INTERNAL_RGB       9

/** @brief On-board Infrared Receiver (IR-R) (Not supported on Pinoo Moto) */
#define PINOO_MOTO_INTERNAL_IR        -1

/** @brief On-board USER BUTTON (Not supported on Pinoo Moto) */
#define PINOO_MOTO_INTERNAL_BUTTON    -1

/** @brief On-board LDR light sensor (Not supported on Pinoo Moto) */
#define PINOO_MOTO_INTERNAL_LDR       -1


// =============================================================================
// Single Jumper Pins
// =============================================================================
#define PINOO_MOTO_JUMPER_A0          A0
#define PINOO_MOTO_JUMPER_A1          A1
#define PINOO_MOTO_JUMPER_A2          A2
#define PINOO_MOTO_JUMPER_A3          A3

#define PINOO_MOTO_JUMPER_D2          2
#define PINOO_MOTO_JUMPER_D3          3
#define PINOO_MOTO_JUMPER_D4          4
#define PINOO_MOTO_JUMPER_D5          5
#define PINOO_MOTO_JUMPER_D6          6
#define PINOO_MOTO_JUMPER_D7          7


// =============================================================================
// RJ11 Ports Matrix (Digital & Analog Interfaces)
// =============================================================================

// Port 1 (Purple/Green) -> Pin 4: D13, Pin 2: D12
#define PINOO_MOTO_PORT1_PIN4         12
#define PINOO_MOTO_PORT1_PIN2         13

// Port 2 (Purple/Green) -> Pin 4: D11 (PWM), Pin 2: D10 (PWM)
#define PINOO_MOTO_PORT2_PIN4         10
#define PINOO_MOTO_PORT2_PIN2         11

// Port 3 (Red/Yellow) -> Pin 4: A7 (Analog-only), Pin 2: A6 (Analog-only)
#define PINOO_MOTO_PORT3_PIN4         A6
#define PINOO_MOTO_PORT3_PIN2         A7

// Port 4 (Red/White) -> Pin 4: A4 (SDA), Pin 2: A5 (SCL) [Hardware I2C]
#define PINOO_MOTO_PORT4_PIN4         A4
#define PINOO_MOTO_PORT4_PIN2         A5

// =============================================================================
// RJ11 Port Compile-Time Type-Safe Abstraction System
// =============================================================================

struct PinooMotoDoor1 {
    static constexpr uint8_t pin4 = PINOO_MOTO_PORT1_PIN4;
    static constexpr uint8_t pin2 = PINOO_MOTO_PORT1_PIN2;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor2 {
    static constexpr uint8_t pin4 = PINOO_MOTO_PORT2_PIN4;
    static constexpr uint8_t pin2 = PINOO_MOTO_PORT2_PIN2;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor3 {
    static constexpr uint8_t pin4 = PINOO_MOTO_PORT3_PIN4;
    static constexpr uint8_t pin2 = PINOO_MOTO_PORT3_PIN2;
    static constexpr bool is_digital = false; // A6/A7 are input-only analog on ATmega328p
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor4 {
    static constexpr uint8_t pin4 = PINOO_MOTO_PORT4_PIN4;
    static constexpr uint8_t pin2 = PINOO_MOTO_PORT4_PIN2;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = true;
};

// Dummy definitions for non-existent doors to support generic code compiling
// while triggering type safety static assertion errors if instantiated.
struct PinooMotoDoorDummy {
    static constexpr uint8_t pin4 = 255;
    static constexpr uint8_t pin2 = 255;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

// Global constexpr door objects
constexpr PinooMotoDoor1 DOOR1{};
constexpr PinooMotoDoor2 DOOR2{};
constexpr PinooMotoDoor3 DOOR3{};
constexpr PinooMotoDoor4 DOOR4{};

constexpr PinooMotoDoorDummy DOOR5{};
constexpr PinooMotoDoorDummy DOOR6{};
constexpr PinooMotoDoorDummy DOOR7{};
constexpr PinooMotoDoorDummy DOOR8{};
constexpr PinooMotoDoorDummy DOOR9{};
constexpr PinooMotoDoorDummy DOOR10{};

#endif // PINOO_MOTO_PINS_H
