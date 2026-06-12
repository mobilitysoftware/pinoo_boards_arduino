/**
 * @file WaterSensor.ino
 * @brief Bilingual (TR/EN) example for Pinoo Water Sensor module.
 * 
 * Bu örnek Door 7'ye bağlı Su Seviyesi Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of Water Level Sensor module connected to Door 7.
 */

#include <Pinoo.h>

// Door 7'ye bağlı Su Seviyesi Sensörü / Water Level Sensor connected to Door 7 (Analog)
Pinoo_WaterSensor waterSensor(DOOR7);

void setup() {
  Serial.begin(9600);
  waterSensor.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Su seviyesi analog değerini oku / Read raw analog water level value
  int level = waterSensor.readValue();

  // Değeri seri port ekrana yazdır / Print value to Serial monitor
  Serial.print("Su Seviyesi / Water Level: ");
  Serial.println(level);

  delay(200);
}
