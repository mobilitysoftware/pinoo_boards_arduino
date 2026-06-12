/**
 * @file Pinoo_Tilt.h
 * @brief Tilt and Vibration Sensor module class.
 * 
 * Supports both compile-time validated digital Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_TILT_H
#define PINOO_TILT_H

#include <Arduino.h>
#include <type_traits>
#include "../Pinoo_Config.h"

class Pinoo_Tilt {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     */
    template <typename PortType, typename = typename std::enable_if<!std::is_integral<PortType>::value>::type>
    Pinoo_Tilt(PortType port) {
        PINOO_ASSERT_DIGITAL(PortType);
        _pin = PortType::pin4;
    }

    template <typename PortType, typename = typename std::enable_if<!std::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Tilt(PortType port, bool bypass) {
        _pin = PortType::pin4;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (e.g., 2).
     */
    Pinoo_Tilt(uint8_t pin);

    /**
     * @brief Initializes the sensor. Must be called in setup().
     */
    void begin();

    /**
     * @brief Reads the digital state of the sensor.
     * @return HIGH or LOW.
     */
    int readValue();

    /**
     * @brief Checks if the sensor is tilted or vibrated.
     * @return true if tilt/vibration detected, false otherwise.
     */
    bool isTilted();

private:
    uint8_t _pin;
};

#endif // PINOO_TILT_H
