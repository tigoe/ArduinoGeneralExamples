/*
   Battery voltage logger for MKR Zero/1010 etc

   Creating a FAT16/FAT32 SD card to work with the library on MacOS:
   On the mac terminal, list your disks:
   $ diskutil list
   You should get a response like this:
   /dev/disk2 (external, physical):
  etc.

   Then format your disk:
   $ sudo diskutil eraseDisk FAT32 DISKNAME MBRFormat /dev/disk2
  
   DISKNAME needs to be all caps, 8 characters or less.
   /dev/disk2 comes from the list you got from diskutil list

   created 10 April 2019
   by Tom Igoe
*/
#include <SD.h>
// The chip select pin. For MKRZero it's SDCARD_SS_PIN
// for mem shield, it's 4
#define SD_CHIP_SELECT 4

// whether or not the SD card initialized:
bool SDAvailable = false;
// name of the file to write to:
String logFile = "DATALOG.CSV";

void setup() {
  Serial.begin(9600);
  while (!Serial);
  // initialize SD card:
  SDAvailable = SD.begin(SD_CHIP_SELECT);
  Serial.println("Card working: " + String(SDAvailable));
}

void loop() {
  // read the battery:
  int adcBatt = analogRead(ADC_BATTERY);
  // convert to a voltage:
  float vBatt = adcBatt * (4.3 / 1023.0);
  float percentage = (vBatt / 4.3) * 100;
  // print it:
  Serial.print(vBatt);
  Serial.print ("V, ");
  Serial.print(percentage);
  Serial.println("%");

  // If the SD card initialized correctly,
  // write to it:
  if (SDAvailable) {
    File dataFile = SD.open(logFile, FILE_WRITE);
    dataFile.print(vBatt);
    dataFile.print ("V,");
    dataFile.print(percentage);
    dataFile.println("%");
    dataFile.close();
  }
  delay(1000);
}
