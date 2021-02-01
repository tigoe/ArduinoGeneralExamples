/*
  Example for Serial Studio and Nano 33 IoT
  Reads a joystick on A0, A1, and D2
  and the accelerometer and gyro on a Nano 33 IoT
  Serial Studio download: https://github.com/Serial-Studio/Serial-Studio/tags
  Tutorial: https://www.alex-spataru.com/blog/introducing-serial-studio
  Uses the following library:
  http://librarymanager/All#Arduino_LSM6DS3
  The circuit:
  - Joystick H axis attached to pin A0
  - Joystick V axis attached to pin A1
  - Nano 33 IoT built-in LSM6DS6 IMU

  Included in the project folder are 3 JSON files for Serial Studio:
  joystick.json, imu.json, combined.json
  Comment out the lines you don't need

  created 1 Feb 2021
  by Tom Igoe
*/
#include <Arduino_LSM6DS3.h>

// pin for the pushbutton:
const int buttonPin = 2;

void setup() {
  Serial.begin(9600);
  // stop until serial port is open:
  while (!Serial);
  // initialize the pushbutton:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialise the IMU:
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (true);
  }
}

void loop() {
  // arrays for the accel and gyro readings:
  float accel[3];
  float gyro[3];

  // read joystick: h, v, button
  int horizontal = analogRead(A0);
  delay(1);
  int vertical = analogRead(A1);
  int buttonState = digitalRead(buttonPin);
  // read accelerometer:
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accel[0], accel[1], accel[2]);
  }
  // read gyroscope:
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyro[0], gyro[1], gyro[2]);
  }
  // print them all:
  Serial.print("/*");
  Serial.print("Joystick and IMU,");
  Serial.print(horizontal);
  Serial.print(",");
  Serial.print(vertical);
  Serial.print(",");
  Serial.print(buttonState);
  for (int axis = 0; axis < 3; axis++) {
    Serial.print(",");
    Serial.print(accel[axis]);
  }
  for (int axis = 0; axis < 3; axis++) {
    Serial.print(",");
    Serial.print(gyro[axis]);
  }
  Serial.println("*/");
}
