#include <Arduino_JSON.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  /*
    What we're waiting for:
    {"mousex": 345, "mousey": 600 }
  */
  // variables for incoming results:
  int x = 0;
  int y = 0;
  
  // as long as there's any incoming serial data:
  while (Serial.available() > 0) {
    // read until you get a newline:
    String incoming = Serial.readStringUntil('\n');
    // convert to JSON:
    JSONVar jsonData = JSON.parse(incoming);

    // Check to see if you have what you need:
    if (jsonData.hasOwnProperty("mousex") &&            // does the property exist?
        JSON.typeof(jsonData["mousex"]) == "number") {  // is it the right data type?
      x = int(jsonData["mousex"]);                      // then use it.
    }

    if (jsonData.hasOwnProperty("mousey") &&            // does the property exist?
        JSON.typeof(jsonData["mousey"]) == "number") {  // is it the right data type?
      y = int(jsonData["mousey"]);                      // then use it.
    }

    // print the result:
    Serial.print("x = ");
    Serial.print(x);
    Serial.print(",   y = ");
    Serial.println(y);
  }
}
