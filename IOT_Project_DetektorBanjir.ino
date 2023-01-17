#include <LiquidCrystal_I2C.h>
#define ECHO_PIN 2
#define TRIG_PIN 3
#define buzzer 4
#define ledmerah 13
#define ledkuning 12
#define ledhijau 11

LiquidCrystal_I2C lcd(0x27,20,4);
void setup() {
  pinMode(ledmerah, OUTPUT);
  pinMode(ledkuning, OUTPUT);
  pinMode(ledhijau, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  digitalWrite(ledmerah, HIGH);
  digitalWrite(ledkuning, HIGH);
  digitalWrite(ledhijau, HIGH);
  tone(4,300,500);
  lcd.setCursor(0,0);
  lcd.print("Detektor  Banjir");
  lcd.setCursor(5,1);
  lcd.print("oleh");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  A. Mukhlis A.");
  lcd.setCursor(0,1);
  lcd.print("SMAN 2  PONOROGO");
  delay(3000);
  digitalWrite(ledmerah, LOW);
  digitalWrite(ledkuning, LOW);
  digitalWrite(ledhijau, LOW);
  digitalWrite(buzzer, LOW);
  lcd.clear();
 }

 float kedalaman(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int durasi = pulseIn(ECHO_PIN, HIGH);
  return 400-durasi*0.034/2;
  }

void loop() {
  float kdlm = kedalaman();
 if(kdlm > 370)
 {
    digitalWrite(ledmerah, HIGH);
    digitalWrite(ledkuning, LOW);
    digitalWrite(ledhijau, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kdlmn :");
    lcd.setCursor(7,0);
    lcd.print(kdlm);
    lcd.setCursor(14,0);
    lcd.print("cm");
    lcd.setCursor(0,1);
    lcd.print("Satus :");
    lcd.setCursor(9,1);
    lcd.print("Bahaya");
    tone(4,800,1000);
    delay(1000);
    lcd.clear();
    delay(100);
 }
 else{
   if(kdlm >= 320 && kdlm < 370)
 {
    digitalWrite(ledmerah, LOW);
    digitalWrite(ledkuning, HIGH);
    digitalWrite(ledhijau, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kdlmn :");
    lcd.setCursor(7,0);
    lcd.print(kdlm);
    lcd.setCursor(14,0);
    lcd.print("cm");
    lcd.setCursor(0,1);
    lcd.print("Satus :");
    lcd.setCursor(9,1);
    lcd.print("Siaga");
    //digitalWrite(buzzer, LOW);
    delay(1000);
    lcd.clear();
    delay(100);
 }
  else{
    digitalWrite(ledmerah, LOW);
    digitalWrite(ledkuning, LOW);
    digitalWrite(ledhijau, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kdlmn :");
    lcd.setCursor(7,0);
    lcd.print(kdlm);
    lcd.setCursor(14,0);
    lcd.print("cm");
    lcd.setCursor(0,1);
    lcd.print("Satus :");
    lcd.setCursor(9,1);
    lcd.print("Aman");
    //digitalWrite(buzzer, LOW);
    delay(1000);
    lcd.clear();
    delay(100);
  }
   }


}
