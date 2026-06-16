/**
 * @file Servo.ino
 * @brief Pinoo ESP32 Shield — Servo Motor kullanım örneği.
 *
 * Bu örnek Port 4'e bağlı olan bir Servo motorun açısını (0-180 derece) 
 * kontrol etmeyi gösterir.
 *
 * UYARI: ESP32 donanımında servo kontrolü LEDC veya özel PWM kütüphanesi
 * gerektirmektedir. SDK, standart Servo.h arayüzü ile uyumlu donanımsal 
 * kontrol sağlar.
 *
 * Bilingual (TR/EN) Servo Motor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 4 üzerinde Servo Motor / Servo Motor on Port 4 (Pin A = D5)
Pinoo_Servo servo(DOOR4);

void setup() {
  servo.begin(); // Servo motoru başlat / Initialize servo
}

void loop() {
  // Servo milini sırayla 0, 90 ve 180 derecelere döndürür
  // Turn servo shaft to 0, 90, and 180 degrees
  
  servo.write(0);
  delay(1000);

  servo.write(90);
  delay(1000);

  servo.write(180);
  delay(1000);
  
  // Yavaş bir süpürme hareketi yap (0 -> 180 derece)
  // Sweep slowly from 0 to 180 degrees
  for (int aci = 180; aci >= 0; aci -= 5) {
    servo.write(aci);
    delay(30);
  }
  delay(1000);
}
