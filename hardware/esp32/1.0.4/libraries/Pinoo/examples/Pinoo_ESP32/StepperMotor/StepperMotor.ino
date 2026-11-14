/**
 * @file StepperMotor.ino
 * @brief Pinoo ESP32 Shield — Adım (Stepper) Motor kontrol örneği.
 *
 * Bu örnek tümleşik motor sürücü (L293D) pinlerini kullanarak bir adım motorunun
 * saat yönü (CW) ve saat yönü tersi (CCW) yönünde nasıl döndürüleceğini gösterir.
 *
 * Stepper Pin Mimarisi / Stepper Pin Mappings:
 *   Motor 1 & Motor 2 çıkışları kullanılır:
 *   IN1: D0, IN2: D2, IN3: D4, IN4: D15
 *
 * Bilingual (TR/EN) built-in Stepper Motor control example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Stepper motor pinleri / Stepper Motor driver pins
Pinoo_Stepper stepper(PINOO_ESP32_STEPPER_A, PINOO_ESP32_STEPPER_B, PINOO_ESP32_STEPPER_C, PINOO_ESP32_STEPPER_D);

void setup() {
  stepper.begin(); // Adım motorunu başlat / Initialize stepper
}

void loop() {
  // Saat yönünde (CW) 512 adım dön (Yaklaşık 90 derece)
  // Step clockwise 512 steps
  stepper.stepCW(512, 4); // 4ms adım gecikmesi / 4ms delay
  delay(1000);

  // Saat yönünün tersine (CCW) 512 adım dön
  // Step counter-clockwise 512 steps
  stepper.stepCCW(512, 4);
  
  // Bobinleri kapatıp enerji tasarrufu yap / Stop stepper and release coils
  stepper.stop();
  delay(2000);
}
