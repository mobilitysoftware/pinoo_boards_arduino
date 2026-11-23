/**
 * @file Pinoo_Buzzer.h
 * @brief Buzzer module class for controlling active and passive buzzers.
 * 
 * Supports both compile-time validated Port structures and raw pin numbers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_BUZZER_H
#define PINOO_BUZZER_H

#include <Arduino.h>

#include "../Pinoo_Config.h"

/**
 * @brief Buzzer type.
 *
 * - PASSIVE_BUZZER: on-board buzzer (e.g. Pinoo Moto D8). Frequency is controlled with tone().
 * - ACTIVE_BUZZER:  Pinoo external Buzzer module. Has its own oscillator, single fixed tone,
 *                   only on/off.
 * - AUTO_BUZZER:    (default) picks the type from the connection: PINOO_INTERNAL_BUZZER pin
 *                   -> PASSIVE_BUZZER, any Door/Port or other pin -> ACTIVE_BUZZER.
 *
 * AUTO_BUZZER is appended last so the numeric values of the old modes do not change.
 */
enum BuzzerMode {
    PASSIVE_BUZZER,
    ACTIVE_BUZZER,
    AUTO_BUZZER
};

class Pinoo_Buzzer {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     * @param mode Buzzer type (defaults to AUTO_BUZZER: a Door/Port is the external
     *             module, so it resolves to ACTIVE_BUZZER).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_Buzzer(PortType port, BuzzerMode mode = AUTO_BUZZER) : _mode(mode == AUTO_BUZZER ? ACTIVE_BUZZER : mode) {
        PINOO_ASSERT_DIGITAL(PortType);
        _pin = PortType::pin4;
    }

    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_Buzzer(PortType port, bool bypass, BuzzerMode mode = AUTO_BUZZER) : _mode(mode == AUTO_BUZZER ? ACTIVE_BUZZER : mode) {
        _pin = PortType::pin4;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (e.g., PINOO_INTERNAL_BUZZER or 9).
     * @param mode Buzzer type (defaults to AUTO_BUZZER: PINOO_INTERNAL_BUZZER is
     *             PASSIVE_BUZZER, any other pin is ACTIVE_BUZZER).
     */
    Pinoo_Buzzer(uint8_t pin, BuzzerMode mode = AUTO_BUZZER);

    /**
     * @brief Initializes the buzzer pin mode. Must be called in setup().
     */
    void begin();

    /**
     * @brief Turns the buzzer on (for Passive, plays a default 1000Hz frequency).
     */
    void turnOn();

    /**
     * @brief Turns the buzzer off.
     */
    void turnOff();

    /**
     * @brief Plays a tone at a specific frequency.
     * Active buzzer: frequency cannot be changed, so this just turns the buzzer on.
     * @param frequency Tone frequency in Hertz (Hz).
     */
    void playTone(unsigned int frequency);

    /**
     * @brief Plays a tone at a specific frequency for a given duration.
     * Active buzzer: frequency is ignored; the buzzer sounds for @p duration ms
     * and this call blocks until it is finished.
     * @param frequency Tone frequency in Hertz (Hz).
     * @param duration Tone duration in milliseconds.
     */
    void playTone(unsigned int frequency, unsigned long duration);

    /**
     * @brief Stops playing any tone.
     */
    void stop();

private:
    uint8_t _pin;
    BuzzerMode _mode;
};

#endif // PINOO_BUZZER_H
