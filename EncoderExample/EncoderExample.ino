/*
  Encoder change

  Many encoders change 4 steps per detent step. This sketch reads
  an encoder and prints the direction of change when it's been
  turned one detent step.

  created 17 June 2019
  by Tom Igoe
*/

#include <Encoder.h>

Encoder knob(0, 1);     // initialize encoder on pins 0 and 1
int lastKnobState = 0;  // set last knob state

void setup() {
  // open serial communications
  Serial.begin(9600);
}

void loop() {
  // read the encoder:
  int knobState = knob.read();
  //get the change in the encoder:
  int knobChange = knobState - lastKnobState;
  // if it's changed by 4 or more pulses:
  if (abs(knobChange) >= 4) {
    // You just want direction of change, not value, so
    // divide value by abs. value to get 1 or -1:
    knobChange = knobChange / abs(knobChange);
    // print the result:
    Serial.println(knobChange);
    // save the current state for next time:
    lastKnobState = knobState;
  }

}
