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


char ssid[] = "Aguia";
char pass[] = "0102030405";

WiFiUDP Udp;
const IPAddress outIp(192,168,1,111);
const unsigned int outPort = 8089;
const unsigned int localPort = 1222;

int autoriza;
int modo;

OSCErrorCode error;

void setup(){
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  pinMode(D8,INPUT);

  pinMode(D2,OUTPUT);
  pinMode(D5,OUTPUT);

  digitalWrite(D2,HIGH);
  digitalWrite(D5,HIGH);

  
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
    modo = 0;
    digitalWrite(D2,LOW);
    digitalWrite(D5,LOW);
     
   if(digitalRead(D0) == HIGH) {
    modo = 1;
    digitalWrite(D2,HIGH);
    delay(150);
    digitalWrite(D2,LOW);
    delay(150);
    digitalWrite(D2,HIGH);
    delay(150);
    digitalWrite(D2,LOW);
    delay(150);
    digitalWrite(D2,HIGH);
    delay(150);
    digitalWrite(D2,LOW);
    delay(150);
    digitalWrite(D2,HIGH);
    delay(150);
    digitalWrite(D2,LOW);
    }else{
    if(digitalRead(D8) == HIGH) {
    modo = 2;
    digitalWrite(D5,HIGH);
    delay(150);
    digitalWrite(D5,LOW);
    delay(150);
    digitalWrite(D5,HIGH);
    delay(150);
    digitalWrite(D5,LOW);
    delay(150);
    digitalWrite(D5,HIGH);
    delay(150);
    digitalWrite(D5,LOW);
    delay(150);
    digitalWrite(D5,HIGH);
    delay(150);
    digitalWrite(D5,LOW);
   } else modo = 0;
   }
}

void certa (OSCMessage &msg) {
    if(msg.getFloat(0)==1.0){
    autoriza=1;
    Serial.println("Autorizado por Certa: ");
    OSCMessage msg3("/certa");
    Udp.beginPacket(outIp, outPort);
    float f=1;
    msg3.add(f);
    msg3.send(Udp);
    Udp.endPacket();
    msg3.empty();
    delay(100);
    OSCMessage msg2("/certa");
    f=0;
    msg2.add(f);
    Udp.beginPacket(outIp, outPort);
    msg2.send(Udp);
    Udp.endPacket();
    delay(100);
    msg2.empty();
    delay(4000);}
    else delay(100);
}

void errada (OSCMessage &msg) {
  if(msg.getFloat(0)==1.0){
  autoriza=1;
  Serial.println("Autorizado por Errada: ");
    
  OSCMessage msg3("/errada");
  Udp.beginPacket(outIp, outPort);
  float f=1;
  msg3.add(f);
  msg3.send(Udp);
  Udp.endPacket();
  msg3.empty();
  delay(100);
  OSCMessage msg2("/errada");
  f=0;
  msg2.add(f);
  Udp.beginPacket(outIp, outPort);
  msg2.send(Udp);
  Udp.endPacket();
  delay(100);
  msg2.empty();
  delay(4000);}
  else delay(100);
}

void nada (OSCMessage &msg) {
  delay(5);
}

void loop() {
  Serial.println(modo);
    switch(modo){
      case 0: torta();break;
      case 1: som(); break;
      case 2: crono(); break;
    };
}

int som(){
 while(true){
    int a=0;
    int b=0;
    int resete=0;
    autoriza=0;
    bool falhou=false;
    
    int tempo = random(40,150);
    tempo=100*tempo;
    digitalWrite(D2,LOW);
    digitalWrite(D5,LOW);
    delay(4000);
    digitalWrite(D2,HIGH);
    digitalWrite(D5,HIGH);
    long tinicial = millis();
    Serial.print("Numero Sorteado:");
    Serial.println(tempo);
    do{
    Serial.println("Periodo de Espera");
    if(!(digitalRead(D0) == LOW && digitalRead(D8)== LOW)){
      bool dedois;
      if(digitalRead(D0) == HIGH) dedois=true;
      else{
      if(digitalRead(D8) == HIGH) dedois = false;
      }
      if(dedois) digitalWrite(D2,LOW);
      else digitalWrite(D5,LOW);
          
      falhou=true;
      Udp.beginPacket(outIp, outPort);
      OSCMessage msg("/1/falhou");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(120);
      OSCMessage msg2("/1/falhou");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
      Serial.println("FALHOU");
      tempo=0;
      break;
    }
    delay(50);
    }while((millis()-tinicial)<tempo);
    if(!falhou){
      {Udp.beginPacket(outIp, outPort);
      OSCMessage msg("/1/beep");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(120);
      OSCMessage msg2("/1/beep");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();}
    delay(5);
    digitalWrite(D2,LOW);
    digitalWrite(D5,LOW);
    while(digitalRead(D0) == LOW && digitalRead(D8)== LOW){
      Serial.println("Esperando Cor");
  
      OSCMessage msg;
      int size = Udp.parsePacket();
      
       if (size > 0) {
        while (size--) {
          msg.fill(Udp.read());
        }
        if (!msg.hasError()) {
          msg.dispatch("/certa", nada);
          msg.dispatch("/errada", nada);
        } else {
          error = msg.getError();
          Serial.print("error: ");
          Serial.println(error);
        }
      }     
      delay(45);
    }
      Serial.println("ESCOLHEU");
    if(digitalRead(D0) == HIGH){
    a=1;  
    }else{
       if(digitalRead(D8) == HIGH){
       b=1;
       }else{
         resete=1;
         a=0;
         b=0;
    }
   }
    
    if(a==1){
      digitalWrite(D2,HIGH);
      Udp.beginPacket(outIp, outPort);
      OSCMessage msg("/vermelho");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(120);
      OSCMessage msg2("/vermelho");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    }
    if(b==1){
      digitalWrite(D5,HIGH);
      Udp.beginPacket(outIp, outPort);
      OSCMessage msg("/azul");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(120);
      OSCMessage msg2("/azul");
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

    Udp.flush();
    OSCMessage msg;
    int size = Udp.parsePacket();
    
     if (size > 0) {
      while (size--) {
        msg.fill(Udp.read());
      }
      if (!msg.hasError()) {
        msg.dispatch("/certa", nada);
        msg.dispatch("/errada", nada);
      } else {
        error = msg.getError();
        Serial.print("error: ");
        Serial.println(error);
      }
    }

    Udp.flush();    
   } 
    while(digitalRead(D1) == LOW && !autoriza){
      Serial.println("Esperando Reset");
      OSCMessage msg;
      int size = Udp.parsePacket();
      
       if (size > 0) {
        while (size--) {
          msg.fill(Udp.read());
        }
        if (!msg.hasError()) {
          msg.dispatch("/certa", certa);
          msg.dispatch("/errada", errada);
        } else {
          error = msg.getError();
          Serial.print("error: ");
          Serial.println(error);
        }
      }
    delay(50);
    }
    //reset
    {

      digitalWrite(D2, LOW);
      delay(100);
      digitalWrite(D5, LOW);      
      OSCMessage msg("/reset");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(100);
      OSCMessage msg2("/reset");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    }   
  }
}

int crono(){
  delay(1000);
}


int torta(){
  while(true){
    int a=0;
    int b=0;
    int resete=0;
    autoriza=0;
    digitalWrite(D2,LOW);
    digitalWrite(D5,LOW);
    while(digitalRead(D0) == LOW && digitalRead(D8)== LOW){
      Serial.println("Esperando Cor");
  
      OSCMessage msg;
      int size = Udp.parsePacket();
      
       if (size > 0) {
        while (size--) {
          msg.fill(Udp.read());
        }
        if (!msg.hasError()) {
          msg.dispatch("/certa", nada);
          msg.dispatch("/errada", nada);
        } else {
          error = msg.getError();
          Serial.print("error: ");
          Serial.println(error);
        }
      }     
      delay(45);
    }
      Serial.println("ESCOLHEU");
    if(digitalRead(D0) == HIGH){
    a=1;  
    }else{
       if(digitalRead(D8) == HIGH){
       b=1;
       }else{
         resete=1;
         a=0;
         b=0;
    }
   }
    
    if(a==1){
      digitalWrite(D2,HIGH);
      Udp.beginPacket(outIp, outPort);
      OSCMessage msg("/vermelho");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(120);
      OSCMessage msg2("/vermelho");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    }
    if(b==1){
      digitalWrite(D5,HIGH);
      Udp.beginPacket(outIp, outPort);
      OSCMessage msg("/azul");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(120);
      OSCMessage msg2("/azul");
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

    Udp.flush();
    OSCMessage msg;
    int size = Udp.parsePacket();
    
     if (size > 0) {
      while (size--) {
        msg.fill(Udp.read());
      }
      if (!msg.hasError()) {
        msg.dispatch("/certa", nada);
        msg.dispatch("/errada", nada);
      } else {
        error = msg.getError();
        Serial.print("error: ");
        Serial.println(error);
      }
    }

    Udp.flush();    
    
    while(digitalRead(D1) == LOW && !autoriza){
      Serial.println("Esperando Reset");
      OSCMessage msg;
      int size = Udp.parsePacket();
      
       if (size > 0) {
        while (size--) {
          msg.fill(Udp.read());
        }
        if (!msg.hasError()) {
          msg.dispatch("/certa", certa);
          msg.dispatch("/errada", errada);
        } else {
          error = msg.getError();
          Serial.print("error: ");
          Serial.println(error);
        }
      }
    delay(50);
    }
    
    //reset
    {

      digitalWrite(D2, LOW);
      delay(100);
      digitalWrite(D5, LOW);      
      OSCMessage msg("/reset");
      float f=1;
      msg.add(f);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      delay(100);
      OSCMessage msg2("/reset");
      f=0;
      msg2.add(f);
      Udp.beginPacket(outIp, outPort);
      msg2.send(Udp);
      Udp.endPacket();
      delay(100);
      msg2.empty();
    }   
  }
}
