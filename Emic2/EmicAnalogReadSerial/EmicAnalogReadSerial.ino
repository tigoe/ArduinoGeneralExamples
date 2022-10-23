/*
  EmicAnalogReadSerial

  Reads an analog input on pin 0 and reads the serial output
  from the Serial1 TX pin using an Emic 2 Text-to-speech module.
  (https://www.sparkfun.com/products/11711)
  This is the minimal example for the Emic module.

  Note: Serial1 is only available on board with two hardware serial 
  ports, such as the SAMD boards (Nano 33 IoT, 
  MKR), the 32U4 boards (Leonardo, Micro), 
  the Due. For Uno boards, use SoftwareSerial 
  instead.

  Attach the center pin of a potentiometer to pin A0,
  and the outside pins to +5V and ground. 
  Attach the SIN pin of the Emic2 to the TX pin 
  of the Arduino.

*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial1.begin(9600);
  // set the word rate at 400 words per minute (can go 75 - 600 wpm):
  Serial1.println("W400");
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println("S" + String(sensorValue));
  Serial1.println("S" + String(sensorValue));
  delay(500);        // delay in between reads for voice legibility
}
