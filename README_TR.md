# Pinoo SDK (Software Development Kit)

Pinoo SDK; Pinoo ONE, Pinoo Shield, Pinoo Bricky, Pinoo Moto ve Pinoo ESP32 kartları için geliştirilmiş, öğrencilerin ve eğitimcilerin elektronik projelerini metin tabanlı olarak Arduino IDE üzerinde kolayca kodlamasını sağlayan resmi yazılım geliştirme kitidir.

Bu SDK, karmaşık donanım ve register işlemlerini basitleştirerek anlaşılır ve modüler C++ sınıfları (Örn: `Pinoo_Led`, `Pinoo_Buzzer`, `Pinoo_DcMotor`) sunar.

---

## 🎯 Temel Özellikler

- **Geniş Kart Desteği:** AVR ve ESP32 mimarili tüm Pinoo kartları ile tam uyumluluk.
- **Kolaylaştırılmış Modül Sınıfları:** RJ11 bağlantı yapısına uygun, tak-çalıştır kütüphaneler.
- **Zengin Örnek Kod Kütüphanesi:** Her kart ve sensör için hazır, test edilmiş örnek kodlar.
- **Dahili IoT Desteği:** ThingsBoard ve WiFiManager kütüphaneleri ile ESP32 tabanlı projelerde bulut entegrasyonu.

---

## 📸 Görseller

![Pinoo Kart Ailesi ve Modülleri](docs/images/pinoo_boards_family.webp)

---

## 🗺️ Mimarî Yapı

Aşağıdaki şemada, Pinoo SDK'nın kullanıcı kodu ile donanım ve alt kütüphaneler arasındaki köprü görevi gösterilmektedir:

```mermaid
graph TD
    UserCode[Kullanıcı Kodu / Sketch] -->|Pinoo.h ve Modül API'leri| SDK[Pinoo SDK Core]
    SDK -->|Boards Konfigürasyonu| PinConfig[Pin Haritaları / src/boards]
    SDK -->|Üçüncü Parti Alt Yapı| ExtLibs[Açık Kaynak Kütüphaneler]

    subgraph Donanım Desteği
        PinConfig -->|AVR Platformu| AVR[Pinoo ONE / Shield / Bricky / Moto]
        PinConfig -->|ESP32 Platformu| ESP[Pinoo ESP32]
    end

    subgraph libraries/ (Bağımlılıklar)
        ExtLibs --> Adafruit[Adafruit NeoPixel / PWM Sürücü]
        ExtLibs --> IR[IRremote]
        ExtLibs --> LCD[LiquidCrystal I2C]
        ExtLibs --> TB[ThingsBoard / TBPubSubClient]
        ExtLibs --> WM[WiFiManager]
        ExtLibs --> JSON[ArduinoJson]
    end
```

---

## 🔌 Uyumlu Kartlar Tablosu

| Kart Adı         | Mimari | Mikrodenetleyici  | Öne Çıkan Özellikler                                              |
| :--------------- | :----- | :---------------- | :---------------------------------------------------------------- |
| **Pinoo ONE**    | AVR    | ATmega328P        | Bağımsız kodlanabilir ana robotik kart                            |
| **Pinoo Shield** | AVR    | ATmega328P (Nano) | Üzerine Arduino Nano takılan RJ11 genişletme kartı                |
| **Pinoo Bricky** | AVR    | ATmega328P        | LEGO uyumlu minyatür robotik kart                                 |
| **Pinoo Moto**   | AVR    | ATmega328P        | 8x DC / 4x Step motor sürücülü, Bluetooth özellikli gelişmiş kart |
| **Pinoo ESP32**  | ESP32  | ESP32-WROOM-32    | Dahili Wi-Fi, Bluetooth ve IoT özellikli geliştirme kartı         |

---

## 📂 Klasör Yapısı

```text
pinoo_sdk/
├── src/                          # SDK Ana Kaynak Dosyaları
│   ├── Pinoo.h                   # Ana Kütüphane Başlık Dosyası
│   ├── boards/                   # Kart-Pin Tanımlamaları (.h ve .cpp)
│   └── modules/                  # Sensör ve Aktüatör Kütüphaneleri (LED, Buzzer, Motor vb.)
├── examples/                     # Arduino IDE Örnekleri
│   ├── Pinoo_ONE/                # Pinoo ONE örnek projeleri
│   ├── Pinoo_Shield/             # Pinoo Shield örnek projeleri
│   ├── Pinoo_Bricky/             # Pinoo Bricky örnek projeleri
│   ├── Pinoo_Moto/               # Pinoo Moto (Çoklu Motor) örnek projeleri
│   └── Pinoo_ESP32/              # Pinoo ESP32 (IoT/Wi-Fi) örnek projeleri
├── hardware/                     # Arduino IDE Kart Yöneticisi Paketleri
│   ├── avr/                      # AVR Kart Tanımları ve Kütüphaneleri (1.0.2)
│   └── esp32/                    # ESP32 Kart Tanımları ve Kütüphaneleri (1.0.2)
├── library.properties            # Arduino Kütüphane Metadata Dosyası
└── package_pinoo_index.json      # Arduino Kart Yöneticisi JSON Dosyası
```

---

## 🛠️ Arduino IDE Kurulum Rehberi

Pinoo kartlarını ve SDK kütüphanelerini Arduino IDE'ye entegre etmek için aşağıdaki adımları sırasıyla uygulayın:

### 1. Kart Yöneticisi URL'lerini Tanımlama

1. Arduino IDE'yi açın.
2. **Dosya (File)** -> **Tercihler (Preferences)** menüsünü açın.
3. **Ek Devre Kartları Yöneticisi URL'leri (Additional Boards Manager URLs)** kutucuğuna şu üç URL'yi ekleyin (Kutucuğun sağındaki pencere ikonuna tıklayarak alt alta ekleyebilirsiniz):
   ```url
   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   https://raw.githubusercontent.com/mobilitysoftware/pinoo_boards_arduino/main/package_pinoo_index.json
   ```
4. **Tamam (OK)** butonuna basarak kaydedin.

### 2. Kart Paketlerini Yükleme

1. **Araçlar (Tools)** -> **Kart (Board)** -> **Kart Yöneticisi... (Boards Manager...)** menüsüne girin.
2. Arama çubuğuna **Pinoo** yazın.
3. Çıkan **Pinoo AVR Boards** ve **Pinoo ESP32 Boards** paketlerinin yanındaki **Kur (Install)** butonlarına tıklayarak kurulumları tamamlayın.

### 3. Sürücü (Driver) Kurulumu (Gerekliyse)

Pinoo kartları bilgisayarla iletişim kurmak için **CH340** USB-Seri dönüştürücüsünü kullanır. Kartınız bilgisayara bağlıyken `Port` kısmında görünmüyorsa [CH340 Sürücüsünü indirin ve kurun](https://www.wch-ic.com/downloads/ch341ser_zip.html).

---

## 📖 Örnek Kodlara Erişim ve Kullanım

Kurulum adımları tamamlandıktan sonra, örnek kodlara Arduino IDE içinden kolayca erişebilirsiniz:

1. **Dosya (File)** -> **Örnekler (Examples)** -> **Pinoo Modules** (veya kullandığınız karta özel örnek klasörü) yolunu izleyin.
2. Projenizde kullanmak istediğiniz modülün kodunu seçin.
3. Aşağıdaki örnek kod şablonunu referans alarak kendi kodlarınızı yazabilirsiniz:

```cpp
#include <Pinoo.h>

// Pinoo ONE ve 1. Kapıya (RJ11) bağlı LED nesnesi oluşturma
Pinoo_Led led(DOOR1, 1);

void setup() {
  // LED modülünü başlat
  led.begin();
}

void loop() {
  led.ledOn();   // LED'i yak
  delay(1000);   // 1 saniye bekle
  led.ledOff();  // LED'i söndür
  delay(1000);   // 1 saniye bekle
}
```

---

## 🤝 Açık Kaynak Kütüphaneler ve Atıflar

Pinoo SDK, geliştirme sürecini kolaylaştırmak amacıyla topluluk tarafından geliştirilen harika açık kaynaklı kütüphanelerden ve altyapılardan yararlanmaktadır. Bu projelerin orijinal sahiplerine ve katkıda bulunanlarına teşekkür ederiz:

| Kütüphane / Proje             | Kullanım Amacı                                      | Geliştirici / Sahibi                | Lisans       |
| :---------------------------- | :-------------------------------------------------- | :---------------------------------- | :----------- |
| **Adafruit NeoPixel**         | NeoPixel adreslenebilir RGB LED kontrolü            | Adafruit Industries                 | LGPL-3.0     |
| **Adafruit BusIO**            | I2C ve SPI donanım haberleşme altyapısı             | Adafruit Industries                 | BSD-3-Clause |
| **Adafruit PWM Servo Driver** | PCA9685 PWM sürücü kontrolü (Pinoo Moto)            | Adafruit Industries                 | BSD-3-Clause |
| **ArduinoJson**               | JSON formatında veri paketleme ve ayrıştırma        | Benoît Blanchon                     | MIT          |
| **IRremote**                  | Kızılötesi (IR) alıcı ve verici sinyal yönetimi     | shirriff, z3t0, Armin Joachimsmeyer | MIT          |
| **LiquidCrystal I2C**         | I2C destekli LCD ekranların kontrolü                | Frank de Brabander                  | LGPL-2.1     |
| **ServoESP32**                | ESP32 üzerinde kararlı Servo motor kontrolü         | Jaroslav Paral                      | GPL-3.0      |
| **ThingsBoard**               | ThingsBoard IoT bulut platformu istemcisi           | ThingsBoard Authors                 | Apache-2.0   |
| **TBPubSubClient**            | MQTT tabanlı ağ haberleşmesi (PubSubClient tabanlı) | Nick O'Leary                        | MIT          |
| **WiFiManager**               | ESP32 için Wi-Fi portal yapılandırması              | tzapu, tablatronix                  | GPL-3.0      |

---

## ⚖️ Lisans ve Hak Sahibi Bilgisi

Bu SDK, **Mobility Software** tarafından **Pinoo Robotics** için özel olarak hazırlanmıştır.

Her hakkı **Mobility Software** ve **Atölye Vizyon**'a aittir.

- 🌐 [Mobility Software](https://mobilitysoftware.net)
- 🌐 [Pinoo Robotics](https://pinoo.io)
- 🌐 [Atölye Vizyon](https://www.atolyevizyon.com)
