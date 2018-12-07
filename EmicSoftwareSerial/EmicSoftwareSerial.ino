/*
  EmicSoftwareSerial

  Reads an analog input on pin 0 and reads the serial output
  from the SoftwareSerial TX pin using an Emic 2 Text-to-speech module.
  (https://www.sparkfun.com/products/11711)
  This is the minimal example for the Emic module.

  Attach the center pin of a potentiometer to pin A0,
  and the outside pins to +5V and ground. Attach the SIN pin of the
  Emic2 to pin 3 pin of the Arduino

*/
#include <SoftwareSerial.h>

SoftwareSerial emic(2,3);  // RX = 2, TX = 3

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  emic.begin(9600);
  // set the word rate at 400 words per minute (can go 75 - 600 wpm):
  emic.println("W400");
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println("S" + String(sensorValue));
  emic.println("S" + String(sensorValue));
  delay(500);        // delay in between reads for voice legibility
}
