/*Multi-Purpose Table Electronics

Single metal surface that will act as one pole , 
and 4 tongs as seperate poles. 

Each tong will get a colored ring to indicate player

when player touches metal tong to metal play surface, noise
activates and all player lights flash that color. 

When starting up game, each tong will plug in seperately, and
illuminate the ring beneath it. 

*/

/* Fender-Style guitar jack pinout:
	9	1/4" Plug Ground (chasis)
	1	Pole #1 closed when plug is inserted
	2	Pole #1 common
	3   Pole #1 Closed when plug is out
	8	1/4" Plug Ring
	4	1/4" Plug Tip
	7	Pole #2 Closed when plug is out	
	6	Pole #2 common
	5	Pole #2 Closed when plug is inserted
*/	

/***********************************************************
*                         INCLUDES                         *
***********************************************************/
#include <Adafruit_NeoPixel.h>



/***********************************************************
*                         DEFINES                          *
***********************************************************/
#define PLAYER_YELLOW_LEDPIN      A0     // 
#define PLAYER_GREEN_LEDPIN       A1     // 
#define PLAYER_BLUE_LEDPIN        A2    // 
#define PLAYER_PURPLE_LEDPIN      A3
#define PLAYER_YELLOW_CONTACT     12
#define PLAYER_GREEN_CONTACT      11
#define PLAYER_BLUE_CONTACT       10
#define PLAYER_PURPLE_CONTACT     9
#define SOUND_TRIGGER_PIN		  3 	
#define PLAYER_YELLOW_SWITCH      8
#define PLAYER_GREEN_SWITCH       7
#define PLAYER_BLUE_SWITCH        6
#define PLAYER_PURPLE_SWITCH      5
#define DIAG_PIN                  13

/***********************************************************
*                      GLOBAL VARS                         *
***********************************************************/
Adafruit_NeoPixel playerYellowRing = Adafruit_NeoPixel(16, PLAYER_YELLOW_LEDPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel playerGreenRing = Adafruit_NeoPixel(16, PLAYER_GREEN_LEDPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel playerBlueRing = Adafruit_NeoPixel(16, PLAYER_BLUE_LEDPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel playerPurpleRing = Adafruit_NeoPixel(16, PLAYER_PURPLE_LEDPIN, NEO_GRB + NEO_KHZ800);

uint8_t  contactYellow_state = 0;       // Init variables and Set initial contact states
uint8_t  contactGreen_state	 = 0;       // Init variables and Set initial contact states
uint8_t  contactBlue_state 	 = 0;       // Init variables and Set initial contact states
uint8_t  contactPurple_state = 0;       // Init variables and Set initial contact states

uint8_t  switchYellow_state  = 0;       // Init variables and Set initial switch states
uint8_t  switchGreen_state	 = 0;       // This is the jack's plug detection switch
uint8_t  switchBlue_state 	 = 0;       // 
uint8_t  switchPurple_state  = 0;       // 

uint8_t yellowRingState		 = 0;



/***********************************************************
*                          SETUP                           *
***********************************************************/
void setup(){
Serial.begin(9600);
//Pin Mode Sets
	//pinMode(PLAYER_YELLOW_LEDPIN, OUTPUT);
	//pinMode(PLAYER_GREEN_LEDPIN, OUTPUT);
	///pinMode(PLAYER_BLUE_LEDPIN, OUTPUT);
	///pinMode(PLAYER_PURPLE_LEDPIN, OUTPUT);

	pinMode(PLAYER_YELLOW_CONTACT, INPUT_PULLUP);
	pinMode(PLAYER_GREEN_CONTACT, INPUT_PULLUP);
	pinMode(PLAYER_BLUE_CONTACT, INPUT_PULLUP);
	pinMode(PLAYER_PURPLE_CONTACT, INPUT_PULLUP);

	pinMode(PLAYER_YELLOW_SWITCH, INPUT_PULLUP);	
	pinMode(PLAYER_GREEN_SWITCH, INPUT_PULLUP);
	pinMode(PLAYER_BLUE_SWITCH, INPUT_PULLUP);
	pinMode(PLAYER_PURPLE_SWITCH, INPUT_PULLUP);
	//pinMode(DIAG_PIN, INPUT_PULLUP);

	//pinMode(SOUND_TRIGGER_PIN, OUTPUT);
//
	delay(100);
// Neopixel Initalize all pixels to off
	playerYellowRing.begin();
	playerBlueRing.begin();
	playerGreenRing.begin();
	playerPurpleRing.begin();
	delay(100);
	//
	playerYellowRing.show();
	playerBlueRing.show();
	playerGreenRing.show();
	playerPurpleRing.show();
	//delay(1);
Serial.println("Setup Completed");
}

/***********************************************************
*                          LOOP                            *
***********************************************************/
void loop(){
	//Serial.println("looping");
	delay(0);
readSwitchStates() ;
drawActivePlayerColors();
readSwitchStates() ;
killDisconnectedPlayers();
readContactStates() ;
touchMonitor();
}

/***********************************************************
*                 readSwitchStates                         *
***********************************************************/

void readSwitchStates(){
  // Read all digitial inputs for the Jack Switches	
  switchYellow_state = !digitalRead(PLAYER_YELLOW_SWITCH);
  switchGreen_state = !digitalRead(PLAYER_GREEN_SWITCH);
  switchBlue_state = !digitalRead(PLAYER_BLUE_SWITCH);
  switchPurple_state = !digitalRead(PLAYER_PURPLE_SWITCH);

  }

/***********************************************************
*                 readContactStates                         *
***********************************************************/

void readContactStates(){
  // Read all digitial inputs for the jack switches store as state
  contactYellow_state = !digitalRead(PLAYER_YELLOW_CONTACT);
  contactGreen_state = !digitalRead(PLAYER_GREEN_CONTACT);
  contactBlue_state = !digitalRead(PLAYER_BLUE_CONTACT);
  contactPurple_state = !digitalRead(PLAYER_PURPLE_CONTACT);
//  	Serial.print("contact States: ");
//	Serial.print(contactYellow_state);
//	Serial.print(contactGreen_state);
//	Serial.print(contactBlue_state);
//	Serial.println(contactPurple_state);
}

/***********************************************************
*                 drawActivePlayerColors                   *
***********************************************************/

void drawActivePlayerColors(){
//Serial.println("DrawingPlayer Colors");
// check for yellow player connection  


   if(switchYellow_state){
	   //Serial.println("YellowConnected");
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 255,200,0);
			playerYellowRing.show();
			delay(1);
		}
 }
//green player
   if(switchGreen_state){
	   //Serial.println("GreenConnected");
		for(uint16_t i=0; i<playerGreenRing.numPixels(); i++) {
			playerGreenRing.setPixelColor(i, 0,255,0);
			playerGreenRing.show();
			delay(1);
		}
 }
//blue player
   if(switchBlue_state){
	   //Serial.println("BlueConnected");	
		for(uint16_t i=0; i<playerBlueRing.numPixels(); i++) {
			playerBlueRing.setPixelColor(i, 5,5,255);
			playerBlueRing.show();
			delay(1);
		}
 } 
//purple player
   if(switchPurple_state){
	   //Serial.println("PurpleConnected");
		for(uint16_t i=0; i<playerPurpleRing.numPixels(); i++) {
			playerPurpleRing.setPixelColor(i, 255,0,255);
			playerPurpleRing.show();
			delay(1);
		}
 }  
 }  
void killDisconnectedPlayers(){
	/*
	// now turn off old players who are no longer active
*/  
  if(switchYellow_state == 0){
	   //Serial.println("YellowConnected");
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 0,0,0);
			playerYellowRing.show();
			delay(1);
		}
 }
  if(switchGreen_state == 0){
	   //Serial.println("GreenwConnected");
		for(uint16_t i=0; i<playerGreenRing.numPixels(); i++) {
			playerGreenRing.setPixelColor(i, 0,0,0);
			playerGreenRing.show();
			delay(1);
		}
 }
 
// blue
  if(switchBlue_state == 0){
	   //Serial.println("BluewConnected");
		for(uint16_t i=0; i<playerBlueRing.numPixels(); i++) {
			playerBlueRing.setPixelColor(i, 0,0,0);
			playerBlueRing.show();
			delay(1);
		}
 } 
// purple
  if(switchPurple_state == 0){
	   //Serial.println("PurplewConnected");
		for(uint16_t i=0; i<playerPurpleRing.numPixels(); i++) {
			playerPurpleRing.setPixelColor(i, 0,0,0);
			playerPurpleRing.show();
			delay(1);
		}
 } 

 }  
  
 /*
 
/***********************************************************
*                 touchMonitor                   *
***********************************************************/

void touchMonitor(){
	uint8_t l = 0;
  // Read all inputs to see when the surface is touched (player error/out) 	
  if(contactYellow_state){
	//I'd trigger the sound here if I decide 	
	for(l; l < 5; l++){
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 255,200,0);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 255,200,0);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 255,200,0);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 255,200,0);
			playerPurpleRing.show();
			}
		delay(500);
			//
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 255,255,255);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 255,255,255);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 255,255,255);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 255,255,255);
			playerPurpleRing.show();
			}
		delay(250);
			//
	}
	delay(1000);
	return;
  }
////// GREEN CONTACT ///

  if(contactGreen_state){
	//I'd trigger the sound here if I decide 	
	for(l; l < 5; l++){
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 0,255,0);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 0,255,0);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 0,255,0);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 0,255,0);
			playerPurpleRing.show();
			}
		delay(500);
			//
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 255,255,255);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 255,255,255);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 255,255,255);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 255,255,255);
			playerPurpleRing.show();
			}
		delay(250);
			//
	}
	delay(1000);
	return;
  }
////// BLUE CONTACT ///

  if(contactBlue_state){
	//I'd trigger the sound here if I decide 	
	for(l; l < 5; l++){
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 5,5,255);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 5,5,255);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 5,5,255);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 5,5,255);
			playerPurpleRing.show();
			}
		delay(500);
			//
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 255,255,255);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 255,255,255);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 255,255,255);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 255,255,255);
			playerPurpleRing.show();
			}
		delay(250);
			//
	}
	delay(1000);
	return;
  }
 ////// PURPLE CONTACT ///

  if(contactPurple_state){
	//I'd trigger the sound here if I decide 	
	for(l; l < 5; l++){
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 255,0,255);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 255,0,255);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 255,0,255);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 255,0,255);
			playerPurpleRing.show();
			}
		delay(500);
			//
		for(uint16_t i=0; i<playerYellowRing.numPixels(); i++) {
			playerYellowRing.setPixelColor(i, 255,255,255);
			playerYellowRing.show();
			playerGreenRing.setPixelColor(i, 255,255,255);
			playerGreenRing.show();
			playerBlueRing.setPixelColor(i, 255,255,255);
			playerBlueRing.show();
			playerPurpleRing.setPixelColor(i, 255,255,255);
			playerPurpleRing.show();
			}
		delay(250);
			//
	}
	delay(1000);
	return;
  } 
  }
