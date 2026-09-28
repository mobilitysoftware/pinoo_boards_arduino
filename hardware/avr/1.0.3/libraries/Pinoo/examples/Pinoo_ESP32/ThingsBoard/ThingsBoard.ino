/**
 * @file ThingsBoard.ino
 * @brief Pinoo ESP32 Shield — ThingsBoard IoT Telemetri Gönderim Örneği.
 *
 * Bu örnek, ESP32'nin WiFi özelliğini kullanarak Pinoo IoT sunucusuna (iot.pinoo.io)
 * bağlanmayı ve Port 5'e bağlı LDR (Işık) sensöründen okunan verileri telemetri
 * olarak göndermeyi gösterir.
 *
 * Gereksinimler / Requirements:
 *   - ThingsBoard sunucu adresi: iot.pinoo.io
 *   - Cihazınıza ait Access Token (ThingsBoard panelinden alınır)
 *   - Port 5'te LDR sensörü (veya simüle edilmiş veri)
 *
 * Durum Göstergesi (RGB LED) / Status Indicator:
 *   - Mavi: WiFi / Sunucuya bağlanılıyor
 *   - Yeşil (Kısa Flaş): Telemetri başarıyla gönderildi
 *   - Kırmızı: Bağlantı koptu / Bağlantı hatası
 *
 * NOT: Bu özellik sadece Pinoo ESP32 Shield'de mevcuttur.
 * AVR tabanlı kartlarda derlenmez.
 *
 * Bilingual (TR/EN) ThingsBoard telemetry example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

// Bu örneğin yalnızca ESP32 platformunda derlenmesini sağlıyoruz
// Enforce compilation only on ESP32 platform
#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

#include <WiFi.h>
#include <Arduino_MQTT_Client.h> // ThingsBoard için gereken MQTT istemcisi
#include <ThingsBoard.h>         // ThingsBoard SDK ana başlığı

// WiFi Ağ Bilgileri / WiFi Network Settings
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingsBoard Sunucu Bilgileri / ThingsBoard Server Settings
const char* tb_server = "iot.pinoo.io";       // Pinoo IoT Sunucusu / Pinoo IoT Server
const char* tb_token = "YOUR_DEVICE_TOKEN";   // Cihaz Erişim Anahtarı / Device Access Token
const uint16_t tb_port = 1883;                // Standart şifresiz MQTT portu / Unencrypted MQTT Port

// Sensörler ve Göstergeler / Sensors & Indicators
Pinoo_Ldr ldr(DOOR5);                  // Port 5'e bağlı LDR / Ldr sensor on Port 5
Pinoo_RgbLed rgb(PINOO_INTERNAL_RGB, 2); // Dahili RGB LED / On-board RGB LED

// Ağ ve MQTT istemcileri / Network and MQTT clients
WiFiClient espClient;
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient);

// WiFi bağlantısını başlatan fonksiyon / Initialize WiFi connection
void connectWiFi() {
  Serial.print("[WIFI] Ağa bağlanılıyor: ");
  Serial.println(ssid);
  
  // Bağlantı süresince LED'i mavi yap
  // Turn LED blue during connection
  rgb.setColorAll(0, 0, 255); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[WIFI] WiFi bağlantısı başarılı!");
  Serial.print("[WIFI] IP Adresi: ");
  Serial.println(WiFi.localIP());
}

// ThingsBoard sunucusuna bağlanmayı deneyen fonksiyon / Connect to ThingsBoard
void connectThingsBoard() {
  if (!tb.connected()) {
    Serial.print("[TB] Sunucuya bağlanılıyor: ");
    Serial.print(tb_server);
    Serial.print(" (Token: ");
    Serial.print(tb_token);
    Serial.println(")");

    rgb.setColorAll(0, 0, 255); // Bağlantı sırasında Mavi LED

    if (!tb.connect(tb_server, tb_token, tb_port)) {
      Serial.println("[TB] Sunucu bağlantısı başarısız!");
      rgb.setColorAll(255, 0, 0); // Hata durumunda Kırmızı LED
      delay(1000);
      return;
    }
    Serial.println("[TB] Sunucuya başarıyla bağlandı.");
    rgb.setColorAll(0, 255, 0); // Başarılı olunca kısa süre Yeşil
    delay(500);
    rgb.clear();
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- Pinoo ESP32 ThingsBoard Ornegi Baslatiliyor ---");

  ldr.begin();
  rgb.begin();
  rgb.setBrightness(40);
  rgb.clear();

  connectWiFi();
}

void loop() {
  // WiFi bağlantısını kontrol et, koptuysa tekrar bağlan
  // Check and reconnect WiFi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
    return;
  }

  // ThingsBoard bağlantısını kontrol et, koptuysa tekrar bağlan
  // Check and reconnect ThingsBoard if disconnected
  if (!tb.connected()) {
    connectThingsBoard();
    if (!tb.connected()) {
      delay(3000);
      return;
    }
  }

  // LDR sensöründen ışık yüzdesini oku
  // Read light percentage from LDR sensor
  int lightLevel = ldr.getLightPercentage();

  Serial.print("[DATA] Isik Seviyesi / Light Level: ");
  Serial.print(lightLevel);
  Serial.println("%");

  // Telemetriyi ThingsBoard sunucusuna gönder
  // Send telemetry value to ThingsBoard server
  // Key: "light", Value: lightLevel
  if (tb.sendTelemetryData("light", lightLevel)) {
    Serial.println("[TB] Telemetri verisi gonderildi. / Telemetry sent.");
    
    // Başarılı gönderimde kısa bir yeşil flaş
    // Short green flash on successful send
    rgb.setColorAll(0, 255, 0);
    delay(100);
    rgb.clear();
  } else {
    Serial.println("[TB] Telemetri gonderilemedi! / Telemetry send failed!");
    
    // Hata durumunda kısa kırmızı flaş
    // Short red flash on error
    rgb.setColorAll(255, 0, 0);
    delay(200);
    rgb.clear();
  }

  // ThingsBoard döngüsünü çalıştır (içsel mesajlaşmalar için)
  // Process internal ThingsBoard loop
  tb.loop();

  // 5 saniyede bir veri gönder
  // Send telemetry every 5 seconds
  delay(5000);
}
