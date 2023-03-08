#include <WaveHC.h>
#include <WaveUtil.h>

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // This object represent the WAV file 
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

// time to play each tone in milliseconds
#define PLAY_TIME 200

/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))
#define tongsPin A5

int state = 0;

void setup() {
  Serial.begin(115200);

  pinMode(tongsPin, INPUT_PULLUP);

  if (!card.init()) error("card.init");

  // enable optimized read - some cards may timeout
  card.partialBlockRead(true);

  if (!vol.init(card)) error("vol.init");

  if (!root.openRoot(vol)) error("openRoot");

  PgmPrintln("Init Done");
  
  playStartup();
  
  delay(3000); // Allow everything to come up to temp (mostly the other arduino to pullup)
}

void loop() {
  if(digitalRead(tongsPin) == 0 && state == 0){playBuzzer(); delay(1500);}
  
  if(digitalRead(tongsPin) == 0){state = 1;}
  if(digitalRead(tongsPin) == 1){state = 0;}

  delay(50);
  
  Serial.print("digitalRead 13: ");  Serial.println(digitalRead(13));
  Serial.print("state: ");  Serial.println(state);
  Serial.println(); 
}

/////////////////////////////////// HELPERS
/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

// Number of files.
#define FILE_COUNT 16
      
/*
 * Play file by name and print latency in ms
 */
void playBuzzer(void) {
  char name[10];
  
  // copy flash string to RAM
  strcpy_P(name, PSTR("buzzer2.wav"));
  
  uint32_t t = millis();
    
  // open file by name
  if (!file.open(root, name)) error("open by name"); 
    
  // create wave and start play
  if (!wave.create(file))error("wave.create");
  wave.play();
    
  // print time
  Serial.println(millis() - t);
    
  // stop after PLAY_TIME ms
  Serial.println("Done");
    
  // check for play errors
  sdErrorCheck();
}

void playStartup(void) {
  char name[10];
  
  // copy flash string to RAM
  strcpy_P(name, PSTR("frogger.wav"));
  
  uint32_t t = millis();
    
  // open file by name
  if (!file.open(root, name)) error("open by name"); 
    
  // create wave and start play
  if (!wave.create(file))error("wave.create");
  wave.play();
    
  // print time
  Serial.println(millis() - t);
    
  // stop after PLAY_TIME ms
  Serial.println("Done");
    
  // check for play errors
  sdErrorCheck();
}
