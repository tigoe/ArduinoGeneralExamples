void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  /*
    What we're aiming for:
    {"knob": 234,
    "button": 1 }
  */
  // make the prototype string:
  String jsonString = "{\"knob\": KNOBVAL, \"button\": BUTTONVAL }";
  // read the sensors:
  int knobState = analogRead(A0);
  int buttonState = digitalRead(2);
  // replace the placeholders in the prototype
  // with the actual values:
  jsonString.replace("KNOBVAL", String(knobState));
  jsonString.replace("BUTTONVAL", String(buttonState));
  Serial.println(jsonString);
}
