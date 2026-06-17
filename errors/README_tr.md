# Pinoo SDK Hata Kılavuzu

Pinoo SDK, kartlarımızın ve bağlı sensörlerimizin/modüllerimizin yanlış bağlantı nedeniyle fiziksel olarak zarar görmesini engellemek amacıyla **Derleme Zamanı Güvenlik Kontrolleri (Compile-Time Safety Checks)** gerçekleştirmektedir. 

Eğer bir modülü yanlış veya uyumsuz bir kapıya (RJ11 portuna) bağlayıp kod derlemeye çalışırsanız, Arduino IDE derlemeyi durduracak ve hata çıktısında ilgili hata kodunu gösterecektir.

Aşağıdaki tablodan karşılaştığınız hata koduna tıklayarak detaylı çözüm kılavuzuna ulaşabilirsiniz:

## Hata Kodları Tablosu

| Hata Kodu | Hata Açıklaması | Çözüm Kılavuzu |
| :--- | :--- | :--- |
| **E01** | Analog sensörler dijital portlara bağlanamaz (Yalnızca Port 7, 8, 9, 10 kullanılabilir). | [E01_tr.md](E01_tr.md) |
| **E02** | Çift Sinyalli (Dual-Signal) port gereksinimi (Yalnızca Port 5, 6, 9, 10 kullanılabilir). | [E02_tr.md](E02_tr.md) |
| **E03** | LCD Ekran donanımsal I2C portuna bağlanmalıdır (Yalnızca Port 10 kullanılabilir). | [E03_tr.md](E03_tr.md) |
| **E04** | Joystick modülü çift analog giriş gerektirir (Yalnızca Port 9 veya 10 kullanılabilir). | [E04_tr.md](E04_tr.md) |
| **E12** | `analogWrite` işlemi PWM destekli port gerektirir (Yalnızca Port 2 veya 5 kullanılabilir). | [E12_tr.md](E12_tr.md) |
| **E13** | Dijital modüller analog portlara bağlanamaz (Yalnızca Port 1, 2, 3, 4, 5, 6 kullanılabilir). | [E13_tr.md](E13_tr.md) |

---

## ⚠️ Güvenlik Kontrollerini Devre Dışı Bırakma (Bypass Mode)

Kendi özel projelerinizde veya standart dışı port eşleşmelerinde bu güvenlik sistemini devre dışı bırakmak isteyebilirsiniz. 

> [!CAUTION]
> Güvenlik kontrollerini devre dışı bırakmak, yanlış port bağlantılarında kartın veya modüllerin fiziksel olarak **hasar görmesine veya yanmasına** neden olabilir. Bu durumdaki donanım arızaları garanti kapsamı dışındadır.

Güvenlik mekanizmasını devre dışı bırakmak için kodunuzun en üst satırına, kütüphaneyi dahil etmeden önce `#define PINOO_BYPASS_SAFETY` tanımını eklemeniz gerekir:

```cpp
#define PINOO_BYPASS_SAFETY
#include <Pinoo.h>

// Artık istediğiniz modülü istediğiniz porta tanımlayabilirsiniz.
Pinoo_Led led(DOOR9, 1); // Normalde hata verecek olan bu bağlantı artık derlenir.
```
