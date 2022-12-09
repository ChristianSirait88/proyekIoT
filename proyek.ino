#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <DHT_U.h>
#define DHTPIN D7 
#define DHTTYPE DHT11
#define BLYNK_TEMPLATE_ID "TMPL9wgbFNkm"
#define BLYNK_DEVICE_NAME "Christian"
char auth[] = "my9ll8Ke-nQT5FvyRm-0Kd8v3DItuScl";
char ssid[] = "lab IoT";
char pass[] = "ifiot2202";

DHT dht(DHTPIN, DHTTYPE);
float temp;
int sensor = D8;
int led1 = D1;
int led2 = D2;
int mode=2;

BLYNK_WRITE(V0){
  if (param.asInt()==HIGH) {
  digitalWrite(D2,LOW);
  }
  else{
  digitalWrite(D2, HIGH);
  }
}

BLYNK_WRITE(V1){
  if (param.asInt()==HIGH) {
  digitalWrite(D1,LOW);
  }
  else{
  digitalWrite(D1, HIGH);
  }
}

BLYNK_WRITE(V2){
  if (param.asInt()==HIGH) {
  mode = 1;
  }
  else{
  mode = 2;
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass,"blynk.cloud");
  pinMode(sensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  Serial.println(mode);
  if (mode == 2){
      long state = digitalRead(sensor);
        if(state == HIGH) {
          Serial.println("Motion detected!");
          temp = dht.readTemperature();//baca suhu
          if (isnan(temp)) { //jika tidak ada hasil
              Serial.println("DHT11 tidak terbaca... !");
              return;
            }
            else{//jika ada hasilnya 
            Serial.println(temp);
            if (temp <= 30 ){    
              digitalWrite(led1, HIGH);
              digitalWrite(led2, LOW);
              delay(3000);
            }
            else if (temp > 30 && temp <=35){
              digitalWrite(led2, HIGH);
              digitalWrite(led1, LOW);
              delay(3000);
            }
            else {
              digitalWrite(led1, LOW);
              digitalWrite(led2, LOW);
              delay(3000);
            }
            }
      delay(1000); 
        }
        else {
          Serial.println("Motion absent!");
          delay(1000);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          } 
      }
      else{

      }
}
