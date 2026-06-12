/**
 * @file Pinoo_IrReceiver.h
 * @brief Infrared Receiver (IR-R) module class.
 * 
 * Supports receiving infrared remote control signals.
 * Wraps the standard IRremote library.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_IR_RECEIVER_H
#define PINOO_IR_RECEIVER_H

#include <Arduino.h>
#include <IRremote.hpp>
#include "../Pinoo_Config.h"

class Pinoo_IrReceiver {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     */
    template <typename PortType>
    Pinoo_IrReceiver(PortType port) : _pin(PortType::pin4), _irrecv(PortType::pin4) {
        PINOO_ASSERT_DIGITAL(PortType);
    }

    template <typename PortType>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_IrReceiver(PortType port, bool bypass) : _pin(PortType::pin4), _irrecv(PortType::pin4) {
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (defaults to 12 for internal IR receiver).
     */
    Pinoo_IrReceiver(uint8_t pin = 12);

    /**
     * @brief Initializes the IR receiver. Must be called in setup().
     */
    void begin();

    /**
     * @brief Checks if a new IR code has been received and decoded.
     * @return true if code is available, false otherwise.
     */
    bool available();

    /**
     * @brief Returns the last decoded raw IR code.
     * @return The 32-bit raw decoded value.
     */
    unsigned long getCode();

    /**
     * @brief Resumes receiving the next IR signal packet. Must be called after processing a code.
     */
    void resume();

private:
    uint8_t _pin;
    IRrecv _irrecv;
};

#endif // PINOO_IR_RECEIVER_H
