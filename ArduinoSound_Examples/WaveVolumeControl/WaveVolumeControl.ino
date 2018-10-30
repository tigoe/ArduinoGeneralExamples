/*
  This reads a wave file from an SD card and plays it using the I2S interface to
  a MAX08357 I2S Amp Breakout board.

  A potentiometer connected to pin A0 adjusts the volume
  
  The wav file must be stereo signed 16 bit 44100Hz.

  Circuit:
   Arduino/Genuino Zero, MKRZero or MKR1000 board
   SD breakout or shield connected
   MAX08357:
     GND connected GND
     VIN connected 5V
     LRC connected to pin 0 (Zero) or pin 3 (MKR1000, MKRZero)
     BCLK connected to pin 1 (Zero) or pin 2 (MKR1000, MKRZero)
     DIN connected to pin 9 (Zero) or pin A6 (MKR1000, MKRZero)

  created 15 November 2016
  by Sandeep Mistry
  modified 29 Oct 2018
  by Tom Igoe
*/

#include <SD.h>
#include <ArduinoSound.h>

// filename of wave file to play
const char filename[] = "mySound.wav";

// variable representing the Wave File
SDWaveFile waveFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // wait until serial monitor is open. This is
  // for debugging only. Remove when writing your own code:
  while (!Serial);
 
  // setup the SD card, depending on your shield of breakout board
  // you may need to pass a pin number in begin for SS
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card is valid.");

  // create a SDWaveFile
  waveFile = SDWaveFile(filename);

  // check if the WaveFile is valid
  if (!waveFile) {
    Serial.println("wave file is invalid!");
    while (1); // do nothing
  }
  // print the file's duration:
  long duration = waveFile.duration();
  Serial.print("Duration = ");
  Serial.print(duration);
  Serial.println(" seconds");

  // check if the I2S output can play the wave file
  if (!AudioOutI2S.canPlay(waveFile)) {
    Serial.println("unable to play wave file using I2S!");
    while (1); // do nothing
  }

  // start playback
  Serial.println("looping file");
  AudioOutI2S.loop(waveFile);
}

void loop() {
  // read analog in
  int sensorReading = analogRead(A0);
  // map to a 0-100 range:
  int loudness = map(sensorReading, 0, 1023, 0, 100);
  // set the volume:
  AudioOutI2S.volume(loudness);
  Serial.print("loudness: ");
  Serial.println(loudness);
}
