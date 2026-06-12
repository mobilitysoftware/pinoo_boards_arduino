/**
 * @file DcMotor.ino
 * @brief Bilingual (TR/EN) example for Pinoo DC Motor module.
 * 
 * Bu örnek kart üzerindeki DC motor sürücü terminallerinin nasıl kontrol edileceğini gösterir.
 * This example demonstrates how to control the DC motor driver terminals on the board.
 */

#include <Pinoo.h>

// Sol ve Sağ motorları tanımla / Declare Left and Right DC motors
Pinoo_DcMotor leftMotor(LEFT_MOTOR);
Pinoo_DcMotor rightMotor(RIGHT_MOTOR);

void setup() {
  leftMotor.begin();  // Motorları başlat / Initialize motors
  rightMotor.begin();
}

void loop() {
  // Motorları ileri tam hız sür / Drive motors forward full speed
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
  delay(2000);

  // Motorları durdur / Stop motors
  leftMotor.stop();
  rightMotor.stop();
  delay(1000);

  // Motorları geri yarım hız sür / Drive motors backward half speed
  leftMotor.setSpeed(-128);
  rightMotor.setSpeed(-128);
  delay(2000);

  // Motorları kilitle (aktif fren) / Actively brake motors
  leftMotor.brake();
  rightMotor.brake();
  delay(2000);
}
