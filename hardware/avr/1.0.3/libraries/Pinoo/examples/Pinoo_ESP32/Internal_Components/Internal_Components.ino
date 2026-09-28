/**
 * @file Internal_Components.ino
 * @brief Pinoo ESP32 Shield üzerindeki dahili bileşenlerin kullanım örneği.
 *
 * Bu örnek Pinoo ESP32 Shield-V1.1 kartındaki dahili bileşenleri gösterir:
 *   - Dahili LED          → GPIO 13
 *   - RGB NeoPixel LED    → GPIO 13 (Pinoo ONE ile aynı pin)
 *   - IR Kızılötesi Alıcı → GPIO 12 (Pinoo ONE ile aynı pin)
 *   - Dahili Motor 1      → D0 / D2  (L293D)
 *   - Dahili Motor 2      → D4 / D15 (L293D)
 *
 * NOT: Pinoo ESP32 Shield'de dahili buton, LDR ve buzzer YOKTUR.
 * Bu bileşenler için ilgili port modüllerini kullanınız.
 *
 * Bilingual (TR/EN) example for Pinoo ESP32 Shield on-board components:
 *   - On-board LED (D13), RGB NeoPixel (D13), IR Receiver (D12)
 *   - Built-in DC Motor 1 (D0/D2) and Motor 2 (D4/D15) via L293D driver
 */

#include <Pinoo.h>

// Dahili LED / On-board LED
Pinoo_Led dahiliLed(PINOO_INTERNAL_LED);

// Dahili RGB NeoPixel LED (GPIO 13, 2 LED zinciri)
// On-board RGB NeoPixel (same GPIO 13 as Pinoo ONE, 2-LED chain)
Pinoo_RgbLed dahiliRgb(PINOO_INTERNAL_RGB, 2);

// Dahili IR alıcı (GPIO 12) / On-board IR Receiver (GPIO 12)
Pinoo_IrReceiver dahiliIr(PINOO_INTERNAL_IR);

// Dahili DC Motorlar (L293D sürücü üzerinden)
// On-board DC Motors via integrated L293D driver
Pinoo_DcMotor motor1(PINOO_ESP32_MOTOR1_A, PINOO_ESP32_MOTOR1_B);
Pinoo_DcMotor motor2(PINOO_ESP32_MOTOR2_A, PINOO_ESP32_MOTOR2_B);

void setup() {
  Serial.begin(115200);

  // Bileşenleri başlat / Initialize components
  dahiliLed.begin();
  dahiliRgb.begin();
  dahiliIr.begin();
  motor1.begin();
  motor2.begin();

  // Parlaklığı ayarla / Set brightness
  dahiliRgb.setBrightness(40);

  Serial.println("Pinoo ESP32 Shield - Dahili Bilesenler Hazir");
  Serial.println("Internal Components Ready");
}

void loop() {
  // IR sinyal gelmiş mi kontrol et / Check for incoming IR signal
  if (dahiliIr.available()) {
    unsigned long kod = dahiliIr.getCode();
    Serial.print("IR Kod / Code: 0x");
    Serial.println(kod, HEX);
    dahiliIr.resume();

    // IR koduna göre renk değiştir / Change RGB color based on IR code
    if (kod == 0xFF30CF) {         // Örnek: uzaktan 1 tuşu / Remote button 1
      dahiliRgb.setColorAll(255, 0, 0);   // Kırmızı / Red
    } else if (kod == 0xFF18E7) { // Uzaktan 2 tuşu / Remote button 2
      dahiliRgb.setColorAll(0, 255, 0);   // Yeşil / Green
    } else if (kod == 0xFF7A85) { // Uzaktan 3 tuşu / Remote button 3
      dahiliRgb.setColorAll(0, 0, 255);   // Mavi / Blue
    }
  }

  // LED yanıp sönsün / Blink on-board LED
  dahiliLed.toggle();

  // Motorları çalıştır ve durdur / Run and stop motors
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  delay(1000);

  motor1.stop();
  motor2.stop();
  delay(500);

  motor1.setSpeed(-150);
  motor2.setSpeed(-150);
  delay(1000);

  motor1.stop();
  motor2.stop();
  dahiliRgb.clear();
  delay(500);
}
