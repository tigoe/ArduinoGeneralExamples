/*
  Tuning the sensitivity of a button debounce delay
  with a potentiometer

   created by Tom Igoe
   8 Mar 2020
*/

// I/O pin for the button
const int buttonPin = 2;

// button press count
int count = 0;
// previous state of the button
int lastButtonState = HIGH;

void setup() {
  // initialize serial and button:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read the tuning potentiometer:
  int debounceDelay = analogRead(A1);

  // read the button:
  int buttonState = digitalRead(buttonPin);
  // if it's changed:
  if (buttonState != lastButtonState) {
    // debounce:
    delay(debounceDelay);
    if (buttonState == LOW) {     // if it's pressed:
      count++;
      Serial.println("press");

    } else {    // if it's released:
      Serial.println("release");
      Serial.println(String(count) + " presses");
      Serial.print("debounced: ");
      Serial.println(String(debounceDelay) + "ms");
      Serial.println();
    }
    // save for next time:
    lastButtonState = buttonState;
  }
}
