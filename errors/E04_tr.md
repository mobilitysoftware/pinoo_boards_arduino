# Pinoo Hata Çözümü - E04

## ❌ Hata Mesajı
> **PINOO ERROR [E04]:** Joystick requires a port with two analog inputs (Port 9 or Port 10).

---

## 🔍 Hataya Yol Açan Durum
Pinoo Joystick modülü hem X ekseni hem de Y ekseni için iki ayrı analog değer üretir. Bu nedenle, bağlandığı portta **iki adet bağımsız analog okuma (ADC) pini** bulunmalıdır.

Pinoo kartlarında iki adet analog pini birden taşıyan çift analog kapılar yalnızca **Port 9 ve Port 10**'dur. Modülü diğer portlara tanımladığınızda bu hata oluşur.

---

## 🛠️ Çözüm Adımları

1. **Fiziksel Bağlantıyı Değiştirin:** Joystick modülünün RJ11 kablosunu kart üzerindeki **Port 9 (DOOR9)** veya **Port 10 (DOOR10)** kapılarından birine takın.
2. **Kod Tanımlamasını Güncelleyin:** Kodunuzdaki nesne tanımlama kısmında port ismini taktığınız kapıya göre güncelleyin.

### Hatalı Kod Örneği
```cpp
#include <Pinoo.h>

// HATA: Joystick tek analoglu porta (DOOR7) veya dijital porta bağlanamaz!
Pinoo_Joystick joystick(DOOR7); 

void setup() {}
void loop() {}
```

### Doğru Kod Örneği
```cpp
#include <Pinoo.h>

// DOĞRU: Joystick çift analog destekli porta (DOOR9) bağlanmıştır.
Pinoo_Joystick joystick(DOOR9); 

void setup() {
  joystick.begin();
}
void loop() {
  int x = joystick.getX();
  int y = joystick.getY();
}
```

---

## 🔌 Uyumlu Kapılar Listesi
E04 hatasını gidermek için modülü bağlayabileceğiniz kapılar şunlardır:
* **DOOR9** (Port 9)
* **DOOR10** (Port 10)
