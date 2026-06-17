# Pinoo Hata Çözümü - E03

## ❌ Hata Mesajı
> **PINOO ERROR [E03]:** LCD Screen must be connected to the hardware I2C port (Port 10).

---

## 🔍 Hataya Yol Açan Durum
Pinoo LCD Ekran modülü gibi **I2C haberleşme protokolünü** kullanan cihazları **Port 10 (DOOR10)** dışındaki başka bir porta tanımlamaya çalıştığınızda bu hata oluşur.

I2C protokolü özel donanımsal SCL ve SDA pinleri gerektirir. Pinoo kartlarında bu pinler yalnızca **Port 10** üzerinde tanımlıdır.

---

## 🛠️ Çözüm Adımları

1. **Fiziksel Bağlantıyı Değiştirin:** LCD ekran modülünün RJ11 kablosunu kart üzerindeki **Port 10 (DOOR10)** kapısına takın.
2. **Kod Tanımlamasını Güncelleyin:** Kodunuzdaki nesne tanımlama kısmında port ismini `DOOR10` olarak güncelleyin.

### Hatalı Kod Örneği
```cpp
#include <Pinoo.h>

// HATA: LCD Ekran sadece Port 10'a bağlanabilir, Port 1 (DOOR1) kullanılamaz!
Pinoo_Lcd lcd(DOOR1); 

void setup() {}
void loop() {}
```

### Doğru Kod Örneği
```cpp
#include <Pinoo.h>

// DOĞRU: LCD Ekran donanımsal I2C portuna (DOOR10) bağlanmıştır.
Pinoo_Lcd lcd(DOOR10); 

void setup() {
  lcd.begin();
  lcd.print("Merhaba Pinoo!");
}
void loop() {}
```

---

## 🔌 Uyumlu Kapılar Listesi
E03 hatasını gidermek için modülü bağlayabileceğiniz tek kapı şudur:
* **DOOR10** (Port 10)
