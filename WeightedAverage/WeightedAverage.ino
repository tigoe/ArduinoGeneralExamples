/*
  Weighted average on an analog sensor
  Uses a trimmer pot on A1 to set the weighting, 
  but in a real-world application, you'd likely use other factors

  Based on an idea from   David Schultz, at
  http://home.earthlink.net/~david.schultz/rnd/2002/KalmanApogee.pdf

  created 17 Oct 2005
  refactored 20 Feb 2017
  by Tom Igoe
 */
float lastEstimate = 0;     // last estimate of the reading 
float currentEstimate = 0;  // current estimate

void setup() {
  Serial.begin(9600);       // initialize serial
}

void loop() {
  int sensorValue = analogRead(A0);       // read the sensor
  delay(1);                               // delay to let ADC stabilize
  float weight = analogRead(A1) / 1023.0; // weight from 0 to 1
  // filter the sensor's result:
  float currentEstimate = (sensorValue * weight) + (lastEstimate * (1 - weight));
  
  Serial.print(sensorValue);          // print the unfiltered value
  Serial.print(",");                  // print a comma
  Serial.println(currentEstimate);    // print the current estimate
  lastEstimate = currentEstimate;     // save the current estimate for next time
}


