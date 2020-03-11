/*
  Tuning the sensitivity of a light sensor
  with a potentiometer

   created by Tom Igoe
   8 Mar 2020
*/


void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int lightSensor = analogRead(A0);
  // 1 ms delay to stabilize ADC:
  delay(1);
  // read the tuning potentiometer:
  int threshold = analogRead(A1);
  // print the sensor val:
  Serial.print("sensor: " + String(lightSensor));
  // if the sensor val is over the threshold, print that:
  if (lightSensor > threshold) {
    Serial.print("  over threshold: " + String(threshold));
  }
  // end of line:
  Serial.println();
}
