/*
   Interruptible Fade of an LED using Interval library
   Works on any of the Arduino and compatible boards

   Fades an LED once every 30ms in the fader() function,
   and checks a button in the main loop() function.

   created 24 Jan 2017
   by Tom Igoe
*/

#include <Interval.h>


const int buttonPin = 5;  // pushbutton on pin 5
const int ledPin = 3;     // LED on pin 3

volatile byte level = 0;  // volatile because both loops change it
int increment = 1;        // increment of change of the fade level
Interval fadeTimer;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  fadeTimer.setInterval(fader, 30);   // start fader() as an interval
}

void loop() {
  // read the button:
  int buttonState = digitalRead(buttonPin);
  // set level to 0 while the button is held down:
  if (buttonState == LOW) {
    level = 0;
  }
  fadeTimer.check();
}

void fader() {
  analogWrite(ledPin, level); // fade the LED

  level = level + increment;  // change the level
  // if the level is at the extremes, change the
  // direction of the increment:
  if (level == 255 || level == 0) {
    increment = -increment;
  }
}

