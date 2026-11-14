# Pinoo Hata Çözümü - E14

## ❌ Hata Mesajı
> **PINOO ERROR [E14]:** On Pinoo Moto, servo motors connect to the motor driver channels, not to doors. Use Pinoo_Servo(channel) with a channel number from 0 to 15.

---

## 🔍 Hataya Yol Açan Durum
Pinoo Moto'da servo motorlar bir kapı pini ile değil, kart üzerindeki motor sürücüsü (PCA9685) ile sürülür. Servoyu bir kapıyla tanımlamak (`Pinoo_Servo servo(DOOR1);`) sessizce yanlış sürücü kanalını sürerdi, bu yüzden SDK derlemeyi durdurur.

---

## 🛠️ Çözüm Adımları

1. **Kapı yerine kanal numarası (0-15) kullanın.**
2. **Kanal çakışmasından kaçının:** Servonun kanalı aynı anda bir DC motor ya da step motor tarafından kullanılmamalıdır. Örneğin 8. kanal `MOTOR5` ve `STEPPER3` ile ortaktır.

### Hatalı Kod Örneği
```cpp
#include <Pinoo.h>

// HATA: Pinoo Moto'da servo kapı ile tanımlanamaz.
Pinoo_Servo servo(DOOR1);
```

### Doğru Kod Örneği
```cpp
#include <Pinoo.h>

// DOĞRU: Servo motor sürücünün 8. kanalında.
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

## 🔌 Kanal Haritası
| Sürücü bloğu | Kanallar | DC motorlar | Step motor | Servo kanalları |
| :--- | :--- | :--- | :--- | :--- |
| 1 | 0 - 3 | MOTOR1, MOTOR2 | STEPPER1 | 0 - 3 |
| 2 | 4 - 7 | MOTOR3, MOTOR4 | STEPPER2 | 4 - 7 |
| 3 | 8 - 11 | MOTOR5, MOTOR6 | STEPPER3 | 8 - 11 |
| 4 | 12 - 15 | MOTOR7, MOTOR8 | STEPPER4 | 12 - 15 |
