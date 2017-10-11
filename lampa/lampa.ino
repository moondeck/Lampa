/*
 * Lampa control firmware - 2017 Olgierd "moondeck" Nowakowski
 * MIT License
 */

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define PIN   D2

IPAddress localip(10,0,0,1);
IPAddress gateway(10,0,0,1);
IPAddress subnet(255,255,255,0);

Adafruit_NeoPixel PIXEL = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  PIXEL.begin();

  pinMode(D0, INPUT);
  Serial.begin(115200);
  Serial.println("lampa firmware v0.1.0 - 2017 moondeck");

  /*
  Serial.print("setting softap config...");
  Serial.println(WiFi.softAPConfig(localip, gateway, subnet) ? "ready" : "failed");

  Serial.print("setting up softap...");
  Serial.println(WiFi.softAP("Lampa") ? "ready" : "failed");

  Serial.print("softap address : ");
  Serial.println(WiFi.softAPIP());
  */
  
  PIXEL.setPixelColor(0, 0,0,0);
  
  WiFi.forceSleepBegin();

}


int LEDON = 0;
int button = 0;

void LampaWakeup() {
  WiFi.forceSleepWake();
  Serial.println("WIFI WAKEUP");
}

void LampaSleep() {
  WiFi.forceSleepBegin();
  Serial.println("WIFI SLEEP");
}

void loop() {

    while(digitalRead(D0)) delay(1);

    while(!digitalRead(D0)) {
      button++;
      delay(100);
    }

    Serial.println(button);
    
    if(button > 6 && button < 10) {
      //LampaWakeup();
      PIXEL.setPixelColor(0, 255,255,255);
    } else if(button < 6 && button > 2) {
      //LampaWakeup();
      PIXEL.setPixelColor(0, random(255), random(255), random(255));
    } else if(button > 10) {
      //LampaSleep();
      PIXEL.setPixelColor(0, 0,0,0);
    }

    PIXEL.show();
    button = 0; 
}
