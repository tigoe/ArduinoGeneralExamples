/*
  Encoder change with pushbutton

  Many encoders change 4 steps per detent step. This sketch reads
  an encoder and prints the direction of change when it's been
  turned one  detent step.

  Additionally, many encoders have a built-in pushbutton.
  This sketch  reads both the encoder's change and the pushbutton
  change.

  created 17 June 2019
  by Tom Igoe
*/

#include <Encoder.h>

const int buttonPin = 5; // pushbutton is on pin 5
Encoder knob(0, 1);      // initialize encoder on pins 0 and 1
int lastKnobState = 0;   // set last knob state
int lastButtonState = 0; // set last button state

void setup() {
  // open serial communications
  Serial.begin(9600);
  pinMode (buttonPin, INPUT_PULLUP);
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
    // save the current state for comparison next time:
    lastKnobState = knobState;
  }

  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the pushbutton has changed:
  if (buttonState != lastButtonState) {
    // wait a few milliseconds to debounce the button
    delay(3);
    // print the type of change, depending on the
    // state of the button:
    if (buttonState == LOW) {
      Serial.println("button was pressed");
    } else {
      Serial.println("button was released");
    }
    // save the current button state for comparison next time:
    lastButtonState = buttonState;
  }
}
