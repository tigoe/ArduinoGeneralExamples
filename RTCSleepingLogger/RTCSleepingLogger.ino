/*
  TMP36 SD datalogger  with sleep functionality
  Saves data from two analog inputs to an SD card and shows how to
  use an alarm to wake an M0-based board  from standby mode.
  Works only on M0-based boards.

  Note that the USB serial port will disappear while the board is in standby mode.
  To bring the board out of standby mode, double-tap the reset button.

  RTC code based on Arturo Guadalupi's RTC sleep example 
  created by Tom Igoe
  20 Feb 2018
*/

#include <RTCZero.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;   // CS pin for the SD card. For MKRZero use SDCARD_SS_PIN
RTCZero rtc;                // realtime clock
int state = LOW;            // LED state
bool cardPresent = false;   // if the card is present
float refVoltage = 0;       // reference voltage of the board

void setup() {
  Serial.println(__DATE__);         // print date of compile
  Serial.println(__TIME__);         // print time of compile
  pinMode(LED_BUILTIN, OUTPUT);     // set builtin LED to output
  cardPresent = initializeCard();   // check to see if SD card is accessible

  rtc.begin();                      // start the realtime clock
  rtc.setAlarmTime(00, 00, 00);     // set an alarm for processor wakeup
  rtc.enableAlarm(rtc.MATCH_SS);    // enable it
  rtc.attachInterrupt(alarmMatch);  // have the wakeup happen when the RTC seconds matches 00

  // to set the date and time (epoch, or seconds since 1/1/1970) from a POSIX machine, type:
  // $ date +D%DT%s
  // thanks to Paul Stoffregen for this trick

  // wait ten seconds for user to input datetime via serial:
  while (millis() < 10000) {
    digitalWrite(LED_BUILTIN, HIGH);
    if (Serial.available()) {
      // if you get the D
      if (Serial.findUntil("D", "T")) {
        rtc.setMonth(Serial.parseInt());  // set the month, day, year
        rtc.setDay(Serial.parseInt());
        rtc.setYear(Serial.parseInt());
      } // if you get the T:
      if (Serial.findUntil("T", "\n")) {
        unsigned long epoch = Serial.parseInt();  // set the epoch
        rtc.setEpoch(epoch);
        Serial.println(getTimeStamp());   // print the timestamp
      }
    }
  }
  // serial delay over, turn off the LED:
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  rtc.standbyMode();    // Sleep until next alarm match
}

void alarmMatch() {
  String timestamp = getTimeStamp();    // get the timestamp
  float tempNow = temperatureRead();    // get the temperature now
  digitalWrite(LED_BUILTIN, HIGH);      // turn on the LED
  if (cardPresent) {                    // if the SD card is present
    writeToCard(tempNow, timestamp);    // write temp and time to SD card
  } else {                              // if card's not there,
    Serial.print(timestamp);            // print data serially
    Serial.print(",");
    Serial.println(tempNow);
  }
  digitalWrite(LED_BUILTIN, LOW);       // turn off the LED after writing
}

String getTimeStamp() {
  // make an ISO8601 formatted timestring:
  //  e.g. 2018 - 02 - 21T01: 49: 51.296Z
  String timestamp = "20";
  timestamp += rtc.getYear();
  timestamp += "-";
  if (rtc.getMonth() <= 9) timestamp += "0";
  timestamp += rtc.getMonth();
  timestamp += "-";
  if (rtc.getDay() <= 9) timestamp += "0";
  timestamp += rtc.getDay();
  timestamp += "T";
  if (rtc.getHours() <= 9) timestamp += "0";
  timestamp += rtc.getHours();
  timestamp += ":";
  if (rtc.getMinutes() <= 9) timestamp += "0";
  timestamp += rtc.getMinutes();
  timestamp += ":";
  if (rtc.getSeconds() <= 9) timestamp += "0";
  timestamp += rtc.getSeconds();
  timestamp += "Z";
  return timestamp;
}

float temperatureRead() {  // read the temperature sensor:
  int tempSensor = analogRead(A0);
  delay(1);   // let the ADC stabilize
  // read the board voltage on A1:
  refVoltage = (analogRead(A1) / 1023.0) * 3.3;
  // convert temp to voltage:
  float voltage = (tempSensor / 1023.0) * refVoltage;
  // convert to temperature (degrees Celsius):
  float temperature = (voltage - 0.5) / 0.01;
  return temperature;
}

bool initializeCard() {
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return false;
  }
  Serial.println("card initialized.");
  return true;
}


bool writeToCard(float temp, String datetime) {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(datetime);
    dataFile.print(",");
    dataFile.print(refVoltage);
    dataFile.print("V,");
    dataFile.print(temp);
    dataFile.println("deg.C,");
    dataFile.close();
    Serial.println("data written");
    return true;
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening  datalog.txt");
    return false;
  }
}
