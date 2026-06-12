/**
 * @file Pinoo_IrReceiver.cpp
 * @brief Infrared Receiver (IR-R) module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_IrReceiver.h"

Pinoo_IrReceiver::Pinoo_IrReceiver(uint8_t pin) 
    : _pin(pin), _irrecv(pin) {}

void Pinoo_IrReceiver::begin() {
    _irrecv.enableIRIn(); // Start the receiver timer
}

bool Pinoo_IrReceiver::available() {
    return _irrecv.decode();
}

unsigned long Pinoo_IrReceiver::getCode() {
    return _irrecv.decodedIRData.decodedRawData;
}

void Pinoo_IrReceiver::resume() {
    _irrecv.resume();
}
