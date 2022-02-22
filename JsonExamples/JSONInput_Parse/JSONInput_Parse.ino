/*
  JSON Object Parsing a String

  This sketch demonstrates how to read in a string of text terminated
  by a newline, then parse it as a JSON object.

  Uses Arduino_JSON library: https://librarymanager/All#Arduino_JSON

  note: this can't handle really large JSON strings. The longest I've given it is
  about 900 bytes
  
  created 22 Feb 2022
  by Tom Igoe
  based on examples by Sandeep Mistry
*/

#include <Arduino_JSON.h>

void setup() {
  Serial.begin(9600);
  // wait 3 seconds for serial monitor to open:
  if (!Serial) delay (3000);
}

void loop() {
  // if there is any serial data available:
  if (Serial.available() ) {
    // read until you get a newline character:
    String input = Serial.readStringUntil('\n');
    // convert the incoming string to a JSONVar object:
    JSONVar data = JSON.parse(input);
    // inspect the object for its parts:
    inspect(data);
  }
}

void inspect(JSONVar thisObject) {
  // if this object is not a JSON object type, don't parse it:
  if (JSON.typeof(thisObject) != "object") return;

  // get an array of all the keys in the object:
  JSONVar theseKeys = thisObject.keys();
  Serial.println();
  Serial.println("this is a JSON object. Its keys: ");
  Serial.println(theseKeys);

  // iterate over the keys of the object and get the values:
  for (int i = 0; i < theseKeys.length(); i++) {

    // get the value corresponding to key i:
    JSONVar thisValue = thisObject[theseKeys[i]];

    // print the key and type for this value:
    Serial.print("JSON.typeof(data[");
    Serial.print(theseKeys[i]);
    Serial.print("]) = ");
    Serial.println(JSON.typeof(thisValue));
    // print the value  of this key:
    Serial.print("value of key ");
    Serial.print(theseKeys[i]);
    Serial.print(" = ");
    Serial.println(thisValue);

    // if it's an object inspect it:
    if (JSON.typeof(thisValue) == "object") {
      inspect(thisValue);
    }
    // if it's a string parse it:
    if (JSON.typeof(thisValue) == "string") {
      JSONVar myData = JSON.parse(thisValue);
      // then inspect it:
      inspect(myData);
    }
    // final println:
    Serial.println();
  }
}
