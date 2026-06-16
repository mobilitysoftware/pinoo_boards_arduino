/**
 * @file Potentiometer.ino
 * @brief Bilingual (TR/EN) example for Pinoo Potentiometer module.
 * 
 * Bu örnek Door 3'e bağlı Potansiyometre modülünün kullanımını gösterir.
 * This example demonstrates usage of Potentiometer module connected to Door 3.
 */

#include <Pinoo.h>

// Door 3'e bağlı Potansiyometre / Potentiometer connected to Door 3 (Analog)
Pinoo_Potentiometer pot(DOOR3);

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
