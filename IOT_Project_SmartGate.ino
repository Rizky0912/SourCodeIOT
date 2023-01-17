#include <ThingSpeak.h>
#include <WiFi.h>
#include "DHTesp.h"
const char * SSID = "Wokwi-GUEST";
const char * PASS = "";
WiFiClient client;
DHTesp dhtSensor;
int lampu1 = 4;
int buzzer = 5;
const int DHT_PIN = 13;
unsigned long ChannelNumber = 1994898;
const char * ReadAPIKey = "18TJZ1P8470PZM3D";
const char * WriteAPIKey = "ZLWZLYP5UZGX40DX";
const int FieldNumber1 = 1;
void setup()
{
dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
pinMode(lampu1, OUTPUT);
pinMode(buzzer, OUTPUT);
Serial.begin(115200);
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
void loop()
{
int A = ThingSpeak.readLongField(ChannelNumber, FieldNumber1,
ReadAPIKey);
if(A == 1){
Serial.println("lampu1 Nyala");
digitalWrite(lampu1, HIGH);
} else if(A == 0) {
Serial.println("lampu1 Mati");
digitalWrite(lampu1, LOW);
}
TempAndHumidity tmp = dhtSensor.getTempAndHumidity();
if(tmp.temperature <= 30.00 || tmp.humidity >= 50.00)
{
digitalWrite(buzzer,HIGH);
delay(250);
digitalWrite(buzzer,LOW);
delay(200);
}
else
{
digitalWrite(buzzer,LOW);
}
ThingSpeak.setField(3, tmp.temperature);
ThingSpeak.setField(4, tmp.humidity);
ThingSpeak.writeFields(ChannelNumber, WriteAPIKey);
// Menghidupkan dan mematikan lampu1
}
