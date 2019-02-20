void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // set a timeout of 10 ms for parsing numbers
  // from the incoming serial string:
  Serial.setTimeout(10);
}

void loop() {
  // look for an integer in the incoming serial string:
  while (Serial.available()) {
    int x = Serial.parseInt();
    Serial.println(x);
  }
}
