/**
 * @file Pinoo_RgbLed.cpp
 * @brief RGB LED (NeoPixel) module source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_RgbLed.h"

Pinoo_RgbLed::Pinoo_RgbLed(uint8_t pin, uint16_t count) 
    : _strip(count, pin, NEO_GRB + NEO_KHZ800) {}

void Pinoo_RgbLed::begin() {
    _strip.begin();
    clear();
}

void Pinoo_RgbLed::setColor(uint16_t index, uint8_t r, uint8_t g, uint8_t b) {
    _strip.setPixelColor(index, _strip.Color(r, g, b));
    _strip.show();
}

void Pinoo_RgbLed::setColorAll(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = _strip.Color(r, g, b);
    for (uint16_t i = 0; i < _strip.numPixels(); i++) {
        _strip.setPixelColor(i, color);
    }
    _strip.show();
}

void Pinoo_RgbLed::setBrightness(uint8_t brightness) {
    _strip.setBrightness(brightness);
    _strip.show();
}

void Pinoo_RgbLed::clear() {
    _strip.clear();
    _strip.show();
}
