---
trigger: always_on
---

# GROUND TRUTH DATA: PINOO ESP32 SHIELD-V1.1 MAP & ARCHITECTURE

Use this document to implement the hardware abstraction layer (HAL) and pin mapping for the **Pinoo ESP32 Shield-V1.1** board. This board uses a 32-bit Tensilica architecture (ESP32-WROOM-32D module) which requires specific handling for analog resolution (12-bit) and input-only pins.

---

## 1. ON-BOARD INTERNAL COMPONENTS & MOTORS

These components and integrated driver chips are embedded on the main shield:

- **USER LED:** `D13`
- **RGB D13.1 & RGB D13.2:** Connected via `D13` (Typically addressable chain or multiplexed).
- **IR-R (Infrared Receiver):** `D12`
- **INTEGRATED MOTOR DRIVER (L293D style):**
  - **MOTOR-1:** Control lines routed to `D0` and `D2`.
  - **MOTOR-2:** Control lines routed to `D4` and `D15`.
  - **STEPPER:** Combined sequence using `D0`, `D2`, `D15`, `D4`.

---

## 2. RJ11 PORTS MATRIX (PORTS 1 - 10)

Each RJ11 port outputs either 5V or 3.3V alongside two dedicated signal lines. The specific ESP32 GPIO configurations are directly silkscreened on the PCB:

| Port No     | Power | Pin A (Main Signal) | Pin B (Secondary Signal) | Special Architecture Notes / ADC Channels                          |
| :---------- | :---- | :------------------ | :----------------------- | :----------------------------------------------------------------- |
| **Port 1**  | 5V    | **D16**             | _None / NC_              | UART2 RX pin context.                                              |
| **Port 2**  | 5V    | **D17**             | _None / NC_              | UART2 TX pin context.                                              |
| **Port 3**  | 5V    | **D18**             | **D19**                  | VSPI Hardware Pins (MOSI/MISO). Full Digital I/O.                  |
| **Port 4**  | 5V    | **D5**              | **D23**                  | VSPI CS & MOSI context. Full Digital I/O.                          |
| **Port 5**  | 5V    | **D36** (A1-0)      | **D39** (A1-3)           | **CRITICAL:** Input-Only Pins (Sensor Only, no output capability). |
| **Port 6**  | 3V3   | **D27** (A2-7)      | **D14** (A2-6)           | ADC2 Channels. Supports Digital Input/Output & Analog Input.       |
| **Port 7**  | 5V    | **D25** (A2-8)      | **D26** (A2-9)           | ADC2 Channels. Supports Digital Input/Output & Analog Input.       |
| **Port 8**  | 3V3   | **D32** (A1-4)      | **D33** (A1-5)           | ADC1 Channels. Supports Digital Input/Output & Analog Input.       |
| **Port 9**  | 5V    | **D34** (A1-6)      | **D35** (A1-7)           | **CRITICAL:** Input-Only Pins (Sensor Only, no output capability). |
| **Port 10** | 5V    | **D21 (SDA)**       | **D22 (SCL)**            | Hardware I2C Architecture master pins.                             |

---

## 3. SPECIAL DEVELOPMENT CONSIDERATIONS FOR ESP32 SHIELD

### A. Input-Only Restriction (Ports 5 & 9)

- **GPIO 36, 39, 34, 35** lack internal pull-up/pull-down configuration capabilities and **CANNOT** act as OUTPUTs.
- **SDK Action:** If a user tries to initialize an actuator (like a Servo, LED, or Buzzer) on Port 5 or Port 9, the compiler/SDK should drop a warning or fail gracefully. These ports are strictly for incoming sensor data (LDR, Distance, Button, etc.).

### B. Analog Resolution

- Standard Arduino (AVR) uses 10-bit analog read (`0-1023`). ESP32 uses 12-bit (`0-4095`).
- **SDK Action:** The core SDK abstraction layer must automatically scale analog readings using an internal architecture check to keep behaviors consistent across all Pinoo platforms:

```cpp
  #if defined(ARDUINO_ARCH_ESP32)
      int raw = analogRead(pin);
      return (raw >> 2); // Scales 12-bit down to 10-bit for block compatibility
  #endif

4. CODE GEN TARGETS FOR ANTIGRAVITY
Task 1: Create src/boards/Pinoo_ESP32_Pins.h
Generate the target architecture macros when PINOO_BOARD_ESP32 is flagged:

#ifndef PINOO_ESP32_PINS_H
#define PINOO_ESP32_PINS_H

// --- ON-BOARD COMPONENTS ---
#define PINOO_ESP32_USER_LED       13
#define PINOO_ESP32_IR_RECEIVER    12

// --- RJ11 PORTS CONFIGURATION ---
#define PINOO_ESP32_PORT1_PIN_A    16
#define PINOO_ESP32_PORT2_PIN_A    17

#define PINOO_ESP32_PORT3_PIN_A    18
#define PINOO_ESP32_PORT3_PIN_B    19

#define PINOO_ESP32_PORT4_PIN_A    5
#define PINOO_ESP32_PORT4_PIN_B    23

#define PINOO_ESP32_PORT5_PIN_A    36 // INPUT ONLY
#define PINOO_ESP32_PORT5_PIN_B    39 // INPUT ONLY

#define PINOO_ESP32_PORT6_PIN_A    27
#define PINOO_ESP32_PORT6_PIN_B    14

#define PINOO_ESP32_PORT7_PIN_A    25
#define PINOO_ESP32_PORT7_PIN_B    26

#define PINOO_ESP32_PORT8_PIN_A    32
#define PINOO_ESP32_PORT8_PIN_B    33

#define PINOO_ESP32_PORT9_PIN_A    34 // INPUT ONLY
#define PINOO_ESP32_PORT9_PIN_B    35 // INPUT ONLY

#define PINOO_ESP32_PORT10_SDA     21 // I2C
#define PINOO_ESP32_PORT10_SCL     22 // I2C

// --- ONBOARD MOTOR REGISTERS ---
#define PINOO_ESP32_MOTOR1_A       0
#define PINOO_ESP32_MOTOR1_B       2
#define PINOO_ESP32_MOTOR2_A       4
#define PINOO_ESP32_MOTOR2_B       15

#endif // PINOO_ESP32_PINS_H

Task 2: Implement Guard Logic inside src/Pinoo_Config.h
Ensure that the build flags intercept ARDUINO_ARCH_ESP32 to inject these registers over the classic AVR macros.
```
