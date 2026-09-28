/**
 * @file Pir.ino
 * @brief Pinoo ESP32 Shield — PIR Hareket Sensörü kullanım örneği.
 *
 * Bu örnek Port 1'e bağlı PIR Hareket Sensöründen gelen dijital sinyali
 * okuyarak ortamda bir hareket olup olmadığını algılamayı gösterir.
 *
 * Bilingual (TR/EN) PIR Motion Sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 1 üzerinde PIR Hareket Sensörü / PIR Sensor on Port 1 (D16)
Pinoo_Pir pir(DOOR1);

void setup() {
  Serial.begin(115200);
  pir.begin(); // Sensörü başlat / Initialize PIR sensor
}

void loop() {
  // Hareket algılandı mı kontrol et / Check if motion detected
  bool hareketVar = pir.isMotionDetected();

  if (hareketVar) {
    Serial.println("HAREKET ALGILANDI! / MOTION DETECTED!");
  } else {
    Serial.println("Hareket yok. / No motion.");
  }

  delay(250);
}
