/**
 * @file Pinoo_Servo.h
 * @brief Servo motor module class. Wraps the standard Arduino Servo library.
 * 
 * Supports both compile-time validated Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_SERVO_H
#define PINOO_SERVO_H

#include <Arduino.h>
#include <Servo.h>

#include "../Pinoo_Config.h"

class Pinoo_Servo {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_Servo(PortType port) {
        PINOO_ASSERT_DIGITAL(PortType);
        _pin = PortType::pin4;
    }

    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Servo(PortType port, bool bypass) {
        _pin = PortType::pin4;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (e.g., 9).
     */
    Pinoo_Servo(uint8_t pin);

    /**
     * @brief Initializes the servo motor and attaches it to the pin. Must be called in setup().
     */
    void begin();

    /**
     * @brief Writes a value to the servo, controlling the shaft.
     * @param angle The angle in degrees (0 to 180).
     */
    void write(int angle);

    /**
     * @brief Reads the current angle of the servo.
     * @return Current angle (0 to 180 degrees).
     */
    int read();

    /**
     * @brief Detaches the servo motor from its pin.
     */
    void detach();

private:
    uint8_t _pin;
    Servo _servo;
};

#endif // PINOO_SERVO_H
