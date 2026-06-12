/**
 * @file Pinoo_Potentiometer.h
 * @brief Potentiometer module class for reading analog rotary angles.
 * 
 * Supports both compile-time validated analog Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_POTENTIOMETER_H
#define PINOO_POTENTIOMETER_H

#include <Arduino.h>

#include "../Pinoo_Config.h"

class Pinoo_Potentiometer {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT7).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_Potentiometer(PortType port) {
        PINOO_ASSERT_ANALOG(PortType);
        _pin = PortType::pin4;
    }

    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Potentiometer(PortType port, bool bypass) {
        _pin = PortType::pin4;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino analog pin (e.g., A0).
     */
    Pinoo_Potentiometer(uint8_t pin);

    /**
     * @brief Initializes the sensor. Must be called in setup().
     */
    void begin();

    /**
     * @brief Reads the raw analog value of the potentiometer.
     * @return Analog value between 0 and 1023.
     */
    int readValue();

    /**
     * @brief Reads the potentiometer position as a percentage.
     * @return Position percentage (0% to 100%).
     */
    int getValuePercentage();

private:
    uint8_t _pin;
};

#endif // PINOO_POTENTIOMETER_H
