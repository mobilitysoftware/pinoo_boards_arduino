/**
 * @file SoilMoisture.ino
 * @brief Bilingual (TR/EN) example for Pinoo Soil Moisture Sensor module.
 * 
 * Bu örnek Door 3'e bağlı Toprak Nem Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of Soil Moisture Sensor module connected to Door 3.
 */

#include <Pinoo.h>

// Door 3'e bağlı Toprak Nem Sensörü / Soil Moisture Sensor connected to Door 3 (Analog)
Pinoo_SoilMoisture soilSensor(DOOR3);

void setup() {
  Serial.begin(9600);
  soilSensor.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Toprak nem seviyesini oku / Read raw and percentage moisture levels
  int raw = soilSensor.readValue();
  int percent = soilSensor.getMoisturePercentage();

  // Değerleri seri port ekrana yazdır / Print values to Serial monitor
  Serial.print("Nem / Moisture: ");
  Serial.print(raw);
  Serial.print(" (");
  Serial.print(percent);
  Serial.println("%)");

  delay(500);
}
