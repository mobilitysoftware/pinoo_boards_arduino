/**
 * @file Tilt.ino
 * @brief Pinoo ESP32 Shield — Eğim ve Darbe Sensörü kullanım örneği.
 *
 * Bu örnek Port 2'ye bağlı Eğim ve Darbe (Tilt) sensöründen eğim veya
 * darbe durumunu dijital olarak okumayı gösterir.
 *
 * Bilingual (TR/EN) Tilt & Vibration Sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 2 üzerinde Eğim/Darbe Sensörü / Tilt sensor on Port 2 (D17)
Pinoo_Tilt tilt(DOOR2);

void setup() {
  Serial.begin(115200);
  tilt.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Sensör eğilmiş veya darbe almış mı kontrol et / Check tilt state
  bool egimVar = tilt.isTilted();

  Serial.print("Sensör Durumu / Sensor State: ");
  if (egimVar) {
    Serial.println("EGIM / DARBE VAR (TILTED / SHOCK)");
  } else {
    Serial.println("DENGEDE (BALANCED / NORMAL)");
  }

  delay(100);
}
