/**
 * @file Lcd.ino
 * @brief Bilingual (TR/EN) example for Pinoo LCD Screen module.
 * 
 * Bu örnek Door 10'a bağlı I2C LCD Ekran modülünün kullanımını gösterir.
 * This example demonstrates usage of I2C LCD Screen module connected to Door 10.
 */

#include <Pinoo.h>

// Door 10'a bağlı I2C LCD ekran / I2C LCD screen connected to Door 10 (Hardware I2C)
Pinoo_Lcd lcd(DOOR10);

void setup() {
  lcd.begin(); // Ekranı başlat / Initialize LCD
  
  // Arka ışığı aç / Turn on backlight
  lcd.backlight();

  // Ekranı temizle / Clear screen
  lcd.clear();

  // Yazı yazdır / Print text
  lcd.print("Pinoo Robotics!");
  
  // Kursörü 2. satıra getir (Sütun 0, Satır 1)
  // Move cursor to 2nd row (Column 0, Row 1)
  lcd.setCursor(0, 1);
  lcd.print("I2C LCD Screen");
}

void loop() {
  // Dongude yapilacak bir sey yok / Nothing to repeat in loop
}
