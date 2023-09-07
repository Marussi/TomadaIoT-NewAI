#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include <FirebaseESP8266.h>
#if defined(ESP32)
#include <WiFi.h>
#include <Wire.h>
#include "addons/RTDBHelper.h"
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <PZEM004Tv30.h>

#define WIFI_SSID "AndroidAPEEEE" // your wifi SSID
#define WIFI_PASSWORD "zpmk5064" //your wifi PASSWORD

PZEM004Tv30 pzem(3, 1);
#define rele 0         // pin d0 as toggle pin
#define FIREBASE_HOST "tomada-iot-inteligente-default-rtdb.firebaseio.com" // change here
#define FIREBASE_AUTH "f6sRxmu2smIeihsEvAe4ZkXgEauomfECdqnGt0W9"  // your private key
FirebaseData firebaseData;
FirebaseData fbdo;
FirebaseConfig config;

void setup ()
{
  pinMode(rele, OUTPUT);

  Serial1.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial1.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial1.print(".");
    delay(500);
  }
  Serial1.println();
  Serial1.print("connected: ") ;
  Serial1.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);     
}
void loop ()
{
  if(Firebase.getString(firebaseData, "/ReleStatus"))
  {
    String ledstatus = firebaseData.stringData();
    if(ledstatus.toInt() == 1){
      digitalWrite(rele, HIGH);
      Serial1.println("on");

    float voltage = pzem.voltage();
  if (voltage != NAN) {
    Serial1.print("Tensao:  ");
    Serial1.print(voltage);
    Serial1.println("V");

    float volts = voltage;
        Firebase.RTDB.setFloat(&fbdo, "/Tomada IOT/Tensão", volts);
        
  } else {
    Serial1.println("Error reading voltage");
  }

  float current = pzem.current();
  if (current != NAN) {
    Serial1.print("Currente: ");
    Serial1.print(current);
    Serial1.println("A");

    float corrente = current;
        Firebase.RTDB.setFloat(&fbdo, "/Tomada IOT/Corrente", corrente);
        
  } else {
    Serial1.println("Error reading current");
  }

  float power = pzem.power();
  if (current != NAN) {
    Serial1.print("Potencia: ");
    Serial1.print(power);
    Serial1.println("W");

float potência = power;
        Firebase.RTDB.setFloat(&fbdo, "/Tomada IOT/Potência", potência);
        
  } else {
    Serial1.println("Error reading power");
  }

  float energy = pzem.energy();
  if (current != NAN) {
    Serial1.print("Energia: ");
    Serial1.print(energy, 3);
    Serial1.println("kWh");

float energia = energy;
float energiza = energy * 0.89;
 Firebase.RTDB.setFloat(&fbdo, "/Tomada IOT/kWh", energia);
 Firebase.RTDB.setFloat(&fbdo, "/Tomada IOT/Custo", energiza);
 
  } else {
    Serial1.println("Error reading energy");
  }

  float frequency = pzem.frequency();
  if (current != NAN) {
    Serial1.print("Frequencia: ");
    Serial1.print(frequency, 1);
    Serial1.println("Hz");

    float frequencia = frequency;
        Firebase.RTDB.setFloat(&fbdo, "/Tomada IOT/Frequência", frequencia);
        
  } else {
    Serial1.println("Error reading frequency");
  }

  float pf = pzem.pf();
  if (current != NAN) {
    Serial1.print("Factor De Potencia: ");
    Serial1.println(pf);

    float pfa = pf;
        Firebase.RTDB.setFloat(&fbdo, "/Tomada IOT/FatorPotência", pfa);
        
  } else {
    Serial1.println("Error reading power factor");
  }

  Serial1.println();
  delay(2000);
     
    }
    else {
      digitalWrite(rele, LOW);
      Serial.println("off");
    }
  }else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
}
