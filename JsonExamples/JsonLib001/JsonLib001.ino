#include <Arduino_JSON.h>

JSONVar jsonData;
void setup() {
  Serial.begin(9600);
}

void loop() {
  /*
    What we're aiming for:
    {"knob": 234,
    "button": 1 }
  */
  jsonData["knob"] = analogRead(A0);
  jsonData["button"] = digitalRead(2);
  Serial.println(JSON.stringify(jsonData));
}
