/**
 * @file IrReceiver.ino
 * @brief Pinoo Kızılötesi (IR) Alıcı modülü kullanımı.
 * 
 * Bu örnek Pinoo ONE kartındaki dahili kızılötesi alıcının (D12 pinine bağlı)
 * kumandadan gelen sinyalleri nasıl okuduğunu gösterir.
 * 
 * This example demonstrates how to read signals from an IR remote control
 * using the on-board IR receiver (connected to Pin D12) on the Pinoo ONE.
 */

#include <Pinoo.h>

// Dahili IR Alıcıyı başlat (Varsayılan olarak Pin 12)
// Initialize on-board IR Receiver (Defaults to Pin 12)
Pinoo_IrReceiver kizilotesi;

// Not: Harici bir IR alıcı modülünü RJ11 portuna bağlıyorsanız:
// Note: If you are connecting an external IR receiver module to an RJ11 port:
// Pinoo_IrReceiver kizilotesiHarici(DOOR1);

void setup() {
  Serial.begin(9600);
  
  // IR Alıcıyı başlat / Initialize IR Receiver
  kizilotesi.begin();
  
  Serial.println("Kizilotesi Alici Hazir. Kumandadan bir tusa basin...");
  Serial.println("IR Receiver Ready. Press a button on your remote...");
}

void loop() {
  // Yeni bir kod alındı mı kontrol et / Check if a new code is received
  if (kizilotesi.available()) {
    // Alınan kodu oku / Get decoded raw value
    unsigned long kod = kizilotesi.getCode();
    
    // Alınan kodu seri port ekranına HEX formatında yazdır
    // Print the received code to Serial Monitor in HEX format
    Serial.print("Alinan Kod / Received Code (HEX): 0x");
    Serial.println(kod, HEX);
    
    // Kumanda tuşlarına göre işlem yapma örneği
    // Example of handling specific remote control buttons
    if (kod == 0xFF30CF || kod == 0x1) {
      Serial.println("-> Tus: 1 / Button: 1");
    } else if (kod == 0xFF18E7 || kod == 0x2) {
      Serial.println("-> Tus: 2 / Button: 2");
    } else if (kod == 0xFF7A85 || kod == 0x3) {
      Serial.println("-> Tus: 3 / Button: 3");
    }
    
    // Bir sonraki sinyali almak için alıcıyı sıfırla/hazırla
    // Reset receiver to prepare for the next signal packet
    kizilotesi.resume();
  }
}
