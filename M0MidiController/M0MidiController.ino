/*
  4-key MIDI piano controller

  Reads four pushbuttons, and when any of them have changed, sends
  MIDI noteon or noteoff messages. Sends an all notes off message
  when all buttons are released.

  With four buttons, there are 2^4, or 16, combinations. Each
  combination plays a different note, starting from the base note.

  Uses Serial1 for MIDI, so will work on any board with 2 hardware serial ports

  created 13 Feb 2017
  by Tom Igoe
*/

int keys[] = {5, 6, 9, 10};   // four pins for pushbuttons (keys)
int lastKeyState;             // previous state of the keys
int keyCount = 4;             // number of keys
int baseNote = 48;            // C4, used as the base note
int lastNote = 0;             // last note played
int lastpitchBendSensor = 0;

void setup() {
  Serial.begin(9600);                  // initialize serial
  Serial1.begin(31250);                // initialize MIDI serial

  for (int k = 0; k < keyCount; k++) { // iterate over the keys
    pinMode(keys[k], INPUT);           // make each an input
  }
}

void loop() {
  int currentKeyState = 0;  // holds the current state of all keys

  for (int k = 0; k < keyCount; k++) {     // iterate over the keys
    int thisKey = digitalRead(keys[k]);    // read each key
    bitWrite(currentKeyState, k, thisKey); // write it to currentKeyState
  }

  // read a 10-bit analog input and convert it to
  // 2 7-bit bytes, to send as the least significant byte (lsb)
  // and most significant byte (msb) of a pitch bend message:
  int pitchBendSensor = analogRead(A0);          // read analog input
  if (pitchBendSensor > 10 && lastNote !=0) {    // if it's > 10 and there's a note playing
    byte msb = highByte(pitchBendSensor << 1);   // get the high bits
    byte lsb = lowByte(pitchBendSensor);         // get the low 8 bits
    bitWrite(lsb, 7, 0);                         // clear the top bit
    midiCommand(0xE0, lsb, msb);                 // send the pitch bend message
  }

  // if the state of any of the keys has changed,
  // either play or release a note:
  if (currentKeyState != lastKeyState) {         // if any keys have changed
    Serial.println(currentKeyState, BIN);        // print state of all the keys
    if (currentKeyState > lastKeyState) {        // if current > last,
      // then a key has been pressed
      int newNote = currentKeyState + baseNote;  // calculate note
      midiCommand(0x90, newNote, 127);           // send noteOn (0x90)
      Serial.print(newNote, HEX);                // print note
      Serial.println(" on");
      lastNote = newNote;                        // save for next noteOff
    } else {                                     // if current < last,
      // then a key has been released
      midiCommand(0x80, lastNote, 127);          // send noteOff (0x80);                          // clear lastNote
      Serial.print(lastNote, HEX);               // print last note
      Serial.println(" off");
      lastNote = 0;
    }
  }

  // this algorithm isn't perfect, and results in some "stuck notes"
  // so if currentKeyState == 0 (all keys released),
  // then send a control message, all notes off:
  if (currentKeyState == 0 && lastKeyState != 0) {
    midiCommand(0xB0, 0x7B, 0x00);
    Serial.println("all notes off");
  }

  // save the state of all keys for next time:
  lastKeyState = currentKeyState;               // save previous state of keys
}

// send a 3-byte midi message
void midiCommand(byte cmd, byte data1, byte  data2) {
  Serial1.write(cmd);     // command byte (should be > 127)
  Serial1.write(data1);   // data byte 1 (should be < 128)
  Serial1.write(data2);   // data byte 2 (should be < 128)
}


