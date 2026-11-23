/**
 * @file Pinoo_Errors.h
 * @brief Centralized error message definitions and assertion macros for compile-time validation.
 * 
 * Defines all standard error codes, disclaimers, compiler warnings, and helper macros
 * supporting both safe mode and bypass mode for the Pinoo SDK.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_ERRORS_H
#define PINOO_ERRORS_H

// --- LEGAL DISCLAIMER WARNING FOR GLOBAL BYPASS ---
#ifdef PINOO_BYPASS_SAFETY
    #warning "PINOO WARNING: Safety checks are bypassed globally. Using non-standard port connections may cause physical damage to sensors, actuators, or the Pinoo control board. Pinoo Robotics & Mobility Software accepts no responsibility for hardware damage."
#endif

#if defined(ARDUINO_PINOO_MOTO) || defined(PINOO_BOARD_MOTO)
    // Pinoo Moto has four doors (DOOR1-DOOR4). Messages use the Moto door names.
    #define PINOO_ERR_E01 \
        "PINOO ERROR [E01]: On Pinoo Moto, analog sensors can only be connected to the analog doors (DOOR3 or DOOR4). Digital doors (DOOR1, DOOR2) are not allowed. " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E01.md"

    #define PINOO_ERR_E02 \
        "PINOO ERROR [E02]: On Pinoo Moto, this module needs a dual-signal digital door (DOOR1 or DOOR2). DOOR3 is analog-only and DOOR4 is the I2C bus. " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E02.md"

    #define PINOO_ERR_E03 \
        "PINOO ERROR [E03]: On Pinoo Moto, the LCD Screen must be connected to the I2C door (DOOR4). " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E03.md"

    #define PINOO_ERR_E04 \
        "PINOO ERROR [E04]: On Pinoo Moto, the Joystick requires a door with two analog inputs (DOOR3 or DOOR4). " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E04.md"

    #define PINOO_ERR_E13 \
        "PINOO ERROR [E13]: On Pinoo Moto, digital modules can only be connected to the digital doors (DOOR1 or DOOR2). DOOR3 is analog-only and DOOR4 is the I2C bus. " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E13.md"

    #define PINOO_ERR_E14 \
        "PINOO ERROR [E14]: On Pinoo Moto, servo motors connect to the motor driver channels, not to doors. Use Pinoo_Servo(channel) with a channel number from 0 to 15. " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E14.md"
#else
    #define PINOO_ERR_E01 \
        "PINOO ERROR [E01]: Analog sensors can only be connected to analog ports (Port 7, Port 8, Port 9, or Port 10). Digital ports (Ports 1-6) are not allowed. " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E01.md"

    #define PINOO_ERR_E02 \
        "PINOO ERROR [E02]: The selected module requires a Dual-Signal port (Port 5, Port 6, Port 9, or Port 10). " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E02.md"

    #define PINOO_ERR_E03 \
        "PINOO ERROR [E03]: LCD Screen must be connected to the hardware I2C port (Port 10). " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E03.md"

    #define PINOO_ERR_E04 \
        "PINOO ERROR [E04]: Joystick requires a port with two analog inputs (Port 9 or Port 10). " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E04.md"

    #define PINOO_ERR_E13 \
        "PINOO ERROR [E13]: Digital modules can only be connected to digital ports (Port 1, Port 2, Port 3, Port 4, Port 5, or Port 6). Analog ports (Ports 7-10) are not allowed. " \
        "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E13.md"
#endif

#define PINOO_ERR_E12 \
    "PINOO ERROR [E12]: Pinoo::analogWrite requires a PWM-capable port (Port 2 or Port 5). " \
    "For support visit: https://github.com/mobilitysoftware/pinoo_boards_arduino/blob/main/errors/E12.md"

#ifndef PINOO_ERR_E14
    #define PINOO_ERR_E14 "PINOO ERROR [E14]: This error only applies to Pinoo Moto."
#endif

// --- COMPILE-TIME ASSERTION HELPER MACROS ---
#ifdef PINOO_BYPASS_SAFETY
    #define PINOO_ASSERT_ANALOG(PortType)   static_assert(true, "")
    #define PINOO_ASSERT_DUAL(PortType)     static_assert(true, "")
    #define PINOO_ASSERT_I2C(PortType)      static_assert(true, "")
    #define PINOO_ASSERT_JOYSTICK(PortType) static_assert(true, "")
    #define PINOO_ASSERT_PWM(PortType)      static_assert(true, "")
    #define PINOO_ASSERT_DIGITAL(PortType)  static_assert(true, "")
#else
    #define PINOO_ASSERT_ANALOG(PortType)   static_assert(PortType::is_analog, PINOO_ERR_E01)
    #define PINOO_ASSERT_DUAL(PortType)     static_assert(PortType::is_dual, PINOO_ERR_E02)
    #define PINOO_ASSERT_I2C(PortType)      static_assert(PortType::is_i2c, PINOO_ERR_E03)
    #define PINOO_ASSERT_JOYSTICK(PortType) static_assert(PortType::has_dual_analog, PINOO_ERR_E04)
    #define PINOO_ASSERT_PWM(PortType)      static_assert(PortType::is_pwm, PINOO_ERR_E12)
    #define PINOO_ASSERT_DIGITAL(PortType)  static_assert(PortType::is_digital, PINOO_ERR_E13)
#endif

#endif // PINOO_ERRORS_H
