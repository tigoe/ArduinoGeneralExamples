/*
  Multiple button read
  reads buttons 2 through 9, saves them to the 8 bits
  of a single byte

  created 18 Feb 2020
  by Tom Igoe and Cy Kim
*/

// global variable to hold 8 values of 8 button states:
byte buttons = 0b00000000;

void setup() {
  // start serial communication:
  Serial.begin(9600);
  // loop over the buttons:
  for (int p = 0; p < 8; p++) {
    // set the IO state of each button
    // note: buttons 2 through 9
    pinMode(p + 2, INPUT_PULLUP);
  }
}

void loop() {
  // loop over the buttons:
  for (int p = 0; p < 8; p++) {
    // read the state of each button input:
    // note: buttons 2 through 9
    int thisButton = digitalRead(p + 2);
    // write the state of each button
    // to the equivalent bit position in the variable buttons:
    buttons = buttons | (thisButton << p);
  }
  // print it out in binary:
  Serial.println(buttons, BIN);
}
