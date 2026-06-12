/**
 * @file RgbLed.ino
 * @brief Pinoo RGB LED (NeoPixel) modülü kullanımı.
 * 
 * Bu örnek Pinoo ONE kartındaki dahili RGB LED'lerin (D13 pinine bağlı 2 adet)
 * ve harici RGB LED modüllerinin nasıl kontrol edileceğini gösterir.
 * 
 * This example demonstrates how to control the on-board RGB LEDs (2 LEDs on Pin D13)
 * and external RGB LED modules on the Pinoo ONE board.
 */

#include <Pinoo.h>

// Dahili RGB LED'leri başlat (Varsayılan olarak Pin 13 ve 2 LED)
// Initialize on-board RGB LEDs (Defaults to Pin 13 and 2 LEDs)
Pinoo_RgbLed dahiliRgb;

// Not: Harici bir RGB LED şeridi kullanıyorsanız, port ve LED sayısını belirtebilirsiniz:
// Note: If using an external RGB LED strip, you can specify the port and LED count:
// Pinoo_RgbLed hariciRgb(PORT1, 4); // Port 1'e bağlı 4 LED'li RGB modülü

void setup() {
  Serial.begin(9600);
  
  // RGB LED'leri başlat / Initialize RGB LEDs
  dahiliRgb.begin();
  
  // Parlaklığı ayarla (0 - 255) / Set brightness (0 - 255)
  dahiliRgb.setBrightness(50); 
  
  Serial.println("Pinoo RGB LED Hazir / RGB LED Ready");
}

void loop() {
  // 1. Adım: Dahili LED'leri farklı renklere ayarla
  // Step 1: Set on-board LEDs to different colors (Pixel 0: Red, Pixel 1: Green)
  Serial.println("Kirmizi ve Yesil / Red and Green");
  dahiliRgb.setColor(0, 255, 0, 0);   // 0. LED Kırmızı / 0th LED Red
  dahiliRgb.setColor(1, 0, 255, 0);   // 1. LED Yeşil / 1st LED Green
  delay(1000);

  // 2. Adım: Renkleri değiştir
  // Step 2: Swap the colors (Pixel 0: Blue, Pixel 1: Yellow)
  Serial.println("Mavi ve Sari / Blue and Yellow");
  dahiliRgb.setColor(0, 0, 0, 255);   // 0. LED Mavi / 0th LED Blue
  dahiliRgb.setColor(1, 255, 255, 0); // 1. LED Sarı / 1st LED Yellow
  delay(1000);

  // 3. Adım: Tüm LED'leri aynı anda Mavi yap
  // Step 3: Set all LEDs to Cyan simultaneously
  Serial.println("Turkuaz / Cyan (All)");
  dahiliRgb.setColorAll(0, 255, 255); // Tüm LED'ler Turkuaz / All LEDs Cyan
  delay(1000);

  // 4. Adım: LED'leri söndür
  // Step 4: Turn off all LEDs
  Serial.println("Sondur / Clear");
  dahiliRgb.clear();
  delay(1000);
}
