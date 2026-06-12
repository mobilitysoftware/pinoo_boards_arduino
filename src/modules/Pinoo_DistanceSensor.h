/**
 * @file Pinoo_DistanceSensor.h
 * @brief HC-SR04 Ultrasonic Distance Sensor module class.
 * 
 * Supports both compile-time validated dual-signal Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_DISTANCE_SENSOR_H
#define PINOO_DISTANCE_SENSOR_H

#include <Arduino.h>
#include <type_traits>
#include "../Pinoo_Config.h"

class Pinoo_DistanceSensor {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT5).
     */
    template <typename PortType, typename = typename std::enable_if<!std::is_integral<PortType>::value>::type>
    Pinoo_DistanceSensor(PortType port) {
        PINOO_ASSERT_DUAL(PortType);
        _trigPin = PortType::pin4;
        _echoPin = PortType::pin2;
    }

    template <typename PortType, typename = typename std::enable_if<!std::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_DistanceSensor(PortType port, bool bypass) {
        _trigPin = PortType::pin4;
        _echoPin = PortType::pin2;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param trigPin Trigger pin of HC-SR04.
     * @param echoPin Echo pin of HC-SR04.
     */
    Pinoo_DistanceSensor(uint8_t trigPin, uint8_t echoPin);

    /**
     * @brief Initializes the sensor pins. Must be called in setup().
     */
    void begin();

    /**
     * @brief Measures and returns the distance in centimeters.
     * @return Distance in centimeters (cm) as a float.
     */
    float getDistance();

private:
    uint8_t _trigPin;
    uint8_t _echoPin;
};

#endif // PINOO_DISTANCE_SENSOR_H
