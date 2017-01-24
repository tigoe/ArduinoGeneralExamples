/*
   Interruptible Fade of an LED using Scheduler
   Works on any of the ARM-based Arduino and compatible boards

   Fades an LED once every 30ms in the fader() function,
   and checks a button in the main loop() function.

   created 24 Jan 2017
   by Tom Igoe
*/

#include <Scheduler.h>    // scheduler works only on ARM boards

const int buttonPin = 5;  // pushbutton on pin 5
const int ledPin = 3;     // LED on pin 3

volatile byte level = 0;  // volatile because both loops change it
int increment = 1;        // increment of change of the fade level

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Scheduler.startLoop(fader);   // start fader() as a loop
}

void loop() {
  // read the button:
  int buttonState = digitalRead(buttonPin);
  // set level to 0 while the button is held down:
  if (buttonState == LOW) {
    level = 0;
  }
  yield();    // yield processor to other loops
}

void fader() {
  analogWrite(ledPin, level); // fade the LED

  level = level + increment;  // change the level
  // if the level is at the extremes, change the
  // direction of the increment:
  if (level == 255 || level == 0) {
    increment = -increment;
  }
  delay(30);    // wait 30ms
  yield();      // yield to other loops
}

