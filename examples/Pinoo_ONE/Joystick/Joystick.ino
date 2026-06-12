/**
 * @file Joystick.ino
 * @brief Bilingual (TR/EN) example for Pinoo Joystick module.
 * 
 * Bu örnek Port 9'a bağlı Joystick modülünün kullanımını gösterir.
 * This example demonstrates usage of Joystick module connected to Port 9.
 */

#include <Pinoo.h>

// Port 9'a bağlı Joystick / Joystick connected to Port 9 (Dual Analog)
Pinoo_Joystick joystick(PORT9);

void setup() {
  Serial.begin(9600);
  joystick.begin(); // Joystick'i başlat / Initialize Joystick
}

void loop() {
  // X ve Y eksen değerlerini oku / Read X and Y values
  int xVal = joystick.getX();
  int yVal = joystick.getY();

  // Değerleri seri port ekranına yazdır / Print to Serial monitor
  Serial.print("Joystick X: ");
  Serial.print(xVal);
  Serial.print(" | Y: ");
  Serial.println(yVal);

  delay(200);
}
