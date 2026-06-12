/**
 * @file Pinoo_TempHumidity.h
 * @brief DHT11 Temperature and Humidity sensor module class.
 * 
 * Supports both compile-time validated digital Port structures and raw pin numbers.
 * Includes a self-contained DHT11 single-wire protocol reader.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_TEMP_HUMIDITY_H
#define PINOO_TEMP_HUMIDITY_H

#include <Arduino.h>
#include "../Pinoo_Config.h"

class Pinoo_TempHumidity {
public:
    /**
     * @brief Constructor for compile-time validated Port connections.
     * @tparam PortType The structure type representing the Pinoo Port.
     * @param port The constexpr Port instance (e.g., PORT1).
     */
    template <typename PortType>
    Pinoo_TempHumidity(PortType port) {
        PINOO_ASSERT_DIGITAL(PortType);
        _pin = PortType::pin4;
    }

    template <typename PortType>
    [[deprecated("PINOO WARNING: Local safety checks bypassed. Non-standard connections can damage hardware. Pinoo Robotics accepts no liability.")]]
    Pinoo_TempHumidity(PortType port, bool bypass) {
        _pin = PortType::pin4;
    }

    /**
     * @brief Constructor for raw Arduino pin connections.
     * @param pin The Arduino pin number (e.g., 2).
     */
    Pinoo_TempHumidity(uint8_t pin);

    /**
     * @brief Initializes the sensor. Must be called in setup().
     */
    void begin();

    /**
     * @brief Performs a sensor read operation.
     * @return true if read was successful and checksum passed, false otherwise.
     */
    bool read();

    /**
     * @brief Returns the last read temperature value.
     * @return Temperature in degrees Celsius (°C).
     */
    float getTemperature();

    /**
     * @brief Returns the last read relative humidity value.
     * @return Relative humidity percentage (%).
     */
    float getHumidity();

private:
    uint8_t _pin;
    float _temperature;
    float _humidity;
    unsigned long _lastReadTime;
    
    // Reads raw 40-bit data from DHT11
    bool readRaw(uint8_t data[5]);
};

#endif // PINOO_TEMP_HUMIDITY_H
