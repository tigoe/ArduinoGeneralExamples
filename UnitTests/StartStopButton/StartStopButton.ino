/*
  start/stop button
  uses the press of a button
  to change state of the system

   created by Tom Igoe
   8 Mar 2020
*/

// I/O pin for the button
const int buttonPin = 2;
const int debounceDelay = 4;

// previous state of the button
int lastButtonState = HIGH;
bool reading = false;

void setup() {
  // initialize serial, button and LED:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // read the button:
  int buttonState = digitalRead(buttonPin);
  // if it's changed:
  if (buttonState != lastButtonState) {
    delay(debounceDelay);
    if (buttonState == LOW) {     // if it's pressed:
      reading = !reading;
      digitalWrite(LED_BUILTIN, reading);
    }
    // save state for next time:
    lastButtonState = buttonState;
  }

  if (reading) {
    int sensorReading = analogRead(A0);
    Serial.println(sensorReading);
  }

}
