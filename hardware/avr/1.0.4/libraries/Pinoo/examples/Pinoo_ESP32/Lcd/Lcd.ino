/**
 * @file Lcd.ino
 * @brief Pinoo ESP32 Shield — I2C LCD Ekran kullanım örneği.
 *
 * Bu örnek Port 10 (donanımsal I2C portu) üzerine bağlı I2C LCD ekranın 
 * kullanımını gösterir.
 *
 * I2C Pin Mimarisi / I2C Pin Layout:
 *   SDA → D21
 *   SCL → D22
 *
 * Bilingual (TR/EN) I2C LCD Screen example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 10 üzerinde I2C LCD ekran (I2C adresi genelde 0x27 veya 0x3F olur)
// I2C LCD display on Port 10 (usually address 0x27 or 0x3F)
Pinoo_Lcd lcd(DOOR10);

void setup() {
  lcd.begin(); // LCD'yi başlat / Initialize LCD
  
  lcd.print("Pinoo ESP32!"); // İlk satıra yazı yaz / Print to first row
  lcd.setCursor(0, 1);
  lcd.print("I2C LCD Hazir"); // İkinci satıra yazı yaz / Print to second row
  delay(2000);
}

void loop() {
  // Ekrandaki belirli bir alanı temizleyip saniye sayacı yazdırıyoruz
  // Print running seconds counter on LCD screen
  lcd.setCursor(0, 1);
  lcd.print("Seconds: ");
  lcd.print(millis() / 1000);
  delay(500);
}
