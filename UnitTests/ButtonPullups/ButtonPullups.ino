/*
    Minimal test to see if a pushbutton works. Does nothing else.

     created 16 Feb 2020
     by Tom Igoe
*/
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
  // print out the state. If it's wired with a pullup
  // resistor, it will go HIGH (1) when pressed.
  // if it's wired with a pulldown resistor, it will go
  // LOW (0) when pressed:
  Serial.println(buttonState);
}
