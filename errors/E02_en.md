# Pinoo Error Troubleshooting - E02

## ❌ Error Message
> **PINOO ERROR [E02]:** The selected module requires a Dual-Signal port (Port 5, Port 6, Port 9, or Port 10).

---

## 🔍 Cause of the Error
This error occurs when you connect double-signal modules—such as the Pinoo Ultrasonic Distance Sensor or the Temperature & Humidity Sensor (DHT11)—to single-signal ports like **Port 1, 2, 3, 4, 7, or 8**.

These sensors require two separate microcontroller signal lines (e.g. Trig & Echo or Data & Feedback) to be connected simultaneously, which are only routed to specific ports on the Pinoo board.

---

## 🛠️ Resolution Steps

1. **Change the Physical Connection:** Plug the module's RJ11 cable into one of the dual-signal ports (**Port 5, Port 6, Port 9, or Port 10**).
2. **Update the Code Definition:** Change the port parameter in your code's object definition to match the new port.

### Incorrect Code Example
```cpp
#include <Pinoo.h>

// ERROR: Distance sensor cannot be connected to a single-signal port (DOOR1)!
Pinoo_DistanceSensor distance(DOOR1); 

void setup() {}
void loop() {}
```

### Correct Code Example
```cpp
#include <Pinoo.h>

// CORRECT: Distance sensor is connected to a dual-signal port (DOOR5).
Pinoo_DistanceSensor distance(DOOR5); 

void setup() {
  distance.begin();
}
void loop() {
  int distanceCm = distance.getDistance();
}
```

---

## 🔌 Compatible Ports List
To resolve the E02 error, connect the module to any of these dual-signal ports:
* **DOOR5** (Port 5)
* **DOOR6** (Port 6)
* **DOOR9** (Port 9)
* **DOOR10** (Port 10)
