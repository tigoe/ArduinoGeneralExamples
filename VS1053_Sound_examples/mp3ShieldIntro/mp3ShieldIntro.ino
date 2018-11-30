/*
 VS1053 example
 using SparkFun MP3 shield
 and Adafruit VS1053 library
 in beatiful harmony

 created 30 Nov 2018
 by Tom Igoe
 
 */
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// VS1053 and SD card are both SPI devices.
// Set their respective pins:

// These are the pin numbers for the SparkFun MP3 shield:
#define VS1053_RESET   -1     // VS1053 reset pin (not used)
#define VS1053_CS       6     // VS1053 chip select pin 
#define VS1053_DCS      7     // VS1053 Data/command select pin 
#define CARDCS          9     // SD card chip select pin
#define VS1053_DREQ     2     // VS1053 Data request

// make an instance of the MP3 player library:
Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);


void setup() {
  Serial.begin(9600);
  // initialize the MP3 player:
  if (! musicPlayer.begin()) {
    Serial.println("Couldn't find VS1053. Do you have the right pin numbers set?");
    while (true);
  }

  // start communication with the MP3 shield:
  if (!SD.begin(CARDCS)) {
    Serial.println("SD failed, or not present");
    while (true);  // don't do anything more
  }

  // Set volume for left and right channels.
  // 0 = loudest, 100 = silent:
  musicPlayer.setVolume(10, 10);
  // use the VS1053 interrrupt pin so it can
  // let you know when it's ready for commands.
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  // file names must be 8 characters long, maximum, plus .mp3:
  musicPlayer.startPlayingFile("SOUND001.MP3");
}

void loop() {
  // read a potentiometer (0-1023 readings) and
  // map to a range from 100 to 0:
  int loudness = map(analogRead(A0), 0, 1023, 100, 0);
  // set the volume:
  musicPlayer.setVolume(loudness, loudness);

  // loop the player:
  if (musicPlayer.stopped()) {
    musicPlayer.startPlayingFile("SOUND001.MP3");
  }
}
