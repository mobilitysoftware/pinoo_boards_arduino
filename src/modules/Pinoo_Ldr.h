/**
 * @file Pinoo_Ldr.h
 * @brief Light Dependent Resistor (LDR) module class.
 * 
 * Supports both compile-time validated analog Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_LDR_H
#define PINOO_LDR_H

#include <Arduino.h>
#include "../Pinoo_Config.h"

class Pinoo_Ldr {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT7).
     */
    template <typename PortType>
    Pinoo_Ldr(PortType port) {
        PINOO_ASSERT_ANALOG(PortType);
        _pin = PortType::pin4;
    }

    template <typename PortType>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Ldr(PortType port, bool bypass) {
        _pin = PortType::pin4;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino analog pin (e.g., A6).
     */
    Pinoo_Ldr(uint8_t pin);

    /**
     * @brief Initializes the sensor. Must be called in setup().
     */
    void begin();

    /**
     * @brief Reads the raw light value.
     * @return Analog value between 0 and 1023.
     */
    int readValue();

    /**
     * @brief Reads the light level as a percentage.
     * @return Light percentage (0% to 100%).
     */
    int getLightPercentage();

private:
    uint8_t _pin;
};

#endif // PINOO_LDR_H
