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
bool handleRpc(String requestId, String method, String params) {
  bool handled = false;  // Komut tanındı ve uygulandı mı? / Was the command recognised and applied?

  // 1. DC Motor Hız ve Yön Kontrolü
  // Örnek ThingsBoard çağrısı: method = "setMotor", params = 150 (-255 ile 255 arası)
  if (method.equalsIgnoreCase("setMotor") || method.equalsIgnoreCase("motorSpeed")) {
    int speed = params.toInt();
    motor1.setSpeed(speed);
    handled = true;
  }
  // 2. Motor Durdurma
  else if (method.equalsIgnoreCase("stopMotor")) {
    motor1.stop();
    handled = true;
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
    handled = true;
  }
  // 4. Dahili RGB LED Renk Kontrolü
  else if (method.equalsIgnoreCase("setLed")) {
    if (params == "true" || params == "1") {
      rgb.setColorAll(0, 255, 0); // Yeşil
      handled = true;
    } else if (params == "false" || params == "0") {
      rgb.clear();
      handled = true;
    } else if (params.equalsIgnoreCase("red") || params.equalsIgnoreCase("kirmizi")) {
      rgb.setColorAll(255, 0, 0);
      handled = true;
    } else if (params.equalsIgnoreCase("blue") || params.equalsIgnoreCase("mavi")) {
      rgb.setColorAll(0, 0, 255);
      handled = true;
    }
  }
  // 5. Uzaktan Wi-Fi / Token Ayarlarını Sıfırlama (Provisioning Moduna Alma)
  else if (method.equalsIgnoreCase("resetWifi")) {
    Serial.println("SYS:RESET_WIFI");
    rgb.setColorAll(0, 0, 255);
    handled = true;
  }

  // ThingsBoard'a RPC yanıtı (Response) döndür
  // Format: RPC_RESP:<requestId>:<payload>
  // Komut tanınmadıysa "error" döner, böylece ThingsBoard hatayı görebilir.
  if (requestId.length() > 0) {
    Serial.print("RPC_RESP:");
    Serial.print(requestId);
    Serial.println(handled ? ":{\"status\":\"ok\"}" : ":{\"status\":\"error\"}");
  }
  return handled;
}

// =============================================================================
// JSON DEĞER OKUYUCU (JSON VALUE READER)
// =============================================================================
/**
 * {"method":"setMotor","params":180} gibi bir satırdan verilen anahtarın değerini döndürür.
 * - Alanların sırası fark etmez ("params" "method"tan önce gelebilir).
 * - Sayı, true/false ve metin değerlerini okur (tırnaklar kaldırılır).
 * - İç içe nesne ya da dizi değerini ham metin olarak döndürür ({r:255,g:0} gibi).
 * Reads the value of a key from a one-line JSON object. Key order does not matter.
 */
String jsonValue(const String& payload, const char* key) {
  char needle[24];
  snprintf(needle, sizeof(needle), "\"%s\":", key);

  int i = payload.indexOf(needle);
  if (i == -1) return "";
  i += strlen(needle);
  while (i < (int)payload.length() && payload[i] == ' ') i++;

  int depth = 0;
  bool inString = false;
  int j = i;
  for (; j < (int)payload.length(); j++) {
    char c = payload[j];
    if (c == '"') inString = !inString;
    if (inString) continue;
    if (c == '{' || c == '[') depth++;
    else if (c == '}' || c == ']') {
      if (depth == 0) break;  // Üst nesnenin sonu / end of the outer object
      depth--;
    }
    else if (c == ',' && depth == 0) break;
  }

  String value = payload.substring(i, j);
  value.replace("\"", "");
  value.trim();
  return value;
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

      // Metod ve parametreyi JSON içerisinden ayrıştır (alan sırası fark etmez)
      String method = jsonValue(payload, "method");
      String params = jsonValue(payload, "params");

      if (method.length() > 0) {
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
