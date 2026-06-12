/**
 * @file Pinoo.h
 * @brief Main umbrella header file for the Pinoo SDK.
 * 
 * Includes board configurations, all component modules, and general I/O helpers.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#ifndef PINOO_H
#define PINOO_H

#include <Arduino.h>
#include "Pinoo_Config.h"

// =============================================================================
// General I/O Helper Interface
// =============================================================================
namespace Pinoo {

    /**
     * @brief Reads digital value from a Pinoo Port.
     * @tparam PortType The structure type of the Pinoo Port.
     * @param port The constexpr Port object (e.g., PORT1).
     * @return HIGH or LOW.
     */
    template <typename PortType>
    inline int digitalRead(PortType port) {
        return ::digitalRead(port.pin4);
    }

    /**
     * @brief Writes digital value to a Pinoo Port.
     * @tparam PortType The structure type of the Pinoo Port.
     * @param port The constexpr Port object (e.g., PORT1).
     * @param value HIGH or LOW.
     */
    template <typename PortType>
    inline void digitalWrite(PortType port, int value) {
        ::digitalWrite(port.pin4, value);
    }

    /**
     * @brief Reads analog value from an analog-capable Pinoo Port.
     * @tparam PortType The structure type of the Pinoo Port.
     * @param port The constexpr Port object (e.g., PORT7).
     * @return Analog value (0 to 1023 on AVR).
     */
    template <typename PortType>
    inline int analogRead(PortType port) {
        PINOO_ASSERT_ANALOG(PortType);
        return ::analogRead(port.pin4);
    }

    /**
     * @brief Writes analog PWM duty cycle to a PWM-capable Pinoo Port.
     * @tparam PortType The structure type of the Pinoo Port.
     * @param port The constexpr Port object (e.g., PORT2).
     * @param value PWM duty cycle (0 to 255).
     */
    template <typename PortType>
    inline void analogWrite(PortType port, int value) {
        PINOO_ASSERT_PWM(PortType);
        ::analogWrite(port.pin4, value);
    }

    // Overloads for raw pins (fallback/advanced use)
    inline int digitalRead(uint8_t pin) { return ::digitalRead(pin); }
    inline void digitalWrite(uint8_t pin, int value) { ::digitalWrite(pin, value); }
    inline int analogRead(uint8_t pin) { return ::analogRead(pin); }
    inline void analogWrite(uint8_t pin, int value) { ::analogWrite(pin, value); }

} // namespace Pinoo

// =============================================================================
// Include Modules
// =============================================================================
#include "modules/Pinoo_Led.h"
#include "modules/Pinoo_Buzzer.h"
#include "modules/Pinoo_Servo.h"
#include "modules/Pinoo_DcMotor.h"
#include "modules/Pinoo_DistanceSensor.h"
#include "modules/Pinoo_WaterSensor.h"
#include "modules/Pinoo_SoilMoisture.h"
#include "modules/Pinoo_Ldr.h"
#include "modules/Pinoo_TempHumidity.h"
#include "modules/Pinoo_Tilt.h"
#include "modules/Pinoo_Pir.h"
#include "modules/Pinoo_Button.h"
#include "modules/Pinoo_Potentiometer.h"
#include "modules/Pinoo_Joystick.h"
#include "modules/Pinoo_Lcd.h"
#include "modules/Pinoo_Bluetooth.h"
#include "modules/Pinoo_LineTracker.h"
#include "modules/Pinoo_RgbLed.h"
#include "modules/Pinoo_IrReceiver.h"

#endif // PINOO_H
