/*
  Bit masking to determine which bits of a byte are set.
 */
void setup() {
  Serial.begin(9600);
}

void loop() {
  byte number = random(255);        // get an arbitrary number from 0 - 255
  Serial.print("Random number: ");
  Serial.print(number);             // print the number in decimal
  Serial.print( " = ");             // print a tab
  Serial.println(number, BIN);      // print the number in binary
  
  // which bits are set? (set = 1, cleared = 0)
  for (int b = 0; b < 8; b++) {     // loop from 0 to 7
    byte mask = 1 << b;             // make a mask
   
    // compare the mask and the number bitwise:
    if ((number & mask) > 0) {       // if the result is > 0
      Serial.print("Bit number ");
      Serial.print(b);
      Serial.println(" is 1");      // then this bit is 1 (set)
    } else {                        // if the result is < 0
      Serial.print("Bit number ");
      Serial.print(b);
      Serial.println(" is 0");      // then this bit is 0 (cleared)
    }
    delay(100);                     // delay just to see it slower
  }
  Serial.println();                 // print an empty line
  delay(10000);
}
