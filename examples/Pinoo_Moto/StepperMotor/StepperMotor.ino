/**
 * @file StepperMotor.ino
 * @brief Bilingual (TR/EN) example for Pinoo Stepper motor module.
 * 
 * Bu örnek kartın motor sürücü çıkışına bağlı bir step motorun nasıl kontrol edileceğini gösterir.
 * This example demonstrates how to control a stepper motor connected to the card's motor driver output.
 */

#include <Pinoo.h>

// STEPPER2 kanalındaki Step Motor (Sürücü 2, PCA9685 kanal 4-7) / Stepper motor on channel STEPPER2 (driver block 2, PCA9685 channels 4-7)
// Kanallar: STEPPER1=0-3, STEPPER2=4-7, STEPPER3=8-11, STEPPER4=12-15 / Channels: STEPPER1=0-3, STEPPER2=4-7, STEPPER3=8-11, STEPPER4=12-15
Pinoo_Stepper stepper(STEPPER2);

void setup() {
  stepper.begin(); // Step motoru başlat / Initialize Stepper motor
}

void loop() {
  // Saat yönünde 64 adım dön (5ms gecikme ile) / Rotate 64 steps clockwise (with 5ms delay)
  stepper.stepCW(64, 5);
  delay(1000); // 1 saniye bekle / Wait 1 second

  // Saat yönünün tersine 64 adım dön (5ms gecikme ile) / Rotate 64 steps counter-clockwise (with 5ms delay)
  stepper.stepCCW(64, 5);
  delay(1000); // 1 saniye bekle / Wait 1 second

  // Motor bobinlerini serbest bırak (ısınmayı önlemek için) / Release motor coils (to prevent overheating)
  stepper.stop();
  delay(2000); // 2 saniye bekle / Wait 2 seconds
}
