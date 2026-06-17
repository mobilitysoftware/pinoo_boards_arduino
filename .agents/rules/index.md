# Pinoo SDK Index

Welcome to the Pinoo SDK codebase directory index. Below you will find organized links to the core source files, board pin definitions, and board-specific example codes.

---

## 🛠️ Core Configurations
- Main Header: [Pinoo.h](file:///d:/Projeler/pinoo_sdk/src/Pinoo.h)
- Configuration Logic: [Pinoo_Config.h](file:///d:/Projeler/pinoo_sdk/src/Pinoo_Config.h)
- Error Definitions: [Pinoo_Errors.h](file:///d:/Projeler/pinoo_sdk/src/Pinoo_Errors.h)

### 📌 Board Pin Definitions
- **Pinoo ONE**: [Pinoo_ONE_Pins.h](file:///d:/Projeler/pinoo_sdk/src/boards/Pinoo_ONE_Pins.h)
- **Pinoo Shield**: [Pinoo_Shield_Pins.h](file:///d:/Projeler/pinoo_sdk/src/boards/Pinoo_Shield_Pins.h)
- **Pinoo Bricky**: [Pinoo_Bricky_Pins.h](file:///d:/Projeler/pinoo_sdk/src/boards/Pinoo_Bricky_Pins.h)
- **Pinoo Moto**: [Pinoo_Moto_Pins.h](file:///d:/Projeler/pinoo_sdk/src/boards/Pinoo_Moto_Pins.h)
- **Pinoo ESP32** (Deferred): [Pinoo_ESP32_Pins.h](file:///d:/Projeler/pinoo_sdk/src/boards/Pinoo_ESP32_Pins.h)

### 🏎️ Moto Board PCA9685 Internal Driver
- Header: [Pinoo_MOTO_PCA9685.h](file:///d:/Projeler/pinoo_sdk/src/boards/Pinoo_MOTO_PCA9685.h)
- Source: [Pinoo_MOTO_PCA9685.cpp](file:///d:/Projeler/pinoo_sdk/src/boards/Pinoo_MOTO_PCA9685.cpp)

---

## 📂 Board-Specific Example Code Folders
To avoid confusion, each board has its own dedicated examples directory. The module code is identical, but the internal/on-board examples are customized for each board's physical capabilities.

- 📐 **Pinoo ONE Examples**: [examples/Pinoo_ONE/](file:///d:/Projeler/pinoo_sdk/examples/Pinoo_ONE)
- 🛡️ **Pinoo Shield Examples**: [examples/Pinoo_Shield/](file:///d:/Projeler/pinoo_sdk/examples/Pinoo_Shield)
- 🧱 **Pinoo Bricky Examples**: [examples/Pinoo_Bricky/](file:///d:/Projeler/pinoo_sdk/examples/Pinoo_Bricky)
- 🏎️ **Pinoo Moto Examples**: [examples/Pinoo_Moto/](file:///d:/Projeler/pinoo_sdk/examples/Pinoo_Moto)

---

## 🧩 Hardware Modules Index

| Module / Class | Header File | Source File |
| :--- | :--- | :--- |
| **Pinoo_Led** | [Pinoo_Led.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Led.h) | [Pinoo_Led.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Led.cpp) |
| **Pinoo_Buzzer** | [Pinoo_Buzzer.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Buzzer.h) | [Pinoo_Buzzer.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Buzzer.cpp) |
| **Pinoo_Button** | [Pinoo_Button.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Button.h) | [Pinoo_Button.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Button.cpp) |
| **Pinoo_Ldr** | [Pinoo_Ldr.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Ldr.h) | [Pinoo_Ldr.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Ldr.cpp) |
| **Pinoo_DcMotor** | [Pinoo_DcMotor.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_DcMotor.h) | [Pinoo_DcMotor.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_DcMotor.cpp) |
| **Pinoo_Stepper** | [Pinoo_Stepper.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Stepper.h) | [Pinoo_Stepper.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Stepper.cpp) |
| **Pinoo_Servo** | [Pinoo_Servo.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Servo.h) | [Pinoo_Servo.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Servo.cpp) |
| **Pinoo_DistanceSensor** | [Pinoo_DistanceSensor.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_DistanceSensor.h) | [Pinoo_DistanceSensor.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_DistanceSensor.cpp) |
| **Pinoo_LineTracker** | [Pinoo_LineTracker.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_LineTracker.h) | [Pinoo_LineTracker.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_LineTracker.cpp) |
| **Pinoo_IrReceiver** | [Pinoo_IrReceiver.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_IrReceiver.h) | [Pinoo_IrReceiver.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_IrReceiver.cpp) |
| **Pinoo_RgbLed** | [Pinoo_RgbLed.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_RgbLed.h) | [Pinoo_RgbLed.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_RgbLed.cpp) |
| **Pinoo_Bluetooth** | [Pinoo_Bluetooth.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Bluetooth.h) | [Pinoo_Bluetooth.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Bluetooth.cpp) |
| **Pinoo_Lcd** | [Pinoo_Lcd.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Lcd.h) | [Pinoo_Lcd.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Lcd.cpp) |
| **Pinoo_Joystick** | [Pinoo_Joystick.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Joystick.h) | [Pinoo_Joystick.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Joystick.cpp) |
| **Pinoo_Potentiometer** | [Pinoo_Potentiometer.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Potentiometer.h) | [Pinoo_Potentiometer.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Potentiometer.cpp) |
| **Pinoo_Pir** | [Pinoo_Pir.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Pir.h) | [Pinoo_Pir.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Pir.cpp) |
| **Pinoo_Tilt** | [Pinoo_Tilt.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Tilt.h) | [Pinoo_Tilt.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_Tilt.cpp) |
| **Pinoo_WaterSensor** | [Pinoo_WaterSensor.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_WaterSensor.h) | [Pinoo_WaterSensor.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_WaterSensor.cpp) |
| **Pinoo_SoilMoisture** | [Pinoo_SoilMoisture.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_SoilMoisture.h) | [Pinoo_SoilMoisture.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_SoilMoisture.cpp) |
| **Pinoo_TempHumidity** | [Pinoo_TempHumidity.h](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_TempHumidity.h) | [Pinoo_TempHumidity.cpp](file:///d:/Projeler/pinoo_sdk/src/modules/Pinoo_TempHumidity.cpp) |
