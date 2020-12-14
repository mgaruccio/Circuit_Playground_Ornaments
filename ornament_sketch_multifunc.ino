#include "Adafruit_Arcada.h"
#include "Adafruit_Arcada_Filesystem.h"

#include <Adafruit_Circuit_Playground.h>
#include "pitches.h"
Adafruit_Arcada arcada;
//FatFileSystem Arcada_QSPI_FileSys;

// defines speed of song lower is slower, higher is faster... 2 is about right
const int speed = 3;

// brightness of the Neopixels... for my eyes brighter red looks more even with green
// this is pulled from another source, proper gamma correction would probably be smarter, but w/e
const int green = 75;
const int red   = 125;

// number of notes in the song
const int numNotes = 26;

// Jingle Bells!
int melody[] = {                          
  NOTE_B4, NOTE_B4, NOTE_B4, 
  NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_D5, NOTE_G4, NOTE_A4,
  NOTE_B4, 0,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
  NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, 
  NOTE_D5, NOTE_D5, NOTE_C5, NOTE_A4, 
  NOTE_G4};

// Durations... 8 = 1/8, 4 = 1/4, 3 = ~3/8, 2 = 1/2, 1 = Full
int noteDurations[] = {    
  4, 4, 2, 
  4, 4, 2, 
  4, 4, 3, 8,
  1, 4,
  4, 4, 3, 8, 
  4, 4, 4, 8, 8,
  4, 4, 4, 4, 
  1
  };

// timing variable for cycling pictures
unsigned long prevMillis = 10000;


void setup() {

  Serial.println("starting arcada");
  if (!arcada.arcadaBegin()) {
    while (1);
  }
  arcada.enableSpeaker(false);

  Serial.println("starting circuit playground");
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(100);
  
 
  
  // If we are using TinyUSB we will have the filesystem show up!
  arcada.filesysBeginMSD();

  Serial.begin(115200);
  //while(!Serial) delay(10);       // Wait for Serial Monitor before continuing
  Serial.println("foo");


  // Start TFT and fill blue
  arcada.displayBegin();
  arcada.display->fillScreen(ARCADA_BLUE);
  Serial.println("screen filled, looking for filesystem");

  if (arcada.filesysBegin()) {
    Serial.println("Found filesystem!");
  } else {
    arcada.haltBox("No filesystem found! For QSPI flash, load CircuitPython. For SD cards, format with FAT");
  }

  // Turn on backlight
  arcada.setBacklight(255);
  
}

void playSong() {
  Serial.println("button pressed! playing music");
  for (int thisNote = 0; thisNote < numNotes; thisNote++) { // play notes of the melody
      if (melody[thisNote] != 0){
        if (thisNote % 2){
          for (int p = 0; p <= 8; p=p+2){
            CircuitPlayground.setPixelColor(p, red, 0, 0);
            CircuitPlayground.setPixelColor(p+1, 0, green, 0);
          }
        }
        else{
          for (int p = 0; p <= 8; p=p+2){
            CircuitPlayground.setPixelColor(p, 0, green, 0);
            CircuitPlayground.setPixelColor(p+1, red, 0, 0);
          }
        }
      }
      
      int noteDuration = (1000 / speed) / noteDurations[thisNote];
      CircuitPlayground.playTone(melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
    for (int p = 0; p < 10; p++){
      CircuitPlayground.setPixelColor(p, 0, 0, 0);
    }
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("enering loop");

  for (int p = 0; p < 10; p++){
    CircuitPlayground.setPixelColor(p, 0, 0, 0);
  }

  char *path = "/";
  char *fileList[] {};
  char filename[24];
  File dir;
  dir = arcada.open(path);

  while (1) {
    if (CircuitPlayground.rightButton() || CircuitPlayground.leftButton()) {
      playSong();
    }
    unsigned long nowMillis = millis();
    if (nowMillis - prevMillis >= 10000) {
      prevMillis = nowMillis;
      File entry = dir.openNextFile();
      if (!entry) {
        break;
      }
      entry.getName(filename, 24);
      Serial.println(filename);
      if (strstr(filename, ".bmp")) {
        ImageReturnCode stat = arcada.drawBMP(filename, 0, 0);
        if(stat == IMAGE_ERR_FILE_NOT_FOUND) {
          arcada.haltBox("File not found");
        } else if(stat == IMAGE_ERR_FORMAT) {
          arcada.haltBox("Not a supported BMP variant.");
        } else if(stat == IMAGE_ERR_MALLOC) {
          arcada.haltBox("Malloc failed (insufficient RAM).");  
        }
      }
    }
    
  }

}
