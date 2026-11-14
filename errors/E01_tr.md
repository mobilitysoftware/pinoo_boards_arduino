# Pinoo Hata Çözümü - E01

## ❌ Hata Mesajı
> **PINOO ERROR [E01]:** Analog sensors can only be connected to analog ports (Port 7, Port 8, Port 9, or Port 10). Digital ports (Ports 1-6) are not allowed.

---

## 🔍 Hataya Yol Açan Durum
Pinoo LDR (Işık Sensörü), Potansiyometre, Toprak Nem Sensörü, Yağmur/Su Seviyesi Sensörü gibi analog sinyal üreten modülleri **Port 1, 2, 3, 4, 5 veya 6** gibi dijital portlara tanımladığınızda bu hata oluşur. 

Bu portlarda mikrodenetleyicinin analog-dijital dönüştürücü (ADC) özelliği bulunmadığı için kart analog veriyi okuyamaz.

---

## 🛠️ Çözüm Adımları

1. **Fiziksel Bağlantıyı Değiştirin:** Sensörün RJ11 kablosunu kart üzerindeki yeşil renkli analog portlardan birine takın (**Port 7, Port 8, Port 9 veya Port 10**).
2. **Kod Tanımlamasını Güncelleyin:** Kodunuzdaki nesne tanımlama kısmında port ismini yeni taktığınız kapıyla değiştirin.

### Hatalı Kod Örneği
```cpp
#include <Pinoo.h>

// HATA: LDR modülü dijital porta (DOOR1) bağlanamaz!
Pinoo_Ldr ldr(DOOR1); 

void setup() {}
void loop() {}
```

### Doğru Kod Örneği
```cpp
#include <Pinoo.h>

// DOĞRU: LDR modülü analog porta (DOOR7) bağlanmıştır.
Pinoo_Ldr ldr(DOOR7); 

void setup() {
  ldr.begin();
}
void loop() {
  int isik = ldr.getValue();
}
```

---

## 🔌 Uyumlu Kapılar Listesi
E01 hatasını gidermek için modülü bağlayabileceğiniz kapılar şunlardır:
* **DOOR7** (Port 7)
* **DOOR8** (Port 8)
* **DOOR9** (Port 9)
* **DOOR10** (Port 10)

---

## 🏎️ Pinoo Moto
Pinoo Moto'da dört kapı vardır (**DOOR1 - DOOR4**). Genel mesajdaki "Port 5, 6, 9, 10" numaraları Pinoo ONE'a aittir. Pinoo Moto'da derleyici mesajı zaten Moto kapılarını gösterir.

* **Pinoo Moto'da geçerli kapılar:** DOOR3, DOOR4
* Analog modüller (ışık, potansiyometre, toprak nem, su seviye) DOOR3 ya da DOOR4'e takılır.
* Kapı haritası için: [Pinoo Moto Dokümanları](https://pinoo-moto.gitbook.io/pinoo-moto/).
