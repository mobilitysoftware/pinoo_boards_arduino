/**
 * @file WiFi.ino
 * @brief Pinoo ESP32 Shield — WiFiManager ile WiFi bağlantı örneği.
 *
 * Bu örnek ESP32'nin dahili WiFi özelliğini ve WiFiManager kütüphanesini
 * kullanarak kolayca kablosuz ağa bağlanmayı gösterir. Eğer kayıtlı bir ağ yoksa
 * veya bağlanamazsa, "Pinoo-ESP32-WiFi" adında bir Hotspot (AP) oluşturur.
 * Kullanıcı bu ağa bağlanıp 192.168.4.1 adresinden WiFi bilgilerini girebilir.
 *
 * Bağlantı durumları dahili RGB LED ile gösterilir:
 *   - Mavi (Blinking/Solid): AP / Konfigürasyon modunda
 *   - Yeşil (Solid): Bağlantı başarılı
 *   - Kırmızı: Bağlantı başarısız (Yeniden başlatılıyor)
 *
 * NOT: Bu özellik sadece Pinoo ESP32 Shield'de mevcuttur.
 * AVR tabanlı kartlarda (ONE, Shield, Bricky, Moto) derlenmez.
 *
 * Bilingual (TR/EN) WiFi connection example using WiFiManager for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

// Bu örneğin yalnızca ESP32 platformunda derlenmesini sağlıyoruz
// Enforce compilation only on ESP32 platform
#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

#include <WiFi.h>
#include <WiFiManager.h> // Türkçeleştirilmiş WiFiManager kütüphanesi / Localized WiFiManager

// Dahili RGB LED (GPIO 13, 2 LED zinciri)
// On-board RGB NeoPixel (GPIO 13, 2-LED chain)
Pinoo_RgbLed rgb(PINOO_INTERNAL_RGB, 2);

// WiFiManager konfigürasyon moduna girdiğinde çağrılacak callback fonksiyonu
// Callback function when WiFiManager enters configuration mode
void configModeCallback(WiFiManager *myWiFiManager) {
  Serial.println("[WIFI] Konfigurasyon Modu Aktif! / Configuration Mode Active!");
  Serial.print("[WIFI] Olusturulan Hotspot: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.println("[WIFI] Lutfen telefondan bu aga baglanip 192.168.4.1 adresini acin.");
  Serial.println("[WIFI] Please connect to this AP and open 192.168.4.1 on your browser.");
  
  // Konfigürasyon modunda olduğumuzu belirtmek için RGB LED'i Mavi yapıyoruz
  // Set RGB LED to Blue to indicate configuration mode
  rgb.setColorAll(0, 0, 255); 
}

void setup() {
  // Seri haberleşmeyi başlat / Initialize serial port
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- Pinoo ESP32 WiFiManager Baslatiliyor ---");

  // Dahili RGB LED'i başlat / Initialize on-board RGB LED
  rgb.begin();
  rgb.setBrightness(40);
  rgb.clear();

  // WiFiManager nesnesini oluştur / Instantiate WiFiManager
  WiFiManager wm;

  // Bilinen WiFi ağlarını sıfırlamak (test etmek) isterseniz alttaki satırın yorumunu kaldırın
  // Uncomment the line below if you want to reset saved WiFi credentials for testing
  // wm.resetSettings();

  // Konfigürasyon modu callback fonksiyonunu ata
  // Register the configuration mode callback
  wm.setAPCallback(configModeCallback);

  // Otomatik olarak bağlanmayı dene veya "Pinoo-ESP32-WiFi" adında AP başlat
  // Try to connect automatically or start "Pinoo-ESP32-WiFi" Access Point
  if (!wm.autoConnect("Pinoo-ESP32-WiFi")) {
    Serial.println("[WIFI] Baglanti kurulamadi ve zaman asimi olustu. Yeniden baslatiliyor...");
    Serial.println("[WIFI] Failed to connect and hit timeout. Restarting...");
    
    // Hata durumunda Kırmızı LED yakıp 3 saniye sonra ESP'yi yeniden başlat
    // Turn on Red LED on error and restart ESP after 3 seconds
    rgb.setColorAll(255, 0, 0);
    delay(3000);
    ESP.restart();
  }

  // Bağlantı başarılı ise buraya geçer
  // If connection is successful, execution continues here
  Serial.println("[WIFI] WiFi Baglantisi Basarili! / Connected Successfully!");
  Serial.print("[WIFI] IP Adresi / IP Address: ");
  Serial.println(WiFi.localIP());

  // Başarılı bağlantıyı belirtmek için Yeşil LED yakıyoruz
  // Set RGB LED to Green to indicate successful connection
  rgb.setColorAll(0, 255, 0);
}

void loop() {
  // WiFi bağlantı durumunu periyodik olarak kontrol et
  // Periodically check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    // Bağlantı sağlıklı ise RGB LED'i yavaşça yeşil yakıp söndür (nefes alma efekti)
    // Breathing Green effect if connection is healthy
    for (int b = 10; b <= 80; b += 2) {
      rgb.setBrightness(b);
      rgb.setColorAll(0, 255, 0);
      delay(30);
    }
    for (int b = 80; b >= 10; b -= 2) {
      rgb.setBrightness(b);
      rgb.setColorAll(0, 255, 0);
      delay(30);
    }
  } else {
    // Bağlantı koparsa Kırmızı LED yakıp yeniden bağlanmayı dene
    // If connection drops, light Red and attempt reconnect
    rgb.setColorAll(255, 0, 0);
    Serial.println("[WIFI] Baglanti koptu. Yeniden baglanilmaya calisiliyor...");
    WiFi.begin();
    delay(5000);
  }
}
