/**
 * @file RgbLed.ino
 * @brief Pinoo RGB LED (NeoPixel) modülü kullanımı.
 * 
 * Bu örnek Pinoo Bricky kartına bağlanan harici bir RGB LED modülünün (örneğin Door 1)
 * nasıl kontrol edileceğini gösterir.
 * 
 * This example demonstrates how to control an external RGB LED module
 * connected to a door (e.g., Door 1) on the Pinoo Bricky board.
 */

#include <Pinoo.h>

// Door 1'e bağlı 2 LED'li RGB LED modülünü başlat
// Initialize RGB LED module with 2 LEDs connected to Door 1
Pinoo_RgbLed rgb(DOOR1, 2);

void setup() {
  Serial.begin(9600);
  
  // RGB LED modülünü başlat / Initialize RGB LED module
  rgb.begin();
  
  // Parlaklığı ayarla (0 - 255) / Set brightness (0 - 255)
  rgb.setBrightness(50); 
  
  Serial.println("Pinoo RGB LED Hazir / RGB LED Ready");
}

void loop() {
  // 1. Adım: LED'leri farklı renklere ayarla
  // Step 1: Set LEDs to different colors (Pixel 0: Red, Pixel 1: Green)
  Serial.println("Kirmizi ve Yesil / Red and Green");
  rgb.setColor(0, 255, 0, 0);   // 0. LED Kırmızı / 0th LED Red
  rgb.setColor(1, 0, 255, 0);   // 1. LED Yeşil / 1st LED Green
  delay(1000);

  // 2. Adım: Renkleri değiştir
  // Step 2: Swap the colors (Pixel 0: Blue, Pixel 1: Yellow)
  Serial.println("Mavi ve Sari / Blue and Yellow");
  rgb.setColor(0, 0, 0, 255);   // 0. LED Mavi / 0th LED Blue
  rgb.setColor(1, 255, 255, 0); // 1. LED Sarı / 1st LED Yellow
  delay(1000);

  // 3. Adım: Tüm LED'leri aynı anda Mavi yap
  // Step 3: Set all LEDs to Cyan simultaneously
  Serial.println("Turkuaz / Cyan (All)");
  rgb.setColorAll(0, 255, 255); // Tüm LED'ler Turkuaz / All LEDs Cyan
  delay(1000);

  // 4. Adım: LED'leri söndür
  // Step 4: Turn off all LEDs
  Serial.println("Sondur / Clear");
  rgb.clear();
  delay(1000);
}
