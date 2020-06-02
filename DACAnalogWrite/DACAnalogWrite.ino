/*
  DAC example for SAMD boards (MKR series, Nano 33 IoT)

  Reads an analog input, uses it to set the voltage attached
  to the DAC on pin A0 of the SAMD-based boards.

  created 1 Jun 2020
  by Tom Igoe
*/

void setup() {
  // initialize serial communications:
  Serial.begin(9600);
  // set DAC resolution to 10-bit:
  analogWriteResolution(10);
}

void loop() {
  // read analog in 1:
  int level = analogRead(A1);
  // convert to a voltage (assumes 3.3V reference voltage):
  float voltage = (level * 3.3) / 1024.0;
  // set the DAC using the analog in level:
  analogWrite(A0, level);

  // print it:
  Serial.print("voltage: ");
  Serial.println(voltage);
}
