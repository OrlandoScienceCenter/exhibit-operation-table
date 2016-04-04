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

boolean  contactYellow_state = 0;       // Init variables and Set initial contact states
boolean  contactGreen_state	 = 0;       // Init variables and Set initial contact states
boolean  contactBlue_state 	 = 0;       // Init variables and Set initial contact states
boolean  contactPurple_state = 0;       // Init variables and Set initial contact states

boolean  switchYellow_state  = 0;       // Init variables and Set initial switch states
boolean  switchGreen_state	 = 0;       // This is the jack's plug detection switch
boolean  switchBlue_state 	 = 0;       // 
boolean  switchPurple_state  = 0;       // 



/***********************************************************
*                          SETUP                           *
***********************************************************/
void setup(){
Serial.begin(9600);
//Pin Mode Sets
	pinMode(PLAYER_YELLOW_LEDPIN, OUTPUT);
	pinMode(PLAYER_GREEN_LEDPIN, OUTPUT);
	pinMode(PLAYER_BLUE_LEDPIN, OUTPUT);
	pinMode(PLAYER_PURPLE_LEDPIN, OUTPUT);

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
	delay(100);
readSwitchStates() ;
drawActivePlayerColors();
///readContactStates() ;
//touchMonitor();
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
	Serial.print("Switch States: ");
	Serial.print(switchYellow_state);
	Serial.print(switchGreen_state);
	Serial.print(switchBlue_state);
	Serial.println(switchPurple_state);
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
Serial.println("DrawingPlayer Colors");
// check for yellow player connection  
   if(switchYellow_state){
  		for(uint8_t n; n < playerYellowRing.numPixels(); n++) {
		playerYellowRing.setPixelColor(n,0xffff00);
		}
		playerYellowRing.show();
	}
// check for green player connection	
  if(1){
  		for(uint8_t g; g < playerGreenRing.numPixels(); g++) {
		playerGreenRing.setPixelColor(g,0x00ff00);
		}
		playerGreenRing.show();
	}
	delay(5);
 // check for blue player connection	
  if(1){
  		for(uint8_t n; n < playerBlueRing.numPixels(); n++) {
		playerBlueRing.setPixelColor(n,0x0000ff);
		}
		playerBlueRing.show();
	}	
 // check for purple player connection	
   if(1){
  		for(uint8_t n; n < playerPurpleRing.numPixels(); n++) {
		playerPurpleRing.setPixelColor(n,0x0000ff);
		}
		playerPurpleRing.show();
	}
//	else{
//		for(uint8_t n; n < playerPurpleRing.numPixels(); n++) {
//		playerPurpleRing.setPixelColor(n,0x000000);
//		}
//		playerPurpleRing.show();
//	}
  delay(5);
 }

  
/***********************************************************
*                 touchMonitor                   *
***********************************************************/

void touchMonitor(){
  // Read all inputs to see when the surface is touched (player error/out) 	
  if(!contactYellow_state){
	//I'd trigger the sound here if I decide 	
	for(uint8_t l; l < 5; l++){
		for(uint8_t n; n < playerYellowRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0x00ffff); // Set everything to yellow
			playerBlueRing.setPixelColor(n,0x00ffff);
			playerGreenRing.setPixelColor(n,0x00ffff);
			playerPurpleRing.setPixelColor(n,0x00ffff);
			}
		delay(250);
			//
		for(uint8_t n; n < playerYellowRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0xffffff); // Set everything to white
			playerBlueRing.setPixelColor(n,0xffffff);
			playerGreenRing.setPixelColor(n,0xffffff);
			playerPurpleRing.setPixelColor(n,0xffffff);
			}
	playerYellowRing.show();
	playerBlueRing.show();
	playerGreenRing.show();
	playerPurpleRing.show();
	}
	loop();;
  }
  if(!contactBlue_state){
	//I'd trigger the sound here if I decide 	
	for(uint8_t l; l < 5; l++){
		for(uint8_t n; n < playerBlueRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0x00ff00); // Set everything to blue
			playerBlueRing.setPixelColor(n,0x00ff00);
			playerGreenRing.setPixelColor(n,0x00ff00);
			playerPurpleRing.setPixelColor(n,0x00ff00);
			}
		delay(250);
			//
		for(uint8_t n; n < playerBlueRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0xffffff); // Set everything to white
			playerBlueRing.setPixelColor(n,0xffffff);
			playerGreenRing.setPixelColor(n,0xffffff);
			playerPurpleRing.setPixelColor(n,0xffffff);
			}
	playerYellowRing.show();
	playerBlueRing.show();
	playerGreenRing.show();
	playerPurpleRing.show();		
	}
	loop();;
  }
    if(!contactGreen_state){
	//I'd trigger the sound here if I decide 	
	for(uint8_t l; l < 5; l++){
		for(uint8_t n; n < playerGreenRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0x00ff00); // Set everything to blue
			playerBlueRing.setPixelColor(n,0x00ff00);
			playerGreenRing.setPixelColor(n,0x00ff00);
			playerPurpleRing.setPixelColor(n,0x00ff00);
			}
		delay(250);
			//
		for(uint8_t n; n < playerGreenRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0xffffff); // Set everything to white
			playerBlueRing.setPixelColor(n,0xffffff);
			playerGreenRing.setPixelColor(n,0xffffff);
			playerPurpleRing.setPixelColor(n,0xffffff);
			}
	playerYellowRing.show();
	playerBlueRing.show();
	playerGreenRing.show();
	playerPurpleRing.show();		
	}
	loop();;
 }
    if(!contactPurple_state){
	//I'd trigger the sound here if I decide 	
	for(uint8_t l; l < 5; l++){
		for(uint8_t n; n < playerPurpleRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0x00ff00); // Set everything to blue
			playerBlueRing.setPixelColor(n,0x00ff00);
			playerGreenRing.setPixelColor(n,0x00ff00);
			playerPurpleRing.setPixelColor(n,0x00ff00);
			}
		delay(250);
			//
		for(uint8_t n; n < playerPurpleRing.numPixels(); n++) {
			playerYellowRing.setPixelColor(n,0xffffff); // Set everything to white
			playerBlueRing.setPixelColor(n,0xffffff);
			playerGreenRing.setPixelColor(n,0xffffff);
			playerPurpleRing.setPixelColor(n,0xffffff);
			}
	playerYellowRing.show();
	playerBlueRing.show();
	playerGreenRing.show();
	playerPurpleRing.show();
	}
	loop();;
  }
 }


