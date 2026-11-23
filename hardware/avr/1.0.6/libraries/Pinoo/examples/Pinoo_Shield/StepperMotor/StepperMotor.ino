/**
 * @file StepperMotor.ino
 * @brief Bilingual (TR/EN) example for Pinoo Stepper motor module.
 * 
 * Bu örnek kartın motor sürücü çıkışına bağlı bir step motorun nasıl kontrol edileceğini gösterir.
 * This example demonstrates how to control a stepper motor connected to the card's motor driver output.
 */

#include <Pinoo.h>

// Varsayılan motor sürücü pinleri ile Step Motor nesnesi oluştur / Create Stepper motor object with default driver pins (IN1=11, IN2=10, IN3=6, IN4=5)
Pinoo_Stepper stepper;

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
