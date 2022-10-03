int ledPins[] = {2, 3, 9, 10, 11, 12};
int intensity = 127;
int difference = 10;
long lastLoopTime = 0;
int interval = 50;
int thisLed = 0;

void setup() {
  for (int p = 0; p < 6; p++) {
    pinMode(ledPins[p], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  if (millis() - lastLoopTime > interval) {
    // increment thisLed
    thisLed++;
    thisLed %= 6;
    
    // increment intensity:
 //   intensity += difference;

    //  for a more random effect,
    // comment out the previous line and add these lines:
    //reset the random number generator when on the first LED:
    if (thisLed == 0) randomSeed(millis());
    //increment with a random number:
    intensity += random(-difference, difference);

    // if intensity gets to an extreme, reverse difference:
    if (intensity <= 0 || intensity >= 255) {
      difference = -difference;
    }


    // constrain intensity:
    intensity = constrain(intensity, 0, 255);
    // set LED intensity:
    analogWrite(ledPins[thisLed], intensity);
    // update timestamp:
    lastLoopTime = millis();
  }
}
