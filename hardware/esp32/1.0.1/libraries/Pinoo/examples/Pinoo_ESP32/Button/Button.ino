/**
 * @file Button.ino
 * @brief Pinoo ESP32 Shield — Buton modülü kullanım örneği.
 *
 * Bu örnek Port 2 üzerindeki buton modülünün durumunu okumayı ve 
 * Port 1 üzerindeki LED modülünü bu butona göre kontrol etmeyi gösterir.
 *
 * UYARI: Port 1 (D16) ve Port 2 (D17) dijital çıkış ve girişleri destekler.
 *
 * Bilingual (TR/EN) button example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 2 üzerinde buton / Button on Port 2 (D17)
Pinoo_Button buton(DOOR2);

// Port 1 üzerinde LED / LED on Port 1 (D16)
Pinoo_Led led(DOOR1);

void setup() {
  Serial.begin(115200);

  buton.begin(); // Butonu başlat / Initialize button
  led.begin();   // LED'i başlat / Initialize LED
}

void loop() {
  // Buton basılı mı kontrol et / Check if button is pressed
  bool basili = buton.isPressed();

  if (basili) {
    led.turnOn(); // Buton basılı ise LED'i yak / Turn LED on if button is pressed
    Serial.println("Buton Basili / Button Pressed");
  } else {
    led.turnOff(); // Değilse LED'i söndür / Turn LED off if released
  }

  delay(50);
}
