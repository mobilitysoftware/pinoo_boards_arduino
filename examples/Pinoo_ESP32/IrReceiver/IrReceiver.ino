/**
 * @file IrReceiver.ino
 * @brief Pinoo ESP32 Shield — Kızılötesi (IR) alıcı modülü örneği.
 *
 * Bu örnek Port 3'e bağlı harici bir IR Alıcı modülünden veya kart üzerindeki
 * dahili IR Alıcıdan (GPIO 12) gelen kumanda sinyallerini okumayı gösterir.
 *
 * NOT: Varsayılan olarak Port 3 (D18) üzerinde harici alıcı tanımlanmıştır.
 * Dahili alıcıyı kullanmak için constructor parametresini PINOO_INTERNAL_IR yapabilirsiniz.
 *
 * Bilingual (TR/EN) Infrared (IR) Receiver example for Pinoo ESP32 Shield.
 */

#include <Pinoo.h>

#if !defined(ARDUINO_ARCH_ESP32)
  #error "Bu ornek yalnizca Pinoo ESP32 Shield icin gecerlidir. / This example is only for Pinoo ESP32 Shield."
#endif

// Port 3 üzerinde harici IR Alıcı / External IR Receiver on Port 3 (D18)
Pinoo_IrReceiver ir(DOOR3);

// NOT: Dahili alıcıyı test etmek isterseniz üsttekini yorum satırı yapıp alttakini açın:
// Pinoo_IrReceiver ir(PINOO_INTERNAL_IR);

void setup() {
  Serial.begin(115200);
  ir.begin(); // IR Alıcıyı başlat / Initialize IR receiver
  Serial.println("IR Alıcı sinyal bekliyor... / IR Receiver waiting for signal...");
}

void loop() {
  // Sinyal gelip gelmediğini kontrol et / Check if signal received
  if (ir.available()) {
    unsigned long kod = ir.getCode(); // Gelen tuş kodunu al / Get received code
    
    Serial.print("Gelen IR Kod / Received IR Code: 0x");
    Serial.println(kod, HEX);
    
    ir.resume(); // Bir sonraki sinyal için hazırla / Prepare for next signal
  }
  delay(100);
}
