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
  int knobState = analogRead(A0);
  int buttonState = digitalRead(2);
  String jsonString = "{\"knob\": ";
  jsonString += String(knobState);
  jsonString += ", \"button\":";
  jsonString += String(buttonState);
  jsonString += "}";

  Serial.println(jsonString);
}
