/*
  OSX sleep control

  This sketch for Arduino 32U4-based boards (Leonardo, micro, Yun, etc)
  emulates a keyboard and mouse to put an OSX computer to sleep.
  
  In order to make this work, you need to choose the mac's screen saver 
  hot corners and set the bottom left corner to "sleep".
  
  Then, when there's a high-going change on D3, the Arduino
  will either send a mouse move to get the mouse in the corner for sleep,
  or send a spacebar keystroke to wake it up.
  
  created 10 Oct 2014
  by Tom Igoe
  
*/

int lastSensor = 0;        // last sensor reading
boolean sleeping = false;  // state of the computer

void setup() {
  pinMode(3, INPUT);   // make D3 an input
}

void loop() {
  int sensor = digitalRead(3);    // read D3
  if (lastSensor < sensor) {      // look for a high-going change
    signalComputer(sleeping);     // signal the computer
    sleeping = !sleeping;         // toggle the sleep state
  }
  lastSensor = sensor;            // save sensor reading for next loop
}

void signalComputer(int asleep) {
  if (asleep == true) {      // if computer is asleep, wake it:
    Keyboard.begin();        // take control of keyboard
    Keyboard.print(" ");     // send a space bar
    Keyboard.end();          // release keyboard control
  } else {
    for (int x = 0; x < 500; x++) {
        Mouse.begin();         // take control of the mouse
      Mouse.move(-50, 50 , 1); // move to lower left corner
      Mouse.end();             // release mouse
      }
  }
}
