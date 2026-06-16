/**
 * @file Pinoo_ESP32_Pins.h
 * @brief Placeholder pin mapping for the Pinoo ESP32 board.
 * 
 * NOTE: Pin definitions in this file are placeholders.
 * They will be fully mapped to the physical Pinoo ESP32 schematics in a future update.
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_ESP32_PINS_H
#define PINOO_ESP32_PINS_H

#include <Arduino.h>

// On-Board Internal Components (Placeholders)
#define PINOO_ESP32_INTERNAL_LED     2  // Common on-board blue LED for ESP32
#define PINOO_ESP32_INTERNAL_IR      15
#define PINOO_ESP32_INTERNAL_BUTTON  4
#define PINOO_ESP32_INTERNAL_LDR     36
#define PINOO_ESP32_INTERNAL_BUZZER  5

// RJ11 Doors Matrix (Placeholders - replicating ONE template for compilation sanity)
struct PinooESP32Door1 {
    static constexpr uint8_t pin4 = 12;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true; // ESP32 supports PWM on almost all digital pins
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door2 {
    static constexpr uint8_t pin4 = 13;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door3 {
    static constexpr uint8_t pin4 = 14;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door4 {
    static constexpr uint8_t pin4 = 27;
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door5 {
    static constexpr uint8_t pin4 = 26;
    static constexpr uint8_t pin2 = 25;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door6 {
    static constexpr uint8_t pin4 = 33;
    static constexpr uint8_t pin2 = 32;
    static constexpr bool is_digital = true;
    static constexpr bool is_analog = false;
    static constexpr bool is_pwm = true;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door7 {
    static constexpr uint8_t pin4 = 34; // Input-only ADC pin on ESP32
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door8 {
    static constexpr uint8_t pin4 = 35; // Input-only ADC pin on ESP32
    static constexpr uint8_t pin2 = 0;
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door9 {
    static constexpr uint8_t pin4 = 36; // Input-only ADC pin on ESP32
    static constexpr uint8_t pin2 = 39; // Input-only ADC pin on ESP32
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = false;
};

struct PinooESP32Door10 {
    static constexpr uint8_t pin4 = 21; // SDA on ESP32
    static constexpr uint8_t pin2 = 22; // SCL on ESP32
    static constexpr bool is_digital = false;
    static constexpr bool is_analog = true;
    static constexpr bool is_pwm = false;
    static constexpr bool is_dual = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_i2c = true;
};

// Global constexpr door objects mapped to ESP32 doors
constexpr PinooESP32Door1 DOOR1{};
constexpr PinooESP32Door2 DOOR2{};
constexpr PinooESP32Door3 DOOR3{};
constexpr PinooESP32Door4 DOOR4{};
constexpr PinooESP32Door5 DOOR5{};
constexpr PinooESP32Door6 DOOR6{};
constexpr PinooESP32Door7 DOOR7{};
constexpr PinooESP32Door8 DOOR8{};
constexpr PinooESP32Door9 DOOR9{};
constexpr PinooESP32Door10 DOOR10{};

#endif // PINOO_ESP32_PINS_H
