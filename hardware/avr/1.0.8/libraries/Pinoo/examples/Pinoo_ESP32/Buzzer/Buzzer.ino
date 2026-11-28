/**
 * @file Buzzer.ino
 * @brief Pinoo ESP32 Shield — Buzzer modülü kullanım örneği.
 *
 * Bu örnek Port 3'e bağlı Buzzer modülünün (aktif buzzer) nasıl kontrol edileceğini gösterir.
 * Aktif buzzer tek bir sabit tonda öter, yalnızca açılır ve kapanır.
 * Kapı (DOOR) verildiğinde SDK otomatik olarak aktif buzzer seçer.
 *
 * Bilingual (TR/EN) active buzzer module example for Pinoo ESP32 Shield.
 * The Buzzer module is an active buzzer: a single fixed tone, on/off only.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 3 üzerinde Buzzer modülü / Buzzer module on Port 3 (Pin A = D18)
Pinoo_Buzzer buzzer(DOOR3);

void setup() {
  buzzer.begin(); // Buzzer'ı başlat / Initialize buzzer
}

void loop() {
  // Buzzer'ı aç / Turn the buzzer on
  buzzer.turnOn();
  delay(500);

  // Buzzer'ı kapat / Turn the buzzer off
  buzzer.turnOff();
  delay(500);

  // 200 ms'lik kısa bir bip sesi / A short 200 ms beep
  // (aktif buzzer'da frekans değeri yok sayılır / the frequency is ignored on an active buzzer)
  buzzer.playTone(1000, 200);
  delay(1000);
}
