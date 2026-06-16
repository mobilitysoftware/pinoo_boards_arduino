/**
 * @file Pinoo_Config.h
 * @brief Architecture & board selection preprocessor logic.
 * 
 * Automatically detects the target microcontroller platform (such as ESP32
 * or standard AVR-based Uno/Nano compatible boards) and loads the corresponding
 * pin mapping definitions. Users can also manually override the selection by
 * defining the target board macro (e.g., PINOO_BOARD_SHIELD) before inclusion.
 * 
 * Supported Boards:
 * - PINOO_BOARD_ONE (Pinoo ONE - Arduino Uno compatible)
 * - PINOO_BOARD_SHIELD (Pinoo Shield - Arduino Nano compatible)
 * - PINOO_BOARD_BRICKY (Pinoo Bricky - Arduino Nano compatible)
 * - PINOO_BOARD_MOTO (Pinoo Moto - Arduino Uno compatible)
 * - PINOO_BOARD_ESP32 (Pinoo ESP32 - ESP32 Dev Module compatible)
 * 
 * @author Pinoo Robotics
 * @copyright Copyright (c) 2026 Pinoo Robotics
 */

#ifndef PINOO_CONFIG_H
#define PINOO_CONFIG_H

#include "Pinoo_Errors.h"

// =============================================================================
// Lightweight Type Traits Helpers (C++11 compatibility fallback for AVR)
// =============================================================================
namespace Pinoo {
    template <bool B, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template <typename T>
    struct is_integral {
        static constexpr bool value = false;
    };

    template <> struct is_integral<bool> { static constexpr bool value = true; };
    template <> struct is_integral<char> { static constexpr bool value = true; };
    template <> struct is_integral<signed char> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned char> { static constexpr bool value = true; };
    template <> struct is_integral<short> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned short> { static constexpr bool value = true; };
    template <> struct is_integral<int> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned int> { static constexpr bool value = true; };
    template <> struct is_integral<long> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned long> { static constexpr bool value = true; };
    template <> struct is_integral<long long> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned long long> { static constexpr bool value = true; };
}

// =============================================================================
// Automatic Architecture & Board Detection
// =============================================================================

// 1. Resolve board selection from compiler board macro flags (-DARDUINO_PINOO_*)
#if defined(ARDUINO_PINOO_ESP32) || defined(PINOO_BOARD_ESP32)
    #ifndef PINOO_BOARD_ESP32
        #define PINOO_BOARD_ESP32
    #endif
#elif defined(ARDUINO_PINOO_SHIELD) || defined(PINOO_BOARD_SHIELD)
    #ifndef PINOO_BOARD_SHIELD
        #define PINOO_BOARD_SHIELD
    #endif
#elif defined(ARDUINO_PINOO_BRICKY) || defined(PINOO_BOARD_BRICKY)
    #ifndef PINOO_BOARD_BRICKY
        #define PINOO_BOARD_BRICKY
    #endif
#elif defined(ARDUINO_PINOO_MOTO) || defined(PINOO_BOARD_MOTO)
    #ifndef PINOO_BOARD_MOTO
        #define PINOO_BOARD_MOTO
    #endif
#elif defined(ARDUINO_PINOO_ONE) || defined(PINOO_BOARD_ONE)
    #ifndef PINOO_BOARD_ONE
        #define PINOO_BOARD_ONE
    #endif
#endif

// 2. Fallback auto-detection if no specific Pinoo board is defined (e.g., using generic Uno/Nano profiles)
#if !defined(PINOO_BOARD_ONE) && !defined(PINOO_BOARD_SHIELD) && !defined(PINOO_BOARD_BRICKY) && !defined(PINOO_BOARD_MOTO) && !defined(PINOO_BOARD_ESP32)
    #if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
        #define PINOO_BOARD_ESP32
    #elif defined(ARDUINO_AVR_NANO)
        // Default Nano-compatible board
        #define PINOO_BOARD_SHIELD
    #elif defined(ARDUINO_AVR_UNO) || defined(__AVR_ATmega328P__)
        // Default Uno-compatible board
        #define PINOO_BOARD_ONE
    #else
        // General fallback
        #define PINOO_BOARD_ONE
    #endif
#endif

// =============================================================================
// Load Pin Definitions & Map Board Components
// =============================================================================

#if defined(PINOO_BOARD_ESP32)
    #include "boards/Pinoo_ESP32_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_ESP32_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_ESP32_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_ESP32_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_ESP32_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_ESP32_INTERNAL_BUZZER
    #define PINOO_INTERNAL_RGB     PINOO_ESP32_INTERNAL_RGB  // GPIO 13 — same pin as Pinoo ONE

#elif defined(PINOO_BOARD_SHIELD)
    #include "boards/Pinoo_Shield_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_SHIELD_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_SHIELD_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_SHIELD_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_SHIELD_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_SHIELD_INTERNAL_BUZZER
    #define PINOO_INTERNAL_RGB     -1

#elif defined(PINOO_BOARD_BRICKY)
    #include "boards/Pinoo_Bricky_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_BRICKY_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_BRICKY_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_BRICKY_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_BRICKY_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_BRICKY_INTERNAL_BUZZER
    #define PINOO_INTERNAL_RGB     -1

#elif defined(PINOO_BOARD_MOTO)
    #include "boards/Pinoo_Moto_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_MOTO_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_MOTO_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_MOTO_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_MOTO_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_MOTO_INTERNAL_BUZZER
    #define PINOO_INTERNAL_RGB     PINOO_MOTO_INTERNAL_RGB

#else // PINOO_BOARD_ONE or generic fallback
    #include "boards/Pinoo_ONE_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_ONE_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_ONE_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_ONE_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_ONE_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_ONE_INTERNAL_BUZZER
    #define PINOO_INTERNAL_RGB     13
#endif

// =============================================================================
// Cross-Platform Analog Read Helper
// =============================================================================
// ESP32 ADC is 12-bit (0-4095). All other Pinoo boards use AVR 10-bit (0-1023).
// PINOO_ANALOG_READ(pin) normalises the result to 10-bit on all platforms so
// that block-based code runs identically regardless of the target architecture.
//
// Usage inside module .cpp files:
//   int value = PINOO_ANALOG_READ(_pin);
// =============================================================================
#if defined(ARDUINO_ARCH_ESP32)
    #define PINOO_ANALOG_READ(pin) (analogRead(pin) >> 2)  // 12-bit -> 10-bit
#else
    #define PINOO_ANALOG_READ(pin) (analogRead(pin))       // AVR native 10-bit
#endif

#endif // PINOO_CONFIG_H
