/**
 * @file Pinoo_IrReceiver.cpp
 * @brief Infrared Receiver (IR-R) module source implementation.
 *
 * ## Why IRremote.hpp is included ONLY here
 *
 * IRremote (v3.x) is a "single compilation unit" library: every function body
 * is defined in .hpp files that are included by IRremote.hpp.  Including
 * IRremote.hpp in more than one .cpp file means the linker sees each symbol
 * (irparams, FeedbackLEDControl, every IRrecv/IRsend method, etc.) defined
 * multiple times → "multiple definition" link errors.
 *
 * This file is the SOLE translation unit that includes IRremote.hpp.
 * Pinoo_IrReceiver.h uses a PIMPL byte-buffer pattern so that IRrecv never
 * appears in the public header, keeping all other translation units (including
 * the user's sketch) completely isolated from IRremote.
 *
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

// Include the full IRremote implementation FIRST and ONLY in this file.
#include <IRremote.hpp>

#include "Pinoo_IrReceiver.h"

// ---------------------------------------------------------------------------
// Placement new for AVR
// ---------------------------------------------------------------------------
// AVR-GCC does not provide <new>, so placement new (operator new(size_t, void*))
// is not available by default. We define it here — it is a no-op that simply
// returns the provided pointer, which is exactly what placement new must do.
// Defining it here keeps the definition in exactly one TU (this file).
// ---------------------------------------------------------------------------
#if defined(__AVR__)
#ifndef PINOO_PLACEMENT_NEW_DEFINED
#define PINOO_PLACEMENT_NEW_DEFINED
inline void* operator new(size_t, void* ptr) noexcept { return ptr; }
inline void  operator delete(void*, void*) noexcept {}  // required companion
#endif
#endif

// Validate that the PIMPL buffer declared in the header is large enough.
// If this assertion fires, increase PINOO_IRRECV_BUF_SIZE in Pinoo_IrReceiver.h.
static_assert(sizeof(IRrecv) <= PINOO_IRRECV_BUF_SIZE,
    "PINOO_IRRECV_BUF_SIZE is too small for IRrecv — increase it in Pinoo_IrReceiver.h");

// ---------------------------------------------------------------------------
// Helper: access the IRrecv object living in the byte buffer
// ---------------------------------------------------------------------------
static inline IRrecv* asIrRecv(uint8_t* buf) {
    return reinterpret_cast<IRrecv*>(buf);
}

// ---------------------------------------------------------------------------
// Private init — placement-constructs IRrecv into the aligned buffer
// ---------------------------------------------------------------------------
void Pinoo_IrReceiver::_init() {
    new (_irrecvBuf) IRrecv(_pin);
}

// ---------------------------------------------------------------------------
// Constructors / Destructor
// ---------------------------------------------------------------------------
Pinoo_IrReceiver::Pinoo_IrReceiver(uint8_t pin)
    : _pin(pin) {
    _init();
}

Pinoo_IrReceiver::~Pinoo_IrReceiver() {
    asIrRecv(_irrecvBuf)->~IRrecv();
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
void Pinoo_IrReceiver::begin() {
    asIrRecv(_irrecvBuf)->enableIRIn();
}

bool Pinoo_IrReceiver::available() {
    return asIrRecv(_irrecvBuf)->decode();
}

unsigned long Pinoo_IrReceiver::getCode() {
    return asIrRecv(_irrecvBuf)->decodedIRData.decodedRawData;
}

void Pinoo_IrReceiver::resume() {
    asIrRecv(_irrecvBuf)->resume();
}
