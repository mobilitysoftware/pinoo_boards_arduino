/**
 * @file SoilMoisture.ino
 * @brief Pinoo ESP32 Shield — Toprak Nem Sensörü kullanım örneği.
 *
 * Bu örnek Port 9'a bağlı Toprak Nem (Soil Moisture) sensöründen 
 * toprağın nem oranını (%) okumayı gösterir.
 *
 * UYARI: Port 9 (D34) input-only analog bir pindir ve yalnızca sensör okumaları için
 * kullanılabilir. ESP32'nin 12-bit ADC değeri otomatik olarak 10-bit (0-1023)
 * aralığına ölçeklenir.
 *
 * Bilingual (TR/EN) Soil Moisture Sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 9 üzerinde Toprak Nem Sensörü / Soil Moisture on Port 9 (D34, input-only analog)
Pinoo_SoilMoisture nemSensoru(DOOR9);

void setup() {
  Serial.begin(115200);
  nemSensoru.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Ham direnç değerini ve nem yüzdesini (%0-100) oku
  // Read raw analog value and humidity percentage (0-100%)
  int hamDeger = nemSensoru.readValue();
  int yuzde = nemSensoru.getMoisturePercentage();

  Serial.print("Ham Deger / Raw: ");
  Serial.print(hamDeger);
  Serial.print(" | Toprak Nem / Soil Moisture: ");
  Serial.print(yuzde);
  Serial.println("%");

  delay(500);
}
