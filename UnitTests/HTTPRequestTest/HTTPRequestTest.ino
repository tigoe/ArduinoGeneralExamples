/*
  Test HTTP Client
  Context: Arduino, with WINC1500 module
*/
// include required libraries and config files
#include <SPI.h>
//#include <WiFi101.h>
#include <WiFiNINA.h>
//#include <ESP8266WiFi.h>    // use this instead of WiFi101 for ESP8266 modules
#include <ArduinoHttpClient.h>
#include "config.h"

WiFiClient netSocket;               // network socket to server
const char server[] = "www.example.com";  // server name
String route = "/";              // API route
long lastRequest = 0;
int requestDelay = 2000;
long requestCount = 0;

void setup() {

  Serial.begin(9600);               // initialize serial communication

  // while you're not connected to a WiFi AP,
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);           // print the network name (SSID)
    WiFi.begin(ssid, pass);         // try to connect
    delay(2000);
  }

  // When you're connected, print out the device's network status:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  if (millis() - lastRequest > requestDelay) {
    long startTime = millis();
    int newRequest = request(requestCount);
    long requestTime = millis() - startTime;
    Serial.println(newRequest);
    lastRequest = millis();
    requestCount++;
  }
}

int request(int result) {
  HttpClient http(netSocket, server, 80);      // make an HTTP client
  http.get(route);  // make a GET request
  delay(10);
  if (http.connected()) {       // while connected to the server,
    if (http.available()) {
      Serial.write(char(http.read()));
    }
  }
  Serial.println("Hit!");
  //  // when there's nothing left to the response,
  http.stop();                     // close the request
  return result;
}
