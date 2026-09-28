/**
 * @file Internal_Components.ino
 * @brief Bilingual (TR/EN) example for Pinoo Shield on-board components.
 * 
 * Bu örnek Pinoo Shield kartındaki dahili LED (D13) ve kızılötesi alıcı (D12)
 * bileşenlerinin kullanımını gösterir.
 * 
 * This example shows the usage of on-board components of Pinoo Shield:
 * LED (D13) and IR Receiver (D12).
 */

#include <Pinoo.h>

// Dahili bileşen tanımlamaları / Internal component declarations
Pinoo_Led dahiliLed(PINOO_INTERNAL_LED);               // Dahili LED (D13) / On-board LED
Pinoo_IrReceiver dahiliIr(PINOO_INTERNAL_IR);          // Dahili IR Alıcı (D12) / On-board IR Receiver

void setup() {
  Serial.begin(9600);
  
  // Bileşenleri başlat / Initialize components
  dahiliLed.begin();
  dahiliIr.begin();

  Serial.println("Pinoo Shield Dahili Bilesenler Hazir / Internal Components Ready");
}

void loop() {
  // Kızılötesi sinyal gelmiş mi kontrol et / Check if IR signal received
  if (dahiliIr.available()) {
    unsigned long kod = dahiliIr.getCode();
    Serial.print("IR: 0x");
    Serial.println(kod, HEX);
    
    // Gelen sinyale göre dahili LED'i kontrol et (örneğin sinyal alındığında LED'i yakıp söndür)
    // Control internal LED based on received signal (e.g. toggle LED when signal received)
    dahiliLed.turnOn();
    delay(100);
    dahiliLed.turnOff();
    
    dahiliIr.resume(); // Bir sonraki paket için hazırla / Prepare for next packet
  }
  
  delay(50);
}
