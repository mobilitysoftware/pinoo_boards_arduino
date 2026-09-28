/**
 * @file Tilt.ino
 * @brief Bilingual (TR/EN) example for Pinoo Tilt/Vibration Sensor module.
 * 
 * Bu örnek Door 1'e bağlı Eğim ve Darbe Sensörünün kullanımını gösterir.
 * This example demonstrates usage of Tilt and Vibration Sensor connected to Door 1.
 */

#include <Pinoo.h>

// Door 1'e bağlı Eğim/Darbe Sensörü / Tilt sensor connected to Door 1 (Digital)
Pinoo_Tilt tiltSensor(DOOR1);

void setup() {
  Serial.begin(9600);
  tiltSensor.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Eğim/darbe algılandı mı oku / Check if tilted
  bool tilted = tiltSensor.isTilted();

  Serial.print("Sensor Durumu: ");
  if (tilted) {
    Serial.println("EGIM-DARBE ALGILANDI / TILT DETECTED");
  } else {
    Serial.println("NORMAL");
  }

  delay(100);
}
