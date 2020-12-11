#include <OSCBoards.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <OSCMatch.h>
#include <OSCMessage.h>
#include <OSCTiming.h>

#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>


char ssid[] = "Androido";
char pass[] = "0102030405";

WiFiUDP Udp;
const IPAddress outIp(192,168,43,243);
const unsigned int outPort = 8089;
const unsigned int localPort = 1222;

void setup(){
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  pinMode(D2,INPUT);
  pinMode(D6,INPUT);

  pinMode(D8,OUTPUT);
  pinMode(D7,OUTPUT);



      digitalWrite(D8,HIGH);
      digitalWrite(D7,HIGH);
  
  Serial.begin(74880);
  // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());
  }

void loop() {
    int a=0;
    int b=0;
    int resete=0;
    while(digitalRead(D2) == LOW && digitalRead(D6)== LOW){
      Serial.println("Esperando Cor");
    delay(50);
    }
      Serial.println("ESCOLHEU");
    if(digitalRead(D2) == HIGH){
    a=1;  
    }else{
       if(digitalRead(D6) == HIGH){
       b=1;
       }else{
         resete=1;
         a=0;
         b=0;
    }
   }
    
    if(a==1){
      digitalWrite(D8,LOW);
      OSCMessage msg("/1/push3");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(100);
      OSCMessage msg2("/1/push3");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    }
    if(b==1){
      digitalWrite(D7,LOW);
      OSCMessage msg("/1/push4");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(100);
      OSCMessage msg2("/1/push4");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    } 

    int c=0;
    int e=0;

    while(digitalRead(D0) == LOW && digitalRead(D1)== LOW){
      Serial.println("Esperando Resposta");
    delay(50);
    }

    if(digitalRead(D0) == HIGH){
    c=1;  
    }else{
       if(digitalRead(D1) == HIGH){
       e=1;
       }else{
         resete=1;
         c=0;
         e=0;
    }
   }

      if(c==1){
      OSCMessage msg("/1/push1");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(100);
      OSCMessage msg2("/1/push1");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    }
    if(e==1){
      OSCMessage msg("/1/push2");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(100);
      OSCMessage msg2("/1/push2");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    } 

    delay(4000);
    
    //reset
    {

      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D7, HIGH);      
      OSCMessage msg("/1/push5");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(100);
      OSCMessage msg2("/1/push5");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    } 
         
}
