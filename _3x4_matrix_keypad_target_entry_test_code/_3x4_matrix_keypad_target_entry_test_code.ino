#include "Keypad.h"
 
const byte ROWS = 4; // number of rows
const byte COLS = 3; // number of columns
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
byte colPins[COLS] = {4, 3, 2};    // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


int targetrow = 0;
int targetcol = 0;
char key;
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  inputTarget();
  Serial.print("Target: ");
  Serial.print(targetrow);
  Serial.print(",");
  Serial.println(targetcol);
  delay(1000);
}

void inputTarget() {
key = "";
Serial.println("* error reenter, # enter next");
  Serial.println("Enter Target Row");
  while (key != '#' ) {
    key = keypad.getKey();
    if (key == '*') {
      targetrow = 0;
      Serial.println("Re-enter Target Row");
    } else {
      if (key != '#') {
        targetrow = convertINT(key);
    } 
    }
  }
  key = "";
  Serial.println("* error reenter, # enter next");
  Serial.println("Enter Target Column");
  while (key != '#' ) {
    key = keypad.getKey();
    if (key == '*') {
      targetcol = 0;
      Serial.println("Re-enter Target Column");
    } else {
     if (key != '#') { 
    targetcol = convertINT(key);
    } 
    }
  }
}

int convertINT(char temp) {
  
  if (temp == '0') {Serial.println("This is 0");return 0;}
  if (temp == '1') {return 1;}
  if (temp == '2') {return 2;}
  if (temp == '3') {return 3;}
  if (temp == '4') {return 4;}
  if (temp == '5') {return 5;}
  if (temp == '6') {return 6;}
  if (temp == '7') {return 7;}
  if (temp == '8') {return 8;}
  if (temp == '9') {return 9;}
  return -1;
}

