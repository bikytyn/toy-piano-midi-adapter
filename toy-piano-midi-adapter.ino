/*
  Toy Piano to USB MIDI Adapter
  Target: Arduino Micro (ATmega32U4)
  Description: Converts a 54-key children's keyboard resistive matrix into native USB MIDI.
*/

#include <MIDIUSB.h>

const int numRows = 7;
const int numCols = 8;

// Rows (Left ribbon)
const int rowPins[numRows] = {2, 3, 4, 5, 6, 7, 8};

// Columns (Right ribbon - mapped to match physical layout)
const int colPins[numCols] = {A3, A2, A1, A0, 15, 14, 16, 10};

// State matrix for key tracking and debounce
bool lastKeyState[numRows][numCols];

void setup() {
  // Setup row pins as outputs (default HIGH)
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  
  // Setup column pins as inputs with internal pull-ups
  for (int j = 0; j < numCols; j++) {
    pinMode(colPins[j], INPUT_PULLUP);
  }
  
  // Initialize state array
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      lastKeyState[i][j] = HIGH;
    }
  }
}

void loop() {
  for (int i = 0; i < numRows; i++) {
    // Pull current row LOW
    digitalWrite(rowPins[i], LOW);
    
    for (int j = 0; j < numCols; j++) {
      // Compensate for serpentine (zig-zag) PCB trace layout on odd rows
      int colIndex = (i % 2 == 1) ? (numCols - 1 - j) : j;
      int keyIndex = (i * numCols) + colIndex;
      
      if (keyIndex >= 54) continue; // Limit to 54 keys

      bool pressed = (digitalRead(colPins[j]) == LOW);

      if (pressed != lastKeyState[i][j]) {
        byte midiNote = 36 + keyIndex; // 36 = C2 (adjust base note as needed)
        
        if (pressed) {
          noteOn(0, midiNote, 100);
        } else {
          noteOff(0, midiNote, 0);
        }
        
        lastKeyState[i][j] = pressed;
        delay(3); // Small debounce delay
      }
    }
    
    // Return current row HIGH
    digitalWrite(rowPins[i], HIGH);
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}
