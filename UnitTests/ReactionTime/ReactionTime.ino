/*
  Reaction timer
  Crude test of how long it takes a user
  to press a button after an LED is turned on

   created by Tom Igoe
   8 Mar 2020
*/

// I/O pin for the button
const int buttonPin = 2;

// button press count
int count = 0;
// previous state of the button
int lastButtonState = HIGH;

// reaction test start and end
long startTime = 0;
long endTime = 0;
bool timing = false;

void setup() {
  // initialize serial, button and LED:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (!timing) {
    // random delay from 1-7 secs:
    delay (random(1000, 7000));
    Serial.println("go");
    // set timing flag, LED, and startTime:
    timing = true;
    digitalWrite(LED_BUILTIN, HIGH);
    startTime = millis();
  }

  // read the button:
  int buttonState = digitalRead(buttonPin);
  // if it's changed:
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {     // if it's pressed:
      endTime = millis();
    }  else {     // if it's released:
      // print the reaction time on release:
      Serial.print("reaction time: ");
      Serial.print(endTime - startTime);
      Serial.println(" ms");
      // reset timing flag and LED:
      timing = false;
      digitalWrite(LED_BUILTIN, LOW);
    }
    // save state for next time:
    lastButtonState = buttonState;
  }

}
