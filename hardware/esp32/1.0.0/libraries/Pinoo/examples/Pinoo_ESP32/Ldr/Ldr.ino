/**
 * @file Ldr.ino
 * @brief Pinoo ESP32 Shield — LDR (Işık) Sensörü kullanım örneği.
 *
 * Bu örnek Port 5'e bağlı LDR modülünden ortamın ışık yoğunluğunu okumayı gösterir.
 *
 * UYARI: Port 5 (D36) input-only analog bir pindir ve yalnızca sensör okumaları için
 * kullanılabilir. ESP32'nin 12-bit ADC değeri otomatik olarak 10-bit (0-1023)
 * aralığına ölçeklenir.
 *
 * Bilingual (TR/EN) LDR (Light Sensor) example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 5 üzerinde LDR sensörü / LDR sensor on Port 5 (D36, input-only analog)
Pinoo_Ldr ldr(DOOR5);

void setup() {
  Serial.begin(115200);
  ldr.begin(); // Sensörü başlat / Initialize LDR
}

void loop() {
  // Ham analog değeri ve ışık yüzdesini (%0-100) oku
  // Read raw value and percentage (0-100%)
  int hamDeger = ldr.readValue();
  int yuzde = ldr.getLightPercentage();

  Serial.print("Ham Deger / Raw Value: ");
  Serial.print(hamDeger);
  Serial.print(" | Isik Yuzdesi / Light %: ");
  Serial.print(yuzde);
  Serial.println("%");

  delay(300);
}
