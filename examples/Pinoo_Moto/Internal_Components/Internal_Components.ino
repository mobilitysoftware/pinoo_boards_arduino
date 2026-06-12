/**
 * @file Internal_Components.ino
 * @brief Bilingual (TR/EN) example for Pinoo Moto on-board components.
 * 
 * Bu örnek Pinoo Moto kartındaki dahili LED (D13), pasif buzzer (D8) ve 
 * RGB LED şeridinin (D9 pinine bağlı NeoPixel zinciri) kullanımını gösterir.
 * 
 * This example shows the usage of on-board components of Pinoo Moto:
 * LED (D13), Passive Buzzer (D8), and RGB LED strip (NeoPixel chain on Pin D9).
 */

#include <Pinoo.h>

// Dahili bileşen tanımlamaları / Internal component declarations
Pinoo_Led dahiliLed(PINOO_INTERNAL_LED);               // Dahili LED (D13) / On-board LED
Pinoo_Buzzer dahiliBuzzer(PINOO_INTERNAL_BUZZER, PASSIVE_BUZZER); // Dahili Pasif Buzzer (D8) / On-board Buzzer
Pinoo_RgbLed dahiliRgb(PINOO_INTERNAL_RGB, 2);         // Dahili RGB LED'ler (D9 pininde 2 adet) / On-board RGB LEDs (2 on D9)

void setup() {
  Serial.begin(9600);
  
  // Bileşenleri başlat / Initialize components
  dahiliLed.begin();
  dahiliBuzzer.begin();
  dahiliRgb.begin();

  // RGB LED parlaklığını ayarla / Set RGB LED brightness
  dahiliRgb.setBrightness(50);

  Serial.println("Pinoo Moto Dahili Bilesenler Hazir / Internal Components Ready");
}

void loop() {
  // LED'i yak ve buzzer'ı çalıştır, RGB LED'leri kırmızı yap
  // Turn LED/RGB red and play tone on Buzzer
  dahiliLed.turnOn();
  dahiliRgb.setColorAll(255, 0, 0); // Kırmızı / Red
  dahiliBuzzer.playTone(1000);      // 1000Hz ton çal / Play 1000Hz tone
  delay(1000);

  // LED/RGB kapat, buzzer durdur
  // Turn off LED/RGB and stop Buzzer
  dahiliLed.turnOff();
  dahiliRgb.clear();
  dahiliBuzzer.stop();
  delay(1000);

  // RGB LED'leri yeşil yap
  // Set RGB LEDs to green
  dahiliRgb.setColor(0, 0, 255, 0); // 0. LED Yeşil / 0th LED Green
  dahiliRgb.setColor(1, 0, 255, 0); // 1. LED Yeşil / 1st LED Green
  delay(1000);
  dahiliRgb.clear();
}
