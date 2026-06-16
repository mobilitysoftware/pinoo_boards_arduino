/**
 * @file Potentiometer.ino
 * @brief Pinoo ESP32 Shield — Potansiyometre modülü kullanım örneği.
 *
 * Bu örnek Port 5'e bağlı olan Potansiyometre modülünün analog değerini
 * okumayı gösterir.
 *
 * UYARI: Port 5 (D36) input-only analog pindir. Donanımsal 12-bit ADC çözünürlüğü,
 * SDK tarafından otomatik olarak 10-bit (0-1023) aralığına ölçeklenir.
 *
 * Bilingual (TR/EN) Potentiometer example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 5 üzerinde Potansiyometre / Potentiometer on Port 5 (D36, input-only analog)
Pinoo_Potentiometer pot(DOOR5);

void setup() {
  Serial.begin(115200);
  pot.begin(); // Potansiyometreyi başlat / Initialize potentiometer
}

void loop() {
  // Ham analog değeri ve direnç yüzdesini (%0-100) oku
  // Read raw analog value and position percentage (0-100%)
  int hamDeger = pot.readValue();
  int yuzde = pot.getValuePercentage();

  Serial.print("Ham Deger / Raw: ");
  Serial.print(hamDeger);
  Serial.print(" | Pozisyon / Position %: ");
  Serial.print(yuzde);
  Serial.println("%");

  delay(200);
}
