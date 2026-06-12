/**
 * @file Led.ino
 * @brief Bilingual (TR/EN) example for Pinoo Led module.
 * 
 * Bu örnek Door 1'e bağlı bir Led modülünün nasıl kontrol edileceğini gösterir.
 * This example demonstrates how to control a Led module connected to Door 1.
 */

#include <Pinoo.h>

// Door 1'e bağlı LED modülü / LED module connected to Door 1
Pinoo_Led led(DOOR1);

void setup() {
  led.begin(); // LED'i başlat / Initialize LED
}

void loop() {
  // LED'i yak / Turn LED on
  led.turnOn();
  delay(1000);

  // LED'i söndür / Turn LED off
  led.turnOff();
  delay(1000);

  // LED durumunu tersine çevir / Toggle LED state
  led.toggle();
  delay(500);
  led.toggle();
  delay(500);
}
