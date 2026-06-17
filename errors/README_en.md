# Pinoo SDK Error Guide

The Pinoo SDK performs **Compile-Time Safety Checks** to prevent physical damage to your boards and connected sensors or modules caused by incorrect port connections.

If you try to define a module on an incompatible RJ11 port and compile your code, the Arduino IDE will halt compilation and display the relevant error code in the output panel.

Click the error code you encountered in the table below to go to the detailed troubleshooting guide:

## Error Code Table

| Error Code | Description | Troubleshooting Guide |
| :--- | :--- | :--- |
| **E01** | Analog sensors cannot be connected to digital ports (Only Ports 7, 8, 9, 10 are allowed). | [E01_en.md](E01_en.md) |
| **E02** | The selected module requires a Dual-Signal port (Only Ports 5, 6, 9, 10 are allowed). | [E02_en.md](E02_en.md) |
| **E03** | LCD Screen must be connected to the hardware I2C port (Only Port 10 is allowed). | [E03_en.md](E03_en.md) |
| **E04** | Joystick requires a port with two analog inputs (Only Port 9 or 10 are allowed). | [E04_en.md](E04_en.md) |
| **E12** | `analogWrite` requires a PWM-capable port (Only Port 2 or 5 are allowed). | [E12_en.md](E12_en.md) |
| **E13** | Digital modules cannot be connected to analog ports (Only Ports 1, 2, 3, 4, 5, 6 are allowed). | [E13_en.md](E13_en.md) |

---

## ⚠️ Bypassing Safety Checks (Bypass Mode)

In some advanced or custom projects where non-standard port configurations are required, you may want to disable these safety checks.

> [!CAUTION]
> Disabling safety checks means the compiler will no longer warn you about incompatible port connections. Incorrect wiring can cause **physical damage or permanent burn-out** of your board or modules. Hardware failures caused this way are **not covered by warranty**.

To disable the safety mechanism, add `#define PINOO_BYPASS_SAFETY` at the very top of your sketch, before including the Pinoo library:

```cpp
#define PINOO_BYPASS_SAFETY
#include <Pinoo.h>

// Now you can define any module on any port without compile-time errors.
Pinoo_Led led(DOOR9, 1); // This connection would normally cause an error, but it now compiles.
```
