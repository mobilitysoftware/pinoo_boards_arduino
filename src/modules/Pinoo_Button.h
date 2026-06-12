/**
 * @file Pinoo_Button.h
 * @brief Button module class for reading digital button states.
 *
 * Supports both compile-time validated digital Port structures and raw pin numbers.
 * Safely handles analog-only pins (like A6/A7 on ATmega328P) using analog thresholding.
 *
 * ## Active-LOW / Active-HIGH
 * Most physical buttons short the pin to GND when pressed (active-LOW) and rely
 * on an external or internal pull-up to hold the pin HIGH when released.
 * The Pinoo ONE on-board button (A7) is active-LOW but A7 is an analog-only pin
 * on the ATmega328P — it cannot use INPUT_PULLUP. Therefore:
 *   - For analog-only pins the button is read via analogRead() with a threshold.
 *   - The `_activeLow` flag inverts the logic so that isPressed() returns true
 *     only when the pin is actually pulled LOW (i.e., button is pressed).
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
     * @param port     The constexpr Port instance (e.g., DOOR1).
     * @param activeLow true  → button is pressed when pin reads LOW (default, most push-buttons).
     *                  false → button is pressed when pin reads HIGH.
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_Button(PortType port, bool activeLow = true) {
        PINOO_ASSERT_DIGITAL(PortType);
        _pin          = PortType::pin4;
        _activeLow    = activeLow;
        _isAnalogOnly = false;
    }

    /**
     * @brief Constructor for compile-time validated Port connections (bypass mode).
     * @warning Bypasses hardware safety checks. Use only for non-standard wiring.
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Button(PortType port, bool activeLow, bool bypass) {
        _pin          = PortType::pin4;
        _activeLow    = activeLow;
        _isAnalogOnly = false;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin       The Arduino pin number (e.g., 2 or A7).
     * @param activeLow true  → button is pressed when pin reads LOW (default).
     *                  false → button is pressed when pin reads HIGH.
     */
    Pinoo_Button(uint8_t pin, bool activeLow = true);

    /**
     * @brief Initializes the button pin mode. Must be called in setup().
     *
     * For normal digital pins, sets INPUT_PULLUP when activeLow = true, or
     * plain INPUT when activeLow = false.
     * For analog-only pins (A6/A7 on ATmega328P), no pinMode is applied
     * because those pins do not support digital modes at all.
     */
    void begin();

    /**
     * @brief Reads the raw pin state (HIGH or LOW), accounting for analog-only pins.
     * @return HIGH (1) or LOW (0).
     */
    int readValue();

    /**
     * @brief Checks if the button is currently pressed.
     *
     * Automatically accounts for active-LOW / active-HIGH wiring.
     *
     * @return true if pressed, false otherwise.
     */
    bool isPressed();

private:
    uint8_t _pin;           ///< Arduino pin number.
    bool    _activeLow;     ///< true = pressed when LOW, false = pressed when HIGH.
    bool    _isAnalogOnly;  ///< true for A6/A7 on ATmega328P (no digital mode support).
};

#endif // PINOO_BUTTON_H
