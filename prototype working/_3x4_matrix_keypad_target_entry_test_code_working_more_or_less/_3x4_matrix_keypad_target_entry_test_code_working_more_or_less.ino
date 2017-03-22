#include "Keypad.h"
 
const byte keyROWS = 4; // number of rows
const byte keyCOLS = 3; // number of columns
char keys[keyROWS][keyCOLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte rowPins[keyROWS] = {49,47,45,43};
byte colPins[keyCOLS] = {41,39,37};

//byte rowPins[keyROWS] = {8, 7, 6, 5}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
//byte colPins[keyCOLS] = {4, 3, 2};    // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, keyROWS, keyCOLS);


int targetrow = -999;
int targetcol = -999;
char key;

int ROWS = 3;
int COLS = 5;
 
void setup()
{
  Serial.begin(9600);
  Serial.write(17);
}
 
void loop()
{
 while (targetrow < 0 || targetrow > ROWS) {
  Serial.write(12);
  Serial.print("Row? ");
  targetrow = inputTarget();
  if (targetrow > ROWS) {Serial.println("Out of Bounds");}
 }
 while (targetcol < 0 || targetcol > COLS) {
  Serial.write(12);
  Serial.print("Col? ");
  targetcol = inputTarget();
  if (targetcol > COLS) {Serial.println("Out of Bounds");}
 }
 Serial.write(12);
  Serial.print("Target: ");
  Serial.print(targetrow);
  Serial.print(",");
  Serial.println(targetcol);
  delay(1000);
  targetrow = -999;
  targetcol = -999;
}



int inputTarget() {

key=0;
 while(!key)  // Check for a valid key.
  {
    key = keypad.getKey();
  }
    //switch (key)
    //{
     //   default:
     Serial.print(" ");
     Serial.println(key);
        if (key-48>=17) {return (key-55);} else { return(key-48);}
        
    //}
}

