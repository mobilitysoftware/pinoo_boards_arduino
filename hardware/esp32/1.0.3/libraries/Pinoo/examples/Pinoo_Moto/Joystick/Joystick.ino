/**
 * @file Joystick.ino
 * @brief Bilingual (TR/EN) example for Pinoo Joystick module.
 * 
 * Bu örnek Door 3'e bağlı Joystick modülünün kullanımını gösterir.
 * This example demonstrates usage of Joystick module connected to Door 3.
 */

#include <Pinoo.h>

// Door 3'e bağlı Joystick / Joystick connected to Door 3 (Dual Analog)
Pinoo_Joystick joystick(DOOR3);

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
