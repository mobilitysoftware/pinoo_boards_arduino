/**
 * @file SoilMoisture.ino
 * @brief Bilingual (TR/EN) example for Pinoo Soil Moisture Sensor module.
 * 
 * Bu örnek Port 8'e bağlı Toprak Nem Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of Soil Moisture Sensor module connected to Port 8.
 */

#include <Pinoo.h>

// Port 8'e bağlı Toprak Nem Sensörü / Soil Moisture Sensor connected to Port 8 (Analog)
Pinoo_SoilMoisture soilSensor(PORT8);

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
