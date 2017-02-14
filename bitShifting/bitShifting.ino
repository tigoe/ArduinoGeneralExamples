void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int x = 0; x < 8; x++) { // loop fom 0 to 7
    byte number = 1 << x;       // shift a number left by x bits
    Serial.print(number);       // print it in decimal
    Serial.print("\t");         // print a tab
    Serial.println(number, BIN);// print it in binary
    delay(500);
  }
  delay(5000);
  for (int x = 0; x < 8; x++) {   // loop fom 0 to 7
    byte number = 0x10000000 >> x;// shift a number right by x bits
    Serial.print(number);         // print it in decimal
    Serial.print("\t");           // print a tab
    Serial.println(number, BIN);  // print it in binary
    delay(500);
  }
  delay(5000);
}
