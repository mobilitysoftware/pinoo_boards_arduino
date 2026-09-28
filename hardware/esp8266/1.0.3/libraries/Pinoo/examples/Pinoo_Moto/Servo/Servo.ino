/**
 * @file Servo.ino
 * @brief Bilingual (TR/EN) example for Pinoo Servo motor module.
 * 
 * Bu örnek Door 2'ye bağlı Servo motor modülünün nasıl kontrol edileceğini gösterir.
 * This example demonstrates how to control a Servo motor module connected to Door 2.
 */

#include <Pinoo.h>

// Door 2'ye bağlı Servo motor / Servo motor connected to Door 2
Pinoo_Servo myServo(DOOR2);

void setup() {
  myServo.begin(); // Servo motoru başlat / Initialize servo
}

void loop() {
  // 0 dereceye git / Move to 0 degrees
  myServo.write(0);
  delay(1000);

  // 90 dereceye git / Move to 90 degrees
  myServo.write(90);
  delay(1000);

  // 180 dereceye git / Move to 180 degrees
  myServo.write(180);
  delay(1000);
}
