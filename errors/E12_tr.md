# Pinoo Hata Çözümü - E12

## ❌ Hata Mesajı
> **PINOO ERROR [E12]:** Pinoo::analogWrite requires a PWM-capable port (Port 2 or Port 5).

---

## 🔍 Hataya Yol Açan Durum
Pinoo SDK içerisinde `analogWrite` (PWM - Darbe Genişlik Modülasyonu) sinyali göndermeyi gerektiren modülleri (Örn: Hız ayarlı DC Motor, Işık şiddeti ayarlanabilir LED, Buzzer tonlama vb.) **Port 2 veya Port 5** dışındaki portlara tanımladığınızda bu hata oluşur.

PWM sinyali donanımsal zamanlayıcılar (Timers) gerektirir. Pinoo kartlarında bu donanımsal özellik yalnızca **Port 2 (DOOR2) ve Port 5 (DOOR5)** kapılarında desteklenmektedir.

---

## 🛠️ Çözüm Adımları

1. **Fiziksel Bağlantıyı Değiştirin:** PWM kontrolü yapmak istediğiniz modülün RJ11 kablosunu kart üzerindeki **Port 2 (DOOR2)** veya **Port 5 (DOOR5)** kapılarından birine takın.
2. **Kod Tanımlamasını Güncelleyin:** Nesne tanımlamasında port ismini taktığınız kapıyla değiştirin.

### Hatalı Kod Örneği
```cpp
#include <Pinoo.h>

// HATA: analogWrite (PWM) özelliği Port 1'de desteklenmez!
// Bu atama bazı gelişmiş motor/led sürüşlerinde E12 hatasına neden olur.
Pinoo_Led led(DOOR1); 

void setup() {
  led.begin();
}
void loop() {
  // E12 Hatası: analogWrite dijital pin üzerinde PWM gerektirir
  led.setBrightness(128); 
}
```

### Doğru Kod Örneği
```cpp
#include <Pinoo.h>

// DOĞRU: Modül PWM destekli porta (DOOR2) bağlanmıştır.
Pinoo_Led led(DOOR2); 

void setup() {
  led.begin();
}
void loop() {
  led.setBrightness(128); // Başarılı parlaklık kontrolü!
}
```

---

## 🔌 Uyumlu Kapılar Listesi
E12 hatasını gidermek ve PWM sinyali kullanabilmek için modülü bağlayabileceğiniz kapılar şunlardır:
* **DOOR2** (Port 2)
* **DOOR5** (Port 5)
