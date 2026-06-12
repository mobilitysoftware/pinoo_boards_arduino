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

#elif defined(PINOO_BOARD_SHIELD)
    #include "boards/Pinoo_Shield_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_SHIELD_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_SHIELD_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_SHIELD_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_SHIELD_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_SHIELD_INTERNAL_BUZZER

#elif defined(PINOO_BOARD_BRICKY)
    #include "boards/Pinoo_Bricky_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_BRICKY_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_BRICKY_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_BRICKY_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_BRICKY_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_BRICKY_INTERNAL_BUZZER

#elif defined(PINOO_BOARD_MOTO)
    #include "boards/Pinoo_Moto_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_MOTO_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_MOTO_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_MOTO_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_MOTO_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_MOTO_INTERNAL_BUZZER

#else // PINOO_BOARD_ONE or generic fallback
    #include "boards/Pinoo_ONE_Pins.h"
    #define PINOO_INTERNAL_LED     PINOO_ONE_INTERNAL_LED
    #define PINOO_INTERNAL_IR      PINOO_ONE_INTERNAL_IR
    #define PINOO_INTERNAL_BUTTON  PINOO_ONE_INTERNAL_BUTTON
    #define PINOO_INTERNAL_LDR     PINOO_ONE_INTERNAL_LDR
    #define PINOO_INTERNAL_BUZZER  PINOO_ONE_INTERNAL_BUZZER
#endif

#endif // PINOO_CONFIG_H
