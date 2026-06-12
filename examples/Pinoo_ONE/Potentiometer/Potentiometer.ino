/**
 * @file Potentiometer.ino
 * @brief Bilingual (TR/EN) example for Pinoo Potentiometer module.
 * 
 * Bu örnek Port 7'ye bağlı Potansiyometre modülünün kullanımını gösterir.
 * This example demonstrates usage of Potentiometer module connected to Port 7.
 */

#include <Pinoo.h>

// Port 7'ye bağlı Potansiyometre / Potentiometer connected to Port 7 (Analog)
Pinoo_Potentiometer pot(PORT7);

void setup() {
  Serial.begin(9600);
  pot.begin(); // Sensörü başlat / Initialize potentiometer
}

void loop() {
  // Değerleri oku / Read raw value and percentage position
  int raw = pot.readValue();
  int percent = pot.getValuePercentage();

  Serial.print("Potansiyometre: ");
  Serial.print(raw);
  Serial.print(" (");
  Serial.print(percent);
  Serial.println("%)");

  delay(200);
}
