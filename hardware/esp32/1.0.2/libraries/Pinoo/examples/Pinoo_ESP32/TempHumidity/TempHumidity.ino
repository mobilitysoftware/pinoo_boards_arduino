/**
 * @file TempHumidity.ino
 * @brief Pinoo ESP32 Shield — Sıcaklık ve Nem (DHT) Sensörü örneği.
 *
 * Bu örnek Port 3'e bağlı olan Sıcaklık ve Nem (DHT11/DHT22) sensöründen 
 * ortamın sıcaklık (°C) ve nem (%) değerlerini okumayı gösterir.
 *
 * UYARI: DHT sensörleri donanımsal çift yönlü dijital haberleşme yapar.
 * Port 3 (D18/D19) bu işlem için uygundur.
 *
 * Bilingual (TR/EN) DHT Temp/Humidity Sensor example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 3 üzerinde Sıcaklık-Nem Sensörü / Temp-Humidity sensor on Port 3 (D18)
Pinoo_TempHumidity dht(DOOR3);

void setup() {
  Serial.begin(115200);
  dht.begin(); // Sensörü başlat / Initialize sensor
}

void loop() {
  // Sensör verilerini oku / Read sensor values
  if (dht.read()) {
    float sicaklik = dht.getTemperature();
    float nem = dht.getHumidity();

    Serial.print("Sıcaklık / Temp: ");
    Serial.print(sicaklik);
    Serial.print(" *C | Nem / Humidity: ");
    Serial.print(nem);
    Serial.println(" %");
  } else {
    Serial.println("DHT okuma hatası! / DHT reading failed!");
  }

  delay(2000);
}
