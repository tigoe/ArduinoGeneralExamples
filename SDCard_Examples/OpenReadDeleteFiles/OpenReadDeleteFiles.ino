/*
  SD open, read, delete

  This sketch reads an SD card connected to the SPI bus
  It opens each file in turn, reads one line from it, and then deletes
  the file. 

  created 6 May 2021
  by Tom Igoe
*/

#include <SD.h>

const int csPin = 10;
File root;

void setup() {
  Serial.begin(9600);
  // wait for serial port to open:
  while (!Serial);
  Serial.println("starting SD card:");
  // wait for SD card to initialize:  
  while (!SD.begin(csPin));
  Serial.println("SD card works. Getting root directory:");
  // open the root directory:
  root = SD.open("/");
  Serial.println("Let's go:");
}

void loop() {
  // open the next file in the root directory:
  File entry = root.openNextFile();
  // if there is a file to read:
  if (entry) {
    // set a 10ms timeout for reading strings from the file
    // (this speeds up reading the strings a bit):
    entry.setTimeout(10);
    // if the file is not a directory:
    if (!entry.isDirectory()) {
      // print the file name:
      Serial.println(entry.name());
      // read from the file until there's nothing else in it:
      while (entry.available()) {
        // this assumes all the data for each entry
        // are on a single line with a newline at the end:
        String data = entry.readString();
        // do something with the data:
        Serial.println(data);
      }
      Serial.println("file removed");
    }
    // close the file:
    entry.close();
    // remove the file:
    SD.remove(entry.name());
  }
}
