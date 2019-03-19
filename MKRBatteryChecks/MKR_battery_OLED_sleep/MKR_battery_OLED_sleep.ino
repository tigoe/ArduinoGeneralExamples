/*
  Check battery level once a second and display on an SSD1306 OLED
  Sleep for most of a second.
  Circuit:
    SSD1306 128x32 OLED screen attached to I2C

  Font created by http://oleddisplay.squix.ch/

  created 18 Mar 2019
  by Tom Igoe
*/

#include <RTCZero.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "font.h"
#include <ArduinoLowPower.h>

// 128x32 pixel display:
Adafruit_SSD1306 display(128, 32, &Wire);

RTCZero rtc;
int days = 0;
volatile bool awake = true;

void setup() {
  Serial.begin(9600);
  // initialize the display library:
  while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED setup failed. Check connections");
  }

  // set clock. You only care about time since sketch started:
  rtc.begin();
  rtc.setTime(0, 0, 0);

  // call the wake() function when processor wakes up:
  LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, wake, CHANGE);
}

void loop() {
  if (awake) {
    // read the battery:
    int adcBatt = analogRead(ADC_BATTERY);

    // convert to a voltage:
    float vBatt = adcBatt * (4.3 / 1023.0);
    float percentage = (vBatt / 4.3) * 100;

    // Format a string like so:
    // xx.xxV, yy.yy%
    // T: d:h:m:s
    String logger = String(vBatt);
    logger += "V, " + String(percentage);
    logger += "%\nT: " + String(days);
    logger += ":" + String(rtc.getHours());
    logger += ":" + String(rtc.getMinutes());
    logger += ":" + String(rtc.getSeconds());

    // display it on an OLED:
    displayWrite(logger);

    // handle day rollover (customized in case you go over a month):
    if (rtc.getHours() == 23
        && rtc.getMinutes() == 59
        && rtc.getSeconds() == 59) days++;
  }

  // put the processor to sleep for 900ms:
  awake = false;
  LowPower.sleep(900);
}

// when the processor wakes up, set awake = true:
void wake() {
  awake = true;
}

// display the text on the screen:
void displayWrite(String message) {
  display.clearDisplay();
  display.setFont(&Open_Sans_Light_14);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(message);
  display.display();
}
