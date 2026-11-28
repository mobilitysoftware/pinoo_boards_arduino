/**
 * @file DistanceSensor.ino
 * @brief Bilingual (TR/EN) example for Pinoo Distance Sensor module.
 * 
 * Bu örnek Door 1'e bağlı HC-SR04 Mesafe Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of HC-SR04 Distance Sensor module connected to Door 1.
 */

#include <Pinoo.h>

// Door 1'e bağlı Mesafe Sensörü / Distance Sensor connected to Door 1 (Dual Signal)
Pinoo_DistanceSensor distanceSensor(DOOR1);

void setup() {
  Serial.begin(9600);
  distanceSensor.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Mesafeyi santimetre olarak ölç / Measure distance in cm
  float distance = distanceSensor.getDistance();

  // Değeri seri port ekrana yazdır / Print value to Serial monitor
  Serial.print("Mesafe / Distance: ");
  if (distance >= 0) {
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Okunamadi / Out of Range");
  }

  delay(200);
}
