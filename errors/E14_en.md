# Pinoo Error Troubleshooting - E14

## ❌ Error Message
> **PINOO ERROR [E14]:** On Pinoo Moto, servo motors connect to the motor driver channels, not to doors. Use Pinoo_Servo(channel) with a channel number from 0 to 15.

---

## 🔍 Cause of the Error
On Pinoo Moto, servo motors are driven by the on-board motor driver (PCA9685), not by a door pin. Defining a servo with a door (`Pinoo_Servo servo(DOOR1);`) would silently drive the wrong driver channel, so the SDK stops the build.

---

## 🛠️ Resolution Steps

1. **Use a channel number (0-15)** instead of a door.
2. **Avoid channel conflicts:** The servo channel must not be used by a DC motor or stepper motor at the same time. For example channel 8 is shared with `MOTOR5` and `STEPPER3`.

### Incorrect Code Example
```cpp
#include <Pinoo.h>

// ERROR: On Pinoo Moto a servo cannot be defined with a door.
Pinoo_Servo servo(DOOR1);
```

### Correct Code Example
```cpp
#include <Pinoo.h>

// CORRECT: Servo on motor driver channel 8.
Pinoo_Servo servo(8);

void setup() {
  servo.begin();
}
void loop() {
  servo.write(90);
  delay(1000);
}
```

---

## 🔌 Channel Map
| Driver block | Channels | DC motors | Stepper | Servo channels |
| :--- | :--- | :--- | :--- | :--- |
| 1 | 0 - 3 | MOTOR1, MOTOR2 | STEPPER1 | 0 - 3 |
| 2 | 4 - 7 | MOTOR3, MOTOR4 | STEPPER2 | 4 - 7 |
| 3 | 8 - 11 | MOTOR5, MOTOR6 | STEPPER3 | 8 - 11 |
| 4 | 12 - 15 | MOTOR7, MOTOR8 | STEPPER4 | 12 - 15 |
