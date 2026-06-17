# Pinoo Error Troubleshooting - E04

## ❌ Error Message
> **PINOO ERROR [E04]:** Joystick requires a port with two analog inputs (Port 9 or Port 10).

---

## 🔍 Cause of the Error
The Pinoo Joystick module produces two separate analog values—one for the X-axis and one for the Y-axis. Therefore, it requires a port that exposes **two independent Analog-to-Digital Converter (ADC) input pins** on a single RJ11 connector.

On the Pinoo board, only **Port 9 and Port 10** carry two analog pins. Connecting the Joystick to any other port will trigger this compile-time safety check.

---

## 🛠️ Resolution Steps

1. **Change the Physical Connection:** Plug the Joystick's RJ11 cable into **Port 9 (DOOR9)** or **Port 10 (DOOR10)**.
2. **Update the Code Definition:** Change the port parameter in your code's object definition to match the correct port.

### Incorrect Code Example
```cpp
#include <Pinoo.h>

// ERROR: Joystick cannot be connected to a single analog port (DOOR7)!
Pinoo_Joystick joystick(DOOR7); 

void setup() {}
void loop() {}
```

### Correct Code Example
```cpp
#include <Pinoo.h>

// CORRECT: Joystick is connected to a dual-analog port (DOOR9).
Pinoo_Joystick joystick(DOOR9); 

void setup() {
  joystick.begin();
}
void loop() {
  int xVal = joystick.getX();
  int yVal = joystick.getY();
}
```

---

## 🔌 Compatible Ports List
To resolve the E04 error, plug the module into:
* **DOOR9** (Port 9)
* **DOOR10** (Port 10)
