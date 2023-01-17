#include <ThingSpeak.h>            
#include <WiFi.h>                  

const char * SSID = "Wokwi-GUEST"; 
const char * PASS = "";            
WiFiClient  client;               

int lampu1 = 14;                   
int lampu2 = 4;                    

unsigned long ChannelNumber =  1974833;       
const char * ReadAPIKey = "6063BH6AI2L057EC"; 
const int FieldNumber1 = 1;                                           
const int FieldNumber2 = 2;                                      

void setup()
{

  pinMode(lampu1, OUTPUT);
  pinMode(lampu2, OUTPUT);
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
 int A = ThingSpeak.readLongField(ChannelNumber, FieldNumber1, ReadAPIKey);
 int B = ThingSpeak.readLongField(ChannelNumber, FieldNumber2, ReadAPIKey);

  // Menghidupkan dan mematikan lampu1
  if(A == 1){
    Serial.println("lampu1 Nyala");
    digitalWrite(lampu1, HIGH);
  } else if(A == 0) {
    Serial.println("lampu1 Mati");
    digitalWrite(lampu1, LOW);
  }

  // Menghidupkan dan mematikan lampu2
  if(B == 1){
    Serial.println("lampu2 Nyala");
    digitalWrite(lampu2, HIGH);
  } else if(B == 0){
    Serial.println("lampu2 Mati");
    digitalWrite(lampu2, LOW);
  } 
}
