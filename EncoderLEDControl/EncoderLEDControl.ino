/*
  Encoder change with pushbutton

  Reads an encoder and its pushbutton and uses the changes
  to control an LED. The knob turns the intensity up and down
  and the button turns it on and off, saving the intensity
  when turned off for when it turns back on.

  created 17 June 2019
  by Tom Igoe
*/

#include <Encoder.h>

const int buttonPin = 5; // pushbutton is on pin 5
const int ledPin = 3;    // LED is on pin 3
Encoder knob(0, 1);      // initialize encoder on pins 0 and 1
int lastKnobState = 0;   // set last knob state
int lastButtonState = 0; // set last button state
int intensity = 0;       // intensity of the LED
int lastIntensity = 0;   // intensity before LED was last turned off

void setup() {
  // open serial communications
  Serial.begin(9600);
  // set I/O pin states:
  pinMode (buttonPin, INPUT_PULLUP);
  pinMode (ledPin, OUTPUT);
}

void loop() {
  // add any encoder knob change to the intensity:
  intensity = intensity + readEncoderChange();
  // constrain it to 0-255:
  intensity = constrain(intensity, 0, 255);

  // if the button is released:
  if (readButtonChange() == 1) {
    // if the light is on, turn it off:
    if (intensity > 0) {
      // save intensity before it's turned off:
      lastIntensity = intensity;
      intensity = 0;
    } else {
      // restore it to the last intensity before turning off:
      intensity = lastIntensity;
    }
  }
  // update the intensity of the LED:
  analogWrite(ledPin, intensity);
}

int readEncoderChange() {
  // returns 0 for no change, -1 for one direction, 1 for the other:
  int result = 0;
  // read the encoder:
  int knobState = knob.read();
  //get the change in the encoder:
  int knobChange = knobState - lastKnobState;
  // if it's changed by 4 or more pulses:
  if (abs(knobChange) >= 4) {
    // You just want direction of change, not value, so
    // divide value by abs. value to get 1 or -1:
    result = knobChange / abs(knobChange);
    // save the current state for comparison next time:
    lastKnobState = knobState;
  }
  return result;
}

int readButtonChange() {
  // returns 0 for no change, 1 for HIGH, -1 for LOW
  int result = 0;
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the pushbutton has changed:
  if (buttonState != lastButtonState) {
    // wait a few milliseconds to debounce the button
    delay(3);
    // print the type of change, depending on the
    // state of the button:
    if (buttonState == LOW) {
      result = -1;
    } else {
      result = 1;
    }
    // save the current button state for comparison next time:
    lastButtonState = buttonState;
  }
  return result;
}
