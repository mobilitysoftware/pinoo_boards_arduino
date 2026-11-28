/**
 * @file LineTracker.ino
 * @brief Bilingual (TR/EN) example for Pinoo Line Tracker module.
 * 
 * Bu örnek Door 9'a bağlı Çizgi İzleme Sensörü modülünün kullanımını gösterir.
 * Modül ANALOG çalışır: sol ve sağ sensör 0-1023 arası değer verir. Bu yüzden iki analog
 * girişi olan bir kapıya (Joystick'in bağlandığı kapı) takılır. Değerler zemine ve sensör
 * yüksekliğine göre değişir: önce Seri Monitör'den kendi zeminindeki değerlere bak, sonra
 * setThreshold() ile eşiği ayarla. Eşiğin üstündeki değer "çizgi var" sayılır.
 * 
 * This example demonstrates usage of the Line Tracker module connected to Door 9.
 * The module is ANALOG: the left and right sensors return a value between 0 and 1023.
 * It therefore connects to a door with two analog inputs (the same door type as the Joystick).
 * Values depend on the surface and sensor height: check the Serial Monitor on your own surface
 * first, then tune setThreshold(). A reading above the threshold counts as "line detected".
 */

#include <Pinoo.h>

// Door 9'a bağlı Çizgi İzleme Sensörü / Line Tracker connected to Door 9 (two analog inputs)
Pinoo_LineTracker tracker(DOOR9);

void setup() {
  Serial.begin(9600);
  tracker.begin(); // Sensörü başlat / Initialize tracker

  // Çizgi eşiği (0-1023, varsayılan 512) / Line threshold (0-1023, default 512)
  tracker.setThreshold(512);
}

void loop() {
  // Sol ve sağ sensör değerlerini oku / Read left and right sensor values
  int leftValue = tracker.readLeft();
  int rightValue = tracker.readRight();

  Serial.print("Sol / Left: ");
  Serial.print(leftValue);
  Serial.print(tracker.isOnLineLeft() ? " (SIYAH / BLACK)" : " (BEYAZ / WHITE)");
  Serial.print(" | Sag / Right: ");
  Serial.print(rightValue);
  Serial.println(tracker.isOnLineRight() ? " (SIYAH / BLACK)" : " (BEYAZ / WHITE)");

  delay(200);
}
