/**
 * @file RgbLed.ino
 * @brief Pinoo ESP32 Shield — RGB NeoPixel LED modülü kullanım örneği.
 *
 * Bu örnek Port 3'e bağlı olan harici bir NeoPixel RGB LED şeridini/modülünü
 * kontrol etmeyi gösterir.
 *
 * UYARI: Port 3 (D18) hızlı dijital haberleşmeye (WS2812) uygundur.
 * Bu örnekte 1 adet LED'e sahip bir modül simüle edilmiştir.
 *
 * Bilingual (TR/EN) NeoPixel RGB LED example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 3 üzerinde 1 adet LED'e sahip RGB NeoPixel modülü
// External RGB NeoPixel module with 1 pixel on Port 3 (D18)
Pinoo_RgbLed rgb(DOOR3, (uint16_t)1);

void setup() {
  rgb.begin();         // RGB LED modülünü başlat / Initialize RGB LED
  rgb.setBrightness(40); // Parlaklığı ayarla / Set brightness (0-255)
}

void loop() {
  // Kırmızı renk yak / Set color to Red
  rgb.setColorAll(255, 0, 0);
  delay(1000);

  // Yeşil renk yak / Set color to Green
  rgb.setColorAll(0, 255, 0);
  delay(1000);

  // Mavi renk yak / Set color to Blue
  rgb.setColorAll(0, 0, 255);
  delay(1000);

  // Renkleri kapat / Clear and turn off
  rgb.clear();
  delay(1000);
}
