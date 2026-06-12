/**
 * @file Pinoo_Button.h
 * @brief Button module class for reading digital button states.
 * 
 * Supports both compile-time validated digital Port structures and raw pin numbers.
 * Safely handles analog-only pins (like A6/A7 on ATmega328P) using analog thresholding.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_BUTTON_H
#define PINOO_BUTTON_H

#include <Arduino.h>
#include "../Pinoo_Config.h"

class Pinoo_Button {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     */
    template <typename PortType>
    Pinoo_Button(PortType port) {
        PINOO_ASSERT_DIGITAL(PortType);
        _pin = PortType::pin4;
        _isAnalogOnly = false;
    }

    template <typename PortType>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Button(PortType port, bool bypass) {
        _pin = PortType::pin4;
        _isAnalogOnly = false;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (e.g., 2 or A7).
     */
    Pinoo_Button(uint8_t pin);

    /**
     * @brief Initializes the button pin mode. Must be called in setup().
     */
    void begin();

    /**
     * @brief Reads the button state.
     * @return HIGH (1) if pressed, LOW (0) if not pressed.
     */
    int readValue();

    /**
     * @brief Checks if the button is pressed.
     * @return true if pressed, false otherwise.
     */
    bool isPressed();

private:
    uint8_t _pin;
    bool _isAnalogOnly;
};

#endif // PINOO_BUTTON_H
