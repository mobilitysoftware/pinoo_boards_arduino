/**
 * @file DcMotor.ino
 * @brief Bilingual (TR/EN) example for Pinoo Moto DC motor outputs.
 *
 * Pinoo Moto üzerinde 8 adet DC motor çıkışı vardır: MOTOR1 ... MOTOR8.
 * "Sol" / "sağ" ayrımı yoktur; her çıkış bağımsızdır ve istediğin motoru istediğin
 * çıkışa bağlayabilirsin. Bu örnek MOTOR1 ve MOTOR2'ye bağlı iki motoru sürer.
 * Sürücü blokları: MOTOR1+MOTOR2, MOTOR3+MOTOR4, MOTOR5+MOTOR6, MOTOR7+MOTOR8.
 *
 * Pinoo Moto has 8 DC motor outputs: MOTOR1 ... MOTOR8.
 * There is no "left" / "right": every output is independent and you can connect
 * any motor to any output. This example drives two motors on MOTOR1 and MOTOR2.
 * Driver blocks: MOTOR1+MOTOR2, MOTOR3+MOTOR4, MOTOR5+MOTOR6, MOTOR7+MOTOR8.
 */

#include <Pinoo.h>

// Motorları tanımla / Declare the motors (MOTOR1 ... MOTOR8)
Pinoo_DcMotor motor1(MOTOR1);
Pinoo_DcMotor motor2(MOTOR2);

void setup() {
  motor1.begin();  // Motorları başlat / Initialize motors
  motor2.begin();
}

void loop() {
  // Motorları ileri tam hız sür / Drive motors forward full speed
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  delay(2000);

  // Motorları durdur / Stop motors
  motor1.stop();
  motor2.stop();
  delay(1000);

  // Motorları geri tam hız sür / Drive motors backward full speed
  motor1.setSpeed(-255);
  motor2.setSpeed(-255);
  delay(2000);

  // Motorları kilitle (aktif fren) / Actively brake motors
  motor1.brake();
  motor2.brake();
  delay(2000);
}
