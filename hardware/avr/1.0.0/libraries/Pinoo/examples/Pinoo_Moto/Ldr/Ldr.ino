/**
 * @file Ldr.ino
 * @brief Bilingual (TR/EN) example for Pinoo Ldr light sensor module.
 * 
 * Bu örnek Door 3'e bağlı Işık (LDR) Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of Light (LDR) Sensor module connected to Door 3.
 */

#include <Pinoo.h>

// Door 3'e bağlı Işık Sensörü / Light Sensor connected to Door 3 (Analog)
Pinoo_Ldr ldr(DOOR3);

void setup() {
  Serial.begin(9600);
  ldr.begin(); // LDR'yi başlat / Initialize LDR
}

void loop() {
  // Işık seviyesini oku / Read raw and percentage light levels
  int raw = ldr.readValue();
  int percent = ldr.getLightPercentage();

  // Değerleri seri port ekrana yazdır / Print values to Serial monitor
  Serial.print("Isik / Light: ");
  Serial.print(raw);
  Serial.print(" (");
  Serial.print(percent);
  Serial.println("%)");

  delay(500);
}
