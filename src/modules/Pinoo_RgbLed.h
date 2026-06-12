/**
 * @file Pinoo_RgbLed.h
 * @brief RGB LED (NeoPixel) module class.
 * 
 * Supports controlling individual and chained RGB LEDs connected to Pinoo boards.
 * Wraps the Adafruit_NeoPixel library under the hood.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_RGB_LED_H
#define PINOO_RGB_LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <type_traits>
#include "../Pinoo_Config.h"

class Pinoo_RgbLed {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     * @param count Number of RGB LEDs in the chain (defaults to 2 for on-board RGB).
     */
    template <typename PortType, typename = typename std::enable_if<!std::is_integral<PortType>::value>::type>
    Pinoo_RgbLed(PortType port, uint16_t count = 2) 
        : _strip(count, PortType::pin4, NEO_GRB + NEO_KHZ800) {
        PINOO_ASSERT_DIGITAL(PortType);
    }

    template <typename PortType, typename = typename std::enable_if<!std::is_integral<PortType>::value>::type>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_RgbLed(PortType port, bool bypass, uint16_t count = 2) 
        : _strip(count, PortType::pin4, NEO_GRB + NEO_KHZ800) {
    }

    /**
     * @brief Constructor for raw pin and internal RGB LED.
     * @param pin The Arduino pin number (defaults to 13 for internal RGB LED).
     * @param count Number of RGB LEDs in the chain (defaults to 2 for internal RGB).
     */
    Pinoo_RgbLed(uint8_t pin = 13, uint16_t count = 2);

    /**
     * @brief Initializes the RGB LED pin. Must be called in setup().
     */
    void begin();

    /**
     * @brief Sets the color of a specific LED in the chain.
     * @param index 0-based index of the LED.
     * @param r Red intensity (0-255).
     * @param g Green intensity (0-255).
     * @param b Blue intensity (0-255).
     */
    void setColor(uint16_t index, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Sets the color of all LEDs in the chain.
     * @param r Red intensity (0-255).
     * @param g Green intensity (0-255).
     * @param b Blue intensity (0-255).
     */
    void setColorAll(uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Sets the overall brightness of the LEDs.
     * @param brightness Brightness value from 0 (off) to 255 (full).
     */
    void setBrightness(uint8_t brightness);

    /**
     * @brief Clears (turns off) all LEDs in the chain.
     */
    void clear();

private:
    Adafruit_NeoPixel _strip;
};

#endif // PINOO_RGB_LED_H
