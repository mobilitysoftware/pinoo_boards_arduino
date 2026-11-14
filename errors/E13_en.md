# Pinoo Error Troubleshooting - E13

## ❌ Error Message
> **PINOO ERROR [E13]:** Digital modules can only be connected to digital ports (Port 1, Port 2, Port 3, Port 4, Port 5, or Port 6). Analog ports (Ports 7-10) are not allowed.

---

## 🔍 Cause of the Error
This error occurs when you connect digital signal modules—such as a Pinoo LED, Buzzer, Button, PIR Motion Sensor, or Tilt/Shock Sensor—to analog ports like **Port 7, 8, 9, or 10**.

These analog ports are reserved for sensors that output continuous voltage-based readings. Digital modules only produce binary (0 or 1) signals and must be used on designated digital ports on the Pinoo board.

---

## 🛠️ Resolution Steps

1. **Change the Physical Connection:** Plug the module's RJ11 cable into one of the digital ports (**Port 1, Port 2, Port 3, Port 4, Port 5, or Port 6**).
2. **Update the Code Definition:** Change the port parameter in your code's object definition to match the new port.

### Incorrect Code Example
```cpp
#include <Pinoo.h>

// ERROR: LED (digital module) cannot be connected to an analog port (DOOR7)!
Pinoo_Led led(DOOR7); 

void setup() {}
void loop() {}
```

### Correct Code Example
```cpp
#include <Pinoo.h>

// CORRECT: LED module is connected to a digital port (DOOR1).
Pinoo_Led led(DOOR1); 

void setup() {
  led.begin();
}
void loop() {
  led.turnOn();
  delay(1000);
  led.turnOff();
  delay(1000);
}
```

---

## 🔌 Compatible Ports List
To resolve the E13 error, connect the module to any of these digital ports:
* **DOOR1** (Port 1)
* **DOOR2** (Port 2)
* **DOOR3** (Port 3)
* **DOOR4** (Port 4)
* **DOOR5** (Port 5)
* **DOOR6** (Port 6)

---

## 🏎️ Pinoo Moto
Pinoo Moto has four doors (**DOOR1 - DOOR4**). The "Port 5, 6, 9, 10" numbers in the generic message belong to Pinoo ONE. On Pinoo Moto the compiler message already lists the Moto doors.

* **Valid digital doors on Pinoo Moto:** DOOR1, DOOR2
* Digital modules (LED, buzzer, button, PIR, tilt, DHT11, RGB LED) connect to DOOR1 or DOOR2. DOOR3 is analog-only and DOOR4 is the I2C bus.
* See the door map: [Pinoo Moto Docs](https://pinoo-moto.gitbook.io/pinoo-moto/).
