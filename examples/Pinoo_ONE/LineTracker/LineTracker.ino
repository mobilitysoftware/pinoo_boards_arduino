/**
 * @file LineTracker.ino
 * @brief Bilingual (TR/EN) example for Pinoo Line Tracker module.
 * 
 * Bu örnek Port 5'e bağlı Çizgi İzleme Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of Line Tracker module connected to Port 5.
 */

#include <Pinoo.h>

// Port 5'e bağlı Çizgi İzleme Sensörü / Line Tracker connected to Port 5 (Dual Signal)
Pinoo_LineTracker tracker(PORT5);

void setup() {
  Serial.begin(9600);
  tracker.begin(); // Sensörü başlat / Initialize tracker
}

void loop() {
  // Sol ve sağ sensörlerin durumlarını oku / Read left and right sensor states
  bool leftDetect = tracker.isOnLineLeft();
  bool rightDetect = tracker.isOnLineRight();

  Serial.print("Sol / Left: ");
  Serial.print(leftDetect ? "SIYAH / BLACK" : "BEYAZ / WHITE");
  Serial.print(" | Sag / Right: ");
  Serial.println(rightDetect ? "SIYAH / BLACK" : "BEYAZ / WHITE");

  delay(200);
}
