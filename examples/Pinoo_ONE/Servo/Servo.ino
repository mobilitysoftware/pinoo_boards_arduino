/**
 * @file Servo.ino
 * @brief Bilingual (TR/EN) example for Pinoo Servo motor module.
 * 
 * Bu örnek Port 3'e bağlı Servo motor modülünün nasıl kontrol edileceğini gösterir.
 * This example demonstrates how to control a Servo motor module connected to Port 3.
 */

#include <Pinoo.h>

// Port 3'e bağlı Servo motor / Servo motor connected to Port 3
Pinoo_Servo myServo(PORT3);

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
