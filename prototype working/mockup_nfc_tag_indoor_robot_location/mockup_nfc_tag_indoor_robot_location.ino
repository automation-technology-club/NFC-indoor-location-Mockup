/*Mockup for mapping system using NFC tags for indoor robot 
 * location system.
 * 
 * Copyright(c) 2017, LeRoy Miller
 * 
 * Currently working on a UNO, but will probably need a MEGA
 * after NFC reader is added, and Bittybot library is added.
 * 
 * A compass maybe used for turning the robot left and right.
 * 
 */


int start = 107; //mockup starting location, this will be read by the NFC reader
int target = 67; //Target location to move the robot too
int targetrow;
int targetcol;
int row;
int col;

//My Gird is 3 x 5 (0,0 to 2,4) - I am using the "Checksum" of the RFID
//tags
int codes[3][5] = {
  {67,121,127,117,107},
  {137,147,157,103,97},
  {143,133,187,177,183},
};  //Map of NFC codes (currently just numbers) will be codes read

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Current Map:");
int a, b;
  for (a = 0; a < 3; a++) {
    for (b = 0; b < 5; b++) {
      Serial.print(codes[a][b]);
      Serial.print(' ');
    }
    Serial.println();
      }
      Serial.println();
  Serial.print("Target: ");
  Serial.println(target);
  Serial.print("Target location: ");
  findnumbers(target);
  targetrow = row;
  targetcol = col;
  Serial.print("Robot Start: ");
  Serial.println(start);
  Serial.print("Start Location: ");
  findnumbers(start);
  calculatemove();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void findnumbers(int findnumber) {
int a, b;
  for (a = 0; a < 3; a++) {
    for (b = 0; b < 5; b++) {
      if (findnumber == codes[a][b]) {
        row = a;
        col = b;}
      }
  }
  Serial.print(row);
  Serial.print(",");
  Serial.println(col);
}

void calculatemove() {

/*This is the logic for the move, but currently only tells
 * a direction and how far the robot should move, it will should
 * recalculate each time it reads a new NFC tag, until target is
 * reached.
 */

  if (targetrow > row) {
    Serial.print("Move down ");
    Serial.print(targetrow - row);
    Serial.println(" rows.");
      }
  if (targetrow < row) {
    Serial.print("Move up ");
    Serial.print (row - targetrow);
    Serial.println(" rows.");
  }
  if (targetrow == row) {
    Serial.println("We are on the correct row.");   
  }
  if (targetcol > col) {
    Serial.print("Move ");
    Serial.print(targetcol - col);
    Serial.println(" columns to the right");
  }
  if (targetcol < col) {
    Serial.print("Move ");
    Serial.print(col - targetcol);
    Serial.println(" columns to the left.");
  }
  if (targetcol == col) {
    Serial.println("At the target column");
  }
  if (targetcol == col && targetrow == row) {
    Serial.println("We are at target.");
  }
}

