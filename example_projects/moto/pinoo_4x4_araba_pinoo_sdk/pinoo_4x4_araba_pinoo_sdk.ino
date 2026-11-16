// ======================================================
//   Pinoo Moto Kart - 4x4 ARABA KONTROLÜ (Pinoo SDK)
//   Pinoo Kontrol Merkezi "Live Firmware" protokolü ile çalışır.
//
//   Her komut '#' ile biter. Örn: A40#  RON#  CONN#
//   (Seri Monitör'den denerken satır sonu olarak '#' yaz, ya da "Yeni satır" seç; ikisi de kabul edilir.)
//
//   A[hız][yön]#        Hareket. Hız: 0..4 (0 dur, 4 tam hız). Yön: 0 ileri, 1 geri, 2 sol, 3 sağ
//   E[taraf][yön][hız]# Tek taraf sürüş (çapraz sürüş). Taraf: 0 sağ, 1 sol. Yön: 0 ileri, 1 geri. Hız: 0..4
//   C[pin][frekans 4 hane][süre]#  Buzzer. Frekans 0000 ise susturur. Süre = (süre+1) * 250 ms
//   M0[port]#           RGB başlat (bu kartta dahili RGB kullanılır, görmezden gelinir)
//   M1[piksel][RRGGBB]# RGB rengi (HEX). Örn: M10FF0000# -> piksel 0 kırmızı. Piksel 0 ve 1 dahili LED'ler
//   M2#                 RGB göster (bu kartta M1 renkleri hemen uygular)
//   CONN# / DCON#       Bağlandı / koptu melodileri
//   RON# / ROFF#        RGB aç (yeşil) / kapat
//
//   Eski harf komutları (F B L R G H I J S, 1-4 vites) kaldırıldı; uygulama artık yukarıdaki komutları gönderir.
// ======================================================

#include <Pinoo.h>

#if !defined(PINOO_BOARD_MOTO)
#error "Kart olarak Araçlar > Kart > Pinoo AVR Boards > Pinoo Moto seçili olmalı."
#endif

// =============================================================
// Motor Tanımlamaları / Motor Declarations
// =============================================================
// Pinoo Moto PCA9685 Kanal Haritası / PCA9685 Channel Map:
//   MOTOR1 → kanal 0,1   (Sol Arka  / Left  Rear)
//   MOTOR2 → kanal 2,3   (Sağ Arka  / Right Rear)
//   MOTOR7 → kanal 12,13 (Sol Ön    / Left  Front)
//   MOTOR8 → kanal 14,15 (Sağ Ön    / Right Front)
Pinoo_DcMotor leftRear(MOTOR1);
Pinoo_DcMotor rightRear(MOTOR2);
Pinoo_DcMotor leftFront(MOTOR7);
Pinoo_DcMotor rightFront(MOTOR8);

// Dahili bileşenler / Internal components
Pinoo_Buzzer buzzer(PINOO_INTERNAL_BUZZER, PASSIVE_BUZZER);  // D8
Pinoo_RgbLed rgb(PINOO_INTERNAL_RGB, 2);                     // D9, 2 adet NeoPixel

// =============================================================
// Durum / State
// =============================================================
const int MAX_SPEED = 255;        // setSpeed üst sınırı / setSpeed maximum
bool rgbEnabled = true;
String rxBuffer = "";             // Gelen komut tamponu / incoming command buffer

// =============================================================
// Sol / Sağ taraf sürüşü
//   Sol taraf motorları: + değer = ileri.
//   Sağ taraf motorları karşılıklı monte edilmiştir, o yüzden + değer = ileri için
//   motora ters işaret verilir. Bu fonksiyonlarda her iki taraf için de + = ileri.
// =============================================================
void setLeft(int speed) {
  leftFront.setSpeed(speed);
  leftRear.setSpeed(speed);
}

void setRight(int speed) {
  rightFront.setSpeed(-speed);
  rightRear.setSpeed(-speed);
}

void stopAllMotors() {
  leftFront.stop();
  leftRear.stop();
  rightFront.stop();
  rightRear.stop();
}

// A komutu hareketleri / "A" command movements
// Sol ve sağ dönüş Pinoo Kontrol Merkezi'nin referans yazılımıyla aynıdır:
//   sol: sol taraf yavaş geri, sağ taraf ileri / left: left side slow backward, right side forward
//   sağ: sol taraf ileri, sağ taraf yavaş ileri / right: left side forward, right side slow forward
void drive(int gear, int dir) {
  if (gear <= 0) { stopAllMotors(); return; }
  int s = MAX_SPEED * gear / 4;
  switch (dir) {
    case 0: setLeft(s);      setRight(s);      break;  // ileri / forward
    case 1: setLeft(-s);     setRight(-s);     break;  // geri / backward
    case 2: setLeft(-s / 4); setRight(s);      break;  // sol / left
    case 3: setLeft(s);      setRight(s / 4);  break;  // sağ / right
    default: stopAllMotors(); break;
  }
}

// E komutu: tek taraf / "E" command: one side
void driveSide(bool right, bool forward, int gear) {
  int s = MAX_SPEED * gear / 4;
  if (!forward) s = -s;
  if (right) setRight(s);
  else       setLeft(s);
}

// =============================================================
// Melodiler / Melodies
// =============================================================
void playToggleBeep() {
  buzzer.playTone(880, 120);  delay(150);
  buzzer.playTone(988, 120);  delay(150);
  buzzer.stop();
}

void playConnectMelody() {
  buzzer.playTone(988,  150); delay(180);
  buzzer.playTone(1319, 150); delay(180);
  buzzer.playTone(1760, 250); delay(280);
  buzzer.stop();
}

void playDisconnectMelody() {
  buzzer.playTone(392, 200);  delay(220);
  buzzer.playTone(330, 250);  delay(280);
  buzzer.playTone(262, 400);  delay(420);
  buzzer.stop();
}

// =============================================================
// Yardımcı: 2 haneli HEX → sayı / 2-digit HEX → number
// =============================================================
int hexNibble(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  return 0;
}

uint8_t hexByte(const String& s, int pos) {
  return (uint8_t)((hexNibble(s[pos]) << 4) | hexNibble(s[pos + 1]));
}

// =============================================================
// Komut işleyici / Command handler
// =============================================================
void handleCommand(const String& cmd) {
  if (cmd.length() == 0) return;

  // Bağlantı ve RGB aç/kapat komutları (çok harfli) / multi-letter commands
  if (cmd == "CONN") { playConnectMelody(); return; }
  if (cmd == "DCON") { stopAllMotors(); playDisconnectMelody(); return; }
  if (cmd == "RON")  { rgbEnabled = true;  playToggleBeep(); rgb.setColorAll(0, 255, 0); return; }
  if (cmd == "ROFF") { rgbEnabled = false; playToggleBeep(); rgb.clear(); return; }

  char c = cmd[0];

  // A[hız][yön]: hareket / drive
  if (c == 'A' && cmd.length() >= 3) {
    int gear = cmd[1] - '0';
    int dir  = cmd[2] - '0';
    drive(constrain(gear, 0, 4), dir);
  }
  // E[taraf][yön][hız]: tek taraf sürüş / one side
  else if (c == 'E' && cmd.length() >= 4) {
    bool right   = (cmd[1] == '0');
    bool forward = (cmd[2] == '0');
    int gear     = constrain(cmd[3] - '0', 0, 4);
    driveSide(right, forward, gear);
  }
  // C[pin][frekans 4 hane][süre]: buzzer
  else if (c == 'C' && cmd.length() >= 7) {
    int note = cmd.substring(2, 6).toInt();
    int mult = cmd[6] - '0';
    if (note <= 0) {
      buzzer.stop();
    } else {
      buzzer.playTone(note, (unsigned long)(mult + 1) * 250UL);
    }
  }
  // M: RGB (M0 başlat, M1 renk, M2 göster)
  else if (c == 'M' && cmd.length() >= 2) {
    if (cmd[1] == '1' && cmd.length() >= 9) {
      int pixel = cmd[2] - '0';
      uint8_t r = hexByte(cmd, 3);
      uint8_t g = hexByte(cmd, 5);
      uint8_t b = hexByte(cmd, 7);
      if (rgbEnabled && pixel >= 0 && pixel < 2) rgb.setColor(pixel, r, g, b);
    }
    // M0 ve M2: dahili LED'lerde ek bir işlem gerekmez / no extra action needed
  }
}

// =============================================================
// SETUP
// =============================================================
void setup() {
  Serial.begin(9600);

  // Motorları başlat (PCA9685 I2C sürücüsünü de başlatır)
  leftRear.begin();
  rightRear.begin();
  leftFront.begin();
  rightFront.begin();
  stopAllMotors();

  buzzer.begin();
  rgb.begin();
  rgb.setBrightness(60);
  rgb.clear();

  // Başlangıç sinyali / Startup signal
  rgb.setColorAll(0, 100, 255);
  buzzer.playTone(1000, 100);
  delay(150);
  buzzer.stop();
  rgb.clear();
}

// =============================================================
// LOOP: '#' ya da satır sonu gelene kadar tampona topla
// =============================================================
void loop() {
  while (Serial.available()) {
    char ch = (char)Serial.read();
    if (ch == '#' || ch == '\n' || ch == '\r') {
      handleCommand(rxBuffer);
      rxBuffer = "";
    } else if (rxBuffer.length() < 24) {
      rxBuffer += ch;
    } else {
      rxBuffer = "";  // Çok uzun / bozuk komut: at / drop an over-long command
    }
  }
}
