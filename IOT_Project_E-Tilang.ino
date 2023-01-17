//Sistem Tilang Elektronik
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// definisi pin untuk OLED display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// definisi pin untuk sensor IR
#define IR_PIN 2

// definisi pin untuk buzzer
#define BUZZER_PIN 3

// variabel untuk menyimpan status sensor IR
int irStatus = 0;

// variabel untuk menyimpan jumlah pelanggaran
int jumlahPelanggaran = 0;

void setup() {
// mulai komunikasi I2C dengan OLED display
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.display();

// konfigurasi pin sensor IR sebagai input
pinMode(IR_PIN, INPUT);

// konfigurasi pin buzzer sebagai output
pinMode(BUZZER_PIN, OUTPUT);

// mulai komunikasi serial
Serial.begin(9600);
}

void loop() {
// baca status sensor IR
irStatus = digitalRead(IR_PIN);

// jika sensor IR mendeteksi adanya kendaraan
if (irStatus == HIGH) {
// nyalakan buzzer
digitalWrite(BUZZER_PIN, HIGH);
// tunggu selama 0.5 detik
delay(500);
// matikan buzzer
digitalWrite(BUZZER_PIN, LOW);
// tambahkan jumlah pelanggaran
jumlahPelanggaran++;
// tampilkan jumlah pelanggaran di OLED display
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0,0);
display.println("Jumlah Pelanggaran:");
display.setTextSize(4);
display.setCursor(0,20);
display.println(jumlahPelanggaran);
display.display();
// kirim jumlah pelanggaran ke serial monitor
Serial.println("Jumlah Pelanggaran: " + String(jumlahPelanggaran));
}
}