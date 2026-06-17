/**
 * @file Pinoo_LineTracker.h
 * @brief Dual-channel Line Tracking sensor module class.
 * 
 * Supports both compile-time validated dual-signal Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_LINE_TRACKER_H
#define PINOO_LINE_TRACKER_H

#include <Arduino.h>

#include "../Pinoo_Config.h"

class Pinoo_LineTracker {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT5).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_LineTracker(PortType port) {
        PINOO_ASSERT_DUAL(PortType);
        _leftPin = PortType::pin4;
        _rightPin = PortType::pin2;
    }

    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_LineTracker(PortType port, bool bypass) {
        _leftPin = PortType::pin4;
        _rightPin = PortType::pin2;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param leftPin Pin connected to left tracking sensor.
     * @param rightPin Pin connected to right tracking sensor.
     */
    Pinoo_LineTracker(uint8_t leftPin, uint8_t rightPin);

    /**
     * @brief Initializes the sensor pins. Must be called in setup().
     */
    void begin();

    /**
     * @brief Reads the left sensor state.
     * @return HIGH (1) if line detected, LOW (0) if not.
     */
    int readLeft();

    /**
     * @brief Reads the right sensor state.
     * @return HIGH (1) if line detected, LOW (0) if not.
     */
    int readRight();

    /**
     * @brief Checks if the left sensor is over the line.
     * @return true if left sensor detects the line, false otherwise.
     */
    bool isOnLineLeft();

    /**
     * @brief Checks if the right sensor is over the line.
     * @return true if right sensor detects the line, false otherwise.
     */
    bool isOnLineRight();

private:
    uint8_t _leftPin;
    uint8_t _rightPin;
};

#endif // PINOO_LINE_TRACKER_H
