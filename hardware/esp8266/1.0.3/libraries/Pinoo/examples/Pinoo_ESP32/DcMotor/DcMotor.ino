/**
 * @file DcMotor.ino
 * @brief Pinoo ESP32 Shield — Dahili DC Motor kontrol örneği.
 *
 * Bu örnek Pinoo ESP32 Shield üzerindeki tümleşik L293D motor sürücü ile
 * bağlı olan DC motorların (Motor 1 ve Motor 2) nasıl sürüleceğini gösterir.
 *
 * Motor Sürücü Pin Tanımları / Driver Pin Out:
 *   Motor 1 → A: D0, B: D2
 *   Motor 2 → A: D4, B: D15
 *
 * Bilingual (TR/EN) built-in DC Motor control example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Dahili DC Motorlar / On-board DC Motors (L293D)
Pinoo_DcMotor motor1(PINOO_ESP32_MOTOR1_A, PINOO_ESP32_MOTOR1_B);
Pinoo_DcMotor motor2(PINOO_ESP32_MOTOR2_A, PINOO_ESP32_MOTOR2_B);

void setup() {
  // Motorları başlat / Initialize motors
  motor1.begin();
  motor2.begin();
}

void loop() {
  // Motorları ileri tam hız sür / Drive motors forward full speed (255)
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  delay(2000);

  // Motorları yavaşça durdur / Coast to a stop
  motor1.stop();
  motor2.stop();
  delay(1000);

  // Motorları geri yarım hız sür / Drive motors backward half speed (-128)
  motor1.setSpeed(-128);
  motor2.setSpeed(-128);
  delay(2000);

  // Motorları kilitleyerek aktif fren yap / Brake motors actively
  motor1.brake();
  motor2.brake();
  delay(2000);
}
