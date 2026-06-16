/**
 * @file Buzzer.ino
 * @brief Pinoo ESP32 Shield — Buzzer modülü kullanım örneği.
 *
 * Bu örnek Port 3 üzerindeki Pasif Buzzer modülü ile basit ses tonları 
 * üretmeyi gösterir.
 *
 * UYARI: ESP32 üzerinde ton çalmak için LEDC (PWM) yapısı kullanılır.
 * SDK içindeki playTone() metodu bunu otomatik yönetir.
 *
 * Bilingual (TR/EN) passive buzzer example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 3 üzerinde Pasif Buzzer / Passive Buzzer on Port 3 (Pin A = D18)
Pinoo_Buzzer buzzer(DOOR3, PASSIVE_BUZZER);

void setup() {
  buzzer.begin(); // Buzzer'ı başlat / Initialize buzzer
}

void loop() {
  // 440Hz frekansta (La notası) ton çal / Play 440Hz tone (La/A4 note)
  buzzer.playTone(440);
  delay(500);

  // Tonu durdur / Stop playing
  buzzer.stop();
  delay(500);

  // 880Hz frekansta 300ms süren kısa bip sesi çal
  // Play short 880Hz beep for 300ms duration
  buzzer.playTone(880, 300);
  delay(1000);
}
