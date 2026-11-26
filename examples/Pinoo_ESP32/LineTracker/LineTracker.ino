/**
 * @file LineTracker.ino
 * @brief Pinoo ESP32 Shield — Çizgi İzleme modülü kullanım örneği.
 *
 * Bu örnek Port 8'e bağlı olan kızılötesi Çizgi İzleme (Line Tracker) sensörünün
 * siyah/beyaz zemin değerlerini okumayı gösterir.
 *
 * UYARI: Çizgi İzleme modülü ANALOGDUR (sol ve sağ sensör 0-1023 değer verir), bu yüzden
 * iki analog girişi olan bir porta (Joystick'in bağlandığı port) takılmalıdır.
 *
 * Bilingual (TR/EN) Line Tracker sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 8 üzerinde Çizgi İzleme Sensörü / Line Tracker on Port 8 (two analog inputs, ADC1: Wi-Fi ile birlikte çalışır)
Pinoo_LineTracker tracker(DOOR8);

void setup() {
  Serial.begin(115200);
  tracker.begin(); // Sensörü başlat / Initialize line tracker
  tracker.setThreshold(512); // Çizgi eşiği (0-1023) / Line threshold (0-1023)
}

void loop() {
  // Sol ve sağ sensörlerin çizgi algılama durumlarını oku
  // Read left and right sensor detection states (black vs white)
  Serial.print("Sol Sensör / Left: ");
  Serial.print(tracker.readLeft());
  Serial.print(tracker.isOnLineLeft() ? " (SIYAH / BLACK)" : " (BEYAZ / WHITE)");
  Serial.print(" | Sağ Sensör / Right: ");
  Serial.print(tracker.readRight());
  Serial.println(tracker.isOnLineRight() ? " (SIYAH / BLACK)" : " (BEYAZ / WHITE)");

  delay(200);
}
