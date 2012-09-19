/*
  LED chaser with tilt switch
 
 This sketch turns on 7 LEDs in a linear sequence. There is a tilt switch 
 on pin 10 that, depending on its state, determines the direction of the 
 sequence.
 
 Circuit: 
 * LEDs on pins 2 through 9
 * Tilt switch on pin 10
 
 created 19 Sep 2012
 by Tom Igoe
 */
 
void setup() {
  // loop over the pins that the LEDs are on, and
  // make them all outputs:
  for (int pin = 2; pin < 10; pin++)  {
    pinMode(pin, OUTPUT); 
  }
  // make pin 10 an input:
  pinMode(10, INPUT);
}

void loop() {
  // read the tilt switch:
  int tiltSwitch =digitalRead(10);

  // if the tilt switch is high, turn on pins
  // in ascending order:
  if (tiltSwitch == HIGH) {
    // loop over the pins to turn them on:
    for (int pin = 2; pin < 10; pin++)  {
      digitalWrite(pin,HIGH);  // turn the pin on
      delay(50);               // small delay before the next pin
    }
    // loop over the pins to turn them off:
    for (int pin = 2; pin < 10; pin++)  {
      digitalWrite(pin,LOW); // turn the pin on
      delay(50);             // small delay before the next pin
    }
  } 
  // if the tilt switch is low, turn on pins
  // in descending order:
  else {
    // loop over the pins to turn them on:
    for (int pin = 9; pin > 1; pin--)  {
      digitalWrite(pin,HIGH); // turn the pin on
      delay(50);               // small delay before the next pin
    }
    // loop over the pins to turn them off:
    for (int pin = 9; pin > 1; pin--)  {
      digitalWrite(pin,LOW); // turn the pin on
      delay(50);             // small delay before the next pin
    } 
  }
}





