#include <ThingSpeak.h>
#include <WiFi.h>
#include <ESP32Servo.h>

const char * SSID = "Wokwi-GUEST";
const char * PASS = "";
WiFiClient client;
unsigned long ChannelNumber = 2006566;
const char * ReadAPIKey = "DUTOMSHLBUAMJJM6
";
const int FieldNumber1 = 1;

int buzzer1 = 14;
int servo =  5;

Servo myservo;
int rotasi = 90;

void soundBuzzer(){
  tone(buzzer1, 250);
  delay(1000);
  tone(buzzer1, 100,800);
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzer1, OUTPUT);
  myservo.attach(5);
  myservo.write(90);
  Serial.println();
  WiFi.begin(SSID, PASS);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() {
  int A = ThingSpeak.readLongField(ChannelNumber, FieldNumber1,
  ReadAPIKey);

  if(A == 1){
  Serial.println("GERBANG TERBUKA");
  soundBuzzer();
  tutup();
  } 
  else if(A == 0) {
  Serial.println("GERBANG TERTUTUP");
  noTone(buzzer1);
  buka();
  }
}

void tutup(){
  if(rotasi <= 90){
    myservo.write(rotasi);
    delay(500);
    rotasi--;
  }
  if(rotasi <= 90 ) rotasi = 0;
}

void buka(){
  if(rotasi <= 90){
    myservo.write(rotasi);
    delay(500);
    rotasi+=4;
  }
  if(rotasi >= 0 ) rotasi = 90;
}
