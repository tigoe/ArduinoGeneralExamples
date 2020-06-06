/*
 ADC_BATTERY is pin 33 for the MKR boards, though it's only 
 declared in the MKRZero board definition.
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the battery:
int adcBatt = analogRead(ADC_BATTERY);
  // convert to a voltage:
  float vBatt = adcBatt * (4.3 / 1023.0);
  float percentage = (vBatt / 4.3) * 100;
  // print it:
  Serial.print(vBatt);
  Serial.print ("V, ");
  Serial.print(percentage);
  Serial.println("%");
  delay(1);
}
