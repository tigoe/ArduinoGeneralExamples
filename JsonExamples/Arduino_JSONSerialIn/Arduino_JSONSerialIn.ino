/*
  JSON Object

  This sketch demonstrates how to use the
  Official Arduino JSON library to read
  JSON objects in the serial port

  created 31 Mar 2019
  updated 10 April 2020
  by Tom Igoe
  from examples by Sandeep Mistry
*/

#include <Arduino_JSON.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  // wait for serial input:
  /*
    What we're waiting for:
    unknown JSON string
    {"bri":234, "ct":5343, "on": true}
    {"name":"Apollo", "age": 3, "tagged": true, "new":false}
  */

  while (Serial.available()) {
    // read until newline"
    String incoming = Serial.readStringUntil('\n');

    // parse the string into a JSONVar object:
    JSONVar jsonOjbect = JSON.parse(incoming);

    // jsonOjbect.keys() can be used to get an array
    // of all the keys in the object
    JSONVar jsonKeys = jsonOjbect.keys();

    // read over the object, one key at a time:
    for (int i = 0; i < jsonKeys.length(); i++) {
      JSONVar thisValue = jsonOjbect[jsonKeys[i]];
      Serial.print("Item number : ");
      Serial.println(i);
      // print the key and the value:
      Serial.print(jsonKeys[i]);
      Serial.print(" : ");
      Serial.println(thisValue);

      // print the data type:
      Serial.print("Data type : ");
      Serial.println(JSON.typeof(thisValue));

      // here's how you can get the data type and convert
      // to another variable:
      if (JSON.typeof(thisValue) == "number") {
        int copiedValue = (int)thisValue;
        // do an arbitrary operation on it that's specific
        // to the data type, just to show it works:   
        Serial.print("It's a number and its square is: ");
        Serial.println(copiedValue * copiedValue);
      }
      Serial.println();
    }
  }
}
