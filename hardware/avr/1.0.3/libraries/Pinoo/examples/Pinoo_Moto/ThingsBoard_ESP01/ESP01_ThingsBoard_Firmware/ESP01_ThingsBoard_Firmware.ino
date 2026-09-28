/**
 * @file ESP01_ThingsBoard_Firmware.ino
 * @brief Pinoo Moto için Akıllı Yapılandırmalı (SmartProv) Şeffaf IoT Köprüsü
 * 
 * Bu yazılım ESP-01 (ESP8266) modülüne yüklenir.
 * 
 * ÖZELLİKLER:
 * 1. SmartProv Captive Portal:
 *    - İlk açılışta veya ağa bağlanamadığında "Pinoo_IoT_Setup" adında bir Wi-Fi erişim noktası (AP) açar.
 *    - Kullanıcı telefon/bilgisayarla bağlanarak Wi-Fi ağını, şifresini ve ThingsBoard Token / Sunucu bilgilerini girer.
 *    - Kod içine hiçbir Wi-Fi veya API bilgisi sabit (hardcoded) yazılmaz!
 * 
 * 2. Şeffaf "Al - Ver - Gönder" İletişim Hattı:
 *    - ESP-01 üzerinde hiçbir sensör ya da motor mantığı barındırmaz.
 *    - Pinoo Moto'dan seri port üzerinden gelen telemetri satırlarını (JSON formatında) doğrudan ThingsBoard'a basar.
 *    - ThingsBoard'dan gelen uzaktan kontrol (RPC) emirlerini doğrudan seri porttan Pinoo Moto'ya iletir.
 *    - Pinoo Moto'dan "SYS:RESET_WIFI" komutu geldiğinde kayıtlı ağ bilgilerini silip tekrar kurulum moduna geçer.
 * 
 * Donanım:
 *   - ESP-01 (ESP8266, 1MB Flash)
 *   - Seri Port: 9600 Baud (Pinoo Moto ile uyumlu)
 * 
 * Kütüphaneler:
 *   - SmartProv (v2.1.3+)
 *   - PubSubClient
 * 
 * @author Pinoo Robotics
 */

#define SP_AP_PREFIX        "Pinoo_Moto_IoT" // Kurulum AP adı: Pinoo_Moto_IoT_XXXX
#define SP_RESET_PIN        0                // GPIO0 (Fabrika sıfırlama butonu)
#define SP_LED_PIN          2                // GPIO2 (Durum LED'i)
#define SP_RESET_HOLD_MS    3000             // Sıfırlama için basılı tutma süresi

#define MQTT_MAX_PACKET_SIZE 512             // ThingsBoard için yeterli MQTT paket boyutu

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SmartProv.h>

// =============================================================================
// NESNELER VE TANIMLAMALAR
// =============================================================================
SmartProv prov;
WiFiClient espClient;
PubSubClient mqttClient(espClient);

#define SERIAL_BAUD 9600

// ThingsBoard Yapılandırma Parametreleri
String tbServer = "iot.pinoo.io";
int    tbPort   = 1883;
String tbToken  = "";

unsigned long lastMqttRetry = 0;
bool tbConnectedLast = false;

// =============================================================================
// THINGSBOARD RPC (UZAKTAN KONTROL) GERİ ÇAĞIRMA (CALLBACK)
// =============================================================================
// ThingsBoard'dan gelen RPC komutlarını olduğu gibi Pinoo Moto'ya iletir (Şeffaf Köprü).
void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Topic formatı: v1/devices/me/rpc/request/{requestId}
  String topicStr = String(topic);
  String requestId = "";
  int lastSlash = topicStr.lastIndexOf('/');
  if (lastSlash != -1) {
    requestId = topicStr.substring(lastSlash + 1);
  }

  // Pinoo Moto'ya iletilen format:
  // RPC:<requestId>:<payload_json>
  // Örn: RPC:1:{"method":"setMotor","params":180}
  Serial.print("RPC:");
  Serial.print(requestId);
  Serial.print(":");
  Serial.println(message);
}

// =============================================================================
// THINGSBOARD MQTT BAĞLANTISI
// =============================================================================
boolean connectThingsBoard() {
  if (tbToken.length() == 0) {
    Serial.println("[ERROR:TB_TOKEN_EMPTY]");
    return false;
  }

  Serial.println("[STATUS:TB_CONNECTING]");
  // ThingsBoard MQTT'de kullanıcı adı Device Token'dır, şifre boştur.
  if (mqttClient.connect("PinooMoto_Bridge", tbToken.c_str(), NULL)) {
    Serial.println("[STATUS:TB_CONNECTED]");
    // RPC komutlarını dinle
    mqttClient.subscribe("v1/devices/me/rpc/request/+");
    tbConnectedLast = true;
    return true;
  } else {
    Serial.print("[ERROR:TB_CONNECT_FAILED:");
    Serial.print(mqttClient.state());
    Serial.println("]");
    tbConnectedLast = false;
    return false;
  }
}

// =============================================================================
// SETUP
// =============================================================================
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(100);

  Serial.println("\n[PINOO_MOTO_ESP01_SMARTPROV_START]");

  // SmartProv Kurulum Sayfasına Özel Form Alanları Ekleme
  // Bu alanlar captive portal sayfasında kullanıcının karşısına çıkar:
  prov.addField("tb_token",  "ThingsBoard Cihaz Token (Access Token)", "Token yapistiriniz");
  prov.addField("tb_server", "ThingsBoard Sunucu Adresi",              "iot.pinoo.io");
  prov.addField("tb_port",   "ThingsBoard Port (Standart: 1883)",      "1883");

  // SmartProv Başlat
  prov.begin(SP_RESET_PIN, SP_LED_PIN);

  // Wi-Fi bağlandığında çalışacak callback
  prov.onConnected([]() {
    Serial.println("[STATUS:WIFI_CONNECTED]");
    Serial.print("[INFO:IP:");
    Serial.print(prov.getIP());
    Serial.println("]");

    // Kayıtlı ThingsBoard parametrelerini flash'tan oku
    String savedServer = prov.getField("tb_server");
    String savedPort   = prov.getField("tb_port");
    String savedToken  = prov.getField("tb_token");

    if (savedServer.length() > 0) tbServer = savedServer;
    if (savedPort.length() > 0)   tbPort   = savedPort.toInt();
    if (savedToken.length() > 0)  tbToken  = savedToken;

    Serial.print("[INFO:TB_SERVER:");
    Serial.print(tbServer);
    Serial.println("]");

    mqttClient.setServer(tbServer.c_str(), tbPort);
    mqttClient.setCallback(onMqttMessage);

    connectThingsBoard();
  });
}

// =============================================================================
// LOOP
// =============================================================================
void loop() {
  // 1. SmartProv Durum Makinesini Güncelle (Captive Portal / Wi-Fi bağlantısı)
  prov.update();

  // Kurulum modunda ise (AP açık)
  if (prov.isSetupMode()) {
    // Kurulum modunda olduğunu Pinoo Moto'ya periyodik bildirebiliriz
    static unsigned long lastSetupNotify = 0;
    if (millis() - lastSetupNotify > 5000) {
      lastSetupNotify = millis();
      Serial.println("[STATUS:SETUP_MODE]");
    }
  }

  // 2. Wi-Fi ve MQTT Yönetimi
  if (prov.isConnected()) {
    if (!mqttClient.connected()) {
      if (tbConnectedLast) {
        Serial.println("[STATUS:TB_DISCONNECTED]");
        tbConnectedLast = false;
      }

      unsigned long now = millis();
      if (now - lastMqttRetry > 5000) {
        lastMqttRetry = now;
        connectThingsBoard();
      }
    } else {
      mqttClient.loop();
    }
  }

  // 3. ŞEFFAF KÖPRÜ: Pinoo Moto'dan Seri Porttan Gelen Verileri Oku
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();

    if (line.length() > 0) {
      // TELEMETRİ GÖNDERİMİ:
      // Pinoo Moto doğrudan JSON satırı gönderdiyse {"temp":25,...} veya TELEMETRY:{...}
      if (line.startsWith("{") && line.endsWith("}")) {
        if (mqttClient.connected()) {
          mqttClient.publish("v1/devices/me/telemetry", line.c_str());
          Serial.println("[STATUS:TELEMETRY_SENT]");
        } else {
          Serial.println("[ERROR:TB_NOT_CONNECTED]");
        }
      }
      else if (line.startsWith("TELEMETRY:") || line.startsWith("telemetry:")) {
        String payload = line.substring(line.indexOf(':') + 1);
        payload.trim();
        if (mqttClient.connected()) {
          mqttClient.publish("v1/devices/me/telemetry", payload.c_str());
          Serial.println("[STATUS:TELEMETRY_SENT]");
        } else {
          Serial.println("[ERROR:TB_NOT_CONNECTED]");
        }
      }
      // ATTRIBUTE (ÖZNİTELİK) GÖNDERİMİ:
      // Pinoo Moto kart özellikleri göndermek isterse (örn: ATTR:{"firmware":"1.0"})
      else if (line.startsWith("ATTR:") || line.startsWith("attr:")) {
        String payload = line.substring(line.indexOf(':') + 1);
        payload.trim();
        if (mqttClient.connected()) {
          mqttClient.publish("v1/devices/me/attributes", payload.c_str());
          Serial.println("[STATUS:ATTR_SENT]");
        }
      }
      // RPC YANITI:
      // ThingsBoard'a RPC sonucu dönmek gerekirse (örn: RPC_RESP:1:{"status":"ok"})
      else if (line.startsWith("RPC_RESP:")) {
        int firstColon = line.indexOf(':');
        int secondColon = line.indexOf(':', firstColon + 1);
        if (secondColon != -1) {
          String reqId = line.substring(firstColon + 1, secondColon);
          String respPayload = line.substring(secondColon + 1);
          String topic = "v1/devices/me/rpc/response/" + reqId;
          if (mqttClient.connected()) {
            mqttClient.publish(topic.c_str(), respPayload.c_str());
          }
        }
      }
      // SİSTEM / AYAR SIFIRLAMA EMRİ:
      // Pinoo Moto üzerindeki bir buton ile Wi-Fi/Token sıfırlanmak istenirse
      else if (line == "SYS:RESET_WIFI" || line == "RESET_WIFI") {
        Serial.println("[ACTION:RESETTING_CREDENTIALS]");
        prov.resetCredentials();
      }
      // DURUM SORGUSU
      else if (line == "SYS:STATUS?" || line == "STATUS?") {
        Serial.print("[STATUS:WIFI=");
        Serial.print(prov.isConnected() ? "CONNECTED" : (prov.isSetupMode() ? "SETUP_MODE" : "DISCONNECTED"));
        Serial.print(",TB=");
        Serial.print(mqttClient.connected() ? "CONNECTED" : "DISCONNECTED");
        Serial.println("]");
      }
    }
  }
}
