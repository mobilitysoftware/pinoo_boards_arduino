/**
 * @file Pinoo_ESP32_Pins.h
 * @brief Dedicated pin mappings for the Pinoo ESP32 Shield V1.1 board.
 *
 * This file defines the hardware pin constants for on-board components,
 * the integrated motor driver (L293D), and the 10-port RJ11 matrix of
 * the Pinoo ESP32 Shield V1.1 (ESP32-WROOM-32D).
 *
 * IMPORTANT ESP32-SPECIFIC NOTES:
 *   - GPIO 34, 35, 36, 39 are INPUT-ONLY: no pull-up/pull-down, no output.
 *   - ESP32 ADC is 12-bit (0-4095). The SDK scales this to 10-bit (0-1023)
 *     for cross-platform compatibility. See analogRead() wrappers in Pinoo_Config.h.
 *   - RGB LED and IR Receiver share the same pins as Pinoo ONE (D13 / D12).
 *
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_ESP32_PINS_H
#define PINOO_ESP32_PINS_H

#include <Arduino.h>

// =============================================================================
// On-Board Internal Components
// =============================================================================

/** @brief On-board USER LED pin (GPIO 13) */
#define PINOO_ESP32_INTERNAL_LED       13

/** @brief On-board WS2812 RGB LED (NeoPixel) pin (GPIO 13 — same as Pinoo ONE) */
#define PINOO_ESP32_INTERNAL_RGB       13

/** @brief On-board Infrared Receiver (IR-R) pin (GPIO 12 — same as Pinoo ONE) */
#define PINOO_ESP32_INTERNAL_IR        12

/** @brief On-board USER BUTTON (Not supported on Pinoo ESP32 Shield) */
#define PINOO_ESP32_INTERNAL_BUTTON    -1

/** @brief On-board LDR light sensor (Not supported on Pinoo ESP32 Shield) */
#define PINOO_ESP32_INTERNAL_LDR       -1

/** @brief On-board Passive Buzzer (Not supported on Pinoo ESP32 Shield) */
#define PINOO_ESP32_INTERNAL_BUZZER    -1


// =============================================================================
// Integrated Motor Driver (L293D) Pin Assignments
// =============================================================================

/** @brief Motor 1 — Control line A (GPIO 0) */
#define PINOO_ESP32_MOTOR1_A           0

/** @brief Motor 1 — Control line B (GPIO 2) */
#define PINOO_ESP32_MOTOR1_B           2

/** @brief Motor 2 — Control line A (GPIO 4) */
#define PINOO_ESP32_MOTOR2_A           4

/** @brief Motor 2 — Control line B (GPIO 15) */
#define PINOO_ESP32_MOTOR2_B           15

/** @brief Stepper motor uses the same pins as Motor 1 + Motor 2 (D0, D2, D4, D15) */
#define PINOO_ESP32_STEPPER_A          PINOO_ESP32_MOTOR1_A
#define PINOO_ESP32_STEPPER_B          PINOO_ESP32_MOTOR1_B
#define PINOO_ESP32_STEPPER_C          PINOO_ESP32_MOTOR2_A
#define PINOO_ESP32_STEPPER_D          PINOO_ESP32_MOTOR2_B


// =============================================================================
// RJ11 Ports Matrix — Raw Pin Defines
// =============================================================================

// Port 1  (5V)   -> Pin A: D16 (UART2 RX)
#define PINOO_ESP32_PORT1_PIN_A        16

// Port 2  (5V)   -> Pin A: D17 (UART2 TX)
#define PINOO_ESP32_PORT2_PIN_A        17

// Port 3  (5V)   -> Pin A: D18 (VSPI MOSI), Pin B: D19 (VSPI MISO)
#define PINOO_ESP32_PORT3_PIN_A        18
#define PINOO_ESP32_PORT3_PIN_B        19

// Port 4  (5V)   -> Pin A: D5 (VSPI CS), Pin B: D23 (VSPI MOSI context)
#define PINOO_ESP32_PORT4_PIN_A        5
#define PINOO_ESP32_PORT4_PIN_B        23

// Port 5  (5V)   -> Pin A: D36 (ADC1-CH0), Pin B: D39 (ADC1-CH3) — INPUT ONLY
#define PINOO_ESP32_PORT5_PIN_A        36  // INPUT-ONLY: no output, no pull resistors
#define PINOO_ESP32_PORT5_PIN_B        39  // INPUT-ONLY: no output, no pull resistors

// Port 6  (3V3)  -> Pin A: D27 (ADC2-CH7), Pin B: D14 (ADC2-CH6)
#define PINOO_ESP32_PORT6_PIN_A        27
#define PINOO_ESP32_PORT6_PIN_B        14

// Port 7  (5V)   -> Pin A: D25 (ADC2-CH8 / DAC1), Pin B: D26 (ADC2-CH9 / DAC2)
#define PINOO_ESP32_PORT7_PIN_A        25
#define PINOO_ESP32_PORT7_PIN_B        26

// Port 8  (3V3)  -> Pin A: D32 (ADC1-CH4), Pin B: D33 (ADC1-CH5)
#define PINOO_ESP32_PORT8_PIN_A        32
#define PINOO_ESP32_PORT8_PIN_B        33

// Port 9  (5V)   -> Pin A: D34 (ADC1-CH6), Pin B: D35 (ADC1-CH7) — INPUT ONLY
#define PINOO_ESP32_PORT9_PIN_A        34  // INPUT-ONLY: no output, no pull resistors
#define PINOO_ESP32_PORT9_PIN_B        35  // INPUT-ONLY: no output, no pull resistors

// Port 10 (5V)   -> Pin A: D21 (SDA), Pin B: D22 (SCL) — Hardware I2C
#define PINOO_ESP32_PORT10_SDA         21
#define PINOO_ESP32_PORT10_SCL         22


// =============================================================================
// RJ11 Port Compile-Time Type-Safe Abstraction System
// =============================================================================
// Capability flags:
//   is_digital      — pin can be driven HIGH/LOW as output
//   is_analog       — pin can read analog voltage (ADC)
//   is_pwm          — pin supports PWM (LEDC on ESP32)
//   is_dual         — port has two signal pins (pin_a + pin_b)
//   has_dual_analog — both pins of a dual port are ADC-capable
//   is_input_only   — pin cannot be used as output (GPIO 34/35/36/39)
//   is_i2c          — port is wired to hardware I2C (SDA/SCL)
// =============================================================================

// --- Port 1: D16 — Single digital, UART2 RX context ---
struct PinooESP32Door1 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT1_PIN_A;
    static constexpr uint8_t pin_b      = 0;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT1_PIN_A; // legacy alias
    static constexpr uint8_t pin2       = 0;                        // legacy alias
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = false;
    static constexpr bool is_pwm        = true;  // ESP32 LEDC
    static constexpr bool is_dual       = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = false;
};

// --- Port 2: D17 — Single digital, UART2 TX context ---
struct PinooESP32Door2 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT2_PIN_A;
    static constexpr uint8_t pin_b      = 0;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT2_PIN_A;
    static constexpr uint8_t pin2       = 0;
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = false;
    static constexpr bool is_pwm        = true;
    static constexpr bool is_dual       = false;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = false;
};

// --- Port 3: D18 + D19 — Dual digital, VSPI MOSI/MISO context ---
struct PinooESP32Door3 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT3_PIN_A;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT3_PIN_B;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT3_PIN_A;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT3_PIN_B;
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = false;
    static constexpr bool is_pwm        = true;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = false;
};

// --- Port 4: D5 + D23 — Dual digital ---
struct PinooESP32Door4 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT4_PIN_A;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT4_PIN_B;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT4_PIN_A;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT4_PIN_B;
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = false;
    static constexpr bool is_pwm        = true;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = false;
};

// --- Port 5: D36 + D39 — Dual analog, INPUT ONLY (ADC1) ---
struct PinooESP32Door5 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT5_PIN_A;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT5_PIN_B;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT5_PIN_A;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT5_PIN_B;
    static constexpr bool is_digital    = false;
    static constexpr bool is_analog     = true;
    static constexpr bool is_pwm        = false;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_input_only = true;  // GPIO 36 & 39: output not possible
    static constexpr bool is_i2c        = false;
};

// --- Port 6: D27 + D14 — Dual digital+analog (ADC2), 3.3V supply ---
struct PinooESP32Door6 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT6_PIN_A;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT6_PIN_B;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT6_PIN_A;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT6_PIN_B;
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = true;
    static constexpr bool is_pwm        = true;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = false;
};

// --- Port 7: D25 + D26 — Dual digital+analog (ADC2 / DAC) ---
struct PinooESP32Door7 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT7_PIN_A;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT7_PIN_B;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT7_PIN_A;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT7_PIN_B;
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = true;
    static constexpr bool is_pwm        = true;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = false;
};

// --- Port 8: D32 + D33 — Dual digital+analog (ADC1), 3.3V supply ---
struct PinooESP32Door8 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT8_PIN_A;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT8_PIN_B;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT8_PIN_A;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT8_PIN_B;
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = true;
    static constexpr bool is_pwm        = true;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = false;
};

// --- Port 9: D34 + D35 — Dual analog, INPUT ONLY (ADC1) ---
struct PinooESP32Door9 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT9_PIN_A;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT9_PIN_B;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT9_PIN_A;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT9_PIN_B;
    static constexpr bool is_digital    = false;
    static constexpr bool is_analog     = true;
    static constexpr bool is_pwm        = false;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = true;
    static constexpr bool is_input_only = true;  // GPIO 34 & 35: output not possible
    static constexpr bool is_i2c        = false;
};

// --- Port 10: D21 (SDA) + D22 (SCL) — Hardware I2C ---
struct PinooESP32Door10 {
    static constexpr uint8_t pin_a      = PINOO_ESP32_PORT10_SDA;
    static constexpr uint8_t pin_b      = PINOO_ESP32_PORT10_SCL;
    static constexpr uint8_t pin4       = PINOO_ESP32_PORT10_SDA;
    static constexpr uint8_t pin2       = PINOO_ESP32_PORT10_SCL;
    static constexpr bool is_digital    = true;
    static constexpr bool is_analog     = false;
    static constexpr bool is_pwm        = false;
    static constexpr bool is_dual       = true;
    static constexpr bool has_dual_analog = false;
    static constexpr bool is_input_only = false;
    static constexpr bool is_i2c        = true;
};


// =============================================================================
// Global constexpr door objects
// =============================================================================

constexpr PinooESP32Door1  DOOR1{};
constexpr PinooESP32Door2  DOOR2{};
constexpr PinooESP32Door3  DOOR3{};
constexpr PinooESP32Door4  DOOR4{};
constexpr PinooESP32Door5  DOOR5{};
constexpr PinooESP32Door6  DOOR6{};
constexpr PinooESP32Door7  DOOR7{};
constexpr PinooESP32Door8  DOOR8{};
constexpr PinooESP32Door9  DOOR9{};
constexpr PinooESP32Door10 DOOR10{};

#endif // PINOO_ESP32_PINS_H
