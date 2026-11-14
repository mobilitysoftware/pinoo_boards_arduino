/**
 * @file LineTracker.ino
 * @brief Pinoo ESP32 Shield — Çizgi İzleme modülü kullanım örneği.
 *
 * Bu örnek Port 3'e bağlı olan kızılötesi Çizgi İzleme (Line Tracker) sensörünün
 * siyah/beyaz zemin algılama durumlarını okumayı gösterir.
 *
 * UYARI: Çizgi İzleme modülü çift dijital pin gerektirir. Port 3 (D18/D19)
 * donanımsal çift pindir.
 *
 * Bilingual (TR/EN) Line Tracker sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 3 üzerinde Çizgi İzleme Sensörü / Line Tracker on Port 3 (Left=D18, Right=D19)
Pinoo_LineTracker tracker(DOOR3);

void setup() {
  Serial.begin(115200);
  tracker.begin(); // Sensörü başlat / Initialize line tracker
}

void loop() {
  // Sol ve sağ sensörlerin çizgi algılama durumlarını oku
  // Read left and right sensor detection states (black vs white)
  bool leftDetect = tracker.isOnLineLeft();
  bool rightDetect = tracker.isOnLineRight();

  Serial.print("Sol Sensör / Left: ");
  Serial.print(leftDetect ? "SIYAH / BLACK" : "BEYAZ / WHITE");
  Serial.print(" | Sağ Sensör / Right: ");
  Serial.println(rightDetect ? "SIYAH / BLACK" : "BEYAZ / WHITE");

  delay(200);
}
