/*
  Check battery level once a second and write to an SD card
  Circuit:
      SD card in a MKR Zero

  created 18 Mar 2019
  by Tom Igoe
*/

#include <RTCZero.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoLowPower.h>

const int chipSelect = SDCARD_SS_PIN;

RTCZero rtc;
int days = 0;
volatile bool awake = true;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }

  // set clock. You only care about time since sketch started:
  rtc.begin();
  rtc.setTime(0, 0, 0);

  // write to the SD card:
  cardWrite("V, %, Uptime");
  // call the wake() function when processor wakes up:
  LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, wake, CHANGE);
}

void loop() {
  if (awake) {
    // turn on the LED while awake:
    digitalWrite(LED_BUILTIN, HIGH);
    // read the battery:
    int adcBatt = analogRead(ADC_BATTERY);

    // convert to a voltage:
    float vBatt = adcBatt * (4.3 / 1023.0);
    float percentage = (vBatt / 4.3) * 100;

    // Format a string like so:
    // xx.xx, yy.yy, d:h:m:s
    String logger = String(vBatt);
    logger += ", " + String(percentage);
    logger += ", " + String(days);
    logger += ":" + String(rtc.getHours());
    logger += ":" + String(rtc.getMinutes());
    logger += ":" + String(rtc.getSeconds());

    // Write to the SD card:
    cardWrite(logger);

    // handle day rollover (customized in case you go over a month):
    if (rtc.getHours() == 23
        && rtc.getMinutes() == 59
        && rtc.getSeconds() == 59) days++;
  }
  // turn off the LED before sleeping:
  digitalWrite(LED_BUILTIN, LOW);
  // put the processor to sleep for 900ms:
  awake = false;
  LowPower.sleep(900);
}

// when the processor wakes up, set awake = true:
void wake() {
  awake = true;
}

// display the text on the screen:
void cardWrite(String message) {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(message);
    Serial.println(message);
    dataFile.close();
  }
}
