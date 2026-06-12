/**
 * @file Pinoo_Moto_Pins.h
 * @brief Placeholder pin mapping for the Pinoo Moto board.
 * 
 * NOTE: Pin definitions in this file are placeholders.
 * They will be fully mapped to the physical Pinoo Moto schematics in a future update.
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_MOTO_PINS_H
#define PINOO_MOTO_PINS_H

#include <Arduino.h>

// On-Board Internal Components (Placeholders)
#define PINOO_MOTO_INTERNAL_LED     13
#define PINOO_MOTO_INTERNAL_IR      12
#define PINOO_MOTO_INTERNAL_BUTTON  A7
#define PINOO_MOTO_INTERNAL_LDR     A6
#define PINOO_MOTO_INTERNAL_BUZZER  9

// RJ11 Doors Matrix (Placeholders - replicating ONE template for compilation sanity)
struct PinooMotoDoor1 {
    static constexpr uint8_t pin4 = 2;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor2 {
    static constexpr uint8_t pin4 = 3;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor3 {
    static constexpr uint8_t pin4 = 4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor4 {
    static constexpr uint8_t pin4 = 7;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor5 {
    static constexpr uint8_t pin4 = 8;
    static constexpr uint8_t pin2 = 9;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor6 {
    static constexpr uint8_t pin4 = 12;
    static constexpr uint8_t pin2 = 13;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor7 {
    static constexpr uint8_t pin4 = A0;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor8 {
    static constexpr uint8_t pin4 = A1;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor9 {
    static constexpr uint8_t pin4 = A2;
    static constexpr uint8_t pin2 = A3;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = false;
};

struct PinooMotoDoor10 {
    static constexpr uint8_t pin4 = A4;
    static constexpr uint8_t pin2 = A5;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = true;
};

// Global constexpr door objects mapped to Moto doors
constexpr PinooMotoDoor1 DOOR1{};
constexpr PinooMotoDoor2 DOOR2{};
constexpr PinooMotoDoor3 DOOR3{};
constexpr PinooMotoDoor4 DOOR4{};
constexpr PinooMotoDoor5 DOOR5{};
constexpr PinooMotoDoor6 DOOR6{};
constexpr PinooMotoDoor7 DOOR7{};
constexpr PinooMotoDoor8 DOOR8{};
constexpr PinooMotoDoor9 DOOR9{};
constexpr PinooMotoDoor10 DOOR10{};

#endif // PINOO_MOTO_PINS_H
