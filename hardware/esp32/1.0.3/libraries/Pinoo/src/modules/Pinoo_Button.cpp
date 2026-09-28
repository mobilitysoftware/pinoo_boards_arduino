/**
 * @file Pinoo_Button.cpp
 * @brief Button module source implementation.
 *
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Button.h"

// ---------------------------------------------------------------------------
// Constructor — raw pin
// ---------------------------------------------------------------------------
Pinoo_Button::Pinoo_Button(uint8_t pin, bool activeLow)
    : _pin(pin), _activeLow(activeLow)
{
    // A6 and A7 on ATmega328P are analog-only: they have no digital input
    // circuitry and cannot use pinMode() or INPUT_PULLUP.
    // All other platforms treat every pin as capable of digital I/O.
#if defined(__AVR_ATmega328P__) || defined(ARDUINO_AVR_UNO)
    _isAnalogOnly = (pin == A6 || pin == A7);
#else
    _isAnalogOnly = false;
#endif
}

// ---------------------------------------------------------------------------
// begin()
// ---------------------------------------------------------------------------
void Pinoo_Button::begin() {
    if (_isAnalogOnly) {
        // A6/A7: no pinMode — the pin is always in analog-input mode.
        // An external pull-up resistor on the PCB holds the line HIGH when
        // the button is open; pressing shorts it to GND (analog value → 0).
        return;
    }

    if (_activeLow) {
        // Internal pull-up keeps the pin HIGH at rest; button pulls it LOW.
        pinMode(_pin, INPUT_PULLUP);
    } else {
        // External pull-down or active-HIGH source; no internal pull-up needed.
        pinMode(_pin, INPUT);
    }
}

// ---------------------------------------------------------------------------
// readValue() — returns HIGH or LOW
// ---------------------------------------------------------------------------
int Pinoo_Button::readValue() {
    if (_isAnalogOnly) {
        // Threshold: values < 100 (close to GND) = LOW (button pressed on active-LOW).
        // The Pinoo ONE on-board button pulls A7 toward 0 V when pressed.
        // analogRead range is 0–1023; we use 100 as a conservative LOW threshold.
        return (analogRead(_pin) < 100) ? LOW : HIGH;
    }
    return digitalRead(_pin);
}

// ---------------------------------------------------------------------------
// isPressed() — accounts for active-LOW / active-HIGH wiring
// ---------------------------------------------------------------------------
bool Pinoo_Button::isPressed() {
    int raw = readValue();
    // active-LOW: pressed   → pin LOW  → return true
    // active-HIGH: pressed  → pin HIGH → return true
    return _activeLow ? (raw == LOW) : (raw == HIGH);
}
