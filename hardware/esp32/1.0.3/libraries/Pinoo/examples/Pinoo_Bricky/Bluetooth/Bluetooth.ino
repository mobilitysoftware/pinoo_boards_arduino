/**
 * @file Bluetooth.ino
 * @brief Bilingual (TR/EN) example for Pinoo Bluetooth module.
 * 
 * Bu örnek kart üzerindeki özel sokete bağlı Bluetooth modülünün kullanımını gösterir.
 * This example demonstrates usage of the Bluetooth module connected to the dedicated on-board socket.
 */

#include <Pinoo.h>

// Bluetooth modülü (Donanımsal RX/TX soketini kullanır)
// Bluetooth module (Uses the dedicated on-board RX/TX socket)
Pinoo_Bluetooth bluetooth;

Pinoo_Led led(DOOR1); // Örnek olarak Door 1'e bir LED bağladık / Connected a LED to Door 1

void setup() {
  bluetooth.begin(9600); // Bluetooth iletişimini başlat / Start Bluetooth
  led.begin();
}

void loop() {
  // Bluetooth'tan veri gelip gelmediğini kontrol et / Check if data is received
  if (bluetooth.available()) {
    String cmd = bluetooth.readString(); // Satır sonuna kadar oku / Read line
    
    // Gelen komuta göre LED'i aç/kapat
    // Turn LED on/off depending on the received command
    if (cmd == "AC" || cmd == "ON") {
      led.turnOn();
      bluetooth.println("LED acildi / LED turned ON");
    } 
    else if (cmd == "KAPAT" || cmd == "OFF") {
      led.turnOff();
      bluetooth.println("LED kapatildi / LED turned OFF");
    }
  }
}
