/**
 * @file Pinoo_Shield_Pins.h
 * @brief Placeholder pin mapping for the Pinoo Shield board.
 * 
 * NOTE: Pin definitions in this file are placeholders.
 * They will be fully mapped to the physical Pinoo Shield schematics in a future update.
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_SHIELD_PINS_H
#define PINOO_SHIELD_PINS_H

#include <Arduino.h>

// On-Board Internal Components (Placeholders)
#define PINOO_SHIELD_INTERNAL_LED     13
#define PINOO_SHIELD_INTERNAL_IR      12
#define PINOO_SHIELD_INTERNAL_BUTTON  A7
#define PINOO_SHIELD_INTERNAL_LDR     A6
#define PINOO_SHIELD_INTERNAL_BUZZER  9

// RJ11 Doors Matrix (Placeholders - replicating ONE template for compilation sanity)
struct PinooShieldDoor1 {
    static constexpr uint8_t pin4 = 2;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor2 {
    static constexpr uint8_t pin4 = 3;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor3 {
    static constexpr uint8_t pin4 = 4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor4 {
    static constexpr uint8_t pin4 = 7;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor5 {
    static constexpr uint8_t pin4 = 8;
    static constexpr uint8_t pin2 = 9;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor6 {
    static constexpr uint8_t pin4 = 12;
    static constexpr uint8_t pin2 = 13;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor7 {
    static constexpr uint8_t pin4 = A0;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor8 {
    static constexpr uint8_t pin4 = A1;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor9 {
    static constexpr uint8_t pin4 = A2;
    static constexpr uint8_t pin2 = A3;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = false;
};

struct PinooShieldDoor10 {
    static constexpr uint8_t pin4 = A4;
    static constexpr uint8_t pin2 = A5;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = true;
};

// Global constexpr door objects mapped to Shield doors
constexpr PinooShieldDoor1 DOOR1{};
constexpr PinooShieldDoor2 DOOR2{};
constexpr PinooShieldDoor3 DOOR3{};
constexpr PinooShieldDoor4 DOOR4{};
constexpr PinooShieldDoor5 DOOR5{};
constexpr PinooShieldDoor6 DOOR6{};
constexpr PinooShieldDoor7 DOOR7{};
constexpr PinooShieldDoor8 DOOR8{};
constexpr PinooShieldDoor9 DOOR9{};
constexpr PinooShieldDoor10 DOOR10{};

#endif // PINOO_SHIELD_PINS_H
