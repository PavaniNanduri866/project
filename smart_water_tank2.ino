#include<ESP8266WiFi.h>
#include<PubSubClient.h>
#include<ArduinoJson.h>
char data[100];

#define CLIENT_ID "wtank"
#define port 1883
const char *ssid="Panuchinnu";
const char *pswd="9247391670";
const char *mqtt_server="100.25.118.95";
WiFiClient espclient;
PubSubClient client(espclient);
String waterlevel,ontime,offtime ;
void setup()
{
  pinMode(D2,OUTPUT);//trig
  pinMode(D0,INPUT);//echo
  pinMode(D5,OUTPUT);//relay
  Serial.begin(9600);
  WiFi.begin(ssid,pswd);
  while(WiFi.status()!=WL_CONNECTED)
  {
   Serial.print("....");
   delay(200);
  }
Serial.println("\n WiFi CONNECTED");
Serial.println(ssid);
Serial.println(WiFi.localIP());
client.setServer(mqtt_server,1883);
}
void reconnect() {
  while(!client.connected())
  {
    Serial.print("Attempting mqtt connect");
  if(client.connect(CLIENT_ID))
  {
    Serial.println("connected");
    
  }
  }
  // put your setup code here, to run once:
}

void loop() {
  
  digitalWrite(D2,LOW);
  delayMicroseconds(2);
  digitalWrite(D2,HIGH);
  delayMicroseconds(10);
  digitalWrite(D2,LOW);
  int dur;
  dur=pulseIn(D0,HIGH);
  float distance=(0.034*dur)/2;
  Serial.println(distance);
  delay(1000);
  String motor;
  if (distance<=4)
  {
    digitalWrite(D5,HIGH);
    motor="OFF";
    Serial.println("tank is full");
  }
  if (distance>=24)
  {
    digitalWrite(D5,LOW);
    motor="ON";
    Serial.println("tank is empty");
  }

  if(!client.connected())
  {
    reconnect();
  }
   StaticJsonDocument<300> Doc;
   Doc["distance"]=String(distance);
   Doc["motor"]=String(motor);
   serializeJson(Doc, data);
   if(client.connect(CLIENT_ID))
   {
      if (distance<=26)
      {
        client.publish("wtank",data);
      }
      
   }
   delay(10000);
   
  
}
