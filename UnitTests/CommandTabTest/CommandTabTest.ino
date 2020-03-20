/*
  A test of the Keyboard library's ability to send command-tab
  messages to switch applications. Inspired by Jake Sherwood.

  created 7ish Mar 2020
  by Tom Igoe
 */
#include <Keyboard.h>

void setup() {
  Keyboard.begin();
}

void loop() {
  // press the command key:
  Keyboard.press(KEY_LEFT_GUI);
  // do this ten times, assuming you'll scroll through ten apps:
  for (int x = 0; x < 10; x++) {
    // delay after the command key:
    delay(170);
    // press tab:
    Keyboard.press(KEY_TAB);
    // hold time:
    delay(260);
    // release tab:
    Keyboard.release(KEY_TAB);
  }
  // release everything:
  Keyboard.releaseAll();
  // don't loop:
  while (true);
}
