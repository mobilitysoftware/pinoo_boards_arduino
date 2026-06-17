/**
 * @file Led.ino
 * @brief Pinoo ESP32 Shield — LED modülü kullanım örneği.
 *
 * Bu örnek Port 1'e bağlı LED modülünü yakıp söndürmeyi (Blink) gösterir.
 *
 * Bilingual (TR/EN) LED module example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 1 üzerinde LED modülü / LED module on Port 1 (Pin A = D16)
Pinoo_Led led(DOOR1);

void setup() {
  led.begin(); // LED modülünü başlat / Initialize LED
}

void loop() {
  // LED'i yak / Turn LED on
  led.turnOn();
  delay(1000);

  // LED'i söndür / Turn LED off
  led.turnOff();
  delay(1000);

  // LED durumunu tersine çevir (yanıyorsa söner, sönükse yanar)
  // Toggle LED state (on -> off / off -> on)
  led.toggle();
  delay(500);
  led.toggle();
  delay(500);
}
