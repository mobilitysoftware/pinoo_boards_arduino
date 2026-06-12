/**
 * @file Buzzer.ino
 * @brief Bilingual (TR/EN) example for Pinoo Buzzer module.
 * 
 * Bu örnek Port 2'ye bağlı Pasif Buzzer modülünün nasıl kontrol edileceğini gösterir.
 * This example demonstrates how to control a Passive Buzzer module connected to Port 2.
 */

#include <Pinoo.h>

// Port 2'ye bağlı Pasif Buzzer / Passive Buzzer module connected to Port 2
Pinoo_Buzzer buzzer(PORT2, PASSIVE_BUZZER);

void setup() {
  buzzer.begin(); // Buzzer'ı başlat / Initialize Buzzer
}

void loop() {
  // Belirli bir frekansta ton çal (Örn: 440Hz - La notası)
  // Play a tone at specific frequency (e.g. 440Hz - Note A)
  buzzer.playTone(440);
  delay(500);

  // Tonu durdur / Stop playing
  buzzer.stop();
  delay(500);

  // 1000Hz frekansta 200ms süren kısa bir bip sesi çal
  // Play a short beep at 1000Hz for 200ms duration
  buzzer.playTone(1000, 200);
  delay(1000);
}
