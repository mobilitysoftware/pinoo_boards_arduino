# Pinoo Error Troubleshooting - E01

## ❌ Error Message
> **PINOO ERROR [E01]:** Analog sensors can only be connected to analog ports (Port 7, Port 8, Port 9, or Port 10). Digital ports (Ports 1-6) are not allowed.

---

## 🔍 Cause of the Error
This error occurs when you define an analog signal generating module—such as the LDR (Light Sensor), Potentiometer, Soil Moisture Sensor, or Rain/Water Level Sensor—on a digital port (**Port 1, 2, 3, 4, 5, or 6**).

These digital ports lack Analog-to-Digital Converter (ADC) hardware capabilities on the microcontroller, making it impossible to read analog values.

---

## 🛠️ Resolution Steps

1. **Change the Physical Connection:** Plug the sensor's RJ11 cable into one of the green analog ports (**Port 7, Port 8, Port 9, or Port 10**).
2. **Update the Code Definition:** Change the port parameter in your code's object definition to match the new port you plugged it into.

### Incorrect Code Example
```cpp
#include <Pinoo.h>

// ERROR: LDR module cannot be connected to a digital port (DOOR1)!
Pinoo_Ldr ldr(DOOR1); 

void setup() {}
void loop() {}
```

### Correct Code Example
```cpp
#include <Pinoo.h>

// CORRECT: LDR module is connected to an analog port (DOOR7).
Pinoo_Ldr ldr(DOOR7); 

void setup() {
  ldr.begin();
}
void loop() {
  int lightValue = ldr.getValue();
}
```

---

## 🔌 Compatible Ports List
To resolve the E01 error, you can connect the module to any of these analog ports:
* **DOOR7** (Port 7)
* **DOOR8** (Port 8)
* **DOOR9** (Port 9)
* **DOOR10** (Port 10)
