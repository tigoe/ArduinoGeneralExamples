/*
   The Arduino models based on the SAMD M0+ processor, 
   including the MKR series of boards and the Nano 33 IoT,
   have a built-in digital-to-analog converter. This means 
   that they can output a true changing voltage from 0V to
   the supply voltage of the board (3.3V for most of them).

   This example demonstrates DAC output on those boards.
   It outputs a sinewave from 0-3.3V on pin A0.

   created 19 Nov 2019
   by Tom Igoe
*/

float inputValue = 0.0;  // input value for the sine function

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // set the DAC resolution to 10 bits:
  analogWriteResolution(10);
}

void loop() {
  // change the input by 1 degree:
  inputValue = inputValue + PI / 180;
  // get the sine of the input:
  float sineValue = sin(inputValue);
  // range of sine is -1 to 1. Scale to 0 - 1023:
  float outputValue = (sineValue * 512) + 512;
  // output:
  Serial.println(outputValue);
  // the DAC on the MKR boards and the Nano 33 IoT is on pin A0:
  analogWrite(A0, outputValue);
}
