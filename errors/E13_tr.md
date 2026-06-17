# Pinoo Hata Çözümü - E13

## ❌ Hata Mesajı
> **PINOO ERROR [E13]:** Digital modules can only be connected to digital ports (Port 1, Port 2, Port 3, Port 4, Port 5, or Port 6). Analog ports (Ports 7-10) are not allowed.

---

## 🔍 Hataya Yol Açan Durum
Pinoo LED, Buzzer, Buton, Engel Algılama (PIR), Eğme/Darbe Sensörü gibi dijital (0 ve 1) sinyallerle çalışan modülleri **Port 7, 8, 9 veya 10** gibi analog portlara tanımladığınızda bu hata oluşur.

Pinoo kartlarında port verimliliğini sağlamak amacıyla dijital modüller yalnızca **Port 1, 2, 3, 4, 5 ve 6** kapılarında kullanılabilir.

---

## 🛠️ Çözüm Adımları

1. **Fiziksel Bağlantıyı Değiştirin:** Modülün RJ11 kablosunu kart üzerindeki dijital portlardan birine takın (**Port 1, Port 2, Port 3, Port 4, Port 5 veya Port 6**).
2. **Kod Tanımlamasını Güncelleyin:** Nesne tanımlamasında port ismini yeni taktığınız kapıyla değiştirin.

### Hatalı Kod Örneği
```cpp
#include <Pinoo.h>

// HATA: LED (dijital modül) analog porta (DOOR7) bağlanamaz!
Pinoo_Led led(DOOR7); 

void setup() {}
void loop() {}
```

### Doğru Kod Örneği
```cpp
#include <Pinoo.h>

// DOĞRU: LED modülü dijital porta (DOOR1) bağlanmıştır.
Pinoo_Led led(DOOR1); 

void setup() {
  led.begin();
}
void loop() {
  led.ledOn();
  delay(1000);
  led.ledOff();
  delay(1000);
}
```

---

## 🔌 Uyumlu Kapılar Listesi
E13 hatasını gidermek için modülü bağlayabileceğiniz dijital kapılar şunlardır:
* **DOOR1** (Port 1)
* **DOOR2** (Port 2)
* **DOOR3** (Port 3)
* **DOOR4** (Port 4)
* **DOOR5** (Port 5)
* **DOOR6** (Port 6)
