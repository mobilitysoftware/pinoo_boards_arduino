/**
 * @file Pinoo_Led.h
 * @brief LED module class for controlling LEDs connected to Pinoo boards.
 * 
 * Supports both compile-time validated Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_LED_H
#define PINOO_LED_H

#include <Arduino.h>

#include "../Pinoo_Config.h"

class Pinoo_Led {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_Led(PortType port) {
        PINOO_ASSERT_DIGITAL(PortType);
        _pin = PortType::pin4;
        _state = false;
    }

    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Led(PortType port, bool bypass) {
        _pin = PortType::pin4;
        _state = false;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (e.g., 13).
     */
    Pinoo_Led(uint8_t pin);

    /**
     * @brief Initializes the LED pin mode. Must be called in setup().
     */
    void begin();

    /**
     * @brief Turns the LED on.
     */
    void turnOn();

    /**
     * @brief Turns the LED off.
     */
    void turnOff();

    /**
     * @brief Toggles the LED state.
     */
    void toggle();

    /**
     * @brief Sets the brightness of the LED (using PWM).
     * @param brightness Brightness value from 0 (off) to 255 (fully on).
     */
    void setBrightness(uint8_t brightness);

    /**
     * @brief Checks if the LED is currently on.
     * @return true if the LED is on, false otherwise.
     */
    bool isOn() const;

private:
    uint8_t _pin;
    bool _state;
};

#endif // PINOO_LED_H
