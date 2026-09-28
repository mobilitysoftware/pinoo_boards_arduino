/**
 * @file Motors_Control.ino
 * @brief Bilingual (TR/EN) example for Pinoo Moto DC, Stepper, and Servo motor controls.
 * 
 * Bu örnek Pinoo Moto kartındaki PCA9685 sürücüsü üzerinden DC Motor, Step Motor
 * ve Servo Motorların nasıl kontrol edileceğini gösterir.
 * 
 * This example demonstrates how to control DC Motors, Stepper Motors,
 * and Servo Motors via the onboard PCA9685 driver on the Pinoo Moto board.
 */

#include <Pinoo.h>

// DC Motor nesnesi (MOTOR1 kanalında - Sürücü 1) / DC Motor object (on MOTOR1 channel - Driver 1)
Pinoo_DcMotor dcMotor(MOTOR1);

// Step Motor nesnesi (STEPPER2 kanalında - Sürücü 2) / Stepper Motor object (on STEPPER2 channel - Driver 2)
// Not: Aynı sürücü bloğu (Sürücü 1) üzerinde çakışma olmaması için STEPPER2 kullanılmıştır.
// Note: STEPPER2 is used to avoid resource conflict on the same driver block (Driver 1).
Pinoo_Stepper stepper(STEPPER2);

// Servo Motor nesnesi (PCA9685 kanal 8'de - Sürücü 3) / Servo Motor object (on PCA9685 channel 8 - Driver 3)
// Not: Aynı sürücü blokları ile çakışmaması için Sürücü 3 (Kanal 8) tercih edilmiştir.
// Note: Channel 8 on Driver 3 is used to prevent overlapping with other active driver blocks.
Pinoo_Servo servo(8);

void setup() {
  // Motorları başlat / Initialize motors
  dcMotor.begin();
  stepper.begin();
  servo.begin();
}

void loop() {
  // 1. DC Motor Testi / DC Motor Test
  dcMotor.setSpeed(255); // Tam hız ileri / Full speed forward
  delay(1500);
  dcMotor.setSpeed(-255); // Tam hız geri / Full speed backward
  delay(1500);
  dcMotor.stop(); // Motoru durdur / Stop motor
  delay(1000);

  // 2. Step Motor Testi / Stepper Motor Test
  stepper.stepCW(100, 5); // 100 adım saat yönünde dön / Rotate 100 steps CW
  delay(1000);
  stepper.stepCCW(100, 5); // 100 adım saat yönünün tersine dön / Rotate 100 steps CCW
  delay(1000);
  stepper.stop(); // Enerjiyi kes / Stop and release coils
  delay(1000);

  // 3. Servo Motor Testi / Servo Motor Test
  servo.write(0); // 0 dereceye git / Move to 0 degrees
  delay(1000);
  servo.write(90); // 90 dereceye git / Move to 90 degrees
  delay(1000);
  servo.write(180); // 180 dereceye git / Move to 180 degrees
  delay(1000);
  servo.detach(); // Servoyu serbest bırak / Detach servo
  delay(2000);
}
