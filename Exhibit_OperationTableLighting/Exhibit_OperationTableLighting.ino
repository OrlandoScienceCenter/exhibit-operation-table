#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel stripL = Adafruit_NeoPixel(45, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripR = Adafruit_NeoPixel(45, 6, NEO_GRB + NEO_KHZ800);

int state = 0;

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  stripL.begin();
  stripL.show(); // Initialize all pixels to 'off'

  stripR.begin();
  stripR.show(); // Initialize all pixels to 'off'
  
  pinMode(13, INPUT_PULLUP);
 /* 
  int i = 0;
  do{
    fadeOut(1);
    fadeIn(1);
  }while(i < 8);
  */
  delay (5000);
}

void loop() {  
  if (digitalRead(13) == LOW) {setRed(); delay(900); state = 0;} else {if(state == 0){fadeOut(1); state = 1;}}
}

void setRed() {
  uint16_t i;
  
      stripL.setBrightness(255);
      stripR.setBrightness(255);

    for(i=0; i<45; i++) {
      stripL.setPixelColor(i, 255, 0, 0);
      stripR.setPixelColor(i, 255, 0, 0);
    }
    stripL.show();
    stripR.show();
}

void turnOff() {
    stripL.setBrightness(0);
    stripR.setBrightness(0);

    stripL.show();
    stripR.show();
}

void fadeOut(int dTime) {
  uint16_t i;

    for(i=255; i>0; i--) {
      stripL.setBrightness(i);
      stripR.setBrightness(i);
      
      stripL.show();
      stripR.show();
    
      delay(dTime);
    }
    
      stripL.setBrightness(0);
      stripR.setBrightness(0);
      
      stripL.show();
      stripR.show();
}

void fadeIn(int dTime) {
  uint16_t i;

    for(i=0; i>255; i++) {
      stripL.setBrightness(i);
      stripR.setBrightness(i);
      
      stripL.show();
      stripR.show();
    
      delay(dTime);
    }
    
      stripL.setBrightness(0);
      stripR.setBrightness(0);
      
      stripL.show();
      stripR.show();
}
