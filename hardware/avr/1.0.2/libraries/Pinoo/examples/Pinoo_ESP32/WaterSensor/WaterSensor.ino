/**
 * @file WaterSensor.ino
 * @brief Pinoo ESP32 Shield — Su Seviyesi Sensörü kullanım örneği.
 *
 * Bu örnek Port 8'e bağlı Su Seviyesi sensöründen su seviyesi miktarını (%)
 * analog olarak okumayı gösterir.
 *
 * UYARI: Port 8 (D32/D33) analog okumayı (ADC) destekler. ESP32 12-bit ADC
 * değeri SDK tarafından otomatik olarak 10-bit (0-1023) aralığına ölçeklenir.
 *
 * Bilingual (TR/EN) Water Level Sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 8 üzerinde Su Seviyesi Sensörü / Water Level Sensor on Port 8 (D32)
Pinoo_WaterSensor suSensoru(DOOR8);

void setup() {
  Serial.begin(115200);
  suSensoru.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Ham analog seviyeyi ve yüzde miktarını oku
  // Read raw analog value and level percentage
  int hamDeger = suSensoru.readValue();
  int yuzde = map(hamDeger, 0, 1023, 0, 100);

  Serial.print("Ham Deger / Raw: ");
  Serial.print(hamDeger);
  Serial.print(" | Su Seviyesi / Water Level: ");
  Serial.print(yuzde);
  Serial.println("%");

  delay(300);
}
