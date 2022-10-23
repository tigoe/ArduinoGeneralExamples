/*
  EmicAnalogReadSerial

  Reads serial in from the serial monitor and sents serial output
  from the Serial1 TX pin to an Emic2 Text-to-speech module.
  (https://www.sparkfun.com/products/11711)
  This is the minimal example for the Emic module.

  Note: Serial1 is only available on board with two software serial ports, such as the SAMD boards (Nano 22 IoT, MKR), the 32U4 boards (Leonardo, Micro), the Due. For Uno boards, use SoftwareSerial instead.

Attach the SIN pin of the Emic2 to the TX pin of the Arduino and the SOUT to the RX pin of the Arduino. 

*/
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial1.begin(9600);
  // set the word rate at 275 words per minute (can go 75 - 600 wpm):
  Serial1.println("W275");
}

void loop() {
  // read serial from the Serial Monitor:
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    // print out the value you read to the Emic2:
    Serial.println("S" + input);
    Serial1.println("S" + input);
  }
  delay(500);  // delay in between reads for voice legibility
}