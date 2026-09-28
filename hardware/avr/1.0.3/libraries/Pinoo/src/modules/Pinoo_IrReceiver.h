/**
 * @file Pinoo_IrReceiver.h
 * @brief Infrared Receiver (IR-R) module class.
 *
 * Supports receiving infrared remote control signals via the IRremote library.
 *
 * ## IRremote / "multiple definition" isolation
 *
 * IRremote (v3.x) is a header-only library: including IRremote.hpp in any
 * translation unit compiles ALL of its function bodies (ISR, globals, decoders,
 * sender methods, etc.) into that object file.  If two translation units both
 * include IRremote.hpp the linker sees every symbol twice → "multiple definition".
 *
 * To prevent this, this header does NOT include IRremote.hpp at all.
 * Instead, it uses a PIMPL (Pointer-to-Implementation) pattern:
 *   - The private implementation struct (PinooIrImpl) is only forward-declared
 *     here; its definition lives in Pinoo_IrReceiver.cpp alongside IRremote.hpp.
 *   - Heap allocation (new/delete) is avoided: the impl lives in a raw-byte
 *     buffer whose size is validated at compile time in the .cpp.
 *
 * Result: IRremote.hpp is compiled EXACTLY ONCE (in Pinoo_IrReceiver.cpp).
 * No other translation unit, including the user's sketch, ever sees IRremote.hpp
 * through this header.
 *
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_IR_RECEIVER_H
#define PINOO_IR_RECEIVER_H

#include <Arduino.h>
#include "../Pinoo_Config.h"

// ---------------------------------------------------------------------------
// Storage size of the PIMPL buffer.
// IRrecv on AVR (2-byte pointers) holds:
//   IRData (protocol + address + command + extra + numberOfBits + flags +
//           decodedRawData + decodedRawDataArray[2] + *rawDataPtr)
//     ≈ 26 bytes + padding
//   plus: lastDecodedProtocol, lastDecodedAddress, lastDecodedCommand, repeatCount
//     ≈ 10 bytes
// Total on AVR  : ~36–44 bytes (2-byte pointers).
// Total on ESP32: ~64–96 bytes (4-byte pointers, larger IRData struct).
// 128 bytes gives comfortable headroom on both architectures.
// A static_assert in Pinoo_IrReceiver.cpp validates the actual size at build time.
// ---------------------------------------------------------------------------
#define PINOO_IRRECV_BUF_SIZE 1024

class Pinoo_IrReceiver {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., DOOR1).
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    Pinoo_IrReceiver(PortType port) : _pin(PortType::pin4) {
        PINOO_ASSERT_DIGITAL(PortType);
        _init();
    }

    /**
     * @brief Constructor for compile-time validated Port connections (bypass mode).
     * @warning Bypasses hardware safety checks. Use only for non-standard wiring.
     */
    template <typename PortType, typename = typename Pinoo::enable_if<!Pinoo::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_IrReceiver(PortType port, bool bypass) : _pin(PortType::pin4) {
        _init();
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (defaults to 12 for the internal IR receiver).
     */
    explicit Pinoo_IrReceiver(uint8_t pin = PINOO_INTERNAL_IR);

    ~Pinoo_IrReceiver();

    /**
     * @brief Initializes the IR receiver. Must be called in setup().
     */
    void begin();

    /**
     * @brief Checks if a new IR code has been received and decoded.
     * @return true if a code is available, false otherwise.
     */
    bool available();

    /**
     * @brief Returns the last decoded raw IR code.
     * @return The 32-bit raw decoded value.
     */
    unsigned long getCode();

    /**
     * @brief Resumes receiving the next IR signal packet.
     *        Must be called after processing a code.
     */
    void resume();

private:
    uint8_t _pin; ///< The Arduino pin connected to the IR receiver signal line.

    // Raw storage for the IRrecv object — avoids including IRremote.hpp here.
    // The actual IRrecv object is placement-new'd into this buffer in the .cpp.
    alignas(void*) uint8_t _irrecvBuf[PINOO_IRRECV_BUF_SIZE];

    void _init(); ///< Placement-constructs the IRrecv object in _irrecvBuf.
};

#endif // PINOO_IR_RECEIVER_H
