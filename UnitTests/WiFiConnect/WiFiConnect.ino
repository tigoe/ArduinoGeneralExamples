/*
  Minimal test to see if WiFi library can connect to a WiFi
  access point. Does nothing else.

  created 16 Feb 2020
  by Tom Igoe
*/

#include <SPI.h>       // WiFi radios use SPI to communicate with processor
#include <WiFiNINA.h>  // use this for MKR 1010, Nano 33 IoT
//#include <WiFi101.h> // use this for MKR1000

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // wait until the serial monitor is open:
  while (!Serial);

  //  while the WiFi radio is not connected to a
  // WiFi Access Point, keep trying to connect:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Trying to connect");
    WiFi.begin("ssid", "password");
    // 2 second delay between attempts
    // to be polite to the access point:
    delay(2000);
  }
  // you'll only get here if you connected successfully:
  Serial.println("connected");

}

void loop() {
  // nothing happens here. Your test is done
}
