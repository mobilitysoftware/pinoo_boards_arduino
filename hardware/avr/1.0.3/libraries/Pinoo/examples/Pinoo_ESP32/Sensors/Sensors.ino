/**
 * @file Sensors.ino
 * @brief Pinoo ESP32 Shield — Port sensörlerinin kullanım örneği.
 *
 * Bu örnek Port 5 ve Port 9 (input-only analog portlar) ile
 * Port 8 (dual analog, 3.3V) kullanımını gösterir.
 *
 * UYARI: ESP32 ADC 12-bit (0–4095) değer üretir.
 * Pinoo SDK içindeki PINOO_ANALOG_READ() makrosu bunu otomatik olarak
 * 10-bit (0–1023) değere dönüştürür — tüm Pinoo kartlarıyla uyumlu çalışır.
 *
 * Port Haritası / Port Map:
 *   Port 5  (5V, INPUT ONLY) → Pin A: D36 (A1-0), Pin B: D39 (A1-3)
 *   Port 8  (3V3, dual)      → Pin A: D32 (A1-4), Pin B: D33 (A1-5)
 *   Port 9  (5V, INPUT ONLY) → Pin A: D34 (A1-6), Pin B: D35 (A1-7)
 *   Port 10 (5V, I2C)        → SDA: D21, SCL: D22
 *
 * Bilingual (TR/EN) sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

// Port 8 üzerinde LDR (Pin A = D32) / LDR on Port 8 (Pin A = D32)
Pinoo_Ldr ldr(DOOR8);

// Port 5 üzerinde potansiyometre (Pin A = D36, INPUT ONLY)
// Potentiometer on Port 5 (Pin A = D36, input-only)
Pinoo_Potentiometer pot(DOOR5);

// Port 9 üzerinde toprak nem sensörü (Pin A = D34, INPUT ONLY)
// Soil moisture sensor on Port 9 (Pin A = D34, input-only)
Pinoo_SoilMoisture toprakNem(DOOR9);

// Port 10 üzerinde LCD ekran (I2C: SDA=D21, SCL=D22)
// LCD display on Port 10 (I2C: SDA=D21, SCL=D22)
Pinoo_Lcd lcd(DOOR10);

void setup() {
  Serial.begin(115200);

  ldr.begin();
  pot.begin();
  toprakNem.begin();
  lcd.begin();

  lcd.print("Pinoo ESP32");
  lcd.setCursor(0, 1);
  lcd.print("Sensors Ready");
  delay(1500);
  lcd.clear();

  Serial.println("Pinoo ESP32 Sensor Ornegi / Sensor Example");
}

void loop() {
  // Sensör okumalar / Sensor readings
  int isikYuzdesi     = ldr.getLightPercentage();
  int potYuzdesi      = pot.getValuePercentage();
  int toprakYuzdesi   = toprakNem.getMoisturePercentage();

  // Seri monitöre yazdır / Print to Serial Monitor
  Serial.print("Isik/Light: ");
  Serial.print(isikYuzdesi);
  Serial.print("% | Pot: ");
  Serial.print(potYuzdesi);
  Serial.print("% | Toprak Nem/Soil: ");
  Serial.print(toprakYuzdesi);
  Serial.println("%");

  // LCD ekrana yazdır / Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Isik:");
  lcd.print(isikYuzdesi);
  lcd.print("% Pot:");
  lcd.print(potYuzdesi);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Toprak Nem: ");
  lcd.print(toprakYuzdesi);
  lcd.print("%");

  delay(500);
}
