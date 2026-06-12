/**
 * @file Internal_Components.ino
 * @brief Bilingual (TR/EN) example for Pinoo ONE on-board components.
 * 
 * Bu örnek Pinoo ONE kartındaki dahili LED (D13), buton (A7), ışık sensörü (LDR - A6),
 * pasif buzzer (D9), kızılötesi alıcı (D12) ve RGB LED (D13) bileşenlerinin kullanımını gösterir.
 * 
 * This example shows the usage of on-board components of Pinoo ONE:
 * LED (D13), Button (A7), Light Sensor (LDR - A6), Passive Buzzer (D9),
 * IR Receiver (D12), and RGB LED (D13).
 */

#include <Pinoo.h>

// Dahili bileşen tanımlamaları / Internal component declarations
Pinoo_Led dahiliLed(PINOO_INTERNAL_LED);               // Dahili LED (D13) / On-board LED
Pinoo_Button dahiliButon(PINOO_INTERNAL_BUTTON);       // Dahili Buton (A7) / On-board Button
Pinoo_Ldr dahiliIsik(PINOO_INTERNAL_LDR);              // Dahili LDR (A6) / On-board Light Sensor
Pinoo_Buzzer dahiliBuzzer(PINOO_INTERNAL_BUZZER, PASSIVE_BUZZER); // Dahili Pasif Buzzer (D9) / On-board Buzzer
Pinoo_IrReceiver dahiliIr(PINOO_INTERNAL_IR);          // Dahili IR Alıcı (D12) / On-board IR Receiver
Pinoo_RgbLed dahiliRgb(PINOO_INTERNAL_LED, 2);         // Dahili RGB LED (D13, 2 LED) / On-board RGB LED

void setup() {
  Serial.begin(9600);
  
  // Bileşenleri başlat / Initialize components
  dahiliLed.begin();
  dahiliButon.begin();
  dahiliIsik.begin();
  dahiliBuzzer.begin();
  dahiliIr.begin();
  dahiliRgb.begin();

  // RGB LED parlaklığını ayarla / Set RGB LED brightness
  dahiliRgb.setBrightness(50);

  Serial.println("Pinoo ONE Dahili Bilesenler Hazir / Internal Components Ready");
}

void loop() {
  // Buton durumunu oku / Read button state
  bool butonDurumu = dahiliButon.isPressed();

  // Işık seviyesini oku / Read light percentage
  int isikYuzdesi = dahiliIsik.getLightPercentage();

  // Seri porttan yazdır / Print to Serial Monitor
  Serial.print("Buton: ");
  Serial.print(butonDurumu ? "BASILDI / PRESSED" : "SERBEST / RELEASED");
  Serial.print(" | Isik / Light: ");
  Serial.print(isikYuzdesi);
  Serial.print("%");

  // Kızılötesi sinyal gelmiş mi kontrol et / Check if IR signal received
  if (dahiliIr.available()) {
    unsigned long kod = dahiliIr.getCode();
    Serial.print(" | IR: 0x");
    Serial.print(kod, HEX);
    dahiliIr.resume(); // Bir sonraki paket için hazırla / Prepare for next packet
  }
  Serial.println();

  // Butona basıldığında LED yansın, RGB LED'ler kırmızı olsun ve Buzzer çalsın
  // Turn LED/RGB red and play tone on Buzzer when button is pressed
  if (butonDurumu) {
    dahiliLed.turnOn();
    dahiliRgb.setColorAll(255, 0, 0); // Kırmızı / Red
    dahiliBuzzer.playTone(1000);      // 1000Hz ton çal / Play 1000Hz tone
  } else {
    dahiliLed.turnOff();
    dahiliRgb.clear();
    dahiliBuzzer.stop();
  }

  delay(150);
}
