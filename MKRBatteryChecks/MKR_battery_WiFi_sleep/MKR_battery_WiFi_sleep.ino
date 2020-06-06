/**----------------------------------
  Check battery level once a second and write to an SD card
  Circuit:
      SD card in a MKR Zero

  created 18 Mar 2019
  by Tom Igoe
*/

#include <RTCZero.h>
#include <SPI.h>
#include <WiFi101.h>      // for MKR1000 modules
//#include <WiFiNINA.h>       // for MKR1010 modules
//#include <ESP8266WiFi.h>  // for ESP8266 modules
// include libraries for HTTP calls and JSON formatting:
#include <ArduinoHttpClient.h>
#include <Arduino_JSON.h>
#include "arduino_secrets.h"    // sensitive information

RTCZero rtc;
int days = 0;
volatile bool awake = true;

WiFiSSLClient netSocket;  // network socket to server
String route = "/data";   // API route
JSONVar currentStatus;       // JSON for sensor data
JSONVar requestBody;      // JSOn for body of the request
String contentType = "application/json";  // content type header

// the HTTP client is global so you can use it in multiple functions below:
HttpClient client(netSocket, SECRET_SERVER, 443);
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);              // initialize serial communication
  pinMode(LED_BUILTIN, OUTPUT);
  if  (!Serial) delay(2000);

  // start RTC:
  rtc.begin();
  // turn network connection LED off:
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.maxLowPowerMode();
  connectToNetwork();

  rtc.setAlarmTime(0, 0, 20);
  rtc.enableAlarm(rtc.MATCH_MMSS);
  rtc.attachInterrupt(wake);
}

void loop() {
  if (awake) {
    // Format a string like so:
    // d-m-y_hh:mm:ss
    String timestamp =  String(rtc.getDay()) + "-";
    timestamp += String(rtc.getMonth()) + "-";
    timestamp += String(rtc.getYear()) + "_";
    if (rtc.getHours() <= 9) timestamp += "0";
    timestamp += String(rtc.getHours())  + ":";
    if (rtc.getMinutes() <= 9) timestamp += "0";
    timestamp += String(rtc.getMinutes())  + ":";
    if (rtc.getSeconds() <= 9) timestamp += "0";
    timestamp += String(rtc.getSeconds());

    // caclulate uptime:
    unsigned long uptime = rtc.getEpoch() - startTime;
    int upSeconds = uptime % 60;
    int upMinutes = (uptime / 60) % 60;
    int upHours = (uptime / 3600) % 24;
    int upDays = (uptime / 86400);
    // convert to a string 0:00:00:00:
    String uptimeStamp =  String(upDays) + ":";
    if (upHours <= 9) uptimeStamp += "0";
    uptimeStamp += String(upHours) + ":";
    if (upMinutes <= 9) uptimeStamp += "0";
    uptimeStamp += String(upMinutes) + ":";
    if (upSeconds <= 9) uptimeStamp += "0";
    uptimeStamp += String(upSeconds);

    currentStatus["timestamp"] = timestamp;
    currentStatus["uptime"] = uptimeStamp;
    // Write to the server:

    // turn off the LED before sleeping:
    digitalWrite(LED_BUILTIN, LOW);

    // add the sensor data to the request body:
    requestBody["data"] = JSON.stringify(currentStatus);
    if (Serial) Serial.println(JSON.stringify(requestBody));
    // make the request:
    client.post(route, contentType, JSON.stringify(requestBody));

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    if (Serial) Serial.print("Status code: ");
    if (Serial) Serial.println(statusCode);
    if (Serial) Serial.print("Response: " );
    if (Serial) Serial.println(response);
    // when there's nothing left to the response,
    client.stop();           // close the request

    // if disconnected from WiFi, attempt to reconnect:
    if (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_BUILTIN, LOW);
      connectToNetwork();
    }

    // put the processor to sleep until the next hour:
    awake = false;
    rtc.standbyMode();
  }
}

// when the processor wakes up, set awake = true:
void wake() {
  awake = true;
}


void connectToNetwork() {
  byte mac[6];

  // try to connect to the network:
  while ( WiFi.status() != WL_CONNECTED) {
    if (Serial) Serial.println("Attempting to connect to: " + String(SECRET_SSID));
    //Connect to WPA / WPA2 network:
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(2000);
  }
  if (Serial) Serial.println("connected to: " + String(SECRET_SSID));
  // You're connected, turn on the LED:
  digitalWrite(LED_BUILTIN, HIGH);

  // get your MAC address:
  WiFi.macAddress(mac);
  IPAddress ip = WiFi.localIP();
  if (Serial) Serial.print(ip);
  if (Serial) Serial.print("  MAC Address: ");
  if (Serial) Serial.print(macToString(mac));
  requestBody["macAddress"] = macToString(mac);
  requestBody["sessionKey"] = SECRET_SESSIONKEY;

  if (Serial) Serial.print("  Signal Strength: ");
  if (Serial) Serial.println(WiFi.RSSI());

  // set the time from the network:

  while (startTime == 0) {
    if (Serial) Serial.println("Attempting to get network time");
    startTime = WiFi.getTime();
    delay(2000);
  }

  rtc.setEpoch(startTime);
  if (Serial) Serial.println(String(rtc.getHours()) +
                               ":" + String(rtc.getMinutes())  +
                               ":" + String(rtc.getSeconds()));
}

// convert the MAC address to a String:
String macToString(byte mac[]) {
  String result;
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      result += "0";
    }
    result += String(mac[i], HEX);
    if (i > 0)  result += ":";
  }
  return result;
}
