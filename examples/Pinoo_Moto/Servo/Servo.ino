/**
 * @file Servo.ino
 * @brief Bilingual (TR/EN) example for Pinoo Servo motor module.
 * 
 * Bu örnek Pinoo Moto'nun motor sürücüsünün (PCA9685) 8. kanalına bağlı servo motorun nasıl kontrol edileceğini gösterir.
 * Pinoo Moto'da servo bir kapıya (DOOR) değil, motor sürücü kanalına (0-15) bağlanır.
 * This example demonstrates how to control a servo motor connected to channel 8 of the Pinoo Moto motor driver (PCA9685).
 * On Pinoo Moto a servo connects to a motor driver channel (0-15), not to a door.
 */

#include <Pinoo.h>

// PCA9685 kanal 8'e (Sürücü 3) bağlı Servo motor / Servo motor connected to PCA9685 channel 8 (driver block 3)
Pinoo_Servo myServo(8);

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
