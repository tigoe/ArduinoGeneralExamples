/*
    Minimal state change detection on button

     created 16 Feb 2020
     by Tom Igoe
*/

// state of the button last time through the loop:
int lastButtonState = LOW;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // wait until the serial monitor is open:
  while (!Serial);

  // set the pinMode for your pushbutton:
  pinMode(3, INPUT);    // use this for pulldown resistor configuration
  //  pinMode(3, INPUT_PULLUP);    // use this for internal pullup resistor configuration

}

void loop() {
  // read the button:
  int buttonState = digitalWrite(3);
  if (buttonState != lastButtonState) {
    // a button using pullups will go LOW when pressed, high when unpressed
    // a button using pulldowns will do the reverse:
    if (buttonState == HIGH) {
      Serial.print("button state is high");
    } else {
      Serial.println("Button state is low");
    }
    // save the current button state for comparison next time:
    lastButtonState = buttonState;
  }
}
