/**
 * @file Pinoo_TempHumidity.cpp
 * @brief DHT11 Temperature and Humidity sensor module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_TempHumidity.h"

Pinoo_TempHumidity::Pinoo_TempHumidity(uint8_t pin) 
    : _pin(pin), _temperature(0.0f), _humidity(0.0f), _lastReadTime(0) {}

void Pinoo_TempHumidity::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

float Pinoo_TempHumidity::getTemperature() {
    read();
    return _temperature;
}

float Pinoo_TempHumidity::getHumidity() {
    read();
    return _humidity;
}

bool Pinoo_TempHumidity::read() {
    unsigned long currentTime = millis();
    // Throttle reads to at least 1.5 seconds intervals to prevent self-heating/timeout
    if (currentTime - _lastReadTime < 1500 && _lastReadTime != 0) {
        return true;
    }

    uint8_t data[5] = {0, 0, 0, 0, 0};
    if (!readRaw(data)) {
        return false;
    }

    // Checksum verification
    if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        return false;
    }

    _humidity = (float)data[0] + (float)data[1] * 0.1f;
    _temperature = (float)data[2] + (float)data[3] * 0.1f;
    _lastReadTime = currentTime;

    return true;
}

bool Pinoo_TempHumidity::readRaw(uint8_t data[5]) {
    // 1. Send start signal
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(20); // Hold low for 20ms

    digitalWrite(_pin, HIGH);
    delayMicroseconds(30);
    pinMode(_pin, INPUT_PULLUP);

    // 2. Read response pulses
    unsigned long timeout = 10000;
    unsigned long start = micros();
    
    while (digitalRead(_pin) == HIGH) {
        if (micros() - start > timeout) return false;
    }
    
    start = micros();
    while (digitalRead(_pin) == LOW) {
        if (micros() - start > timeout) return false;
    }

    start = micros();
    while (digitalRead(_pin) == HIGH) {
        if (micros() - start > timeout) return false;
    }

    // 3. Read 40 bits of data
    for (int i = 0; i < 40; ++i) {
        start = micros();
        while (digitalRead(_pin) == LOW) {
            if (micros() - start > timeout) return false;
        }

        start = micros();
        while (digitalRead(_pin) == HIGH) {
            if (micros() - start > timeout) return false;
        }
        unsigned long highTime = micros() - start;

        int byteIdx = i / 8;
        data[byteIdx] <<= 1;
        if (highTime > 40) { // '0' is ~26-28us, '1' is ~70us
            data[byteIdx] |= 1;
        }
    }

    return true;
}
