// ======================================================
//   Pinoo Moto Kart - 4x4 ARABA KONTROLÜ
//   Pinoo SDK Sınıfları ile yazılmış versiyon.
//
//   Protokol (Bluetooth / Serial):
//     F  → İleri         B → Geri
//     L  → Sol Dön       R → Sağ Dön
//     G  → İleri-Sol     H → İleri-Sağ
//     I  → Geri-Sol      J → Geri-Sağ
//     S  → Dur
//     1..4 → Vites (40%, 60%, 80%, 100%)
//     RON  → RGB Aç      ROFF → RGB Kapat
//     C    → BT Bağlandı D    → BT Ayrıldı
// ======================================================

#define PINOO_BOARD_MOTO   // Pinoo Moto kartını seç / Select Pinoo Moto board

#include <Pinoo.h>

// =============================================================
// Motor Tanımlamaları / Motor Declarations
// =============================================================
// Pinoo Moto PCA9685 Kanal Haritası / PCA9685 Channel Map:
//   MOTOR1 → kanal 0,1  (Sol Arka  / Left  Rear)
//   MOTOR2 → kanal 2,3  (Sağ Arka  / Right Rear)
//   MOTOR7 → kanal 12,13 (Sol Ön   / Left  Front)
//   MOTOR8 → kanal 14,15 (Sağ Ön   / Right Front)

Pinoo_DcMotor leftRear(MOTOR1);   // Sol Arka Motor  / Left  Rear Motor
Pinoo_DcMotor rightRear(MOTOR2);  // Sağ Arka Motor  / Right Rear Motor
Pinoo_DcMotor leftFront(MOTOR7);  // Sol Ön Motor    / Left  Front Motor
Pinoo_DcMotor rightFront(MOTOR8); // Sağ Ön Motor    / Right Front Motor

// =============================================================
// Dahili Bileşenler / Internal Components
// =============================================================
Pinoo_Buzzer buzzer(PINOO_INTERNAL_BUZZER, PASSIVE_BUZZER);  // Dahili Pasif Buzzer (D8)
Pinoo_RgbLed rgb(PINOO_INTERNAL_RGB, 2);                     // Dahili 2 adet NeoPixel (D9)

// =============================================================
// Vites & Hız Sistemi / Gear & Speed System
// =============================================================
int currentGear = 4;           // Varsayılan vites: 4 (tam hız) / Default gear: 4 (full speed)
float gearRatios[] = { 0.0f, 0.40f, 0.60f, 0.80f, 1.00f }; // Vites oranları / Gear ratios

// Anlık hız (0-255), vites oranına göre hesaplanır
// Current speed (0-255), calculated from gear ratio
int currentSpeed() {
    return (int)(255.0f * gearRatios[currentGear]);
}

// =============================================================
// Komut Watchdog / Command Watchdog
// =============================================================
unsigned long lastCmdTime = 0;
const unsigned long CMD_TIMEOUT = 420; // ms
String lastMoveCmd = "S";

// =============================================================
// Durum Değişkenleri / State Variables
// =============================================================
bool rgbEnabled = true;
bool btConnected = false;

// =============================================================
// Yardımcı: Tüm Motorları Durdur / Helper: Stop All Motors
// =============================================================
void stopAllMotors() {
    leftRear.stop();
    rightRear.stop();
    leftFront.stop();
    rightFront.stop();
}

// =============================================================
// Sol Taraf & Sağ Taraf Hız Ayarı / Set Left & Right Side Speed
// =============================================================
void setLeftSpeed(int speed) {
    leftFront.setSpeed(speed);
    leftRear.setSpeed(speed);
}

void setRightSpeed(int speed) {
    rightFront.setSpeed(speed);
    rightRear.setSpeed(speed);
}

// =============================================================
// Hareket Fonksiyonları / Movement Functions
//
// Not: Motor takılı yöne göre sol ve sağ taraf
//      ters yönde dönmektedir (karşılıklı montaj).
//      Pozitif setSpeed → ileri hareket.
// =============================================================
void driveForward() {
    int s = currentSpeed();
    setLeftSpeed(s);
    setRightSpeed(-s);  // Sağ taraf ters bağlı / Right side is reversed
}

void driveBackward() {
    int s = currentSpeed();
    setLeftSpeed(-s);
    setRightSpeed(s);
}

void turnLeft() {
    // Yerinde sola dön: Sol geri, Sağ ileri / Pivot left: Left back, Right forward
    int s = currentSpeed();
    setLeftSpeed(-s);
    setRightSpeed(-s);
}

void turnRight() {
    // Yerinde sağa dön: Sol ileri, Sağ geri / Pivot right: Left forward, Right backward
    int s = currentSpeed();
    setLeftSpeed(s);
    setRightSpeed(s);
}

void forwardLeft() {
    int s = currentSpeed();
    setLeftSpeed(s / 2);  // Sol yavaş / Left slow
    setRightSpeed(-s);    // Sağ tam hız / Right full speed
}

void forwardRight() {
    int s = currentSpeed();
    setLeftSpeed(s);       // Sol tam hız / Left full speed
    setRightSpeed(-s / 2); // Sağ yavaş / Right slow
}

void backwardLeft() {
    int s = currentSpeed();
    setLeftSpeed(-s / 2);
    setRightSpeed(s);
}

void backwardRight() {
    int s = currentSpeed();
    setLeftSpeed(-s);
    setRightSpeed(s / 2);
}

// =============================================================
// Melodi Fonksiyonları / Melody Functions
// =============================================================
void playToggleBeep() {
    buzzer.playTone(880, 120);
    delay(150);
    buzzer.playTone(988, 120);
    delay(150);
    buzzer.stop();
}

void playConnectMelody() {
    buzzer.playTone(988,  150); delay(180);
    buzzer.playTone(1319, 150); delay(180);
    buzzer.playTone(1760, 250); delay(280);
    buzzer.stop();
}

void playDisconnectMelody() {
    buzzer.playTone(392, 200); delay(220);
    buzzer.playTone(330, 250); delay(280);
    buzzer.playTone(262, 400); delay(420);
    buzzer.stop();
}

// =============================================================
// RGB Renk Yardımcıları / RGB Color Helpers
// =============================================================
void setRgbColor(uint8_t r, uint8_t g, uint8_t b) {
    if (!rgbEnabled) return;
    rgb.setColorAll(r, g, b);
}

void updateRgbForMove(const String& cmd) {
    if (!rgbEnabled) return;
    if      (cmd == "F") rgb.setColorAll(0,   255, 0);   // Yeşil / Green
    else if (cmd == "B") rgb.setColorAll(255,  80, 0);   // Turuncu / Orange
    else if (cmd == "L" || cmd == "R")
                         rgb.setColorAll(255, 255, 0);   // Sarı / Yellow
    else if (cmd == "G" || cmd == "H" || cmd == "I" || cmd == "J")
                         rgb.setColorAll(0,   180, 255); // Açık Mavi / Cyan
    else                 rgb.clear();                     // Dur → Söndür / Stop → Off
}

// =============================================================
// SETUP
// =============================================================
void setup() {
    Serial.begin(9600);

    // Motorları başlat (PCA9685 I2C sürücüsünü de başlatır)
    // Initialize motors (also initializes the PCA9685 I2C driver)
    leftRear.begin();
    rightRear.begin();
    leftFront.begin();
    rightFront.begin();

    // Dahili bileşenleri başlat / Initialize internal components
    buzzer.begin();
    rgb.begin();
    rgb.setBrightness(60);

    stopAllMotors();

    // Başlangıç sinyali / Startup signal
    rgb.setColorAll(0, 100, 255);
    buzzer.playTone(1000, 100);
    delay(150);
    buzzer.stop();
    rgb.clear();
}

// =============================================================
// LOOP
// =============================================================
void loop() {

    // ----------- Seri / Bluetooth Komut Okuma -----------
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        lastCmdTime = millis();

        // Vites komutları / Gear commands
        if      (cmd == "1") currentGear = 1;
        else if (cmd == "2") currentGear = 2;
        else if (cmd == "3") currentGear = 3;
        else if (cmd == "4") currentGear = 4;

        // Hareket komutları / Movement commands
        else if (cmd == "F" || cmd == "B" ||
                 cmd == "L" || cmd == "R" ||
                 cmd == "G" || cmd == "H" ||
                 cmd == "I" || cmd == "J" ||
                 cmd == "S") {
            lastMoveCmd = cmd;
            updateRgbForMove(cmd);
        }

        // RGB kontrolü / RGB control
        else if (cmd == "RON") {
            rgbEnabled = true;
            playToggleBeep();
            rgb.setColorAll(0, 255, 0);
        }
        else if (cmd == "ROFF") {
            rgbEnabled = false;
            playToggleBeep();
            rgb.clear();
        }

        // Bluetooth bağlantı durumu / Bluetooth connection state
        else if (cmd == "C") {
            btConnected = true;
            playConnectMelody();
            setRgbColor(0, 255, 0);
        }
        else if (cmd == "D") {
            btConnected = false;
            playDisconnectMelody();
            rgb.clear();
        }
    }

    // ----------- Watchdog: Komut gelmezse dur -----------
    // ----------- Watchdog: Stop if no command received --
    if (millis() - lastCmdTime > CMD_TIMEOUT) {
        stopAllMotors();
        lastMoveCmd = "S";
        rgb.clear();
        return;
    }

    // ----------- Son Hareket Komutunu Uygula -----------
    // ----------- Execute Last Movement Command ----------
    if      (lastMoveCmd == "F") driveForward();
    else if (lastMoveCmd == "B") driveBackward();
    else if (lastMoveCmd == "L") turnLeft();
    else if (lastMoveCmd == "R") turnRight();
    else if (lastMoveCmd == "G") forwardLeft();
    else if (lastMoveCmd == "H") forwardRight();
    else if (lastMoveCmd == "I") backwardLeft();
    else if (lastMoveCmd == "J") backwardRight();
    else                          stopAllMotors();
}
