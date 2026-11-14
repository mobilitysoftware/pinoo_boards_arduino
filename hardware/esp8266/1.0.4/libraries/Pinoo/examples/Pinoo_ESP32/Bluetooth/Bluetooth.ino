/**
 * @file Bluetooth.ino
 * @brief Pinoo ESP32 Shield — Dahili BLE/WiFi Bluetooth örneği.
 *
 * Bu örnek ESP32'nin dahili Bluetooth Classic Serial (SerialBT) özelliğini
 * kullanarak bir bluetooth terminalinden komut alıp DC motorları kontrol
 * etmeyi gösterir.
 *
 * Gereksinimler / Requirements:
 *   - "BluetoothSerial" kütüphanesi (Arduino-ESP32 core ile birlikte gelir)
 *   - Telefonda bir Bluetooth Serial Terminal uygulaması
 *     (örn. Serial Bluetooth Terminal - Android)
 *
 * Komutlar / Commands (terminal üzerinden / via terminal):
 *   'f' → İleri / Forward
 *   'b' → Geri / Backward
 *   'l' → Sol / Left (Motor 1 dur, Motor 2 ileri)
 *   'r' → Sağ / Right (Motor 1 ileri, Motor 2 dur)
 *   's' → Dur / Stop
 *
 * NOT: Bu özellik sadece Pinoo ESP32 Shield'de mevcuttur.
 * AVR tabanlı kartlarda (ONE, Shield, Bricky, Moto) derlenmez.
 *
 * Bilingual (TR/EN) Bluetooth motor control example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

// ESP32 yalnızca Bluetooth Classic için bu guard gereklidir
// This guard ensures the sketch only compiles on ESP32
#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu örnek yalnızca Pinoo ESP32 Shield için geçerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Dahili DC Motorlar / On-board DC Motors (L293D)
Pinoo_DcMotor motor1(PINOO_ESP32_MOTOR1_A, PINOO_ESP32_MOTOR1_B);
Pinoo_DcMotor motor2(PINOO_ESP32_MOTOR2_A, PINOO_ESP32_MOTOR2_B);

// Dahili RGB LED / On-board RGB LED
Pinoo_RgbLed rgb(PINOO_INTERNAL_RGB, 2);

const int HIZLANDIRMA = 180; // PWM hızı (0-255) / Speed (0-255)

void ileri() {
  motor1.setSpeed(HIZLANDIRMA);
  motor2.setSpeed(HIZLANDIRMA);
  rgb.setColorAll(0, 255, 0); // Yeşil / Green
}

void geri() {
  motor1.setSpeed(-HIZLANDIRMA);
  motor2.setSpeed(-HIZLANDIRMA);
  rgb.setColorAll(255, 165, 0); // Turuncu / Orange
}

void sol() {
  motor1.stop();
  motor2.setSpeed(HIZLANDIRMA);
  rgb.setColorAll(0, 0, 255); // Mavi / Blue
}

void sag() {
  motor1.setSpeed(HIZLANDIRMA);
  motor2.stop();
  rgb.setColorAll(255, 0, 255); // Mor / Purple
}

void dur() {
  motor1.stop();
  motor2.stop();
  rgb.setColorAll(255, 0, 0); // Kırmızı / Red
}

void setup() {
  Serial.begin(115200);

  motor1.begin();
  motor2.begin();
  rgb.begin();
  rgb.setBrightness(40);

  // Bluetooth başlat / Start Bluetooth
  SerialBT.begin("Pinoo-ESP32"); // Bluetooth cihaz adı / Device name
  Serial.println("Bluetooth hazir: 'Pinoo-ESP32' olarak gorunur.");
  Serial.println("Bluetooth ready: visible as 'Pinoo-ESP32'");

  dur(); // Güvenli başlangıç / Safe initial state
}

void loop() {
  // Bluetooth'tan gelen karakteri oku / Read incoming Bluetooth character
  if (SerialBT.available()) {
    char komut = SerialBT.read();
    Serial.print("Komut / Command: ");
    Serial.println(komut);

    switch (komut) {
      case 'f': case 'F': ileri();  SerialBT.println("Ileri / Forward");   break;
      case 'b': case 'B': geri();   SerialBT.println("Geri / Backward");   break;
      case 'l': case 'L': sol();    SerialBT.println("Sol / Left");         break;
      case 'r': case 'R': sag();    SerialBT.println("Sag / Right");        break;
      case 's': case 'S': dur();    SerialBT.println("Dur / Stop");         break;
      default:
        SerialBT.println("? Bilinmeyen komut / Unknown command");
        break;
    }
  }
}
