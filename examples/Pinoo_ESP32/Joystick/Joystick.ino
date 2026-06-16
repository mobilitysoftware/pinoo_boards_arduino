/**
 * @file Joystick.ino
 * @brief Pinoo ESP32 Shield — Joystick modülü kullanım örneği.
 *
 * Bu örnek Port 7'ye bağlı Joystick modülünün X ve Y eksen analog 
 * değerlerini okumayı gösterir.
 *
 * UYARI: Joystick modülü çift analog okuma gerektirir. Port 7 (D25/D26)
 * her iki pinde de ADC (analog giriş) desteği sunar.
 *
 * Bilingual (TR/EN) Joystick module example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 7 üzerinde Joystick / Joystick on Port 7 (X = D25, Y = D26)
Pinoo_Joystick joystick(DOOR7);

void setup() {
  Serial.begin(115200);
  joystick.begin(); // Joystick'i başlat / Initialize joystick
}

void loop() {
  // X ve Y eksen değerlerini oku (0 - 1023 aralığında ölçeklenir)
  // Read X and Y values (scaled automatically to 0 - 1023)
  int xVal = joystick.getX();
  int yVal = joystick.getY();

  // Joystick butonuna basılıp basılmadığını kontrol et
  // Check if joystick button is pressed
  bool butonBasili = joystick.isButtonPressed();

  Serial.print("X Eksen: ");
  Serial.print(xVal);
  Serial.print(" | Y Eksen: ");
  Serial.print(yVal);
  Serial.print(" | Buton: ");
  Serial.println(butonBasili ? "BASILI / PRESSED" : "SERBEST / RELEASED");

  delay(100);
}
