/**
 * @file Pinoo_Bluetooth.cpp
 * @brief Bluetooth module (HM10) source implementation using Hardware Serial.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_Bluetooth.h"

Pinoo_Bluetooth::Pinoo_Bluetooth() {}

void Pinoo_Bluetooth::begin(long baud) {
    if (!Serial) {
        Serial.begin(baud);
    }
}

int Pinoo_Bluetooth::available() {
    return Serial.available();
}

int Pinoo_Bluetooth::read() {
    return Serial.read();
}

String Pinoo_Bluetooth::readString() {
    String str = Serial.readStringUntil('\n');
    str.trim();
    return str;
}

size_t Pinoo_Bluetooth::write(uint8_t val) {
    return Serial.write(val);
}

void Pinoo_Bluetooth::print(const char* str) {
    Serial.print(str);
}

void Pinoo_Bluetooth::print(const String& str) {
    Serial.print(str);
}

void Pinoo_Bluetooth::println(const String& str) {
    Serial.println(str);
}
