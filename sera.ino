#include <MQTTClient.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
const char* ssid = "AndroidAP";
const char* password = "swzv4802"; 
const int  pwm = D0; 
const int motori=D1;
const int motorg=D2;
const int sui=D3;
const int sug=D4;


int nem;
int yagmur;
String gelen;
WiFiClient net;
MQTTClient client;
SoftwareSerial serial_connection(12,13);


void setup()
{
Serial.begin(9600);
serial_connection.begin(9600);
client.begin("broker.mqtt-dashboard.com", net);
connect();
pinMode(motori,OUTPUT);
pinMode(motorg,OUTPUT);
pinMode(sui,OUTPUT);
pinMode(sug,OUTPUT);
pinMode(A0,INPUT);
pinMode(D5,INPUT);
}

void connect() {
Serial.print("checking wifi...");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(1000);
}

Serial.print("\nconnecting...");
while (!client.connect("arduino", "try", "try")) {
Serial.print(".");
delay(1000);
}
Serial.println("\nconnected!");
client.subscribe("/komut");
}
void loop()
{  
  Serial.print("\nTesting Publisher every 5 sec");
  
 nem=digitalRead(D8);
 Serial.println(nem);
 yagmur=analogRead(A0);
 if(nem==1 && yagmur>500)
 {//nem yok yagmur yok 
  client.publish("/sera", ("Lütfen Sulamayı Açınız."));
  client.loop();
  }
  else if(nem==1 && yagmur<500)
  {//nem yok yagmur var  
    client.publish("/sera", ("Lütfen Çatıyı Açınız."));
  client.loop();
  }
  else if(nem==0 && yagmur<500)
  {//nem var yagmur var
    digitalWrite(sui, LOW);
    digitalWrite(sug, LOW);
    client.publish("/sera", ("Lütfen Çatıyı Kapatınız."));
    client.loop();
  }
  else if(nem==0 &&  yagmur>500)
  {//nem var  yagmur yok
    digitalWrite(sui, LOW);
    digitalWrite(sug, LOW);
    client.publish("/sera", ("Durum Stabil Çatıyı Açıp Yada Kapatabilirsiniz."));
    client.loop();
  }
   delay(1000);
  }




void messageReceived(String topic, String payload, char * bytes, unsigned int length)
{ 
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 gelen = (String)payload;
  Serial.print(gelen);
  if(gelen=="ac")
  { digitalWrite(motori, HIGH);
    digitalWrite(motorg, LOW);
    analogWrite(pwm,255);
    delay(3000);
    digitalWrite(motori, LOW);
    Serial.print(gelen);
  }  
  if(gelen=="kapat")
  { digitalWrite(motorg, HIGH);
    digitalWrite(motori, LOW);
    delay(750);
    digitalWrite(motorg, LOW);
  }
  if(gelen=="sula")
  { digitalWrite(sui, HIGH);
    digitalWrite(sug, LOW);
  }
  if(gelen=="su kapat")
  {
    digitalWrite(sui, LOW);
    digitalWrite(sug, LOW);
    
  }
  
  

}

