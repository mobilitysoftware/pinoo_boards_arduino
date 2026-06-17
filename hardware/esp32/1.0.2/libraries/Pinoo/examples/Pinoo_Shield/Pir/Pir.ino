/**
 * @file Pir.ino
 * @brief Bilingual (TR/EN) example for Pinoo PIR Motion Sensor module.
 * 
 * Bu örnek Door 1'e bağlı PIR Hareket Sensörünün kullanımını gösterir.
 * This example demonstrates usage of PIR Motion Sensor connected to Door 1.
 */

#include <Pinoo.h>

// Door 1'e bağlı PIR Hareket Sensörü / PIR Motion Sensor connected to Door 1 (Digital)
Pinoo_Pir motionSensor(DOOR1);

void setup() {
  Serial.begin(9600);
  motionSensor.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Hareket algılandı mı kontrol et / Check if motion is detected
  bool motion = motionSensor.isMotionDetected();

  if (motion) {
    Serial.println("HAREKET ALGILANDI / MOTION DETECTED");
  } else {
    Serial.println("HAREKET YOK / NO MOTION");
  }

  delay(250);
}
