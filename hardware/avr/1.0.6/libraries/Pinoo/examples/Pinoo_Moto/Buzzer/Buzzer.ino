/**
 * @file Buzzer.ino
 * @brief Bilingual (TR/EN) example for Pinoo Buzzer module.
 *
 * Bu örnek Door 2'ye bağlı Buzzer modülünün (aktif buzzer) nasıl kontrol edileceğini gösterir.
 * Aktif buzzer tek bir sabit tonda öter, yalnızca açılır ve kapanır.
 * Kartın üzerindeki dahili buzzer pasiftir ve farklı frekanslarda melodi çalabilir:
 * onun için Internal_Components örneğine bak.
 *
 * This example demonstrates how to control the Buzzer module (active buzzer) connected to Door 2.
 * An active buzzer makes a single fixed tone, it can only be switched on and off.
 * The on-board buzzer is passive and can play different frequencies: see the
 * Internal_Components example.
 */

#include <Pinoo.h>

// Door 2'ye bağlı Buzzer modülü / Buzzer module connected to Door 2
// Kapı (Door) verildiğinde otomatik olarak aktif buzzer seçilir.
// A Door means the external module, so ACTIVE_BUZZER is selected automatically.
Pinoo_Buzzer buzzer(DOOR2);

void setup() {
  buzzer.begin(); // Buzzer'ı başlat / Initialize Buzzer
}

void loop() {
  // Buzzer'ı aç / Turn the buzzer on
  buzzer.turnOn();
  delay(500);

  // Buzzer'ı kapat / Turn the buzzer off
  buzzer.turnOff();
  delay(500);

  // 200 ms'lik kısa bir bip sesi / A short 200 ms beep
  // (aktif buzzer'da frekans değeri yok sayılır / the frequency is ignored on an active buzzer)
  buzzer.playTone(1000, 200);
  delay(1000);
}
