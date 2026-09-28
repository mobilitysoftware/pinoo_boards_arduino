/**
 * @file PinooMoto_ThingsBoard_Client.ino
 * @brief Pinoo Moto için Akıllı ThingsBoard İstemcisi ve RPC Yöneticisi
 * 
 * Bu yazılım Pinoo Moto kartına (ATmega328P) yüklenir.
 * Kart üzerindeki ESP-01 modülü (SmartProv ile programlanmış) ile Seri Port (9600 Baud)
 * üzerinden konuşur.
 * 
 * ÇALIŞMA PRENSİBİ:
 * 1. ESP-01 tarafı tamamen "şeffaf köprüdür"; Wi-Fi ve ThingsBoard bağlantısını yönetir.
 * 2. Pinoo Moto tarafı ise tüm robotik mantığı ve RPC tanımlamalarını barındırır:
 *    - Sensör verilerini okur ve JSON formatında ESP-01'e aktarır (Telemetri Gönderimi).
 *    - ThingsBoard'dan gelen uzaktan kontrol komutlarını (RPC) ayrıştırır ve motorları/eyleyicileri çalıştırır.
 *    - İstenirse ThingsBoard'a RPC cevabı (response) döner.
 *    - Kart üzerindeki bir durumdan veya butondan ESP-01'in Wi-Fi ayarlarını sıfırlayabilir ("SYS:RESET_WIFI").
 * 
 * ÖNEMLİ:
 * Pinoo Moto'ya bu kodu yüklerken ESP-01 modülü kart soketinden GEÇİCİ OLARAK ÇIKARILMALIDIR!
 * Yükleme bittikten sonra ESP-01 yerine takılmalıdır.
 * 
 * @author Pinoo Robotics
 */

#include <Pinoo.h>

// =============================================================================
// DONANIM VE BİLEŞEN TANIMLAMALARI
// =============================================================================

// Door 3'e bağlı LDR (Işık Sensörü)
Pinoo_Ldr ldr(DOOR3);

// Pinoo Moto üzerindeki Dahili Pasif Buzzer (Pin 8)
Pinoo_Buzzer buzzer(PINOO_MOTO_INTERNAL_BUZZER);

// Pinoo Moto üzerindeki Dahili RGB LED (Pin 9)
Pinoo_RgbLed rgb(PINOO_MOTO_INTERNAL_RGB, 2);

// Motor 1 (DC Motor Kontrolü için)
Pinoo_DcMotor motor1(MOTOR1);

// Telemetri gönderim periyodu (ms)
const unsigned long TELEMETRY_INTERVAL = 3000;
unsigned long lastTelemetryTime = 0;

// =============================================================================
// RPC (UZAKTAN KONTROL) KOMUT YÖNETİCİSİ (RPC DISPATCHER)
// =============================================================================
/**
 * ThingsBoard platformundan gelen RPC komutları burada işlenir.
 * Yeni bir kontrol eklemek istediğinizde (örn: servo, diğer motorlar)
 * sadece bu fonksiyona yeni bir "else if" eklemeniz yeterlidir!
 */
void handleRpc(String requestId, String method, String params) {
  // 1. DC Motor Hız ve Yön Kontrolü
  // Örnek ThingsBoard çağrısı: method = "setMotor", params = 150 (-255 ile 255 arası)
  if (method.equalsIgnoreCase("setMotor") || method.equalsIgnoreCase("motorSpeed")) {
    int speed = params.toInt();
    motor1.setSpeed(speed);
  }
  // 2. Motor Durdurma
  else if (method.equalsIgnoreCase("stopMotor")) {
    motor1.stop();
  }
  // 3. Buzzer Kontrolü (Aç/Kapat veya Frekans)
  // Örnek: method = "setBuzzer", params = true / false / 1 / 0 / 1500
  else if (method.equalsIgnoreCase("setBuzzer")) {
    if (params == "true" || params == "1") {
      buzzer.playTone(1000); // 1000 Hz ses üret
    } else if (params == "false" || params == "0") {
      buzzer.stop();
    } else {
      // Sayısal frekans verildiyse o tonda çal
      int freq = params.toInt();
      if (freq > 0) buzzer.playTone(freq);
      else buzzer.stop();
    }
  }
  // 4. Dahili RGB LED Renk Kontrolü
  else if (method.equalsIgnoreCase("setLed")) {
    if (params == "true" || params == "1") {
      rgb.setColorAll(0, 255, 0); // Yeşil
    } else if (params == "false" || params == "0") {
      rgb.clear();
    } else if (params.equalsIgnoreCase("red") || params.equalsIgnoreCase("kirmizi")) {
      rgb.setColorAll(255, 0, 0);
    } else if (params.equalsIgnoreCase("blue") || params.equalsIgnoreCase("mavi")) {
      rgb.setColorAll(0, 0, 255);
    }
  }
  // 5. Uzaktan Wi-Fi / Token Ayarlarını Sıfırlama (Provisioning Moduna Alma)
  else if (method.equalsIgnoreCase("resetWifi")) {
    Serial.println("SYS:RESET_WIFI");
    rgb.setColorAll(0, 0, 255);
  }

  // ThingsBoard'a RPC yanıtı (Response) döndür
  // Format: RPC_RESP:<requestId>:<payload>
  if (requestId.length() > 0) {
    Serial.print("RPC_RESP:");
    Serial.print(requestId);
    Serial.println(":{\"status\":\"ok\"}");
  }
}

// =============================================================================
// GELEN SERİ VERİLERİ AYRIŞTIRICI (PARSER)
// =============================================================================
void processIncomingSerial(String line) {
  // Format: RPC:<requestId>:<json_payload>
  // Örn: RPC:1:{"method":"setMotor","params":180}
  if (line.startsWith("RPC:")) {
    int firstColon = line.indexOf(':');
    int secondColon = line.indexOf(':', firstColon + 1);

    if (secondColon != -1) {
      String requestId = line.substring(firstColon + 1, secondColon);
      String payload = line.substring(secondColon + 1);

      // Metod ve parametreyi JSON içerisinden ayrıştır
      int methodStart = payload.indexOf("\"method\":\"");
      if (methodStart != -1) {
        methodStart += 10;
        int methodEnd = payload.indexOf("\"", methodStart);
        String method = payload.substring(methodStart, methodEnd);

        int paramsStart = payload.indexOf("\"params\":", methodEnd);
        String params = "";
        if (paramsStart != -1) {
          paramsStart += 9;
          while (paramsStart < (int)payload.length() && payload[paramsStart] == ' ') paramsStart++;
          int paramsEnd = payload.indexOf("}", paramsStart);
          if (paramsEnd != -1) {
            params = payload.substring(paramsStart, paramsEnd);
            params.replace("\"", "");
            params.trim();
          }
        }

        handleRpc(requestId, method, params);
      }
    }
  }
  // ESP-01 Durum Bildirimleri
  else if (line == "[STATUS:SETUP_MODE]") {
    // ESP-01 kurulum modunda (AP açık); RGB LED'i sarı yaparak kullanıcıya bildir
    rgb.setColorAll(255, 150, 0);
  }
  else if (line == "[STATUS:TB_CONNECTED]") {
    // ThingsBoard'a başarıyla bağlandı; yeşil flaş
    rgb.setColorAll(0, 255, 0);
    delay(200);
    rgb.clear();
  }
  else if (line == "[STATUS:TB_DISCONNECTED]") {
    // Bağlantı koptu; kırmızı flaş
    rgb.setColorAll(255, 0, 0);
    delay(200);
    rgb.clear();
  }
}

// =============================================================================
// SETUP
// =============================================================================
void setup() {
  // ESP-01 ile haberleşme (9600 baud)
  Serial.begin(9600);

  // Donanımları başlat
  ldr.begin();
  buzzer.begin();
  rgb.begin();
  rgb.setBrightness(40);
  rgb.clear();
  motor1.begin();

  // Açılış LED efekti (Mavi)
  rgb.setColorAll(0, 0, 255);
  delay(400);
  rgb.clear();
}

// =============================================================================
// LOOP
// =============================================================================
void loop() {
  // 1. TELEMETRİ GÖNDERİMİ (Sensör Verilerini ThingsBoard'a Aktar)
  unsigned long currentMillis = millis();
  if (currentMillis - lastTelemetryTime >= TELEMETRY_INTERVAL) {
    lastTelemetryTime = currentMillis;

    int lightPercentage = ldr.getLightPercentage();

    // Veriyi standart JSON satırı olarak ESP-01'e gönder
    // ESP-01 bu satırı doğrudan ThingsBoard telemetri konusuna basar.
    Serial.print("{\"light\":");
    Serial.print(lightPercentage);
    Serial.println("}");
  }

  // 2. GELEN KOMUTLARI DİNLE (ThingsBoard RPC -> ESP-01 -> Pinoo Moto)
  while (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      processIncomingSerial(line);
    }
  }
}
