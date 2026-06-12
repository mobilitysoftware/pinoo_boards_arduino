/**
 * @file Pinoo_Joystick.h
 * @brief Joystick module class for reading dual-axis analog values and click button.
 * 
 * Supports both compile-time validated dual-analog Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_JOYSTICK_H
#define PINOO_JOYSTICK_H

#include <Arduino.h>
#include "../Pinoo_Config.h"

class Pinoo_Joystick {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT9).
     */
    template <typename PortType>
    Pinoo_Joystick(PortType port) {
        PINOO_ASSERT_JOYSTICK(PortType);
        _xPin = PortType::pin4;
        _yPin = PortType::pin2;
        _btnPin = 0;
        _hasButton = false;
    }

    template <typename PortType>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Joystick(PortType port, bool bypass) {
        _xPin = PortType::pin4;
        _yPin = PortType::pin2;
        _btnPin = 0;
        _hasButton = false;
    }

    /**
     * @brief Constructor for raw Arduino pin connections (with optional button).
     * @param xPin The analog pin connected to X axis (e.g., A2).
     * @param yPin The analog pin connected to Y axis (e.g., A3).
     * @param btnPin The digital pin connected to button (optional).
     */
    Pinoo_Joystick(uint8_t xPin, uint8_t yPin, uint8_t btnPin = 0);

    /**
     * @brief Initializes the joystick pins. Must be called in setup().
     */
    void begin();

    /**
     * @brief Reads the X-axis analog value.
     * @return Analog value between 0 and 1023 (centered around ~512).
     */
    int getX();

    /**
     * @brief Reads the Y-axis analog value.
     * @return Analog value between 0 and 1023 (centered around ~512).
     */
    int getY();

    /**
     * @brief Checks if the joystick button is pressed.
     * @return true if pressed, false otherwise (always false if button is not connected).
     */
    bool isButtonPressed();

private:
    uint8_t _xPin;
    uint8_t _yPin;
    uint8_t _btnPin;
    bool _hasButton;
};

#endif // PINOO_JOYSTICK_H
