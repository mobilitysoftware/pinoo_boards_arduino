/**
 * @file Pinoo_Bricky_Pins.h
 * @brief Placeholder pin mapping for the Pinoo Bricky board.
 * 
 * NOTE: Pin definitions in this file are placeholders.
 * They will be fully mapped to the physical Pinoo Bricky schematics in a future update.
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_BRICKY_PINS_H
#define PINOO_BRICKY_PINS_H

#include <Arduino.h>

// On-Board Internal Components (Placeholders)
#define PINOO_BRICKY_INTERNAL_LED     13
#define PINOO_BRICKY_INTERNAL_IR      12
#define PINOO_BRICKY_INTERNAL_BUTTON  A7
#define PINOO_BRICKY_INTERNAL_LDR     A6
#define PINOO_BRICKY_INTERNAL_BUZZER  9

// RJ11 Ports Matrix (Placeholders - replicating ONE template for compilation sanity)
struct PinooBrickyPort1 {
    static constexpr uint8_t pin4 = 2;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort2 {
    static constexpr uint8_t pin4 = 3;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort3 {
    static constexpr uint8_t pin4 = 4;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort4 {
    static constexpr uint8_t pin4 = 7;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort5 {
    static constexpr uint8_t pin4 = 8;
    static constexpr uint8_t pin2 = 9;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort6 {
    static constexpr uint8_t pin4 = 12;
    static constexpr uint8_t pin2 = 13;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort7 {
    static constexpr uint8_t pin4 = A0;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort8 {
    static constexpr uint8_t pin4 = A1;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort9 {
    static constexpr uint8_t pin4 = A2;
    static constexpr uint8_t pin2 = A3;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = false;
};

struct PinooBrickyPort10 {
    static constexpr uint8_t pin4 = A4;
    static constexpr uint8_t pin2 = A5;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = true;
};

// Global constexpr port objects mapped to Bricky ports
constexpr PinooBrickyPort1 PORT1{};
constexpr PinooBrickyPort2 PORT2{};
constexpr PinooBrickyPort3 PORT3{};
constexpr PinooBrickyPort4 PORT4{};
constexpr PinooBrickyPort5 PORT5{};
constexpr PinooBrickyPort6 PORT6{};
constexpr PinooBrickyPort7 PORT7{};
constexpr PinooBrickyPort8 PORT8{};
constexpr PinooBrickyPort9 PORT9{};
constexpr PinooBrickyPort10 PORT10{};

#endif // PINOO_BRICKY_PINS_H
