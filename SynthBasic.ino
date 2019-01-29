#include <LiquidCrystal.h>
#include <Keypad.h>
#include "notes.h"

byte currScale = 1;
//scale from 1 - 8.

  int noteSel = 0;

int freq = 33;
char key;
bool playStrobe = false;
char previous = 'A';
int strobeNote = 0;

int baseNotes[] = {33,35,37,39,41,44,46,49,52,55,58,62};

int melody[] = {
  G4, B4, D3, B4, D3, B4, D3, B4, D3, B4, D3, B4, D3, C5, D3, E5, C3, G4,
  C3, D5, E3, B4, E3, G4, E3, E5, E3, B4, E3, E5, G3, B4, G3, D5, G3, B4,
  G3, E5, C3, G4, C3, A4, C3, B4, C3, F5, F3, C5, F3, D5, G3, B4, G3, 
  F5, G3, B4, G3, F5, G3, B4, G3, A4, G3, B4, G3, G5, G3, A4, G3, F5, G3, 
  B4, G3, E5, G3, G4, G3, A4,
  B3, C5, B3, G5, C3, G4, C3, D5, E3, B4, E3, E5, E3, B4, E3, E5, E3, B4, 
  E3, E5, E3, G4, E3, D5, E3, B4, E3, E5, C3, G4, C3, A5, C3, B4, C3, F5, 
  F3, C5, F3, D5, 
  G3, B4, G3, F5, G3, B4, G3, F5, G3, B4, G3, F5,
  G3, A4, G3, G5, G3, B4, G3, E5, G3, B4, G3, B4, G3, C5
  
};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4
};

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'c','C','d','D'},
  {'E','f','F','g'},
  {'G','a','A','B'},
  {'s','S','T','R'}
};

//  C     C#    D     D#
//  E     F     F#    G
//  G#    A     A#    B
//  <Scl  Scl>  Tri   Saw

byte rowPins[ROWS] = {46, 48, 50, 52}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {38, 40, 42, 44}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS );
const int rs = 41, en = 39, d4 = 43, d5 = 45, d6 = 47, d7 = 49;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Press a key now.");
  Serial.begin(9600);
  //key = 'A';
}

void loop() {
  key = keypad.getKey();
  if(key) {
  bool isKey = false;
  switch (key){
    case 'c':  
      isKey=true;
      noteSel = 0;
      break;
    case 'C':
      isKey = true;
      noteSel = 1;
      break;
    case 'd':
      isKey = true;
      noteSel = 2;
      break;
    case 'D':
      isKey = true;
      noteSel = 3;
      break;
    case 'E':
      isKey = true;
      noteSel = 4;
      break;
    case 'f':
      isKey = true;
      noteSel = 5;
      break;
    case 'F':
      isKey = true;
      noteSel = 6;
      break;
    case 'g':
      isKey = true;
      noteSel = 7;
      break;
    case 'G':
      isKey = true;
      noteSel = 8;
      break;
    case 'a':
      isKey = true;
      noteSel = 9;
      break;
    case 'A':
      isKey = true;
      noteSel = 10;
      break;
    case 'B':
      isKey = true;
      noteSel = 11;
      break;
    default:
      isKey = false;
      break;
  }
  if(key!='R'){
    if (key=='s') { 
      if (currScale!=1) { 
        currScale--;
        freq=baseNotes[noteSel]*pow(2,currScale-1); 
      }
      else freq=baseNotes[noteSel]*pow(2,currScale-1);
      lcd.clear();
      lcd.print(previous);
      lcd.print(currScale);
      lcd.print(", f: " + String(freq) + "Hz");
      lcd.setCursor(0,1);
      lcd.print("Triangle");
    }
    else if (key=='S') { 
      if (currScale!=8){
        currScale++; 
        freq=baseNotes[noteSel]*pow(2,currScale-1);
      }
      else freq=baseNotes[noteSel]*pow(2,currScale-1);
      lcd.clear();
      lcd.print(previous);
      lcd.print(currScale);
      lcd.print(", f: " + String(freq) + "Hz");
      lcd.setCursor(0,1);
      lcd.print("Triangle");
    }
    else {
      freq=baseNotes[noteSel]*pow(2,currScale-1);
      strobeNote=0;
      playStrobe=false;
      lcd.clear();
      lcd.print(key);
      lcd.print(currScale);
      lcd.print(", f: " + String(freq) + "Hz");
      lcd.setCursor(0,1);
      lcd.print("Triangle");
      previous = key;
    }
  }
  else { 
    playStrobe = true; 
  }
  }
  if (playStrobe) {
    int noteDuration = 1000 / noteDurations[strobeNote];
    tone(8, melody[strobeNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    if (strobeNote>124) strobeNote=-1;
    strobeNote++;
    lcd.clear();
    lcd.print("f: " + String(melody[strobeNote]) + "Hz");
    Serial.println(key);
    lcd.setCursor(0,1);
    lcd.print("deadmau5: Strobe");
  }
  else tone(8, freq, 20);
}
