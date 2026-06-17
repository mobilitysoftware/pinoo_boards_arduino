# Pinoo Error Troubleshooting - E12

## ❌ Error Message
> **PINOO ERROR [E12]:** Pinoo::analogWrite requires a PWM-capable port (Port 2 or Port 5).

---

## 🔍 Cause of the Error
This error is triggered when you call `analogWrite` or use a module requiring Pulse Width Modulation (PWM) signal generation—such as speed control for a DC Motor, brightness control for a LED, or audio frequency control on a Buzzer—on ports other than **Port 2 or Port 5**.

PWM signal generation relies on internal hardware Timers. On Pinoo boards, these hardware timers are only connected to **Port 2 (DOOR2)** and **Port 5 (DOOR5)**.

---

## 🛠️ Resolution Steps

1. **Change the Physical Connection:** Plug the PWM-controlled module's RJ11 cable into **Port 2 (DOOR2)** or **Port 5 (DOOR5)**.
2. **Update the Code Definition:** Change the port parameter in your code's object definition to match the correct port.

### Incorrect Code Example
```cpp
#include <Pinoo.h>

// ERROR: analogWrite (PWM) is not supported on Port 1 (DOOR1).
Pinoo_Led led(DOOR1); 

void setup() {
  led.begin();
}
void loop() {
  // E12 Error: analogWrite requires a PWM-capable port
  led.setBrightness(128); 
}
```

### Correct Code Example
```cpp
#include <Pinoo.h>

// CORRECT: Module is connected to a PWM-capable port (DOOR2).
Pinoo_Led led(DOOR2); 

void setup() {
  led.begin();
}
void loop() {
  led.setBrightness(128); // Successful brightness control!
}
```

---

## 🔌 Compatible Ports List
To resolve the E12 error and use PWM features, connect the module to:
* **DOOR2** (Port 2)
* **DOOR5** (Port 5)
