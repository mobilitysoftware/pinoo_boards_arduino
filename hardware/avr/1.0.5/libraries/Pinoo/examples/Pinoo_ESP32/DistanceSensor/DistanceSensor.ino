/**
 * @file DistanceSensor.ino
 * @brief Pinoo ESP32 Shield — Mesafe sensörü kullanım örneği.
 *
 * Bu örnek Port 7'ye bağlı ultrasonik mesafe sensöründen (HC-SR04) 
 * santimetre cinsinden mesafe ölçmeyi gösterir.
 *
 * UYARI: Port 7 çift yönlü dijital/analog pindir (Trig=D25, Echo=D26).
 *
 * Bilingual (TR/EN) ultrasonic distance sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 7 üzerinde mesafe sensörü / Distance sensor on Port 7 (Trig=D25, Echo=D26)
Pinoo_DistanceSensor mesafe(DOOR7);

void setup() {
  Serial.begin(115200);
  mesafe.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Mesafeyi santimetre olarak ölç / Measure distance in cm
  float cm = mesafe.getDistance();

  Serial.print("Mesafe / Distance: ");
  Serial.print(cm);
  Serial.println(" cm");

  delay(200);
}
