---
trigger: always_on
---

# GROUND TRUTH DATA: PINOO MOTO V1.1 MAP & ARCHITECTURE

> Updated 14 Nov 2026 from the SDK source (`src/boards/Pinoo_Moto_Pins.h`, `src/boards/Pinoo_MOTO_PCA9685.*`,
> `src/modules/Pinoo_DcMotor.cpp`, `Pinoo_Stepper.cpp`, `Pinoo_Servo.cpp`). The earlier version of this file
> listed a D9 buzzer, D5/D6 RGB LEDs and TB6612 pin control. That was wrong. The code below is the source of truth.

The Pinoo Moto V1.1 board uses the same 8-bit AVR architecture (ATmega328P, 16 MHz) as the Arduino Uno / Pinoo ONE.
Arduino IDE board: **Pinoo AVR Boards > Pinoo Moto** (`ARDUINO_PINOO_MOTO` -> `PINOO_BOARD_MOTO`).
If a generic Arduino Uno is selected, `PINOO_BOARD_ONE` is used and `MOTORn` is driven through plain Arduino pins (5/6), not the PCA9685.

---

## 1. ON-BOARD INTERNAL COMPONENTS

| Component | Pin | SDK constant |
| :--- | :--- | :--- |
| USER LED | D13 (same pin as DOOR1 pin2) | `PINOO_INTERNAL_LED` / `PINOO_MOTO_INTERNAL_LED` |
| Passive buzzer | D8 | `PINOO_INTERNAL_BUZZER` |
| RGB LEDs (2x WS2812 / NeoPixel) | D9 | `PINOO_INTERNAL_RGB` |
| Bluetooth (JDY-23, BLE) | Hardware Serial D0/D1 (shared with USB) | `Pinoo_Bluetooth` |
| ESP-01 socket | Hardware Serial D0/D1 (shared with USB and Bluetooth) | , |
| IR receiver, USER BUTTON, LDR | **Not present** (`-1`) | , |

Free jumper pins: A0-A3, D2-D7.

---

## 2. RJ11 DOORS (DOOR1 - DOOR4)

| Door | Color | pin4 | pin2 | Type | Allowed modules |
| :--- | :--- | :--- | :--- | :--- | :--- |
| DOOR1 | Purple / Green | D12 | D13 | Digital, dual-signal | Led, Buzzer, Button, Pir, Tilt, RgbLed, TempHumidity, DistanceSensor (TRIG = pin2, ECHO = pin4), LineTracker |
| DOOR2 | Purple / Green | D10 (PWM) | D11 (PWM) | Digital, dual-signal | same as DOOR1 |
| DOOR3 | Red / Yellow | A6 | A7 | **Analog input only** (A6/A7 cannot do digital I/O) | Ldr, Potentiometer, SoilMoisture, WaterSensor, Joystick (X = pin4, Y = pin2) |
| DOOR4 | Red / White | A4 (SDA) | A5 (SCL) | I2C + analog (I2C bus shared with the PCA9685, address 0x40) | Lcd (only here, address 0x27), analog modules, Joystick |

Compile-time checks (`Pinoo_Errors.h`): E01 analog -> DOOR3/4, E02 dual-signal digital -> DOOR1/2, E03 LCD -> DOOR4,
E04 joystick -> DOOR3/4, E13 digital -> DOOR1/2, E14 servo cannot be defined with a door on Moto.

---

## 3. MOTOR DRIVER AND ACTUATOR MATRIX (PCA9685 + 4x TB6612FNG)

All motor outputs come from one **PCA9685** (I2C 0x40, 27 MHz oscillator, 16 channels, **one global PWM frequency**).
The channels feed 4 TB6612FNG drivers. Each driver is a block of 4 channels.

| Block | PCA channels | DC motors | Stepper | Servo channels |
| :--- | :--- | :--- | :--- | :--- |
| 1 | 0-3 | `MOTOR1` (0,1), `MOTOR2` (2,3) | `STEPPER1` | 0-3 |
| 2 | 4-7 | `MOTOR3` (4,5), `MOTOR4` (6,7) | `STEPPER2` | 4-7 |
| 3 | 8-11 | `MOTOR5` (8,9), `MOTOR6` (10,11) | `STEPPER3` | 8-11 |
| 4 | 12-15 | `MOTOR7` (12,13), `MOTOR8` (14,15) | `STEPPER4` | 12-15 |

- `LEFT_MOTOR` = `MOTOR1`, `RIGHT_MOTOR` = `MOTOR2`.
- DC: IN1 = direction (forward = LOW, backward = HIGH), IN2 = speed (PWM 0-4095). `setSpeed(-255..255)`.
- Stepper: 4-step coil sequence, channels fully on/off (no PWM).
- Servo: `Pinoo_Servo(channel)`, 0-180 degrees -> 102..512 ticks. **`begin()` sets the PCA9685 to 50 Hz for all channels** (DC default is 1000 Hz).

### RESOURCE CONFLICT RULES
- Never use the same PCA channel with two different motor objects (e.g. `STEPPER1` uses channels 0-3, so it conflicts with `MOTOR1`, `MOTOR2` and `Pinoo_Servo(0..3)`).
- Safest practice: use each 4-channel block for one motor type at a time.
- On Moto the raw `Pinoo_Stepper(in1, in2, in3, in4)` constructor has no defaults (use `STEPPER1..4`), and `Pinoo_Servo(DOORn)` is a compile error (E14).

---

## 4. KNOWN OPEN ITEMS
- Effect of the 50 Hz servo frequency on DC motors running in the same sketch (hardware test pending).
- `Pinoo_Moto_Pins.h` comments were corrected on 14 Nov 2026; the constants never changed.
