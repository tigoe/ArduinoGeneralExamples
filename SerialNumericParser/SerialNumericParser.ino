/*
  Serial input with parsing
 
 This example shows how to read a serial stream of 
 comma-separated values, parse the ASCII numeric strings
 int numeric variables, and use them.
 
 The circuit:
 * LEDs on pins 5 and 6. But could be used for many things.
 
 created 7 May 2013
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Assumes a string in from the serial port like so:
  // s ledNumber, brightness \n
  // for example: "s5,200\n":

  int ledNumber = 0;
  int brightness = 0;
  
  if (Serial.find("s")) {
    ledNumber = Serial.parseInt(); // parses numeric characters before the comma
    brightness = Serial.parseInt();// parses numeric characters after the comma
    
    // print the results back to the sender:
    Serial.print("LED number: " );
    Serial.print(ledNumber);
    Serial.print(" at ");
    Serial.println(brightness);

    // set the LED:
    analogWrite(ledNumber, brightness);
  }
}



