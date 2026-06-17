# Pinoo Hata Çözümü - E02

## ❌ Hata Mesajı
> **PINOO ERROR [E02]:** The selected module requires a Dual-Signal port (Port 5, Port 6, Port 9, or Port 10).

---

## 🔍 Hataya Yol Açan Durum
Pinoo Mesafe Sensörü (Ultrasonik) veya Sıcaklık-Nem Sensörü (DHT11) gibi aynı anda iki farklı veri hattı (Trig/Echo veya Veri/Geri besleme) kullanan çift sinyalli modülleri **Port 1, 2, 3, 4, 7 veya 8** gibi tek sinyal hatlı portlara tanımladığınızda bu hata oluşur.

Pinoo kartlarında yalnızca belirli portlar çift sinyal (Dual-Signal) taşıyabilir.

---

## 🛠️ Çözüm Adımları

1. **Fiziksel Bağlantıyı Değiştirin:** Modülün RJ11 kablosunu kart üzerindeki çift sinyal destekli portlardan birine takın (**Port 5, Port 6, Port 9 veya Port 10**).
2. **Kod Tanımlamasını Güncelleyin:** Kodunuzdaki nesne tanımlama kısmında port ismini yeni taktığınız kapıyla değiştirin.

### Hatalı Kod Örneği
```cpp
#include <Pinoo.h>

// HATA: Mesafe sensörü tek sinyalli porta (DOOR1) bağlanamaz!
Pinoo_DistanceSensor mesafe(DOOR1); 

void setup() {}
void loop() {}
```

### Doğru Kod Örneği
```cpp
#include <Pinoo.h>

// DOĞRU: Mesafe sensörü çift sinyal destekli porta (DOOR5) bağlanmıştır.
Pinoo_DistanceSensor mesafe(DOOR5); 

void setup() {
  mesafe.begin();
}
void loop() {
  int uzaklik = mesafe.getDistance();
}
```

---

## 🔌 Uyumlu Kapılar Listesi
E02 hatasını gidermek için modülü bağlayabileceğiniz çift sinyalli kapılar şunlardır:
* **DOOR5** (Port 5)
* **DOOR6** (Port 6)
* **DOOR9** (Port 9)
* **DOOR10** (Port 10)
