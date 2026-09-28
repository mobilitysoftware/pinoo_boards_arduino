/**
 * @file TempHumidity.ino
 * @brief Bilingual (TR/EN) example for Pinoo Temperature & Humidity Sensor.
 * 
 * Bu örnek Door 1'e bağlı Sıcaklık-Nem (DHT11) Sensörü modülünün kullanımını gösterir.
 * This example demonstrates usage of Temp-Humidity (DHT11) Sensor module connected to Door 1.
 */

#include <Pinoo.h>

// Door 1'e bağlı Sıcaklık-Nem Sensörü / DHT11 connected to Door 1 (Digital)
Pinoo_TempHumidity dht(DOOR1);

void setup() {
  Serial.begin(9600);
  dht.begin(); // DHT11'i başlat / Initialize sensor
}

void loop() {
  // Ölçüm yap / Perform reading
  if (dht.read()) {
    float temp = dht.getTemperature();
    float hum = dht.getHumidity();

    Serial.print("Sicaklik / Temp: ");
    Serial.print(temp);
    Serial.print(" *C | Nem / Humidity: ");
    Serial.print(hum);
    Serial.println("%");
  } else {
    Serial.println("Sensor okunamadi / Sensor read failed");
  }

  delay(2000); // En az 2 saniye bekletilmeli / Wait at least 2 seconds
}
