/**
 * @file DistanceSensor.ino
 * @brief Bilingual (TR/EN) example for Pinoo Distance Sensor module.
 * 
 * Bu örnek Port 5'e bağlı HC-SR04 Mesafe Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of HC-SR04 Distance Sensor module connected to Port 5.
 */

#include <Pinoo.h>

// Port 5'e bağlı Mesafe Sensörü / Distance Sensor connected to Port 5 (Dual Signal)
Pinoo_DistanceSensor distanceSensor(PORT5);

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
