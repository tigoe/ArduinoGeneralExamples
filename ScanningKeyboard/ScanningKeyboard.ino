/*
  A crude scanning keyboard
  Allows for text entry using one pushbutton.

  Turning the encoder to the right advances the characters through the
  ASCII table. Turning it to the left decreases the character value.
  Pressing the button selects the character and advances the cursor.
  At the low end of the characters, space is followed by tab,
  then DELETE. At the upper end of the characters,
  ~ is followed by carriage return and newline.

  Circuit:
    - rotary encoder attached to pins 4 and 5
    - pushbutton attached to pin 3

  created 23 Feb 2019
  by Tom Igoe
*/

#include <Keyboard.h>

const int buttonPin = 3;
int lastButtonState = LOW;
int timestamp = 0;
int rollover = 750;

char character = 'a';

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  // read the sensors:
  int buttonState = digitalRead(buttonPin);

  // if the button has changed:
  if (buttonState != lastButtonState) {
    // debounce the button:
    delay(10);
    // if button is pressed:
    if (buttonState == LOW) {
      // write the current character and take a timestamp:
      Keyboard.write(character);
      timestamp = millis();
    }
    // save current state for next time through the loop:
    lastButtonState = buttonState;
  }
  // if the button remains pressed, rollover:
  if (buttonState == LOW) {
    // after the rollover delay passes:
    if (millis() - timestamp > rollover) {
      // write the current character again:
      Keyboard.write(character);
      // delay 1/10 of the initial rollover time:
      delay(rollover / 10);
    }
  }

  if (buttonState == HIGH) {
    if (millis() - timestamp > rollover) {
      character++;
      // there are several edge cases:
      switch (character) {
        case 0X1F:        // unprintables below space in ASCII table
          // replace with tab instead:
          character = '\t';
          Keyboard.write(character);
          break;
        case '\t':        // tab:
          // since last character was tab, replace with delete:
          Keyboard.write(KEY_DELETE);
          // reset current character:
          character = 'a';
          break;
        case 127:         // DEL
          // print newline and carriage return instead:
          Keyboard.println();
          break;
        default:
          // delete, then print character, then advance
          Keyboard.write(8);
          Keyboard.write(character);
          break;
      }
      // constrain character to between tab and ~:
      character =  constrain(character, '\t', '~');
      timestamp = millis();
    }
  }
}
