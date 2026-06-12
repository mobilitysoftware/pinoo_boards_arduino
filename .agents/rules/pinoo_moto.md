---
trigger: always_on
---

# GROUND TRUTH DATA: PINOO MOTO V1.1 MAP & ARCHITECTURE

Use this document to implement the hardware abstraction layer (HAL) and pin mapping for the **Pinoo Moto V1.1** board. This board shares the same 8-bit AVR architecture (ATmega328p) as the Arduino Uno / Pinoo ONE.

---

## 1. ON-BOARD INTERNAL COMPONENTS
These components are directly embedded on the Pinoo Moto PCB:

- **BUZZER (Pasif):** `D9`
- **RGB LED 1:** `D5`
- **RGB LED 2:** `D6`
- **INTEGRATED BLUETOOTH (JDY-23 Module):** Connected via Hardware Serial (`D0/RX` and `D1/TX`).
- **EXTERNAL COMM HEADERS:** - Dedicated socket options for External BT and ESP-01 WiFi modules (share serial/pin interfaces under the hood).

---

## 2. RJ11 PORTS MATRIX (PORTS 1 - 4)
The board breaks out 4 multi-signal RJ11 ports. According to physical trace verification, the pin assignments are:

| Port No | Color Code | Microcontroller Pins | Special Hardware Capabilities |
| :--- | :--- | :--- | :--- |
| **Port 1** | Purple / Green | **D13** & **D12** | Digital I/O, SPI interaction (SCK/MISO) |
| **Port 2** | Purple / Green | **D11** & **D10** | Digital I/O, PWM, SPI interaction (MOSI/SS) |
| **Port 3** | Red / Yellow | **A7** & **A6** | Pure Analog Input (`A6`/`A7` lack digital output capability on AVR) |
| **Port 4** | Red / White | **A5 (SCL)** & **A4 (SDA)** | Hardware I2C Architecture |

---

## 3. MOTOR DRIVER & ACTUATOR MATRIX (TB6612FNG)
The board features **4 onboard TB6612FNG dual DC/Stepper motor drivers**, driving a dense array of 16 Yellow/Red/Black jumper pins. 

### Core Actuator Capabilities:
- Up to **16 Servo Motors** (using individual signal pins mapped from the controller).
- Up to **8 DC Motors** (shared channels).
- Up to **4 Stepper Motors** (utilizing full-bridge drivers).

### CRITICAL HARDWARE CONSTRAINT (Resource Conflict)
The motor pins run on shared internal lines routed from the same TB6612 drivers. 
- **Rule:** If a user configures a driver channel (e.g., Driver 1) to operate a **Stepper Motor**, they **CANNOT** simultaneously use that same channel's pins to control **DC Motors** or specific **Servos** tied to those shared control registers.
- **SDK Action:** The library documentation and class design should prevent/warn against concurrent instantiation of conflicting motor types on the same physical driver block.

---

## 4. CODE GEN TARGETS FOR ANTIGRAVITY

### Task 1: Create `src/boards/Pinoo_MOTO_Pins.h`
Generate the target macro architecture for this board when `PINOO_BOARD_MOTO` is defined:

```cpp
#ifndef PINOO_MOTO_PINS_H
#define PINOO_MOTO_PINS_H

// --- ON-BOARD COMPONENTS ---
#define PINOO_MOTO_BUZZER         9
#define PINOO_MOTO_RGB1           5
#define PINOO_MOTO_RGB2           6

// --- RJ11 PORTS ---
#define PINOO_MOTO_PORT1_PIN_A    13
#define PINOO_MOTO_PORT1_PIN_B    12

#define PINOO_MOTO_PORT2_PIN_A    11
#define PINOO_MOTO_PORT2_PIN_B    10

#define PINOO_MOTO_PORT3_PIN_A    A7 // Analog Only
#define PINOO_MOTO_PORT3_PIN_B    A6 // Analog Only

#define PINOO_MOTO_PORT4_SCL      A5 // I2C
#define PINOO_MOTO_PORT4_SDA      A4 // I2C

// --- MOTOR CONTROLLER MAPPING ---
// Note to AI: Map the internal ATmega328p pins dedicated to the 4 x TB6612 logic 
// (IN1, IN2, PWM channels) based on the standard Pinoo Moto register layouts.

#endif // PINOO_MOTO_PINS_H

Task 2: Update src/Pinoo_Config.h
Integrate conditional compilation logic to route compilation to Pinoo_MOTO_Pins.h if the target hardware configuration flags the Moto board instead of Pinoo ONE.