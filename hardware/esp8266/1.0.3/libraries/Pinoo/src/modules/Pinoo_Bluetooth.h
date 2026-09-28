/**
 * @file Pinoo_Bluetooth.h
 * @brief Bluetooth module class (HM10). Wraps the hardware Serial communication.
 * 
 * Connected directly to the hardware RX/TX pins of the Pinoo card.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_BLUETOOTH_H
#define PINOO_BLUETOOTH_H

#include <Arduino.h>

class Pinoo_Bluetooth {
public:
    /**
     * @brief Constructor for Pinoo_Bluetooth. No port required.
     */
    Pinoo_Bluetooth();

    /**
     * @brief Initializes the Bluetooth module communication. Must be called in setup().
     * @param baud Baud rate for Serial communication (defaults to 9600 for HM10).
     */
    void begin(long baud = 9600);

    /**
     * @brief Checks if data is available to be read.
     * @return Number of bytes available to read.
     */
    int available();

    /**
     * @brief Reads a character from the Bluetooth module.
     * @return The read character, or -1 if no data is available.
     */
    int read();

    /**
     * @brief Reads a string from the Bluetooth module until a newline is received.
     * @return The read string.
     */
    String readString();

    /**
     * @brief Writes a single character to the Bluetooth module.
     * @param val Character to write.
     * @return Number of bytes written.
     */
    size_t write(uint8_t val);

    /**
     * @brief Prints text to the Bluetooth module.
     * @param str Null-terminated string.
     */
    void print(const char* str);

    /**
     * @brief Prints a string to the Bluetooth module.
     * @param str String object.
     */
    void print(const String& str);

    /**
     * @brief Prints a line of text to the Bluetooth module (with newline).
     * @param str String object.
     */
    void println(const String& str);
};

#endif // PINOO_BLUETOOTH_H
