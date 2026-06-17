# Pinoo Error Troubleshooting - E03

## ❌ Error Message
> **PINOO ERROR [E03]:** LCD Screen must be connected to the hardware I2C port (Port 10).

---

## 🔍 Cause of the Error
This error occurs when you connect modules utilizing the **I2C communication protocol**—such as the Pinoo Character LCD Screen—to any port other than **Port 10 (DOOR10)**.

The I2C protocol requires dedicated hardware Serial Clock (SCL) and Serial Data (SDA) pins. On the Pinoo board, these pins are only routed to **Port 10**.

---

## 🛠️ Resolution Steps

1. **Change the Physical Connection:** Connect the LCD Screen module's RJ11 cable to **Port 10 (DOOR10)**.
2. **Update the Code Definition:** Change the port parameter in your code's object definition to `DOOR10`.

### Incorrect Code Example
```cpp
#include <Pinoo.h>

// ERROR: LCD screen must be connected to Port 10. Port 1 (DOOR1) is not allowed!
Pinoo_Lcd lcd(DOOR1); 

void setup() {}
void loop() {}
```

### Correct Code Example
```cpp
#include <Pinoo.h>

// CORRECT: LCD screen is connected to the hardware I2C port (DOOR10).
Pinoo_Lcd lcd(DOOR10); 

void setup() {
  lcd.begin();
  lcd.print("Hello Pinoo!");
}
void loop() {}
```

---

## 🔌 Compatible Ports List
To resolve the E03 error, the module must be connected to:
* **DOOR10** (Port 10)
