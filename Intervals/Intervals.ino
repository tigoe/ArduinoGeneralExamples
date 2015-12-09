#include "interval.h"

Timer ledTimer;               // set a timer for the LED
Timer motorTimer;             // set a timer for the motor
int blinkState = HIGH;        // the LED state, HIGH or LOW

void setup() {
  Serial.begin(9600);          // initialize serial
  pinMode(13, OUTPUT);         // set the LED to be an output
  ledTimer.set(blink, 2000);   // timer's callback function is blink, interval is 2000ms
  motorTimer.set(spin, 1000);  // timer's callback function is spin, interval is 2000ms
}

void loop() {
  ledTimer.interval = analogRead(A0); // read a pot, change LED timer interval
  ledTimer.check();                   // check the LED timer
  motorTimer.check();                 // check the motor timer
}

void blink() {
  blinkState = !blinkState;
  digitalWrite(13, blinkState);
  Serial.println("\ttock");
}

void spin() {
  Serial.println("motor is spinning");
}


