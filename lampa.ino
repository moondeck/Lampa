#include <Adafruit_NeoPixel.h>
#define PIN   D2

Adafruit_NeoPixel PIXEL = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  PIXEL.begin();

  pinMode(D0, INPUT);
  Serial.begin(115200);
  Serial.println("lampa firmware v0.1.0 - 2017 moondeck");

  PIXEL.setPixelColor(0, 0,0,0);
}


int LEDON = 0;
int button = 0;

void loop() {

    while(digitalRead(D0)) delay(1);

    while(!digitalRead(D0)) {
      button++;
      delay(100);
    }

    Serial.println(button);
    
    if(button > 6 && button < 10) {
      PIXEL.setPixelColor(0, 255,255,255);
    } else if(button < 6 && button > 2) {
      PIXEL.setPixelColor(0, random(255), random(255), random(255));
    } else if(button > 10) {
      PIXEL.setPixelColor(0, 0,0,0);
    }

    PIXEL.show();
    button = 0; 
}
