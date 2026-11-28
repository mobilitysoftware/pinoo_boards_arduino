/**
 * @file Pinoo_LineTracker.h
 * @brief Dual-channel (left/right) analog Line Tracking sensor module class.
 * 
 * The Pinoo Line Tracker module has two ANALOG outputs (left and right reflective
 * IR sensors), so it connects to a door with two analog inputs (same as the Joystick),
 * e.g. DOOR3 on Pinoo Moto. Supports compile-time validated Port structures and raw pin numbers.
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
     * @param port The constexpr Port instance with two analog inputs (e.g., DOOR3 on Pinoo Moto).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_LineTracker(PortType port) {
        PINOO_ASSERT_JOYSTICK(PortType);  // two analog inputs required (E04)
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
     * @param leftPin Analog pin connected to left tracking sensor.
     * @param rightPin Analog pin connected to right tracking sensor.
     */
    Pinoo_LineTracker(uint8_t leftPin, uint8_t rightPin);

    /**
     * @brief Initializes the sensor pins. Must be called in setup().
     */
    void begin();

    /**
     * @brief Reads the left sensor analog value.
     * @return Analog value between 0 and 1023. The value for line / background depends on
     *         the surface and sensor height; check it first and tune setThreshold().
     */
    int readLeft();

    /**
     * @brief Reads the right sensor analog value.
     * @return Analog value between 0 and 1023 (see readLeft()).
     */
    int readRight();

    /**
     * @brief Sets the analog threshold used by isOnLineLeft() / isOnLineRight().
     * @param threshold Value between 0 and 1023. Default is 512. A reading above
     *                  the threshold is treated as "over the line".
     */
    void setThreshold(int threshold);

    /**
     * @brief Checks if the left sensor is over the line (reading > threshold).
     * @return true if left sensor detects the line, false otherwise.
     */
    bool isOnLineLeft();

    /**
     * @brief Checks if the right sensor is over the line (reading > threshold).
     * @return true if right sensor detects the line, false otherwise.
     */
    bool isOnLineRight();

private:
    uint8_t _leftPin;
    uint8_t _rightPin;
    int _threshold = 512;
};

#endif // PINOO_LINE_TRACKER_H
