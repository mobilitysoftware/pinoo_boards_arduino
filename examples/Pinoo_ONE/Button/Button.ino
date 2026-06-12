/**
 * @file Button.ino
 * @brief Bilingual (TR/EN) example for Pinoo Button module.
 * 
 * Bu örnek Port 1'e bağlı Buton modülünün kullanımını gösterir.
 * This example demonstrates usage of Button module connected to Port 1.
 */

#include <Pinoo.h>

// Port 1'e bağlı Buton modülü / Button module connected to Port 1 (Digital)
Pinoo_Button button(PORT1);

void setup() {
  Serial.begin(9600);
  button.begin(); // Butonu başlat / Initialize button
}

void loop() {
  // Buton basılı mı kontrol et / Check if button is pressed
  bool pressed = button.isPressed();

  Serial.print("Buton Durumu / Button State: ");
  if (pressed) {
    Serial.println("BASILDI / PRESSED");
  } else {
    Serial.println("SERBEST / RELEASED");
  }

  delay(100);
}
