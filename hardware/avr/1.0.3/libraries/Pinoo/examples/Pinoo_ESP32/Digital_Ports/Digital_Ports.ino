/**
 * @file Digital_Ports.ino
 * @brief Pinoo ESP32 Shield — Dijital port bileşenlerinin kullanım örneği.
 *
 * Bu örnek ESP32 Shield üzerindeki dijital portların (Port 1-4)
 * LED, buton, buzzer ve mesafe sensörü ile kullanımını gösterir.
 *
 * Port Haritası / Port Map:
 *   Port 1 (5V, tek pin)   → Pin A: D16
 *   Port 2 (5V, tek pin)   → Pin A: D17
 *   Port 3 (5V, çift pin)  → Pin A: D18, Pin B: D19
 *   Port 4 (5V, çift pin)  → Pin A: D5,  Pin B: D23
 *   Port 6 (3V3, çift pin) → Pin A: D27, Pin B: D14
 *   Port 7 (5V, çift pin)  → Pin A: D25, Pin B: D26
 *
 * Bilingual (TR/EN) digital port example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

// Port 1 üzerinde LED (Pin A = D16) / LED on Port 1 (Pin A = D16)
Pinoo_Led led(DOOR1);

// Port 2 üzerinde buton (Pin A = D17) / Button on Port 2 (Pin A = D17)
Pinoo_Button buton(DOOR2);

// Port 3 üzerinde buzzer (Pin A = D18) / Buzzer on Port 3 (Pin A = D18)
Pinoo_Buzzer buzzer(DOOR3, PASSIVE_BUZZER);

// Port 7 üzerinde ultrasonik mesafe sensörü
// Ultrasonic distance sensor on Port 7 (Trig=D25, Echo=D26)
Pinoo_DistanceSensor mesafe(DOOR7);

void setup() {
  Serial.begin(115200);

  led.begin();
  buton.begin();
  buzzer.begin();
  mesafe.begin();

  Serial.println("Pinoo ESP32 Dijital Port Ornegi / Digital Port Example");
}

void loop() {
  // Mesafeyi ölç / Measure distance
  float cm = mesafe.getDistance();

  Serial.print("Mesafe / Distance: ");
  Serial.print(cm);
  Serial.println(" cm");

  // Buton basıldığında LED yakar ve buzzer çalar
  // Button press: turn LED on and play tone
  if (buton.isPressed()) {
    led.turnOn();
    buzzer.playTone(880); // La / A5 note
    Serial.println("Buton basili / Button pressed");
  } else {
    led.turnOff();
    buzzer.stop();
  }

  // 20 cm'den yakın bir nesne varsa uyar
  // Warn if object is closer than 20 cm
  if (cm > 0 && cm < 20.0) {
    led.toggle();
    buzzer.playTone(2000, 100); // Kısa uyarı tonu / Short warning beep
    Serial.println("YAKIN NESNE / CLOSE OBJECT!");
  }

  delay(200);
}
